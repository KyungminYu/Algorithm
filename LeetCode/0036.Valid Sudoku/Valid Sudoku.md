```
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
```
 
I validate the Sudoku board by tracking which digits have appeared in each row, column, and 3x3 sub-box.

I use three boolean tables: rows, cols, and boxes, where rows[i][d] indicates whether digit d has already appeared in row i (similarly for columns and boxes).
Then I scan the 9x9 board. For each digit, I compute its box index as (i // 3) * 3 + (j // 3).
If the digit was already seen in the same row, column, or box, I return False. 
Otherwise, I mark it as seen and continue.
If I finish the scan without conflicts, I return True.

Time complexity is O(9*9), which is O(1) for fixed-size Sudoku (or O(n^2) if generalized). Space is O(1).
