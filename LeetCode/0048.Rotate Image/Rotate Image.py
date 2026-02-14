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