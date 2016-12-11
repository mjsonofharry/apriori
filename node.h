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
    mBuffer  = 0;
    mChild   = NULL;
    mCount   = 0;

    mLabel   = "";
    mSupport = 0;
} // end constructor


Node::Node(string label)
{
    mBuffer  = 0;
    mChild   = NULL;
    mCount   = 0;

    mLabel   = label;
    mSupport = 0;
} // end constructor


Node::~Node()
{
    int i;

    if (mChild != NULL)
    {
        for (i = 0; i < mCount; i++)
        {
            delete mChild[i];
        }

        delete [] mChild;
        mChild = NULL;
    } // end if
} // end destructor


void Node::add(Node *newNode)
{
    if (mBuffer <= mCount + 1)
    {
        upsize();
    } // end if

    mCount++;

    mChild[mCount] = newNode;

    printf("\tInserted new node (%s), count incremented (%d)\n", newNode->getLabel().c_str(), newNode->getCount());
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

    printf("\tBuffer too small (%d) to increase number of nodes (%d), upsizing\n", mBuffer, mCount);

    /* buffer is zero, so set it to default */
    if (mBuffer == 0)
    {
        mBuffer = STARTING_BUFFER;
    }
    /* double the current buffer */
    else
    {
        mBuffer *= 2;
    } // end if

    /* array is null, so allocate it */
    if (mChild == NULL)
    {
        mChild = new Node*[mBuffer];
        for (i = 0; i < mBuffer; i++)
        {
            mChild[i] = NULL;
        } // end for
    }
    /* array already exists, so copy to a new larger one */
    else
    {
        /* allocate heap space for new array */
        array = new Node*[mBuffer];
        if (array == NULL)
        {
            perror(NULL);
            exit(1);
        } // end if

        /* copy old array data to new array, then sanitize old array */
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
            mChild[i] = NULL;
        } // end for

        delete [] mChild;
        mChild = array;
        array  = NULL;
    } // end if

    printf("\tNew buffer allocated (%d)\n", mBuffer);
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
