```
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        length = len(nums)
        res = []
        visited = [False] * length
        self.solve(nums, res, [], visited, length)
        return res
    
    def solve(self, nums:List, res:List, permutation:List, visited:List, remains: int):
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
```


#### GPT revised
I generate all permutations using backtracking.
I keep a visited array to ensure each number is used at most once in the current path, and a permutation list as the current path.

When permutation reaches length n, I copy it into res, 
Otherwise, I try every unused index, mark it visited, recurse, then undo the choice.

This run in O(n * n!) times and uses O(n) auxiliary space, excluding the output.

#### My answer
To find permutations, I traversed all nums elements by using dfs. 
At the solve method, I sent nums, res, permutation, visited, remains parameters.
nums is source data, res is the reference of the result list, permutation is a list that contains current permutation data. visited is a list that check the nums's each element is already used. 
Finally, remains is a count of remained item that would be used for permutation.

Then, I append permutations to the res list if remains is 0.
if not, traversing all nums that is not visited yet with push each nums[idx] to the permutation value.