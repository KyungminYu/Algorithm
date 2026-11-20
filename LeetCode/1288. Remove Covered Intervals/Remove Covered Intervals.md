```
class Solution:
    def removeCoveredIntervals(self, intervals: list[list[int]]) -> int:
        intervals.sort(key = lambda x: (x[0], -x[1]))
        remain_count = len(intervals)
        max_end = 0
        for interval in intervals:
            if interval[1] <= max_end:
                remain_count -= 1
            max_end = max(max_end, interval[1])
        return remain_count

```

I use greedy approach to solve it
First, I sort intervals, with (x[0], -x[1]). it means that I sort it as ascending order for first element and if first elements are same, I compare second elements as descending order.
Second, I define remain_count and max_end values for our logic.
Third, I traverse all elements, and if current interval's end is smaller than current max_end, then I count down remain count. Because it means fully covered state.
Its time complexity is O(n log n) and space complexity is O(1)