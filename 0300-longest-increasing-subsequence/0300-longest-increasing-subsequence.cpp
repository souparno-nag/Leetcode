class Solution { 
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        for (int idx = n-1; idx >= 0; idx--) {
            for (int prev_idx = idx-1; prev_idx >= -1; prev_idx--) {
                int notTake = dp[idx+1][prev_idx+1];
                int take = 0;
                if (prev_idx == -1 || nums[prev_idx] < nums[idx]) {
                    take = dp[idx+1][idx+1] + 1;
                }
                dp[idx][prev_idx+1] = max(take, notTake);
            }
        }
        return dp[0][0];
    }
};