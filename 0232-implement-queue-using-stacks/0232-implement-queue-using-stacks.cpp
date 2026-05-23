class MyQueue {
    stack<int> s1, s2;
    int size;
public:
    MyQueue() {
        size = 0;
    }
    
    void push(int x) {
        s1.push(x);
        size++;
    }
    
    int pop() {
        if (size == 0) return -1;
        int top;
        if (s2.size() != 0) {
            top = s2.top();
        } else {
            while (s1.size()) {
                s2.push(s1.top());
                s1.pop();
            }
            top = s2.top();
        }
        s2.pop();
        size--;
        return top;
    }
    
    int peek() {
        if (size == 0) return -1;
        int top;
        if (s2.size() != 0) {
            top = s2.top();
        } else {
            while (s1.size()) {
                s2.push(s1.top());
                s1.pop();
            }
            top = s2.top();
        }
        return top;
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