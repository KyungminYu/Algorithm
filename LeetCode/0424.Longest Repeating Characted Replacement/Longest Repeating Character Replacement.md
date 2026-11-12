
### Not Optimal
```
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        n = len(s)
        if n <= 0 :
            return 0
        res = 1
        # left to right is repeating period
        for ch in s:
            left = 0
            changed = 0
            # fitst, suppose simulation of filling same character to end of string 
            for right in range(n):
                if s[right] != ch:
                    changed += 1
                # and then, cancel it until changed count is larger than k
                while changed > k:
                    if s[left] != ch:
                        changed -= 1
                    left += 1
                #  calculate length and compare it with previous result and remain larget one as a result value
                length = right - left + 1
                res = max(res, length)
        # repeat it until
        return res
```

# Optimal
```
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        count = {}
        left = 0
        max_freq = 0
        res = 0

        for right, r_ch in enumerate(s):
            count[r_ch] = count.get(r_ch, 0) + 1
            max_freq = max(max_freq, count[r_ch])

            window_size = right - left + 1

            while window_size - max_freq > k:
                l_ch = s[left]
                count[l_ch] -= 1
                left += 1
                window_size = right - left + 1
            res = max(res, window_size) 
        return res
```

I use a sliding window. 
If window size - max frequency is greater than k, I shrink the window. 
The time complexity is O(n), and the space complexity is O(1).
