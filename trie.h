#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <sstream>
#include "linkedList.h"

using namespace std;

class Trie
{
    private:
        struct Node
        {
            LinkedList<Node*> mList;
            string            mLabel;
            int               mSupport;

            /* Purpose:  Default constructor for node
             *     Pre:  None
             *    Post:  Node is initialized with default values
             ******************************************************************/
            Node()
            {
                mLabel   = "";
                mSupport = 0;
            } // end function

            Node(string label)
            {
                mLabel   = label;
                mSupport = 0;
            }

            /* Purpose:  Destructor for node
             *     Pre:  None
             *    Post:  Node pointers are grounded
             ******************************************************************/
            ~Node()
            {
                mList.clear();
            } //end function

            bool operator==(Node &rhs)
            {
                return mLabel == rhs.mLabel;
            }

            bool operator<(Node &rhs)
            {
                return mLabel < rhs.mLabel;
            }

            bool operator<=(Node &rhs)
            {
                return mLabel <= rhs.mLabel;
            }

            bool operator>(Node &rhs)
            {
                return mLabel > rhs.mLabel;
            }

            bool operator>=(Node &rhs)
            {
                return mLabel >= rhs.mLabel;
            }
        }; // end struct

        int  mCount;
        int  mMinimumSupport;
        Node *mRootNode;
    // end private

    public:
        Trie();
        ~Trie();

        int  getCount();
        void insert(stringstream &itemset);
        void prune(Node *node);
        void read(istream &dataset);
        void removeSubtree(Node *rootNode);
        void write(ostream &target, const int &limit);
        void write(ostream &target, const int &limit, Node *node, int depth);
    // end public
}; // end class

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
    Node *tmp, *newNode;
    string item;

    tmp = mRootNode;

    while (itemset)
    {
        itemset >> item;

        newNode = new Node(item);

        if (!tmp->mList.insert(newNode))
        {
            delete newNode;
        }

        tmp = tmp->mList.search(tmp);
        tmp->mSupport++;
    }
}

void Trie::prune(Node *node)
{
    Node *tmp;
    int count;

    if(node->mSupport < mMinimumSupport)
    {
        removeSubtree(node);
    }
    else
    {
        count = node->mList.getCount();
        for (int i = 0; i < count; i++)
        {
            tmp = node->mList.getData(i);
            prune(tmp);
        }
    }
}

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

void Trie::removeSubtree(Node *node)
{
    Node *tmp;
    int count;

    count = node->mList.getCount();

    for (int i = 0; i < count; i++)
    {
        tmp = node->mList.getData(i);
        removeSubtree(tmp);
    }
    delete node;
    node = NULL;
}


void Trie::write(ostream &target, const int &limit)
{
    write(target, limit, mRootNode, 0);
}


void Trie::write(ostream &target, const int &limit, Node *node, int depth)
{
    Node *tmp;
    int count;

    depth++;

    if (depth > limit)
    {
        return;
    }

    count = node->mList.getCount();
    for (int i = 0; i < count; i++)
    {
        target << node->mLabel << ", ";
        tmp = node->mList.getData(i);
        write(target, limit, tmp, depth);
    }
    printf("\n");
}

#endif
