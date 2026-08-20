class Solution:
    def islandsAndTreasure(self, grid: List[List[int]]) -> None:

        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        m = len(grid)
        n = len(grid[0])

        queue = deque()

        for r in range(m):
            for c in range(n):
                if grid[r][c] == 0:
                    queue.append([r, c])

        while queue:
            pos = queue.popleft()
            r = pos[0]
            c = pos[1]
            
            for d in dirs:
                nr = r + d[0]
                nc = c + d[1]

                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue

                if grid[nr][nc] != 2 ** 31 - 1:
                    continue

                grid[nr][nc] = grid[r][c] + 1

                queue.append([nr, nc])



