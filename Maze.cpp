#include <iostream> 
#include <sstream> 
#include <algorithm> 
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

void Maze::createMaze() {
   setUpMaze(); // Set up the maze first 
   int r1, w1, r2, w2;  // room1 rank, wall 1 rank;   room2 rank, wall 2 rank;   
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
   
   /*int last = mySize - 1; 
   int pairNum1, pairNum2; // represent a random adjacent pair 
   int wallVal; 
   RandGen gen;                  // Random number generator 
   
   pairNum1 = gen.RandInt(0, last); 
   wallVal = gen.RandInt(1, 4); 
   pairNum2 = decideCellIndex(pairNum1, wallVal); */
   //myList.
   
   /*while (mySets.find(0) != mySets.find(last)) {      
      if (mySets.find(pairNum1) != mySets.find(pairNum2)) {
         mySets.destroyWall(wallVal, pairNum1); 
         mySets.unionSets(mySets.find(pairNum1), mySets.find(pairNum2)); 
      }
   }*/
   
   
	/*int temp, side, index;		//index and side to be randomly selected
	int size = mySize - 1;			//legal last index
	RandGen gen;				//random number generator

	list<int>::iterator i;		

	temp=	gen.RandInt(0, myList.size() - 1);	//randomly selecting index
	side=	gen.RandInt(1, 4);				//randomly selecting side

	int j = 0;
	for (i = myList.begin() ; j < myList.size(); i++, j++)
		if (j == temp) {
			index= *i;
			break;
		}

	if (side == BOTTOM)
		checkBottom(size, side, index);

	else if (side == RIGHT)
		checkRight(size, side, index);

	else if (side == TOP)
		checkTop(size, side, index);

	else if (side == LEFT)
		checkLeft(size, side, index);	

	if (mySets.find(index) == mySets.find(0))
		//if index is not in set zero, insert back into list of choices.
		myList.erase(i);		*/	

}


void Maze::genRandAdjRooms(int & r1,  int & w1,  int & r2, int & w2)
{

  // first generate room 1   
  RandGen gen;				//random number generator
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
   // for testing
   //cout << "row1, row2, col1, col2 = " <<  row1 << "," << row2 << "," << col1 << "," << col2 << endl;
  // cout << "r1, w1, r2, w2 = " << r1 <<"," <<w1<<"," << r2<<"," <<w2 << endl;
   
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
	cout <<endl;
}


/*
void Maze::checkBottom(int size, int side, int index){
	list<int>::iterator i;
	if((side == BOTTOM) && (index < size - myWidth)){
		//"size - myY" means that the index is at least as 
		//high as the next to last row.
		if((mySets.find(index) != mySets.find(index + myWidth)) &&
				mySets.destroyWall(side, index)){	
			//make sure that the proposed indeces are not already in the 
			//same set and that the wall was destroyed.
			
			mySets.unionSets(index,index+myWidth);	//place cells at indeces 
												//into same set
			if(mySets.find(index+myWidth)==0){
				i= find(myList.begin(),myList.end(),index+myWidth);
				if(i!=myList.end())
					myList.erase(i);
			}
		}
	}
}

void Maze::checkRight(int size, int side, int index){
	list<int>::iterator i;
	if((side==RIGHT)&&(index<size)){
		//make sure that index is not the last index
		if((mySets.find(index)!=mySets.find(index+1))&&
				mySets.destroyWall(side,index)){
			//make sure that the proposed indeces are not already in the 
			//same set and that the wall was destroyed.

			mySets.unionSets(index,index+1);	//place cells at indeces 
												//into same set
			if(mySets.find(index+1)==0){
				i= find(myList.begin(),myList.end(),index+1);
				if(i!=myList.end())
					myList.erase(i);

			}
		}
	}

}

void Maze::checkTop(int size,int side, int index){
	list<int>::iterator i;
	if((side== TOP) && (index >= myWidth)){
		//"index >= myY" means that the index is at least in the
		//second row.
		if((mySets.find(index)!=mySets.find(index-myWidth))&&
				mySets.destroyWall(BOTTOM,index-myWidth)){
			//make sure that the proposed indeces are not already in the 
			//same set and that the wall was destroyed.

			mySets.unionSets(index-myWidth,index);	//place cells at indeces 
												//into same set
			if(mySets.find(index-myWidth)==0){
				i= find(myList.begin(),myList.end(),index-myWidth);
				if(i!=myList.end())
					myList.erase(i);

			}

		}
	}
}

void Maze::checkLeft(int size, int side, int index){
	list<int>::iterator i;
	if((side== LEFT) && (index > 0)){
		//make sure that index is not the first one
		if((mySets.find(index)!=mySets.find(index-1))&&
				mySets.destroyWall(RIGHT,index-1)){
			//make sure that the proposed indeces are not already in the 
			//same set and that the wall was destroyed.

			mySets.unionSets(index-1,index);	//place cells at indeces 
												//into same set
			if(mySets.find(index-1)==0){
				i= find(myList.begin(),myList.end(),index-1);
				if(i!=myList.end())
					myList.erase(i);

			}
		}
	}	

}*/