```
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
```

I use binary search to find the minimum valid eating speed. 
For each mid, I calculate the total required hours. 
If it takes more than h hours, the speed is too slow, so I search the larger half. 
Otherwise, I keep mid as a possible answer and search for a smaller speed. 
The time complexity is O(n log m), where m is the maximum pile size.
