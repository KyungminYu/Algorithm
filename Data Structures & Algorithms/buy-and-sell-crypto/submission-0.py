class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        minVal = 101
        res = 0

        for p in prices:
            profit = p - minVal
            res = max(res, profit)
            minVal = min(minVal, p)
        return res