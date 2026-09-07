class Solution {
    long long MOD = 1e9+7;
    long long countDisSub(int i, string s, vector<long long>& dp) {
        if (i == -1) return 0;
        if (dp[i] != -1) return dp[i];
        int j = -1;
        for (int k = i-1; k >= 0; k--) {
            if (s[k] == s[i]) {
                j = k;
                break;
            }
        }
        if (j != -1) return dp[i] =  ((2*countDisSub(i-1, s, dp)%MOD)%MOD - countDisSub(j-1, s, dp) + MOD)%MOD;
        return dp[i] = ((2*countDisSub(i-1, s, dp)%MOD+1)%MOD - countDisSub(j, s, dp) + MOD)%MOD;
    }
    
public:
    int distinctSubseqII(string s) {
        int n = s.length();
        vector<long long> dp(n, -1);
        return (int) countDisSub(n-1, s, dp);
    }
};