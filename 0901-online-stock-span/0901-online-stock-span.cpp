class StockSpanner {
    stack<pair<int, int>> st;
    int ind = -1;
public:
    StockSpanner() {
        ind = -1;
    }
    
    int next(int price) {
        ind++;
        while (!st.empty() && price >= st.top().first) st.pop();
        int result = ind - (st.empty() ? -1 : st.top().second);
        st.push({price, ind});
        return result;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */