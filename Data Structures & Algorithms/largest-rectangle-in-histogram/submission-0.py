class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        l = len(heights)

        stk = []
        leftSide = [-1] * l
        for i in range(l):
            while len(stk) > 0 and heights[stk[-1]] >= heights[i]:
                stk.pop()
            if stk:
                leftSide[i] = stk[-1]
            stk.append(i)

        stk = []
        rightSide = [l] * l
        for i in range(l - 1, -1, -1):
            while len(stk) > 0 and heights[stk[-1]] >= heights[i]:
                stk.pop()
            if stk:
                rightSide[i] = stk[-1]
            stk.append(i)

        res = 0
        for i in range(l):
            area = (rightSide[i] - leftSide[i] - 1) * heights[i]
            res = max(res, area)

        return res