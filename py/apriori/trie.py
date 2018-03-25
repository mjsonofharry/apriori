import sys

class Node:
    def __init__(self, label):
        self.mChildren = []
        self.mLabel = label
        self.mSupport = 1

    def add_child(self, label):
        self.mChildren.append(Node(label))

    def display_children(self):
        print([child.mLabel for child in self.mChildren])

    def get_child(self, label):
        node = [child for child in self.mChildren if child.mLabel is label][0]
        return node

class Trie:
    def __init__(self):
        self.mRoot = Node("Root")
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

        for child in node.mChildren:
            self.display(node=child, tabs=tabs+1)

    def get_node_count(self, node=None):
        count = 1
        if not node:
            node = self.mRoot

        for child in node.mChildren:
            count += self.get_node_count(child)
        return count

    def insert_item_as_node(self, node, item_label):
        print("\t\tInserting item:", item_label)
        for child in node.mChildren:
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

        node.mChildren = [child for child in node.mChildren if child.mSupport >= support_threshold]
        for child in node.mChildren:
            self.prune(support_threshold, node=child)

    def compute_all_paths_dfs(self, path, node):
        path.append(node.mLabel)
        if not node.mChildren:
            self.mPaths.append(path)
        else:
            for child in node.mChildren:
                self.compute_all_paths_dfs(path, child)

    def write_results_to_file(self):
        for node in self.mRoot.mChildren:
            self.compute_all_paths_dfs([], node=node)

        for path in self.mPaths:
            print(path)
