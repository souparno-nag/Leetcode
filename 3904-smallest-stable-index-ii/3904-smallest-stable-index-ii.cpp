class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> suffix(n);
        // calculating suffix minimum
        int min_val = INT_MAX;
        for (int i = n-1; i >= 0; i--) {
            min_val = min(min_val, nums[i]);
            suffix[i] = min_val;
        }
        // find min instability
        int max_val = INT_MIN, instability = INT_MAX;
        for (int i = 0; i < n; i++) {
            max_val = max(max_val, nums[i]);
            instability = min(instability, max_val-suffix[i]);
            if (instability <= k) return i;
        }
        return -1;
    }
};