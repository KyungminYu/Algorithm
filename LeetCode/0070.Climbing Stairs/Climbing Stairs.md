```
class Solution:
    def climbStairs(self, n: int) -> int:
        dp = [0] * (n + 1)
        dp[0] = dp[1] = 1
        for i in range(2, n + 1):
            dp[i] = dp[i - 1] + dp[i - 2]
        return dp[n]
```
### GPT revised
I used dynamic programming.

Let dp[i] be the number of ways to reach stair i.
To reach stair i, the last move must come from i-1 (take 1 step) or i-2 (take 2 steps), so dp[i] = dp[i-1] + dp[i-2].
The base cases are dp[0] = 1 and dp[1] = 1.

I compute dp from 2 to n, and return dp[n].
Time complexity is O(n) and space complexity is O(n).


### My solution

I use dynamic programming. 

The number of the ways to reach n th stair is the sum of n - 1 th case and n - 2 th case.
This is because I can step up maximum 2 stairs.

So, I defined dp recursion relation formula as dp[i] = dp[i - 1] + dp[i - 2].

By implementing this formula, I can get the number of the ways to reach n the stair.