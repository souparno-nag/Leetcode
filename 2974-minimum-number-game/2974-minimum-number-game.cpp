class Solution {
public:
    vector<int> numberGame(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> arr(n);
        for (int i = 0; i < n; i+=2) {
            arr[i] = nums[i+1];
            arr[i+1] = nums[i];
        }
        return arr;
    }
};