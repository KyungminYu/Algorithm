"""
Definition of Interval:
class Interval(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end
"""

class Solution:
    def minMeetingRooms(self, intervals: List[Interval]) -> int:
        if len(intervals) == 0:
            return 0
        intervals = sorted(intervals, key = lambda x: x.start)

        freeroom = [intervals[0].end]
        for interval in intervals[1:]:
            if freeroom[0] <= interval.start:
                heapq.heappop(freeroom)
            heapq.heappush(freeroom, interval.end)

        return len(freeroom)