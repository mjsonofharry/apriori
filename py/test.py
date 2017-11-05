from trie import Trie

def main():
    trie = Trie()
    trie.read_dataset_from_file("../samples/T5.N0.01K.D0.02K.txt")
    trie.display()
    trie.prune(2)
    trie.display()

if __name__ == "__main__":
    main()
