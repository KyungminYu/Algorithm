class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        nums = [1] + nums + [1]
        l = len(nums)
        cache = {}

        def solve(left: int, right: int) -> int:
            if right < left:
                return 0

            if (left, right) in cache:
                return cache[(left, right)]
            res = 0
            if right == left:
                res = nums[left]
                res *= nums[left - 1]
                res *= nums[right + 1]
            else:
                for idx in range(left, right + 1, 1):
                    calc = nums[idx]
                    calc *= nums[left - 1]
                    calc *= nums[right + 1]
                    calc += (solve(left, idx - 1) + solve(idx + 1, right))
                    res = max(res, calc)

            cache[(left, right)] = res
            return res

        return solve(1, l - 2)
