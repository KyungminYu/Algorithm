class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        length = len(nums)
        current_max = nums[0]
        res = nums[0]
        for i in range(1, length):
            current_max = max(current_max + nums[i], nums[i])
            res = max(res, current_max)
        return res