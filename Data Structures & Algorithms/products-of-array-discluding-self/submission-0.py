class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        product = 1
        zeroCnt = 0
        for num in nums:
            if num == 0:
                zeroCnt += 1
            else:
                product *= num
        res = []

        for num in nums:
            if num == 0:
                if zeroCnt > 1:
                    res.append(0)
                else:
                    res.append(product)
            else:
                if zeroCnt > 0:
                    res.append(0)
                else:
                    res.append(product // num)
        return res