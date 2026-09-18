class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        l = len(nums)
        dp = [0] * l
        dp[0] = nums[0]
        for i in range(1, l):
            dp[i] = max(nums[i], dp[i - 1] + nums[i])
        return max(dp)