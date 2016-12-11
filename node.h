#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

const int INITIAL_BUFFER_SIZE = 8;

class Node
{
    private:
        Node   **mChild;
        int    mBuffer;
        int    mCount;

        string mLabel;
        int    mSupport;

        void resize();

    public:
        bool flag;

        Node();
        Node(string label);
        ~Node();

        void   add(string item);
        Node*  get(const string &searchKey);
        int    getCount();
        string getLabel();
        int    getSupport();

        Node* operator[](const int &index);
        void  operator++();
};


Node::Node(string label)
{
    mChild  = new Node*[INITIAL_BUFFER_SIZE];
    if (mChild == NULL)
    {
        fprintf(stderr, "Node::Node: ERROR: MEMORY ALLOCATION FAILURE\n");
        exit(1);
    }

    mBuffer = INITIAL_BUFFER_SIZE;
    for (int i = 0; i < mBuffer; i++)
    {
        mChild[i] = NULL;
    }
    mCount = 0;

    mLabel   = label;
    mSupport = 1;

    flag = false;

    printf("Created new node with label %s and buffer %d\n", mLabel.c_str(), mBuffer);
}

Node::~Node()
{
    if (mChild != NULL)
    {
        delete mChild;
        mChild = NULL;
    }
}

void Node::add(string label)
{
    Node *newNode;

    newNode = new Node(label);
    if (newNode == NULL)
    {
        fprintf(stderr, "Node::add: ERROR: MEMORY ALLOCATION FAILURE\n");
        exit(1);
    }

    if (mBuffer <= mCount + 1)
    {
        printf("Node::add: Warning: resizing buffer (%d) to store %d nodes\n", mBuffer, mCount + 1);
        resize();
    }

    mChild[mCount] = newNode;
    mCount++;

    newNode = NULL;
}

Node* Node::get(const string &searchKey)
{
    if (mChild == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < mCount; i++)
    {
        if (mChild[i] == NULL)
        {
            return NULL;
        }

        if (mChild[i]->mLabel == searchKey)
        {
            return mChild[i];
        }
    }

    return NULL;
}

int Node::getCount()
{
    return mCount;
}

string Node::getLabel()
{
    return mLabel;
}

int Node::getSupport()
{
    return mSupport;
}

void Node::resize()
{

    mBuffer *= 2;

    Node **array = new Node*[mBuffer];
    if (array == NULL)
    {
        fprintf(stderr, "Node::resize: ERROR: MEMORY ALLOCATION FAILURE\n");
        exit(1);
    }

    for (int i = 0; i < mCount; i++)
    {
        array[i]  = mChild[i];
        mChild[i] = NULL;
    }

    for (int i = mCount; i < mBuffer; i++)
    {
        array[i] = NULL;
    }

    mChild = array;
    array  = NULL;
}

Node* Node::operator[](const int &i)
{
    return mChild[i];
}

void Node::operator++()
{
    mSupport++;
}

#endif
