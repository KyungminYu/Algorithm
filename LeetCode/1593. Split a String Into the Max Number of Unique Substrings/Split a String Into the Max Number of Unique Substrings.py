class Solution:
    def maxUniqueSplit(self, s: str) -> int:
        # I use backtracking to solve it,
        # First, I define substring_set for contain current substrings
        # Second, I define solve method with parameter idx
        # Third, if curIdx is length of s, I will return substring_set's length
        # Forth, if not, I check all available substrings and if it is not contained in the current set, I will add and traverse recursively, also, discard it after traverse. Finally, I return max value among  each cases's results
        # Its time complexity is O(n 2^n) and space complexity is O(n)
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
