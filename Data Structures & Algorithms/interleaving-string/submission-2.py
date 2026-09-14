class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        l1 = len(s1)
        l2 = len(s2)
        l3 = len(s3)
        if l1 + l2 != l3:
            return False

        dp = [[False] * (l2 + 1) for _ in range(l1 + 1)]
        dp[0][0] = True
        for i1 in range(l1 + 1):
            for i2 in range(l2 + 1):
                if i1 == 0 and i2 == 0:
                    continue
                idx1 = i1 - 1
                idx2 = i2 - 1
                idx3 = i1 + i2 - 1
                if 0 <= idx1 and s1[idx1] == s3[idx3]:
                    dp[i1][i2] = dp[i1][i2] or dp[i1 - 1][i2]
                if 0 <= idx2 and s2[idx2] == s3[idx3]:
                    dp[i1][i2] = dp[i1][i2] or dp[i1][i2 - 1]
        return dp[l1][l2]