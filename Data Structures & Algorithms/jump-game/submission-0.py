class Solution:
    def canJump(self, nums: List[int]) -> bool:
        l = len(nums)
        dp = [False] * l
        dp[0] = True
        for i in range(l):
            for j in range(nums[i] + 1):
                nxt = i + j
                if nxt < l:
                    dp[nxt] = dp[nxt] or dp[i]
        return dp[l - 1]