class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        len1 = len(word1)
        len2 = len(word2)

        dp = [[0] * (len1 + 1) for _ in range(len2 + 1)]

        for i in range(1, len2 + 1):
            dp[i][0] = dp[i - 1][0] + 1
        for i in range(1, len1 + 1):
            dp[0][i] = dp[0][i - 1] + 1

        for i in range(1, len2 + 1):
            for j in range(1, len1 + 1):
                if word2[i - 1] == word1[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1
        return dp[len2][len1]
