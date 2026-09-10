class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        dp = [int(1e9)] * (amount + 1)
        dp[0] = 0
        for a in range(1, amount + 1):
            for c in coins:
                if c <= a:
                    dp[a] = min(dp[a], dp[a - c] + 1)
        return dp[amount] if dp[amount] != int(1e9) else -1