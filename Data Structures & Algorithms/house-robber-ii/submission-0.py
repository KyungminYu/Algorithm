class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        if n < 2:
            return nums[0]
        elif n == 2:
            return max(nums[0], nums[1])
        dp = [[0] * n for _ in range(2)]
        dp[0][0] = nums[0]
        dp[0][1] = max(dp[0][0], nums[1])
        for i in range(2, n - 1):
            dp[0][i] = max(dp[0][i - 1], dp[0][i - 2] + nums[i])

        dp[1][0] = 0
        dp[1][1] = max(dp[1][0], nums[1])
        for i in range(2, n):
            dp[1][i] = max(dp[1][i - 1], dp[1][i - 2] + nums[i])
        print(dp)
        return max(dp[0][n - 2], dp[1][n - 1])