class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            int minm = nums[i], maxm = nums[i];
            for (int j = i+1; j < n; j++) {
                minm = min(minm, nums[j]);
                maxm = max(maxm, nums[j]);
                sum += (maxm-minm);
            }
        }
        return sum;
    }
};