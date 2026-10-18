class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        # To solve this problem, I will use DP algorithm.
        # First, define DP recurrence relation as dp[amount] += dp[amount - coin], subject to dp[0] = 1
        # Second, traverse all cases that represents combination of amount and len(coins).
        # Finally, return dp[amount]

        dp = [0] * (amount + 1)
        dp[0] = 1
        for coin in coins:
            for a in range(amount + 1):
                if a < coin:
                    continue
                dp[a] += dp[a - coin]
        return dp[amount] 