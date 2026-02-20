class Solution {
public:
    int minimumTrianglePathSum(int i, int j, vector<vector<int>>& triangle, vector<vector<int>>& dp, int n) {
        if (i == (n-1)) return dp[i][j] = triangle[i][j];
        if (dp[i][j] != -100001) return dp[i][j];
        int down = minimumTrianglePathSum(i + 1, j, triangle, dp, n);
        int diagonal = minimumTrianglePathSum(i + 1, j + 1, triangle, dp, n);
        return dp[i][j] = min(down, diagonal) + triangle[i][j];
    }
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int> (n, -100001));
        return minimumTrianglePathSum(0, 0, triangle, dp, n);
    }
};
// Time Complexity: O(NxN)
// Space Complexity: O(NxN) {dp} + O(N) {recursive stack space}
