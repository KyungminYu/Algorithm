```
class Solution:
    def rob(self, nums: list[int]) -> int:
        n = len(nums)
        dp = [0] * (n + 1)
        dp[1] = nums[0]
        for i in range(2, n + 1):
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1])
        return dp[n]
```

I use dynamic programming.
and I apply a recurrence formula as a dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]), and base case is dp[0] = 0, dp[1] = nums[0]
Its time complexity is O(n) and space complexity is O(n)