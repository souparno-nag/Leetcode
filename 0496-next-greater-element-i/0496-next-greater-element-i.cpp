class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums2.size();
        vector<int> nge(n);
        stack<int> st;
        for (int i = n-1; i >= 0; i--) {
            while (!st.empty() && nums2[i] > st.top()) st.pop();
            if (!st.empty()) nge[i] = st.top();
            else nge[i] = -1;
            st.push(nums2[i]);
        }
        int m = nums1.size();
        vector<int> result(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (nums1[i] == nums2[j]) {
                    result[i] = nge[j];
                    break;
                }
            }
        }
        return result;
    }
};