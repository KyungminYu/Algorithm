class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        # I use a sliding window. If window size - max frequency is greater than k, I shrink the window. The time complexity is O(n), and the space complexity is O(1).
        count = {}
        left = 0
        max_freq = 0
        res = 0

        for right, r_ch in enumerate(s):
            count[r_ch] = count.get(r_ch, 0) + 1
            max_freq = max(max_freq, count[r_ch])

            window_size = right - left + 1

            # Shrink if the window needs more than k replacements.
            while window_size - max_freq > k:
                l_ch = s[left]
                count[l_ch] -= 1
                left += 1
                window_size = right - left + 1
            res = max(res, window_size)
        return res