class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        res = []

        def solve(mask: int, candi: List):
            if len(candi) == len(nums):
                res.append(candi[:])
                return
            
            for idx in range(0, len(nums)):
                if (mask & (1 << idx)):
                    continue
                solve(mask | (1 << idx), candi + [nums[idx]])

        solve(0, [])

        return res