class Solution {
public:
    int countMinimumPathSum(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
        if (i == 0 && j == 0) return dp[i][j] = grid[i][j];
        if (i < 0 || j < 0) return INT_MAX;
        if (dp[i][j] != -1) return dp[i][j];
        int up = countMinimumPathSum(i - 1, j, grid, dp);
        int left = countMinimumPathSum(i, j - 1, grid, dp);
        return dp[i][j] = min(up, left) + grid[i][j];
    }
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int> (n, -1));
        return countMinimumPathSum(m - 1, n - 1, grid, dp);
    }
};
// Time Complexity = O(MxN)
// Space Complexity = O(MxN) {dp} + O((M-1)+(N-1)) {recursion stack from path length}
