#include "header.h"

int main()
{
    Trie trie;
    ifstream fin;
    ofstream fout;

    fin.open("T5.N0.01K.D0.02K.txt");
    fout.open("output_test.txt");

    cout << "Reading...\n";
    trie.read(fin);
    cout << "Read complete. Writing...\n";
    trie.write(fout, 2);
    cout << "Write complete. Goodbye!\n";

    return 0;
}
