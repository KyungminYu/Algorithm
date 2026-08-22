class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        
        res = [0] * len(temperatures)

        stk = []
        for idx, t in enumerate(temperatures):
            while len(stk) > 0 and stk[-1][0] < t:
                info = stk.pop()
                res[info[1]] = idx - info[1]
            stk.append([t, idx])


        return res