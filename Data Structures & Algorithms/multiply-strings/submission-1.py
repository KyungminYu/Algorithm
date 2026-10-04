class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        if num1 == "0" or num2 == "0":
            return "0"
        
        l1 = len(num1)
        l2 = len(num2)

        product = 0
        for i in range(l1):
            for j in range(l2):
                product += (int(num1[l1 - i - 1]) * int(num2[l2 - j - 1])) * (10 ** (i + j))
        res = ""
        while product:
            res = str(product % 10)+ res
            product //= 10
        return res