class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        
        res = [nums[0]]
        for idx in range(1, len(nums)):
            if res[-1] < nums[idx]:
                res.append(nums[idx])
                continue
            if res[-1] == nums[idx]:
                continue
            l = 0
            r = len(res) - 1
            while l <= r:
                m = (l + r) // 2
                if res[m] < nums[idx]:
                    l = m + 1
                else:
                    r = m - 1
            res[l] = nums[idx]
        return len(res)

        