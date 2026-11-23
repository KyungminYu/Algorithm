# I will use a Trie (prefix tree) data structure to solve this problem.
# Each TrieNode has two attributes: 'children' (a dictionary mapping characters to child nodes)
# and 'end' (a boolean indicating whether a complete word ends at the current node).

# First, I initialize an empty root node in the __init__ method.
# Second, for the insert method, I iterate through each character in the word.
# If the character is not in curr.children, I create a new TrieNode and add it to the dictionary.
# Once all characters are processed, I mark curr.end as True.
# Third, search and startsWith share the same traversal logic, differing only in what they return:
# search returns curr.end to ensure an exact match, whereas startsWith returns True as long as the prefix path exists.

# Time Complexity: O(L) for insert, search, and startsWith, where L is the length of the word or prefix.
# Space Complexity: O(N * L) in the worst case, where N is the number of words and L is their average length.

class TrieNode:
    def __init__(self, val: chr = None):
        self.val = val
        self.end = False
        self.children = {}


class Trie:

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        curr = self.root
        for ch in word:
            if ch not in curr.children:
                curr.children[ch] = TrieNode(ch)
            curr = curr.children[ch]
        curr.end = True

    def search(self, word: str) -> bool:
        curr = self.root
        for ch in word:
            if ch not in curr.children:
                return False
            curr = curr.children[ch]
        return curr.end

    def startsWith(self, prefix: str) -> bool:
        curr = self.root
        for ch in prefix:
            if ch not in curr.children:
                return False
            curr = curr.children[ch]
        return True

# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)