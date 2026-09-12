class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        s = sum(nums)
        if s % 2 == 1:
            return False
        target = s // 2
        nums.sort()

        cache = {}

        def solve(idx: int, curSum: int) -> bool:
            if idx == len(nums):
                return curSum == target
            if (idx, curSum) in cache:
                return cache[(idx, curSum)]
            if curSum + nums[idx] == target:
                cache[(idx, curSum)] = True
                return True
            res = False
            res = res or solve(idx + 1, curSum + nums[idx])
            res = res or solve(idx + 1, curSum)
            cache[(idx, curSum)] = res
            return res
        return solve(0, 0)