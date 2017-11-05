from trie import Trie

def main():
    trie = Trie()
    trie.read_dataset_from_file("../samples/T5.N0.01K.D0.02K.txt")
    trie.prune(2)
    trie.write_results_to_file()

if __name__ == "__main__":
    main()
