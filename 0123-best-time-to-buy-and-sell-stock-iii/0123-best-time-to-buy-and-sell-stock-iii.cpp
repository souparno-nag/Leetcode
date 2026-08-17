class Solution {
    int maxProfitHelper(int ind, int transactionNo, vector<vector<int>>& dp, vector<int>& prices, int n) {
        if (ind == n || transactionNo == 0) return 0;
        if (dp[ind][transactionNo] != -1e9) return dp[ind][transactionNo];
        if (transactionNo % 2 == 0) {
            return dp[ind][transactionNo] = max(
                maxProfitHelper(ind+1, transactionNo-1, dp, prices, n) - prices[ind],
                maxProfitHelper(ind+1, transactionNo, dp, prices, n)
            );
        } else {
            return dp[ind][transactionNo] = max(
                maxProfitHelper(ind+1, transactionNo-1, dp, prices, n) + prices[ind],
                maxProfitHelper(ind+1, transactionNo, dp, prices, n)
            );
        }
    }
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int> (5, -1e9));
        return maxProfitHelper(0, 4, dp, prices, n);
    }
};