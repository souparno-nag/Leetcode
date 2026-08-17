class Solution {
    int maxProfitHelper(int ind, int buy, int capacity, vector<int>& prices, int n, vector<vector<vector<int>>>& dp) {
        if (capacity == 0 || ind == n) return 0;
        if (dp[ind][buy][capacity] != -1e9) return dp[ind][buy][capacity];
        if (buy) {
            return dp[ind][buy][capacity] = max(
                - prices[ind] + maxProfitHelper(ind+1, 0, capacity, prices, n, dp),
                maxProfitHelper(ind+1, 1, capacity, prices, n, dp)
            );
        } else {
            return dp[ind][buy][capacity] = max(
                prices[ind] + maxProfitHelper(ind+1, 1, capacity-1, prices, n, dp),
                maxProfitHelper(ind+1, 0, capacity, prices, n, dp)
            );
        }
    }
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int> (3, -1e9)));
        return maxProfitHelper(0, 1, 2, prices, n, dp);
    }
};