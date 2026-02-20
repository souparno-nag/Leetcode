class Solution {
public:
    int countUniquePaths(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<int> dp (n, 0);
        for (int i = 0; i < m; i++) {
            vector<int> temp (n, 0);
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j]) {
                    temp[j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) {
                    temp[j] = 1;
                } else {
                    int up = (i > 0) ? dp[j] : 0;
                    int left = (j > 0) ? temp[j-1] : 0;
                    temp[j] = up + left;
                }
            }
            dp = temp;
        }
        return dp[n-1];
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        return countUniquePaths(obstacleGrid);
    }
};