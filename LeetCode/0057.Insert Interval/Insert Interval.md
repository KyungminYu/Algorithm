```
class Solution:
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        length = len(intervals)
        idx = 0
        res = []
        while idx < length and intervals[idx][1] < newInterval[0]:
            res.append(intervals[idx])
            idx += 1

        while idx < length and intervals[idx][0] <= newInterval[1]:
            newInterval[0] = min(newInterval[0], intervals[idx][0])
            newInterval[1] = max(newInterval[1], intervals[idx][1])
            idx += 1
        res.append(newInterval)

        while idx < length:
            res.append(intervals[idx])
            idx += 1
        return res
```

### GPT revise

I solve it with a single linear scan.

I maintain a pointer and build the answer in three phases:
Add all intervals that end before newInterval starts (no overlap).
While intervals overlap newInterval, merge them by expanding newInterval with
start = min(start, interval.start) and end = max(end, interval.end).
Append the merged newInterval, then append the remaining intervals.

This runs in O(n) time and uses O(n) extra space for the output.


### My solution

To solve this problem, 
I used simulation approach. 

While I insert newInterval, I will face 3 different cases.
First, current interval's end is smaller than newInterval's start.
Second, newInterval overlaps some intervals.
Lastly, newInterval's end is smaller than current interval's start.

I also represent second case differently.
This case means that current interval's start is smaller than newInterval's end.
At this time, newInterval can merge current interval to itself.

Change this description to codes, I can represent like this.

This logic's time complexity is O(n) and space complexity is O(n).