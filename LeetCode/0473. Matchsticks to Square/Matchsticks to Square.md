```
class Solution:
    def makesquare(self, matchsticks: list[int]) -> bool:
        sum_stick = sum(matchsticks)
        if sum_stick % 4 > 0:
            return False
        
        matchsticks.sort(reverse = True)
        one_side = sum_stick // 4
        if matchsticks[0] > one_side:
            return False
        
        sides = [one_side] * 4

        def solve(idx):
            if idx == len(matchsticks):
                for i in range(4):
                    if sides[i] != 0:
                        return False 
                return True
            
            for i in range(4):
                if sides[i] - matchsticks[idx] >= 0:
                    sides[i] -= matchsticks[idx]
                    if solve(idx + 1):
                        return True
                    sides[i] += matchsticks[idx]
            return False
        return solve(0)
```

I use backtracking.
First, I calculate the total length. If it is not divisible by four, I return False.
Second, I sort the matchsticks in descending order for faster pruning.
Third, I initialize four sides with the target length.
Then, I try to place each matchstick on every available side.
If all matchsticks are placed successfully, I return True.
It's time complexity is O(4^n) and space complexity is O(n)