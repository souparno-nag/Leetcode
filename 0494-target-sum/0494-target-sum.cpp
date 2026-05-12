class Solution {
public:
    int countWaysToTarget(vector<int>& nums, int ind, int sum) {
        // define base case
        if (ind == 0) {
            if ((sum + nums[ind] == 0) && (sum - nums[ind] == 0)) return 2;
            if (sum + nums[ind] == 0) return 1;
            else if (sum - nums[ind] == 0) return 1;
            return 0;
        }
        // define all possibilities
        int add = countWaysToTarget(nums, ind-1, sum-nums[ind]);
        int subtract = countWaysToTarget(nums, ind-1, sum+nums[ind]);
        return add + subtract;
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        return countWaysToTarget(nums, n-1, target);
    }
};