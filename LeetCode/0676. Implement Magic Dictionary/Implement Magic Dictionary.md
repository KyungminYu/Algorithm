```
class TrieNode:
    def __init__(self, val: chr = None):
        self.val = val
        self.end = False
        self.children = {}

class MagicDictionary:

    def __init__(self):
        self.root = TrieNode()
    
    def buildDict(self, dictionary: list[str]) -> None:
        def make_trie(word: str):
            curr = self.root
            for ch in word:
                if ch not in curr.children:
                    curr.children[ch] = TrieNode(ch)
                curr = curr.children[ch]
            curr.end = True
        for word in dictionary:
            make_trie(word)

    def search(self, searchWord: str) -> bool:
        def search_internal(curr: TrieNode, idx: int, isChanged: bool) -> bool:
            if idx == len(searchWord):
                return curr.end and isChanged 
            ch = searchWord[idx]
            if ch in curr.children:
                if search_internal(curr.children[ch], idx + 1, isChanged):
                    return True
            
            if not isChanged:
                for child_ch in curr.children:
                    if child_ch == ch:
                        continue
                    if search_internal(curr.children[child_ch], idx + 1, True):
                        return True
            
            return False
        return search_internal(self.root, 0, False)


# Your MagicDictionary object will be instantiated and called as such:
# obj = MagicDictionary()
# obj.buildDict(dictionary)
# param_2 = obj.search(searchWord)
```

I use a Trie data structure and insert each word from the dictionary into the Trie, marking its end node.
For search, I traverse the Trie with DFS, allowing exactly one character change and returning curr.end and is_changed at the end.
Its time complexity is O(n * l) for buildDict and O(l^2) for search (n = # of words, l = avg word length), and space complexity is O(n * l).

