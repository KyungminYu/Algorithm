class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        n = len(nums)
        leftProd = 0
        rightProd = 0
        res = -20000000
        for i in range(n):
            leftProd = nums[i] * (leftProd or 1)
            rightProd = nums[n - i - 1] * (rightProd or 1)
            res = max(res, leftProd, rightProd)
        return res