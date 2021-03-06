import pytest
import os, sys
parent_rpath = os.path.join(os.path.dirname(__file__), '..')
sys.path.insert(0, os.path.abspath(parent_rpath))
import apriori

def __test__do_not_run():
    assert 'New mission' is 'refuse this mission'

def test__must_always_fail():
    assert 'This sentence' is False

def test__module_exists():
    assert 'apriori' in sys.modules

def test__node_exists():
    try:
        node_class = apriori.Node
    except:
        pytest.fail('Failed to access apriori.Node')

def test__trie_exists():
    try:
        trie_class = apriori.Trie
    except AttruteError:
        pytest.fail('Failed to access apriori.Trie')
