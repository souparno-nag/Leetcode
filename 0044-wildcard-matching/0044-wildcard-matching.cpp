class Solution {
public:
    bool isMatch(string s, string p) {
        int n = p.length(), m = s.length();
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        // define base case
        dp[0][0] = true;
        for (int j = 1; j <= m; j++) dp[0][j] = false;
        int k = 0;
        while (p[k++] == '*') dp[k][0] = true;
        // build the table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[i-1] == s[j-1] || p[i-1] == '?') dp[i][j] = dp[i-1][j-1];
                else if (p[i-1] == '*') {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                } else {
                    dp[i][j] = false;
                }
            }
        }
        return dp[n][m];
    }
};