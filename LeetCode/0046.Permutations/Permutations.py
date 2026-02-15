class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        length = len(nums)
        res = []
        visited = [False] * length
        self.solve(nums, res, [], visited, length)
        return res

    def solve(self, nums: List, res: List, permutation: List, visited: List, remains: int):
        if remains == 0:
            res.append(permutation[:])
            return

        for idx in range(len(nums)):
            if visited[idx]:
                continue
            visited[idx] = True
            permutation.append(nums[idx])
            self.solve(nums, res, permutation, visited, remains - 1)
            visited[idx] = False
            permutation.pop()
