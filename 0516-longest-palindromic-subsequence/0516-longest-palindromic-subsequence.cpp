class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int low = n-1; low >= 0; low--) {
            for (int high = low; high < n; high++) {
                if (low == high) {
                    dp[low][high] = 1;
                    continue;
                }
                if (s[low] == s[high]) dp[low][high] = 2 + dp[low+1][high-1];
                else {
                    dp[low][high] = max(dp[low+1][high], dp[low][high-1]);
                }
            }
        }
        return dp[0][n-1];
    }
};

// class Solution {
// public:
//     int lps(string s, int low, int high, vector<vector<int>>& dp) {
//         if (dp[low][high] != -1) return dp[low][high];
//         if (low > high) return dp[low][high] = 0;
//         if (low == high) return dp[low][high] =  1;
//         if (s[low] == s[high]) return dp[low][high] =  2 + lps(s, low+1, high-1, dp);
//         return dp[low][high] = max(lps(s, low+1, high, dp), lps(s, low, high-1, dp));
//     }
//     int longestPalindromeSubseq(string s) {
//         int n = s.length();
//         vector<vector<int>> dp(n, vector<int>(n, -1));
//         return lps(s, 0, n-1, dp);
//     }
// };