
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