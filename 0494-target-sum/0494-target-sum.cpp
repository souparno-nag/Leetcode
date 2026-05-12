class Solution {
public:
    int countWaysToTarget(vector<int>& nums, int target) {
        int n = nums.size();
        int totalSum = 0;
        for (int i = 0; i < n; i++) totalSum += nums[i];
        if (abs(target) > totalSum) return 0;
        vector<vector<int>> dp(n, vector<int>(2*totalSum+1, 0));
        int offset = totalSum;
        // define base case
        dp[0][offset+nums[0]] += 1;
        dp[0][offset-nums[0]] += 1;
        // build the table
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= 2 * totalSum; ++j) {
                if (dp[i - 1][j] != 0) {
                    int ways = dp[i - 1][j];
                    // Add nums[i]
                    int addIdx = j + nums[i];
                    if (addIdx <= 2 * totalSum)
                        dp[i][addIdx] += ways;
                    // Subtract nums[i]
                    int subIdx = j - nums[i];
                    if (subIdx >= 0)
                        dp[i][subIdx] += ways;
                }
            }
        }
        return dp[n - 1][offset + target];
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        return countWaysToTarget(nums, target);
    }
};