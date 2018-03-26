class Node:
    def __init__(self, label):
        self.mChildren = []
        self.mLabel = label
        self.mSupport = 1

    def add_child(self, label):
        new_node = Node(label)
        self.mChildren.append(new_node)
        return new_node

    def display_children(self):
        print([child.mLabel for child in self.get_children()])

    def get_child(self, label):
        matches = [child for child in self.mChildren if child.mLabel is label]
        if matches:
            return matches[0]
        return None

    def get_children(self):
        return [child for child in self.mChildren]

class HashNode:
    def __init__(self, label):
        self.mChildren = {}
        self.mLabel = label
        self.mSupport = 1

    def add_child(self, label):
        new_node = Node(label)
        self.mChildren[label] = new_node
        return new_node

    def display_children(self):
        print([child.mLabel for child in self.get_children()])

    def get_child(self, label):
        return mChildren.get(label)

    def get_children(self):
        return [child for child in self.mChildren.values()]
