class Solution {
public:
    void generateSubsequences(vector<int>& nums, int index, vector<int>& ds, vector<vector<int>>& result) {
        if (index == nums.size()) {
            result.push_back(ds);
            return;
        }
        ds.push_back(nums[index]);
        generateSubsequences(nums, index+1, ds, result);
        ds.pop_back();
        generateSubsequences(nums, index+1, ds, result);
        return;
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<int> ds;
        vector<vector<int>> result;
        generateSubsequences(nums, 0, ds, result);
        return result;
    }
};