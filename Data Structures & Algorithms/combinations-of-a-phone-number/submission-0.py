class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        info = {}
        info["2"] = "abc"
        info["3"] = "def"
        info["4"] = "ghi"
        info["5"] = "jkl"
        info["6"] = "mno"
        info["7"] = "pqrs"
        info["8"] = "tuv"
        info["9"] = "wxyz"
        
        res = []

        def solve(idx: int, candi: str):
            if idx == len(digits):
                if len(candi) > 0:
                    res.append(candi)
                return
            for ch in info[digits[idx]]:
                solve(idx + 1, candi + ch)
            
        solve(0, "")
        return res