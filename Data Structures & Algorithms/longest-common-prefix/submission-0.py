class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        res = ""
        minL = 200
        for s in strs:
            minL = min(minL, len(s))

        for idx in range(minL):
            ch = strs[0][idx]
            isCommon = True
            for s in strs[1:]:
                if ch != s[idx]:
                    isCommon = False
                    break
            if not isCommon:
                break
            res += ch
        return res