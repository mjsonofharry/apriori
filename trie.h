/*       Authors: Matthew James Harrison & Roemello McCoy
 *         Class: CSI-281-01 Data Structures & Algorithms
 *    Assignment: Final Project: Apriori
 * Date Assigned: November 21,  2016
 *      Due Date: December 10, 2016
 *
 * Description:
 *   Apriori
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

#include "node.h"

const string ROOT_LABEL = "TRIE_ROOT_IGNORE";

using namespace std;

class Trie
{
    private:
        Node *mRootNode;
    // end private

    public:
        Trie();
        ~Trie();

        void insert(stringstream &itemset);
        void prune(const int &support);
        void prune(Node *node, const int &support);
        void removeSubtree(Node *node);

        void read(ifstream &dataset);
        void write(ofstream &target, const int &klimit);
        void wdfs(ofstream &target, const int &klimit, Node *node, int depth, string path);
    // end public
}; // end class


/* Purpose: Constructor for trie
 *     Pre: None
 *    Post: Trie initialized with default values
 ******************************************************************************/
Trie::Trie()
{
    mRootNode = new Node();
    if (mRootNode == NULL)
    {
        fprintf(stderr, "CRITICAL: Failed to allocate space for new Node!\n");
        exit(1);
    }
} // end constructor


/* Purpose: Destructor for trie
 *     Pre: None
 *    Post: All subtrees destroyed
 ******************************************************************************/
Trie::~Trie()
{
    removeSubtree(mRootNode);
} // end destructor


/* Purpose: Insert itemset into trie
 *     Pre: Stringstream containing itemset
 *    Post: Each item from itemset inserted into trie
 ******************************************************************************/
void Trie::insert(stringstream &itemset)
{
    Node *node;
    string item;

    /* begin traversal */
    node = mRootNode;

    /* for each item in the itemset */
    while (itemset)
    {
        if (node == NULL)
        {
            fprintf(stderr, "CRITICAL: Inserting into NULL Node!\n");
            exit(1);
        }

        node++;
        itemset >> item;

        /* create child node if it does not exist */
        if (!node->isExist(item))
        {
            node->insert(item);
        } // end if

        /* go to child node */
        node = node->get(item);
    } // end while
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
void Trie::prune(Node *node, const int &support)
{
    if (node->support() < support)
    {
        removeSubtree(node);
    }
    else
    {
        for (int i = 0; i < node->size(); i++)
        {
            prune((*node)[i], support);
        } // end for
    } // end if
} // end function


/* Purpose: Remove subtree
 *     Pre: Subtree parent
 *    Post: All nodes in subtree destroyed
 ******************************************************************************/
void Trie::removeSubtree(Node *node)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->size(); i++)
        {
            removeSubtree((*node)[i]);
        } // end for

        delete node;
        node = NULL;
    } // end if
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
            printf("Reading itemset: %s\n", str.c_str());

            itemset.str(str);
            insert(itemset);

            itemset.str(string());
            itemset.clear();
        } // end if
    } // end while
} // end function


/* Purpose: Wrapper function to write k-itemsets to output file
 *     Pre: Output file stream, k-limit
 *    Post: k-itemsets written to output file
 ******************************************************************************/
void Trie::write(ofstream &target, const int &klimit)
{
    target << klimit << "-itemset\n";
    wdfs(target, klimit, mRootNode, 0, "");
    printf("\n");
} // end function


/* Purpose: Perform DFS traversal to write k-itemsets to output file
 *     Pre: Output file stream, k-limit or max depth to traverse, current node,
 *          current depth, current path
 *    Post: Only frequent itemsets remain in trie
 ******************************************************************************/
void Trie::wdfs(ofstream &target, const int &klimit, Node *node, int depth, string path)
{
    node->mark();

    for (int i = 0; i < node->size(); i++)
    {
        if (depth == klimit)
        {
            target << path << " (" << node->support() << ")\n";
        }
        else if (!(*node)[i]->isMarked())
        {
            wdfs(target, klimit, (*node)[i], depth + 1, path + " " + node->getLabel(i));
        }
    }
}

#endif
