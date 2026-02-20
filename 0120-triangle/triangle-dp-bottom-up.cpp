class Solution {
public:
    int minimumTrianglePathSum(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int> (n, 0));
        for (int j = 0; j < n; j++) {
            dp[n-1][j] = triangle[n-1][j];
        }
        for (int i = n-2; i >= 0; i--) {
            for (int j = i; j >= 0; j--) {
                int down = dp[i+1][j];
                int diagonal = dp[i+1][j+1];
                dp[i][j] = min(down, diagonal) + triangle[i][j];
            }
        }
        return dp[0][0];
    }
    int minimumTotal(vector<vector<int>>& triangle) {
        return minimumTrianglePathSum(triangle);
    }
};
// Time Complexity: O(N^2)
// Space Complexity: O(N^2) {dp}
