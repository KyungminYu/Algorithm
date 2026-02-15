```
class Solution:
    def canJump(self, nums: List[int]) -> bool:
        reachable_end = 0
        for pos, jump in enumerate(nums):
            if reachable_end < pos:
                return False
            reachable_end = max(reachable_end, pos + jump)
        return True
```

### GPT revised
I use a greedy approach.
I keep reachable_end, the farthest index I can reach so far.

I scan the array from left to right. 
If I ever encounter an index pos that is greater than reachable_end, 
it means I can’t reach this position, so I return False.

Otherwise, I update reachable_end = max(reachable_end, pos + jump) to extend the farthest reachable index.
If I finish the loop without getting stuck, I return True.

### My solution
To solve this problem, I used greedy approach.
At first, I defined reachable_end. It is the position that is currently reachable by using any way.
In the loop, I checked the reachable_end and pos variable to validate current position is reachable.
If reachable_end is smaller than pos, I returned False,
If not, I updated reachable_end to max(reachable_end, pos + jump)
If loop is finished without return False, I return True
