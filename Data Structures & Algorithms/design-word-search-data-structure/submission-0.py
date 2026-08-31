class TrieNode:
    def __init__(self):
        self.children = {}
        self.endOfWord = False

class WordDictionary:

    def __init__(self):
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        cur = self.root
        for ch in word:
            if ch not in cur.children:
                cur.children[ch] = TrieNode()
            cur = cur.children[ch]
        cur.endOfWord = True

    def search(self, word: str) -> bool:
        def solve(idx: int, node: TrieNode) -> bool:
            if idx == len(word):
                return node.endOfWord

            ch = word[idx]

            if ch == ".":
                for child in node.children.values():
                    if solve(idx + 1, child):
                        return True
                return False

            if ch not in node.children:
                return False

            return solve(idx + 1, node.children[ch])
        return solve(0, self.root)
        
