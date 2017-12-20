/*
 * QUEUE
 *
 *  Created on: Jul 10, 2017
 *      Author: michaelhuang
 */

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

//----------Queue Template-------------------
template <class T>
class Queue {
public:
   Queue() : front(NULL), rear(NULL), numItems(0) {}
   ~Queue();
   bool enqueue(const T & item);
   bool dequeue(T & item);
   bool isEmpty() const;
   void print() const;

private:
   struct QueueNode {
      T value;
      QueueNode *next;
   };

   QueueNode *front;
   QueueNode *rear;
   int numItems;
};

template <class T>
Queue<T>::~Queue() {
   T tempItem;

   while(!isEmpty())
      dequeue(tempItem);
}

template <class T>
bool Queue<T>::enqueue(const T & item) {
   QueueNode *newNode = new QueueNode;
   newNode->value = item;
   newNode->next = NULL;

   if(isEmpty())
   {
      front = rear = newNode;
   }
   else
   {
      rear->next = newNode;
      rear = newNode;
   }
   numItems++;
   return true;
}

template <class T>
bool Queue<T>::dequeue(T & item) {
   if(isEmpty()) {
      return false;
   }
   else {
      QueueNode *nodePtr = front;
      front = front->next;
      item = nodePtr->value;

      delete nodePtr;
      numItems--;
      return true;
   }
}

template <class T>
bool Queue<T>::isEmpty() const {
   if (!numItems)
      return true;
   else
      return false;
}

template <class T>
void Queue<T>::print() const {
   QueueNode *nodePtr = front;

   while(nodePtr)
   {
      std::cout << nodePtr->value << " ";
      nodePtr = nodePtr->next;
   }
}
//---------End of Queue Template----------
#endif /* QUEUE_ */
