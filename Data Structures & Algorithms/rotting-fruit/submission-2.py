class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        m = len(grid)
        n = len(grid[0])
        
        q = deque()
        fresh = 0

        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    fresh += 1
                elif grid[r][c] == 2:
                    q.append((r, c))
        res = 0
        while q and fresh > 0:
            res += 1
            for _ in range(len(q)):
                r, c = q.popleft()
                for d in dirs:
                    nr = r + d[0]
                    nc = c + d[1]
                    if nr < 0 or nc < 0 or m <= nr or n <= nc:
                        continue
                    if grid[nr][nc] == 1:
                        grid[nr][nc] = 2
                        fresh -= 1
                        q.append((nr, nc))

        return res if fresh == 0 else -1
        