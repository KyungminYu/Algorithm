```
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
```

I used dynamic programming.

To solve this problem. 
I defined dp array that meant the number of ways to decode end with i th string
It is basically filled with 0. and set dp[0] and dp[1] as a 1.

For each iteration if some condition is fulfilled, dp[i - 1] and dp[i - 2] will be added.
: num1 that made by s[i - 2: i] is the value between 10 and 26.
: num2 that made by s[i - 1] is not 0.

After end of the loop, I return dp[len(s)]

This logic's time complexity is O(n) and space complexity