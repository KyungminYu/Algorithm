class Solution:
    def findMin(self, nums: List[int]) -> int:
        # PASS: LowerBound
        n = len(nums)
        l = 0
        r = n - 1
        while l < r:
            m = (l + r) // 2
            if nums[m] < nums[r]:
                r = m
            else:
                l = m + 1
        return nums[l]