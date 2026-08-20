class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        # PASS O(m * n) m: len(chars), n: len(s)
        l = len(s)
        res = 0
        chars = set(s)
        for c in chars:
            count = 0
            left = 0
            for right in range(l):
                if s[right] == c:
                    count += 1
                while (right - left + 1) - count > k:
                    if s[left] == c:
                        count -= 1
                    left += 1
                res = max(res, (right - left + 1))
        return res