class Solution:
    def combinationSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        res = []

        def solve(idx: int, end: int, remain: int, candi: List[int]):
            if remain == 0:
                res.append(candi[:])
                return
            if idx >= end or remain < 0:
                return
            
            solve(idx, end, remain - nums[idx], candi + [nums[idx]])
            solve(idx + 1, end, remain, candi)

        solve(0, len(nums), target, [])

        return list(res)