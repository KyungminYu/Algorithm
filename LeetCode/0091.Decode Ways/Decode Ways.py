class Solution:
    def numDecodings(self, s: str) -> int:
        l = len(s)
        if l == 0 or s[0] == '0':
            return 0

        dp = [0] * (l + 1)
        dp[0] = 1
        dp[1] = 1
        for i in range(2, l + 1):
            num1 = int(s[i - 2:i])
            num2 = int(s[i - 1])
            if 10 <= num1 <= 26:
                dp[i] += dp[i - 2]
            if 0 != num2:
                dp[i] += dp[i - 1]

        return dp[l]