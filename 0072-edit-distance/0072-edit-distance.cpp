class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        vector<int> dp(m+1, 0), temp(m+1, 0);
        // define base cases
        for (int j = 0; j <= m; j++) dp[j] = j;
        // build the dp table
        for (int i = 1; i <= n; i++) {
            temp[0] = i;
            for (int j = 1; j <= m; j++) {
                if (word1[i-1] == word2[j-1]) {
                    temp[j] = dp[j-1];
                    continue;
                }
                temp[j] = 1 + min(
                    temp[j-1], // insert
                    min(
                        dp[j], // delete
                        dp[j-1] // replace
                    )
                );
            }
            dp = temp;
        }
        return dp[m];
    }
};