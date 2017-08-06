#include "DisjSets.h"
#include <fstream> 
#include <sstream> 
#include <iostream> 
using namespace std; 

DisjSets::DisjSets(int numElements) : s(numElements) {
   for (int i = 0; i < s.size(); i++)
      s[i].setName(-1); 
}

void DisjSets::unionSets(int root1, int root2) {
   int temp1 = find(root1), temp2 = find(root2); 
   
   if(temp2 < temp1)
      s[temp1].setName(temp2); 
   else {
      if(s[root2].getName() == s[root1].getName())
         s[temp1].setName(s[temp1].getName() - 1); 
      s[temp2].setName(temp1); 
   }
}

// Return the name of the set that contains x
int DisjSets::find(int x) {
   if (s[x].getName() < 0)
      return x; 
   else {
      s[x].setName(find(s[x].getName())); 
      return s[x].getName(); 
   }
}

int DisjSets::getSize() const {
   return s.size();  // size of the vector 
}

void DisjSets::destroyWall(int wallVal, int index) {
   s[index].destroyWall(wallVal); 
}

void DisjSets::setWall(int wallVal, int index, int newVal) {
   s[index].setWall(wallVal, newVal); 
}

void DisjSets::print(int index) {
   s[index].print(); 
}

void DisjSets::getSides(int index, string &bottom, string &right) {
   s[index].getSides(bottom, right); 
}