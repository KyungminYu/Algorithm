class Solution:
    def solve(self, board: List[List[str]]) -> None:
        
        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        m = len(board)
        n = len(board[0])

        def protect(r: int, c: int):
            if board[r][c] != 'O':
                return
            board[r][c] = 'P'
            for d in dirs:
                nr = r + d[0]
                nc = c + d[1]
                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue
                protect(nr, nc)

        for r in range(m):
            protect(r, 0)
            protect(r, n - 1)

        for c in range(n):
            protect(0, c)
            protect(m - 1, c)

        for r in range(m):
            for c in range(n):
                if board[r][c] == 'O':
                    board[r][c] = 'X'
                elif board[r][c] == 'P':
                    board[r][c] = 'O'