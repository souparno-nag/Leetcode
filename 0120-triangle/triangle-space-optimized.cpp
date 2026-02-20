class Solution {
public:
    int minimumTrianglePathSum(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(n, 0);
        for (int j = 0; j < n; j++) {
            dp[j] = triangle[n-1][j];
        }
        for (int i = n-2; i >= 0; i--) {
            vector<int> temp(n, 0);
            for (int j = i; j >= 0; j--) {
                int down = dp[j];
                int diagonal = dp[j+1];
                temp[j] = min(down, diagonal) + triangle[i][j];
            }
            dp = temp;
        }
        return dp[0];
    }
    int minimumTotal(vector<vector<int>>& triangle) {
        return minimumTrianglePathSum(triangle);
    }
};
// Time Complexity: O(NxN)
// Space Complexity: O(N) {dp}
