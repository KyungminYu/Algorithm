class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        validNum = [0] * 101
        for candidate in candidates:
            validNum[candidate] += 1
        res = []
        self.solve(target, target, res, [], validNum)
        return res

    def solve(self, target: int, lastUsed: int, res: List, combination: List, validNum: List):
        if target == 0:
            res.append(combination[:])
            return
        for combi in range(min(target, lastUsed), 0, -1):
            if validNum[combi] <= 0:
                continue
            validNum[combi] -= 1
            combination.append(combi)
            self.solve(target - combi, combi, res, combination, validNum)
            validNum[combi] += 1
            combination.pop()

    # I use backtracking.
    # Starting from start, I add each valid candidate and recursively search with the reduced target.
    # I reuse the same index because each candidate can be selected multiple times.
    # The time complexity is exponential, and the recursion depth is O(target / min(candidates)).

    # def solve(self, curIdx: int, remain: int, candi: list):
    #     if remain == 0:
    #         res.append(candi[:])
    #         return
    #     for idx in range(curIdx, len(candidates)):
    #         val = candidates[idx]
    #         if remain - val < 0:
    #             continue
    #         self.solve(idx, remain - val, candi + [val])