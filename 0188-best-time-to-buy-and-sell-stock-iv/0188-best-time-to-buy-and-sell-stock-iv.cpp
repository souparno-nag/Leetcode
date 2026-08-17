class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {        
        int n = prices.size();
        vector<int> dp(2*k+1, 0), temp(2*k+1, 0);
        for (int ind = n-1; ind >= 0; ind--) {
            for (int transactionNo = 1; transactionNo <= 2*k; transactionNo++) {
                if (transactionNo % 2 == 0) {
                    temp[transactionNo] = max(
                        dp[transactionNo-1] - prices[ind],
                        dp[transactionNo]
                    );
                } else {
                    temp[transactionNo] = max(
                        dp[transactionNo-1] + prices[ind],
                        dp[transactionNo]
                    );
                }
            }
            dp = temp;
        }
        return dp[2*k];
    }
};