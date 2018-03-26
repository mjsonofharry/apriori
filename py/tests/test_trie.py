from test_common import apriori
from apriori import Trie

import sys

def test__init():
    trie = Trie()
    root = trie.mRoot
    assert root.mSupport == sys.maxsize
    assert trie.mPaths == []
