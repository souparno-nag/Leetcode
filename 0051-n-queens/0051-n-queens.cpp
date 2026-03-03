class Solution {
public:
    bool isValid (vector<string> board, int row, int col, int n) {
        for (int i = 0; i < n; i++) {
            if (board[i][col] == 'Q') return false;
            if (board[row][i] == 'Q') return false;
        }
        int r = row, c = col;
        while (r >= 0 && c >= 0) {
            if (board[r--][c--] == 'Q') return false;
        }
        r = row; c = col;
        while (r >= 0 && c < n) {
            if (board[r--][c++] == 'Q') return false;
        }
        return true;
    }
    void nQueens(vector<string> board, int row, int n, vector<vector<string>>& result) {
        if (row == n) {
            result.push_back(board);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col, n)) {
                board[row][col] = 'Q';
                nQueens(board, row+1, n, result);
                board[row][col] = '.';
            }
        }
        return;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board (n, string(n, '.'));
        nQueens(board, 0, n, result);
        return result;
    }
};