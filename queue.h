/* ***       Author:  Wei Kian Chen
     *  Last Update:  January 21, 2014
     *        Class:  CSI-281
     *     Filename:  queue.h
     *
     *  Description:
     *      This is the template queue definition.
     *
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

template <typename T>
class Queue {
   private:
       template <typename R>
       struct Node
       {
          R       mData;
          Node<R> *mNext;

          /*      Pre:  None
           *     Post:  This object is initialized using default values
           *  Purpose:  To intialize date object
           *************************************************************************/
          Node()
          {
             mData = R();
             mNext = NULL;
          }


          /*      Pre:  None
           *     Post:  This object is initialized using specified data
           *  Purpose:  To intialize date object
           *************************************************************************/
          Node(R data)
          {
             mData = data;
             mNext = NULL;
          }
       };

      Node<T> *mHead, *mTail;
      int     mCount;

   public:
      Queue();
      ~Queue();

      int  getCount();

      void clear();
      T    dequeue();
      void display();
      void enqueue(T data);
      bool isEmpty();
      bool isExist(T searchKey);
};


template <typename T>
Queue<T>::Queue()
{
   mHead  = NULL;
   mTail  = NULL;
   mCount = 0;
}


template <typename T>
Queue<T>::~Queue()
{
   while (!isEmpty())
      dequeue();
}


template <typename T>
int Queue<T>::getCount()
{
   return mCount;
}


template <typename T>
void Queue<T>::clear()
{
   while (!isEmpty())
      dequeue();
}


template <typename T>
T Queue<T>::dequeue()
{
   T       data = T();
   Node<T> *tmp;

   if (!isEmpty())
   {
      tmp = mHead;

      mHead = tmp->mNext;

      tmp->mNext = NULL;
      data = tmp->mData;

      delete tmp;

      if (mHead == NULL)
         mTail = NULL;

      mCount--;
   }

   return data;
}


template <typename T>
void Queue<T>::display()
{
   Node<T> *tmp;

   if (isEmpty())
      cout << "Empty Queue\n";
   else
   {
      tmp = mHead;

      while (tmp != NULL)
      {
         cout << tmp->mData << " ";
         tmp = tmp->mNext;
      }
      cout << endl;
   }
}


template <typename T>
void Queue<T>::enqueue(T data)
{
   Node<T> *newNode;

   newNode = new Node<T>(data);
   if (newNode == NULL)
   {
      cerr << "System Error:  Insufficient Space to Generate Another Node!!\n";
      return;
   }

   mCount++;

   if (mHead == NULL)
   {
      mHead = newNode;
      mTail = newNode;
   }
   else
   {
      mTail->mNext = newNode;
      mTail = newNode;
   }
}


template <typename T>
bool Queue<T>::isEmpty()
{
   return mCount == 0;
}


template <typename T>
bool Queue<T>::isExist(T searchKey)
{
   bool    found = false;
   Node<T> *tmp;

   if (!isEmpty())
   {
      tmp = mHead;

      while (tmp != NULL)
      {
         if (tmp->mData == searchKey)
         {
            found = true;
            break;
         }

         tmp = tmp->mNext;
      }
   }

   return found;
}


#endif
