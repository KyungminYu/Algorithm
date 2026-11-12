```
from collections import Counter


class Solution:
    def minWindow(self, s: str, t: str) -> str: 
        m = len(s)
        n = len(t)
        if m < n:
            return ""
        counter = Counter(t)
        remain = n
        left = 0
        resLIdx = 0
        resLen = m + 1

        for right, c in enumerate(s):
            if counter[c] > 0:
                remain -= 1
            counter[c] -= 1

            while remain == 0:
                if right - left < resLen:
                    resLIdx = left
                    resLen = right - left
                l_ch = s[left]
                if counter[l_ch] == 0:
                    remain += 1
                counter[l_ch] += 1
                left += 1

        if resLen == m + 1:
            return ""
        return s[resLIdx: resLIdx + resLen + 1]
```

I use a sliding window and a counter to track the required characters. 
When all characters are included, I shrink the window and update the minimum result. 
The time complexity is O(m + n), and the space complexity is O(n).
