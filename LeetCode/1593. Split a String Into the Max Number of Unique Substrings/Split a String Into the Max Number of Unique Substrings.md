```
class Solution:
    def maxUniqueSplit(self, s: str) -> int:
        substring_set = set()
        def solve(curIdx: int) -> int: 
            if curIdx == len(s):
                return len(substring_set)
            res = 0
            for idx in range(curIdx, len(s)):
                substring = s[curIdx: idx + 1]
                if substring in substring_set:
                    continue
                substring_set.add(substring)
                res = max(res, solve(idx + 1))
                substring_set.remove(substring)
            return res
        
        return solve(0)
        
```

I use backtracking.
First, I create a set to store the substrings in the current partition.
Starting at curIdx, I try every possible substring.
If a substring is not already used, I add it to the set and continue recursively.
After the recursive call, I remove it to explore other partitions.
When curIdx reaches the end of the string, I return the number of unique substrings.

Its time complexity is O(n 2^n) and space complexity is O(n)      