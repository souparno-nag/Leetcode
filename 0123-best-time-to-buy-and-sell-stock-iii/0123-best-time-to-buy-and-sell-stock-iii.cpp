class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n+1, vector<int> (5, 0));
        for (int ind = n-1; ind >= 0; ind--) {
            for (int transactionNo = 1; transactionNo <= 4; transactionNo++) {
                if (transactionNo % 2 == 0) {
                    dp[ind][transactionNo] = max(
                        dp[ind+1][transactionNo-1] - prices[ind],
                        dp[ind+1][transactionNo]
                    );
                } else {
                    dp[ind][transactionNo] = max(
                        dp[ind+1][transactionNo-1] + prices[ind],
                        dp[ind+1][transactionNo]
                    );
                }
            }
        }
        return dp[0][4];
    }
};