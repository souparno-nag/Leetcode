class Solution {
public:
    int countMinimumPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, 0);
        for (int i = 0; i < m; i++) {
            vector<int> temp(n, 0);
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    temp[j] = grid[i][j];
                } else {
                    int up = (i > 0) ? dp[j] : INT_MAX;
                    int left = (j > 0) ? temp[j-1] : INT_MAX;
                    temp[j] = min(up, left) + grid[i][j];
                }
            }
            dp = temp;
        }
        return dp[n-1];
    }
    int minPathSum(vector<vector<int>>& grid) {
        return countMinimumPathSum(grid);
    }
};
// Time Complexity: O(MxN)
// Space Complexity: O(N) {dp}
