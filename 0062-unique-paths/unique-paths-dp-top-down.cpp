class Solution {
public:
    int countUniquePaths(int i, int j, vector<vector<int>>& dp) {
        if (i == 0 && j == 0) return dp[i][j] = 1;
        if (i < 0 || j < 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        int up = countUniquePaths(i - 1, j, dp);
        int left = countUniquePaths(i, j - 1, dp);
        return dp[i][j] = up + left;
    }
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp (m, vector<int> (n, -1));
        return countUniquePaths(m - 1, n - 1, dp);
    }
};
// Time Complexity = O(M*N)
// Space Complexity = O((M-1)*(N-1)) {due to recursion stack space} + O(M*N) {dp}
