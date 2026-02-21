class Solution {
public:
    int findMinPathSum(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> dp(n, 101);
        for (int j = 0; j < n; j++) {
            dp[j] = matrix[0][j];
        }
        for (int i = 1; i < m; i++) {
            vector<int> temp(n, 101);
            for (int j = 0; j < n; j++) {
                int straightUp = dp[j];
                int leftUp = (j != 0) ? dp[j-1] : INT_MAX;
                int rightUp = (j != n-1) ? dp[j+1] : INT_MAX;
                temp[j] = min(straightUp, min(leftUp, rightUp)) + matrix[i][j];
            }
            dp = temp;
        }
        int minPath = INT_MAX;
        for (int j = 0; j < n; j++) {
            minPath = min(minPath, dp[j]);
        }
        return minPath;
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        return findMinPathSum(matrix);
    }
};
// Time Complexty: O(MxN)
// Space Complexity: O(N) {dp}
