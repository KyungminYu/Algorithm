```
class Solution:
    def dailyTemperatures(self, temperatures: list[int]) -> list[int]:

        n = len(temperatures) 
        res = [0] * n
        stk = []
        for day, temp in enumerate(temperatures):
            while stk and stk[-1][0] < temp:
                c_temp, c_day = stk.pop()
                diff = day - c_day
                res[c_day] = diff
            stk.append((temp, day))
        return res
        
```

I use a monotonic decreasing stack storing (temp, day) tuples.
I pop elements while the stack's top temperature is lower than the current temperature, and record the day difference in the result array.
Its time Complexity is O(n) and Space Complexity is O(n)