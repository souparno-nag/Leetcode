class Solution {
public:
    int countCombinations(vector<int>& coins, int target) {
        int n = coins.size();
        vector<uint32_t> dp(target+1, 0), curr(target+1, 0);
        // base case
        for (int sum = 0; sum <= target; sum++) dp[sum] = (sum % coins[0] == 0);
        // build the table
        for (int ind = 1; ind < n; ind++) {
            for (int sum = 0; sum <= target; sum++) {
                uint32_t notPick = dp[sum];
                uint32_t pick = (coins[ind] <= sum) ? curr[sum-coins[ind]] : 0;
                curr[sum] = (pick + notPick);
            }
            dp = curr;
        }
        return (int) dp[target];
    }
    int change(int amount, vector<int>& coins) {
        return countCombinations(coins, amount);
    }
};