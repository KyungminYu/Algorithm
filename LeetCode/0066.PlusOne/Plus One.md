```
class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        l = len(digits)
        carry = 0
        digits[l - 1] += 1
        for i in range(l - 1, -1, -1):
            sum = digits[i] + carry
            digits[i] = sum % 10
            carry = sum // 10
        if carry > 0:
            digits = [carry] + digits
        return digits
```

I used a basic addition with a carry.

First, I incremented last digit and iterated from right to left.
In each iteration, I added digits[i] and carry, 
and calculate digits[i] and carry to carry into the next digit.
Finally, I added remaining carry to the front of the array.
