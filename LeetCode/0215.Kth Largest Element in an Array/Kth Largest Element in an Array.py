class Solution:
    def findKthLargest(self, nums: list[int], k: int) -> int:
        pq = []

        for num in nums:
            heapq.heappush(pq, num)
            if len(pq) > k:
                heapq.heappop(pq)
        return pq[0]