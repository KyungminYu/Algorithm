class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        pq = []
        res = []

        for idx, num in enumerate(nums):
            heapq.heappush(pq, [-num, idx])
            if k - 1 <= idx:
                while pq[0][1] <= idx - k:
                    heapq.heappop(pq)
                res.append(-pq[0][0])

        return res