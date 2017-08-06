#ifndef RANDGEN_H
#define RANDGEN_H

class RandGen {
public: 
   RandGen();                                               // Set seed for all instances
   int RandInt(int max = INT_MAX);              
   int RandInt(int low, int max); 
   bool RandBool(); // gen true or false
   int RandSign();   // gen -1 or +1
   double RandReal(); 
   double RandReal(double low, double max); 
   
   static void SetSeed(int seed);
 
private: 
   static int ourInitialized; 
}; 

#endif 