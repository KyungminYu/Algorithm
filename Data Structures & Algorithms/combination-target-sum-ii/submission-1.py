class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        res = []
        candidates.sort()

        def solve(idx: int, end: int, remain: int, candi: List[int]):
            if remain == 0:
                res.append(candi[:])
                return
            if idx >= end or remain < 0:
                return
            
            solve(idx + 1, end, remain - candidates[idx], candi + [candidates[idx]])
            while idx + 1 < end and candidates[idx] == candidates[idx + 1]:
                idx += 1
            solve(idx + 1, end, remain, candi)

        solve(0, len(candidates), target, [])

        return res