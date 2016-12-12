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

#include "header.h"

int main()
{
    Trie trie;
    ifstream fin;
    ofstream fout;

    fin.open("T5.N0.01K.D0.02K.txt");
    printf("Opened %s", "T5.N0.01K.D0.02K.txt\n");
    fout.open("output_test.txt");
    printf("Opened %s", "output_test.txt\n");

    trie.read(fin);
    fin.close();

    trie.prune(2);

    for (int i = 0; i < 9; i++)
    {
        printf("Writing %d-itemsets\n", i);
        trie.write(fout, i);
    }

    fout.close();

    return 0;
}
