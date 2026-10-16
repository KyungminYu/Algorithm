class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        l1 = len(text1)
        l2 = len(text2)

        dp = [[0] * (l2 + 1) for _ in range(l1 + 1)]

        for idx1 in range(l1):
            for idx2 in range(l2):
                dpIdx1 = idx1 + 1
                dpIdx2 = idx2 + 1
                if text1[idx1] == text2[idx2]:
                    dp[dpIdx1][dpIdx2] = dp[dpIdx1 - 1][dpIdx2 - 1] + 1
                else:
                    dp[dpIdx1][dpIdx2] = max(dp[dpIdx1][dpIdx2 - 1], dp[dpIdx1 - 1][dpIdx2])

        return dp[l1][l2]