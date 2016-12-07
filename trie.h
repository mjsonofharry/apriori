#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <stringstream>
#include <linkedList.h>

using namespace std;

struct Data
{
    Node   *mNode;
    string mLabel;

    Data()
    {
        mNode  = NULL;
        mLabel = "";
    }

    Data(Node *node, string data)
    {
        mNode  = node;
        mLabel = data;
    }

    ~Data()
    {
        mNode  = NULL;
        mLabel = "";
    }

    Data& operator=(const Data &rhs)
    {
        mNode  = rhs.mNode;
        mLabel = rhs.mLabel;
    }

    bool operator==(const Data &rhs)
    {
        return mLabel == rhs.mLabel;
    }

    bool operator<(const Data &rhs)
    {
        return mLabel < rhs.mLabel;
    }

    bool operator<=(const Data &rhs)
    {
        return mLabel <= rhs.mLabel;
    }

    bool operator>(const Data &rhs)
    {
        return mLabel > rhs.mLabel;
    }

    bool operator>=(const Data &rhs)
    {
        return mLabel >= rhs.mLabel;
    }
}

class Trie
{
    private:
        struct Node
        {
            LinkedList <Data*> mList;
            int mSupport;

            /* Purpose:  Default constructor for node
             *     Pre:  None
             *    Post:  Node is initialized with default values
             ******************************************************************/
            Node()
            {
                mSupport = 0;
            } // end function

            Node(string data)
            {
                Data item;

                item.mLabel = data;

                mList.insert(item);
            }

            /* Purpose:  Destructor for node
             *     Pre:  None
             *    Post:  Node pointers are grounded
             ******************************************************************/
            ~Node()
            {
                mList.clear();
            } //end function
        } // end struct

        Node *mRootNode;
        int  mCount;
    // end private

    public:
        /* Purpose:  Constructor for trie
         *     Pre:  None
         *    Post:  Creates root node
         ******************************************************************/
        Trie()
        {
            mRootNode = new Node();
        }

        /* Purpose:  Destructor for trie
         *     Pre:  None
         *    Post:  Destroys subtree from root node
         ******************************************************************/
        ~Trie()
        {
            removeSubtree(mRootNode);
        }

        /* Purpose:  Get the root node of the trie
         *     Pre:  None
         *    Post:  Returns root node
         ******************************************************************/
        Node *getRootNode()
        {
            return mRootNode;
        } // end function

        /* Purpose:  Get the number of nodes in the trie
         *     Pre:  None
         *    Post:  Returns number of nodes
         ******************************************************************/
        int getCount()
        {
            return mCount;
        } // end function

        void insert(Node *newNode);

        void insert(string data)
        {
        }

        void prune();

        /* Purpose:  Read a dataset
         *     Pre:  Input stream
         *    Post:  Inserts each transaction into the trie
         ******************************************************************/
        void read(istream in)
        {
            stringstream ss;
            string data;

            /* read each transaction */
            while (in)
            {
                /* get a single transaction */
                getline(in, data);
                ss.str() = data;

                /* insert each item of the current transaction */
                while (ss)
                {
                    ss >> data;
                    insert(data);
                }
            }
        }

        void removeSubtree(Node *rootNode);
        void write(ostream out);
    // end public
} // end class

#endif
