class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size()-1;
        int minVal = INT_MAX;
        while (low <= high) {
            int mid = (low + high)/2;
            if (nums[low] <= nums[high]) {
                minVal = min(minVal, nums[low]);
                break;
            }
            if (nums[low] <= nums[mid]) {
                minVal = min(minVal, nums[low]);
                low = mid+1;
            } else {
                minVal = min(minVal, nums[mid]);
                high = mid-1;
            }
        }
        return minVal;
    }
};