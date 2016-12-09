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
            LinkedList<Data> mList;
            string           mLabel;
            int              mSupport;

            /* Purpose:  Default constructor for node
             *     Pre:  None
             *    Post:  Node is initialized with default values
             ******************************************************************/
            Node()
            {
                mLabel   = "";
                mSupport = 0;
            } // end function

            /* Purpose:  Destructor for node
             *     Pre:  None
             *    Post:  Node pointers are grounded
             ******************************************************************/
            ~Node()
            {
                mList.clear();
            } //end function

            bool operator==(const Node &rhs)
            {
                return mLabel == rhs.mLabel;
            }

            bool operator<(const Node &rhs)
            {
                return mLabel < rhs.mLabel;
            }

            bool operator<=(const Node &rhs)
            {
                return mLabel <= rhs.mLabel;
            }

            bool operator>(const Node &rhs)
            {
                return mLabel > rhs.mLabel;
            }

            bool operator>=(const Node &rhs)
            {
                return mLabel >= rhs.mLabel;
            }
        } // end struct

        struct Data
        {
            Node   *mNode;
            string mItem;

            Data()
            {
                mNode = NULL;
                mItem = "";
            }

            Data(Node *node, string item)
            {
                mNode = node;
                mItem = item;
            }

            ~Data()
            {
                mNode = NULL;
                mItem = "";
            }

            Data& operator=(const Data &rhs)
            {
                mNode = rhs.mNode;
                mItem = rhs.mItem;
            }

            bool operator==(const Data &rhs)
            {
                return mItem == rhs.mItem;
            }

            bool operator<(const Data &rhs)
            {
                return mItem < rhs.mItem;
            }

            bool operator<=(const Data &rhs)
            {
                return mItem <= rhs.mItem;
            }

            bool operator>(const Data &rhs)
            {
                return mItem > rhs.mItem;
            }

            bool operator>=(const Data &rhs)
            {
                return mItem >= rhs.mItem;
            }
        } // end struct

        Node *mRootNode;
        int  mCount;
    // end private

    public:
        Trie();
        ~Trie();

        Node* getRootNode();
        int   getCount();

        void insert(stringstream &itemset);
        void prune();
        void read(istream &dataset);
        void removeSubtree(Node *rootNode);
        void write(ostream &target);
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
Node* Trie::getRootNode()
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

void Trie::insert(stringstream &itemset)
{
    Node * node;
    Data * tmp;
    string item;
    int index;

    currentNode = mRootNode;

    while (itemset)
    {
        itemset >> item;
        tmp = tmp(NULL, item);

        /* CASE 1: item exists in child list */
        if ((index = isExist(tmp)) != -1)
        {

        }
        /* CASE 2: item does not exist in child list */
        else
        {

        }
    }
}

void Trie::prune();

/* Purpose:  Read a dataset
 *     Pre:  Input stream
 *    Post:  Inserts each itemset from the dataset into the trie
 ******************************************************************/
void Trie::read(istream &dataset)
{
    stringstream itemset;
    string str;

    /* read each itemset */
    while (dataset)
    {
        getline(dataset, str);
        itemset.str() = str;

        insert(itemset);
        itemset.str() = "";
    }
}

void Trie::removeSubtree(Node *rootNode);
void Trie::write(ostream target);

#endif
