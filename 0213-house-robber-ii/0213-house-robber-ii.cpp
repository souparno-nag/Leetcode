class Solution {
public:
    int maxNonAdjacentSum(vector<int>& nums) {
        int n = nums.size();
        int prev = nums[0], prev2 = 0;
        for (int i = 1; i < n; i++) {
            int take = nums[i] + (i > 1 ? prev2 : 0);
            int notTake = prev;
            
            int curr = max(take, notTake);
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }
    int rob(vector<int>& nums) {
        vector<int> temp1, temp2;
        int n = nums.size();
        if (n == 1) return nums[0];
        for (int i = 0; i < n; i++) {
            if (i != 0) temp1.push_back(nums[i]);
            if (i != n-1) temp2.push_back(nums[i]);
        }
        return max(maxNonAdjacentSum(temp1), maxNonAdjacentSum(temp2));
    }
};