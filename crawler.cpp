#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

int main()
{
    //create data structures
    queue <string> linksToVisit;
    unordered_set <string> visitedLinks;

    string url = "http://javax.mty.itesm.mx/redes2/";
    string folder = "outputs/"; //Make sure this folder exists, if not err 256 is thrown
    string fileName = "insideOutput";
    string command = "";

    //Ask for user input url here in the future

    //Build command to b executed
    command = buildCommand("./parserInside ", url, folder+fileName);

    processorAvailableDoNext();

    cout << "Executing command " << command << " ..." << endl;

    int err; //1 = error, 0 = success

    if ((err = system(command.c_str()))){ //Error >= 1, system call with char ptr
        cout << "There was an error " << err << endl;
        return 1;
    }
    else{ //Success
        cout << "Result stored at " << folder << fileName << " file" << endl;
    }

    //If error everything went succesfull (error = 0) then do:
      //extractUrlsFromFileCreated(folder+fileName);
      //put them in a queue
      //search links inside of queue.front()
      //insert queue.front() to set
      //queue.pop()
      //repeat with every URL, until queue is empty

    return 0;
}
