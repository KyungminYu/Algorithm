class Solution:
    def countSubstrings(self, s: str) -> int:
        res = 0
        for idx in range(len(s)):
            left = idx
            right = idx
            while 0 <= left and right < len(s) and s[left] == s[right]:
                res += 1
                left -= 1
                right += 1

            left = idx
            right = idx + 1
            while 0 <= left and right < len(s) and s[left] == s[right]:
                res += 1
                left -= 1
                right += 1
        return res
