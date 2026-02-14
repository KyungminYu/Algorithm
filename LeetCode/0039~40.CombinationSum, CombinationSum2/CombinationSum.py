class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        valid = [False] * 41
        for candidate in candidates:
            valid[candidate] = True

        res = []
        self.solve(target, target, res, [], valid)
        return res

    def solve(self, target: int, lastUsed: int, res: List, combination: List, valid: List):
        if target == 0:
            res.append(combination[:])
            return
        for combi in range(min(target, lastUsed), 0, -1):
            if valid[combi] == False:
                continue
            combination.append(combi)
            self.solve(target - combi, combi, res, combination, valid)
            combination.pop()