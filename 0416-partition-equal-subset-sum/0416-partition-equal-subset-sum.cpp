class Solution {
public:
    bool checkPartitionSum(vector<int>& nums, int sum) {
        int n = nums.size();
        vector<bool> dp(sum+1, false);
        // define base case
        if (nums[0] <= sum) dp[nums[0]] = true;
        dp[0] = true;
        // form the nested loops
        for (int ind = 1; ind < n; ind++) {
            vector<bool> temp(sum+1, false);
            temp[0] = true;
            for (int target = 0; target <= sum; target++) {
                bool notTake = dp[target];
                bool take = (nums[ind] <= target) ? dp[target-nums[ind]] : false;
                temp[target] = notTake || take;
            }
            dp = temp;
        }
        return dp[sum];
    }
    bool canPartition(vector<int>& nums) {
        int n = nums.size(), sum = 0;
        for (int i = 0; i < n; i++) sum += nums[i];
        if (sum % 2 != 0) return false;
        int targetSum = sum/2;
        return checkPartitionSum(nums, targetSum);
    }
};