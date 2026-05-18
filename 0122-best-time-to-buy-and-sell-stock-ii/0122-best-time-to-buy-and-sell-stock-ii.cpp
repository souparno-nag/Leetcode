class Solution {
public:
    int findMaxProfit(vector<int>& prices, int ind, int buy, vector<vector<int>>& dp) {
        // base case
        if (ind == prices.size()) return 0;
        // check dp table
        if (dp[ind][buy] != -1) return dp[ind][buy];
        int profit;
        // define all possibilities
        if (buy) {
            profit = max(
                -prices[ind] + findMaxProfit(prices, ind+1, 0, dp), // buy
                findMaxProfit(prices, ind+1, 1, dp) // don't buy
            );
        } else {
            profit = max(
                prices[ind] + findMaxProfit(prices, ind+1, 1, dp), // sell
                findMaxProfit(prices, ind+1, 0, dp) // don't sell
            );
        }
        return dp[ind][buy] = profit;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return findMaxProfit(prices, 0, 1, dp);
    }
};