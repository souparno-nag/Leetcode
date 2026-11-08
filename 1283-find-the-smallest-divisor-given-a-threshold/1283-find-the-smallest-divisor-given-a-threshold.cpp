class Solution {
    long long sumOfDivisions(vector<int>& nums, int d) {
        long long sum = 0;
        for (int x : nums) sum += (x+d-1)/d; // integer ceiling (x/d)
        return sum;
    }
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        if (nums.size() > threshold) return -1;
        int low = 1, high = *max_element(nums.begin(), nums.end());
        while (low <= high) {
            int mid = (low + high)/2;
            if (sumOfDivisions(nums, mid) <= threshold) high = mid-1;
            else low = mid+1;
        }
        return low;
    }
};