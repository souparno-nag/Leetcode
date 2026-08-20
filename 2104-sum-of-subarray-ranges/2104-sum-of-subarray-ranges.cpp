class Solution {
    long long sumOfMax(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        // find next greater element
        vector<int> nge(n);
        for (int i = n-1; i >= 0; i--) {
            while (!st.empty() && nums[i] > nums[st.top()]) st.pop();
            nge[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        // find previous greater element
        vector<int> pge(n);
        st = stack<int>();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[i] >= nums[st.top()]) st.pop();
            pge[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        // calculate sum
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            int left = i - pge[i], right = nge[i] - i;
            sum += ((long long)nums[i] * left * right);
        }
        return sum;
    }
    long long sumOfMin(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        // find next smallest element
        vector<int> nse(n);
        for (int i = n-1; i >= 0; i--) {
            while (!st.empty() && nums[i] < nums[st.top()]) st.pop();
            nse[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        // find previous smallest element
        vector<int> pse(n);
        st = stack<int>();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[i] <= nums[st.top()]) st.pop();
            pse[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        // calculate sum
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            int left = i - pse[i], right = nse[i] - i;
            sum += ((long long)nums[i] * left * right);
        }
        return sum;
    }
public:
    long long subArrayRanges(vector<int>& nums) {
        return sumOfMax(nums) - sumOfMin(nums);
    }
};