# 2026.11.19
class Solution:
    def merge(self, intervals: list[list[int]]) -> list[list[int]]:
        # I use greedy approach to solve it.
        # First, I sort intervals and traverse it
        # Second, if result array is empty or last result's end is smaller than current interval's start, then I append current interval to result array. If not, I modify last result's end to current interval's end
        # Its time complexity is O(n log n) and space complexity is O(n)

        intervals.sort()
        res = []
        for interval in intervals:
            if not res or res[-1][1] < interval[0]:
                res.append(interval)
            else:
                res[-1][1] = max(res[-1][1], interval[1])
        return res


class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort()
        res = []
        s = intervals[0][0]
        e = intervals[0][1]
        for idx in range(1, len(intervals)):
            interval = intervals[idx]
            if e < interval[0]:
                res.append([s, e])
                s = interval[0]
                e = interval[1]
            elif e < interval[1]:
                e = interval[1]
        res.append([s, e])
        return res
