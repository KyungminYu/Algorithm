class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        # PASS O(n)
        # To address this problem, I will use two pointer.
        # I will iterate all characters in s string with counting frequency of each character.
        # then, check longest repeating character by using two pointer.
        # It is true if (right - left + 1) - count[max Freq] > k, then we can make repeating character

        n = len(s)
        res = 0
        left = 0
        count = defaultdict(int)
        maxFreq = 0
        for right in range(n):
            count[s[right]] += 1
            maxFreq = max(maxFreq, count[s[right]])
            while (right - left + 1) - maxFreq > k:
                count[s[left]] -= 1
                left += 1
            res = max(res, (right - left + 1))

        return res