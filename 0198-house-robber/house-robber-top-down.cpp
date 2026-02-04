class Solution {
public:
    int maxNonAdjacentSum(int index, vector<int>& nums, vector<int>& dp) {
        if (index == 0) return nums[0];
        if (index < 0) return 0;

        if (dp[index] != -1) return dp[index];

        int pick = nums[index] + maxNonAdjacentSum(index-2, nums, dp);
        int notPick = maxNonAdjacentSum(index-1, nums, dp);

        return dp[index] = max(pick, notPick);
    }
    int rob(vector<int>& nums) {
        // this can be represented as maximum sum of non-adjacent elements
        int n = nums.size();
        vector<int> dp (n, -1);
        dp[0] = nums[0];

        return maxNonAdjacentSum(n-1, nums, dp);
    }
};
