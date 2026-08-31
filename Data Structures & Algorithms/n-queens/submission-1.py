class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        res = []
        board = [["."] * n for i in range(n)]
        visited = [set(), set(), set()]

        def solve(row: int):
            if row == n:
                copied = []
                for boardRow in board:
                    copied.append("".join(boardRow))
                if len(copied) > 0:
                    res.append(copied)
                return

            for col in range(n):
                if col in visited[0] or (row + col) in visited[1] or (row - col) in visited[2]:
                    continue
                visited[0].add(col)
                visited[1].add(row + col)
                visited[2].add(row - col)
                board[row][col] = 'Q'
                solve(row + 1)
                visited[0].discard(col)
                visited[1].discard(row + col)
                visited[2].discard(row - col)
                board[row][col] = '.'

        solve(0)
        return res