class Solution {
public:
    int countDistinctSubsequences(string s, string t, int i, int j, vector<vector<int>>& dp) {
        // define base case
        if (j < 0) return 1;
        if (i < 0) return 0;
        // define all possibilities
        if (dp[i][j] != -1) return dp[i][j];
        if (s[i] == t[j]) return dp[i][j] = countDistinctSubsequences(s, t, i-1, j-1, dp) + countDistinctSubsequences(s, t, i-1, j, dp);
        return dp[i][j] = countDistinctSubsequences(s, t, i-1, j, dp);
    }
    int numDistinct(string s, string t) {
        int n = s.length(), m = t.length();
        vector<vector<uint32_t>> dp(n+1, vector<uint32_t>(m+1, 0));
        // base cases
        for (int i = 0; i <= n; i++) dp[i][0] = 1;
        for (int j = 1; j <= m; j++) dp[0][j] = 0;
        // build the dp table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return (int) dp[n][m];
    }
};