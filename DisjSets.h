#ifndef DISJSETS_H
#define DISJSETS_H
#include "Cell.h"
#include <vector>

class DisjSets {
public: 
   DisjSets() { }
   explicit DisjSets(int numElements); 
   
   int find(int x); 
   void unionSets(int root1, int root2); 
   int getSize() const; 
   void setWall(int wallVal, int index, int newVal); 
   void destroyWall(int wallVal, int index); 
   void print(int index); 
   void getSides(int index, string &bottom, string &right); 
   
private:
   vector<Cell> s; 
}; 

#endif