class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = {}
        for n in nums:
            if n not in count:
                count[n] = 0
            count[n] += 1
        pq = []
        for key in count.keys():
            heapq.heappush(pq, [-count[key], key])

        res = []
        while k:
            res.append(heapq.heappop(pq)[1])
            k -= 1
        return res