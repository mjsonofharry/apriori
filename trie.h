/*       Authors: Matthew James Harrison & Roemello McCoy
 *         Class: CSI-281-01 Data Structures & Algorithms
 *    Assignment: Final Project: Apriori
 * Date Assigned: November 21,  2016
 *      Due Date: December 10, 2016
 *
 * Description:
 *   Apriori implemenation in C++. Reads a dataset and computes k-itemsets.
 *
 * Certication of Authenticity:
 *   I certify that this is entirely my own work, except where I have given
 *   fully-documented references to the work of others. I understand the
 *   definition and consequences of plagiarism and acknowledge that the assessor
 *   of this assignment may, for the purpose of assessing this assignment:
 *     -  Reproduce this assignment and provide a copy to another member of
 *        academic staff; and/or
 *     -  Communicate a copy of this assignment to a plagiarism checking service
 *        (which may then retain a copy
 *        of this assignment on its database for the purpose of future
 *        plagiarism checking)
 ******************************************************************************/

#ifndef TRIE_H
#define TRIE_H

#include <climits>
#include <fstream>
#include <sstream>
#include <string>

#include "queue.h"

const string ROOT_LABEL = "TRIE_ROOT_IGNORE";

using namespace std;

class Trie
{
    private:
        struct Node
        {
            Queue<Node*> mQueue;
            string       mItem;
            int          mSupport;

            /* Purpose: Constructor for node
             *     Pre: None
             *    Post: Node initialized with default values
             ******************************************************************/
            Node()
            {
                mItem    = "";
                mSupport = 0;
            } // end constructor

            /* Purpose: Constructor for node
             *     Pre: Item
             *    Post: Node initialized with default values and item
             ******************************************************************/
            Node(string item)
            {
                mItem    = item;
                mSupport = 1;
            } // end constructor

            /* Purpose: Get the number of nodes in the queue
             *     Pre: None
             *    Post: Returns the number of nodes
             ******************************************************************/
            int size()
            {
                return mQueue.getCount();
            } // end function

            Node* operator[](int index)
            {
                return mQueue[index];
            } // end operator
        }; // end struct

        Node *mRootNode;
    // end private

    public:
        Trie();
        ~Trie();

        void insert(stringstream &itemset);
        void prune(const int &support);
        bool prune(Node *node, const int &support);
        void removeSubtree(Node *node);

        void read(ifstream &dataset);
        void write(ofstream &target, const int &klimit);
        void rwrite(ofstream &target, const int &klimit, Node *tmp, string path, int depth);
    // end public
}; // end class


/* Purpose: Constructor for trie
 *     Pre: None
 *    Post: Trie initialized with default values
 ******************************************************************************/
Trie::Trie()
{
    printf("Creating empty tree...\n");
    mRootNode = NULL;
} // end constructor


/* Purpose: Destructor for trie
 *     Pre: None
 *    Post: All subtrees destroyed
 ******************************************************************************/
Trie::~Trie()
{
    printf("Destroying tree...\n");
    removeSubtree(mRootNode);
} // end destructor


/* Purpose: Insert itemset into trie
 *     Pre: Stringstream containing itemset
 *    Post: Each item from itemset inserted into trie
 ******************************************************************************/
