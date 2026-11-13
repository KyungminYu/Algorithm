class Solution:
    def minEatingSpeed(self, piles: list[int], h: int) -> int:
        l = 1
        r = max(piles)
        while l < r:
            mid = (l + r) // 2
            time = 0
            for pile in piles:
                time += pile // mid
                if pile % mid != 0:
                    time += 1
            if h < time:
                l = mid + 1
            else:
                r = mid
        return r