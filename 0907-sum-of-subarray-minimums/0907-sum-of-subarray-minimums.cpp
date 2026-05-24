class Solution {
public:
    vector<int> nextSmallerElement(vector<int>& arr) {
        int n = arr.size();
        vector<int> nse(n);
        stack<int> st;
        for (int i = n-1; i >= 0; i--) {
            while (!st.empty() && arr[i] <= arr[st.top()]) st.pop();
            nse[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        return nse;
    }
    vector<int> prevSmallerElement(vector<int>& arr) {
        int n = arr.size();
        vector<int> pse(n);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[i] < arr[st.top()]) st.pop();
            pse[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        return pse;
    }
    int sumSubarrayMins(vector<int>& arr) {
        vector<int> pse = prevSmallerElement(arr);
        vector<int> nse = nextSmallerElement(arr);
        int total = 0, mod = 1e9+7;
        for (int i = 0; i < arr.size(); i++) {
            int left = i - pse[i], right = nse[i] - i;
            total = (total + (left * right * 1LL * arr[i])%mod)%mod;
        }
        return total;
    }
};