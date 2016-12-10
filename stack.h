/* ***       Author:  Wei Kian Chen
     *  Last Update:  January 21, 2014
     *        Class:  CSI-281
     *     Filename:  stack.h
     *
     *  Description:
     *      This is the template stack definition.
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

template <typename T>
class Stack {
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
      Stack();
      ~Stack();

      int  getCount();

      void clear();
      void display();
      bool isEmpty();
      bool isExist(T searchKey);
      T    pop();
      void push(T data);
};


template <typename T>
Stack<T>::Stack()
{
   mHead  = NULL;
   mTail  = NULL;
   mCount = 0;
}


template <typename T>
Stack<T>::~Stack()
{
   while (!isEmpty())
      pop();
}


template <typename T>
int Stack<T>::getCount()
{
   return mCount;
}


template <typename T>
void Stack<T>::clear()
{
   while (!isEmpty())
      pop();
}


template <typename T>
void Stack<T>::display()
{
   Node<T> *tmp;

   if (isEmpty())
      cout << "Empty Stack\n";
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
bool Stack<T>::isEmpty()
{
   return mCount == 0;
}


template <typename T>
bool Stack<T>::isExist(T searchKey)
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


template <typename T>
T Stack<T>::pop()
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
void Stack<T>::push(T data)
{
   Node<T> *newNode;

   newNode = new Node<T>(data);
   if (newNode == NULL)
   {
      cerr << "System Error:  Insufficient Space to Generate Another Node!!\n";
      return;
   }

   newNode->mNext = mHead;
   mHead = newNode;

   if (mTail == NULL)
      mTail = newNode;

   mCount++;
}


#endif