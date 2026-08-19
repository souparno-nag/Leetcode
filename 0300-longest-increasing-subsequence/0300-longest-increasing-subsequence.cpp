class Solution { 
    int getLIS(int idx, int prev_idx, vector<int>& nums, int n, vector<vector<int>>& dp) {
        if (idx == n) return 0;
        if (dp[idx][prev_idx+1] != -1) return dp[idx][prev_idx+1];
        int notTake = getLIS(idx+1, prev_idx, nums, n, dp);
        int take = 0;
        if (prev_idx == -1 || nums[idx] > nums[prev_idx]) {
            take = 1 + getLIS(idx+1, idx, nums, n, dp);
        }
        return dp[idx][prev_idx+1] = max(notTake, take);
    }
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