```
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        length = len(nums)
        current_max = nums[0]
        res = nums[0]
        for i in range(1, length):
            current_max = max(current_max + nums[i], nums[i])
            res = max(res, current_max)
        return res
```

```
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        dp_max = [0] * n
        dp_max[0] = nums[0]
        res = nums[0]

        for i in range(1, n):
            x = nums[i]
            dp_max[i] = max(x, x + dp_max[i - 1])
            res = max(res, dp_max[i])
        return res
```

I used dynamic programing. 
I tracked current_max that is the maximum subarray's sum ending at index i.
At each element, I decided whether it is better to extend previous subarray(current_max + nums[i]) or start a new subarray(nums[i]).
Then I updated res with the best current_max seen so far.
This runs in O(n) time and O(1) space.