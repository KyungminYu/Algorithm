class Solution:
    def minWindow(self, s: str, t: str) -> str:
        slen = len(s)
        tlen = len(t)

        if slen < tlen:
            return ""

        count = {}
        for ch in t:
            count[ch] = count.get(ch, 0) + 1

        res = [0, slen]
        left = 0
        window = {}
        matched = 0
        for right, ch in enumerate(s):
            window[ch] = window.get(ch, 0) + 1

            if ch in count and count[ch] == window[ch]:
                matched += 1

            while matched == len(count):
                if (right - left + 1) < (res[1] - res[0] + 1):
                    res[0] = left
                    res[1] = right
                
                lch = s[left]
                window[lch] -= 1

                if lch in count and window[lch] < count[lch]:
                    matched -= 1
                left += 1
        if res[0] == 0 and res[1] == slen:
            return ""
        return s[res[0]: res[1] + 1]







