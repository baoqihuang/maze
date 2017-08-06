#ifndef MAZE_H
#define MAZE_H

#include <iostream> 
#include <fstream> 
#include <list> 
#include <vector> 
#include "DisjSets.h"
using namespace std; 

class Maze {
public: 
   Maze() { }
   Maze(int sideLength); 
   
   void setUpMaze();          // Sets up the maze by setting all outside values to -1
                                          // and destroying the outside walls of the entrance and exit 
   void createMaze();         //  Create a maze by randomly picking and destroying walls 
   bool checkIfMaze();        // Checks whether the first and last cells (entrance and exit) are 
                                          // within the same set - thus indicating a maze has been created 
   void print();                    // prints out the maze
   
   


private: 
   /*static const int TOP = 1; 
   static const int LEFT = 2; 
   static const int BOTTOM = 3; 
   static const int RIGHT = 4; */
   
   static const int TOP = 0; 
   static const int LEFT = 3; 
   static const int BOTTOM = 1; 
   static const int RIGHT = 2; 
   
   //void checkBottom(int size, int side, int index); 
   //void checkRight(int size, int side, int index); 
   //void checkTop(int size, int side, int index); 
   //void checkLeft(int size, int side, int index); 
   int decideCellIndex(int cellIndex, int wallVal); 
    void genRandAdjRooms(int & r1,  int & w1,  int & r2, int & w2);
   
   int myHeight, myWidth;  // Height and width of the maze respectively 
   int mySize;                      // Total number of cells in the maze 
   DisjSets mySets;             // Array of the sets that make up the maze 
   list<int> myList;             // List of all possible cells not already contained within set zero
}; 

#endif 