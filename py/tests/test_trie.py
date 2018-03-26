from test_common import apriori
from apriori import Trie

import pytest
import sys

def test__init():
    trie = Trie()
    root = trie.mRoot
    assert root.mLabel == 'Root'
    assert root.mSupport == sys.maxsize
    assert trie.mPaths == []

def test__display_metadata_root_only(capsys):
    trie = Trie()
    trie.display()
    out, err = capsys.readouterr()
    assert out == 'Total nodes: 1\n'

def test__display_metadata_with_itemset(capsys):
    pytest.fail('Not implemented')

def test__display_root_only(capsys):
    trie = Trie()
    root = trie.mRoot
    trie.display(root)
    out, err = capsys.readouterr()
    assert out == ' Root ({})\n'.format(str(sys.maxsize))

def test__display_with_itemset(capsys):
    pytest.fail('Not implemented')

def test__get_node_count_root_only():
    pytest.fail('Not implemented')

def test__get_node_count_with_itemset():
    pytest.fail('Not implemented')

def test__insert_item_as_node():
    pytest.fail('Not implemented')

def test__insert_item_as_node_exception():
    pytest.fail('Not implemented')

def test__insert_itemset_as_branch_first():
    pytest.fail('Not implemented')

def test_insert_itemset_as_branch_second():
    pytest.fail('Not implemented')

def test_insert_itemset_as_branch_exception():
    pytest.fail('Not implemented')
