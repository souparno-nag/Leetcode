class MyQueue {
    stack<int> s1, s2;
    int size;
public:
    MyQueue() {
        size = 0;
    }
    
    void push(int x) {
        for (int i = 0; i < size; i++) {
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(x);
        for (int i = 0; i < size; i++) {
            s1.push(s2.top());
            s2.pop();
        }
        size++;
    }
    
    int pop() {
        if (size == 0) return -1;
        int top = s1.top();
        s1.pop();
        size--;
        return top;
    }
    
    int peek() {
        if (size == 0) return -1;
        return s1.top();
    }
    
    bool empty() {
        return (size == 0);
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */