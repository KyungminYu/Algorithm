# I will use a Trie data structure with DFS to support '.' wildcards.
# First, for addWord, I insert characters into the Trie
# and mark the last node as end = True.
# Second, for search, I will traverse via DFS.
# For '.', check all children. and For normal chars, I follow the matching child.
# and I will return node.end at the end of the word.

# Its time complexity is addWord O(L), search O(L) without '.' or O(26^L) worst-case with '.' and space complexity is O(N * L) for the Trie, O(L) for the recursion stack

class TrieNode:

    def __init__(self, val: chr = None):
        self.val = val
        self.end = False
        self.children = {}


class WordDictionary:

    def __init__(self):
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        curr = self.root
        for ch in word:
            if ch not in curr.children:
                curr.children[ch] = TrieNode(ch)
            curr = curr.children[ch]
        curr.end = True

    def search(self, word: str) -> bool:

        def search_internal(node: TrieNode, idx: int) -> bool:
            if idx == len(word):
                return node.end

            ch = word[idx]
            if ch == ".":
                for child in node.children.values():
                    if search_internal(child, idx + 1):
                        return True
                return False

            if ch not in node.children:
                return False
            return search_internal(node.children[ch], idx + 1)

        return search_internal(self.root, 0)

# Your WordDictionary object will be instantiated and called as such:
# obj = WordDictionary()
# obj.addWord(word)
# param_2 = obj.search(word)