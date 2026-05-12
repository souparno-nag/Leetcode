class Solution {
public:
    int countCombinations(vector<int>& coins, int target) {
        int n = coins.size();
        vector<vector<uint32_t>> dp(n, vector<uint32_t> (target+1, 0));
        // base case
        for (int sum = 0; sum <= target; sum++) dp[0][sum] = (sum % coins[0] == 0);
        // build the table
        for (int ind = 1; ind < n; ind++) {
            for (int sum = 0; sum <= target; sum++) {
                uint32_t notPick = dp[ind-1][sum];
                uint32_t pick = (coins[ind] <= sum) ? dp[ind][sum-coins[ind]] : 0;
                dp[ind][sum] = (pick + notPick);
            }
        }
        return (int) dp[n-1][target];
    }
    int change(int amount, vector<int>& coins) {
        return countCombinations(coins, amount);
    }
};