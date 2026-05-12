class Solution {
public:
int countCoins(vector<vector<int>>& dp, vector<int>& coins, int ind, int target) {
    // define base case
    if (ind == 0) {
        if (target % coins[ind] == 0) return dp[ind][target] = target/coins[ind];
        return dp[ind][target] = 1e9;
    }
    // check dp table 
    if (dp[ind][target] != -1) return dp[ind][target];
    // define all possibilities
    int notPick = countCoins(dp, coins, ind-1, target);
    int pick = 1e9;
    if (coins[ind] <= target) pick = 1 + countCoins(dp, coins, ind, target-coins[ind]);
    return dp[ind][target] = min(pick, notPick);
}
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int> (amount+1, -1));
        int result = countCoins(dp, coins, n-1, amount);
        return result >= 1e9 ? -1 : result;
    }
};