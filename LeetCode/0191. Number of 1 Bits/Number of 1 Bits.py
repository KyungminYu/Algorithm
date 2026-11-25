# I use simulation to solve it.
# Simulate extracting bits by repeatedly dividing n by 2 and checking the remainder.
# Time complexity is O(log n) because n is halved in each iteration.
# Space complexity is O(1) as only a constant amount of extra space is used.
class Solution:
    def hammingWeight(self, n: int) -> int:
        res = 0
        while n:
            res += 1 if n % 2 == 1 else 0
            n = n // 2
        return res