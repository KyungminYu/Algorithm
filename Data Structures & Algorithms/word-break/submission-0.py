class TrieNode:
    def __init__(self, val: str = ""):
        self.val = val
        self.children = {}
        self.exist = False

class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        root = TrieNode()

        def makeTrie(word: str):
            node = root
            for ch in word:
                if ch not in node.children:
                    node.children[ch] = TrieNode(ch)
                node = node.children[ch]
            node.exist = True

        for word in wordDict:
            makeTrie(word)

        cache = {}

        def solve(idx: int) -> bool:
            n = len(s)
            if idx == n:
                return True
            
            if idx in cache:
                return cache[idx]

            node = root
            for endIdx in range(idx, n):
                ch = s[endIdx]
                if ch not in node.children:
                    break
                node = node.children[ch]

                if node.exist and solve(endIdx + 1):
                    cache[endIdx] = True
                    return True
            cache[idx] = False
            return False
        return solve(0)
        