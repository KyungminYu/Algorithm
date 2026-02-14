```
class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        self.transpose(matrix)
        self.flip_horizontal(matrix)

    def transpose(self, matrix: List[List[int]]) -> None:
        size = len(matrix)
        for y in range(size):
            for x in range(y + 1, size):
                matrix[y][x], matrix[x][y] = matrix[x][y], matrix[y][x]

    def flip_horizontal(self, matrix: List[List[int]]) -> None:
        size = len(matrix)
        for y in range(size):
            for x in range(size//2, size):
                matrix[y][x], matrix[y][size - 1 - x] = matrix[y][size - 1 - x], matrix[y][x]
```

To rotate the matrix by 90 degrees clockwise in-place, I first transpose it (swap matrix[y][x] with matrix[x][y] for x > y). Then I reverse each row to perform a horizontal flip. These two steps together produce the 90° rotation, and it runs in O(n^2) time with O(1) extra space.