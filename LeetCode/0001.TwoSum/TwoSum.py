class Solution(object):
    def twoSum(self, nums, target):
        size = len(nums)
        for i in range(0, size-1):
            for j in range(i+1, size):
                if nums[i] + nums[j] == target:
                    return [i, j]
        return []