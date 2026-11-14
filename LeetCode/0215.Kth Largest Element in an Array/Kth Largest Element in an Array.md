```
class Solution:
    def findKthLargest(self, nums: list[int], k: int) -> int:
        pq = []

        for num in nums:
            heapq.heappush(pq, num)
            if len(pq) > k:
                heapq.heappop(pq)
        return pq[0]
```

I use min heap to solve this problem.
By keeping length of pq as under k, 
I can find k th largest value on the min heap's first value.

This logic's time complexity is O(n log k), and space complexity is O(log k)
        