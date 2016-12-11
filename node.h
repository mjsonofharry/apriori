#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

const int STARTING_BUFFER = 8;

class Node
{
    private:
        Node   **mChild;
        int    mCount;
        int    mBuffer;
        string mLabel;
        int    mSupport;

        void upsize();
    public:
        Node();
        Node(string label);
        ~Node();

        void   add(Node *newNode);
        Node*  get(const string &searchKey);
        Node*  get(const int &index);
        int    getCount();
        int    getIndex(string searchKey);
        string getLabel();
        bool   isFrequent(const int minimum);

        Node* operator[](const int &index);
        void  operator++();
}; // end class

Node::Node()
{
    mBuffer  = STARTING_BUFFER;
    mChild   = new Node*[STARTING_BUFFER];
    mCount   = 0;

    mLabel   = "";
    mSupport = 0;
} // end constructor


Node::Node(string label)
{
    mBuffer  = STARTING_BUFFER;
    mChild   = new Node*[STARTING_BUFFER];
    mCount   = 0;

    mLabel   = label;
    mSupport = 0;
} // end constructor


Node::~Node()
{
    if (mChild != NULL)
    {
        delete [] mChild;
        mChild = NULL;
    } // end if
} // end destructor


void Node::add(Node *newNode)
{
    if (mCount >= mBuffer)
    {
        upsize();
    }

    mChild[mCount] = newNode;
    mCount++;
} // end function


Node* Node::get(const int &index)
{
    return mChild[index];
} // end function


Node* Node::get(const string &searchKey)
{
    Node *child;
    int i;

    child = NULL;

    for (i = 0; i < mCount; i++)
    {
        if (mChild[i]->mLabel == searchKey)
        {
            child = mChild[i];
        } // end if
    } // end for

    return child;
} // end function


int Node::getCount()
{
    return mCount;
} // end function


int Node::getIndex(string searchKey)
{
    int childIndex, i;

    childIndex = -1;

    for (i = 0; i < mCount; i++)
    {
        if (mChild[i]->mLabel == searchKey)
        {
            childIndex = i;
            break;
        } // end if
    } // end for

    return childIndex;
} // end function


string Node::getLabel()
{
    return mLabel;
}


bool Node::isFrequent(const int minimum)
{
    return mSupport >= minimum;
}


void Node::upsize()
{
    Node **array;
    int i;

    printf("\tBuffer too small (%d) for number of nodes (%d), upsizing\n", mBuffer, mCount);

    mBuffer *= 2;
    array = new Node*[mBuffer];
    if (array == NULL)
    {
        perror(NULL);
        exit(1);
    } // end if

    /* copy old memory over to new array */
    for (i = 0; i < mCount; i++)
    {
        array[i] = mChild[i];
    } // end for
    for (; i < mBuffer; i++)
    {
        array[i] = NULL;
    } // end for

    for (i = 0; i < mCount; i++)
    {
        delete mChild[i];
        mChild[i] = NULL;
    }

    mChild = array;
    array  = NULL;
} // end function


Node* Node::operator[](const int &index)
{
    return mChild[index];
} // end operator overload


void Node::operator++()
{
    mSupport++;
} // end operator overload


#endif
