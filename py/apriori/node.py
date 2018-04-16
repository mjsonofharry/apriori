import abc


class AbstractNode(metaclass=abc.ABCMeta):
    def display_children(self):
        print([child.mLabel for child in self.get_children()])
   
    @abc.abstractmethod
    def add_child(self, label):
        pass

    @abc.abstractmethod
    def get_child(self, label):
        pass

    @abc.abstractmethod
    def get_children(self):
        pass

    @abc.abstractmethod
    def set_children(self):
        pass


class ListNode(AbstractNode):
    def __init__(self, label):
        self.mChildren = []
        self.mLabel = label
        self.mSupport = 1

    def add_child(self, label):
        new_node = Node(label)
        self.mChildren.append(new_node)
        return new_node

    def get_child(self, label):
        matches = [child for child in self.mChildren if child.mLabel is label]
        if matches:
            return matches[0]
        return None

    def get_children(self):
        return [child for child in self.mChildren]

    def set_children(self, children):
        self.mChildren = children

    def sort(self, key=None, reverse=False):
        self.mChildren.sort(key=key, reverse=reverse)


class HashNode(AbstractNode):
    def __init__(self, label):
        self.mChildren = {}
        self.mLabel = label
        self.mSupport = 1

    def add_child(self, label):
        new_node = Node(label)
        self.mChildren[label] = new_node
        return new_node

    def get_child(self, label):
        return self.mChildren.get(label)

    def get_children(self):
        return [child for child in self.mChildren.values()]

    def set_children(self, children):
        self.mChildren = {child.mLabel:child for child in children}

    def assign(self, key, value):
        self.mChildren[key] = value


class BinaryNode(AbstractNode):
    def __init__(self, label):
        self.mFirstChild = None
        self.mNextSibling = None
        self.mLabel = label
        self.mSupport = 1

    def add_child(self, label):
        new_node = BinaryNode(label)
        if not self.mFirstChild:
            self.mFirstChild = new_node
        else:
            child = self.mFirstChild
            while child.mNextSibling is not None:
                child = child.mNextSibling
            child.mNextSibling = new_node
        return new_node
        
    def get_child(self, label):
        child = self.mFirstChild
        while child is not None:
            if child.mLabel == label:
                return child
            child = child.mNextSibling
        return None

    def get_children(self):
        children = []
        child = self.mFirstChild
        while child is not None:
            children.append(child)
            child = child.mNextSibling
        return children

    def set_children(self, children):
        if not children:
            self.mFirstChild = None
            return
        self.mFirstChild = children[0]
        child = self.mFirstChild
        for new_child in children[1:]:
            child.mNextSibling = new_child
            child = child.mNextSibling

    def get_successors(self):
        return self.mFirstChild, self.mNextSibling

    def get_siblings(self):
        all_siblings = []
        sibling = self.mNextSibling
        while sibling is not None:
            all_siblings.append(sibling)
            sibling = sibling.mNextSibling
        return all_siblings


Node = ListNode