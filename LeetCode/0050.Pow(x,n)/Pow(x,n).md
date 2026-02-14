```
class Solution:
    def myPow(self, x: float, n: int) -> float:
        if n < 0:
            x = 1 / x
            n = -n
        return self.solve(x, n)

    def solve(self, x : float, n : int) -> float:
        if n == 0:
            return 1.0
        half = self.solve(x, n // 2)
        if n % 2 == 0:
            return half * half
        return half * half * x
```

#### GPT revised
I used exponentiation by squaring with divide and conquer.
If n is negative, I convert it to a positive exponent by setting x = 1/x and n = -n.

Then I **recursively** compute half = x^(n//2). 
If n is even, the answer is half * half; if it’s odd, it’s half * half * x.
This reduces the exponent by half each step, 
so the time complexity is O(log n) with O(log n) recursion depth.

#### MY solution
To resolve this problem, I used divide and conquer approach.

If I multiply all x sequentially, I might be TLE.

So, I calculate half of the result previously, and multiply itself and if n is odd multiply x one more time.

In this way, I can solve this problem under O(log n) time.