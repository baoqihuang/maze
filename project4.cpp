//============================================================================
// Name        : project4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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
#include "Maze.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;

bool checkIfValid(int x);
void getMazeInfo(int &sideLength);
//-------End of Main Function Prototype------------------

int main() {
   int sideLength;
   int choice;
   Maze myMaze;

   cout << "Would you like to randomly generate a maze(Press 1)\nor read in a maze from a file(Press 2): ";
   cin >> choice;

   while (choice != 1 && choice != 2) {
      cout << "Only 1 and 2 is valid. Choose again: ";
      cin >> choice;
   }

   if (choice == 1) {
       // Prompt the user to enter the length of the maze side
      getMazeInfo(sideLength);

      // Initialize a maze
      Maze myMaze(sideLength);

      // Create a maze
      myMaze.createMaze(71);

      // print the maze
      myMaze.print();

      // Find the path of the maze
      std::vector<int> pathInds;
      myMaze.findPathBFS(pathInds);
      myMaze.findPathDFS(pathInds);
   }

   else {
      // Read maze from a file
      myMaze.createMaze("mazeInfo.txt");

      // Print the maze
      myMaze.print();

      // Find the path of the maze
      std::vector<int> pathInds;
      myMaze.findPathBFS(pathInds);
      myMaze.findPathDFS(pathInds);
   }

	return 0;
}

//-------Main Function Definition-------------
/**
Checks whether the requested dimensions are legal.
Returns true if they are within the limits and false otherwise.
*/
bool checkIfValid(int x) {
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




