class Solution:
    def longestPalindrome(self, s: str) -> str:
        sIdx = 0
        pLen = 0

        for idx in range(len(s)):
            left = idx
            right = idx
            while 0 <= left and right < len(s) and s[left] == s[right]:
                l = (right - left + 1)
                if pLen < l:
                    pLen = l
                    sIdx = left
                
                left -= 1
                right += 1

            left = idx
            right = idx + 1
            while 0 <= left and right < len(s) and s[left] == s[right]:
                l = (right - left + 1)
                if pLen < l:
                    pLen = l
                    sIdx = left
                
                left -= 1
                right += 1

        return s[sIdx : sIdx + pLen]