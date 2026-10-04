class Solution:

    def myPow(self, x: float, n: int) -> float:
        cache = {}

        def solve(x: float, n: int) -> float:
            if n == 1:
                return x
            elif n == 0:
                return 1
            elif (x, n) in cache:
                return cache[(x, n)]  
            half = solve(x, n // 2)
            res = half * half
            if n % 2 != 0:
                res *= x
            cache[(x, n)] = res
            return res
        if n < 0:
            return 1 / solve(x, -n)
        return solve(x, n) 