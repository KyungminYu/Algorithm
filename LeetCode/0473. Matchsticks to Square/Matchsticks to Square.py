class Solution:
    def makesquare(self, matchsticks: list[int]) -> bool:
        # I use backtracking to solve it
        # First, I calculate sum of sticks and then if it is not divided 4 exactly, I return False
        # Second, I sort matchsticks list
        # Third, I calculate each side's length and make sides list for traversal
        # Forth, I define solve method to use backtracking
        # Fifth, in the method, if idx is len of matchsticks, then I can not process more and I check sides list elements are exactly zero. If they are zero, then I return True
        # if not, I check all sides that can use current idx's matchstick.

        sum_stick = sum(matchsticks)
        if sum_stick % 4 > 0:
            return False

        matchsticks.sort(reverse=True)
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