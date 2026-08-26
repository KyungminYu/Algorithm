class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        def getDist(p: List[int]) -> int:
            return p[0] ** 2 + p[1] ** 2

        pq = []
        for p in points:
            heapq.heappush(pq, (getDist(p), p))

        res = []

        while k > 0:
            dist, p = heapq.heappop(pq)
            k -= 1
            res.append(p)

        return res
        