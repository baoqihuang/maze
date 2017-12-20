#ifndef DISJSETS_H
#define DISJSETS_H
#include "Cell.h"
#include "Queue.h"
#include "Stack.h"
#include <vector>

//---------DisjSets Class Prototype------------------
class DisjSets {
public:
   DisjSets() { }
   explicit DisjSets(int numElements);
   void resize(int numElements) { s.resize(numElements); }

   int find(int x);
   void unionSets(int root1, int root2);
   int getSize() const;
   void setWall(int wallVal, int index, int newVal);
   void destroyWall(int wallVal, int index);
   void print(int index);
   void getSides(int index, string &bottom, string &right);
   int getWallVal(int cell_ind, int wall_ind)  {
      return s[cell_ind].getWallVal(wall_ind);
      }
private:
   vector<Cell> s;
};
//---------End of DisjSets Class Prototype------------------



#endif
