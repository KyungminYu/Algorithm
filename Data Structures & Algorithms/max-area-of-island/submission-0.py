class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        def getArea(r: int, c: int) -> int:
            if grid[r][c] != 1:
                return 0
            res = 1
            grid[r][c] = 0
            for d in dirs:
                nr = r + d[0]
                nc = c + d[1]
                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue
                res += getArea(nr, nc)
            return res

        res = 0
        for r in range(m):
            for c in range(n):
                res = max(res, getArea(r, c))

        return res