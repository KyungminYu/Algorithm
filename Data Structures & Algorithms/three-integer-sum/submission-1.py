class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        l = len(nums)
        nums.sort()
        res = []
        i = 0
        for i in range(l - 2):
            if 0 < i and nums[i - 1] == nums[i]:
                continue
            if 0 < nums[i]:
                break
            j = i + 1
            k = l - 1
            while j < k:
                s = nums[i] + nums[j] + nums[k]
                if s == 0:
                    res.append([nums[i], nums[j], nums[k]])
                    j += 1
                    k -= 1
                    while j < k and nums[j - 1] == nums[j]:
                        j += 1
                    while j < k and nums[k] == nums[k + 1]:
                        k -= 1
                elif s < 0:
                    j += 1
                else:
                    k -= 1
        return res