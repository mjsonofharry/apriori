#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <string>

#include "linkedList.h"

using namespace std;

class Node
{
    private:
        struct Container
        {
            Node   *mChild;
            string mLabel;

            Container()
            {
                mChild   = NULL;
                mLabel   = "";
            } // end constructor

            Container(string label)
            {
                mChild   = NULL;
                mLabel   = label;
            } // end constructor

            ~Container()
            {
                mChild = NULL;
            } // end destructor

            void operator=(Container rhs)
            {
                mChild   = rhs.mChild;
                mLabel   = rhs.mLabel;
            } // end operator

            bool operator==(Container rhs)
            {
                return mLabel == rhs.mLabel;
            } // end operator

            bool operator==(string rhs)
            {
                return mLabel == rhs;
            } // end operator

            bool operator!=(Container rhs)
            {
                return mLabel != rhs.mLabel;
            } // end operator

            bool operator!=(string rhs)
            {
                return mLabel != rhs;
            } // end operator

            bool operator<(Container rhs)
            {
                return mLabel < rhs.mLabel;
            } // end operator

            bool operator<(string rhs)
            {
                return mLabel < rhs;
            } // end operator

            bool operator<=(Container rhs)
            {
                return mLabel <= rhs.mLabel;
            } // end operator

            bool operator<=(string rhs)
            {
                return mLabel <= rhs;
            } // end operator

            bool operator>(Container rhs)
            {
                return mLabel > rhs.mLabel;
            } // end operator

            bool operator>(string rhs)
            {
                return mLabel > rhs;
            } // end operator

            bool operator>=(Container rhs)
            {
                return mLabel >= rhs.mLabel;
            } // end operator

            bool operator>=(string rhs)
            {
                return mLabel >= rhs;
            } // end operator
        }; // end struct

        LinkedList<Container> mList;
        int  mSupport;
        bool mFlag;
    // end private

    public:
        Node();

        void   insert(string label);
        bool   isExist(string label);
        bool   isMarked();
        Node*  get(string label);
        string getLabel(int index);
        void   mark();
        int    size();
        int    support();

        Node* operator[](int i);
        void  operator++();
    // end public
}; // end class


Node::Node()
{
    mSupport = 0;
    mFlag    = false;
} // end function


void Node::insert(string label)
{
    Container newContainer;
    Node      *newNode;

    newNode = new Node();
    if (newNode == NULL)
    {
        exit(1);
    } // end if

    newContainer.mChild = newNode;
    newContainer.mLabel = label;

    mList.insert(newContainer);
} // end function


bool Node::isExist(string label)
{
    return mList.isExist(Container(label));
} // end function


bool Node::isMarked()
{
    return mFlag;
} // end function


Node* Node::get(string label)
{
    Node *tmp = NULL;

    for (int i = 0; i < size(); i++)
    {
        if (mList[i] == label)
        {
            tmp = mList[i].mChild;
            break;
        } // end if
    } // end for

    return tmp;
} // end function


string Node::getLabel(int index)
{
    return mList[index].mLabel;
} // end function


void Node::mark()
{
    mFlag = true;
} // end function


int Node::size()
{
    return mList.getCount();
} // end function


int Node::support()
{
    return mSupport;
} // end function


Node* Node::operator[](int index)
{
    return mList[index].mChild;
} // end operator


void Node::operator++()
{
    mSupport++;
} // end operator


#endif
