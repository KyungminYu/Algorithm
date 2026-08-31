class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        res = []

        def solve(idx: int, end: int, candi: List[int]):
            if idx == end:
                res.append(candi[:])
                return
            solve(idx + 1, end, candi + [nums[idx]])
            solve(idx + 1, end, candi)

        solve(0, len(nums), [])
        return res