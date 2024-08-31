#include <iostream>
#include <vector>
using namespace std;

int dy[] = { 0, -1, 0, 1 };
int dx[] = { -1, 0, 1, 0 };

class Solution {
public:
    int height;
    int width;
    int wordLength;

    bool canMove(int y, int x) {
        return 0 <= y && y < height && 0 <= x && x < width;
    }


    bool exist(vector<vector<char>>& board, int y, int x, string word, int wordIndex) {
        if (wordIndex == wordLength) {
            return true;
        }
        else if (!canMove(y, x) || board[y][x] != word[wordIndex]) {
            return false;
        }
        char origin = board[y][x];
        board[y][x] = 'A' - 1;
        bool result = false;
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            result |= exist(board, ny, nx, word, wordIndex + 1);
        }
        board[y][x] = origin;
        return result;
    }

    bool exist(vector<vector<char>>& board, string word) {
        width = board[0].size();
        height = board.size();
        wordLength = word.length();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (exist(board, y, x, word, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};

int main() {

    vector<vector<char>> board = { { 'A', 'B', 'C', 'E' }, { 'S', 'F', 'C', 'S' }, { 'A', 'D', 'E', 'E' } };
    string word = "ABCCED";
    cout << Solution().exist(board, word) << endl;

    return 0;
}