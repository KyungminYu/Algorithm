class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        cache = {}
        def solve(idx: int, current: int) -> int:
            if idx == len(nums):
                return 1 if current == target else 0
            if (idx, current) in cache:
                return cache[(idx, current)]
            
            res = solve(idx + 1, current + nums[idx]) + solve(idx + 1, current - nums[idx])

            cache[(idx, current)] = res
            return res
        return solve(0, 0)