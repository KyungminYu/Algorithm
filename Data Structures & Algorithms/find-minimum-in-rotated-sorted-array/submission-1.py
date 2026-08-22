class Solution:
    def findMin(self, nums: List[int]) -> int:
        # PASS: Binary Search
        n = len(nums)

        l = 0
        r = n - 1
        res = nums[0]
        while l <= r:
            if nums[l] < nums[r]:
                res = min(res, nums[l])
                break
            m = (l + r) // 2
            res = min(res, nums[m])
            if nums[l] <= nums[m]:
                l = m + 1
            else:
                r = m - 1
        return res
        