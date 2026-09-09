class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        n = len(grid)
        dirs = [[0, 1], [0, -1], [1, 0], [-1, 0]]

        pq = []
        heapq.heappush(pq, (grid[0][0], 0, 0))
        grid[0][0] = -1

        t = 0

        while pq:
            time, r, c = heapq.heappop(pq)
            t = max(t, time)
            if r == n - 1 and c == n - 1:
                return t
            for d in dirs:
                nr = r + d[0]
                nc = c + d[1]
                
                if nr < 0 or nc < 0 or n <= nr or n <= nc or grid[nr][nc] < 0:
                    continue
                heapq.heappush(pq, (grid[nr][nc], nr, nc))
                grid[nr][nc] = -1
                

        return 0