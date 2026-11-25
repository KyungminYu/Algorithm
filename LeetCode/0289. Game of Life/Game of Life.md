```
class Solution:
    def gameOfLife(self, board: list[list[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        m = len(board)
        n = len(board[0])

        dirs = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

        is_live = [[False] * n for _ in range(m)]
        live_neighbors = [[0] * n for _ in range(m)]

        def init(r: int, c: int):
            is_live[r][c] = True if board[r][c] == 1 else False
            for dr, dc in dirs:
                nr = r + dr
                nc = c + dc
                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue
                if board[nr][nc] == 1:
                    live_neighbors[r][c] += 1
        
        for r in range(m):
            for c in range(n):
                init(r, c)

        for r in range(m):
            for c in range(n):
                if is_live[r][c]:
                    if live_neighbors[r][c] < 2:
                        board[r][c] = 0
                    elif live_neighbors[r][c] <= 3:
                        board[r][c] = 1
                    else:
                        board[r][c] = 0
                else:
                    if live_neighbors[r][c] == 3:
                        board[r][c] = 1
```


I traverse all cells in the matrix to solve it.
At the first traversal, I check each cell is initially lived and count live neighborhoods.
At the second traversal, I update each cell under given conditions.
Its time complexity is O(m * n) and space complexity is also O(m * n)