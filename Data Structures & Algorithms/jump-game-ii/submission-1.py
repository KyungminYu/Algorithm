class Solution:
    def jump(self, nums: List[int]) -> int:
        l = len(nums)
        dp = [int(1e9)] * l
        dp[0] = 0
        for idx in range(l):
            eIdx = min(l - 1, idx + nums[idx])
            for rIdx in range(idx + 1, eIdx + 1):
                dp[rIdx] = min(dp[rIdx], dp[idx] + 1)
        return dp[l - 1]