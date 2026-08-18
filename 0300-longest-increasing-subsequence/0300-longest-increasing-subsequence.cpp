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
        vector<vector<int>> dp(n, vector<int> (n+1, -1));
        return getLIS(0, -1, nums, n, dp);
    }
};