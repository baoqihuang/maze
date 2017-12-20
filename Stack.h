/*
 * STACK
 *
 *  Created on: Jul 10, 2017
 *      Author: michaelhuang
 */

#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

//-----------------Stack Template------------------
template <class T>
class Stack {
public:
   Stack() : top(NULL) {}
   ~Stack();
   bool push(const T item);
   bool pop(T & item);
   bool getTop(T & item);
   bool isEmpty() const;
   void print() const;

private:
   struct StackNode {
      T value;
      StackNode *next;
   };

   StackNode *top;
};

template <class T>
Stack<T>::~Stack() {
   T tempItem;

  while(!isEmpty())
     pop(tempItem);
}

template <class T>
bool Stack<T>::push(const T item) {
   StackNode *newNode = new StackNode;
   newNode->value = item;

   if (!top)
   {
      top = newNode;
      newNode->next = NULL;
   }
   else
   {
      newNode->next = top;
      top = newNode;
   }
   return true;
}

template <class T>
bool Stack<T>::pop(T & item) {
   if (isEmpty()) {
      return false;
   }
   else {
      StackNode *nodePtr = top;
      top = top->next;
      item = nodePtr->value;

      delete nodePtr;
      return true;
   }
}

template <class T>
bool Stack<T>::getTop(T & item) {
   if(isEmpty()) {
      return false;
   }
   else {
      item = top->value;
      return true;
   }
}

template <class T>
bool Stack<T>::isEmpty() const {
   if (!top)
      return true;
   else
      return false;
}

template <class T>
void Stack<T>::print() const {
   StackNode *nodePtr = top;

   while(nodePtr)
   {
      std::cout << nodePtr->value << " ";
      nodePtr = nodePtr->next;
   }
}
//----------End of Stack Template------------


#endif /* STACK_ */
