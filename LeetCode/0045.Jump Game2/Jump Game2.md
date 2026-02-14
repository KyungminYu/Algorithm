```
class Solution:
    def jump(self, nums: List[int]) -> int:
        length = len(nums)
        res = 0
        current_end = 0
        reached_end = 0
        for pos in range(length - 1):
            reached_end = max(reached_end, pos + nums[pos])

            if pos == current_end:
                res += 1
                current_end = reached_end
        return res
```

To solve this problem, I used a greedy approach that scans the array level by level .

current_end is the farthest index we can reach using res jumps(the end ot the current range)
reached_end is the farthest index we can reach while scanning positions within the current range.

For each position pos, I update:
reached_end = max(reached_end, pos + nums[pos])

When pos reaches current_end, it means we have finished exploring all positions reachable with the current number of jumps, so we must take one more jump

To jump one more, I increase res and set current_end as a reached_end, it represents I move to the next range.

This gives the minimum number of jumps in O(n) time and O(1) space.