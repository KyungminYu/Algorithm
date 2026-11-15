```
class Solution:
    def partition(self, s: str) -> list[list[str]]:
        res = []

        def isPalindrome(start:int, end: int) -> bool:
            while start <= end:
                if s[start] != s[end]:
                    return False
                start += 1
                end -= 1
            return True

        def solve(curIdx: int, candi: list):
            if curIdx == len(s):
                res.append(candi[:])
                return

            for idx in range(curIdx, len(s)):
                if isPalindrome(curIdx, idx):
                    solve(idx + 1, candi + [s[curIdx:idx + 1]])

        solve(0, [])
        return res
```

I use backtracking. 
From each starting index, I try every possible substring. 
If it is a palindrome, I add it to the current partition and continue from the next index.
This logic has O(n^2 2^n) time complexity and O(n 2^n) space complexity
