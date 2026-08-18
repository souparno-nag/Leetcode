class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int currBuy = 0, currNotBuy = 0, aheadBuy = 0, aheadNotBuy = 0;
        for (int ind = n-1; ind >= 0; ind--) {
            currNotBuy = max(
                aheadBuy + prices[ind],
                aheadNotBuy
            );
            currBuy = max(
                aheadNotBuy - prices[ind] - fee,
                aheadBuy
            );
            aheadNotBuy = currNotBuy;
            aheadBuy = currBuy;
        }
        return aheadBuy;
    }
};