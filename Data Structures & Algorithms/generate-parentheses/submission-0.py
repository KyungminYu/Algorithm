class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res = []

        def solve(openCnt: int, closeCnt: int, candi: List):
            if openCnt == n and closeCnt == n:
                print(candi)
                res.append("".join(candi))
                return
            if openCnt == closeCnt:
                solve(openCnt + 1, closeCnt, candi + ["("])
            elif openCnt > closeCnt:
                if openCnt < n:
                    solve(openCnt + 1, closeCnt, candi + ["("])
                solve(openCnt, closeCnt + 1, candi + [")"])

        solve(0, 0, [])

        return res
        