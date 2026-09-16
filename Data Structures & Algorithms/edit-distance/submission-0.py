class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        l1 = len(word1)
        l2 = len(word2) 

        dp = [[0] * (l2 + 1) for _ in range(l1 + 1)]
        
        for idx1 in range(1, l1 + 1):
            dp[idx1][0] = dp[idx1 - 1][0] + 1
        for idx2 in range(1, l2 + 1):
            dp[0][idx2] = dp[0][idx2 - 1] + 1


        for idx1 in range(1, l1 + 1):
            for idx2 in range(1, l2 + 1):
                if word1[idx1 - 1] == word2[idx2 - 1]:
                    dp[idx1][idx2] = min(dp[idx1 - 1][idx2 - 1], dp[idx1 - 1][idx2] + 1, dp[idx1][idx2 - 1] + 1)
                else:
                    dp[idx1][idx2] = min(dp[idx1 - 1][idx2 - 1], dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]) + 1

        return dp[l1][l2]