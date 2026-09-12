class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        
        # stay: 0, buy = 1, sell = 2
        cache = {}
        def solve(date: int, prevAction: int, hold: int) -> int:
            if len(prices) <= date:
                return 0
            if (date, prevAction, hold) in cache:
                return cache[(date, prevAction, hold)]
            res = 0
            if prevAction == 0:
                if hold >= 0:
                    stayRes = solve(date + 1, 0, hold)
                    sellRes = solve(date + 1, 2, -1) + (prices[date] - hold)
                    res = max(stayRes, sellRes)
                else:                   
                    stayRes = solve(date + 1, 0, hold) 
                    buyRes = solve(date + 1, 1, prices[date])
                    res = max(stayRes, buyRes)
            elif prevAction == 1:
                stayRes = solve(date + 1, 0, hold)
                sellRes = solve(date + 1, 2, -1) + (prices[date] - hold)
                res = max(stayRes, sellRes)
            else:
                res = solve(date + 1, 0, hold) 
            cache[(date, prevAction, hold)] = res
            return res

        return solve(0, 0, -1)