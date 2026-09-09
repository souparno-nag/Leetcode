class Solution {
    int MOD = 1e9+7;    
public:
    int distinctSubseqII(string s) {
        int n = s.length();
        vector<int> last(26, 0);
        vector<long> dp(n+1, 0);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            int j = last[s[i-1]-'a'];
            if (j == 0) dp[i] = (2*dp[i-1]+1 - dp[j] + MOD)%MOD;
            else dp[i] = (2*dp[i-1] - dp[j-1] + MOD)%MOD;
            last[s[i-1]-'a'] = i;
        }
        return dp[n];
    }
};