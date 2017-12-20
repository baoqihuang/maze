#include <iostream> 
#include "Cell.h"
using namespace std; 

//------Cell Class Definitions----------------------
// Initialize topVal, leftVal, bottomVal, rightVal, top, bottom, left, right and name
Cell::Cell() : topVal(1), bottomVal(1), leftVal(1), rightVal(1),
                     top("_"), bottom("_"), left("|"), right("|"), name(-1) {}

//  The function returns true if the wall was destroyed or false if it was not
void Cell::destroyWall(int wallVal) {
   switch(wallVal) {
      case TOP:
                     if (topVal != 0 && topVal != -1) {
                        topVal = 0;
                        top = " ";
                     }
                     break;
      case LEFT:
                     if (leftVal != 0 && leftVal != -1) {
                        leftVal = 0;
                        left = " ";
                     }
                     break;
      case BOTTOM:
                     if (bottomVal != 0 && bottomVal != -1) {
                        bottomVal = 0;
                        bottom = " ";
                     }
                     break;
      case RIGHT:
                  if (rightVal != 0 && rightVal != -1) {
                     rightVal= 0;
                     right= " ";
                  }
                  break;
   }
}

void Cell::setName(int newName) {
   name = newName;
}

void Cell::setWall(int wallVal, int newVal){
	switch(wallVal){
	case TOP:
                  topVal= newVal;
                  if (topVal ==0)
                     top = " ";
                  break;
	case LEFT:
                  leftVal= newVal;
                  if (leftVal ==0)
                     left = " ";
                  break;
	case BOTTOM:
                  bottomVal= newVal;
                  if (bottomVal == 0)
                     bottom = " ";
                  break;
	case RIGHT:
                  rightVal= newVal;
                  if (rightVal == 0)
                     right = " ";
                  break;
	}//end switch

}//end setWall

int Cell::getName() const {
   return name;
}

void Cell::print() {
   cout << bottom << right;
}

void Cell::getSides(string &x, string &y) {
   x = bottom;
   y = right;
}

bool Cell::operator <(const Cell &rhs) const {
   return (name < rhs.name);
}

bool Cell::operator ==(const Cell &rhs) const {
   return (name == rhs.name);
}

Cell &Cell::operator =(const Cell &rhs) {
   if (this != &rhs)
      name = rhs.name;

   return *this;
}
//------End of Cell Class Definition--------------