void Trie::insert(stringstream &itemset)
{
    Node *tmp, *child, *newNode;
    string item;
    bool match;

    printf("Inserting itemset\n");

    /* create root node if necessary */
    if (mRootNode == NULL)
    {
        printf("WARNING: No root node found, attempting to create new\n");
        tmp = new Node();
        if (tmp == NULL)
        {
            fprintf(stderr, "CRITICAL: Failed to allocate heap for new node\n");
            exit(1);
        } // end if
        mRootNode = tmp;
        tmp = NULL;
    } // end if

    /* begin traversal */
    tmp = mRootNode;

    /* for each item in itemset */
    while (itemset)
    {
        itemset >> item;
        printf("Read item: %s\n", item.c_str());

        /* queue is empty */
        if (tmp->mQueue.isEmpty())
        {
            /* attempt to create new node */
            newNode = new Node(item);
            if (newNode == NULL)
            {
                fprintf(stderr, "CRITICAL: Failed to allocate heap for new node\n");
                exit(1);
            } // end if

            /* enqueue new node */
            tmp->mQueue.enqueue(newNode);
            tmp     = newNode;
            newNode = NULL;
        }
        else
        {
            /* search queue for a match */
            match = false;
            for (int i = 0; i < tmp->size(); i++)
            {
                if ((child = (*tmp)[i])->mItem == item)
                {
                    /* match found */
                    match = true;
                    tmp   = child;
                    tmp->mSupport++;

                    child = NULL;
                } // end if
            } // end for

            /* no match found */
            if (!match)
            {
                /* attempt to create new node */
                newNode = new Node(item);
                if (newNode == NULL)
                {
                    fprintf(stderr, "CRITICAL: Failed to allocate heap for new node\n");
                    exit(1);
                } // end if

                /* enqueue new node */
                tmp->mQueue.enqueue(newNode);
                tmp     = newNode;
                newNode = NULL;
            }
        } // end if
    } // end while

    printf("Finished inserting itemset\n");
} // end function


/* Purpose: Wrapper function to prune entire trie
 *     Pre: Minimum support value
 *    Post: Prunes from root node
 ******************************************************************************/
void Trie::prune(const int &support)
{
    prune(mRootNode, support);
} // end function


/* Purpose: Remove subtrees that fail to meet minimum support threshold
 *     Pre: Subtree parent, minimum support value
 *    Post: Only frequent itemsets remain in trie
 ******************************************************************************/
bool Trie::prune(Node *tmp, const int &support)
{
    bool removed = false;

    if (tmp->mSupport < support)
    {
        removeSubtree(tmp);
        removed = true;
    }
    else
    {
        for (int i = 0; i < tmp->size(); i++)
        {
            if (prune((*tmp)[i], support))
            {
                tmp->mQueue.remove(i);
            } // end if
        } // end for
    } // end if

    return removed;
} // end function


/* Purpose: Remove subtree
 *     Pre: Subtree parent
 *    Post: All nodes in subtree destroyed
 ******************************************************************************/
void Trie::removeSubtree(Node *tmp)
{
    if (tmp == NULL)
    {
        return;
    } // end if

    for (int i = 0; i < tmp->size(); i++)
    {
        removeSubtree((*tmp)[i]);
    } // end for

    tmp->mQueue.clear();

    delete tmp;
    tmp = NULL;
} // end function


/* Purpose: Read dataset
 *     Pre: Input file stream
 *    Post: Each itemset read from dataset and inserted
 ******************************************************************************/
void Trie::read(ifstream &dataset)
{
    stringstream itemset;
    string       str;

    while (dataset)
    {
        getline(dataset, str);

        if (str != "")
        {
            printf("Retrieving itemset: %s\n", str.c_str());

            itemset.str(str);
            insert(itemset);

            itemset.str(string());
            itemset.clear();
        } // end if
    } // end while
    printf("Finished retrieving dataset\n");
} // end function


/* Purpose: Wrapper function to write k-itemsets to output file
 *     Pre: Output file stream, k-limit
 *    Post: k-itemsets written to output file
 ******************************************************************************/
void Trie::write(ofstream &target, const int &klimit)
{
    target << klimit << "-itemset\n";
    rwrite(target, klimit, mRootNode, "", 0);
} // end function


/* Purpose: Recurse through trie to retrieve k-itemsets
 *     Pre: Output file stream, k-limit, node, path, depth
 *    Post: All k-itemsets written to file
 ******************************************************************************/
void Trie::rwrite(ofstream &target, const int &klimit, Node *tmp, string path, int depth)
{
    if (depth == klimit)
    {
        target << path << " (" << tmp->mSupport << ")\n";
    }
    else
    {
        /* recurse through children */
        for (int i = 0; i < tmp->size(); i++)
        {
            path = path + " " + (*tmp)[i]->mItem;
            rwrite(target, klimit, (*tmp)[i], path, depth + 1);
        } // end for
    } // end if
} // end function

#endif
