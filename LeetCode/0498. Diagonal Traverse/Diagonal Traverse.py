# I use matrix traversal to resolve it.
# When we traverse matrix in given way, we can observe that the summations of row and col increase gradually in every diagonal.
# Also, direction can be defined by using summations. If summation is even, we have to traverse left-bottom to right-top. If not, we have to traverse right-top to left-bottom.
# Then, if we traverse to right-top, our start point is based on the left edge (0) or bottom edge (s - m + 1), and our end point is based on the top edge (s) or right edge (n - 1).
# Otherwise, if we traverse to left-bottom, our start point is based on the top edge (0) or right edge (s - n + 1), and our end point is based on the left edge (s) or bottom edge (m - 1).
# So we use max for the start point and min for the end point to keep the index inside the matrix boundaries.
# Its time complexity is O(m * n) and space complexity is also O(m * n)

class Solution:
    def findDiagonalOrder(self, mat: list[list[int]]) -> list[int]:
        res = []
        m = len(mat)
        n = len(mat[0])
        for s in range(m + n - 1):
            if s % 2 == 0:
                start = max(0, s - m + 1)
                end = min(s, n - 1)
                for i in range(start, end + 1):
                    r = s - i
                    c = i
                    res.append(mat[r][c])
            else:
                start = max(0, s - n + 1)
                end = min(s, m - 1)
                for i in range(start, end + 1):
                    r = i
                    c = s - i
                    res.append(mat[r][c])
        return res