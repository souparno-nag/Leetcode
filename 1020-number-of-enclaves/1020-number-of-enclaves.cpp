class Solution {
public:
    int delRow[4] = {-1, 0, 1, 0};
    int delCol[4] = {0, -1, 0, 1};
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // first row, last row, first column, last column
                if (i == 0 || i == m-1 || j == 0 || j == n-1) {
                    if (grid[i][j] == 1) {
                        q.push({i, j});
                        visited[i][j] = true;
                    }
                }
            }
        }
        while (!q.empty()) {
            pair<int, int> node = q.front();
            q.pop();
            int r = node.first, c = node.second;
            for (int i = 0; i < 4; i++) {
                int row = r + delRow[i], col = c + delCol[i];
                if (row >= 0 && row < m && col >= 0 && col < n && !visited[row][col] && grid[row][col] == 1) {
                    visited[row][col] = true;
                    q.push({row, col});
                }
            }
        }
        int count = 0;
        for (int i = 1; i < m-1; i++) {
            for (int j = 1; j < n-1; j++) {
                if (!visited[i][j] && grid[i][j] == 1) count++;
            }
        }
        return count;
    }
};