class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int m = accounts.size(), n = accounts[0].size();
        int max_wealth = 0;
        for (int i = 0; i < m; i++) {
            int wealth = 0;
            for (int j = 0; j < n; j++) {
                wealth += accounts[i][j];
            }
            max_wealth = max(max_wealth, wealth);
        }
        return max_wealth;
    }
};