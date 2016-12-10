#include "header.h"

int main()
{
    Trie trie;
    ifstream fin;
    ofstream fout;

    fin.open("T5.N0.01K.D0.02K.txt");
    fout.open("T5.N0.01K.D0.02K-output.txt");

    trie.read(fin);
    trie.write(fout, 2);

    return 0;
}
