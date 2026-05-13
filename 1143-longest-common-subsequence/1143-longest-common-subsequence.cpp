class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.length(), n2 = text2.length();
        vector<int> dp(n2+1, 0), temp(n2+1, 0);
        // base case
        for (int i = 0; i <= n1; i++) dp[0] = 0;
        // build the dp
        for (int i = 1; i<= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (text1[i-1] == text2[j-1]) temp[j] = 1 + dp[j-1];
                else temp[j] = max(dp[j], temp[j-1]);
            }
            dp = temp;
        }
        return dp[n2];
    }
};