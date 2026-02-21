class Solution {
public:
    int findMinPathSum(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
        int m = matrix.size(), n = matrix[0].size();
        if (j < 0 || j >= n) return INT_MAX;
        if (i == 0) return dp[i][j] = matrix[i][j];
        if (dp[i][j] != 101) return dp[i][j];
        int straightUp = findMinPathSum(i - 1, j, matrix, dp);
        int leftUp = findMinPathSum(i - 1, j - 1, matrix, dp);
        int rightUp = findMinPathSum(i - 1, j + 1, matrix, dp);
        return dp[i][j] = min(straightUp, min(leftUp, rightUp)) + matrix[i][j];
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp (m, vector<int> (n, 101));
        int minPath = INT_MAX;
        for (int j = 0; j < n; j++) {
            minPath = min(minPath, findMinPathSum(m-1, j, matrix, dp));
        }
        return minPath;
    }
};