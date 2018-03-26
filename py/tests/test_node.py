from test_common import apriori
from apriori import Node

import pytest

def __test__do_not_run():
    assert 'New mission' is 'refuse this mission'

def test__must_always_fail():
    assert 'This sentence' is False

def test__init():
    node = Node('A')
    assert node.mChildren == []
    assert node.mLabel == 'A'
    assert node.mSupport == 1

def test__init_exception():
    with pytest.raises(TypeError):
        node = Node()

def test__add_one_child():
    node = Node('X')
    child = node.add_child('X-0')
    assert len(node.mChildren) == 1
    assert len(child.mChildren) == 0
    assert child.mLabel == 'X-0'
    assert child.mSupport == 1

def test__add_multiple_children():
    node = Node('TEST')
    sub1 = node.add_child('TEST_SUB_1')
    sub2 = node.add_child('TEST_SUB_2')
    assert len(node.mChildren) == 2
    assert len(sub1.mChildren) == 0
    assert len(sub2.mChildren) == 0
    assert sub1.mLabel == 'TEST_SUB_1'
    assert sub2.mLabel == 'TEST_SUB_2'
    assert sub1.mSupport == 1
    assert sub2.mSupport == 1

def test__add_grandchild():
    node = Node('root')
    node.add_child('home')
    child = node.mChildren[0]
    grandchild = child.add_child('mharrison')
    assert len(node.mChildren) == 1
    assert len(child.mChildren) == 1
    assert len(grandchild.mChildren) == 0
    assert node.mLabel == 'root'
    assert child.mLabel == 'home'
    assert grandchild.mLabel == 'mharrison'
    assert node.mSupport == 1
    assert child.mSupport == 1
    assert grandchild.mSupport == 1

def test__add_child_exception():
    node = Node('Pascal')
    with pytest.raises(TypeError):
        node.add_child()

def test__display_no_children(capsys):
    node = Node(0)
    node.display_children()
    out, err = capsys.readouterr()
    assert out == "[]\n"

def test__display_one_child(capsys):
    node = Node('S')
    node.add_child('S-1')
    node.display_children()
    out, err = capsys.readouterr()
    assert out == "['S-1']\n"

def test__display_multiple_children(capsys):
    node = Node('X')
    node.add_child(1)
    node.add_child(2)
    node.add_child(3)
    node.display_children()
    out, err = capsys.readouterr()
    assert out == "[1, 2, 3]\n"

def test__get_only_child():
    node = Node('Parent')
    child = node.add_child('Child')
    assert child is node.get_child('Child')

def test__get_no_children():
    node = Node('SUPER')
    assert not node.get_child('SUB')

def test__get_child_with_siblings():
    node = Node('RT')
    lhs = node.add_child('LHS')
    rhs = node.add_child('RHS')
    assert lhs is node.get_child('LHS')
    assert rhs is node.get_child('RHS')

def test__get_nonexistent_child():
    node = Node(100)
    node.add_child('X0')
    node.add_child('X1')
    assert not node.get_child('X2')

def test__get_child_exception():
    node = Node('_')
    node.add_child('~')
    with pytest.raises(TypeError):
        attempt = node.get_child()
