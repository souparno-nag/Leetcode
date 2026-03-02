class Solution {
public:
    void generatePowerSet (vector<int> current, int i, int n, vector<vector<int>>& result, vector<int>& nums) {
        result.push_back(current);
        for (int j = i; j < n; j++) {
            if (j > i && nums[j] == nums[j-1]) continue;
            current.push_back(nums[j]);
            generatePowerSet(current, j+1, n, result, nums);
            current.pop_back();
        }
        return;
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> curr;
        generatePowerSet(curr, 0, n, result, nums);
        return result;
    }
};