```
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
```
### GPT revised

To solve this problem, 

I sort the intervals by start time and then greedily merge them in a single pass.

During the traversal, I keep the current merged range [s, e].
If the next interval starts after e, 
there is no overlap, 
so I append [s, e] to the result and reset [s, e] to the next interval.

Otherwise, the intervals overlap, 
so I extend e to max(e, next_end).

After the loop, I append the final [s, e].

### My solution
To solve this problem,

I sort intervals by start, then traverse it to merge greedily.
During traverse, I track the current merged range [s, e].
If the next interval start after e, there is no overlap,
So, I append [s, e] to res array and reset [s, e] as current interval.
Otherwise, I can assume that [s, e] and interval overlapped. 
Under this assumption, if e is smaller that interval end, e can be updated to current interval's end.

After end of traverse, I appended remained [s, e] as a last range.

