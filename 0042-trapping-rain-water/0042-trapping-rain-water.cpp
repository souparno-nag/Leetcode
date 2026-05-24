class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> rightMax(n);
        // computing rightMax
        rightMax[n - 1] = height[n - 1];
        for (int i = n-2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }
        // compute total
        int total = 0, leftMax = INT_MIN;
        for (int i = 0; i < n; i++) {
            leftMax = max(leftMax, height[i]);
            if (height[i] < leftMax && height[i] < rightMax[i]) {
                total += (min(leftMax, rightMax[i]) - height[i]);
            }
        }
        return total;
    }
};