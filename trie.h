#ifndef TRIE_H
#define TRIE_H

#include <fstream>
#include <sstream>
#include <string>

#include "linkedList.h"

const string ROOT_LABEL = "TRIE_ROOT_IGNORE";

using namespace std;

class Trie
{
    private:
        struct Label
        {
            string mItem;
            Node   *mChild;

            Label()
            {
                mItem  = "";
                mChild = NULL;
            } // end constructor

            Label(string item, Node *child)
            {
                mItem  = item;
                mChild = child;
            } // end constructor

            ~Label()
            {
                mChild = NULL;
            } // end destructor

            void operator=(Label &rhs)
            {
                mItem  = rhs.item;
                mChild = rhs.child;
            } // end operator

            bool operator==(Label &rhs)
            {
                return mItem == rhs.mItem;
            } // end operator

            bool operator==(const string &rhs)
            {
                return mItem == rhs;
            } // end operator

            bool operator<(Label &rhs)
            {
                return mItem < rhs.mItem;
            } // end operator

            bool operator<(const string &rhs)
            {
                return mItem < rhs;
            } // end operator

            bool operator<=(Label &rhs)
            {
                return mItem <= rhs.mItem;
            } // end operator

            bool operator<=(const string &rhs)
            {
                return mItem <= rhs;
            } // end operator

            bool operator>(Label &rhs)
            {
                return mItem > rhs.mItem;
            } // end operator

            bool operator>(const string &rhs)
            {
                return mItem > rhs;
            } // end operator

            bool operator>=(Label &rhs)
            {
                return mItem >= rhs.mItem;
            } // end operator

            bool operator>=(const string &rhs)
            {
                return mItem >= rhs;
            } // end operator
        }; // end struct

        struct Node
        {
            LinkedList<Label> mList;
            bool flag;

            Node()
            {
                flag = false;
            } // end constructor

            ~Node()
            {
                mList.clear();
            } // end destructor
        }; // end struct

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
} // end constructor

Trie::~Trie()
{
    removeSubtree(mRootNode);
} // end denstructor

void Trie::insert(stringstream &itemset)
{
    Node *node, *newNode, *tmp;
    string item;
    int index;

    printf("Inserting: ");

    node = mRootNode;

    while (itemset)
    {
        itemset >> item;
        printf("%s ", item.c_str());

        /* check for the label and create it if necessary */
        if (!node->mList.isExist(item))
        {
            newNode = new Node();
            if (newNode == NULL)
            {
                exit(1);
            } // end if

            node->mList.insert(Label(item, newNode))
        } // end if

        /* traverse to the next node */
        tmp = node->mList[0];
        for (int i = 0; tmp != NULL; i++)
        {
            tmp = node->mList[i];

            if (tmp->mLabel == item)
            {
                node = tmp;
                break;
            } // end if
        } // end for
    } // end while
} // end function


void Trie::prune(const int &support)
{
    prune(mRootNode, support);
}


void Trie::prune(Node *node, const int &support)
{
    if (node->getSupport() < support)
    {
        removeSubtree(node);
    }
    else
    {
        for (int i = 0; i < node->getCount(); i++)
        {
            prune((*node)[i], support);
        }
    }
}

void Trie::removeSubtree(Node *node)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->getCount(); i++)
        {
            removeSubtree((*node)[i]);
        }

        delete node;
        node = NULL;
    }
}

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
        }
        printf("Read: %s\n", str.c_str());

        itemset.str(str);
        insert(itemset);

        itemset.str(string());
        itemset.clear();
    }
}

void Trie::write(ostream &target, const int &klimit)
{
    printf("%d-itemset\n", klimit);
    wdfs(target, klimit, mRootNode, 0, "");
    printf("\n");
}

void Trie::wdfs(ostream &target, const int &klimit, Node *node, int depth, string path)
{
    node->flag = true;

    for (int i = 0; i < node->getCount(); i++)
    {
        if (depth == klimit)
        {
            printf("%s (%d)\n", path.c_str(), node->getSupport());
        }
        else if (!(*node)[i]->flag)
        {
            wdfs(target, klimit, (*node)[i], depth + 1, path + " " + (*node)[i]->getLabel());
        }
    }
}

#endif
