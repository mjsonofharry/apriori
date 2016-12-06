#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <stringstream>
#include <linkedList.h>

using namespace std;

class Trie
{
    private:
        struct Node
        {
            LinkedList <Node *> mList;
            int mSupport;

            /* Purpose:  Default constructor for Node
             *     Pre:  None
             *    Post:  Node is initialized with default values
             ******************************************************************/
            Node()
            {

            } // end function

            /* Purpose:  Destructor for Node
             *     Pre:  None
             *    Post:  Node pointers are grounded
             ******************************************************************/
            ~Node()
            {
                mList.clear();
            } //end function
        } // end struct

        Node *mRootNode;
        int mCount;
    // end private

    public:
        Trie();
        ~Trie();

        /* Purpose:  Get the root Node of the Trie
         *     Pre:  None
         *    Post:  Returns root Node
         ******************************************************************/
        Node *getRootNode()
        {
            return mRootNode;
        } // end function

        /* Purpose:  Get the number of nodes in the Trie
         *     Pre:  None
         *    Post:  Returns number of nodes
         ******************************************************************/
        int getCount()
        {
            return mCount;
        } // end function

        void insert(Node *newNode);
        void insert(string data);
        void prune();

        void read(istream in)
        {
            string data;

            while (in)
            {
                getline(in, data);
                insert(data);
            }
        }

        void removeSubtree(Node *rootNode);
        void write(ostream out);
    // end public
} // end class

#endif
