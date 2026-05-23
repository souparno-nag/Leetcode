class MinStack {
    stack<int64_t> st;
    int64_t min_val;
public:
    MinStack() {
        min_val = 0;
    }
    
    void push(int val) {
        if (st.empty()) {
            min_val = val;
            st.push(val);
            return;
        }
        if (val < min_val) {
            int64_t new_value = 2LL*val - min_val;
            st.push(new_value);
            min_val = val;
        } else {
            st.push(val);
        }
    }
    
    void pop() {
        if (st.empty()) return;
        if (st.top() < min_val) {
            min_val = 2*min_val - st.top();
        }
        st.pop();
    }
    
    int top() {
        if (st.top() < min_val) return min_val;
        return (int) st.top();
    }
    
    int getMin() {
        return min_val;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */