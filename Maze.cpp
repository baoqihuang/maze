#include <iostream> 
#include <sstream> 
#include <algorithm> 
#include <vector>
#include "Queue.h"
#include "Stack.h"
#include "Maze.h"
#include "RandGen.h"

using namespace std; 

Maze::Maze(int sideLength) : myHeight (sideLength), myWidth(sideLength),
                                                mySize(sideLength * sideLength), mySets(sideLength * sideLength) {
   for (int i = 0; i < mySize; i++)
      myList.push_back(i);
}

void Maze::setUpMaze() {
   int last = mySize - 1;

   // Destroying the Top wall of the first cell
   // and the Bottom wall of the last indeces
   mySets.destroyWall(TOP, 0);
   mySets.destroyWall(BOTTOM, last);

   // Set up the top wall of the first row
   for (int i = 1; i < myWidth; i++)
      mySets.setWall(TOP, i, -1);

    // Set up the left wall of the first column
   for (int k = 0; k < last; k += myWidth)
      mySets.setWall(LEFT, k, -1);

   // Set up the right wall of the last column
   for (int n = myWidth - 1; n <= last; n += myWidth)
      mySets.setWall(RIGHT, n, -1);

   // Set up the bottom wall of the last row
   for (int j = last, p = myWidth; p > 0; p--, j--)
      mySets.setWall(BOTTOM, j, -1);
}

void Maze::createMaze(int randSeed) {
   setUpMaze(); // Set up the maze first
   int r1, w1, r2, w2;  // room1 rank, wall 1 rank;   room2 rank, wall 2 rank;
   myRandGen.SetSeed(randSeed);
    while (mySets.find(0) != mySets.find(mySize-1)) {  // maze not go through yet
      genRandAdjRooms(r1,w1,r2,w2);

      int root1 = mySets.find(r1);
      int root2 = mySets.find(r2);

      if (root1 != root2)  {// room 1 and room2 not connected yet
          mySets.destroyWall(w1,r1);
          mySets.destroyWall(w2,r2);
          mySets.unionSets(root1, root2);
      }
  }
}

void Maze::saveMazeToFile(std::string const & filename)
{
   ofstream outFile(filename.c_str(), ios::trunc|ios::out);
   if (!outFile.is_open())
      throw runtime_error("Open maze input file failed.\n");
}

 void Maze::createMaze(std::string const & fileName)
 {
    //vector<vector<int> >  mazeCellsInfo;

      // ifstream inFile(fileName, ios::in);
    ifstream inFile(fileName.c_str());

   // Check if the file has been opened successfully
   if (!inFile.is_open())
      throw runtime_error("Open maze input file failed.\n");

   // read the first line of the file,
   int sideLength;
   inFile >> sideLength;
   int lineNum = sideLength * sideLength;

   // init  cell array
   myHeight  = sideLength;
   myWidth = sideLength;
   mySize = sideLength * sideLength;
   mySets.resize(mySize);
   myList.clear();
   for (int i = 0; i < mySize; i++)
      myList.push_back(i);

   // determine wall value
   for (int i = 0; i < lineNum; ++i) {
       int wallVal;
       for (int j = 0; j < 4; ++j) {
          inFile >> wallVal;
          mySets.setWall(j,i,wallVal);
       }

   }
 }

void Maze::genRandAdjRooms(int & r1,  int & w1,  int & r2, int & w2)
{

  // first generate room 1
  RandGen  & gen = myRandGen;				//random number generator
	int rRank1 =	gen.RandInt(0, mySize- 1);	//randomly selecting index
	int row1 = rRank1/myWidth;
   int col1 = rRank1- row1*myWidth;
   int row2 = row1;
   int col2 = col1;

   //  if room 1 is not adjacnt to any outer wals
   if (col1>0 && col1<myWidth-1 && row1>0 && row1<myHeight-1) {
      if (gen.RandBool())
         row2 +=  gen.RandSign();
       else
          col2 +=  gen.RandSign();

   } else if (row1 ==0 && col1 ==0) {   // top left corner
       if (gen.RandBool())
            row2 += 1;
      else
            col2 +=  1;
   } else if (row1 == 0 && col1 == myWidth-1)  {// top right corner
        if(gen.RandBool())
           row2 += 1;
        else
           col2 -= 1;
    } else if (row1 == myHeight-1 && col1==0) { // bot left corner
        if(gen.RandBool())
           row2 -= 1;
        else
           col2 += 1;
   } else if (row1 == myHeight-1 && col1==myWidth-1) { // bot right corner
         if(gen.RandBool())
           row2 -= 1;
        else
           col2 -= 1;
   } else if (row1 == 0)  {// top bound
        if(gen.RandBool())
           row2 += 1;
         else
            col2 +=  gen.RandSign();
   } else if (row1 == myHeight-1) {  // bot bound
         if(gen.RandBool())
           row2 -= 1;
         else
            col2 +=  gen.RandSign();
   }  else if (col1 == 0) {  // left bound
       if(gen.RandBool())
           row2 += gen.RandSign();
        else
           col2 +=  1;
   } else {   // right bound
         if(gen.RandBool())
           row2 += gen.RandSign();
        else
           col2 -=  1;
   }

   r1 = row1*myWidth + col1;
   r2 = row2*myWidth + col2;

   if (row1 == row2 ) {
      w1 =  (col1 > col2) ?  3 : 2;
      w2 =  (col1 > col2) ?  2 : 3;
   } else {
      w1 =  (row1 > row2) ? 0: 1;
      w2 =  (row1 > row2) ? 1: 0;
   }
}


