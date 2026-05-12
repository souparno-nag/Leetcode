class Solution {
public:
    int countCombinations(vector<vector<int>>& dp, vector<int>& coins, int ind, int target) {
        if (ind < 0) {
            return (target == 0) ? 1 : 0;
        }
        if (dp[ind][target] != -1) return dp[ind][target];
        int notPick = countCombinations(dp, coins, ind-1, target);
        int pick = (coins[ind] <= target) ? countCombinations(dp, coins, ind, target-coins[ind]) : 0;
        return dp[ind][target] = pick + notPick;
    }
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int> (amount+1, -1));
        return countCombinations(dp, coins, n-1, amount);
    }
};