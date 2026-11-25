```
class Solution:
    def minFlips(self, a: int, b: int, c: int) -> int:
        res = 0
        while a or b or c:
            a_bit = a & 1
            b_bit = b & 1
            c_bit = c & 1
            a >>= 1
            b >>= 1
            c >>= 1
            if c_bit == 0:
                res += (a_bit + b_bit)
            else:
                res += 1 if a_bit == 0 and b_bit == 0 else 0
        return res
```

I will use bit manipulation to solve it.
I will try to compare each bits, if c's bit is 0, a and b's bit have to be zero. So, I add each bits summation
If c's bit is 1, I add 1 if a and b's bit is 0 representatively.