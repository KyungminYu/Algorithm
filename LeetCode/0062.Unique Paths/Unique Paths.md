```
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [[1] * m for _ in range(n)]
        for i in range(1, n):
            for j in range(1, m):
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
        return dp[n - 1][m - 1]
```

I used dynamic programming.
Each cell's available paths come from the top and the left cells.
So, the number of paths to cell[i][j] is the sum of the number of paths to cell[i - 1][j] and cell[i][j - 1].

Therefore, I can define dp[i][j] = dp[i - 1][j] + dp[i][j - 1].
Also, as a base case, when i is 0 or j is 0, there is only one way.

By using these default values and dp recurrence relation formula, I can get the number of unique paths.

