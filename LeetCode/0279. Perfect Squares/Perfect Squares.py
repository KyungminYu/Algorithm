class Solution:
    def numSquares(self, n: int) -> int:
        # I use dynamic programming,
        # and I define a recurrence formula as dp[i] = min(dp[i], dp[i - each square under i] + 1)
        # Its time complexity is O(n n ^ 0.5) and space complexity is O(n)
        inf = int(1e9)
        dp = [inf] * (n + 1)
        dp[0] = 0
        sqs = [i * i for i in range(int(n ** 0.5) + 1)]
        for i in range(1, n + 1):
            for sq in sqs:
                if i < sq:
                    break
                dp[i] = min(dp[i], dp[i - sq] + 1)
        return dp[n]