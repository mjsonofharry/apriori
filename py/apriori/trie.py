from .node import Node

import sys

def main():
    trie = Trie()
    trie.read_dataset_from_file("../samples/T5.N0.01K.D0.02K.txt")
    trie.prune(2)
    trie.write_results_to_file()

class Trie:
    def __init__(self, AbstractNode=Node):
        self.mRoot = AbstractNode("Root")
        self.mRoot.mSupport = sys.maxsize
        self.mPaths = []

    def display(self, node=None, tabs=0):
        if not node:
            print("Total nodes:", self.get_node_count())
            node = self.mRoot
        else:
            tab = ""
            for i in range(0, tabs):
                tab += " | "

            print(tab, str(node.mLabel), '(' + str(node.mSupport) + ')')

        for child in node.get_children():
            self.display(node=child, tabs=tabs+1)

    def get_node_count(self, node=None):
        count = 1
        if not node:
            node = self.mRoot

        for child in node.get_children():
            count += self.get_node_count(child)
        return count

    def insert_item_as_node(self, node, item_label):
        print("\t\tInserting item:", item_label)
        for child in node.get_children():
            if child.mLabel is item_label:
                child.mSupport += 1
                return
        node.add_child(item_label)

    def insert_itemset_as_branch(self, itemset):
        itemset = [item for item in itemset if item is not ""]
        if not itemset:
            return

        print("\tInserting itemset:", itemset)
        node = self.mRoot
        for label in itemset:
            self.insert_item_as_node(node, label)
            node = node.get_child(label)

    def read_dataset_from_file(self, file_name):
        print("Reading dataset:", file_name)
        with open(file_name, 'r') as data_file:
            data = data_file.read()

        dataset = data.split('\n')
        for line in dataset:
            itemset = line.split(' ')
            self.insert_itemset_as_branch(itemset)

    def prune(self, support_threshold, node=None):
        if not node:
            node = self.mRoot

        pruned_children = [
            child for child in node.get_children() if child.mSupport >= support_threshold
            ]
        node.set_children(pruned_children)
        for child in node.get_children():
            self.prune(support_threshold, node=child)

    def compute_all_paths_dfs(self, path, node):
        path.append(node.mLabel)
        if not node.get_children():
            self.mPaths.append(path)
        else:
            for child in node.get_children():
                self.compute_all_paths_dfs(path, child)

    def write_results_to_file(self):
        for node in self.mRoot.get_children():
            self.compute_all_paths_dfs([], node=node)

        for path in self.mPaths:
            print(path)

if __name__ == '__main__':
    main()
