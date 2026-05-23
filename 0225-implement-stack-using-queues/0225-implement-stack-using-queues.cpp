class MyStack {
    queue<int> q;
    int size;
public:
    MyStack() {
        size = 0;
    }
    
    void push(int x) {
        q.push(x);
        for (int i = 0; i < size; i++) {
            q.push(q.front());
            q.pop();
        }
        size++;
    }
    
    int pop() {
        if (q.empty()) return -1;
        int top = q.front();
        q.pop();
        size--;
        return top;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return (size == 0);
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */