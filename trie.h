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
            string mLabel;
            int mSupport;

            /* Purpose:  Default constructor for node
             *     Pre:  None
             *    Post:  Node is initialized with default values
             ******************************************************************/
            Node()
            {
                mLabel   = "";
                mSupport = 0;
            } // end function

            /* Purpose:  Constructor for node
             *     Pre:  Label
             *    Post:  Node is initialized
             ******************************************************************/
            Node(string label)
            {
                mLabel   = label;
                mSupport = 1;
            }

            /* Purpose:  Destructor for node
             *     Pre:  None
             *    Post:  Node pointers are grounded
             ******************************************************************/
            ~Node()
            {
                mLabel   = "";
                mSupport = 0;
                mList.clear();
            } //end function
        } // end struct

        Node * mRootNode;
        int mCount;
    // end private

    public:
        Trie();
        ~Trie();
        Node * getRootNode();
        int getCount();
        void insert(stringstream & dataset);
        void prune();
        void read(istream & in);
        void removeSubtree(Node * rootNode);
        void write(ostream & out);
    // end public
} // end class

/* Purpose:  Constructor for trie
 *     Pre:  None
 *    Post:  Creates root node
 ******************************************************************/
Trie::Trie()
{
    mRootNode = new Node();
}

/* Purpose:  Destructor for trie
 *     Pre:  None
 *    Post:  Destroys subtree from root node
 ******************************************************************/
Trie::~Trie()
{
    removeSubtree(mRootNode);
}

/* Purpose:  Get the root node of the trie
 *     Pre:  None
 *    Post:  Returns root node
 ******************************************************************/
Node * Trie::getRootNode()
{
    return mRootNode;
} // end function

/* Purpose:  Get the number of nodes in the trie
 *     Pre:  None
 *    Post:  Returns number of nodes
 ******************************************************************/
int Trie::getCount()
{
    return mCount;
} // end function

void Trie::insert(stringstream & dataset)
{
    Node * node, * tmp;
    string item;

    node = mRootNode;

    while (dataset)
    {
        dataset >> item;

        /* CASE 1: item exists in node list */
        if ()
        {

        }
        /* CASE 2: item does not exist in node list */
        else
        {

        }
    }
}

void Trie::prune();

/* Purpose:  Read a dataset
 *     Pre:  Input stream
 *    Post:  Inserts each transaction into the trie
 ******************************************************************/
void Trie::read(istream in)
{
    stringstream dataset;
    string str;

    /* read each transaction */
    while (in)
    {
        /* get a single transaction (i.e. a single line ) */
        getline(in, str);
        dataset.str() = str;

        insert(dataset);
        dataset.str() = "";
    }
}

void Trie::removeSubtree(Node *rootNode);
void Trie::write(ostream out);

#endif
