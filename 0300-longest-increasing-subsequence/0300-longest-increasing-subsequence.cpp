class Solution { 
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> curr(n+1, 0), next(n+1, 0);
        for (int idx = n-1; idx >= 0; idx--) {
            for (int prev_idx = idx-1; prev_idx >= -1; prev_idx--) {
                int notTake = next[prev_idx+1];
                int take = 0;
                if (prev_idx == -1 || nums[prev_idx] < nums[idx]) {
                    take = next[idx+1] + 1;
                }
                curr[prev_idx+1] = max(take, notTake);
            }
            next = curr;
        }
        return next[0];
    }
};