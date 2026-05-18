class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n+1, vector<int>(2, -1));
        // base case
        dp[n][0] = dp[n][1] = 0;
        // build the dp table
        for (int ind = n-1; ind >= 0; ind--) {
            for (int buy = 0; buy < 2; buy++) {
                int profit;
                if (buy) {
                    profit = max(
                        -prices[ind] + dp[ind+1][0], // buy
                        dp[ind+1][1] // don't buy
                    ); 
                } else {
                    profit = max(
                        prices[ind] + dp[ind+1][1], // sell
                        dp[ind+1][0] // don't sell
                    );
                }
                dp[ind][buy] = profit;
            }
        }
        return dp[0][1];
    }
};