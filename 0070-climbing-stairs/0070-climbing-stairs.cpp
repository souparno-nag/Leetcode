class Solution {
public:
    int countPossibleClimbs (int n, vector<int>& dp) {
        if (dp[n] != -1) return dp[n];
        dp[n] = countPossibleClimbs(n-1, dp) + countPossibleClimbs(n-2, dp);
        return dp[n];
    }
    int climbStairs(int n) {
        vector<int> dp(n+1, -1);
        dp[0] = 1; dp[1] = 1;
        return countPossibleClimbs(n, dp);
    }
};