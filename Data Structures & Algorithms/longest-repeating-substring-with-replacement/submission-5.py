class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        # PASS O(n)
        l = len(s)
        res = 0
        left = 0
        count = {}
        maxFreq = 0
        for right in range(l):
            if s[right] in count:
                count[s[right]] += 1
            else:
                count[s[right]] = 1
            maxFreq = max(maxFreq, count[s[right]])

            while (right - left + 1) - maxFreq > k:
                count[s[left]] -= 1
                left += 1
            res = max(res, (right - left + 1))
        return res