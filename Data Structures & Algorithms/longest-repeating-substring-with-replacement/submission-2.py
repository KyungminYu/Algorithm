class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        # TLE O(n ^ 2)
        l = len(s)
        res = 1
        for i in range(l):
            count = {}
            targetCharNum = 0
            for j in range(i, l):
                count[s[j]] = count.get(s[j], 0) + 1
                targetCharNum = max(targetCharNum, count[s[j]])
                if (j - i + 1) - targetCharNum <= k:
                    res = max(res, j - i + 1)
        return res