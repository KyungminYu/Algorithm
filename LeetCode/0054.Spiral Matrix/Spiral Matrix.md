```
class Solution:
    def spiralOrder(self, matrix: list[list[int]]) -> list[int]:
        res = []
        start = 0
        top = 0
        end = len(matrix[0]) - 1
        bottom = len(matrix) - 1
        while start <= end and top <= bottom:
            for c in range(start, end + 1):
                res.append(matrix[top][c])
            top += 1
            for r in range(top, bottom + 1):
                res.append(matrix[r][end])
            end -= 1
            if not (start <= end and top <= bottom):
                break
            for c in range(end, start - 1, -1):
                res.append(matrix[bottom][c])
            bottom -= 1
            for r in range(bottom, top - 1, -1):
                res.append(matrix[r][start])
            start += 1
        return res
```

I just traverse all cells by using row and column index. 
After every traversal, I change the boundary top, bottom, start, end
If its boundary is invalid, I stop traversal. 
Its time complexity is O(n * m) and space complexity is O(n * m)


```
class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        start = 0
        end = len(matrix[0]) - 1
        top = 0
        bottom = len(matrix) - 1
        res = []
        while start <= end and top <= bottom:
            if top <= bottom:
                for i in range(start, end + 1):
                    res.append(matrix[top][i])
                top += 1

            if start <= end:
                for i in range(top, bottom + 1):
                    res.append(matrix[i][end])
                end -= 1

            if top <= bottom:
                for i in range(end, start - 1, -1):
                    res.append(matrix[bottom][i])
                bottom -= 1

            if start <= end:
                for i in range(bottom, top - 1, -1):
                    res.append(matrix[i][start])
                start += 1

        return res
```


#### GPT revised.

I solve this with a simulation using four boundaries: start, end, top, and bottom, 
which represent the current unvisited rectangle.
In each loop, I peel off one “layer” in order:
traverse the top row from start to end, then top += 1
traverse the end column from top to bottom, then end -= 1
traverse the bottom row from end to start, then bottom -= 1
traverse the start column from bottom to top, then start += 1

Before each direction, I check top <= bottom and start <= end to avoid duplicates when only one row or one column is start.
This visits every element exactly once, so the time complexity is O(mn) and extra space is O(1) excluding the output.


#### My solution

I solve this problem with a simulation using four boundaries: start, end, top, bottom
These variables represent the current unvisited rectangle that I have to check in the next step.

In each loop, I visit this rectangle in this way.

First, traverse top row from start to end, then top += 1
Second, traverse end col from top to bottom, then end -= 1
Third, traverse bottom row from end to start, then bottom -= 1
Finally, traverse start col from bottom to top, then start += 1

Before each traverse, I checked top <= bottom and start <= end to avoid duplication.
