class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        rows = [[False] * 10 for _ in range(10)]
        cols = [[False] * 10 for _ in range(10)]
        cell = [[False] * 10 for _ in range(10)]

        for i in range(9):
            for j in range(9):
                if board[i][j] == '.':
                    continue
                num = int(board[i][j])
                cellIdx = (i // 3) * 3 + (j // 3)
                if rows[i][num] or cols[j][num] or cell[cellIdx][num]:
                    return False
                rows[i][num] = True
                cols[j][num] = True
                cell[cellIdx][num] = True
        return True