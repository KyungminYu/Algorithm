class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = [0] * 2001
        for num in nums:
            count[num + 1000] += 1
        
        pq = []

        for idx, c in enumerate(count):
            heapq.heappush(pq, [-c, idx - 1000])

        res = []
        while k > 0:
            res.append(heapq.heappop(pq)[1])
            k -= 1

        return res