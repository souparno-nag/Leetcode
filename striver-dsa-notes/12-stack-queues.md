# Stack / Queues — Striver's A2Z DSA Sheet Notes

Section 12 of 20 · 30 problems · 28 with video, 2 without · [All sections](00-index.md)

[← Sliding Window / 2 Pointer](11-sliding-window-2-pointer.md) | [Binary Trees →](13-binary-trees.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Implementation**

1. [Implement Stack using Arrays](#p247) — Core
2. [Implement Queue using Arrays](#p248) — Core
3. [Implement Stack using Queue](#p249) — Core
4. [Implement Queue using Stack](#p250) — Core
5. [Implement stack using Linkedlist](#p251) — Core
6. [Implement queue using Linkedlist](#p252) — Core
7. [Balanced Paranthesis](#p253) — Core

**Prefix, Infix and Postfix Conversions**

8. [Infix to Postfix Conversion](#p254) — Core
9. [Infix to Prefix Conversion](#p255) — Core
10. [Prefix to Infix Conversion](#p256) — Core
11. [Prefix to Postfix Conversion](#p257) — Core
12. [Postfix to Infix Conversion](#p258) — Core
13. [Postfix to Prefix Conversion](#p259) — Core

**Monotonic Stack**

14. [Next Greater Element](#p260) — Core
15. [Next Greater Element - 2](#p261) — Core
16. [Asteroid Collision](#p262) — Core
17. [Sum of Subarray Minimums](#p263) — Core
18. [Sum of Subarray Ranges](#p264) — Core
19. [Remove K Digits](#p265) — Core
20. [Next Smaller Element](#p266) — Core · *no video*

**FAQs**

21. [Implement Min Stack](#p267) — Core
22. [Sliding Window Maximum](#p268) — Pro
23. [Trapping Rainwater](#p269) — Pro
24. [Largest rectangle in a histogram](#p270) — Pro
25. [Maximum Rectangles](#p271) — Pro
26. [Stock span problem](#p272) — Core
27. [Celebrity Problem](#p273) — Core
28. [LRU Cache](#p274) — Pro
29. [LFU Cache](#p275) — Pro
30. [Number of Greater Elements to the Right](#p276) — Core · *no video*

---

## Implementation

<a id="p247"></a>

### 1. Implement Stack using Arrays

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Implementation | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/implement-a-stack-using-an-array) | [Watch from 11:17](https://youtu.be/tqQ5fTamIN4?t=677) |

#### Problem Statement
Implement a **stack** (LIFO: last in, first out) on top of a fixed-size array, supporting `push(x)`, `pop()`, `top()` and `size()`. You'd normally use the library (`std::stack`, `java.util.Stack`/`ArrayDeque`). Interviewers ask this to see how it works underneath. It's usually a pen-and-paper round.

```text
push 4, pop, push 5, push 6, push 10   ->   stack (bottom→top) = 5 6 10, size = 3, top = 10
```

#### Approach: Array + `top` index (as in the video)
An array needs a **fixed capacity**, so ask the interviewer for the maximum size (10 in the video). Keep `top = −1`, meaning empty.

| op | action |
|---|---|
| `push(x)` | `top++`, then `st[top] = x`. Check overflow (`top == cap − 1`) if asked |
| `pop()` | if not empty, `top−−`. The old value stays in the array but no longer counts |
| `top()` | `st[top]` if `top != −1` |
| `size()` | `top + 1`, which is 0 when empty |

Dry run:
- `push 4`: top = 0.
- `pop`: top = −1. The 4 is still physically in the array but logically gone.
- `push 5, 6, 10`: top = 2, so `size = 3` and `top() = st[2] = 10`.

**Complexity:**
- Time: O(1) for every operation.
- Space: O(capacity), fixed in advance. That's the drawback of arrays, since unused slots are wasted.

**C++**
```cpp
class ArrayStack {
    int cap;
    int top_;
    vector<int> st;
public:
    ArrayStack(int capacity = 10) : cap(capacity), top_(-1), st(capacity) {}
    void push(int x) {
        if (top_ == cap - 1) { cout << "Stack overflow\n"; return; }
        st[++top_] = x;
    }
    int pop() {
        if (top_ == -1) { cout << "Stack empty\n"; return -1; }
        return st[top_--];
    }
    int top() {
        if (top_ == -1) { cout << "Stack empty\n"; return -1; }
        return st[top_];
    }
    int size() { return top_ + 1; }
    bool isEmpty() { return top_ == -1; }
};
```

**Java**
```java
class ArrayStack {
    private final int cap;
    private int top = -1;
    private final int[] st;
    ArrayStack(int capacity) { cap = capacity; st = new int[capacity]; }
    void push(int x) {
        if (top == cap - 1) { System.out.println("Stack overflow"); return; }
        st[++top] = x;
    }
    int pop() {
        if (top == -1) { System.out.println("Stack empty"); return -1; }
        return st[top--];
    }
    int top() {
        if (top == -1) { System.out.println("Stack empty"); return -1; }
        return st[top];
    }
    int size() { return top + 1; }
    boolean isEmpty() { return top == -1; }
}
```

#### Edge Cases & Pitfalls
- Agree with the interviewer on what `pop`/`top` should do when the stack is empty: return −1, throw, or print.
- Popping doesn't erase anything. `top` alone defines the contents.

#### Key Takeaways
- A stack is just an array plus one moving index. Everything is O(1); the cost is the fixed capacity.

[↑ Contents](#contents) · [Next →](#p248)

---

<a id="p248"></a>

### 2. Implement Queue using Arrays

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Implementation | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/implement-a-queue-using-an-array) | [Watch from 19:32](https://youtu.be/tqQ5fTamIN4?t=1172) |

#### Problem Statement
Implement a **queue** (FIFO: first in, first out) on a fixed-size array, supporting `push(x)`, `pop()`, `top()`/`front()` and `size()`.

```text
cap 4: push 3, push 2, push 4, pop, pop, push 2, push 3   ->   queue (front→back) = 4 2 3
```

#### Approach: Circular array with `start`, `end`, `currSize` (as in the video)
- **Why two pointers.** A queue inserts at one end and removes from the other, so it needs `start` (front) and `end` (back), both initially −1, plus `currSize`.
- **Why it wraps.** After some pops, the free space sits at the **front** of the array. Moving with `(i + 1) % cap` reuses it, which makes the array **circular**.

| op | action |
|---|---|
| `push(x)` | if `currSize == cap`, it's full. If empty, `start = end = 0`; else `end = (end + 1) % cap`. Then `q[end] = x`, `currSize++` |
| `pop()` | if empty, error. Save `q[start]`. If `currSize == 1`, reset `start = end = −1`; else `start = (start + 1) % cap`. `currSize−−`, then return the saved value |
| `top()` | `q[start]` if not empty |
| `size()` | `currSize` |

Dry run (cap 4):
- `push 3, 2, 4`: indices 0, 1, 2, so start = 0 and end = 2.
- `pop, pop`: start = 2.
- `push 2`: end = 3.
- `push 3`: end = (3 + 1) % 4 = **0**, wrapping to the front.
- Queue front→back: 4 2 3.

**Complexity:**
- Time: O(1) per operation.
- Space: O(capacity), fixed.

**C++**
```cpp
class ArrayQueue {
    int cap, currSize, start, end;
    vector<int> q;
public:
    ArrayQueue(int capacity = 10) : cap(capacity), currSize(0), start(-1), end(-1), q(capacity) {}
    void push(int x) {
        if (currSize == cap) { cout << "Queue full\n"; return; }
        if (currSize == 0) start = end = 0;
        else end = (end + 1) % cap;
        q[end] = x;
        currSize++;
    }
    int pop() {
        if (currSize == 0) { cout << "Queue empty\n"; return -1; }
        int el = q[start];
        if (currSize == 1) start = end = -1;           // queue becomes empty: reset
        else start = (start + 1) % cap;
        currSize--;
        return el;
    }
    int top() {
        if (currSize == 0) { cout << "Queue empty\n"; return -1; }
        return q[start];
    }
    int size() { return currSize; }
};
```

**Java**
```java
class ArrayQueue {
    private final int cap;
    private int currSize = 0, start = -1, end = -1;
    private final int[] q;
    ArrayQueue(int capacity) { cap = capacity; q = new int[capacity]; }
    void push(int x) {
        if (currSize == cap) { System.out.println("Queue full"); return; }
        if (currSize == 0) start = end = 0;
        else end = (end + 1) % cap;
        q[end] = x;
        currSize++;
    }
    int pop() {
        if (currSize == 0) { System.out.println("Queue empty"); return -1; }
        int el = q[start];
        if (currSize == 1) start = end = -1;
        else start = (start + 1) % cap;
        currSize--;
        return el;
    }
    int top() {
        if (currSize == 0) { System.out.println("Queue empty"); return -1; }
        return q[start];
    }
    int size() { return currSize; }
}
```

#### Edge Cases & Pitfalls
- **Without the modulo, a non-circular array "fills up"** even though slots at the front are free.
- Keep `currSize` explicitly. With only `start` and `end`, a full queue and an empty one can look identical (`start == end`).
- Read the front value **before** resetting the pointers on the last pop.

#### Key Takeaways
- A queue on an array is a **circular buffer**: two indices advanced with `% cap`, plus a size counter.

[↑ Contents](#contents) · [← Previous](#p247) · [Next →](#p249)

---

<a id="p249"></a>

### 3. Implement Stack using Queue

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Implementation | Core | No | [LeetCode](https://leetcode.com/problems/implement-stack-using-queues/) | [Watch from 44:59](https://youtu.be/tqQ5fTamIN4?t=2699) |

#### Problem Statement
Implement a **stack** (LIFO) using only **queue** operations: push to back, pop from front, peek front, size and empty. Support `push`, `pop`, `top` and `empty`.

```text
push 4, push 9, push 2, push 5, top -> 5, pop -> 5, pop -> 2, top -> 9
```

#### Approach: One queue, rotated after each push (as in the video)
A queue gives back the **oldest** element, but a stack needs the **newest**. So after pushing `x`, rotate the queue: take the `size − 1` elements that were already there and move each one from the front to the back. Now `x` is at the front, and the queue's front-to-back order is the stack's top-to-bottom order.

Dry run:
- push 4: `[4]`.
- push 9: `[4,9]`, rotate once, giving `[9,4]`.
- push 2: `[9,4,2]`, rotate twice, giving `[2,9,4]`.
- push 5: `[5,2,9,4]`.
- `top = 5`. Pop gives 5, then pop gives 2, so `top = 9`.

**Complexity:**
- `push`: O(n), where n is the current size.
- `pop`, `top`, `empty`: O(1).
- Space: O(n).

**C++**
```cpp
class MyStack {
    queue<int> q;
public:
    void push(int x) {
        int s = q.size();
        q.push(x);
        for (int i = 0; i < s; i++) {        // move the older elements behind x
            q.push(q.front());
            q.pop();
        }
    }
    int pop() {
        int el = q.front();
        q.pop();
        return el;
    }
    int top() { return q.front(); }
    bool empty() { return q.empty(); }
    int size() { return q.size(); }
};
```

**Java**
```java
class MyStack {
    private final Queue<Integer> q = new LinkedList<>();
    void push(int x) {
        int s = q.size();
        q.add(x);
        for (int i = 0; i < s; i++) q.add(q.remove());
    }
    int pop() { return q.remove(); }
    int top() { return q.peek(); }
    boolean empty() { return q.isEmpty(); }
    int size() { return q.size(); }
}
```

#### Edge Cases & Pitfalls
- Rotate exactly the number of elements that were present **before** `x` was pushed. Rotating `size` times after the push puts `x` back at the end.
- The cost could instead be moved to `pop`, with O(1) push and O(n) pop. Choose based on which operation is more frequent.

#### Key Takeaways
- Reversing order with a single queue is a rotation: re-enqueue everything that was ahead of the newcomer.

[↑ Contents](#contents) · [← Previous](#p248) · [Next →](#p250)

---

<a id="p250"></a>

### 4. Implement Queue using Stack

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Implementation | Core | No | [LeetCode](https://leetcode.com/problems/implement-queue-using-stacks/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/implement-a-queue-using-stacks) | [Watch from 51:08](https://youtu.be/tqQ5fTamIN4?t=3068) |

#### Problem Statement
Implement a **queue** (FIFO) using only **stack** operations: push, pop, top, size and empty. Support `push`, `pop`, `peek`/`top` and `empty`.

```text
push 4, push 2, push 3, push 5, top -> 4, pop, pop, push 6, top -> 3
```

#### Approach 1: Two stacks, expensive push (as in the video)
Keep `s1` so that **its top is always the queue's front**. To push `x`:
1. Move everything from `s1` to `s2`.
2. Push `x` onto `s1`. It's now at the bottom.
3. Move everything back from `s2` to `s1`.

After this, `top`/`pop` on `s1` are exactly the queue's front.

Dry run:
- push 4: `s1 = [4]`.
- push 2: move 4 across, push 2, move 4 back, so `s1` = 2, 4 from bottom to top. The top is 4.
- push 3, push 5: `s1` = 5, 3, 2, 4 from bottom to top.
- `top` gives 4. Pop, pop leaves 5, 3.
- push 6: 6, 5, 3, so `top` gives **3**.

**Complexity:**
- `push`: O(2n).
- `pop`, `top`: O(1).
- Space: O(2n), for two stacks.

This is good when pushes are rare.

**C++**
```cpp
class QueueTwoStacksPushHeavy {
    stack<int> s1, s2;
public:
    void push(int x) {
        while (!s1.empty()) { s2.push(s1.top()); s1.pop(); }   // 1. s1 -> s2
        s1.push(x);                                             // 2. x at the bottom
        while (!s2.empty()) { s1.push(s2.top()); s2.pop(); }   // 3. s2 -> s1
    }
    int pop() {
        int el = s1.top();
        s1.pop();
        return el;
    }
    int top() { return s1.top(); }
    bool empty() { return s1.empty(); }
    int size() { return s1.size(); }
};
```

**Java**
```java
class QueueTwoStacksPushHeavy {
    private final Deque<Integer> s1 = new ArrayDeque<>(), s2 = new ArrayDeque<>();
    void push(int x) {
        while (!s1.isEmpty()) s2.push(s1.pop());
        s1.push(x);
        while (!s2.isEmpty()) s1.push(s2.pop());
    }
    int pop() { return s1.pop(); }
    int top() { return s1.peek(); }
    boolean empty() { return s1.isEmpty(); }
    int size() { return s1.size(); }
}
```

#### Approach 2: Two stacks, amortised O(1) (as in the video)
When pushes are frequent, make **push cheap** and pay only when needed:
- `push(x)`: `s1.push(x)`, always O(1).
- `pop()`/`top()`:
  - if `s2` is **non-empty**, its top is the queue's front;
  - if `s2` is empty, move **everything** from `s1` to `s2`. This reverses the order, so the oldest element lands on top. Then use `s2.top()`.

Elements in `s2` are already in queue order, so a transfer only happens when `s2` runs out.

Dry run:
- Push 2, 3, 4, 5 into `s1`.
- `top`: `s2` is empty, so transfer. Now `s2` (top first) is 2, 3, 4, 5, and `top` = 2.
- `pop` removes 2.
- `push 1` goes into `s1`.
- Pops give 3, 4, 5 straight from `s2`.
- The next `top` finds `s2` empty, transfers the 1, and returns 1.

**Complexity:**
- `push`: O(1).
- `pop`, `top`: amortised O(1), occasionally O(n). Each element is moved from `s1` to `s2` at most once.
- Space: O(2n).

The video's on-screen pseudocode shows `S2.push(x)` for push, but the dry run (and correctness) needs `s1.push(x)`.

**C++**
```cpp
class MyQueue {
    stack<int> s1, s2;                       // s1: input, s2: output (front on top)
    void transfer() {
        if (s2.empty())
            while (!s1.empty()) { s2.push(s1.top()); s1.pop(); }
    }
public:
    void push(int x) { s1.push(x); }
    int pop() {
        transfer();
        int el = s2.top();
        s2.pop();
        return el;
    }
    int peek() {
        transfer();
        return s2.top();
    }
    bool empty() { return s1.empty() && s2.empty(); }
    int size() { return s1.size() + s2.size(); }
};
```

**Java**
```java
class MyQueue {
    private final Deque<Integer> s1 = new ArrayDeque<>(), s2 = new ArrayDeque<>();
    private void transfer() {
        if (s2.isEmpty())
            while (!s1.isEmpty()) s2.push(s1.pop());
    }
    void push(int x) { s1.push(x); }
    int pop() { transfer(); return s2.pop(); }
    int peek() { transfer(); return s2.peek(); }
    boolean empty() { return s1.isEmpty() && s2.isEmpty(); }
    int size() { return s1.size() + s2.size(); }
}
```

#### Edge Cases & Pitfalls
- In approach 2, **only transfer when `s2` is empty**. Transferring while `s2` still holds elements would bury older elements under newer ones and break FIFO.
- `empty()` must check **both** stacks.

#### Key Takeaways
- Two stacks reverse the order twice and give FIFO.
- The input/output-stack split gives amortised O(1) for every operation, a classic amortised-analysis example.

[↑ Contents](#contents) · [← Previous](#p249) · [Next →](#p251)

---

<a id="p251"></a>

### 5. Implement stack using Linkedlist

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Implementation | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/implement-a-stack-using-a-linked-list) | [Watch from 32:13](https://youtu.be/tqQ5fTamIN4?t=1933) |

#### Problem Statement
Implement a **stack** using a **singly linked list**, supporting `push`, `pop`, `top`, `size` and `isEmpty`, with no fixed capacity.

```text
push 2, push 3, push 4, top -> 4, pop, top -> 3, size -> 2
```

#### Approach: Insert and delete at the head (as in the video)
- **Why a linked list.** Arrays need a capacity fixed in advance, while linked-list nodes are allocated as needed, which makes the stack **dynamic**.
- **Why the head.** The head is the only end where both insertion and deletion are O(1) in a singly linked list. So treat **the head as the stack's top**:
  - `push(x)`: `node = new Node(x)`, `node->next = top`, `top = node`, `size++`.
  - `pop()`: `temp = top`, `top = top->next`, free `temp`, `size−−`.
  - `top()`: `top->data`.

Dry run:
- push 2, 3, 4: the list is 4 → 3 → 2, and top points at 4.
- pop removes 4, so the list is 3 → 2 and `top()` = 3.

**Complexity:**
- Time: O(1) for every operation.
- Space: O(n). It's dynamic, using only what's needed.

**C++**
```cpp
class LLStack {
    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(nullptr) {}
    };
    Node* top_ = nullptr;
    int sz = 0;
public:
    void push(int x) {
        Node* node = new Node(x);
        node->next = top_;
        top_ = node;
        sz++;
    }
    int pop() {
        if (top_ == nullptr) return -1;              // empty
        int el = top_->data;
        Node* temp = top_;
        top_ = top_->next;
        delete temp;
        sz--;
        return el;
    }
    int top() { return top_ == nullptr ? -1 : top_->data; }
    int size() { return sz; }
    bool isEmpty() { return top_ == nullptr; }
};
```

**Java**
```java
class LLStack {
    private static class Node {
        int data; Node next;
        Node(int d) { data = d; }
    }
    private Node top = null;
    private int size = 0;
    void push(int x) {
        Node node = new Node(x);
        node.next = top;
        top = node;
        size++;
    }
    int pop() {
        if (top == null) return -1;
        int el = top.data;
        top = top.next;
        size--;
        return el;
    }
    int top() { return top == null ? -1 : top.data; }
    int size() { return size; }
    boolean isEmpty() { return top == null; }
}
```

#### Edge Cases & Pitfalls
- Guard `pop`/`top` on an empty stack. Dereferencing a null `top` crashes.
- In C++, `delete` the popped node to avoid leaks.

#### Key Takeaways
- Stack = linked list with all operations at the head.

[↑ Contents](#contents) · [← Previous](#p250) · [Next →](#p252)

---

<a id="p252"></a>

### 6. Implement queue using Linkedlist

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Implementation | Core | No | — | [Watch from 38:23](https://youtu.be/tqQ5fTamIN4?t=2303) |

#### Problem Statement
Implement a **queue** using a **singly linked list**, supporting `push`, `pop`, `top`/`front`, `size` and `isEmpty`, with no fixed capacity.

```text
push 2, push 3, push 4, top -> 2, pop, top -> 3, size -> 2
```

#### Approach: Insert at the tail, delete at the head (as in the video)
- **The two pointers.** Keep `start` (front) and `end` (back), just like the array version.
- **Push.** `node = new Node(x)`. If the queue is empty, `start = end = node`; otherwise `end->next = node` and `end = node`. Then `size++`.
- **Pop.** `temp = start`, `start = start->next`, free `temp`, `size−−`. If the queue becomes empty, also set `end = null`.
- **Front.** `start->data`.

Dry run:
- push 2, 3, 4: 2 → 3 → 4, with start at 2 and end at 4.
- pop removes 2, so start is at 3 and `top()` = 3.

**Complexity:**
- Time: O(1) for every operation.
- Space: O(n), dynamic.

**C++**
```cpp
class LLQueue {
    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(nullptr) {}
    };
    Node* start = nullptr;
    Node* end = nullptr;
    int sz = 0;
public:
    void push(int x) {
        Node* node = new Node(x);
        if (start == nullptr) start = end = node;
        else { end->next = node; end = node; }
        sz++;
    }
    int pop() {
        if (start == nullptr) return -1;            // empty
        int el = start->data;
        Node* temp = start;
        start = start->next;
        if (start == nullptr) end = nullptr;        // queue became empty
        delete temp;
        sz--;
        return el;
    }
    int top() { return start == nullptr ? -1 : start->data; }
    int size() { return sz; }
    bool isEmpty() { return start == nullptr; }
};
```

**Java**
```java
class LLQueue {
    private static class Node {
        int data; Node next;
        Node(int d) { data = d; }
    }
    private Node start = null, end = null;
    private int size = 0;
    void push(int x) {
        Node node = new Node(x);
        if (start == null) start = end = node;
        else { end.next = node; end = node; }
        size++;
    }
    int pop() {
        if (start == null) return -1;
        int el = start.data;
        start = start.next;
        if (start == null) end = null;
        size--;
        return el;
    }
    int top() { return start == null ? -1 : start.data; }
    int size() { return size; }
    boolean isEmpty() { return start == null; }
}
```

#### Edge Cases & Pitfalls
- When the last element is popped, reset `end` as well. Otherwise the next push links onto a deleted node.

#### Key Takeaways
- Queue = linked list with insertion at the tail and deletion at the head. Keeping a tail pointer makes both O(1).

[↑ Contents](#contents) · [← Previous](#p251) · [Next →](#p253)

---

<a id="p253"></a>

### 7. Balanced Paranthesis

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Implementation | Core | No | [LeetCode](https://leetcode.com/problems/valid-parentheses/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-balanced-parentheses-using-a-stack) | [Watch](https://youtu.be/xwjS0iZhw4I) |

#### Problem Statement
Given a string of brackets `()`, `{}` and `[]`, return `true` if it is **balanced**:
1. every opening bracket has a matching closing bracket of the **same type**;
2. every closing bracket has a matching opening bracket;
3. they close in the correct **order**.

```text
"()[{}()]"  ->  true
"[(])"      ->  false   (']' closes while '(' is still open)
"(()"       ->  false   (an opening bracket is never closed)
"())"       ->  false   (a closing bracket has no opener)
```

#### Intuition
Whenever a closing bracket appears, it must match the **most recent unmatched opening bracket**. "Most recent" means **last in, first out**, so store the opening brackets on a **stack**.

#### Approach: Stack of opening brackets
- Opening bracket: push it.
- Closing bracket:
  - if the stack is **empty**, there's no partner, so return `false`;
  - otherwise pop the top and check that the types match. A mismatch means `false`.
- At the end, the stack must be **empty**. Leftover openers were never closed.

Dry run on `"()[{}()]"`:
- push `(`, `)` matches.
- push `[`, push `{`, `}` matches.
- push `(`, `)` matches.
- `]` matches the `[`.
- Stack empty, so **true**.

**Complexity:** O(n) time. O(n) space in the worst case (all openers). You can't do better, because unmatched openers have to be remembered somewhere.

**C++**
```cpp
bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') st.push(c);
        else {
            if (st.empty()) return false;          // closing with no opener
            char ch = st.top();
            st.pop();
            if ((c == ')' && ch == '(') || (c == '}' && ch == '{') || (c == ']' && ch == '['))
                continue;
            return false;                           // wrong type / order
        }
    }
    return st.empty();                              // all openers closed?
}
```

**Java**
```java
class Solution {
    static boolean isValid(String s) {
        Deque<Character> st = new ArrayDeque<>();
        for (char c : s.toCharArray()) {
            if (c == '(' || c == '{' || c == '[') st.push(c);
            else {
                if (st.isEmpty()) return false;
                char ch = st.pop();
                if ((c == ')' && ch == '(') || (c == '}' && ch == '{') || (c == ']' && ch == '['))
                    continue;
                return false;
            }
        }
        return st.isEmpty();
    }
}
```

#### Edge Cases & Pitfalls
- Don't forget the final `st.empty()` check, which catches `"(()"`.
- Check for an empty stack before calling `top()`/`pop()`, which catches `")"`.

#### Key Takeaways
- "Match with the most recent unmatched item" calls for a stack.

[↑ Contents](#contents) · [← Previous](#p252) · [Next →](#p254)

---

## Prefix, Infix and Postfix Conversions

<a id="p254"></a>

### 8. Infix to Postfix Conversion

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Prefix, Infix and Postfix Conversions | Core | Yes | — | [Watch from 4:50](https://youtu.be/4pIc9UBHJtk?t=290) |

#### Problem Statement
Convert an **infix** expression (operators between operands, like `a+b*(c^d-e)`) to **postfix** (operators after their operands: `abcd^e-*+`). Operands are single letters or digits. Operators are `^`, `*`, `/`, `+` and `-`, with parentheses.

```text
a+b*(c^d-e)^(f+g*h)-i   ->   abcd^e-fgh*+^*+i-
(p+q)*(m-n)             ->   pq+mn-*
```

#### Background (from the video)
- **Infix** is how humans and most programming languages write expressions.
- **Postfix** is used by stack-based calculators.
- **Prefix** is used in Lisp and in expression trees.
- **Precedence:** `^` = 3, `* /` = 2, `+ -` = 1, anything else = −1.

#### Approach: Operator stack (shunting-yard)
Scan left to right, keeping an operator stack and an answer string:
- **operand:** append it to the answer;
- **`(`:** push it;
- **`)`:** pop and append until `(`, then pop the `(`;
- **operator `c`:** while the stack top has **higher precedence**, or **equal** precedence and `c` is left-associative, pop it and append. Then push `c`.

  The stack holds operators in strictly increasing precedence, so anything stronger must leave first. `^` is **right-associative**: `a^b^c = a^(b^c)`. So an incoming `^` does *not* pop an equal `^`. The video pops on `≤` for every operator, which mishandles `a^b^c`; this refinement isn't in the video.
- **End:** pop everything that remains.

Dry run on `(p+q)*(m-n)`:
- `(` push; `p` gives ans `p`; `+` push; `q` gives ans `pq`.
- `)` pops `+`, so ans = `pq+`.
- `*` push. `(` push; `m`; `-` push; `n`; `)` pops `-`, so ans = `pq+mn-`.
- End: pop `*`, giving **`pq+mn-*`**.

**Complexity:** O(n) time. Each operator is pushed and popped once. O(n) space for the stack plus the answer.

**C++**
```cpp
int prec(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}
string infixToPostfix(string s) {
    stack<char> st;
    string ans;
    for (char c : s) {
        if (isalnum((unsigned char)c)) ans += c;                 // operand
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') { ans += st.top(); st.pop(); }
            if (!st.empty()) st.pop();                           // remove '('
        } else {                                                 // operator
            while (!st.empty() && (prec(st.top()) > prec(c) ||
                                   (prec(st.top()) == prec(c) && c != '^'))) {
                ans += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) { ans += st.top(); st.pop(); }
    return ans;
}
```

**Java**
```java
class Solution {
    static int prec(char c) {
        if (c == '^') return 3;
        if (c == '*' || c == '/') return 2;
        if (c == '+' || c == '-') return 1;
        return -1;
    }
    static String infixToPostfix(String s) {
        Deque<Character> st = new ArrayDeque<>();
        StringBuilder ans = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (Character.isLetterOrDigit(c)) ans.append(c);
            else if (c == '(') st.push(c);
            else if (c == ')') {
                while (!st.isEmpty() && st.peek() != '(') ans.append(st.pop());
                if (!st.isEmpty()) st.pop();
            } else {
                while (!st.isEmpty() && (prec(st.peek()) > prec(c) ||
                                         (prec(st.peek()) == prec(c) && c != '^')))
                    ans.append(st.pop());
                st.push(c);
            }
        }
        while (!st.isEmpty()) ans.append(st.pop());
        return ans.toString();
    }
}
```

#### Edge Cases & Pitfalls
- `(` has precedence −1, so operators never pop past it. Only `)` removes it.
- Use `StringBuilder` in Java. `+=` on a `String` inside a loop is O(n²).

#### Key Takeaways
- Keep operators on a stack in increasing precedence, and pop the stronger ones before pushing a weaker one.

[↑ Contents](#contents) · [← Previous](#p253) · [Next →](#p255)

---

<a id="p255"></a>

### 9. Infix to Prefix Conversion

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Prefix, Infix and Postfix Conversions | Core | Yes | — | [Watch from 16:41](https://youtu.be/4pIc9UBHJtk?t=1001) |

#### Problem Statement
Convert an **infix** expression to **prefix** (operators before their operands).

```text
(a+b)*c-d+f   ->   +-*+abcdf
x+y*z/w+u     ->   ++x/*yzwu
```

#### Approach: Reverse → "controlled" infix-to-postfix → reverse (as in the video)
1. **Reverse** the infix string and **swap brackets**, turning `(` into `)` and vice versa.
2. Run **infix-to-postfix with one controlled change** to the popping rule. In reversed order, equal-precedence left-associative operators must **stay** on the stack.
   - For a non-`^` operator, pop only operators of **strictly higher** precedence.
   - For `^`, pop operators of **higher or equal** precedence, so two `^` never sit together.
3. **Reverse** the result.

Dry run on `(a+b)*c-d+f`:
- Step 1 gives `f+d-c*(b+a)`.
- Step 2, in brief:
  - `f`, push `+`, `d`.
  - `-` has equal precedence with `+`, so it's pushed without popping.
  - `c`, push `*`, push `(`, `b`, push `+`, `a`.
  - `)` pops `+`.
  - At the end, pop `*`, `-`, `+`.
  - Result: `fdcba+*-+`.
- Step 3 gives **`+-*+abcdf`**.

**Complexity:** O(n) time: two reversals of O(n/2) each, plus the O(2n) stack pass. O(n) space.

**C++**
```cpp
int prec(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}
string infixToPrefix(string s) {
    reverse(s.begin(), s.end());
    for (char& c : s) {                                  // swap brackets
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }
    stack<char> st;
    string ans;
    for (char c : s) {
        if (isalnum((unsigned char)c)) ans += c;
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') { ans += st.top(); st.pop(); }
            if (!st.empty()) st.pop();
        } else {
            if (c == '^') {                              // pop >= for '^'
                while (!st.empty() && prec(c) <= prec(st.top())) { ans += st.top(); st.pop(); }
            } else {                                     // pop only strictly greater
                while (!st.empty() && prec(c) < prec(st.top())) { ans += st.top(); st.pop(); }
            }
            st.push(c);
        }
    }
    while (!st.empty()) { ans += st.top(); st.pop(); }
    reverse(ans.begin(), ans.end());
    return ans;
}
```

**Java**
```java
class Solution {
    static int prec(char c) {
        if (c == '^') return 3;
        if (c == '*' || c == '/') return 2;
        if (c == '+' || c == '-') return 1;
        return -1;
    }
    static String infixToPrefix(String str) {
        StringBuilder rev = new StringBuilder(str).reverse();
        for (int i = 0; i < rev.length(); i++) {
            char c = rev.charAt(i);
            if (c == '(') rev.setCharAt(i, ')');
            else if (c == ')') rev.setCharAt(i, '(');
        }
        Deque<Character> st = new ArrayDeque<>();
        StringBuilder ans = new StringBuilder();
        for (char c : rev.toString().toCharArray()) {
            if (Character.isLetterOrDigit(c)) ans.append(c);
            else if (c == '(') st.push(c);
            else if (c == ')') {
                while (!st.isEmpty() && st.peek() != '(') ans.append(st.pop());
                if (!st.isEmpty()) st.pop();
            } else {
                if (c == '^') {
                    while (!st.isEmpty() && prec(c) <= prec(st.peek())) ans.append(st.pop());
                } else {
                    while (!st.isEmpty() && prec(c) < prec(st.peek())) ans.append(st.pop());
                }
                st.push(c);
            }
        }
        while (!st.isEmpty()) ans.append(st.pop());
        return ans.reverse().toString();
    }
}
```

#### Edge Cases & Pitfalls
- Forgetting to **swap the brackets** after reversing makes every `)` look like an opener.
- Using the ordinary `≤` popping rule here turns `a-b+c` into `-a+bc` instead of `+-abc`.

#### Key Takeaways
- Prefix is "postfix of the mirror image", with the associativity rule flipped.

[↑ Contents](#contents) · [← Previous](#p254) · [Next →](#p256)

---

<a id="p256"></a>

### 10. Prefix to Infix Conversion

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Prefix, Infix and Postfix Conversions | Core | Yes | — | [Watch from 35:30](https://youtu.be/4pIc9UBHJtk?t=2130) |

#### Problem Statement
Convert a valid **prefix** expression to a fully parenthesised **infix** expression.

```text
*+PQ-MN   ->   ((P+Q)*(M-N))
```

#### Approach: Stack of strings, scanning right to left (as in the video)
Scan **from the end**:
- **operand:** push it as a string;
- **operator `op`:** `t1 = pop()`, `t2 = pop()`, push `"(" + t1 + op + t2 + ")"`.

  In prefix, the first operand popped is the **left** one, because the expression is read backwards.
- The final stack top is the answer.

Dry run on `*+PQ-MN`, right to left:
- N, M are pushed.
- `-` gives `(M-N)`.
- Q, P are pushed.
- `+` gives `(P+Q)`.
- `*` pops `(P+Q)` then `(M-N)`, giving **`((P+Q)*(M-N))`**.

**Complexity:** O(n) iterations. String concatenation can cost up to O(n) each in many languages, so O(n) to O(n²) overall. Mention this to the interviewer. O(n) space.

**C++**
```cpp
string prefixToInfix(string s) {
    stack<string> st;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        char c = s[i];
        if (isalnum((unsigned char)c)) st.push(string(1, c));
        else {
            string t1 = st.top(); st.pop();
            string t2 = st.top(); st.pop();
            st.push("(" + t1 + c + t2 + ")");
        }
    }
    return st.top();
}
```

**Java**
```java
class Solution {
    static String prefixToInfix(String s) {
        Deque<String> st = new ArrayDeque<>();
        for (int i = s.length() - 1; i >= 0; i--) {
            char c = s.charAt(i);
            if (Character.isLetterOrDigit(c)) st.push(String.valueOf(c));
            else {
                String t1 = st.pop(), t2 = st.pop();
                st.push("(" + t1 + c + t2 + ")");
            }
        }
        return st.peek();
    }
}
```

#### Key Takeaways
- Prefix to anything: scan **right to left**, and the first pop is the left operand.

[↑ Contents](#contents) · [← Previous](#p255) · [Next →](#p257)

---

<a id="p257"></a>

### 11. Prefix to Postfix Conversion

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Prefix, Infix and Postfix Conversions | Core | Yes | — | [Watch from 45:04](https://youtu.be/4pIc9UBHJtk?t=2704) |

#### Problem Statement
Convert a valid **prefix** expression to **postfix**.

```text
/-AB*+DEF   ->   AB-DE+F*/
```

#### Approach: Stack of strings, scanning right to left (as in the video)
- **operand:** push it;
- **operator `op`:** `t1 = pop()` (left), `t2 = pop()` (right), push `t1 + t2 + op`.

Dry run on `/-AB*+DEF`, right to left:
- F, E, D are pushed.
- `+` gives `DE+`.
- `*` gives `DE+F*`.
- B, A are pushed.
- `-` gives `AB-`.
- `/` pops `AB-` then `DE+F*`, giving **`AB-DE+F*/`**.

**Complexity:** O(n) iterations, plus string-building cost. O(n) space.

**C++**
```cpp
string prefixToPostfix(string s) {
    stack<string> st;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        char c = s[i];
        if (isalnum((unsigned char)c)) st.push(string(1, c));
        else {
            string t1 = st.top(); st.pop();
            string t2 = st.top(); st.pop();
            st.push(t1 + t2 + c);
        }
    }
    return st.top();
}
```

**Java**
```java
class Solution {
    static String prefixToPostfix(String s) {
        Deque<String> st = new ArrayDeque<>();
        for (int i = s.length() - 1; i >= 0; i--) {
            char c = s.charAt(i);
            if (Character.isLetterOrDigit(c)) st.push(String.valueOf(c));
            else {
                String t1 = st.pop(), t2 = st.pop();
                st.push(t1 + t2 + c);
            }
        }
        return st.peek();
    }
}
```

#### Key Takeaways
- The generic route would be prefix → infix → postfix. The direct stack pass skips building the parenthesised infix.

[↑ Contents](#contents) · [← Previous](#p256) · [Next →](#p258)

---

<a id="p258"></a>

### 12. Postfix to Infix Conversion

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Prefix, Infix and Postfix Conversions | Core | Yes | — | [Watch from 27:51](https://youtu.be/4pIc9UBHJtk?t=1671) |

#### Problem Statement
Convert a valid **postfix** expression to a fully parenthesised **infix** expression.

```text
AB-DE+F*/   ->   ((A-B)/((D+E)*F))
```

#### Approach: Stack of strings, scanning left to right (as in the video)
- **operand:** push it;
- **operator `op`:** `t1 = pop()` (the **right** operand, because it was pushed last), `t2 = pop()` (left), push `"(" + t2 + op + t1 + ")"`.
- The stack top at the end is the answer, provided the input is valid.

Dry run on `AB-DE+F*/`:
- A, B, then `-` gives `(A-B)`.
- D, E, then `+` gives `(D+E)`.
- F, then `*` gives `((D+E)*F)`.
- `/` gives **`((A-B)/((D+E)*F))`**.

**Complexity:** O(n) iterations. String additions cost O(n₁ + n₂) each, which can reach O(n) per step in the worst case. O(n) space.

**C++**
```cpp
string postfixToInfix(string s) {
    stack<string> st;
    for (char c : s) {
        if (isalnum((unsigned char)c)) st.push(string(1, c));
        else {
            string t1 = st.top(); st.pop();          // right operand
            string t2 = st.top(); st.pop();          // left operand
            st.push("(" + t2 + c + t1 + ")");
        }
    }
    return st.top();
}
```

**Java**
```java
class Solution {
    static String postfixToInfix(String s) {
        Deque<String> st = new ArrayDeque<>();
        for (char c : s.toCharArray()) {
            if (Character.isLetterOrDigit(c)) st.push(String.valueOf(c));
            else {
                String t1 = st.pop(), t2 = st.pop();
                st.push("(" + t2 + c + t1 + ")");
            }
        }
        return st.peek();
    }
}
```

#### Edge Cases & Pitfalls
- **Operand order:** in postfix the first pop is the **right** operand. In prefix, scanning backwards, it's the **left** one. Mixing these up silently swaps `A−B` into `B−A`.

#### Key Takeaways
- Postfix to anything: scan left to right, pop two, combine, push.

[↑ Contents](#contents) · [← Previous](#p257) · [Next →](#p259)

---

<a id="p259"></a>

### 13. Postfix to Prefix Conversion

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Prefix, Infix and Postfix Conversions | Core | Yes | — | [Watch from 39:57](https://youtu.be/4pIc9UBHJtk?t=2397) |

#### Problem Statement
Convert a valid **postfix** expression to **prefix**.

```text
AB-DE+F*/   ->   /-AB*+DEF
```

#### Approach: Stack of strings, scanning left to right (as in the video)
- **operand:** push it;
- **operator `op`:** `t1 = pop()` (right), `t2 = pop()` (left), push `op + t2 + t1`.

Dry run:
- A, B, then `-` gives `-AB`.
- D, E, then `+` gives `+DE`.
- F, then `*` gives `*+DEF`.
- `/` gives **`/-AB*+DEF`**.

**Complexity:** O(n) iterations, plus string-building cost. O(n) space.

**C++**
```cpp
string postfixToPrefix(string s) {
    stack<string> st;
    for (char c : s) {
        if (isalnum((unsigned char)c)) st.push(string(1, c));
        else {
            string t1 = st.top(); st.pop();
            string t2 = st.top(); st.pop();
            st.push(c + t2 + t1);
        }
    }
    return st.top();
}
```

**Java**
```java
class Solution {
    static String postfixToPrefix(String s) {
        Deque<String> st = new ArrayDeque<>();
        for (char c : s.toCharArray()) {
            if (Character.isLetterOrDigit(c)) st.push(String.valueOf(c));
            else {
                String t1 = st.pop(), t2 = st.pop();
                st.push(c + t2 + t1);
            }
        }
        return st.peek();
    }
}
```

#### Key Takeaways
- All four non-infix-source conversions share one skeleton: a stack of strings and "pop two, combine, push". Only the scan direction and the combine order change.

[↑ Contents](#contents) · [← Previous](#p258) · [Next →](#p260)

---

## Monotonic Stack

<a id="p260"></a>

### 14. Next Greater Element

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Monotonic Stack | Core | No | [LeetCode](https://leetcode.com/problems/next-greater-element-i/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/next-greater-element) | [Watch](https://youtu.be/e7XQLtOQM3I) |

#### Problem Statement
For every element of `arr`, find the **next greater element**: the first element **to its right** that is strictly greater. Use −1 if there is none.

```text
arr = [6, 0, 8, 1, 3]                         ->  [8, 8, -1, 3, -1]
arr = [4, 12, 5, 3, 1, 2, 5, 3, 1, 2, 4, 6]   ->  [12, -1, 6, 5, 2, 5, 6, 4, 2, 4, 6, -1]
```

LeetCode 496 asks the same question for a subset `nums1` of `nums2`. Compute the NGE array for `nums2` and map each value to its answer (code at the end).

#### What is a monotonic stack?
A stack whose elements are kept in a specific order (increasing or decreasing). This problem starts the monotonic-stack section.

#### Approach 1: Brute Force — scan right for each element
For each `i`, look at `j = i+1, …`. The first `arr[j] > arr[i]` is the answer; then break.

**Complexity:** O(n²) time. O(n) space for the answer. Don't overwrite the input; interviewers discourage modifying it.

**C++**
```cpp
vector<int> nextGreaterBrute(vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n, -1);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[j] > arr[i]) { nge[i] = arr[j]; break; }
    return nge;
}
```

**Java**
```java
class Solution {
    static int[] nextGreaterBrute(int[] arr) {
        int n = arr.length;
        int[] nge = new int[n];
        Arrays.fill(nge, -1);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (arr[j] > arr[i]) { nge[i] = arr[j]; break; }
        return nge;
    }
}
```

#### Approach 2: Optimal — traverse from the back with a decreasing stack
- **Why go backwards.** The answer for `i` lies to its **right**. Traversing from the back means the right side has already been seen when we reach `i`.
- **The light-pole intuition.** Standing at `i` and looking right, you only "see" a **staircase of increasing heights**. Anything shorter than a pole nearer to you is hidden behind it.
- **What to keep.** The stack keeps exactly that staircase, which is **decreasing from bottom to top**.
- **At each `i` (from right to left):**
  1. Pop every element `≤ arr[i]`. They're hidden by `arr[i]` from now on, so they can never be the answer for anything further left.
  2. If the stack is empty, the answer is −1; otherwise it's `st.top()`.
  3. Push `arr[i]`.

Dry run on `[6, 0, 8, 1, 3]` (right to left):
- 3: stack empty, so −1. Push 3.
- 1: top is 3, so 3. Push 1.
- 8: pop 1 and 3, stack empty, so −1. Push 8.
- 0: top is 8, so 8. Push 0.
- 6: pop 0, top is 8, so 8.

Result: **[8, 8, −1, 3, −1]**.

**Complexity:** O(2n) time. The inner `while` isn't n each time: every element is pushed once and popped at most once, so all pops total ≤ n. O(n) space for the stack, plus the answer.

**C++**
```cpp
vector<int> nextGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= arr[i]) st.pop();   // remove hidden poles
        nge[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return nge;
}
```

**Java**
```java
class Solution {
    static int[] nextGreaterElement(int[] arr) {
        int n = arr.length;
        int[] nge = new int[n];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && st.peek() <= arr[i]) st.pop();
            nge[i] = st.isEmpty() ? -1 : st.peek();
            st.push(arr[i]);
        }
        return nge;
    }
}
```

#### LeetCode 496 variant — `nums1 ⊆ nums2` *(not in video)*
Run the same stack pass on `nums2`, store `value → NGE` in a hash map, and look up each element of `nums1`.

**C++**
```cpp
vector<int> nextGreaterElementLC(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> nge;
    stack<int> st;
    for (int i = (int)nums2.size() - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= nums2[i]) st.pop();
        nge[nums2[i]] = st.empty() ? -1 : st.top();
        st.push(nums2[i]);
    }
    vector<int> ans;
    for (int x : nums1) ans.push_back(nge[x]);
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] nextGreaterElementLC(int[] nums1, int[] nums2) {
        Map<Integer, Integer> nge = new HashMap<>();
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = nums2.length - 1; i >= 0; i--) {
            while (!st.isEmpty() && st.peek() <= nums2[i]) st.pop();
            nge.put(nums2[i], st.isEmpty() ? -1 : st.peek());
            st.push(nums2[i]);
        }
        int[] ans = new int[nums1.length];
        for (int k = 0; k < nums1.length; k++) ans[k] = nge.get(nums1[k]);
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- Pop on **`≤`**, not `<`. An equal element isn't "greater", so it must not be reported.
- Stack values vs stack indices: storing **indices** instead lets you compute distances, as in Stock Span or Daily Temperatures.

#### Key Takeaways
- Next-greater queries mean a monotonic (decreasing) stack, filled while scanning from the side where the answers lie.
- Amortised analysis: each element is pushed and popped at most once, so the whole pass is O(n).

[↑ Contents](#contents) · [← Previous](#p259) · [Next →](#p261)

---

<a id="p261"></a>

### 15. Next Greater Element - 2

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Monotonic Stack | Core | No | [LeetCode](https://leetcode.com/problems/next-greater-element-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/next-greater-element-ii-circular-array) | [Watch](https://youtu.be/7PrncD7v9YQ) |

#### Problem Statement
Same as Next Greater Element, but the array is **circular**: after the last element, the search wraps around to the start. Return −1 if no greater element exists anywhere.

```text
arr = [2, 10, 12, 1, 11]   ->  [10, 12, -1, 11, 12]
arr = [1, 2, 1]            ->  [2, -1, 2]
```

#### Intuition — "hypothetically double the array"
Circularity is the same as looking at the array written **twice**, `[2,10,12,1,11, 2,10,12,1,11]`, and asking the ordinary NGE question for the first half. There's no need to build the copy: the **hypothetical index** `j` maps to the real index `j % n`.

#### Approach 1: Brute Force — check the next n−1 positions circularly
For each `i`, check `j = i+1 … i+n−1` using `arr[j % n]`, and take the first greater value.

**Complexity:** O(n²) time, O(n) space for the answer.

**C++**
```cpp
vector<int> nextGreaterCircularBrute(vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n, -1);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= i + n - 1; j++) {
            int idx = j % n;                         // hypothetical -> real index
            if (arr[idx] > arr[i]) { nge[i] = arr[idx]; break; }
        }
    return nge;
}
```

**Java**
```java
class Solution {
    static int[] nextGreaterCircularBrute(int[] arr) {
        int n = arr.length;
        int[] nge = new int[n];
        Arrays.fill(nge, -1);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j <= i + n - 1; j++) {
                int idx = j % n;
                if (arr[idx] > arr[i]) { nge[i] = arr[idx]; break; }
            }
        return nge;
    }
}
```

#### Approach 2: Optimal — monotonic stack over the hypothetical 2n array
- Run the NGE stack from `i = 2n − 1` down to `0`, using `arr[i % n]`.
- Record answers **only when `i < n`**. The pass over the second (virtual) half only fills the stack with what each real element "sees" after wrapping around.

Dry run on `[2,10,12,1,11]`:
- The virtual half seeds the stack with the staircase seen from the end: 12 and 11.
- The real pass then gives:
  - 11: next greater is 12;
  - 1: 11;
  - 12: stack empties, so −1;
  - 10: 12;
  - 2: 10.

**Complexity:** O(4n) time: 2n iterations plus at most 2n pops. O(2n) space for the stack, plus the answer.

**C++**
```cpp
vector<int> nextGreaterElements(vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n, -1);
    stack<int> st;
    for (int i = 2 * n - 1; i >= 0; i--) {
        int val = arr[i % n];
        while (!st.empty() && st.top() <= val) st.pop();
        if (i < n) nge[i] = st.empty() ? -1 : st.top();   // real indices only
        st.push(val);
    }
    return nge;
}
```

**Java**
```java
class Solution {
    static int[] nextGreaterElements(int[] arr) {
        int n = arr.length;
        int[] nge = new int[n];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 2 * n - 1; i >= 0; i--) {
            int val = arr[i % n];
            while (!st.isEmpty() && st.peek() <= val) st.pop();
            if (i < n) nge[i] = st.isEmpty() ? -1 : st.peek();
            st.push(val);
        }
        return nge;
    }
}
```

#### Edge Cases & Pitfalls
- The maximum element always gets −1, and so does every copy of it.
- Don't actually double the array. `i % n` gives the same effect with no extra memory.

#### Key Takeaways
- Circular array = conceptually concatenate it with itself and use `% n` indices. The same trick works for circular subarray sums and similar problems.

[↑ Contents](#contents) · [← Previous](#p260) · [Next →](#p262)

---

<a id="p262"></a>

### 16. Asteroid Collision

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Monotonic Stack | Core | No | [LeetCode](https://leetcode.com/problems/asteroid-collision/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/asteroid-collision) | [Watch](https://youtu.be/_eYGqw_VDR4) |

#### Problem Statement
`asteroids[i]` is an asteroid's size (`|value|`) and direction: **positive moves right**, **negative moves left**, and all move at the same speed.
- When two collide, the **smaller** explodes. If they're the same size, **both** explode.
- Asteroids moving in the same direction never meet.

Return the state after all collisions.

```text
[4, 7, 1, 1, 2, -3, -7, 17, 15, -16]   ->  [4, 17]
[4, 7, 1, 1, 2, -3, -7, 17, 15, -18, -19] -> [-18, -19]
[5, 10, -5]                             ->  [5, 10]
[8, -8]                                 ->  []
```

#### Intuition
- **When collisions happen.** A collision occurs only when a **right-moving** asteroid is followed by a **left-moving** one.
- **What a left-mover hits.** It meets the most recent surviving right-movers, so the latest survivor matters first. That calls for a **stack**.
- **Use a list instead.** A `vector`/`ArrayList` used as a stack keeps the survivors in their original left-to-right order, so you don't have to reverse a stack at the end.

#### Approach: Stack (list) simulation (as in the video)
For each asteroid `a`:
- `a > 0`: push it. It can only collide with something arriving later.
- `a < 0`:
  1. While the top is **positive and smaller** than `|a|`, pop it, since it's destroyed.
  2. If the top is positive and **equal** to `|a|`, pop it. Both are destroyed, so don't push `a`.
  3. Otherwise, push `a` only if the list is **empty** or the top is **negative**. Then nothing to its left can stop it, and same-direction asteroids never collide.
  4. In every remaining case, the top is a bigger positive asteroid, and `a` is destroyed.

Dry run on `[4, 7, 1, 1, 2, -3, -7, 17, 15, -16]`:
- Push 4, 7, 1, 1, 2.
- −3 destroys 2, 1, 1. It then meets 7 > 3, so −3 is destroyed.
- −7 meets 7, which is equal, so both are destroyed.
- Push 17 and 15.
- −16 destroys 15, then meets 17 > 16 and is destroyed.
- Result: **[4, 17]**.

**Complexity:** O(n) time. Each asteroid is pushed and popped at most once. O(n) space.

**C++**
```cpp
vector<int> asteroidCollision(vector<int>& asteroids) {
    vector<int> st;                                       // list used as a stack
    for (int a : asteroids) {
        if (a > 0) { st.push_back(a); continue; }
        while (!st.empty() && st.back() > 0 && st.back() < -a) st.pop_back();  // smaller ones explode
        if (!st.empty() && st.back() == -a) st.pop_back();                     // equal: both explode
        else if (st.empty() || st.back() < 0) st.push_back(a);                 // nothing to hit
        // else: a bigger positive survives, a explodes
    }
    return st;
}
```

**Java**
```java
class Solution {
    static int[] asteroidCollision(int[] asteroids) {
        List<Integer> st = new ArrayList<>();
        for (int a : asteroids) {
            if (a > 0) { st.add(a); continue; }
            while (!st.isEmpty() && st.get(st.size() - 1) > 0 && st.get(st.size() - 1) < -a)
                st.remove(st.size() - 1);
            if (!st.isEmpty() && st.get(st.size() - 1) == -a) st.remove(st.size() - 1);
            else if (st.isEmpty() || st.get(st.size() - 1) < 0) st.add(a);
        }
        int[] res = new int[st.size()];
        for (int i = 0; i < res.length; i++) res[i] = st.get(i);
        return res;
    }
}
```

#### Edge Cases & Pitfalls
- **A negative on top doesn't block a new negative.** A negative followed by a positive (`[-2, 3]`) never collides, because they move apart.
- **Equal sizes.** After destroying smaller ones, check equality *before* deciding whether to push.
- In Java, `List.remove(int index)` removes by position. Make sure you pass `st.size() - 1`, an `int`, not an `Integer` value.

#### Key Takeaways
- This is a stack simulation where each incoming element may cancel several previous ones. Amortised O(n).

[↑ Contents](#contents) · [← Previous](#p261) · [Next →](#p263)

---

<a id="p263"></a>

### 17. Sum of Subarray Minimums

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Monotonic Stack | Core | No | [LeetCode](https://leetcode.com/problems/sum-of-subarray-minimums/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/sum-of-subarray-minimums) | [Watch](https://youtu.be/v0e8p9JCgRc) |

#### Problem Statement
Given `arr`, return the sum of `min(subarray)` over **all** contiguous subarrays, modulo 10⁹ + 7.

```text
arr = [3, 1, 2, 4]   ->  17
subarrays: [3]=3 [3,1]=1 [3,1,2]=1 [3,1,2,4]=1 [1]=1 [1,2]=1 [1,2,4]=1 [2]=2 [2,4]=2 [4]=4
```

#### Approach 1: Brute Force — all subarrays with a running minimum
For each `i`, extend `j` while keeping `mini = min(mini, arr[j])`, and add `mini` to the sum, taking the modulus at each step.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int sumSubarrayMinsBrute(vector<int>& arr) {
    const int MOD = 1e9 + 7;
    int n = arr.size();
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int mini = arr[i];
        for (int j = i; j < n; j++) {
            mini = min(mini, arr[j]);
            sum = (sum + mini) % MOD;
        }
    }
    return (int)sum;
}
```

**Java**
```java
class Solution {
    static int sumSubarrayMinsBrute(int[] arr) {
        final int MOD = 1_000_000_007;
        int n = arr.length;
        long sum = 0;
        for (int i = 0; i < n; i++) {
            int mini = arr[i];
            for (int j = i; j < n; j++) {
                mini = Math.min(mini, arr[j]);
                sum = (sum + mini) % MOD;
            }
        }
        return (int) sum;
    }
}
```

#### Approach 2: Optimal — the contribution of each element
**Flip the question.** Instead of "the min of each subarray", ask: **in how many subarrays is `arr[i]` the minimum?** Then the answer is Σ `arr[i] × count(i)`.

**The counting rule.** `arr[i]` is the minimum of a subarray `[L, R]` iff the subarray stays strictly inside the region between the nearest smaller element on each side:
- `pse[i]` = index of the **previous smaller** element, or −1;
- `nse[i]` = index of the **next smaller** element, or n.

So there are `left = i − pse[i]` choices for L and `right = nse[i] − i` choices for R, giving

  **contribution = arr[i] × left × right**

Example `[3,1,2,4]`, for `arr[1] = 1`: pse = −1 and nse = 4, so left = 2, right = 3, and the contribution is 1 × 6 = 6.

**Duplicates (the video's edge case).** In `[1,1]`, the subarray `[1,1]` would be counted for **both** 1s. Break ties on one side only:
- **next strictly smaller** on the right (pop `≥`);
- **previous smaller *or equal*** on the left (pop `>`).

Now each subarray's minimum is credited to exactly one occurrence, the **left-most** of the equal minima. In `[1,1]`, index 0 owns `[1]` and `[1,1]`, and index 1 owns only its own `[1]`.

Both boundary arrays are standard monotonic-stack passes over **indices** (see Next Greater Element).

**Complexity:** O(5n) time: two stack passes of 2n each plus the final sum. O(5n) space for `nse`, `psee`, two stacks and the input.

**C++**
```cpp
vector<int> findNSE(vector<int>& arr) {                  // next strictly smaller index
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return nse;
}
vector<int> findPSEE(vector<int>& arr) {                 // previous smaller-or-equal index
    int n = arr.size();
    vector<int> psee(n);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) st.pop();
        psee[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return psee;
}
int sumSubarrayMins(vector<int>& arr) {
    const int MOD = 1e9 + 7;
    vector<int> nse = findNSE(arr), psee = findPSEE(arr);
    long long total = 0;
    for (int i = 0; i < (int)arr.size(); i++) {
        long long left = i - psee[i], right = nse[i] - i;
        total = (total + (left * right % MOD) * arr[i] % MOD) % MOD;
    }
    return (int)total;
}
```

**Java**
```java
class Solution {
    static int[] findNSE(int[] arr) {
        int n = arr.length;
        int[] nse = new int[n];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && arr[st.peek()] >= arr[i]) st.pop();
            nse[i] = st.isEmpty() ? n : st.peek();
            st.push(i);
        }
        return nse;
    }
    static int[] findPSEE(int[] arr) {
        int n = arr.length;
        int[] psee = new int[n];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && arr[st.peek()] > arr[i]) st.pop();
            psee[i] = st.isEmpty() ? -1 : st.peek();
            st.push(i);
        }
        return psee;
    }
    static int sumSubarrayMins(int[] arr) {
        final long MOD = 1_000_000_007L;
        int[] nse = findNSE(arr), psee = findPSEE(arr);
        long total = 0;
        for (int i = 0; i < arr.length; i++) {
            long left = i - psee[i], right = nse[i] - i;
            total = (total + (left * right % MOD) * arr[i] % MOD) % MOD;
        }
        return (int) total;
    }
}
```

#### Edge Cases & Pitfalls
- **Equal elements:** with strict boundaries on both sides you double-count; with non-strict boundaries on both sides you miss subarrays. Use exactly one strict side and one non-strict side.
- `left × right × arr[i]` overflows 32 bits. Use 64-bit arithmetic and reduce modulo at each multiplication.
- Store **indices** on the stacks, because you need distances.

#### Key Takeaways
- "Sum over all subarrays of min/max" becomes Σ value × (number of subarrays where it's the extreme). The count comes from the previous and next smaller boundaries, and monotonic stacks compute those in O(n).

[↑ Contents](#contents) · [← Previous](#p262) · [Next →](#p264)

---

<a id="p264"></a>

### 18. Sum of Subarray Ranges

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Monotonic Stack | Core | No | [LeetCode](https://leetcode.com/problems/sum-of-subarray-ranges/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/sum-of-subarray-ranges) | [Watch](https://youtu.be/gIrMptNPf5M) |

#### Problem Statement
The **range** of a subarray is `max − min`. Return the sum of ranges over all subarrays.

```text
nums = [1, 4, 3, 2]   ->  13
nums = [1, 2, 3]      ->  4
nums = [4, -2, -3, 4, 1] -> 59
```

#### Approach 1: Brute Force — running max and min
For each `i`, extend `j`, maintaining `largest` and `smallest`, and add `largest − smallest`. Single-element subarrays contribute 0, so `j` can start at `i + 1`.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
long long subArrayRangesBrute(vector<int>& nums) {
    int n = nums.size();
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int largest = nums[i], smallest = nums[i];
        for (int j = i + 1; j < n; j++) {
            largest = max(largest, nums[j]);
            smallest = min(smallest, nums[j]);
            sum += largest - smallest;
        }
    }
    return sum;
}
```

**Java**
```java
class Solution {
    static long subArrayRangesBrute(int[] nums) {
        int n = nums.length;
        long sum = 0;
        for (int i = 0; i < n; i++) {
            int largest = nums[i], smallest = nums[i];
            for (int j = i + 1; j < n; j++) {
                largest = Math.max(largest, nums[j]);
                smallest = Math.min(smallest, nums[j]);
                sum += largest - smallest;
            }
        }
        return sum;
    }
}
```

#### Approach 2: Optimal — Σ(subarray maximums) − Σ(subarray minimums)
`Σ (max − min) = Σ max − Σ min`, so reuse **Sum of Subarray Minimums** twice:
- **Σ minimums:** contributions from the next smaller (strict) and previous smaller-or-equal boundaries.
- **Σ maximums:** the same with the comparisons flipped, using the next **greater** (strict) and previous **greater-or-equal** boundaries.

No modulus is needed here; the answer fits in 64 bits.

**Complexity:** O(10n) time: two passes of 5n each. O(n) space.

**C++**
```cpp
long long sumOfExtremes(vector<int>& a, bool forMax) {
    int n = a.size();
    vector<int> nxt(n), prv(n);
    stack<int> st;
    // "better" means smaller for minimums, larger for maximums
    auto better = [&](int x, int y) { return forMax ? x > y : x < y; };
    for (int i = n - 1; i >= 0; i--) {                 // next strictly-better
        while (!st.empty() && !better(a[st.top()], a[i])) st.pop();
        nxt[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) {                      // previous better-or-equal
        while (!st.empty() && better(a[i], a[st.top()])) st.pop();
        prv[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    long long total = 0;
    for (int i = 0; i < n; i++)
        total += (long long)a[i] * (i - prv[i]) * (nxt[i] - i);
    return total;
}
long long subArrayRanges(vector<int>& nums) {
    return sumOfExtremes(nums, true) - sumOfExtremes(nums, false);
}
```

**Java**
```java
class Solution {
    static long sumOfExtremes(int[] a, boolean forMax) {
        int n = a.length;
        int[] nxt = new int[n], prv = new int[n];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && !better(a[st.peek()], a[i], forMax)) st.pop();
            nxt[i] = st.isEmpty() ? n : st.peek();
            st.push(i);
        }
        st.clear();
        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && better(a[i], a[st.peek()], forMax)) st.pop();
            prv[i] = st.isEmpty() ? -1 : st.peek();
            st.push(i);
        }
        long total = 0;
        for (int i = 0; i < n; i++)
            total += (long) a[i] * (i - prv[i]) * (nxt[i] - i);
        return total;
    }
    static boolean better(int x, int y, boolean forMax) { return forMax ? x > y : x < y; }
    static long subArrayRanges(int[] nums) {
        return sumOfExtremes(nums, true) - sumOfExtremes(nums, false);
    }
}
```

#### Edge Cases & Pitfalls
- **Negative values:** the formula works unchanged. Contributions can be negative, which is why there's no modulus.
- **The same tie-breaking rule applies to maximums:** one boundary strict, the other non-strict.

#### Key Takeaways
- Linearity: sum of (max − min) = sum of max − sum of min, and each of those is a contribution-technique problem.

[↑ Contents](#contents) · [← Previous](#p263) · [Next →](#p265)

---

<a id="p265"></a>

### 19. Remove K Digits

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Monotonic Stack | Core | No | [LeetCode](https://leetcode.com/problems/remove-k-digits/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/remove-k-digits) | [Watch](https://youtu.be/jmbuRzYPGrg) |

#### Problem Statement
`num` is a non-negative integer given as a string of digits. Remove exactly `k` digits to make the **smallest possible** number. Return it as a string with no leading zeros, or `"0"` if nothing remains.

```text
num = "1432219", k = 3   ->  "1219"
num = "10200",   k = 1   ->  "200"   (not "0200")
num = "10",      k = 2   ->  "0"
num = "123456",  k = 3   ->  "123"
```

#### Intuition
To make a number small, the **leftmost digits** matter most, so we want small digits at the front. Scanning left to right, if the current digit is **smaller than the previous kept digit**, removing that previous (larger) digit makes the number smaller, as long as removals remain. This is a **monotonic increasing stack** of kept digits.

#### Approach: Greedy with a monotonic stack (as in the video)
For each digit `d`:
- while the stack is non-empty, `k > 0` and `top > d`, pop the top and decrement `k`;
- push `d`.

Then handle three edge cases from the video:
1. **Leftover `k`.** For example `"123456"`, where nothing was ever popped. The stack is increasing, so the **last** digits are the largest. Pop `k` more.
2. **Leading zeros.** For example `"10200"` with k = 1 leaves `0,2,0,0`. Strip the zeros from the front.
3. **Nothing left** (everything removed, or only zeros). Return `"0"`.

Dry run on `"1432219"`, k = 3:
- push 1, push 4.
- `3`: 4 > 3, so pop (k = 2), push 3.
- `2`: 3 > 2, so pop (k = 1), push 2.
- `2`: equal, so push.
- `1`: 2 > 1, so pop (k = 0), push 1.
- `9`: push.
- The stack holds 1 2 1 9, giving **"1219"**.

**Complexity:** O(3n + k) time: the scan with its pops, building the string, stripping zeros, and reversing (if you use a real stack). O(n) space.

**C++**
```cpp
string removeKdigits(string num, int k) {
    string st;                                     // string used as a stack
    for (char d : num) {
        while (!st.empty() && k > 0 && st.back() > d) {
            st.pop_back();                         // drop a larger previous digit
            k--;
        }
        st.push_back(d);
    }
    while (k > 0 && !st.empty()) { st.pop_back(); k--; }   // leftover k: drop largest (last)
    int i = 0;
    while (i < (int)st.size() && st[i] == '0') i++;        // strip leading zeros
    string res = st.substr(i);
    return res.empty() ? "0" : res;
}
```

**Java**
```java
class Solution {
    static String removeKdigits(String num, int k) {
        StringBuilder st = new StringBuilder();     // used as a stack
        for (char d : num.toCharArray()) {
            while (st.length() > 0 && k > 0 && st.charAt(st.length() - 1) > d) {
                st.deleteCharAt(st.length() - 1);
                k--;
            }
            st.append(d);
        }
        while (k > 0 && st.length() > 0) { st.deleteCharAt(st.length() - 1); k--; }
        int i = 0;
        while (i < st.length() && st.charAt(i) == '0') i++;
        String res = st.substring(i);
        return res.isEmpty() ? "0" : res;
    }
}
```

The video uses an actual `stack<char>`. It pops everything into a result (which comes out reversed), trims trailing zeros (the leading zeros of the real number), and reverses at the end. Using a string or `StringBuilder` as the stack avoids the reversal, but the logic is identical.

#### Edge Cases & Pitfalls
- **Don't pop on equal digits.** Popping a `2` for another `2` wastes a removal.
- **`k == n`** removes everything, so return `"0"`.
- An all-zero remainder, like `"0000"`, must become `"0"`, not `""`.

#### Key Takeaways
- To get the lexicographically smallest result after deletions, keep an increasing stack and pop larger predecessors while deletions remain. The same idea solves "Remove Duplicate Letters" and "Smallest Subsequence".

[↑ Contents](#contents) · [← Previous](#p264) · [Next →](#p266)

---

<a id="p266"></a>

### 20. Next Smaller Element

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › Monotonic Stack | Core | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
For each element of `arr`, find the **next smaller element**: the first element to its right that is strictly smaller. Use −1 if there is none.

```text
arr = [4, 8, 5, 2, 25]    ->  [2, 5, 2, -1, -1]
arr = [13, 7, 6, 12]      ->  [7, 6, -1, -1]
```

This is the mirror image of Next Greater Element. Swap the comparison and the stack becomes **increasing** from bottom to top.

#### Approach 1: Brute Force — scan right for each element
**Complexity:** O(n²) time, O(n) space for the answer.

**C++**
```cpp
vector<int> nextSmallerBrute(vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n, -1);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[i]) { nse[i] = arr[j]; break; }
    return nse;
}
```

**Java**
```java
class Solution {
    static int[] nextSmallerBrute(int[] arr) {
        int n = arr.length;
        int[] nse = new int[n];
        Arrays.fill(nse, -1);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (arr[j] < arr[i]) { nse[i] = arr[j]; break; }
        return nse;
    }
}
```

#### Approach 2: Optimal — traverse from the back with an increasing stack
Scan from right to left. At each `i`:
1. Pop while the top is **≥ `arr[i]`**. Those elements can never be the "next smaller" for `i` or for anything further left, because `arr[i]` is at least as small and closer.
2. The answer is the top, or −1 if the stack is empty.
3. Push `arr[i]`.

Dry run on `[4, 8, 5, 2, 25]` (right to left):
- 25: −1, push 25.
- 2: pop 25, −1, push 2.
- 5: top is 2, so 2. Push 5.
- 8: top is 5, so 5. Push 8.
- 4: pop 8 and 5, top is 2, so 2.

Result: **[2, 5, 2, −1, −1]**.

**Complexity:** O(2n) time, O(n) space.

**C++**
```cpp
vector<int> nextSmallerElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() >= arr[i]) st.pop();
        nse[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return nse;
}
```

**Java**
```java
class Solution {
    static int[] nextSmallerElement(int[] arr) {
        int n = arr.length;
        int[] nse = new int[n];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && st.peek() >= arr[i]) st.pop();
            nse[i] = st.isEmpty() ? -1 : st.peek();
            st.push(arr[i]);
        }
        return nse;
    }
}
```

#### Edge Cases & Pitfalls
- Equal values are **not** "smaller", so pop on `≥`.
- For the **previous** smaller element, scan left to right instead. Storing **indices** gives the boundaries used in Sum of Subarray Minimums and Largest Rectangle in Histogram.

#### Key Takeaways
- There are four monotonic-stack variants: next/previous × greater/smaller. Pick the scan direction by where the answer lies, and the pop condition by which elements can never be the answer again.

[↑ Contents](#contents) · [← Previous](#p265) · [Next →](#p267)

---

## FAQs

<a id="p267"></a>

### 21. Implement Min Stack

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/min-stack/) | [Watch](https://youtu.be/NdDIaH91P0g) |

#### Problem Statement
Design a stack that supports `push`, `pop`, `top` **and** `getMin` (the minimum element currently in the stack), all in **O(1)**.

```text
push 12, push 15, push 10, getMin -> 10, pop, top -> 15, getMin -> 12
```

#### Approach 1: Stack of pairs `{value, minSoFar}` (as in the video)
- **The extra field.** Each entry stores its value **and the minimum of everything at or below it**: `{val, min(val, st.top().second)}`. Use `val` itself if the stack is empty.
- **Why it works.** Popping removes the pair, and the minimum of the remaining stack is stored in the new top. Nothing has to be recomputed.

Dry run:
- push 12 gives `{12,12}`.
- push 15 gives `{15,12}`.
- push 10 gives `{10,10}`, so `getMin` = 10.
- pop. Now the top is `{15,12}`, so `top` = 15 and `getMin` = 12.

**Complexity:** O(1) for every operation. O(2n) space, since every entry stores two numbers.

**C++**
```cpp
class MinStackPairs {
    stack<pair<int, int>> st;                     // {value, min so far}
public:
    void push(int val) {
        if (st.empty()) st.push({val, val});
        else st.push({val, min(val, st.top().second)});
    }
    void pop() { st.pop(); }
    int top() { return st.top().first; }
    int getMin() { return st.top().second; }
};
```

**Java**
```java
class MinStackPairs {
    private final Deque<int[]> st = new ArrayDeque<>();   // {value, min so far}
    void push(int val) {
        if (st.isEmpty()) st.push(new int[]{val, val});
        else st.push(new int[]{val, Math.min(val, st.peek()[1])});
    }
    void pop() { st.pop(); }
    int top() { return st.peek()[0]; }
    int getMin() { return st.peek()[1]; }
}
```

#### Approach 2: Optimal — one stack plus one `mini` variable (encoded values)
Store only single values, plus a variable `mini` for the current minimum. When a **new minimum** arrives, we must remember the **previous** minimum without extra space. So we push an **encoded** value from which the previous minimum can be recovered.

- **`push(val)`:**
  - empty stack: push `val`, `mini = val`;
  - `val ≥ mini`: push `val` normally;
  - `val < mini`: push `2·val − mini`, then set `mini = val`.
- **Why the encoding is detectable.** `val < mini` means `val − mini < 0`, so `2·val − mini < val`, which equals the new `mini`. Any stored value **smaller than the current `mini`** must therefore be an encoded one.
- **`pop()`:** `x = top`. If `x < mini`, it was encoded, so restore the previous minimum: `mini = 2·mini − x`. That equals `2·val − (2·val − prevMin) = prevMin`. Then pop.
- **`top()`:** if `top < mini`, the real value is `mini`; otherwise it's `top`.
- **`getMin()`:** return `mini`.

Dry run:
- push 12: stack `[12]`, mini = 12.
- push 15: stack `[12, 15]`.
- push 10 < 12: push `2·10 − 12 = 8`, so mini = 10.
- `getMin` = 10. `top`: 8 < 10, so the real top is mini = 10.
- pop: 8 < 10, so mini = 2·10 − 8 = **12**. The previous minimum is restored.
- `top` = 15, `getMin` = 12.

**Complexity:** O(1) for every operation, O(n) space.

**C++**
```cpp
class MinStack {
    stack<long long> st;                          // long long: 2*val - mini can overflow int
    long long mini = LLONG_MAX;
public:
    void push(int value) {
        long long val = value;
        if (st.empty()) { mini = val; st.push(val); }
        else if (val >= mini) st.push(val);
        else {
            st.push(2 * val - mini);              // encoded: remembers the previous minimum
            mini = val;
        }
    }
    void pop() {
        if (st.empty()) return;
        long long x = st.top();
        st.pop();
        if (x < mini) mini = 2 * mini - x;        // undo the encoding
    }
    int top() {
        long long x = st.top();
        return (int)(x < mini ? mini : x);
    }
    int getMin() { return (int)mini; }
};
```

**Java**
```java
class MinStack {
    private final Deque<Long> st = new ArrayDeque<>();
    private long mini = Long.MAX_VALUE;
    void push(int value) {
        long val = value;
        if (st.isEmpty()) { mini = val; st.push(val); }
        else if (val >= mini) st.push(val);
        else {
            st.push(2 * val - mini);
            mini = val;
        }
    }
    void pop() {
        if (st.isEmpty()) return;
        long x = st.pop();
        if (x < mini) mini = 2 * mini - x;
    }
    int top() {
        long x = st.peek();
        return (int) (x < mini ? mini : x);
    }
    int getMin() { return (int) mini; }
}
```

#### Edge Cases & Pitfalls
- **Overflow:** `2·val − mini` can exceed the int range, e.g. val = −2³¹ and mini = 2³¹−1. Use `long long` / `long`.
- **Equal minimum:** pushing a value equal to `mini` takes the normal path (`≥`). That's correct, because popping it leaves `mini` unchanged and an equal value is still below.

#### Key Takeaways
- Two O(1) designs: store `{value, running min}` pairs, or encode the previous minimum into the pushed value whenever the minimum changes.

[↑ Contents](#contents) · [← Previous](#p266) · [Next →](#p268)

---

<a id="p268"></a>

### 22. Sliding Window Maximum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/sliding-window-maximum/) | [Watch](https://youtu.be/NwBvene4Imo) |

#### Problem Statement
Given `nums` and a window size `k`, slide the window from left to right one step at a time. Return the **maximum of each window**.

```text
nums = [1, 3, -1, -3, 5, 3, 7, 1, 6], k = 3   ->  [3, 3, 5, 5, 7, 7, 7]
nums = [1], k = 1                             ->  [1]
```

#### Approach 1: Brute Force — scan every window
For each window start `i` from 0 to n−k, take the max of `nums[i..i+k−1]`.

**Complexity:** O((n−k+1)·k) time, which is about O(n·k). O(n−k+1) space for the answer.

**C++**
```cpp
vector<int> maxSlidingWindowBrute(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> ans;
    for (int i = 0; i + k <= n; i++) {
        int mx = nums[i];
        for (int j = i; j < i + k; j++) mx = max(mx, nums[j]);
        ans.push_back(mx);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] maxSlidingWindowBrute(int[] nums, int k) {
        int n = nums.length;
        int[] ans = new int[n - k + 1];
        for (int i = 0; i + k <= n; i++) {
            int mx = nums[i];
            for (int j = i; j < i + k; j++) mx = Math.max(mx, nums[j]);
            ans[i] = mx;
        }
        return ans;
    }
}
```

#### Approach 2: Optimal — monotonic deque of indices
- **Keep a deque of indices** whose values are **decreasing** from front to back. The front is always the current window's maximum.
- **Why a deque.** The window removes from the **front** when an element leaves on the left, and the monotonic rule removes from the **back** when a bigger element arrives. So we need both ends:
  1. **Expire:** if `dq.front() ≤ i − k`, that index has left the window, so `pop_front`.
  2. **Maintain decreasing:** while `nums[dq.back()] ≤ nums[i]`, `pop_back`. Those elements are older *and* not larger, so they can never be a maximum again.
  3. `push_back(i)`.
  4. Once `i ≥ k − 1`, record `nums[dq.front()]`.

Dry run on `[1,3,−1,−3,5,3,7,1,6]`, k = 3:

| i | val | deque (values) | output |
|---|---|---|---|
| 0 | 1 | 1 | |
| 1 | 3 | 3 (1 popped) | |
| 2 | −1 | 3, −1 | 3 |
| 3 | −3 | 3, −1, −3 | 3 |
| 4 | 5 | 5 (3 expired; −3, −1 popped) | 5 |
| 5 | 3 | 5, 3 | 5 |
| 6 | 7 | 7 | 7 |
| 7 | 1 | 7, 1 | 7 |
| 8 | 6 | 7, 6 (1 popped) | 7 |

**Complexity:** O(2n) time, since each index is pushed and popped at most once. O(k) space for the deque.

**C++**
```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;                                // indices, values decreasing
    vector<int> ans;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();          // out of window
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back(); // useless smaller ones
        dq.push_back(i);
        if (i >= k - 1) ans.push_back(nums[dq.front()]);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] maxSlidingWindow(int[] nums, int k) {
        int n = nums.length;
        Deque<Integer> dq = new ArrayDeque<>();
        int[] ans = new int[n - k + 1];
        int idx = 0;
        for (int i = 0; i < n; i++) {
            if (!dq.isEmpty() && dq.peekFirst() <= i - k) dq.pollFirst();
            while (!dq.isEmpty() && nums[dq.peekLast()] <= nums[i]) dq.pollLast();
            dq.offerLast(i);
            if (i >= k - 1) ans[idx++] = nums[dq.peekFirst()];
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Store indices, not values.** Expiry is decided by position.
- **Popping `≤` on the back is fine.** Popping an equal, older element loses nothing, because the newer equal element outlives it.

#### Key Takeaways
- For "max/min of every window of size k", use a monotonic **deque**: expire from the front, maintain monotonicity from the back.

[↑ Contents](#contents) · [← Previous](#p267) · [Next →](#p269)

---

<a id="p269"></a>

### 23. Trapping Rainwater

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/trapping-rain-water/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/trapping-rain-water) | [Watch](https://youtu.be/1_5VuquLbXg) |

#### Problem Statement
`height[i]` is the height of a building (bar) of width 1. After rain, how much water is trapped between the buildings?

```text
height = [0,1,0,2,1,0,1,3,2,1,2,1]   ->  6
height = [4,2,0,3,2,5]               ->  9
```

#### Intuition — water above one index
The water at index `i` is limited by the tallest wall on its left and the tallest wall on its right. It fills up to the **shorter** of the two:

  **water[i] = min(leftMax, rightMax) − height[i]**   (only when `height[i]` is below both)

Here `leftMax` is the max of `height[0..i]` and `rightMax` is the max of `height[i..n−1]`. The total is the sum over all `i`.

#### Approach 1: Brute Force — scan both sides for every index
For each `i`, compute `leftMax` and `rightMax` by scanning.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int trapBrute(vector<int>& height) {
    int n = height.size(), total = 0;
    for (int i = 0; i < n; i++) {
        int leftMax = 0, rightMax = 0;
        for (int j = 0; j <= i; j++) leftMax = max(leftMax, height[j]);
        for (int j = i; j < n; j++) rightMax = max(rightMax, height[j]);
        total += min(leftMax, rightMax) - height[i];
    }
    return total;
}
```

**Java**
```java
class Solution {
    static int trapBrute(int[] height) {
        int n = height.length, total = 0;
        for (int i = 0; i < n; i++) {
            int leftMax = 0, rightMax = 0;
            for (int j = 0; j <= i; j++) leftMax = Math.max(leftMax, height[j]);
            for (int j = i; j < n; j++) rightMax = Math.max(rightMax, height[j]);
            total += Math.min(leftMax, rightMax) - height[i];
        }
        return total;
    }
}
```

#### Approach 2: Better — prefix max and suffix max arrays (as in the video)
Precompute both sides:
- `prefixMax[i] = max(prefixMax[i−1], h[i])`;
- `suffixMax[i] = max(suffixMax[i+1], h[i])`.

Then sum `min(prefixMax[i], suffixMax[i]) − h[i]`.

**Complexity:** O(3n) time, O(2n) space.

The video also notes a variant: keep only `suffixMax` and track `leftMax` with a variable during the final pass. That's O(n) space.

**C++**
```cpp
int trapPrefixSuffix(vector<int>& h) {
    int n = h.size();
    if (n == 0) return 0;
    vector<int> prefixMax(n), suffixMax(n);
    prefixMax[0] = h[0];
    for (int i = 1; i < n; i++) prefixMax[i] = max(prefixMax[i - 1], h[i]);
    suffixMax[n - 1] = h[n - 1];
    for (int i = n - 2; i >= 0; i--) suffixMax[i] = max(suffixMax[i + 1], h[i]);
    int total = 0;
    for (int i = 0; i < n; i++)
        total += min(prefixMax[i], suffixMax[i]) - h[i];
    return total;
}
```

**Java**
```java
class Solution {
    static int trapPrefixSuffix(int[] h) {
        int n = h.length;
        if (n == 0) return 0;
        int[] prefixMax = new int[n], suffixMax = new int[n];
        prefixMax[0] = h[0];
        for (int i = 1; i < n; i++) prefixMax[i] = Math.max(prefixMax[i - 1], h[i]);
        suffixMax[n - 1] = h[n - 1];
        for (int i = n - 2; i >= 0; i--) suffixMax[i] = Math.max(suffixMax[i + 1], h[i]);
        int total = 0;
        for (int i = 0; i < n; i++)
            total += Math.min(prefixMax[i], suffixMax[i]) - h[i];
        return total;
    }
}
```

#### Approach 3: Optimal — two pointers, O(1) space
**Key observation from the video:** the formula only needs the **smaller** of `leftMax` and `rightMax`.

- Put `l` at the left end and `r` at the right end, tracking `leftMax` and `rightMax` seen so far from each side.
- If `h[l] ≤ h[r]`: somewhere on the right there's a wall at least as tall as `h[l]` (namely `h[r]`).
  - So the left side is the limiting one, and the water at `l` depends only on `leftMax`.
  - If `h[l] < leftMax`, add `leftMax − h[l]`; otherwise update `leftMax`.
  - Then `l++`.
- Else, the mirror image: process `r` using `rightMax`, then `r−−`.

Always move the **smaller** side, because its answer is already determined.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int trap(vector<int>& h) {
    int l = 0, r = (int)h.size() - 1;
    int leftMax = 0, rightMax = 0, total = 0;
    while (l < r) {
        if (h[l] <= h[r]) {                         // left side is the limiting one
            if (h[l] < leftMax) total += leftMax - h[l];
            else leftMax = h[l];
            l++;
        } else {                                    // right side is the limiting one
            if (h[r] < rightMax) total += rightMax - h[r];
            else rightMax = h[r];
            r--;
        }
    }
    return total;
}
```

**Java**
```java
class Solution {
    static int trap(int[] h) {
        int l = 0, r = h.length - 1;
        int leftMax = 0, rightMax = 0, total = 0;
        while (l < r) {
            if (h[l] <= h[r]) {
                if (h[l] < leftMax) total += leftMax - h[l];
                else leftMax = h[l];
                l++;
            } else {
                if (h[r] < rightMax) total += rightMax - h[r];
                else rightMax = h[r];
                r--;
            }
        }
        return total;
    }
}
```

#### Edge Cases & Pitfalls
- **Edges never hold water.** The first and last bars have no wall beyond them, and the formula gives 0 for them automatically.
- **Small inputs.** Arrays with fewer than 3 bars trap nothing.

#### Key Takeaways
- Water at `i` is `min(maxLeft, maxRight) − h[i]`. Prefix/suffix maxima give O(n) time.
- Two pointers drop the space by always processing the side whose bound is already known.

[↑ Contents](#contents) · [← Previous](#p268) · [Next →](#p270)

---

<a id="p270"></a>

### 24. Largest rectangle in a histogram

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/largest-rectangle-in-histogram/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/largest-rectangle-in-histogram) | [Watch](https://youtu.be/Bzat9vgD0fs) |

#### Problem Statement
`heights[i]` is the height of a histogram bar of width 1. Return the area of the **largest rectangle** that fits inside the histogram.

```text
heights = [2, 1, 5, 6, 2, 3]   ->  10   (bars 5 and 6, width 2)
heights = [3, 2, 10, 11, 5, 10, 6, 3]  ->  25   (height 5 across indices 2..6)
heights = [2, 4]               ->  4
```

#### Intuition
- **Fix the height.** The largest rectangle has the height of some bar `i`.
- **Extend sideways.** Using bar `i` as the height, the rectangle extends left and right **until a smaller bar** blocks it.
- **The width formula.** With `pse[i]` the previous smaller index (or −1) and `nse[i]` the next smaller index (or n), the area is

  **heights[i] × (nse[i] − pse[i] − 1)**

#### Approach 1: Brute Force — expand around every bar *(not in video)*
For each `i`, walk left and right while the bars are `≥ heights[i]`.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int largestRectangleBrute(vector<int>& h) {
    int n = h.size(), best = 0;
    for (int i = 0; i < n; i++) {
        int l = i, r = i;
        while (l > 0 && h[l - 1] >= h[i]) l--;
        while (r < n - 1 && h[r + 1] >= h[i]) r++;
        best = max(best, h[i] * (r - l + 1));
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int largestRectangleBrute(int[] h) {
        int n = h.length, best = 0;
        for (int i = 0; i < n; i++) {
            int l = i, r = i;
            while (l > 0 && h[l - 1] >= h[i]) l--;
            while (r < n - 1 && h[r + 1] >= h[i]) r++;
            best = Math.max(best, h[i] * (r - l + 1));
        }
        return best;
    }
}
```

#### Approach 2: Better — precompute PSE and NSE with stacks (the video's first solution)
Compute both boundary arrays with monotonic stacks of indices, using the same code as in Next Smaller Element. Then take `max(h[i] × (nse[i] − pse[i] − 1))`.

**Complexity:** O(5n) time: 2n for each stack pass and n for the final loop. O(4n) space for two arrays and two stacks.

**C++**
```cpp
int largestRectanglePseNse(vector<int>& h) {
    int n = h.size();
    vector<int> pse(n), nse(n);
    stack<int> st;
    for (int i = 0; i < n; i++) {                       // previous smaller
        while (!st.empty() && h[st.top()] >= h[i]) st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {                  // next smaller
        while (!st.empty() && h[st.top()] >= h[i]) st.pop();
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    int best = 0;
    for (int i = 0; i < n; i++)
        best = max(best, h[i] * (nse[i] - pse[i] - 1));
    return best;
}
```

**Java**
```java
class Solution {
    static int largestRectanglePseNse(int[] h) {
        int n = h.length;
        int[] pse = new int[n], nse = new int[n];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && h[st.peek()] >= h[i]) st.pop();
            pse[i] = st.isEmpty() ? -1 : st.peek();
            st.push(i);
        }
        st.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && h[st.peek()] >= h[i]) st.pop();
            nse[i] = st.isEmpty() ? n : st.peek();
            st.push(i);
        }
        int best = 0;
        for (int i = 0; i < n; i++)
            best = Math.max(best, h[i] * (nse[i] - pse[i] - 1));
        return best;
    }
}
```

#### Approach 3: Optimal — single pass (as in the video)
Maintain an increasing stack of indices while scanning left to right. When `heights[i]` is smaller than the top, the top element has just found its **next smaller** element: index `i`. Its **previous smaller** is the element right **below it in the stack**. So pop it and compute its area immediately:
- `element = st.top()`, then pop;
- `pse = st.empty() ? −1 : st.top()`, and `nse = i`;
- `area = h[element] × (nse − pse − 1)`.

After the scan, the indices still on the stack have **no next smaller**, so use `nse = n` for them.

Dry run on `[2,1,5,6,2,3]`:
- `1` pops 2: area = 2 × (1 − (−1) − 1) = 2.
- `2` pops 6: 6 × (4 − 2 − 1) = 6. Then pops 5: 5 × (4 − 1 − 1) = **10**.
- End: pop 3 (3 × 1), then 2 (2 × 4 = 8), then 1 (1 × 6 = 6).
- Best = **10**.

**Complexity:** O(2n) time, since each index is pushed and popped once. O(n) space.

**C++**
```cpp
int largestRectangleArea(vector<int>& h) {
    int n = h.size(), best = 0;
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.top()] > h[i]) {
            int element = st.top(); st.pop();
            int nse = i;                                   // i is its next smaller
            int pse = st.empty() ? -1 : st.top();          // below it in the stack
            best = max(best, h[element] * (nse - pse - 1));
        }
        st.push(i);
    }
    while (!st.empty()) {                                  // no next smaller: nse = n
        int element = st.top(); st.pop();
        int pse = st.empty() ? -1 : st.top();
        best = max(best, h[element] * (n - pse - 1));
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int largestRectangleArea(int[] h) {
        int n = h.length, best = 0;
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && h[st.peek()] > h[i]) {
                int element = st.pop();
                int nse = i;
                int pse = st.isEmpty() ? -1 : st.peek();
                best = Math.max(best, h[element] * (nse - pse - 1));
            }
            st.push(i);
        }
        while (!st.isEmpty()) {
            int element = st.pop();
            int pse = st.isEmpty() ? -1 : st.peek();
            best = Math.max(best, h[element] * (n - pse - 1));
        }
        return best;
    }
}
```

#### Edge Cases & Pitfalls
- **Equal heights:** the single pass pops on `>`, so equal bars stay on the stack. The left-most of a run of equal bars still gets the full width when it's finally popped. The answer is correct either way.
- **Don't forget the remaining stack** after the loop. Increasing histograms are resolved only there.

#### Key Takeaways
- The "previous and next smaller" boundaries are the core of histogram problems. A single monotonic-stack pass finds both at pop time.
- This is the building block for Maximal Rectangle, which comes next.

[↑ Contents](#contents) · [← Previous](#p269) · [Next →](#p271)

---

<a id="p271"></a>

### 25. Maximum Rectangles

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/maximal-rectangle/) | [Watch](https://youtu.be/tOylVCugy9k) |

> *The sheet's video for this problem is an older take U forward recording (pre-A2Z format). The notes follow its approach.*

#### Problem Statement
Given an `n × m` binary matrix, return the area of the largest rectangle that contains **only 1s**.

```text
matrix = [[1,0,1,0,0],
          [1,0,1,1,1],
          [1,1,1,1,1],
          [1,0,0,1,0]]   ->  6   (rows 1–2, columns 2–4)
```

#### Intuition — every row is the base of a histogram
- **Turn rows into histograms.** Fix a row as the **ground**. For each column, count the consecutive 1s going **upwards** from that row; that's a building height. A 0 cuts the building to height 0.
- **Use the previous problem.** Every all-ones rectangle sits on some row with its bottom on that ground. So the answer is the maximum, over all rows, of **Largest Rectangle in Histogram** applied to that row's heights.
- **Update the heights row by row:** `height[j] = (matrix[i][j] == 1) ? height[j] + 1 : 0`.

For the example:

| row | heights | largest rectangle |
|---|---|---|
| 0 | 1 0 1 0 0 | 1 |
| 1 | 2 0 2 1 1 | 3 |
| 2 | 3 1 3 2 2 | **6** (height 2 × width 3) |
| 3 | 4 0 0 3 0 | 4 |

#### Approach 1: Brute Force — check every rectangle *(not in video)*
Enumerate all top-left and bottom-right corners and check whether the rectangle is all 1s. That's O((nm)³) naively, or O((nm)²) with 2-D prefix sums. It's far too slow, so it's shown only as the baseline.

**C++**
```cpp
int maximalRectangleBrute(vector<vector<char>>& matrix) {
    int n = matrix.size();
    if (n == 0) return 0;
    int m = matrix[0].size();
    vector<vector<int>> ps(n + 1, vector<int>(m + 1, 0));    // 2-D prefix sums of 1s
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ps[i + 1][j + 1] = ps[i][j + 1] + ps[i + 1][j] - ps[i][j] + (matrix[i][j] == '1');
    int best = 0;
    for (int r1 = 0; r1 < n; r1++)
        for (int c1 = 0; c1 < m; c1++)
            for (int r2 = r1; r2 < n; r2++)
                for (int c2 = c1; c2 < m; c2++) {
                    int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                    int ones = ps[r2 + 1][c2 + 1] - ps[r1][c2 + 1] - ps[r2 + 1][c1] + ps[r1][c1];
                    if (ones == area) best = max(best, area);
                }
    return best;
}
```

**Java**
```java
class Solution {
    static int maximalRectangleBrute(char[][] matrix) {
        int n = matrix.length;
        if (n == 0) return 0;
        int m = matrix[0].length;
        int[][] ps = new int[n + 1][m + 1];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ps[i + 1][j + 1] = ps[i][j + 1] + ps[i + 1][j] - ps[i][j] + (matrix[i][j] == '1' ? 1 : 0);
        int best = 0;
        for (int r1 = 0; r1 < n; r1++)
            for (int c1 = 0; c1 < m; c1++)
                for (int r2 = r1; r2 < n; r2++)
                    for (int c2 = c1; c2 < m; c2++) {
                        int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                        int ones = ps[r2 + 1][c2 + 1] - ps[r1][c2 + 1] - ps[r2 + 1][c1] + ps[r1][c1];
                        if (ones == area) best = Math.max(best, area);
                    }
        return best;
    }
}
```

#### Approach 2: Optimal — row-by-row heights + largest rectangle in histogram
**Complexity:**
- Time: O(n·m) to update the heights, plus O(n·2m) for the histogram passes, so O(n·m) overall.
- Space: O(m) for the heights and the stack.

**C++**
```cpp
int largestHistogram(vector<int>& h) {
    int n = h.size(), best = 0;
    stack<int> st;
    for (int i = 0; i <= n; i++) {
        int cur = (i == n) ? 0 : h[i];               // sentinel 0 flushes the stack
        while (!st.empty() && h[st.top()] > cur) {
            int el = st.top(); st.pop();
            int pse = st.empty() ? -1 : st.top();
            best = max(best, h[el] * (i - pse - 1));
        }
        st.push(i);
    }
    return best;
}
int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int m = matrix[0].size(), best = 0;
    vector<int> height(m, 0);
    for (auto& row : matrix) {
        for (int j = 0; j < m; j++)
            height[j] = (row[j] == '1') ? height[j] + 1 : 0;   // building heights
        best = max(best, largestHistogram(height));
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int largestHistogram(int[] h) {
        int n = h.length, best = 0;
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 0; i <= n; i++) {
            int cur = (i == n) ? 0 : h[i];
            while (!st.isEmpty() && h[st.peek()] > cur) {
                int el = st.pop();
                int pse = st.isEmpty() ? -1 : st.peek();
                best = Math.max(best, h[el] * (i - pse - 1));
            }
            st.push(i);
        }
        return best;
    }
    static int maximalRectangle(char[][] matrix) {
        if (matrix.length == 0) return 0;
        int m = matrix[0].length, best = 0;
        int[] height = new int[m];
        for (char[] row : matrix) {
            for (int j = 0; j < m; j++)
                height[j] = (row[j] == '1') ? height[j] + 1 : 0;
            best = Math.max(best, largestHistogram(height));
        }
        return best;
    }
}
```

#### Edge Cases & Pitfalls
- **Reset on zero.** A 0 resets its column's height to 0. It does not merely stop adding, because a rectangle can't pass through a 0.
- **Char vs int.** LeetCode passes `char` `'0'`/`'1'`. Other versions pass `int` 0/1, so adjust the comparison.
- **The sentinel trick.** Treating index `n` as height 0 flushes all remaining bars without a separate loop.

#### Key Takeaways
- This reduces a 2-D problem to n instances of the 1-D histogram problem by accumulating column heights.

[↑ Contents](#contents) · [← Previous](#p270) · [Next →](#p272)

---

<a id="p272"></a>

### 26. Stock span problem

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/online-stock-span/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/stock-span-problem) | [Watch](https://youtu.be/eay-zoSRkVc) |

#### Problem Statement
Design `StockSpanner` with `next(price)`. Each call returns the **span** of today's price: the number of consecutive days, ending today and going backwards, on which the price was **≤ today's price**.

```text
prices: 7  2  1  3  3  1  8
spans:  1  1  1  3  4  1  7
```

#### Approach 1: Brute Force — store all prices and count backwards
Keep every price in a list. On `next(price)`, start `count = 1` for today and walk back while `arr[j] ≤ price`.

**Complexity:**
- Time: O(number of days so far) per `next` call. With many calls, describe it to the interviewer as O(total calls) each.
- Space: O(total calls).

**C++**
```cpp
class StockSpannerBrute {
    vector<int> arr;
public:
    int next(int price) {
        arr.push_back(price);
        int count = 1;
        for (int j = (int)arr.size() - 2; j >= 0; j--) {
            if (arr[j] <= price) count++;
            else break;
        }
        return count;
    }
};
```

**Java**
```java
class StockSpannerBrute {
    private final List<Integer> arr = new ArrayList<>();
    int next(int price) {
        arr.add(price);
        int count = 1;
        for (int j = arr.size() - 2; j >= 0; j--) {
            if (arr.get(j) <= price) count++;
            else break;
        }
        return count;
    }
}
```

#### Approach 2: Optimal — previous greater element with a stack of (price, index)
The span ends at the **previous strictly greater** price. So:

  **span = today's index − index of the previous greater element**

Use −1 if there is no previous greater element, so the span is `index + 1`.

This is the Previous Greater Element pattern, computed **online**:
- Keep a decreasing stack of `{price, index}`.
- On each call:
  1. `index++`;
  2. pop while `top.price ≤ price`;
  3. `span = index − (stack empty ? −1 : top.index)`;
  4. push `{price, index}`.

Dry run:
- 7 (index 0): stack empty, span = 0 − (−1) = 1.
- 2 (index 1): top 7, span 1.
- 1 (index 2): span 1.
- 3 (index 3): pop 1 and 2, top 7 at index 0, span = 3.
- 3 (index 4): pop 3, top 7, span = 4.
- 1 (index 5): span 1.
- 8 (index 6): pop everything, span = 7.

**Complexity:** amortised O(1) per call, because each price is pushed and popped once. O(n) space in the worst case.

**C++**
```cpp
class StockSpanner {
    stack<pair<int, int>> st;                    // {price, index}, prices decreasing
    int index = -1;
public:
    int next(int price) {
        index++;
        while (!st.empty() && st.top().first <= price) st.pop();
        int ans = index - (st.empty() ? -1 : st.top().second);
        st.push({price, index});
        return ans;
    }
};
```

**Java**
```java
class StockSpanner {
    private final Deque<int[]> st = new ArrayDeque<>();   // {price, index}
    private int index = -1;
    int next(int price) {
        index++;
        while (!st.isEmpty() && st.peek()[0] <= price) st.pop();
        int ans = index - (st.isEmpty() ? -1 : st.peek()[1]);
        st.push(new int[]{price, index});
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Pop on `≤`.** Equal prices count towards the span.
- **Store indices, not just prices.** The span is a distance.

#### Key Takeaways
- "How far back until something bigger" is a previous greater element problem. Online queries work naturally with a stack of `(value, index)`.

[↑ Contents](#contents) · [← Previous](#p271) · [Next →](#p273)

---

<a id="p273"></a>

### 27. Celebrity Problem

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Core | Yes | [LeetCode](https://leetcode.com/problems/find-the-celebrity/) | [Watch](https://youtu.be/cEadsbTeze4) |

#### Problem Statement
At a party of `n` people (0 … n−1), `M[i][j] = 1` means person `i` **knows** person `j`. The relation isn't necessarily symmetric. A **celebrity** is someone whom **everyone else knows** but who **knows nobody**. Return the celebrity's index, or −1.

```text
M = [[0,1,1,0],
     [0,0,0,0],
     [0,1,0,0],
     [1,1,0,0]]   ->  1   (everyone knows 1; row 1 is all zeros)
```

#### Approach 1: Brute Force — count who knows whom
- Build `knowMe[j]` (how many people know `j`) and `iKnow[i]` (how many people `i` knows) by scanning the whole matrix.
- The celebrity is the `i` with `knowMe[i] == n−1` and `iKnow[i] == 0`.

**Complexity:** O(n²) time, O(2n) space.

**C++**
```cpp
int celebrityBrute(vector<vector<int>>& M) {
    int n = M.size();
    vector<int> knowMe(n, 0), iKnow(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && M[i][j] == 1) { knowMe[j]++; iKnow[i]++; }
    for (int i = 0; i < n; i++)
        if (knowMe[i] == n - 1 && iKnow[i] == 0) return i;
    return -1;
}
```

**Java**
```java
class Solution {
    static int celebrityBrute(int[][] M) {
        int n = M.length;
        int[] knowMe = new int[n], iKnow = new int[n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j && M[i][j] == 1) { knowMe[j]++; iKnow[i]++; }
        for (int i = 0; i < n; i++)
            if (knowMe[i] == n - 1 && iKnow[i] == 0) return i;
        return -1;
    }
}
```

#### Approach 2: Optimal — two-pointer elimination, then verify
- **At most one celebrity exists.** If A and B were both celebrities, A would have to know B, contradicting "A knows nobody".
- **Each comparison eliminates someone.** For any pair `(a, b)`:
  - if `a` knows `b`, then `a` is **not** a celebrity;
  - if `b` knows `a`, then `b` is not;
  - if neither knows the other, then **neither** is a celebrity, because a celebrity must be known by everyone.
- **The elimination loop.** Keep `top = 0` and `down = n−1`. While `top < down`:
  - `M[top][down] == 1` → `top++`;
  - else `M[down][top] == 1` → `down−−`;
  - else → `top++` and `down−−`.
- **Verify.** If `top > down`, there is no candidate. Otherwise check `top`: its whole row must be 0 and its whole column 1, except the diagonal.

Dry run on the example:
- (0,3): 0 doesn't know 3, but 3 knows 0, so down = 2.
- (0,2): 0 knows 2, so top = 1.
- (1,2): 1 doesn't know 2, but 2 knows 1, so down = 1.
- Candidate 1 is verified: row 1 is all zeros and column 1 is all ones off the diagonal. Answer: **1**.

**Complexity:** O(2n) time: n for elimination, n for verification. O(1) space.

**C++**
```cpp
int celebrity(vector<vector<int>>& M) {
    int n = M.size();
    int top = 0, down = n - 1;
    while (top < down) {
        if (M[top][down] == 1) top++;            // top knows someone -> not celeb
        else if (M[down][top] == 1) down--;      // down knows someone -> not celeb
        else { top++; down--; }                  // neither is known by the other
    }
    if (top > down) return -1;
    for (int i = 0; i < n; i++) {                // verify the candidate
        if (i == top) continue;
        if (M[top][i] == 1 || M[i][top] == 0) return -1;
    }
    return top;
}
```

**Java**
```java
class Solution {
    static int celebrity(int[][] M) {
        int n = M.length;
        int top = 0, down = n - 1;
        while (top < down) {
            if (M[top][down] == 1) top++;
            else if (M[down][top] == 1) down--;
            else { top++; down--; }
        }
        if (top > down) return -1;
        for (int i = 0; i < n; i++) {
            if (i == top) continue;
            if (M[top][i] == 1 || M[i][top] == 0) return -1;
        }
        return top;
    }
}
```

#### Edge Cases & Pitfalls
- **Always verify the survivor.** Elimination only proves that nobody *else* can be the celebrity.
- **The diagonal.** Skip `M[i][i]`, which may be 0 or 1 depending on the input.
- **LeetCode 277 variant.** There you only have a `knows(a, b)` API. Use the same logic with API calls instead of matrix lookups.

#### Key Takeaways
- For "find the unique element satisfying a pairwise property", compare two candidates and eliminate one per step. That's O(n) instead of O(n²). A stack of candidates works too; two pointers is the same idea without the stack.

[↑ Contents](#contents) · [← Previous](#p272) · [Next →](#p274)

---

<a id="p274"></a>

### 28. LRU Cache

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/lru-cache/) | [Watch](https://youtu.be/z9bJUPxzFOw) |

#### Problem Statement
Design an **LRU (least recently used) cache** with a fixed `capacity`:
- `get(key)` returns the value, or −1 if the key is absent. A `get` counts as a **use**.
- `put(key, value)` inserts or updates the key. If that pushes the size over `capacity`, **evict the least recently used** key.

Both must run in **O(1)** on average.

```text
LRUCache(2); put(1,1); put(2,2); get(1) -> 1; put(3,3) (evicts 2); get(2) -> -1;
put(4,4) (evicts 1); get(1) -> -1; get(3) -> 3; get(4) -> 4
```

#### Intuition — which data structures?
We need two things:
1. **O(1) lookup by key**: a **hash map**.
2. **O(1) "move to most-recent" and "remove least-recent"**: a **doubly linked list** ordered by recency. A node can be unlinked in O(1) if we can reach it directly, and the map gives us exactly that pointer.

So: `map<key, Node*>` plus a DLL. Dummy **head** and **tail** nodes remove the edge cases. The most recent node sits right after `head`, and the least recent sits right before `tail`.

#### Approach: Hash map + doubly linked list (as in the video)
- `get(key)`:
  - not in the map: return −1;
  - otherwise unlink the node, re-insert it right after `head` (it's now most recent), and return its value.
- `put(key, value)`:
  - **key exists:** update the value and move the node to the front;
  - **key is new and the cache is full:** evict `tail->prev` (the LRU node), erasing it from the map too;
  - in both new-key cases: create the node, insert it after `head`, and add it to the map.

Dry run, capacity 2:
- put(1), put(2): list = head, 2, 1, tail.
- get(1): move 1 to the front, giving 1, 2.
- put(3): full, so evict 2 (just before tail). List = 3, 1.
- get(2) = −1.
- put(4): evict 1. List = 4, 3.

**Complexity:** O(1) average for both operations, assuming an O(1) hash map. O(capacity) space.

**C++**
```cpp
class LRUCache {
    struct Node {
        int key, val;
        Node *prev, *next;
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };
    int cap;
    unordered_map<int, Node*> mpp;
    Node *head, *tail;                                   // dummies
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void insertAfterHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
public:
    LRUCache(int capacity) : cap(capacity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }
    int get(int key) {
        if (!mpp.count(key)) return -1;
        Node* node = mpp[key];
        removeNode(node);                                // mark as most recently used
        insertAfterHead(node);
        return node->val;
    }
    void put(int key, int value) {
        if (mpp.count(key)) {
            Node* node = mpp[key];
            node->val = value;
            removeNode(node);
            insertAfterHead(node);
            return;
        }
        if ((int)mpp.size() == cap) {                    // evict the LRU node
            Node* lru = tail->prev;
            mpp.erase(lru->key);
            removeNode(lru);
            delete lru;
        }
        Node* node = new Node(key, value);
        insertAfterHead(node);
        mpp[key] = node;
    }
};
```

**Java**
```java
class LRUCache {
    private static class Node {
        int key, val;
        Node prev, next;
        Node(int k, int v) { key = k; val = v; }
    }
    private final int cap;
    private final Map<Integer, Node> mpp = new HashMap<>();
    private final Node head = new Node(-1, -1), tail = new Node(-1, -1);
    LRUCache(int capacity) {
        cap = capacity;
        head.next = tail;
        tail.prev = head;
    }
    private void removeNode(Node node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }
    private void insertAfterHead(Node node) {
        node.next = head.next;
        node.prev = head;
        head.next.prev = node;
        head.next = node;
    }
    int get(int key) {
        Node node = mpp.get(key);
        if (node == null) return -1;
        removeNode(node);
        insertAfterHead(node);
        return node.val;
    }
    void put(int key, int value) {
        Node node = mpp.get(key);
        if (node != null) {
            node.val = value;
            removeNode(node);
            insertAfterHead(node);
            return;
        }
        if (mpp.size() == cap) {
            Node lru = tail.prev;
            mpp.remove(lru.key);
            removeNode(lru);
        }
        node = new Node(key, value);
        insertAfterHead(node);
        mpp.put(key, node);
    }
}
```

#### Edge Cases & Pitfalls
- **Store the key inside the node.** At eviction time you only have the node and must erase its key from the map.
- **Updating an existing key** is a use too, so move it to the front. It must not trigger an eviction.
- **Dummy head/tail** avoid null checks when the list is empty or has one element.

#### Key Takeaways
- Hash map plus doubly linked list is *the* O(1) recency structure. Java's `LinkedHashMap` with access order (overriding `removeEldestEntry`) packages the same idea.

[↑ Contents](#contents) · [← Previous](#p273) · [Next →](#p275)

---

<a id="p275"></a>

### 29. LFU Cache

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/lfu-cache/) | [Watch](https://youtu.be/0PSB9y8ehbk) |

#### Problem Statement
Design an **LFU (least frequently used) cache** with a fixed `capacity`:
- `get(key)` returns the value, or −1. A get counts as a **use** and increments the key's frequency.
- `put(key, value)` inserts or updates the key, which also counts as a use. When the cache is full, evict the key with the **lowest use frequency**. On a **tie**, evict the **least recently used** among those keys.

Both must run in **O(1)**.

```text
LFUCache(2); put(1,1); put(2,2); get(1) -> 1; put(3,3) (evicts 2: freq 1 < freq 2 of key 1);
get(2) -> -1; get(3) -> 3; put(4,4) (keys 1 and 3 both have freq 2; 1 is LRU -> evict 1);
get(1) -> -1; get(3) -> 3; get(4) -> 4
```

The video's prerequisite is LRU Cache.

#### Intuition — one LRU list per frequency
- **Group by frequency.** Keys with the same frequency form a group, and *within* each group we need LRU order. So keep a **separate doubly linked list per frequency**, each behaving exactly like the LRU list: newest after its head, oldest before its tail.
- **Two hash maps:**
  - `keyNode`: key → node (the node stores key, value and freq);
  - `freqList`: freq → DLL of the nodes with that frequency.
- **Track `minFreq`**, the smallest frequency present, so eviction is O(1): remove the tail of `freqList[minFreq]`.

#### Approach: `keyNode` + `freqList` + `minFreq` (as in the video)
- **`touch(node)`, i.e. one use:**
  1. remove the node from `freqList[f]`;
  2. if that list is now empty **and** `f == minFreq`, do `minFreq++`;
  3. `node.freq++` and insert it at the front of `freqList[f+1]`.
- **`get(key)`:** if the key is missing, return −1. Otherwise `touch` the node and return its value.
- **`put(key, value)`:**
  - **Existing key:** update the value and `touch` it.
  - **New key:**
    1. If the cache is full, evict the **last** node of `freqList[minFreq]`, which is the least recent among the least frequent, and erase it from `keyNode`.
    2. Create the node with freq 1 and insert it into `freqList[1]`.
    3. Set `minFreq = 1`, because a brand-new key always has the minimum frequency.

**Complexity:** O(1) average for `get` and `put`. O(capacity) space.

**C++**
```cpp
class LFUCache {
    struct Node {
        int key, val, freq;
        Node *prev, *next;
        Node(int k, int v) : key(k), val(v), freq(1), prev(nullptr), next(nullptr) {}
    };
    struct DList {                                       // LRU-ordered list with dummies
        Node *head, *tail;
        int size = 0;
        DList() {
            head = new Node(-1, -1); tail = new Node(-1, -1);
            head->next = tail; tail->prev = head;
        }
        void addFront(Node* n) {
            n->next = head->next; n->prev = head;
            head->next->prev = n; head->next = n;
            size++;
        }
        void remove(Node* n) {
            n->prev->next = n->next; n->next->prev = n->prev;
            size--;
        }
    };
    int cap, minFreq = 0;
    unordered_map<int, Node*> keyNode;
    unordered_map<int, DList*> freqList;
    DList* listOf(int f) {
        if (!freqList.count(f)) freqList[f] = new DList();
        return freqList[f];
    }
    void touch(Node* node) {                             // one more use
        DList* l = freqList[node->freq];
        l->remove(node);
        if (node->freq == minFreq && l->size == 0) minFreq++;
        node->freq++;
        listOf(node->freq)->addFront(node);
    }
public:
    LFUCache(int capacity) : cap(capacity) {}
    int get(int key) {
        if (!keyNode.count(key)) return -1;
        Node* node = keyNode[key];
        touch(node);
        return node->val;
    }
    void put(int key, int value) {
        if (cap == 0) return;
        if (keyNode.count(key)) {
            Node* node = keyNode[key];
            node->val = value;
            touch(node);
            return;
        }
        if ((int)keyNode.size() == cap) {                // evict LRU among least frequent
            DList* l = freqList[minFreq];
            Node* victim = l->tail->prev;
            l->remove(victim);
            keyNode.erase(victim->key);
            delete victim;
        }
        Node* node = new Node(key, value);
        listOf(1)->addFront(node);
        keyNode[key] = node;
        minFreq = 1;
    }
};
```

**Java**
```java
class LFUCache {
    private static class Node {
        int key, val, freq = 1;
        Node prev, next;
        Node(int k, int v) { key = k; val = v; }
    }
    private static class DList {
        final Node head = new Node(-1, -1), tail = new Node(-1, -1);
        int size = 0;
        DList() { head.next = tail; tail.prev = head; }
        void addFront(Node n) {
            n.next = head.next; n.prev = head;
            head.next.prev = n; head.next = n;
            size++;
        }
        void remove(Node n) {
            n.prev.next = n.next; n.next.prev = n.prev;
            size--;
        }
    }
    private final int cap;
    private int minFreq = 0;
    private final Map<Integer, Node> keyNode = new HashMap<>();
    private final Map<Integer, DList> freqList = new HashMap<>();
    LFUCache(int capacity) { cap = capacity; }
    private void touch(Node node) {
        DList l = freqList.get(node.freq);
        l.remove(node);
        if (node.freq == minFreq && l.size == 0) minFreq++;
        node.freq++;
        freqList.computeIfAbsent(node.freq, f -> new DList()).addFront(node);
    }
    int get(int key) {
        Node node = keyNode.get(key);
        if (node == null) return -1;
        touch(node);
        return node.val;
    }
    void put(int key, int value) {
        if (cap == 0) return;
        Node node = keyNode.get(key);
        if (node != null) {
            node.val = value;
            touch(node);
            return;
        }
        if (keyNode.size() == cap) {
            DList l = freqList.get(minFreq);
            Node victim = l.tail.prev;
            l.remove(victim);
            keyNode.remove(victim.key);
        }
        node = new Node(key, value);
        freqList.computeIfAbsent(1, f -> new DList()).addFront(node);
        keyNode.put(key, node);
        minFreq = 1;
    }
}
```

#### Edge Cases & Pitfalls
- **`capacity == 0`:** every put is a no-op.
- **`minFreq` only ever needs `+1` when it changes** inside `touch`, because the touched node moves to `f + 1`. On insertion of a new key it resets to 1.
- **Evict before inserting the new key.** Otherwise the new key, with freq 1, would itself be the victim.

#### Key Takeaways
- LFU = a map of frequency → LRU list, plus a key → node map, plus `minFreq`. It's the LRU design generalised to frequency buckets.

[↑ Contents](#contents) · [← Previous](#p274) · [Next →](#p276)

---

<a id="p276"></a>

### 30. Number of Greater Elements to the Right

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Stack / Queues › FAQs | Core | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an array `arr` and a list of query indices, return, for each query index `i`, the **number of elements to the right of `i` that are strictly greater** than `arr[i]`.

```text
arr = [3, 4, 2, 7, 5, 8, 10, 6], queries = [0, 5]   ->  [6, 1]
(right of 3: 4, 7, 5, 8, 10, 6 -> 6 greater; right of 8: 10 -> 1)
```

This is the counting cousin of Next Greater Element. A monotonic stack finds only the **first** greater element, not how many there are.

#### Approach 1: Brute Force — scan right for each query
**Complexity:** O(n·q) time, O(q) space for the answers. This is fine for GfG's small query counts.

**C++**
```cpp
vector<int> countGreaterBrute(vector<int>& arr, vector<int>& queries) {
    int n = arr.size();
    vector<int> ans;
    for (int idx : queries) {
        int cnt = 0;
        for (int j = idx + 1; j < n; j++)
            if (arr[j] > arr[idx]) cnt++;
        ans.push_back(cnt);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] countGreaterBrute(int[] arr, int[] queries) {
        int n = arr.length;
        int[] ans = new int[queries.length];
        for (int q = 0; q < queries.length; q++) {
            int idx = queries[q], cnt = 0;
            for (int j = idx + 1; j < n; j++)
                if (arr[j] > arr[idx]) cnt++;
            ans[q] = cnt;
        }
        return ans;
    }
}
```

#### Approach 2: Optimal for many queries — Fenwick tree (BIT) from the right
Precompute `greater[i]` for **every** index, then answer each query in O(1):
- Coordinate-compress the values to ranks `1…m`.
- Scan `i` from `n−1` down to `0`, with a BIT counting how many of the elements already seen (all of them to the right of `i`) have each rank:
  - `greater[i]` = (elements seen so far) − (number seen with rank ≤ rank(arr[i]));
  - then add rank(arr[i]) to the BIT.

**Complexity:** O(n log n + q) time, O(n) space.

**C++**
```cpp
vector<int> countGreaterBIT(vector<int>& arr, vector<int>& queries) {
    int n = arr.size();
    vector<int> vals(arr.begin(), arr.end());
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();
    vector<int> bit(m + 1, 0), greater(n);
    auto add = [&](int i) { for (; i <= m; i += i & -i) bit[i]++; };
    auto sum = [&](int i) { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; };
    for (int i = n - 1, seen = 0; i >= 0; i--, seen++) {
        int r = lower_bound(vals.begin(), vals.end(), arr[i]) - vals.begin() + 1;
        greater[i] = seen - sum(r);                  // seen elements with rank > r
        add(r);
    }
    vector<int> ans;
    for (int idx : queries) ans.push_back(greater[idx]);
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] countGreaterBIT(int[] arr, int[] queries) {
        int n = arr.length;
        int[] vals = Arrays.stream(arr).distinct().sorted().toArray();
        int m = vals.length;
        int[] bit = new int[m + 1], greater = new int[n];
        for (int i = n - 1, seen = 0; i >= 0; i--, seen++) {
            int r = Arrays.binarySearch(vals, arr[i]) + 1;
            int s = 0;
            for (int k = r; k > 0; k -= k & -k) s += bit[k];
            greater[i] = seen - s;
            for (int k = r; k <= m; k += k & -k) bit[k]++;
        }
        int[] ans = new int[queries.length];
        for (int q = 0; q < queries.length; q++) ans[q] = greater[queries[q]];
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Strictly greater.** Equal values are not counted; that's why we subtract `sum(r)`, which includes equal ranks.
- **Merge sort works too.** A merge-sort-based "count greater to the right" also gives O(n log n), using the same idea as counting inversions.

#### Key Takeaways
- First greater → monotonic stack. **How many** greater → order statistics: BIT, merge sort, or brute force for tiny inputs.

[↑ Contents](#contents) · [← Previous](#p275)

---
