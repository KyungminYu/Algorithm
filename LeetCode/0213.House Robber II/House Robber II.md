```
class Solution:
    def rob(self, nums: List[int]) -> int:
        l = len(nums)
        if l == 1:
            return nums[0]
        dp = [[0] * (l) for _ in range(2)]
        dp[0][0] = nums[0]
        dp[0][1] = max(nums[0], nums[1])
        dp[1][0] = 0 # not use 1st
        dp[1][1] = nums[1]

        for i in range(2, l - 1):
            dp[0][i] = max(dp[0][i - 1], nums[i] + dp[0][i - 2])
        for i in range(2, l):
            dp[1][i] = max(dp[1][i - 1], nums[i] + dp[1][i - 2])
        return max(dp[0][l - 2], dp[1][l - 1])
```

I used ~~_2 dimension dynamic programming._~~
two linear DP

I think key points is the fact that 0 th house and n - 1 th house is adjacency.

To handle this adjacency restriction, I divide cases to two cases.
One is using first house and not concern last house.
The other one is not concerning first house.

In each case, dp formula is dp[i] = max(dp[i - 1], dp[i - 2] + nums[i])

~~This means that stealing current house or stealing previous house.~~
**This means either skipping the current house (dp[i-1]) or robbing it (dp[i-2] + nums[i]).**


At the end of the loop, I return max(dp[0][l - 2], dp[1][l - 1])