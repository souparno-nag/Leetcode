class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        int prev = nums[0], prev2 = 0;

        for (int i = 1; i < n; i++) {
            int pick = nums[i] + (i > 1 ? prev2 : 0);
            int notPick = prev;

            int curr = max(pick, notPick);
            prev2 = prev;
            prev = curr;
        }

        return prev;
    }
};
