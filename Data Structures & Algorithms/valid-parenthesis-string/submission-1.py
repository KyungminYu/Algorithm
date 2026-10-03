class Solution:
    def checkValidString(self, s: str) -> bool:
        n = len(s)
        cache = {}

        def validCheck(idx: int, opened: int) -> bool:
            if (idx, opened) in cache:
                return cache[(idx, opened)]
            res = False
            if opened < 0:
                res = False
            elif idx == n:
                res = opened == 0
            elif s[idx] == '(':
                res = validCheck(idx + 1, opened + 1)
            elif s[idx] == ')':
                res = validCheck(idx + 1, opened - 1)
            else:
                res = (
                    validCheck(idx + 1, opened + 1)
                    or validCheck(idx + 1, opened - 1)
                    or validCheck(idx + 1, opened)
                )
            cache[(idx, opened)] = res

            return res

        return validCheck(0, 0)