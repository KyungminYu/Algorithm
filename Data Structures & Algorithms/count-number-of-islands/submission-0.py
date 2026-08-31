class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        m = len(grid)
        n = len(grid[0])
        def traverse(r: int, c: int):
            grid[r][c] = "0"
            
            for d in dirs:
                nr = r + d[0]
                nc = c + d[1]
                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue
                if grid[nr][nc] == "1":
                    traverse(nr, nc)

        res = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == "1":
                    traverse(r, c)
                    res += 1
        return res