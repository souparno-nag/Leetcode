class Solution {
    long long MOD = 1e9+7;
    long long countDisSub(int i, string s, vector<long long>& dp, vector<long long>& prevIndex) {
        if (i == -1) return 0;
        if (dp[i] != -1) return dp[i];
        int j = prevIndex[i];
        if (j != -1) return dp[i] =  ((2*countDisSub(i-1, s, dp, prevIndex)%MOD)%MOD - countDisSub(j-1, s, dp, prevIndex) + MOD)%MOD;
        return dp[i] = ((2*countDisSub(i-1, s, dp, prevIndex)%MOD+1)%MOD - countDisSub(j, s, dp, prevIndex) + MOD)%MOD;
    }
    
public:
    int distinctSubseqII(string s) {
        int n = s.length();
        int last[26];
        fill(last, last+26, -1);
        vector<long long> dp(n, -1), prevIndex(n, -1);
        for (int i = 0; i < n; i++) {
            prevIndex[i] = last[s[i] - 'a'];
            last[s[i] - 'a'] = i;
        }
        return (int) countDisSub(n-1, s, dp, prevIndex);
    }
};