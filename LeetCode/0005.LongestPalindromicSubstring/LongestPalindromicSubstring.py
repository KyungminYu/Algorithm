class Solution1:
    def longestPalindrome(self, s: str) -> str:
        ans = ''
        for idx in range(len(s)):
            odd_palindrome = self.get_longest_palindrome(s, idx, idx)
            even_palindrome = self.get_longest_palindrome(s, idx, idx + 1)
            if len(ans) < len(odd_palindrome):
                ans = odd_palindrome
            if len(ans) < len(even_palindrome):
                ans = even_palindrome
        return ans

    def get_longest_palindrome(self, s: str, i: int, j: int) -> str:
        while 0 <= i and j < len(s) and s[i] == s[j]:
            i -= 1
            j += 1
        return s[i + 1:j]