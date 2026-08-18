class Solution {
    int maxProfitHelper(int ind, int buy, vector<int>& prices, int n, vector<vector<int>>& dp) {
        if (ind >= n) return 0;
        if (dp[ind][buy] != -1e9) return dp[ind][buy];
        if (buy) {
            return dp[ind][buy] = max(
                maxProfitHelper(ind+1, 0, prices, n, dp) - prices[ind],
                maxProfitHelper(ind+1, 1, prices, n, dp)
            );
        } else {
            return dp[ind][buy] = max (
                maxProfitHelper(ind+2, 1, prices, n, dp) + prices[ind],
                maxProfitHelper(ind+1, 0, prices, n, dp)
            );
        }
    }
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n+2, vector<int>(2, 0));
        for (int ind = n-1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                if (buy) {
                    dp[ind][buy] = max(
                        dp[ind+1][0] - prices[ind],
                        dp[ind+1][1]
                    );
                } else {
                    dp[ind][buy] = max(
                        dp[ind+2][1] + prices[ind],
                        dp[ind+1][0]
                    );
                }
            }
        }
        return dp[0][1];
    }
};