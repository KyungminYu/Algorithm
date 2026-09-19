class Solution:
    def jump(self, nums: List[int]) -> int:
        l = len(nums)
        res = 0
        end = 0
        farthest = 0
        for idx in range(l - 1):
            farthest = max(farthest, idx + nums[idx])
            if idx == end:
                res += 1
                end = farthest
        return res