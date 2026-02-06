class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if (n == 1) return 0;
        int left = 0, right = 0;
        int length_max = 0;
        while (right < n) {
            if (nums[right] <= k * (long long)nums[left]) {
                right++;
                length_max = max(length_max, right - left);
            } else {
                left++;
            }
        }
        return n - length_max;
    }
};