#ifndef CELL_H
#define CELL_H
#include <iostream> 
using namespace std; 

//--------Cell Class Prototype---------------
class Cell {
public:
   // Default constructor
   Cell();

   // Destroy a given wall of the cell
   void destroyWall(int wallVal);

   // Sets the name of the cell to one given by the user
   void setName(int newName);

   // Sets a given value to a given wall
   void setWall(int wallVal, int newVal);

   int getName() const;

   // print the bottom and right sides of the cell
   void print();

   // return the current values of the bottom and right sides
   void getSides(string &x, string &y);

   bool operator <(const Cell &rhs) const;

   bool operator ==(const Cell &rhs) const;

   Cell &operator = (const Cell &rhs);

   int getWallVal(int wall_ind) {
     if (wall_ind == TOP) return topVal;
     else if (wall_ind == BOTTOM) return bottomVal;
     else if (wall_ind == RIGHT) return rightVal;
     else return leftVal;
   }

private:
   static const int TOP = 0;
   static const int LEFT = 3;
   static const int BOTTOM = 1;
   static const int RIGHT = 2;

   // values to differentiate between the walls
   int topVal, bottomVal, leftVal, rightVal;

   // string value of the cell walls in order to print
   string top, bottom, left, right;

   // Set that contains the cell
   int name;
};
//-----End of Cell Class Prototype-------------------
#endif 
