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

Node::Node()
{
    mChild  = NULL;
    mBuffer = 0;
    mCount  = 0;

    mLabel   = "";
    mSupport = 0;

    flag = false;
}

Node::Node(string label)
{
    mChild  = new Node*[INITIAL_BUFFER_SIZE];
    mBuffer = INITIAL_BUFFER_SIZE;
    mCount  = 0;

    if (mChild == NULL)
    {
        fprintf(stderr, "CHILDLESS NODE");
        perror(NULL);
        exit(1);
    }

    for (int i = 0; i < INITIAL_BUFFER_SIZE; i++)
    {
        mChild[i] = NULL;
    }

    mLabel   = label;
    mSupport = 1;

    flag = false;
}

Node::~Node()
{
    for (int i = 0; i < mBuffer; i++)
    {
        mChild[i] = NULL;
    }

    delete [] mChild;
    mChild = NULL;
}

void Node::add(string label)
{
    Node *newNode = new Node(label);
    if (newNode == NULL)
    {
        fprintf(stderr, "UNABLE TO ALLOCATE NEW NODE");
        perror(NULL);
        exit(1);
    }

    if (mBuffer <= mCount + 1)
    {
        resize();
    }

    mChild[mCount] = newNode;
    mCount++;
}

Node* Node::get(const string &searchKey)
{
    if (mChild == NULL)
    {
        fprintf(stderr, "NULL CHILDREN");
        perror(NULL);
    }

    for (int i = 0; i < mCount && mChild[i] != NULL; i++)
    {
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
    Node **array = new Node*[mBuffer * 2];
    mBuffer *= 2;
    if (array == NULL)
    {
        fprintf(stderr, "UNABLE TO ALLOCATE NEW ARRAY");
        perror(NULL);
        exit(1);
    }

    for (int i = 0; i < mCount; i++)
    {
        array[i] = mChild[i];
        mChild[i] = NULL;
    }

    for (int i = mCount; i < mBuffer; i++)
    {
        array[i] = NULL;
    }

    delete [] mChild;
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
