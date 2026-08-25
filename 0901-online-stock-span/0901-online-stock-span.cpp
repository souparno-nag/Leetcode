class StockSpanner {
    vector<int> arr;
    stack<int> st;
public:
    StockSpanner() {}
    
    int next(int price) {
        arr.push_back(price);
        while (!st.empty() && price >= arr[st.top()]) st.pop();
        int n = arr.size();
        int result = st.empty() ? n : n - 1 - st.top();
        st.push(n-1);
        return result;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */