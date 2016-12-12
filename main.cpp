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
