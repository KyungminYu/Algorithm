class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        n = len(points)
        pq = []
        graph = defaultdict(list)
        for idx1 in range(n):
            for idx2 in range(idx1 + 1, n):
                if idx1 == idx2:
                    continue
                dist = abs(points[idx1][0] - points[idx2][0]) + abs(points[idx1][1] - points[idx2][1])
                heapq.heappush(pq, (dist, idx1, idx2))
        
        parent = list(range(n))
        
        def find(u: int) -> int:
            if parent[u] != u:
                parent[u] = find(parent[u])
            return parent[u]

        def union(u: int, v: int) -> bool:
            p1 = find(u)
            p2 = find(v)
            if p1 == p2:
                return False
            parent[p1] = p2
            return True

        count = 0
        res = 0
        while count < n - 1:
            dist, idx1, idx2 = heapq.heappop(pq)
            if union(idx1, idx2):
                res += dist
                count += 1
        return res