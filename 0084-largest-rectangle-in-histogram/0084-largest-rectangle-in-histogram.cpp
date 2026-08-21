class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> st;
        // next smaller element
        vector<int> nse(n);
        for (int i = n-1; i >= 0; i--) {
            while (!st.empty() && heights[i] <= heights[st.top()]) st.pop();
            nse[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        // previous smaller element
        vector<int> pse(n);
        st = stack<int>();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[i] <= heights[st.top()]) st.pop();
            pse[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        // find max rectangle
        int maxArea = -1e9;
        for (int i = 0; i < n; i++) {
            int breadth = nse[i] - pse[i] - 1;
            maxArea = max(maxArea, heights[i] * breadth);
        }
        return maxArea;
    }
};