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
