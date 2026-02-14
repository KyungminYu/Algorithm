These two problem requires similar concept, backtracking with DFS approach.

But, requirements and restriction are different. So, we have to use slightly different methods.

#### CombinationSum
```
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
```

##### GPT revised
I solve it with backtracking. 
First, I build a boolean valid array to check in O(1) whether a value exists in candidates.
The DFS state is (target, lastUsed, combination), 
where  target is the remaining sum and lastUsed limits the next choice to be <= lastUsed. 
This keeps combinations in non-increasing order, 
so I don’t generate the same set in different orders.
If target becomes 0, I copy the current combination into the result. 
Otherwise, I iterate combi from min(target, lastUsed) down to 1, skip invalid numbers, choose it, recurse with target - combi, and backtrack.

##### My solution
At first, to solve CombinationSum, I defined valid array that it's positions from candidate are true.
It is used for the candidate is used while traversing.

Then, define solve method with target that means remained sum, lastUsed that used in previous step for narrowing next step, res that would be returned as a result, combination that contained current step's combination, and valid that checks used number.
In this method, if target is 0, it means that combination is completed. So, copy of current combination is appended to the res.
If not, I traverse all numbers that I can access with add combination element and call solve method recursively. 

At the end of the method, res array would be made completely.


#### CombinationSum2
```
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
```

#### GPT revised
I handle duplicates by counting frequencies first: 
validNum[x] stores how many times value x appears in candidates, 
so I never use a value more times than it exists.

Then I run backtracking with state (target, lastUsed, combination). 
target is the remaining sum, and lastUsed restricts the next pick to be <= lastUsed, 
keeping the combination in non-increasing order and preventing permutation duplicates.

For each combi from min(target,lastUsed) down to 1, 
I skip if its count is zero, otherwise decrement the count, 
recurse with target-combi, and then restore the count when backtracking.

#### My solution
To solve this problem, first, I counted candidates' element. 
This is because they can be duplicated and combinations' element could not exceed the number of candidate in candidates.

Then, I traversed all available cases by backtracking approach.

Like above problem, I generate res array and return it.