int Maze::decideCellIndex(int cellIndex, int wallVal) {
   if (wallVal == TOP)
      return cellIndex - myWidth;
   else if (wallVal == BOTTOM)
      return cellIndex + myWidth;
   else if (wallVal == LEFT)
      return cellIndex - 1;
   else
      return cellIndex + 1;
}

// Returns true if the first and last indices are within the same
// set. i.e. there is a unique path from the entrance and exit.
bool Maze::checkIfMaze() {
	return myList.empty();
}

void Maze::print(){
	cout << "  ";	//there is no top side for index 0

	for(int j = 1; j < myWidth; j++)	//printing out top side
		cout << " " << "_";

	for(int i = 0; i < mySize; i += myWidth){
			cout <<endl<<"|";		//printing out far left

		for(int m = 0,k = i; m < myWidth; k++, m++)
			mySets.print(k);
	}
	cout <<endl << endl;
}

void Maze::findPathBFS(vector<int> & pathInds)
{
   Queue<int> tmpQ;
   int N = mySize;
   tmpQ.enqueue(0);

   std::vector<int> roomsVisited;
   roomsVisited.push_back(0);

   int i;
   while (!tmpQ.isEmpty()) {
      tmpQ.dequeue(i);
      if (i == N-1) break;

      if (mySets.getWallVal(i, 0) == 0  && i != 0) {  // top,  and  we need to exclude cell 0
            int j = i - myWidth;
            if ( std::find(roomsVisited.begin(), roomsVisited.end(), j) == roomsVisited.end()) {
               tmpQ.enqueue(j);
               roomsVisited.push_back(j);
               if (j == N-1) break;
            }
      }

       if (mySets.getWallVal(i, 1) == 0 ) {  // bot
               int j = i + myWidth;
               if ( std::find(roomsVisited.begin(), roomsVisited.end(), j) == roomsVisited.end()) {
                  tmpQ.enqueue(j);
                  roomsVisited.push_back(j);
                  if (j == N-1) break;

               }
          }

        if (mySets.getWallVal(i, 2) == 0) {  // right
               int j   = i + 1;
               if (std::find(roomsVisited.begin(), roomsVisited.end(), j) == roomsVisited.end() ) {
                  tmpQ.enqueue(j);
                  roomsVisited.push_back(j);
                  if (j == N-1) break;
               }
        }

        if (mySets.getWallVal(i, 3) ==0 ) {  // left
            int j   = i - 1;
               if ( std::find(roomsVisited.begin(), roomsVisited.end(), j) == roomsVisited.end() ) {
                  tmpQ.enqueue(j);
                  roomsVisited.push_back(j);
                  if (j == N-1) break;
               }
          }
   }

   // now we can print the path
   std::cout << "Rooms visited by BFS :" ;
   for (int i=0; i<(int)roomsVisited.size(); ++i)
      cout << roomsVisited[i] << "  " ;
   std::cout << endl;

   // find the path by back trace
   std::vector<int> pathFoundReverse;
   int currInd = roomsVisited.size()-1; // start from the last visited room, which is the exit


   do {
      pathFoundReverse.push_back(roomsVisited[currInd]);
      // find the first neighbor of currInd with backward tracing
      int tmpInd = currInd - 1;
      while ( ! isConnectedNeighbor(roomsVisited[currInd], roomsVisited[tmpInd]) )  tmpInd -- ;

      currInd  = tmpInd;

   } while (currInd >= 0);

   // print the path found
   pathInds.clear();
   std::cout << "This is the Path (in reverse): ";
   for (int i  = 0; i < (int)pathFoundReverse.size(); ++i) {
      cout << pathFoundReverse[i] << ' ';
      pathInds.push_back(i);
   }
   cout << endl;

   cout << "This is the path.\n";
   for (int k = 0; k < mySets.getSize(); ++k) {
      if (std::find(pathFoundReverse.begin(), pathFoundReverse.end(), k) == pathFoundReverse.end()) {
         cout << " ";
         if (k % myWidth == myWidth - 1)
            cout << endl;
      }
      else  {
         cout << "X";
         if (k % myWidth == myWidth - 1)
            cout << endl;
      }
   }
   cout << endl;
}

