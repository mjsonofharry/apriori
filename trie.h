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
        void write(ostream &target, const int &klimit);
        void wdfs(ostream &target, const int &klimit, Node *node, int depth, string path);
    // end public
}; // end class


Trie::Trie()
{
    mRootNode = new Node();
    mRootNode->setLabel(ROOT_LABEL);
} // end constructor


Trie::~Trie()
{
    removeSubtree(mRootNode);
} // end destructor


void Trie::insert(stringstream &itemset)
{
    Node *node;
    string item;
    int subtrees;

    /* begin traversal */
    node = mRootNode;

    /* for each item in the itemset */
    while (itemset)
    {
        if (node == NULL)
        {
            exit(1); // we seem to have met with a terrible fate
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


void Trie::prune(const int &support)
{
    prune(mRootNode, support);
} // end function


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


void Trie::read(ifstream &dataset)
{
    stringstream itemset;
    string       str;

    while (dataset)
    {
        getline(dataset, str);
        if (str == "")
        {
            break;
        } // end if
        printf("Reading itemset: %s\n", str.c_str());

        itemset.str(str);
        insert(itemset);

        itemset.str(string());
        itemset.clear();
    } // end while
} // end function


void Trie::write(ostream &target, const int &klimit)
{
    printf("%d-itemset\n", klimit);
    wdfs(target, klimit, mRootNode, 0, "");
    printf("\n");
} // end function


void Trie::wdfs(ostream &target, const int &klimit, Node *node, int depth, string path)
{
    node->mark();

    for (int i = 0; i < node->size(); i++)
    {
        if (depth == klimit)
        {
            printf("%s (%d)\n", path.c_str(), node->support());
        }
        else if (!(*node)[i]->isMarked())
        {
            wdfs(target, klimit, (*node)[i], depth + 1, path + " " + node->getLabel(i));
        }
    }
}

#endif
