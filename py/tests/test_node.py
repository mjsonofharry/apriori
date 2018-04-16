from test_common import apriori
from apriori import ListNode, HashNode, BinaryNode

import pytest

@pytest.fixture(params=[ListNode, HashNode, BinaryNode])
def AbstractNode(request):
    '''Provides test with each node implementation'''
    return request.param

@pytest.fixture
def simple_tree(AbstractNode):
    '''Provides a 1-layer tree'''
    root = AbstractNode('Root')
    root.add_child('1')
    root.add_child('2')
    root.add_child('3')
    return root

@pytest.fixture
def complex_tree(AbstractNode, simple_tree):
    '''Provides a 2-layer tree'''
    root = simple_tree
    for child in root.get_children():
        label = child.mLabel
        child.add_child(label + '-A')
        child.add_child(label + '-B')
    return root

def test__simple_tree(AbstractNode, simple_tree):
    root = simple_tree
    assert isinstance(root, AbstractNode)
    assert root.mLabel == 'Root'
    assert len(root.get_children()) == 3
    for child in root.get_children():
        assert len(child.get_children()) == 0

def test__complex_tree(AbstractNode, complex_tree):
    root = complex_tree
    assert isinstance(root, AbstractNode)
    assert root.mLabel == 'Root'
    assert len(root.get_children()) == 3
    for child in root.get_children():
        assert len(child.get_children()) == 2

def test__init(AbstractNode):
    node = AbstractNode('MyNode')
    assert node.get_children() == []
    assert node.mLabel == 'MyNode'
    assert node.mSupport == 1

def test__init_exception(AbstractNode):
    with pytest.raises(TypeError):
        node = AbstractNode()

def test__add_one_child(AbstractNode):
    node = AbstractNode('X')
    child = node.add_child('X-0')
    assert len(node.get_children()) == 1
    assert len(child.get_children()) == 0
    assert child.mLabel == 'X-0'
    assert child.mSupport == 1

def test__add_multiple_children(AbstractNode):
    node = AbstractNode('TEST')
    child_1 = node.add_child('TEST_SUB_1')
    child_2 = node.add_child('TEST_SUB_2')
    assert len(node.get_children()) == 2
    assert len(child_1.get_children()) == 0
    assert len(child_2.get_children()) == 0
    assert child_1.mLabel == 'TEST_SUB_1'
    assert child_2.mLabel == 'TEST_SUB_2'
    assert child_1.mSupport == 1
    assert child_2.mSupport == 1

def test__add_grandchild(AbstractNode):
    node = AbstractNode('root')
    node.add_child('home')
    child = node.get_children()[0]
    grandchild = child.add_child('mharrison')
    assert len(node.get_children()) == 1
    assert len(child.get_children()) == 1
    assert len(grandchild.get_children()) == 0
    assert node.mLabel == 'root'
    assert child.mLabel == 'home'
    assert grandchild.mLabel == 'mharrison'
    assert node.mSupport == 1
    assert child.mSupport == 1
    assert grandchild.mSupport == 1

def test__add_child_exception(AbstractNode):
    node = AbstractNode('Pascal')
    with pytest.raises(TypeError):
        node.add_child()

def test__display_no_children(AbstractNode, capsys):
    node = AbstractNode(0)
    node.display_children()
    out, err = capsys.readouterr()
    assert out == "[]\n"

def test__display_one_child(AbstractNode, capsys):
    node = AbstractNode('S')
    node.add_child('S-1')
    node.display_children()
    out, err = capsys.readouterr()
    assert out == "['S-1']\n"

def test__display_multiple_children(AbstractNode, capsys):
    node = AbstractNode('X')
    node.add_child(1)
    node.add_child(2)
    node.add_child(3)
    node.display_children()
    out, err = capsys.readouterr()
    assert out == "[1, 2, 3]\n"

def test__get_only_child(AbstractNode):
    node = AbstractNode('Parent')
    child = node.add_child('Child')
    assert node.get_child('Child') is child

def test__get_child_none(AbstractNode):
    node = AbstractNode('SUPER')
    assert node.get_child('SUB') is None

def test__get_child_with_siblings(AbstractNode):
    node = AbstractNode('RT')
    child_1 = node.add_child('LHS')
    child_2 = node.add_child('RHS')
    assert node.get_child('LHS') is child_1
    assert node.get_child('RHS') is child_2

def test__get_nonexistent_child(AbstractNode):
    node = AbstractNode(100)
    node.add_child('X0')
    node.add_child('X1')
    assert not node.get_child('X2')

def test__get_child_exception(AbstractNode):
    node = AbstractNode('_')
    node.add_child('~')
    with pytest.raises(TypeError):
        attempt = node.get_child()

def test__get_children_single(AbstractNode):
    node = AbstractNode('0')
    child = node.add_child('1')
    assert node.get_children() == [child]

def test__get_children_multiple(AbstractNode):
    node = AbstractNode('Kazu')
    child_1 = node.add_child('Ichi')
    child_2 = node.add_child('Ni')
    child_3 = node.add_child('San')
    assert node.get_children() == [child_1, child_2, child_3]

def test__get_children_none(AbstractNode):
    node = AbstractNode('Pascal')
    assert node.get_children() == []

def test__set_children(AbstractNode, simple_tree):
    node = simple_tree
    child_1 = AbstractNode('Uno')
    child_2 = AbstractNode('Dos')
    child_3 = AbstractNode('Tres')
    children = [child_1, child_2, child_3]
    node.set_children(children)
    assert node.get_children() == children

def test__set_children_empty(AbstractNode, simple_tree):
    node = simple_tree
    node.set_children([])
    assert node.get_children() == []
