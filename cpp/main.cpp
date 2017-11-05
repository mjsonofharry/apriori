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

#include "header.h"

int main(int argc, char *argv[])
{
    Trie trie;
    ifstream fin;
    ofstream fout;

    if (argc != 3)
    {
        printf("Source and target files needed: apriori <source> <target>\nTerminating...\n");
        return 0;
    } // end if

    fin.open(argv[1]);
    printf("Opening %s", argv[1]);
    fout.open(argv[2]);
    printf("Opened %s", argv[2]);

    if (!fin || !fout || fin.fail() || fout.fail())
    {
        fprintf(stderr, "WARNING: Failed to open file.\nTerminating...\n");
    } // end if

    trie.read(fin);
    fin.close();

    trie.prune(2);

    for (int i = 1; i < 9; i++)
    {
        printf("Writing %d-itemsets\n", i);
        trie.write(fout, i);
    } // end for

    fout.close();

    return 0;
}
