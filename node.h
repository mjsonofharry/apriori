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
            Node  *mChild;
            string mItem;
            int    mSupport;

            Container();
            ~Container();

            void  operator=(Container rhs);
            bool  operator==(Container rhs);
            bool  operator==(string rhs);
            bool  operator<(Container rhs);
            bool  operator<(string rhs);
            bool  operator<=(Container rhs);
            bool  operator<=(string rhs);
            bool  operator>(Container rhs);
            bool  operator>(string rhs);
            bool  operator>=(Container rhs);
            bool  operator>=(string rhs);
            Node* operator[](int i);
        }; // end struct

        LinkedList<Container> mList;
    // end private

    public:
        void  insert(Node *newNode);
        bool  isExist(string item);
        Node* retrieve(string item);
        int   subtrees();

        void  operator++();
    // end public
}; // end class

Container::Container()
{
    mChild   = NULL;
    mItem    = "";
    mSupport = 0;
} // end constructor

Container::~Container()
{
    mChild = NULL;
} // end destructor

void Container::operator=(Container rhs)
{
    mChild   = rhs.mChild;
    mItem    = rhs.mItem;
    mSupport = rhs.mSupport;
} // end operator

bool Container::operator==(Container rhs)
{
    return mItem == rhs.mItem;
} // end operator

bool Container::operator==(string rhs)
{
    return mItem == rhs;
} // end operator

bool Container::operator<(Container rhs)
{
    return mItem < rhs.mItem;
} // end operator

bool Container::operator<(string rhs)
{
    return mItem < rhs;
} // end operator

bool Container::operator<=(Container rhs)
{
    return mItem <= rhs.mItem;
} // end operator

bool Container::operator<=(string rhs)
{
    return mItem <= rhs;
} // end operator

bool Container::operator>(Container rhs)
{
    return mItem > rhs.mItem;
} // end operator

bool Container::operator>(string rhs)
{
    return mItem > rhs;
} // end operator

bool Container::operator>=(Container rhs)
{
    return mItem >= rhs.mItem;
} // end operator

bool Container::operator>=(string rhs)
{
    return mItem >= rhs;
} // end operator

Node* Container::operator[](int i)
{
    return mList[i];
} // end operator

#endif
