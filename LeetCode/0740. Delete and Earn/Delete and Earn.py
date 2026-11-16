class Solution:
    def deleteAndEarn(self, nums: list[int]) -> int:
        # I use dynamic programming,
        # and I define a recurrence formula as dp[i] = max(dp[i - 1], dp[i - 2] + points[i])
        # points means that the amount of points I can earn by selecting each num
        # Its time complexity is O(n) and space complexity is O(n) 
        max_val = max(nums)
        points = [0] * (max_val + 1)

        for num in nums:
            points[num] += num

        dp = [0] * (max_val + 1)
        dp[1] = points[1]

        for i in range(2, max_val + 1):
            dp[i] = max(dp[i - 1], dp[i - 2] + points[i])
        return dp[max_val]