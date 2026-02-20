class Solution {
public:
    int countUniquePaths(int m, int n) {
        vector<int> dp (n, 0);
        for (int i = 0; i < m; i++) {
            vector<int> temp (n, 0);
            for (int j = 0; j < n; j++) {
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
    int uniquePaths(int m, int n) {
        return countUniquePaths(m , n);
    }
};
// Time Complexity = O(M*N)
// Space Complexity = O(N) {dp}
