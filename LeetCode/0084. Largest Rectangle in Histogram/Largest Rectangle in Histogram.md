```
class Solution:
    def largestRectangleArea(self, heights: list[int]) -> int:
        n = len(heights)
        stk = []
        left_sight = [-1] * n
        right_sight = [n] * n

        for i in range(n):
            while stk and heights[i] <= heights[stk[-1]]:
                stk.pop()
            if stk:
                left_sight[i] = stk[-1]
            stk.append(i)
            
        stk.clear()

        for i in range(n - 1, -1, -1):
            while stk and heights[i] <= heights[stk[-1]]:
                stk.pop()
            if stk:
                right_sight[i] = stk[-1]
            stk.append(i)
        print(left_sight)
        print(right_sight)

        res = 0
        for i in range(n):
            width = right_sight[i] - left_sight[i] - 1
            res = max(res, width * heights[i])

        return res
```

I use two stacks to solve it.
one handles the idx that height of this idx is larger than current height
the other handles also idx that height of this idx is larger than current height. 
It looks similar but their view is different, left_sights only consider its left side and right_sights consider right side
finally, I can calculate the size of the rectangle's width and multiply width with current height.
Its time complexity is O(n) and space complexity is O(n) 