class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<int> dp(2, 0), temp(2, 0);
        for (int ind = n-1; ind >= 0; ind--) {
            temp[1] = max(
                dp[0] - prices[ind],
                dp[1]
            );
            temp[0] = max(
                dp[1] + prices[ind] - fee,
                dp[0]
            );
            dp = temp;
        }
        return dp[1];
    }
};