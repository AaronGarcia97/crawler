//by Aarón Garcia, Daniela Garcia, Edagr Lopez, Valentin Trujillo

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

//create data structures
queue <string> linksToVisit;
unordered_set <string> visitedLinks;
vector<string> visitedLinksList;

//Check if processor is available, if not exit
void processorAvailableDoNext(){
  cout << "Checking if processor is available... " << endl;
  if (system(NULL))
      puts ("Ok");
  else
      exit (EXIT_FAILURE);
}

//Concatenate command
string buildCommand(string action, string url, string pathToFile){
  string command = "";

  command += action;
  command += url;
  command += " > ";
  command += pathToFile;

  return command;
}

//Executes command that searches for children URIs
int exLinkSearch(string url, string command, string folder, string fileName ){

    command = buildCommand("./parserInside ", url, folder+fileName);

    processorAvailableDoNext();

    cout << "Executing command " << command << " ..." << endl;
    int err; //1 = error, 0 = success

    if ((err = system(command.c_str()))){//Error >= 1, system call with char ptr
        cout << "There was an error " << err << endl;
        return 1;
    }
    else{ //Success
        cout << "Result stored at " << folder << fileName << " file" << endl;
    }
    return 0;
}

//Checks if is a pdf or ppt
/*
UPGRADE:
  Create an unordered_set with common file terminations that we don't want to add
  and check for set.find(uriEnding) each time, so that we can check
  for multiple links in O(1). Load the un_set at the beginnning.
*/
bool isPdfOrPpt(const string uri){
    if(uri.length() < 4) return false;

    string uriEnding = uri.substr(uri.length()-4);

    if( uriEnding == ".pdf" || uriEnding == ".ppt" ){
      return true;
    }
    return false;
}

// Function that extracts Urls From specified file and
// pushes them to the queue if not visited
void extractURL(string folder, string fileName, string url, string &uri){
  ifstream infile(folder + fileName);
  while (infile >> uri) { //mientras haya linea
      if( visitedLinks.find(url+uri) == visitedLinks.end() && !isPdfOrPpt(uri)){ //si no lo hemos visiatdo el link && Si no es pdf o ppt              //
          cout << "## Inserting... " << uri << endl;
          linksToVisit.push(uri);                  //la metemos al queue
          visitedLinks.insert(url+uri);           //lo metemos al set
          visitedLinksList.push_back(uri);        //metemos uri a la lista (vector)
          cout << "XX DONE ------> " << linksToVisit.back() << endl;
      }
  }
}


int main(int argc, char *argv[]){
    string url = "https://www."; // "https://www.dinlabel.com/"; //"https://www.dinlabel.com/";//http://gigamonkeys.com/book/";//http://javax.mty.itesm.mx/redes1/
    string folder = "outputs/"; //Make sure this folder exists, if not err 256 is thrown
    string fileName = "insideOutput";
    string command = "";
    string uri = "";

    int n = 1;
    int maxLinks = 0;

    /* Check you pass domain as argument */
    if( argc != 2 ) {
      fprintf(stderr,"Incorrect Format! Use it like this:\n %s [URL] \n %s webpageToBeCrawled.com\n", argv[0], argv[0]);
	    exit(-1);
    } else {
      url += argv[1];
    }

    do{
      cout << "Max links(Limit 300): ";
      cin >> maxLinks;
    }while(maxLinks > 300);

    exLinkSearch(url, command, folder, fileName);

    extractURL(folder, fileName, url, uri);

    while (!linksToVisit.empty() && n <= maxLinks){ //If stuff gets out of control(or page too big) break it at 300
       uri = linksToVisit.front();
       exLinkSearch(url+uri, command, folder, fileName+to_string(n));  //Get links from front URI
       linksToVisit.pop();
       extractURL(folder, fileName+to_string(n), url, uri);  //Push new links to the queue
       n++;
    }

    cout << "################################################################################" << endl;
    //Display visited URIs
    for(int i=0; i < visitedLinksList.size(); ++i){
      cout << i+1 << ": " << visitedLinksList[i] << endl;
    }

    return 0;
}
