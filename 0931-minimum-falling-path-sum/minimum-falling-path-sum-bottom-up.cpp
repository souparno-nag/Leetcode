class Solution {
public:
    int findMinPathSum(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp (m, vector<int> (n, 101));
        for (int j = 0; j < n; j++) {
            dp[0][j] = matrix[0][j];
        }
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int straightUp = dp[i-1][j];
                int leftUp = (j != 0) ? dp[i-1][j-1] : INT_MAX;
                int rightUp = (j != n-1) ? dp[i-1][j+1] : INT_MAX;
                dp[i][j] = min(straightUp, min(leftUp, rightUp)) + matrix[i][j];
            }
        }
        int minPath = INT_MAX;
        for (int j = 0; j < n; j++) {
            minPath = min(minPath, dp[m-1][j]);
        }
        return minPath;
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        return findMinPathSum(matrix);
    }
};
// Time Complexity: O(MxN)
// Space Complexity: O(MxN) {dp}
