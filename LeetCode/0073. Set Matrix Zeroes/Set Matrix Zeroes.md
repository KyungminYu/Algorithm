```
class Solution:
    def setZeroes(self, matrix: list[list[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        m = len(matrix)
        n = len(matrix[0])
        original_zeros = []
        for r in range(m):
            for c in range(n):
                if matrix[r][c] == 0:
                    original_zeros.append((r, c))

        def fill_zero(r: int, c: int):
            for row in range(m):
                matrix[row][c] = 0
            for col in range(n):
                matrix[r][col] = 0

        for r, c in original_zeros:
            fill_zero(r, c)

```

I use matrix traversal. 
First, I collect positions that have zero as element.
Second, I define fill_zero method that fills its entire row and column to 0.
Finally, I call fill_zero to all collected positions.
Its time complexity is O(m * n) and space complexity is O(m * n)