void Maze::findPathDFS(vector<int> & pathInds)
{
   Stack<int> tmpS;
   int N = mySize;
   tmpS.push(0);

   std::vector<int> roomsVisited;

   int i;
   while (!tmpS.isEmpty()) {
      tmpS.pop(i);
      roomsVisited.push_back(i);
      if (i == N-1) break;

      if (mySets.getWallVal(i, 0) == 0  && i != 0) {  // top,  and  we need to exclude cell 0
         int j = i - myWidth;
         if ( std::find(roomsVisited.begin(), roomsVisited.end(), j) == roomsVisited.end())
               tmpS.push(j);
          }

         if (mySets.getWallVal(i, 1) == 0 ) {  // bottom
             int j = i + myWidth;
             if ( std::find(roomsVisited.begin(), roomsVisited.end(), j) == roomsVisited.end())
                tmpS.push(j);
         }

          if (mySets.getWallVal(i, 2) == 0) {  // right
               int j   = i + 1;
               if (std::find(roomsVisited.begin(), roomsVisited.end(), j) == roomsVisited.end() )
                  tmpS.push(j);
         }

         if (mySets.getWallVal(i, 3) ==0 ) {  // left
            int j   = i - 1;
            if ( std::find(roomsVisited.begin(), roomsVisited.end(), j) == roomsVisited.end() )
               tmpS.push(j);
          }
   }

   // now we can print the path
   std::cout << "Rooms visited by DFS :" ;
   for (int i=0; i<(int)roomsVisited.size(); ++i)
      cout << roomsVisited[i] << "  " ;
   std::cout << endl;

   // find the path by back trace
   std::vector<int> pathFoundReverse;
   int currInd = roomsVisited.size()-1; // start from the last visited room, which is the exit

   do {
      pathFoundReverse.push_back(roomsVisited[currInd]);
      // find the first neighbor of currInd with backward tracing
      int tmpInd = currInd - 1;
      while ( ! isConnectedNeighbor(roomsVisited[currInd], roomsVisited[tmpInd]) )  tmpInd -- ;

      currInd  = tmpInd;

   } while (currInd >= 0);

   // print the path found
   pathInds.clear();
   std::cout << "This is the Path (in reverse): ";
   for (int i  = 0; i < (int)pathFoundReverse.size(); ++i) {
      cout << pathFoundReverse[i] << ' ';
      pathInds.push_back(i);
   }
   cout << endl;

   cout << "This is the path.\n";
   for (int k = 0; k < mySets.getSize(); ++k) {
      if (std::find(pathFoundReverse.begin(), pathFoundReverse.end(), k) == pathFoundReverse.end()) {
         cout << " ";
         if (k % myWidth == myWidth - 1)
            cout << endl;
      }
      else  {
         cout << "X";
         if (k % myWidth == myWidth - 1)
            cout << endl;
      }
   }
   cout << endl;
}

bool Maze::isConnectedNeighbor(int room_i, int room_j)
{
   for (int iw=0; iw<4; ++iw) {
     if (mySets.getWallVal(room_i , iw) == 0)  { // open wall
          int room_i_neighbor;
          if (iw == 0)
             room_i_neighbor = room_i - myWidth;
         else if (iw == 1)
             room_i_neighbor = room_i + myWidth;
         else if (iw ==  2)
             room_i_neighbor = room_i + 1;
          else
            room_i_neighbor = room_i - 1;

          if (room_i_neighbor == room_j)
            return true;
     }

   }
   return false;
}
//-----End of Maze Class Definitions-----------------------





