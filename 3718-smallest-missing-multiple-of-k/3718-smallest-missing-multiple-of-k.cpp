class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> us(nums.begin(), nums.end());
        int c = 1;
        while (true) {
            if (us.find(c*k) == us.end()) break;
            c++;
        }
        return c*k;
    }
};