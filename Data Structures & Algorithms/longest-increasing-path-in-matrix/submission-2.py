class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        m = len(matrix)
        n = len(matrix[0])
        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        self.res = 0
        memo = {}
        def solve(r: int, c: int):
            if (r, c) in memo:
                return memo[(r, c)]
            longest = 1
            for dr, dc in dirs:
                nr = r + dr
                nc = c + dc
                if nr < 0 or nc < 0 or m <= nr or n <= nc:
                    continue
                if matrix[r][c] >= matrix[nr][nc]:
                    continue
                longest = max(longest, 1 + solve(nr, nc))
            memo[(r, c)] = longest
            return longest
        res = 1
        for r in range(m):
            for c in range(n):
                res = max(res, solve(r, c))
        return res