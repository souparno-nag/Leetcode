class Solution {
public:
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, -1, 0, 1};
    void dfs(int r, int c, vector<vector<bool>>& visited, vector<vector<char>>& board) {
        visited[r][c] = true;
        int n = board.size(), m = board[0].size();
        for (int i = 0; i < 4; i++) {
            int row = r + delRow[i];
            int col = c + delCol[i];
            if (row >= 0 && row < n && col >= 0 && col < m && !visited[row][col] && board[row][col] == 'O') {
                dfs(row, col, visited, board);
            }
        }
    }
    void solve(vector<vector<char>>& board) {
        int n = board.size(), m = board[0].size();
        vector<vector<bool>> visited (n, vector<bool> (m, false));
        // traverse first and last rows
        for (int j = 0; j < m; j++) {
            // first row
            if (!visited[0][j] && board[0][j] == 'O') {
                dfs(0, j, visited, board);
            }
            // last row
            if (!visited[n-1][j] && board[n-1][j] == 'O') {
                dfs(n-1, j, visited, board);
            }
        }
        // traverse first and last columns
        for (int i = 0; i < n; i++) {
            // first column
            if (!visited[i][0] && board[i][0] == 'O') {
                dfs(i, 0, visited, board);
            }
            // last column
            if (!visited[i][m-1] && board[i][m-1] == 'O') {
                dfs(i, m-1, visited, board);
            }
        }
        // mark anything not visited as X
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};