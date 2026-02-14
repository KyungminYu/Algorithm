```
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        last = {}
        s_idx = 0
        ans = 0
        for e_idx, x in enumerate(s):
            if x in last and last[x] >= s_idx:
                s_idx = last[x] + 1
            last[x] = e_idx
            ans = max(ans, e_idx - s_idx + 1)
        return ans
```

I use the sliding window technique with two pointers: s_idx is the start of the current window and e_idx is the end of the current window.
last is a hashmap for saving a last index of each character.

For each character x at position e_idx:
If x has appeared before and its last seen index is inside the current window (last[x] >= s_idx), then the substring would contain a duplicate.
So I move the start pointer to one position after that duplicate: s_idx = last[x] + 1.

Then I update last[x] = e_idx to record the current position of x.
The current window length is e_idx - s_idx + 1, and I keep the maximum in ans.

This runs in O(n) time because each character is processed once, and the hash map lookups are O(1) on average. The extra space is O(min(n, alphabet)) for the map. 