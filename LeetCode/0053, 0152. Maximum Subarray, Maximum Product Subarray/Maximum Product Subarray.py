class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        length = len(nums)
        current_min = nums[0]
        current_max = nums[0]
        res = nums[0]
        for i in range(1, length):
            if nums[i] < 0:
                current_min, current_max = current_max, current_min
            current_max = max(nums[i], current_max * nums[i])
            current_min = min(nums[i], current_min * nums[i])
            res = max(res, current_max)
        return res