class TrieNode:
    def __init__(self):
        self.children = {}
        self.word = None

class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:

        root = TrieNode()

        for word in words:
            node = root

            for ch in word:
                if ch not in node.children:
                    node.children[ch] = TrieNode()
                node = node.children[ch]
            node.word = word
        
        
        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        m = len(board)
        n = len(board[0])
        res = []

        def search(node: TrieNode, r: int, c: int):
            ch = board[r][c]
            if ch not in node.children:
                return

            next_node = node.children[ch]

            if next_node.word is not None:
                res.append(next_node.word)
                next_node.word = None

            board[r][c] = "."

            for d in dirs:
                nr = r + d[0]
                nc = c + d[1]
                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue
                if board[nr][nc] == '.':
                    continue
                search(next_node, nr, nc)

            board[r][c] = ch

        for r in range(m):
            for c in range(n):
                search(root, r, c)
        return res

        