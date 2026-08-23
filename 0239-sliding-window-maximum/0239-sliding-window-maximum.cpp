class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> result;
        deque<int> d;   
        for (int i = 0; i < n; i++) {
            // dequeue elements that are out of window
            while(!d.empty() && d.front() <= i-k) d.pop_front();
            // remove elements that are smaller than current element
            while(!d.empty() && nums[d.back()] <= nums[i]) d.pop_back();
            // push element into queue
            d.push_back(i);
            // add max element to result
            if (i >= k-1) result.push_back(nums[d.front()]);
        }
        return result;
    }
};