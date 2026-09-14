class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        slen = len(s)
        tlen = len(t)
        if tlen > slen:
            return 0
            
        memo = {}

        def solve(sIdx: int, tIdx: int) -> int:
            if tIdx == tlen:
                return 1
            if sIdx == slen or slen - sIdx < tlen - tIdx:
                return 0
            if (sIdx, tIdx) in memo:
                return memo[(sIdx, tIdx)]
            res = solve(sIdx + 1, tIdx)
            if s[sIdx] == t[tIdx]:
                res += solve(sIdx + 1, tIdx + 1)
            memo[(sIdx, tIdx)] = res
            return res

        return solve(0, 0)