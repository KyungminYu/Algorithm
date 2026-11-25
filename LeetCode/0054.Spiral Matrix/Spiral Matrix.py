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