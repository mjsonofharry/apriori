#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <sstream>
#include "node.h"
#include "stack.h"

using namespace std;

class Trie
{
    private:
        int mMinimumSupport;
        Node *mRootNode;
    // end private

    public:
        Trie();
        ~Trie();

        void insert(stringstream &itemset);
        void prune(Node *node);
        void removeSubtree(Node *rootNode);

        void read(ifstream &dataset);
        void write(ostream &target, const int &limit);
        void write(ostream &target, const int &limit, Node *node, int depth);
    // end public
}; // end class


Trie::Trie()
{
    mRootNode = new Node();
    if (mRootNode == NULL)
    {
        perror(NULL);
        exit(1);
    }
}


Trie::~Trie()
{
    removeSubtree(mRootNode);
}


void Trie::insert(stringstream &itemset)
{
    Node *node, *newNode;
    string item;
    int index;

    node = mRootNode;

    while (itemset)
    {
        /* retrieve a single item */
        itemset >> item;
        cout << "\tInserting item: " << item << "\n";

        /* item NOT found */
        if ((index = node->getIndex(item)) == -1)
        {
            printf("\tItem does not already exist, creating new\n");
            /* allocate space in the heap */
            newNode = new Node(item);
            if (newNode == NULL)
            {
                perror(NULL);
                exit(1);
            } // end if

            node->add(newNode);
        } // end if

        /* retrieve an index */
        if ((index = node->getIndex(item)) == -1)
        {
            printf("\tFailed to insert or find node\n");
            perror(NULL);
            exit(1);
        }
        else
        {
            node = (*node)[index];
            node++;
        }
    } // end while
} // end function

void Trie::prune(Node *node)
{
    Node *tmp;
    int count, i;

    if(node->isFrequent(mMinimumSupport))
    {
        removeSubtree(node);
    }
    else
    {
        count = node->getCount();
        for (i = 0; i < count; i++)
        {
            tmp = (*node)[i];
            prune(tmp);
        } // end for
    } // end else
} // end function

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
        } // end if
        itemset.str(str);
        cout << "Inserting itemset: " << str << "\n";


        insert(itemset);
        itemset.str(string());
        itemset.clear();
    } // end while
} // end function

void Trie::removeSubtree(Node *node)
{
    Node *tmp;
    int count, i;

    count = node->getCount();

    for (i = 0; i < count; i++)
    {
        tmp = (*node)[i];
        removeSubtree(tmp);
    } // end for
    delete node;
    node = NULL;
} // end function


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
            if (node->getLabel() != "")
            {
                target << node->getLabel() << ", ";
            }

            count = node->getCount();
            for (i = 0; i < count; i++)
            {
                stack.push((*node)[i]);
            }
        }

        stack.clear();
    }
}

#endif
