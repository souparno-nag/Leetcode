class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0, high = nums.size()-1;
        while (low <= high) {
            int mid = (low + high)/2;
            if (nums[mid] == target) return true;
            // mid index val is equal to both low and high
            if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
                low++;
                high--;
                continue;
            }
            // check whether left side is sorted
            if (nums[low] <= nums[mid]) {
                // present within sorted left
                if (nums[low] <= target && target < nums[mid]) high = mid-1;
                // not present in sorted left
                else low = mid+1;
            }
            // when left side is not sorted, means right side is sorted
            else {
                // present in sorted right
                if (nums[mid] < target && target <= nums[high]) low = mid+1;
                // not present in sorted right
                else high = mid-1;
            }
        }
        return false;
    }
};