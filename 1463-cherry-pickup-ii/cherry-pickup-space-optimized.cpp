class Solution {
public:
    int maxCherries (vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(m, vector<int> (m, -1));
        // Base Case
        for (int j1 = 0; j1 < m; j1++) {
            for (int j2 = 0; j2 < m; j2++) {
                if (j1 == j2) {
                    dp[j1][j2] = grid[n-1][j1];
                } else {
                    dp[j1][j2] = grid[n-1][j1] + grid[n-1][j2];
                }
            }
        }
        for (int i = n-2; i >= 0; i--) {
            vector<vector<int>> temp(m, vector<int> (m, -1));
            for (int j1 = 0; j1 < m; j1++) {
                for (int j2 = 0; j2 < m; j2++) {
                    int maxSum = INT_MIN;
                    for (int dj1 = -1; dj1 <= 1; dj1++) {
                        for (int dj2 = -1; dj2 <= 1; dj2++) {
                            int c1 = j1+dj1, c2 = j2+dj2;
                            if (c1 < 0 || c1 >= m || c2 < 0 || c2 >= m) continue;
                            maxSum = max(maxSum, dp[c1][c2]);
                        }
                    }
                    temp[j1][j2] = maxSum + ((j1 == j2) ? grid[i][j1] : grid[i][j1] + grid[i][j2]);
                }
            }
            dp = temp;
        }
        return dp[0][m-1];
    }
    int cherryPickup(vector<vector<int>>& grid) {
        return maxCherries(grid);
    }
};
