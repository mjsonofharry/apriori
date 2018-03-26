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
        print([child.mLabel for child in self.mChildren])

    def get_child(self, label):
        matches = [child for child in self.mChildren if child.mLabel is label]
        if matches:
            return matches[0]
        return None
