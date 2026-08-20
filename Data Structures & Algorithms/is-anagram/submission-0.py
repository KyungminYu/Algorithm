class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        sCounts = [0] * 26
        for c in s:
            sCounts[ord(c) - ord('a')] += 1
        tCounts = [0] * 26
        for c in t:
            tCounts[ord(c) - ord('a')] += 1
        return sCounts == tCounts  