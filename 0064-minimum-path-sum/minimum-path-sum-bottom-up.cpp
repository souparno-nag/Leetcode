class Solution {
public:
    int countMinimumPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int> (n, -1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                } else {
                    int up = (i > 0) ? dp[i-1][j] : INT_MAX;
                    int left = (j > 0) ? dp[i][j-1] : INT_MAX;
                    dp[i][j] = min(up, left) + grid[i][j];
                }
            }
        }
        return dp[m-1][n-1];
    }
    int minPathSum(vector<vector<int>>& grid) {
        return countMinimumPathSum(grid);
    }
};
// Time Complexity: O(MxN)
// Space Complexity: O(MxN) {dp}
