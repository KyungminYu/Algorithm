class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        last = {}
        s_idx = 0
        ans = 0
        for e_idx, x in enumerate(s):
            if x in last and s_idx <= last[x]:
                s_idx = last[x] + 1
            last[x] = e_idx
            ans = max(ans, e_idx - s_idx + 1)
        return ans