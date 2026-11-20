class Solution:
    def eraseOverlapIntervals(self, intervals: list[list[int]]) -> int:
        # I use greedy approach and interval sort with end to solve problem.
        # First, I sort intervals with second element that means end
        # Second, I define return result and lastEnd as 0, -1 representatively.
        # Third, if current interval's start is smaller than lastEnd, then it means overlapped. So I count up resuld count.
        # If not, I update lastEnd as current Interval's end
        # Its time complexity is O(n log n) and space complexity is O(n)
        intervals.sort(key = lambda x: x[1])
        res = 0
        lastEnd = intervals[0][1]
        print(intervals)
        for interval in intervals[1:]:
            if interval[0] < lastEnd:
                res += 1
            else:
                lastEnd = interval[1]
        return res