class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        rows = [[0] * 9 for _ in range(9)]
        cols = [[0] * 9 for _ in range(9)]
        cells = [[0] * 9 for _ in range(9)]

        for r in range(9):
            for c in range(9):
                val = board[r][c]
                if val == ".":
                    continue
                cell = r // 3 * 3 + c // 3
                num = int(val) - 1
                if rows[r][num] == 1 or cols[c][num] == 1 or cells[cell][num] == 1:
                    return False
                rows[r][num] += 1
                cols[c][num] += 1
                cells[cell][num] += 1
        return True