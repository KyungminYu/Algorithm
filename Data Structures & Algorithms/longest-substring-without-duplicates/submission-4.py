class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        l = len(s)
        res = 0
        sIdx = 0
        chars = set()
        for i in range(l):
            while s[i] in chars:
                chars.remove(s[sIdx])
                sIdx += 1
            chars.add(s[i])
            res = max(res, len(chars))
        return res