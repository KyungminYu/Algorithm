class Solution:
    def numberOfSubarrays(self, nums: list[int], k: int) -> int:
        n = len(nums)
        res = 0
        left = 0
        counter = 0
        prefix_count = 0
        for right in range(n):
            rnum = nums[right]
            if rnum % 2 == 1:
                counter += 1
                prefix_count = 0
            while counter == k:
                lnum = nums[left]
                if lnum % 2 == 1:
                    counter -= 1
                left += 1
                prefix_count += 1
            res += prefix_count
        return res