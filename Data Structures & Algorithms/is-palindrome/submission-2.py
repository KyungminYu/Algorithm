class Solution:
    def isPalindrome(self, s: str) -> bool:
        s = s.lower()
        l = len(s)
        left = 0
        right = l - 1

        def isValid(c: str) -> bool:
            val = ord(c)
            return ord('a') <= val <= ord('z') or ord('0') <= val <= ord('9')

        while left < right:
            while left < l and not isValid(s[left]):
                left += 1
            while 0 <= right and not isValid(s[right]):
                right -= 1
            if right <= left:
                break
            if s[left] != s[right]:
                return False
            left += 1
            right -= 1
        return True