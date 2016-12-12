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

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <string>

#include "linkedList.h"

using namespace std;

class Node
{
    private:
        struct Container
        {
            Node   *mChild;
            string mLabel;

            /* Purpose: Constructor for container
             *     Pre: None
             *    Post: Container initialized with default values
             ******************************************************************/
            Container()
            {
                mChild   = NULL;
                mLabel   = "";
            } // end constructor

            /* Purpose: Constructor for container
             *     Pre: Item label
             *    Post: Container initialized with default values and label
             ******************************************************************/
            Container(string label)
            {
                mChild   = NULL;
                mLabel   = label;
            } // end constructor

            /* Purpose: Destructor
             *     Pre: None
             *    Post: Child set to NULL
             ******************************************************************/
            ~Container()
            {
                mChild = NULL;
            } // end destructor

            void operator=(Container rhs)
            {
                mChild   = rhs.mChild;
                mLabel   = rhs.mLabel;
            } // end operator

            bool operator==(Container rhs)
            {
                return mLabel == rhs.mLabel;
            } // end operator

            bool operator==(string rhs)
            {
                return mLabel == rhs;
            } // end operator

            bool operator!=(Container rhs)
            {
                return mLabel != rhs.mLabel;
            } // end operator

            bool operator!=(string rhs)
            {
                return mLabel != rhs;
            } // end operator

            bool operator<(Container rhs)
            {
                return mLabel < rhs.mLabel;
            } // end operator

            bool operator<(string rhs)
            {
                return mLabel < rhs;
            } // end operator

            bool operator<=(Container rhs)
            {
                return mLabel <= rhs.mLabel;
            } // end operator

            bool operator<=(string rhs)
            {
                return mLabel <= rhs;
            } // end operator

            bool operator>(Container rhs)
            {
                return mLabel > rhs.mLabel;
            } // end operator

            bool operator>(string rhs)
            {
                return mLabel > rhs;
            } // end operator

            bool operator>=(Container rhs)
            {
                return mLabel >= rhs.mLabel;
            } // end operator

            bool operator>=(string rhs)
            {
                return mLabel >= rhs;
            } // end operator
        }; // end struct

        LinkedList<Container> mList;
        int  mSupport;
        bool mFlag;
    // end private

    public:
        Node();

        void   insert(string label);
        bool   isExist(string label);
        bool   isMarked();
        Node*  get(string label);
        string getLabel(int index);
        void   mark();
        int    size();
        int    support();

        Node* operator[](int i);
        void  operator++();
    // end public
}; // end class


/* Purpose: Constructor for node
 *     Pre: None
 *    Post: Node initialized with default values
 ******************************************************************************/
Node::Node()
{
    mSupport = 0;
    mFlag    = false;
} // end function


/* Purpose: Insert item into node's linked list
 *     Pre: Item label
 *    Post: Node with given labelinserted into linked list
 ******************************************************************************/
void Node::insert(string label)
{
    Container newContainer;
    Node      *newNode;

    newNode = new Node();
    if (newNode == NULL)
    {
        fprintf(stderr, "CRITICAL: Failed to allocate space for new Node!\n");
        exit(1);
    } // end if

    newContainer.mChild = newNode;
    newContainer.mLabel = label;

    mList.insert(newContainer);
} // end function


/* Purpose: Check if node has a child with given item label
 *     Pre: Item label
 *    Post: Returns true if matching child found
 ******************************************************************************/
bool Node::isExist(string label)
{
    Container tmp;
    tmp.mLabel = label;

    return mList.isExist(tmp);
} // end function


/* Purpose: Check if node has been marked during DFS traversal
 *     Pre: None
 *    Post: Returns true if marked
 ******************************************************************************/
bool Node::isMarked()
{
    return mFlag;
} // end function


/* Purpose: Get child with given label
 *     Pre: Item label
 *    Post: Returns child node
 ******************************************************************************/
Node* Node::get(string label)
{
    Node *tmp = NULL;

    for (int i = 0; i < size(); i++)
    {
        if (mList[i] == label)
        {
            tmp = mList[i].mChild;
            break;
        } // end if
    } // end for

    return tmp;
} // end function


/* Purpose: Get label from child at given index
 *     Pre: Index
 *    Post: Returns label
 ******************************************************************************/
string Node::getLabel(int index)
{
    return mList[index].mLabel;
} // end function


/* Purpose: Mark node as visited during DFS traversal
 *     Pre: None
 *    Post: Node flag marked as true
 ******************************************************************************/
void Node::mark()
{
    mFlag = true;
} // end function


/* Purpose: Get number of nodes in linked list
 *     Pre: None
 *    Post: Returns node count
 ******************************************************************************/
int Node::size()
{
    return mList.getCount();
} // end function


/* Purpose: Get node support value
 *     Pre: None
 *    Post: Returns support
 ******************************************************************************/
int Node::support()
{
    return mSupport;
} // end function


Node* Node::operator[](int index)
{
    return mList[index].mChild;
} // end operator


void Node::operator++()
{
    mSupport++;
} // end operator


#endif
