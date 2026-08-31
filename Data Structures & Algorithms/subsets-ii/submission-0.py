class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        nums.sort()

        res = []

        def solve(idx: int, candi: List):
            if idx == len(nums):
                res.append(candi[:])
                return
            
            solve(idx + 1, candi + [nums[idx]])
            while idx + 1 < len(nums) and nums[idx] == nums[idx + 1]:
                idx += 1
            solve(idx + 1, candi)


        solve(0, [])

        return res