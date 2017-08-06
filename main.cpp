#include <iostream>
#include <fstream>
#include <string> 
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include "Cell.h"
#include "DisjSets.h"
#include "RandGen.h"
#include "maze.h"
using namespace std;



// Main 
bool checkIfValid(int x);
void getMazeInfo(int &sideLength);
void createMazeFromFile(vector<vector<int> > & mazeCellsInfo, string const & filename); 
void printMaze(vector<vector<int> > const & mazeCellsInfo);

int main() {	
   int sideLength = 10; 
   
   getMazeInfo(sideLength); // Prompt the user to enter the length of the maze side 
   for (int i=0; i<20; ++i) {
      Maze myMaze(sideLength); // Initialize a maze
      myMaze.createMaze(); // Create a maze
      myMaze.print(); // print the maze  
   }

    std::vector<std::vector<int> > mazeCellsInfo;
    createMazeFromFile(mazeCellsInfo, "mazeInfo.txt");
    
    for (int i=0; i<mazeCellsInfo.size(); ++i) {
       for (int j=0; j<mazeCellsInfo[i].size(); ++j)
          cout << mazeCellsInfo[i][j] << ' ';
      cout << endl;
    }
    
    //cout <<"   "<<"__"<<"__"<<"__"<<"__"<<endl;
    //cout <<" |"<<" |"<<" |"<<" |"<<" |"<<" |"<<endl;
 
   char tmpChar;
   cin >> tmpChar;
	return 0;

}

/**
Checks whether the requested dimensions are legal. 
Returns true if they are within the limits and false otherwise.
*/
bool checkIfValid(int x){
	bool isValid= true;
	if(x <= 2) {
		cout<<"Invalid dimensions: "<<x<<endl;
		isValid= false;
	} else if(x >60) {
		cout <<"Dimensions chosen are too large: " << x << endl;
		isValid= false;
	}
	return isValid;
}

/**
Get the information of the maze to be created and
call on generateMazes in order to create the maze.
*/
void getMazeInfo(int &sideLength) {
   bool valid; 
   
   do {
      cout<<"Enter size of maze: "<<endl;
      cin >> sideLength;
	
      valid = checkIfValid(sideLength);
      if (!valid)
         cout << "Invalid input. Try again\n"; 
	} while (!valid);	
}


void createMazeFromFile(vector<vector<int> > & mazeCellsInfo, string const & fileName) {
   // Get the name of the file 
   /*string fileName; 
   cout << "Please enter the file name: \n"; 
   cin >> fileName; */
   
  // ifstream inFile(fileName, ios::in); 
  ifstream inFile(fileName.c_str()); 

   // Check if the file has been opened successfully 
   if (!inFile.is_open()) 
      throw runtime_error("Open maze input file failed.\n");
   
   int sideLength; 
   inFile >> sideLength; 
   int lineNum = sideLength * sideLength;
   
   mazeCellsInfo.clear();
   
   for (int i = 0; i < lineNum; ++i) {
       vector<int> cellInfo(4,1);
       for (int j = 0; j < 4; ++j) 
          inFile >> cellInfo[j];
        mazeCellsInfo.push_back(cellInfo);  
   } 
   
}


void printMaze(vector<vector<int> > const & mazeCellsInfo)
{
    /*int cellNum = mazeCellsInfo.size();
    int mazeLen = (int) sqrt((double)cellNum);
     // first print the top wall of maze
     cout << " ";  // the entrance
     for (int i=1; i<mazeLen; ++i)
        cout <<"_";
      cout << endl;
    
    
    int cell_id = 0;
    // loop over all  rows
    for  (int ir=0; ir<mazeLen; ++ir) {
       // now for each row, first print left wall of all cells, need to compensate the last right wall
       for (int ic=0; ic<mazeLen; ++ic) {
          int leftWallVal = mazeCellsInfo[ir*mazeLen + ic][3];
          cout << 
       }
       
    }*/
    
     
   
   
   
   
}






