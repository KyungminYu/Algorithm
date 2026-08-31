class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        m = len(heights)
        n = len(heights[0])
        
        pacific = set()
        atlantic = set()

        def traverse(r: int, c: int, visited: set):
            visited.add((r, c))
            for d in dirs:
                nr = r + d[0]
                nc = c + d[1]
                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue
                if (nr, nc) not in visited and heights[r][c] <= heights[nr][nc]:
                    traverse(nr, nc, visited)

        for row in range(m):
            traverse(row, 0, pacific)
            traverse(row, n - 1, atlantic)

        for col in range(n):
            traverse(0, col, pacific)
            traverse(m - 1, col, atlantic)

        res = []

        for row in range(m):
            for col in range(n):
                if (row, col) in pacific and (row, col) in atlantic:
                    res.append([row, col])

        return res
                