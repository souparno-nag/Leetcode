class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int max_len = 0;

        for (int i = 0; i < n; i++) {
            unordered_set<int> oddSet;
            unordered_set<int> evenSet;
            for (int j = i; j < n; j++) {
                if (nums[j] % 2 == 0) {
                    evenSet.insert(nums[j]);
                } else {
                    oddSet.insert(nums[j]);
                }
                if (oddSet.size() == evenSet.size()) {
                    max_len = max(max_len, j-i+1);
                }
            }
        }
        return max_len;
    }
};