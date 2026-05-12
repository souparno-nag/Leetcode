class Solution {
public:
    int countWaysToTarget(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> dp (n, vector<int> (target+1, 0));
        dp[0][0] = 1;
        if (nums[0] <= target) dp[0][nums[0]] += 1;
        for (int ind = 1; ind < n; ind++) {
            for (int sum = 0; sum <= target; sum++) {
                int notPick = dp[ind-1][sum];
                int pick = (nums[ind] <= sum) ? dp[ind-1][sum-nums[ind]] : 0;
                dp[ind][sum] = pick + notPick;
            }
        }
        return dp[n - 1][target];
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int totalSum = 0;
        for (int i = 0; i < n; i++) totalSum += nums[i];
        int diff = (totalSum - target);
        if (diff < 0 || diff%2 != 0) return 0;
        return countWaysToTarget(nums, diff/2);
    }
};