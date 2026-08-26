class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        pq = []
        for s in stones:
            heapq.heappush(pq, -s)
        
        while len(pq) > 1:
            s1 = -heapq.heappop(pq)
            s2 = -heapq.heappop(pq)

            if s1 == s2:
                continue
            
            heapq.heappush(pq, -abs(s1 - s2))

        if len(pq) == 0:
            return 0

        return -pq[0]
        