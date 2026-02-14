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