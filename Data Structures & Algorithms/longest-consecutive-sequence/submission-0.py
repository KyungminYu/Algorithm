class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        nums = set(nums)
        nums = list(nums)
        nums.sort()

        res = 0
        length = 0
        for idx, num in enumerate(nums):
            if idx == 0 or (0 < idx and num - 1 != nums[idx - 1]):
                length = 1
            else:
                length += 1
            res = max(res, length)

        return res