class Solution {
public:
    int first(vector<int>& arr, int target) {
        int n = arr.size();
        int low = 0, high = n-1;
        int ans = -1;
        while (low <= high) {
            int mid = (low + high)/2;
            if (arr[mid] == target) {
                ans = mid;
                high = mid-1;
            } else if (arr[mid] < target) {
                low = mid+1;
            } else {
                high = mid-1;
            }
        }
        return ans;
    }
    int last(vector<int>& arr, int target) {
        int n = arr.size();
        int low = 0, high = n-1;
        int ans = -1;
        while (low <= high) {
            int mid = (low + high)/2;
            if (arr[mid] == target) {
                ans = mid;
                low = mid+1;
            } else if (arr[mid] > target) {
                high = mid-1;
            } else {
                low = mid+1;
            }
        }
        return ans;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int lb = first(nums, target);
        int ub = last(nums, target);
        return {lb, ub};
    }
};