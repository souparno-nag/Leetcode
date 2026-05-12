class Solution {
public:
    int binarySearch(vector<int>& nums, int low, int high, int target) {
        if (low > high) return low;
        int mid = (low + high)/2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) return binarySearch(nums, low, mid-1, target);
        else return binarySearch(nums, mid+1, high, target);
    }
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        return binarySearch(nums, 0, n-1, target);
    }
};