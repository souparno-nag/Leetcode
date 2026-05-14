class Solution {
public:
    int lps(string s) {
        int n = s.length();
        vector<int> dp(n, 0), curr(n, 0);
        for (int low = n-1; low >= 0; low--) {
            curr[low] = 1;
            for (int high = low+1; high < n; high++) {
                if (s[low] == s[high]) curr[high] = 2 + dp[high-1];
                else curr[high] = max(curr[high-1], dp[high]);
            }
            dp = curr;
        }
        return dp[n-1];
    }
    int minInsertions(string s) {
        return s.length() - lps(s);
    }
};