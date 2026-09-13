class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        cache = {}
        def solve(cIdx: int, remains: int) -> int:
            if remains == 0:
                return 1
            if cIdx == len(coins) or remains < 0:
                return 0
            if (cIdx, remains) in cache:
                return cache[(cIdx, remains)]
            res = (
                solve(cIdx, remains - coins[cIdx])
                + solve(cIdx + 1, remains)
            )
            cache[(cIdx, remains)] = res
            return res
        return solve(0, amount)