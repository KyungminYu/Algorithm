class Solution:
    def partition(self, s: str) -> List[List[str]]:
        res = []
        n = len(s)

        dp = [[False] * (n + 1) for _ in range(n + 1)]
        for pLen in range(1, n + 1):
            for left in range(n - pLen + 1):
                right = left + pLen - 1
                dp[left][right] = (s[left] == s[right] and
                                    (left + 1 > right - 1 or
                                    dp[left + 1][right - 1]))

        def solve(left: int, partition: List):
            if left >= n:
                res.append(partition)
                return
            for right in range(left, n):
                if dp[left][right]:
                    solve(right + 1, partition + [s[left : right + 1]])

        solve(0, [])
        return res