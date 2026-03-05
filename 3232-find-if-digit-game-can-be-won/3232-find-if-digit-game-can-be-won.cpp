class Solution {
public:
    bool canAliceWin(vector<int>& nums) {
        int single_dig = 0, double_dig = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < 10) {
                single_dig += nums[i];
            } else {
                double_dig += nums[i];
            }
        }
        return !(single_dig == double_dig);
    }
};