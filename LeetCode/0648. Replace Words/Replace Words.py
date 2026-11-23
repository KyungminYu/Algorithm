# I use trie data structure and put each word from dictionary into the Trie and mark its end node.
# And then, for search_prefix, I traverse the trie character by character for each word in sentence
# Its time complexity is O(d, # of dictionary, * l, avg length of words, + s, length of sentence), and space complexity is O(d * l)

class TrieNode:
    def __init__(self, val: chr = None):
        self.val = val
        self.end = False
        self.children = {}


class Solution:
    def replaceWords(self, dictionary: list[str], sentence: str) -> str:
        root = TrieNode()

        def make_trie(node: TrieNode, word: str, idx: int):
            if idx == len(word):
                node.end = True
                return
            ch = word[idx]
            if ch not in node.children:
                node.children[ch] = TrieNode(ch)
            make_trie(node.children[ch], word, idx + 1)

        for word in dictionary:
            make_trie(root, word, 0)

        def search_prefix(node: TrieNode, word: str, idx: int):
            if idx == len(word):
                if node.end:
                    return word
                return ""
            if node.end:
                return word[:idx]
            ch = word[idx]
            if ch not in node.children:
                return ""
            return search_prefix(node.children[ch], word, idx + 1)

        res = []
        tokens = sentence.split(" ")
        prefix = search_prefix(root, tokens[0], 0)
        res.append(prefix if len(prefix) > 0 else tokens[0])
        for token in tokens[1:]:
            res.append(" ")
            prefix = search_prefix(root, token, 0)
            res.append(prefix if len(prefix) > 0 else token)

        return "".join(res)