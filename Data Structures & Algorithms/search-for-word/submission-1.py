class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        m = len(board)
        n = len(board[0])

        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]

        def search(r: int, c:int, idx: int) -> bool:
            if board[r][c] != word[idx]:
                return False
            if idx == len(word) - 1:
                return True

            tmp = board[r][c]
            board[r][c] = "_"
            res = False
            for d in dirs:
                nr = r + d[0]
                nc = c + d[1]
                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue
                if search(nr, nc, idx + 1):
                    res = True
            board[r][c] = tmp
            return res

        for r in range(m):
            for c in range(n):
                if search(r, c, 0):
                    return True


        return False
        