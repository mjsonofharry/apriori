#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <sstream>
#include "linkedList.h"
#include "stack.h"

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
                mSupport = 1;
            }

            /* Purpose:  Destructor for node
             *     Pre:  None
             *    Post:  Node pointers are grounded
             ******************************************************************/
            ~Node()
            {
                mList.clear();
            } //end function

            bool operator==(Node *rhs)
            {
                return mLabel == rhs->mLabel;
            }

            bool operator<(Node *rhs)
            {
                return mLabel < rhs->mLabel;
            }

            bool operator<=(Node *rhs)
            {
                return mLabel <= rhs->mLabel;
            }

            bool operator>(Node *rhs)
            {
                return mLabel > rhs->mLabel;
            }

            bool operator>=(Node *rhs)
            {
                return mLabel >= rhs->mLabel;
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
        void read(ifstream &dataset);
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

    if (mRootNode == NULL)
    {
        perror(NULL);
        exit(1);
    }
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
    Node *node, *newNode;
    string item;

    node = mRootNode;

    while (itemset)
    {
        /* increase support of current node */
        node->mSupport++;

        /* retrieve a single item */
        itemset >> item;

        cout << "\t\tInserting: " << item << "\n";

        /* allocate space in the heap */
        newNode = new Node(item);
        if (newNode == NULL)
        {
            perror(NULL);
            exit(1);
        }

        if (node->mList.isExist(newNode))
        {
            cout << "\t\tLinked found. Traveling to next trie node.\n";
            node = node->mList.search(newNode);

            /* new node is not needed this time */
            delete newNode;
            newNode = NULL;
        }
        else
        {
            cout << "\t\tLink not found. Creating link to new trie node.\n";
            node->mList.insert(newNode);
        }
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
void Trie::read(ifstream &dataset)
{
    stringstream itemset;
    string str;

    /* read each itemset */
    while (dataset)
    {
        getline(dataset, str);
        if (str == "")
        {
            break;
        }
        itemset.str(str);
        cout << "\tInserting: " << str << "\n";


        insert(itemset);
        itemset.str(string());
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
    Stack<Node*> stack;
    Node *node;
    int count, i;

    if (mRootNode != NULL)
    {
        stack.push(mRootNode);

        while (!stack.isEmpty())
        {
            node = stack.pop();
            target << node->mLabel << ", ";

            count = node->mList.getCount();
            for (i = 0; i < count; i++)
            {
                stack.push(node->mList.getData(i));
            }
        }

        stack.clear();
    }
}

#endif
