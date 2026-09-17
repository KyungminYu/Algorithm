class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        slen = len(s)
        plen = len(p)

        cache = {}
        def solve(sIdx: int, pIdx: int) -> bool:
            if (sIdx, pIdx) in cache:
                return cache[(sIdx, pIdx)]

            if pIdx == plen:
                return sIdx == slen

            current_match = sIdx < slen and (p[pIdx] == s[sIdx] or p[pIdx] == ".")

            if pIdx + 1 < plen and p[pIdx + 1] == '*':
                res = (current_match and solve(sIdx + 1, pIdx)) or solve(sIdx, pIdx + 2)
            else:
                res = current_match and solve(sIdx + 1, pIdx + 1)
            cache[(sIdx, pIdx)] = res
            return res
        return solve(0, 0)