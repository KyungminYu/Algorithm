```
class Solution:
    def coinChange(self, coins: list[int], amount: int) -> int:
        inf = amount + 1
        dp = [inf] * (amount + 1)
        dp[0] = 0
        for amt in range(1, amount + 1):
            for coin in coins:
                if amt - coin < 0:
                    continue
                dp[amt] = min(dp[amt], dp[amt - coin] + 1)
        return -1 if dp[amount] == inf else dp[amount]
```

I use dynamic programing
and I define a recurrence formula as dp[amount] = min(dp[amount], dp[amount - each coin] + 1), its base case is init dp array as an infinite and set dp[0] as 0
Also return -1 if dp[amount] is still inf, it means that I can not reach out that amount.
its time complexity is O(len(amount) * len(coins)), and space complexity is O(len(amount))