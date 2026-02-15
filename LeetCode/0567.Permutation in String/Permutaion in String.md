```
class Solution:

    def checkInclusion(self, s1: str, s2: str) -> bool:
        s1_len = len(s1)
        s2_len = len(s2)
        if s2_len < s1_len:
            return False

        s1_count = [0] * 26
        s2_sub_count = [0] * 26

        for idx in range(s1_len):
            s1_count[ord(s1[idx]) - ord('a')] += 1

        for idx in range(s1_len):
            s2_sub_count[ord(s2[idx]) - ord('a')] += 1
            
        if s1_count == s2_sub_count:
            return True

        for idx in range(s1_len, s2_len):
            s2_sub_count[ord(s2[idx]) - ord('a')] += 1
            s2_sub_count[ord(s2[idx - s1_len]) - ord('a')] -= 1
            if s1_count == s2_sub_count:
                return True

        return False
```

### GPT revised

I solve it with a single linear scan using a sliding window and fixed-size character counting.

My key observation is: if a substring of s2 is a permutation of s1, then they must have the exact same character frequency.

First, I build s1_count for s1, and I also build s2_sub_count for the first window of s2 with length len(s1).
If the two arrays match, that window is a permutation, so I return True.

Otherwise, I slide the window one character at a time across s2.
For each move, I:

add the new rightmost character to s2_sub_count

remove the old leftmost character from s2_sub_count

After each shift, I compare s2_sub_count with s1_count.
If they match at any point, it means the current window is a permutation of s1, so I return True.
If I finish scanning without a match, I return False.

This runs in O(n) time because I update counts in O(1) per step, and the comparison is constant-size (26 letters).
Space complexity is O(1).

### My solution

I solve it with a single linear scan with a sliding window and character counting.

According to the by observation, If a substring if s2 is a permutation of s1, they must have the exact same character frequency.

First, I define s1_count and s2_sub_count for the first window of s2 with s1's length.
If the two array match, that window is a permutation, so I return True.

Otherwise, I slide the window one character at a time across s2.
For each move, 
I add the new rigthmost character to s2_sub_count,
I remove the old leftmost character from s2_sub_count

After each shift, I compare s2_sub_count with s1_count. 
If they match at any point. It means the current window is a permutation of s1.
so, I return True.
If I finish scanning without a match, I return False/

This runs in O(n) time with O(1) extra space