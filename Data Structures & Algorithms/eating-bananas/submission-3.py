class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        low = 1
        high = max(piles)
        while low <= high:
            k = (low + high) // 2
            time = 0
            for p in piles:
                time += ((p + k - 1) // k)
            if time <= h:
                high = k - 1
            else:
                low = k + 1
        return low