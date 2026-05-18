class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int minPrice = prices[0], profit = 0;
        for (int i = 0; i < n; i++) {
            int p = prices[i] - minPrice;
            profit = max(profit, p);
            minPrice = min(minPrice, prices[i]);
        }
        return profit;
    }
};