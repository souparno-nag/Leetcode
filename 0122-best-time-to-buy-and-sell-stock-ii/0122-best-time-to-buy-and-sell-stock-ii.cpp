class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> next(2, -1), curr(2, -1);
        // base case
        next[0] = next[1] = 0;
        // build the dp table
        for (int ind = n-1; ind >= 0; ind--) {
            for (int buy = 0; buy < 2; buy++) {
                int profit;
                if (buy) {
                    profit = max(
                        -prices[ind] + next[0], // buy
                        next[1] // don't buy
                    ); 
                } else {
                    profit = max(
                        prices[ind] + next[1], // sell
                        next[0] // don't sell
                    );
                }
                curr[buy] = profit;
            }
            next = curr;
        }
        return next[1];
    }
};