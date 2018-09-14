/*
*Team:
*
*Valentin Trujillo - A01328426
*
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <queue>
#include <unordered_set>

using namespace std;

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

int main(){
    //create data structures
    queue <string> linksToVisit;
    unordered_set <string> visitedLinks;

    string url = "http://javax.mty.itesm.mx/redes2/";
    string folder = "outputs/"; //Make sure this folder exists, if not err 256 is thrown
    string fileName = "insideOutput";
    string command = "";
    int n = 0;
    string a = "";
    exLinkSearch(url, command, folder, fileName);

    //extracting Urls From File Created
    ifstream infile("./"+folder+"/" + fileName);
    while (infile >> a) {
        linksToVisit.push(a);
    }

// Una vez que hemos extraido una vez los url, aqui podemos usar los hilos, uno por cara link principal.
    while (!linksToVisit.empty()){
       a = linksToVisit.front();
       exLinkSearch(url+a, command, folder, fileName+to_string(n));

       linksToVisit.pop();
       n++;
    }
    return 0;
}
