#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>

const int CHILDREN = 10;

class Trie
{
    private:
        struct Node
        {
            Node *mChild[CHILDREN];
            int mSupport;

            /* Purpose:  Default constructor for Node
             *     Pre:  None
             *    Post:  Node is initialized with default values
             ******************************************************************/
            Node()
            {
                for (int i = 0; i < CHILDREN; i++)
                {
                    mChild[i] = NULL;
                } // end for

                mSupport = 1;
            } // end function

            /* Purpose:  Destructor for Node
             *     Pre:  None
             *    Post:  Node pointers are grounded
             ******************************************************************/
            ~Node()
            {
                for (int i = 0; i < CHILDREN; i++)
                {
                    mChild[i] = NULL;
                } // end for
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

        int insert(Node *newNode);
        int insert(string data);
        int prune();
        int read(istream in);
        int removeSubtree(Node *rootNode);
        int write(ostream out);
    // end public
} // end class

#endif
