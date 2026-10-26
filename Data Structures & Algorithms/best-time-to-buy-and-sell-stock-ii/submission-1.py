class Solution:
    def maxProfit(self, prices: List[int]) -> int:

        n = len(prices)
        cache = {}
        def solve(idx: int, isHold: bool):
            if idx == n:
                return 0
            if (idx, isHold) in cache:
                return cache[(idx, isHold)]
            res = solve(idx + 1, isHold)

            if isHold:
                res = max(res, prices[idx] + solve(idx + 1, False))
            else:
                res = max(res, -prices[idx] + solve(idx + 1, True))
            cache[(idx, isHold)] = res
            return res

        return solve(0, False)