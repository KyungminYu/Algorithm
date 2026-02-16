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
