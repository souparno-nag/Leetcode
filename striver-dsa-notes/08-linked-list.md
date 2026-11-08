# Linked-List — Striver's A2Z DSA Sheet Notes

Section 8 of 20 · 43 problems · 43 with video, 0 without · [All sections](00-index.md)

[← Recursion](07-recursion.md) | [Bit Manipulation →](09-bit-manipulation.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Fundamentals (Single LL)**

1. [Traversal in Linked List](#p165) — Basic
2. [Deletion of the head of LL](#p166) — Core
3. [Deletion of the tail of Linked List](#p167) — Core
4. [Deletion of the Kth element of Linked List](#p168) — Core
5. [Delete the element with value X](#p169) — Core
6. [Insertion at the head of Linked List](#p170) — Core
7. [Insertion at the tail of Linked List](#p171) — Core
8. [Insertion at the Kth position of Linked List](#p172) — Core
9. [Insertion before the value X in Linked List](#p173) — Core
10. [Find the length of the Linked List](#p174) — Basic
11. [Search in Linked List](#p175) — Core

**Fundamentals (Doubly LL)**

12. [Convert Array to Doubly Linked List](#p176) — Core
13. [Delete Tail of Doubly Linked List](#p177) — Core
14. [Delete Kth Element of Doubly Linked List](#p178) — Core
15. [Removing given node in Doubly Linked List](#p179) — Core
16. [Insert node before head in Doubly Linked List](#p180) — Core
17. [Insert node before tail in Doubly Linked List](#p181) — Core
18. [Insert node before (kth node) in Doubly Linked List](#p182) — Core
19. [Insert before given node in Doubly Linked List](#p183) — Core
20. [Delete head of Doubly Linked List](#p184) — Core
21. [Reverse a Doubly Linked List](#p185) — Core

**Logic Building**

22. [Add two numbers in Linked List](#p186) — Core · *video not transcribed*
23. [Segregate odd and even nodes in Linked List](#p187) — Core
24. [Sort a Linked List of 0's 1's and 2's](#p188) — Core
25. [Remove Nth node from the back of the LL](#p189) — Core
26. [Reverse a LL](#p190) — Core

**FAQs (Medium)**

27. [Add one to a number represented by LL](#p191) — Core
28. [Find Middle of Linked List](#p192) — Basic
29. [Delete the middle node in LL](#p193) — Core
30. [Check if LL is palindrome or not](#p194) — Core
31. [Find the intersection point of Y LL](#p195) — Core
32. [Detect a loop in LL](#p196) — Core
33. [Find the starting point in LL](#p197) — Core
34. [Length of loop in LL](#p198) — Core

**FAQs (Hard)**

35. [Reverse LL in group of given size K](#p199) — Pro
36. [Rotate a LL](#p200) — Core
37. [Merge two Sorted Lists](#p201) — Basic
38. [Flattening of LL](#p202) — Pro
39. [Sort LL](#p203) — Core
40. [Clone a LL with random and next pointer](#p204) — Pro

**FAQS (DLL)**

41. [Delete all occurrences of a key in DLL](#p205) — Core
42. [Remove duplicates from sorted DLL](#p206) — Core
43. [Find Pairs with Given Sum in Doubly Linked List](#p207) — Core

---

## Fundamentals (Single LL)

<a id="p165"></a>

### 1. Traversal in Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Basic | Yes | — | [Watch from 36:45](https://youtu.be/Nq7ok-OyEpg?t=2205) |

> *The sheet gives no video for this problem. The notes follow Striver's Linked List lecture 1 (Nq7ok-OyEpg), which also covers Length (#174) and Search (#175). The traversal part starts at about 36:45.*

#### Problem Statement
Given the `head` of a singly linked list, visit every node in order. For example, print the values or return them as an array.

```text
head: 12 -> 5 -> 8 -> 7 -> null   ->   [12, 5, 8, 7]
```

#### Background — what a linked list is (from the lecture)
- An **array** has a **fixed size** and sits in **contiguous** memory, so index `i` is right after index `i − 1`. It can't grow or shrink.
- A **linked list** stores each element in a **node** that can live **anywhere in the heap**. Each node holds the **data** and a **pointer to the next node**. The first node is the **head**. The last node's `next` is `null` / `nullptr`, and that node is the **tail**.
- Because nodes don't have to be adjacent, the list can **grow and shrink** freely: to add a node, create it anywhere and update one `next` pointer.
- **Where it's used:** stacks and queues, and browser back/forward history, where you don't know in advance how many pages you'll visit. A list with a `prev` pointer as well is a doubly linked list, covered later.
- **Node type:**
  - In C++, use a `struct` or `class` with `int data` and `Node* next`, plus constructors. Prefer `class` when you need OOP features.
  - In Java, use a `class`. There are no pointers, so a field of type `Node` holds a reference.
  - Converting between the two languages means: remove the `*`, change `->` to `.`, and change `nullptr` to `null`.
- **Memory per node:** 4 bytes for the int plus 4 bytes for a pointer on a 32-bit system, or 4 + 8 on a 64-bit system.
- `new Node(x)` returns a pointer (C++) or reference (Java) to a heap object. Use it for every node.

#### Building a list from an array (lecture: array → LL)
Make `head` from `arr[0]` and keep a `mover` at the last node built. For each remaining element, create `temp`, link it with `mover->next = temp`, then advance `mover = temp`. Return `head`. Problems always hand you the head, never the whole list. This takes O(n).

#### Approach: Iterative traversal with a temporary pointer
**Rule 1 of linked lists: never move `head` itself.** If you do, you lose the start of the list. Copy it into `temp` and move that instead:

```text
temp = head
while temp != null:
    visit(temp.data)
    temp = temp.next
```

**Complexity:** O(n) time, O(1) extra space, plus whatever output you build.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int data1, Node* next1) { data = data1; next = next1; }
    Node(int data1) { data = data1; next = nullptr; }
};

Node* convertArr2LL(vector<int>& arr) {
    if (arr.empty()) return nullptr;
    Node* head = new Node(arr[0]);
    Node* mover = head;
    for (int i = 1; i < (int)arr.size(); i++) {
        Node* temp = new Node(arr[i]);
        mover->next = temp;           // link the new node
        mover = temp;                 // advance (same as mover = mover->next)
    }
    return head;
}

vector<int> traverse(Node* head) {
    vector<int> out;
    Node* temp = head;                // never tamper with head
    while (temp != nullptr) {
        out.push_back(temp->data);
        temp = temp->next;
    }
    return out;
}
```

**Java**
```java
class Node {
    int data;
    Node next;
    Node(int data1, Node next1) { this.data = data1; this.next = next1; }
    Node(int data1) { this.data = data1; this.next = null; }
}

class Solution {
    static Node convertArr2LL(int[] arr) {
        if (arr.length == 0) return null;
        Node head = new Node(arr[0]);
        Node mover = head;
        for (int i = 1; i < arr.length; i++) {
            Node temp = new Node(arr[i]);
            mover.next = temp;           // link the new node
            mover = temp;                // advance
        }
        return head;
    }

    static List<Integer> traverse(Node head) {
        List<Integer> out = new ArrayList<>();
        Node temp = head;                // never tamper with head
        while (temp != null) {
            out.add(temp.data);
            temp = temp.next;
        }
        return out;
    }
}
```

#### Recursive traversal *(not in lecture)*
Visit `head`, then recurse on `head->next`. This takes O(n) time but also O(n) stack space, so the iterative version is preferred.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};
void traverseRec(Node* node, vector<int>& out) {
    if (node == nullptr) return;
    out.push_back(node->data);
    traverseRec(node->next, out);
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } }
class Solution {
    static void traverseRec(Node node, List<Integer> out) {
        if (node == null) return;
        out.add(node.data);
        traverseRec(node.next, out);
    }
}
```

#### Key Takeaways
- A linked list is a chain of `(data, next)` nodes scattered in memory. You only ever hold the `head`.
- The traversal template `temp = head; while (temp) { …; temp = temp->next; }` is the basis of almost every linked-list problem.

[↑ Contents](#contents) · [Next →](#p166)

---

<a id="p166"></a>

### 2. Deletion of the head of LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | No | [LeetCode](https://leetcode.com/problems/delete-node-in-a-linked-list/) | [Watch](https://youtu.be/VaECK03Dz-g) |

> *Lecture 2 of the Linked List playlist covers 8 problems: 4 deletions (#166–169) and 4 insertions (#170–173). Every function **returns the (possibly new) head**.*

#### Problem Statement
Delete the **head** (first node) of a singly linked list and return the new head.

```text
12 -> 5 -> 8 -> 7 -> null   ->   5 -> 8 -> 7 -> null
null                        ->   null
```

#### Approach: Move head forward, free the old head
1. **Edge case:** if the list is empty, return `head` unchanged. Every linked-list function needs this check.
2. Save `temp = head`, then set `head = head->next`.
3. **Free the old node.**
   - In C++, call `delete temp` (or `free`). If you only move `head` forward, the old node still sits in the heap.
   - In Java, you don't free it yourself. The **garbage collector** reclaims it once nothing references it, though maybe not immediately.
4. Return `head`.

**Complexity:** O(1) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};
Node* removeHead(Node* head) {
    if (head == nullptr) return head;
    Node* temp = head;
    head = head->next;
    delete temp;                  // free the old head (C++ only)
    return head;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } Node(int d, Node n) { data = d; next = n; } }
class Solution {
    static Node removeHead(Node head) {
        if (head == null) return head;
        head = head.next;         // old head is garbage-collected
        return head;
    }
}
```

#### Key Takeaways
- Always handle the empty list first.
- In C++ you must free deleted nodes. In Java the garbage collector does it.

[↑ Contents](#contents) · [← Previous](#p165) · [Next →](#p167)

---

<a id="p167"></a>

### 3. Deletion of the tail of Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | No | — | [Watch from 6:10](https://youtu.be/VaECK03Dz-g?t=370) |

#### Problem Statement
Delete the **tail** (last node) of a singly linked list and return the head.

```text
12 -> 5 -> 8 -> 7 -> null   ->   12 -> 5 -> 8 -> null
5 -> null                   ->   null
```

#### Approach: Stop at the second-last node
To remove the tail, you need its **predecessor**, so that you can set the predecessor's `next` to `null`.
1. If `head == null` **or** `head->next == null` (zero or one node), return `null`. Deleting the only node leaves an empty list.
2. Otherwise move `temp` while `temp->next->next != null`. When the loop stops, `temp` is the **second-last** node.
3. `delete temp->next` (C++), then set `temp->next = nullptr`. Return `head`.

**Dry run** `12 → 5 → 8 → 7`:
- `temp` = 12: `12.next.next` is 8, so move.
- `temp` = 5: `5.next.next` is 7, so move.
- `temp` = 8: `8.next.next` is null, so stop.
- Free 7 and set `8.next = null`.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};
Node* removeTail(Node* head) {
    if (head == nullptr || head->next == nullptr) {   // empty or single node
        delete head;
        return nullptr;
    }
    Node* temp = head;
    while (temp->next->next != nullptr) temp = temp->next;   // stop at second last
    delete temp->next;
    temp->next = nullptr;
    return head;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } Node(int d, Node n) { data = d; next = n; } }
class Solution {
    static Node removeTail(Node head) {
        if (head == null || head.next == null) return null;   // empty or single node
        Node temp = head;
        while (temp.next.next != null) temp = temp.next;      // stop at second last
        temp.next = null;
        return head;
    }
}
```

#### Key Takeaways
- To delete a node, you need the node **before** it. Here that's the loop `while (temp->next->next != null)`.

[↑ Contents](#contents) · [← Previous](#p166) · [Next →](#p168)

---

<a id="p168"></a>

### 4. Deletion of the Kth element of Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | No | — | [Watch from 15:30](https://youtu.be/VaECK03Dz-g?t=930) |

#### Problem Statement
Delete the **k-th node** (1-indexed) of a singly linked list and return the head. If `k` is larger than the length, leave the list unchanged.

```text
12 -> 5 -> 8 -> 7, k = 3  ->  12 -> 5 -> 7
12 -> 5 -> 8 -> 7, k = 1  ->  5 -> 8 -> 7        (head)
12 -> 5 -> 8 -> 7, k = 4  ->  12 -> 5 -> 8       (tail)
12 -> 5 -> 8 -> 7, k = 7  ->  unchanged
```

#### Approach: Count while traversing, keep `prev`
Build the solution from edge cases:
1. Empty list: return `head`.
2. `k == 1`: delete the head (previous problem).
3. Otherwise traverse with `temp` and `prev = null`, incrementing `cnt` at each node. When `cnt == k`, `temp` is the target. Unlink it with `prev->next = prev->next->next`, free `temp`, and break.
4. If `k` exceeds the length, the loop simply ends and nothing changes.

The same code removes the tail: when `temp` is the last node, `prev->next` becomes `null`.

**Dry run** `k = 3`:
- `cnt` = 1 at node 12, and `cnt` = 2 at node 5. Each time, set `prev = temp` and move `temp` forward.
- `cnt` = 3 at node 8: set `5.next = 8.next` (node 7) and free 8.

**Complexity:** O(k) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};
Node* removeK(Node* head, int k) {
    if (head == nullptr) return head;
    if (k == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    int cnt = 0;
    Node* temp = head;
    Node* prev = nullptr;
    while (temp != nullptr) {
        cnt++;
        if (cnt == k) {
            prev->next = prev->next->next;    // unlink temp
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } Node(int d, Node n) { data = d; next = n; } }
class Solution {
    static Node removeK(Node head, int k) {
        if (head == null) return head;
        if (k == 1) return head.next;
        int cnt = 0;
        Node temp = head, prev = null;
        while (temp != null) {
            cnt++;
            if (cnt == k) {
                prev.next = prev.next.next;       // unlink temp
                break;
            }
            prev = temp;
            temp = temp.next;
        }
        return head;
    }
}
```

#### Key Takeaways
- Tracking `prev` while traversing lets you unlink the current node in O(1).
- One routine handles the head, the middle and the tail, plus the out-of-range case.

[↑ Contents](#contents) · [← Previous](#p167) · [Next →](#p169)

---

<a id="p169"></a>

### 5. Delete the element with value X

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | No | — | [Watch from 29:30](https://youtu.be/VaECK03Dz-g?t=1770) |

#### Problem Statement
Delete the **first node whose value is `x`** and return the head. If `x` isn't present, leave the list unchanged.

```text
12 -> 5 -> 8 -> 7, x = 8   ->  12 -> 5 -> 7
12 -> 5 -> 8 -> 7, x = 12  ->  5 -> 8 -> 7
12 -> 5 -> 8 -> 7, x = 15  ->  unchanged
```

#### Approach: Same as "delete k-th", but match on data
Copy the previous solution and change two lines. The head check becomes `head->data == x`, and the in-loop check becomes `temp->data == x`. The counter is no longer needed.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};
Node* removeElement(Node* head, int x) {
    if (head == nullptr) return head;
    if (head->data == x) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    Node* temp = head;
    Node* prev = nullptr;
    while (temp != nullptr) {
        if (temp->data == x) {
            prev->next = prev->next->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } Node(int d, Node n) { data = d; next = n; } }
class Solution {
    static Node removeElement(Node head, int x) {
        if (head == null) return head;
        if (head.data == x) return head.next;
        Node temp = head, prev = null;
        while (temp != null) {
            if (temp.data == x) {
                prev.next = prev.next.next;
                break;
            }
            prev = temp;
            temp = temp.next;
        }
        return head;
    }
}
```

#### Key Takeaways
- Deleting by position and deleting by value differ only in the condition that locates the node.

[↑ Contents](#contents) · [← Previous](#p168) · [Next →](#p170)

---

<a id="p170"></a>

### 6. Insertion at the head of Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/insert-a-node-at-the-beginning-of-a-singly-linked-list) | [Watch from 32:14](https://youtu.be/VaECK03Dz-g?t=1934) |

#### Problem Statement
Insert a new node with value `val` at the **head** and return the new head.

```text
2 -> 3 -> 1 -> 8, val = 5   ->   5 -> 2 -> 3 -> 1 -> 8
null, val = 5               ->   5
```

#### Approach: New node pointing at the old head
Create `temp = new Node(val, head)` and return `temp`. The new node's `next` is the old head, and it becomes the new head. An empty list (`head == null`) works too, since you just get a single node.

As a one-liner: `head = new Node(val, head);`

**Complexity:** O(1) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};
Node* insertHead(Node* head, int val) {
    Node* temp = new Node(val, head);
    return temp;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } Node(int d, Node n) { data = d; next = n; } }
class Solution {
    static Node insertHead(Node head, int val) {
        return new Node(val, head);
    }
}
```

#### Key Takeaways
- Inserting at the head is O(1). This is why linked lists make good stacks.

[↑ Contents](#contents) · [← Previous](#p169) · [Next →](#p171)

---

<a id="p171"></a>

### 7. Insertion at the tail of Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | No | — | [Watch from 34:40](https://youtu.be/VaECK03Dz-g?t=2080) |

#### Problem Statement
Insert a new node with value `val` at the **tail** and return the head.

```text
2 -> 3 -> 1 -> 8, val = 5   ->   2 -> 3 -> 1 -> 8 -> 5
null, val = 5               ->   5
```

#### Approach: Walk to the last node, then link
1. Empty list: return `new Node(val)`.
2. Move `temp` while `temp->next != null`. Note that the condition is on `temp->next`, not `temp`, so the loop stops **at** the last node instead of running past it.
3. Set `temp->next = new Node(val)` and return `head`.

**Complexity:** O(n) time, O(1) space. Keeping a `tail` pointer makes this O(1).

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};
Node* insertTail(Node* head, int val) {
    if (head == nullptr) return new Node(val);
    Node* temp = head;
    while (temp->next != nullptr) temp = temp->next;   // stop at the last node
    temp->next = new Node(val);
    return head;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } Node(int d, Node n) { data = d; next = n; } }
class Solution {
    static Node insertTail(Node head, int val) {
        if (head == null) return new Node(val);
        Node temp = head;
        while (temp.next != null) temp = temp.next;   // stop at the last node
        temp.next = new Node(val);
        return head;
    }
}
```

#### Key Takeaways
- `while (temp)` visits every node. `while (temp->next)` stops at the last node. Pick the one that fits the job.

[↑ Contents](#contents) · [← Previous](#p170) · [Next →](#p172)

---

<a id="p172"></a>

### 8. Insertion at the Kth position of Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/insert-node-at-kth-position-in-linked-list) | [Watch from 38:32](https://youtu.be/VaECK03Dz-g?t=2312) |

#### Problem Statement
Insert `val` so that it becomes the **k-th node** (1-indexed), where `1 ≤ k ≤ n + 1`, and return the head. `k = n + 1` means appending at the tail.

```text
3 -> 1 -> 5 -> 8, val = 10, k = 1  ->  10 -> 3 -> 1 -> 5 -> 8
3 -> 1 -> 5 -> 8, val = 10, k = 3  ->  3 -> 1 -> 10 -> 5 -> 8
3 -> 1 -> 5 -> 8, val = 10, k = 5  ->  3 -> 1 -> 5 -> 8 -> 10
```

#### Approach: Stop at node k−1, then splice
1. **Empty list:** only `k == 1` is valid, so return `new Node(val)`. For any other `k`, return `null` or report an error.
2. **`k == 1`:** return `new Node(val, head)`.
3. Otherwise traverse with a counter. When `cnt == k − 1`, `temp` is the node that will come **before** the new one.
   - Create `x = new Node(val, temp->next)`. The new node points to `temp`'s old successor **first**.
   - Then set `temp->next = x`.
   - Break.

**Why that order?** If you set `temp->next = x` first, you lose the only pointer to the rest of the list (5 → 8 …).

**Complexity:** O(k) time, which is O(1) at the head and O(n) worst case. O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};
Node* insertPosition(Node* head, int val, int k) {
    if (head == nullptr) return k == 1 ? new Node(val) : head;
    if (k == 1) return new Node(val, head);
    int cnt = 0;
    Node* temp = head;
    while (temp != nullptr) {
        cnt++;
        if (cnt == k - 1) {
            Node* x = new Node(val, temp->next);   // connect to the rest first
            temp->next = x;
            break;
        }
        temp = temp->next;
    }
    return head;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } Node(int d, Node n) { data = d; next = n; } }
class Solution {
    static Node insertPosition(Node head, int val, int k) {
        if (head == null) return k == 1 ? new Node(val) : head;
        if (k == 1) return new Node(val, head);
        int cnt = 0;
        Node temp = head;
        while (temp != null) {
            cnt++;
            if (cnt == k - 1) {
                temp.next = new Node(val, temp.next);   // connect to the rest first
                break;
            }
            temp = temp.next;
        }
        return head;
    }
}
```

#### Key Takeaways
- To insert at position k, stand on node k−1. Link the new node forward first, then link it in from behind.

[↑ Contents](#contents) · [← Previous](#p171) · [Next →](#p173)

---

<a id="p173"></a>

### 9. Insertion before the value X in Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/insert-node-before-value-x-in-linked-list) | [Watch from 50:50](https://youtu.be/VaECK03Dz-g?t=3050) |

#### Problem Statement
Insert `val` **before the first node whose value is `x`** and return the head. `x` is guaranteed to be present (if it isn't, leave the list unchanged).

```text
3 -> 1 -> 5 -> 8, val = 10, x = 5  ->  3 -> 1 -> 10 -> 5 -> 8
3 -> 1 -> 5 -> 8, val = 10, x = 3  ->  10 -> 3 -> 1 -> 5 -> 8
```

#### Approach: Look one node ahead
1. Empty list: `x` can't be present, so return `head`.
2. If `head->data == x`, insert at the head: `return new Node(val, head)`.
3. Otherwise walk while `temp->next != null`. If `temp->next->data == x`, splice in `new Node(val, temp->next)` after `temp` and break. Looking at `temp->next` lets you stand on the node **before** `x`.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};
Node* insertBeforeValue(Node* head, int val, int x) {
    if (head == nullptr) return head;
    if (head->data == x) return new Node(val, head);
    Node* temp = head;
    while (temp->next != nullptr) {
        if (temp->next->data == x) {
            temp->next = new Node(val, temp->next);
            break;
        }
        temp = temp->next;
    }
    return head;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } Node(int d, Node n) { data = d; next = n; } }
class Solution {
    static Node insertBeforeValue(Node head, int val, int x) {
        if (head == null) return head;
        if (head.data == x) return new Node(val, head);
        Node temp = head;
        while (temp.next != null) {
            if (temp.next.data == x) {
                temp.next = new Node(val, temp.next);
                break;
            }
            temp = temp.next;
        }
        return head;
    }
}
```

#### Key Takeaways
- "Insert or delete relative to a value" means peeking at `temp->next->data`, so that you end up standing on the predecessor.

[↑ Contents](#contents) · [← Previous](#p172) · [Next →](#p174)

---

<a id="p174"></a>

### 10. Find the length of the Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Basic | Yes | — | [Watch from 37:20](https://youtu.be/Nq7ok-OyEpg?t=2240) |

#### Problem Statement
Return the number of nodes in a singly linked list.

```text
2 -> 1 -> 3 -> 8 -> null  ->  4
null                      ->  0
```

#### Approach: Traversal with a counter (as in the lecture)
Copy the traversal template and increment `cnt` at each node.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};
int lengthOfLL(Node* head) {
    int cnt = 0;
    Node* temp = head;
    while (temp != nullptr) {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } }
class Solution {
    static int lengthOfLL(Node head) {
        int cnt = 0;
        Node temp = head;
        while (temp != null) {
            cnt++;
            temp = temp.next;
        }
        return cnt;
    }
}
```

#### Recursive version *(not in lecture)*
`len(node)` returns 0 if `node` is null, and `1 + len(node->next)` otherwise. This takes O(n) time and O(n) stack.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};
int lengthRec(Node* node) {
    return node == nullptr ? 0 : 1 + lengthRec(node->next);
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } }
class Solution {
    static int lengthRec(Node node) {
        return node == null ? 0 : 1 + lengthRec(node.next);
    }
}
```

#### Key Takeaways
- Counting nodes is a single traversal. Many later problems (rotate, remove the N-th node from the end, intersection) begin by computing the length.

[↑ Contents](#contents) · [← Previous](#p173) · [Next →](#p175)

---

<a id="p175"></a>

### 11. Search in Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Single LL) | Core | Yes | — | [Watch from 42:04](https://youtu.be/Nq7ok-OyEpg?t=2524) |

#### Problem Statement
Given the `head` of a linked list and a value `k`, return 1 (true) if some node holds `k`, else 0 (false).

```text
1 -> 2 -> 3 -> 5 -> null, k = 5   ->  1
1 -> 2 -> 3 -> 5 -> null, k = 15  ->  0
```

#### Approach: Traverse and compare
Walk the list. As soon as `temp->data == k`, return 1. If the traversal finishes without a match, return 0.

**Complexity:**
- Best case O(1): the head holds `k`.
- Average about n/2 steps.
- Worst case O(n): `k` is absent.
- Space O(1).

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};
int checkIfPresent(Node* head, int k) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == k) return 1;
        temp = temp->next;
    }
    return 0;
}
```

**Java**
```java
class Node { int data; Node next; Node(int d) { data = d; } }
class Solution {
    static int checkIfPresent(Node head, int k) {
        Node temp = head;
        while (temp != null) {
            if (temp.data == k) return 1;
            temp = temp.next;
        }
        return 0;
    }
}
```

#### Notes from the lecture
- Online judges such as Code Studio often use a templated node, `template <typename T> class Node { T data; Node* next; }`. You may need to write `Node<int>*` in the function signature.
- Linked lists can't be binary-searched, because there's no random access. Search is always linear.

#### Key Takeaways
- Searching is a traversal with an early exit.

[↑ Contents](#contents) · [← Previous](#p174) · [Next →](#p176)

---

## Fundamentals (Doubly LL)

<a id="p176"></a>

### 12. Convert Array to Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | Yes | — | [Watch from 4:00](https://youtu.be/0eKMU10uEDI?t=240) |

> *Problems #176–184 all come from Striver's Doubly Linked List lecture (0eKMU10uEDI). The deletions mirror the singly-linked versions; the difference is that every node also has a **`back`** pointer that must be kept consistent.*

#### Problem Statement
Convert an array into a **doubly linked list (DLL)** and return its head. Each node has `data`, `next` (the following node) and `back` (the previous node). The head's `back` is `null`, and so is the tail's `next`.

```text
[1, 3, 2, 4]  ->  null <- 1 <-> 3 <-> 2 <-> 4 -> null
```

#### Approach: Keep a `prev` pointer while building
1. Create `head = new Node(arr[0])` and set `prev = head`.
2. For each `i ≥ 1`:
   - create `temp = new Node(arr[i], next = null, back = prev)`;
   - link `prev->next = temp`;
   - move `prev = temp`.
3. Return `head`.

**Complexity:** O(n) time, O(n) for the nodes.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* convertArr2DLL(vector<int>& arr) {
    if (arr.empty()) return nullptr;
    Node* head = new Node(arr[0]);
    Node* prev = head;
    for (int i = 1; i < (int)arr.size(); i++) {
        Node* temp = new Node(arr[i], nullptr, prev);   // back -> prev
        prev->next = temp;                              // prev -> temp
        prev = temp;
    }
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node convertArr2DLL(int[] arr) {
        if (arr.length == 0) return null;
        Node head = new Node(arr[0]);
        Node prev = head;
        for (int i = 1; i < arr.length; i++) {
            Node temp = new Node(arr[i], null, prev);   // back -> prev
            prev.next = temp;                           // prev -> temp
            prev = temp;
        }
        return head;
    }
}
```

#### Key Takeaways
- Every link in a DLL is made twice: `a->next = b` and `b->back = a`.
- A DLL can be traversed backward from the tail, at the cost of one extra pointer per node.

[↑ Contents](#contents) · [← Previous](#p175) · [Next →](#p177)

---

<a id="p177"></a>

### 13. Delete Tail of Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | — | [Watch from 20:16](https://youtu.be/0eKMU10uEDI?t=1216) |

#### Problem Statement
Delete the **tail** of a DLL and return the head.

```text
1 <-> 3 <-> 2 <-> 4   ->   1 <-> 3 <-> 2
```

#### Approach
In a DLL you can stand **on** the tail and still reach its predecessor through `back`. In a singly linked list you had to stop one node early.
1. If the list is empty or has one node, return `null`.
2. Move `tail` to the last node.
3. Set `newTail = tail->back`, `newTail->next = nullptr` and `tail->back = nullptr`.
4. Free `tail` and return `head`.

**Complexity:** O(n) time to find the tail. This drops to O(1) if a tail pointer is maintained.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* deleteTail(Node* head) {
    if (head == nullptr || head->next == nullptr) { delete head; return nullptr; }
    Node* tail = head;
    while (tail->next != nullptr) tail = tail->next;
    Node* newTail = tail->back;
    newTail->next = nullptr;
    tail->back = nullptr;
    delete tail;
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node deleteTail(Node head) {
        if (head == null || head.next == null) return null;
        Node tail = head;
        while (tail.next != null) tail = tail.next;
        Node newTail = tail.back;
        newTail.next = null;
        tail.back = null;
        return head;
    }
}
```

#### Key Takeaways
- The `back` pointer removes the "stop one before the target" trick that singly linked lists need.

[↑ Contents](#contents) · [← Previous](#p176) · [Next →](#p178)

---

<a id="p178"></a>

### 14. Delete Kth Element of Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | — | [Watch from 25:41](https://youtu.be/0eKMU10uEDI?t=1541) |

#### Problem Statement
Delete the **k-th node** (1-indexed, with `1 ≤ k ≤ length`) of a DLL and return the head.

```text
1 <-> 3 <-> 2 <-> 4, k = 3   ->   1 <-> 3 <-> 4
```

#### Approach (as in the lecture)
1. Walk to the k-th node with a counter and call it `temp`. Let `prev = temp->back` and `front = temp->next`.
2. Then handle four cases:
   - `prev == null && front == null`: this was the only node. Free it and return `null`.
   - `prev == null`: it's the head, so call **`deleteHead`**.
   - `front == null`: it's the tail, so call **`deleteTail`**.
   - Otherwise it's in the middle. Set `prev->next = front` and `front->back = prev`. Then detach `temp` (`temp->next = temp->back = null`) and free it.

**Complexity:** O(k) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* deleteHead(Node* head) {
    if (head == nullptr || head->next == nullptr) { delete head; return nullptr; }
    Node* prev = head; head = head->next;
    head->back = nullptr; prev->next = nullptr; delete prev;
    return head;
}
Node* deleteTail(Node* head) {
    if (head == nullptr || head->next == nullptr) { delete head; return nullptr; }
    Node* tail = head;
    while (tail->next) tail = tail->next;
    tail->back->next = nullptr; tail->back = nullptr; delete tail;
    return head;
}
Node* removeKthElement(Node* head, int k) {
    if (head == nullptr) return nullptr;
    int cnt = 0;
    Node* temp = head;
    while (temp != nullptr) {
        cnt++;
        if (cnt == k) break;
        temp = temp->next;
    }
    if (temp == nullptr) return head;                 // k out of range
    Node* prev = temp->back;
    Node* front = temp->next;
    if (prev == nullptr && front == nullptr) { delete temp; return nullptr; }
    if (prev == nullptr) return deleteHead(head);
    if (front == nullptr) return deleteTail(head);
    prev->next = front;
    front->back = prev;
    temp->next = temp->back = nullptr;
    delete temp;
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node deleteHead(Node head) {
        if (head == null || head.next == null) return null;
        Node prev = head; head = head.next;
        head.back = null; prev.next = null;
        return head;
    }
    static Node deleteTail(Node head) {
        if (head == null || head.next == null) return null;
        Node tail = head;
        while (tail.next != null) tail = tail.next;
        tail.back.next = null; tail.back = null;
        return head;
    }
    static Node removeKthElement(Node head, int k) {
        if (head == null) return null;
        int cnt = 0;
        Node temp = head;
        while (temp != null) {
            cnt++;
            if (cnt == k) break;
            temp = temp.next;
        }
        if (temp == null) return head;                // k out of range
        Node prev = temp.back, front = temp.next;
        if (prev == null && front == null) return null;
        if (prev == null) return deleteHead(head);
        if (front == null) return deleteTail(head);
        prev.next = front;
        front.back = prev;
        temp.next = temp.back = null;
        return head;
    }
}
```

#### Key Takeaways
- Classify the target by whether `prev` and `front` exist, and reuse the head and tail routines for the edge cases.

[↑ Contents](#contents) · [← Previous](#p177) · [Next →](#p179)

---

<a id="p179"></a>

### 15. Removing given node in Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | — | [Watch from 39:41](https://youtu.be/0eKMU10uEDI?t=2381) |

#### Problem Statement
Given a pointer to a node in a DLL, **delete that node**. The node is guaranteed **not to be the head**. Deleting the head would change the head, but this function returns nothing, so the caller couldn't see the new head.

```text
1 <-> 3 <-> 2 <-> 4, node = (2)   ->   1 <-> 3 <-> 4
```

#### Approach
- `prev = node->back` and `front = node->next`.
- If `front == null`, the node is the tail. Set `prev->next = nullptr` and `node->back = nullptr`, free the node, and return.
- Otherwise bypass it: `prev->next = front` and `front->back = prev`. Then detach the node and free it.

There's no traversal, so this is O(1). Being able to delete a node in O(1) given only a pointer to it is a key advantage of DLLs.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
void deleteNode(Node* temp) {
    Node* prev = temp->back;
    Node* front = temp->next;
    if (front == nullptr) {               // tail
        prev->next = nullptr;
        temp->back = nullptr;
        delete temp;
        return;
    }
    prev->next = front;
    front->back = prev;
    temp->next = temp->back = nullptr;
    delete temp;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static void deleteNode(Node temp) {
        Node prev = temp.back, front = temp.next;
        if (front == null) {                  // tail
            prev.next = null;
            temp.back = null;
            return;
        }
        prev.next = front;
        front.back = prev;
        temp.next = temp.back = null;
    }
}
```

#### Key Takeaways
- Given a pointer to a node, a DLL deletes it in O(1). That's why LRU caches pair a DLL with a hash map.

[↑ Contents](#contents) · [← Previous](#p178) · [Next →](#p180)

---

<a id="p180"></a>

### 16. Insert node before head in Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | — | [Watch from 44:44](https://youtu.be/0eKMU10uEDI?t=2684) |

#### Problem Statement
Insert a new node with value `val` **before the head** of a DLL and return the new head.

```text
1 <-> 3 <-> 2, val = 10   ->   10 <-> 1 <-> 3 <-> 2
```

#### Approach
Create `newHead = new Node(val, next = head, back = null)`. If `head` isn't null, set `head->back = newHead`. Return `newHead`.

**Complexity:** O(1).

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* insertBeforeHead(Node* head, int val) {
    Node* newHead = new Node(val, head, nullptr);
    if (head != nullptr) head->back = newHead;
    return newHead;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node insertBeforeHead(Node head, int val) {
        Node newHead = new Node(val, head, null);
        if (head != null) head.back = newHead;
        return newHead;
    }
}
```

[↑ Contents](#contents) · [← Previous](#p179) · [Next →](#p181)

---

<a id="p181"></a>

### 17. Insert node before tail in Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | — | [Watch from 47:25](https://youtu.be/0eKMU10uEDI?t=2845) |

#### Problem Statement
Insert `val` **just before the tail**, so that it becomes the second-to-last node. Return the head.

```text
1 <-> 3 <-> 2, val = 10   ->   1 <-> 3 <-> 10 <-> 2
4, val = 10               ->   10 <-> 4        (single node: before tail = before head)
```

#### Approach
1. If the list has a single node (`head->next == null`), this is the same as inserting before the head.
2. Otherwise:
   - walk `tail` to the last node and let `prev = tail->back`;
   - create `newNode(val, next = tail, back = prev)`;
   - link `prev->next = newNode` and `tail->back = newNode`.

**Complexity:** O(n) to reach the tail.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* insertBeforeTail(Node* head, int val) {
    if (head == nullptr) return new Node(val);
    if (head->next == nullptr) {                      // single node
        Node* nh = new Node(val, head, nullptr);
        head->back = nh;
        return nh;
    }
    Node* tail = head;
    while (tail->next != nullptr) tail = tail->next;
    Node* prev = tail->back;
    Node* newNode = new Node(val, tail, prev);
    prev->next = newNode;
    tail->back = newNode;
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node insertBeforeTail(Node head, int val) {
        if (head == null) return new Node(val);
        if (head.next == null) {                       // single node
            Node nh = new Node(val, head, null);
            head.back = nh;
            return nh;
        }
        Node tail = head;
        while (tail.next != null) tail = tail.next;
        Node prev = tail.back;
        Node newNode = new Node(val, tail, prev);
        prev.next = newNode;
        tail.back = newNode;
        return head;
    }
}
```

[↑ Contents](#contents) · [← Previous](#p180) · [Next →](#p182)

---

<a id="p182"></a>

### 18. Insert node before (kth node) in Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | — | [Watch from 52:31](https://youtu.be/0eKMU10uEDI?t=3151) |

#### Problem Statement
Insert `val` **before the k-th node** (1-indexed, with `1 ≤ k ≤ length`) of a DLL. Return the head.

```text
1 <-> 3 <-> 2 <-> 4, val = 10, k = 3   ->   1 <-> 3 <-> 10 <-> 2 <-> 4
```

#### Approach
1. `k == 1`: insert before the head.
2. Otherwise:
   - walk to the k-th node `temp` and let `prev = temp->back`;
   - create `newNode(val, next = temp, back = prev)`;
   - link `prev->next = newNode` and `temp->back = newNode`.

**Complexity:** O(k).

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* insertBeforeKthElement(Node* head, int k, int val) {
    if (k == 1) {
        Node* nh = new Node(val, head, nullptr);
        if (head) head->back = nh;
        return nh;
    }
    Node* temp = head;
    int cnt = 0;
    while (temp != nullptr) {
        cnt++;
        if (cnt == k) break;
        temp = temp->next;
    }
    if (temp == nullptr) return head;            // k out of range
    Node* prev = temp->back;
    Node* newNode = new Node(val, temp, prev);
    prev->next = newNode;
    temp->back = newNode;
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node insertBeforeKthElement(Node head, int k, int val) {
        if (k == 1) {
            Node nh = new Node(val, head, null);
            if (head != null) head.back = nh;
            return nh;
        }
        Node temp = head;
        int cnt = 0;
        while (temp != null) {
            cnt++;
            if (cnt == k) break;
            temp = temp.next;
        }
        if (temp == null) return head;           // k out of range
        Node prev = temp.back;
        Node newNode = new Node(val, temp, prev);
        prev.next = newNode;
        temp.back = newNode;
        return head;
    }
}
```

[↑ Contents](#contents) · [← Previous](#p181) · [Next →](#p183)

---

<a id="p183"></a>

### 19. Insert before given node in Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | — | [Watch from 57:58](https://youtu.be/0eKMU10uEDI?t=3478) |

#### Problem Statement
Given a pointer to a node in a DLL that is **not the head**, insert `val` **before** it.

```text
1 <-> 3 <-> 2 <-> 4, node = (2), val = 10   ->   1 <-> 3 <-> 10 <-> 2 <-> 4
```

#### Approach
- Let `prev = node->back`.
- Create `newNode(val, next = node, back = prev)`.
- Link `prev->next = newNode` and `node->back = newNode`.

This is O(1), with no traversal. The not-the-head guarantee matters because the function returns nothing, so the head can't change.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
void insertBeforeNode(Node* node, int val) {
    Node* prev = node->back;
    Node* newNode = new Node(val, node, prev);
    prev->next = newNode;
    node->back = newNode;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static void insertBeforeNode(Node node, int val) {
        Node prev = node.back;
        Node newNode = new Node(val, node, prev);
        prev.next = newNode;
        node.back = newNode;
    }
}
```

#### Key Takeaways (DLL insertions)
- Each insertion sets **four** pointers: the new node's `next` and `back`, its predecessor's `next`, and its successor's `back`.

[↑ Contents](#contents) · [← Previous](#p182) · [Next →](#p184)

---

<a id="p184"></a>

### 20. Delete head of Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | — | [Watch from 14:13](https://youtu.be/0eKMU10uEDI?t=853) |

#### Problem Statement
Delete the **head** of a DLL and return the new head.

```text
1 <-> 3 <-> 2 <-> 4   ->   3 <-> 2 <-> 4
```

#### Approach
1. If the list is empty or has a single node, return `null` (freeing that node).
2. Save `prev = head`. Move `head = head->next`.
3. Cut the links both ways: `head->back = nullptr` and `prev->next = nullptr`.
4. Free `prev` and return the new head.

**Complexity:** O(1) time.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* deleteHead(Node* head) {
    if (head == nullptr || head->next == nullptr) { delete head; return nullptr; }
    Node* prev = head;
    head = head->next;
    head->back = nullptr;     // new head has no back
    prev->next = nullptr;     // detach old head
    delete prev;
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node deleteHead(Node head) {
        if (head == null || head.next == null) return null;
        Node prev = head;
        head = head.next;
        head.back = null;
        prev.next = null;
        return head;
    }
}
```

#### Key Takeaways
- Detach the removed node in both directions so that no dangling links remain.

[↑ Contents](#contents) · [← Previous](#p183) · [Next →](#p185)

---

<a id="p185"></a>

### 21. Reverse a Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Fundamentals (Doubly LL) | Core | No | [LeetCode](https://leetcode.com/problems/reverse-linked-list/) | [Watch](https://youtu.be/u3WUW2qe6ww) |

#### Problem Statement
Reverse a doubly linked list and return its new head.

```text
1 <-> 3 <-> 2 <-> 4   ->   4 <-> 2 <-> 3 <-> 1
```

#### Approach 1: Brute Force — reverse the data with a stack (two passes)
1. **Pass 1:** traverse the list and push every `data` value onto a stack. A stack is LIFO, so the values come back out in reverse order.
2. **Pass 2:** traverse again from `head`, overwriting each node's `data` with `st.top()` and popping as you go.

The links are left untouched; only the values are swapped.

**Complexity:** O(2n) time (two passes), O(n) space (the stack).

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* reverseDLLStack(Node* head) {
    stack<int> st;
    for (Node* temp = head; temp != nullptr; temp = temp->next) st.push(temp->data);   // step 1
    for (Node* temp = head; temp != nullptr; temp = temp->next) {                       // step 2
        temp->data = st.top();
        st.pop();
    }
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node reverseDLLStack(Node head) {
        Deque<Integer> st = new ArrayDeque<>();
        for (Node temp = head; temp != null; temp = temp.next) st.push(temp.data);   // step 1
        for (Node temp = head; temp != null; temp = temp.next) temp.data = st.pop(); // step 2
        return head;
    }
}
```

#### Approach 2: Optimal — swap `next` and `back` of every node (one pass)
For a **single node**, reversing the list just means swapping its `next` and `back` pointers. This is a classic swap that needs one temporary variable:

```text
last = current->back        // save before it is overwritten
current->back = current->next
current->next = last
```

After the swap, the "next" node in the **original** order is reached through `current->back`, so advance with `current = current->back`.

When `current` becomes null, `last` is holding the original second-last node. Its `back` pointer now points to the original tail, which is the **new head**, so return `last->back`.

**Dry run** `1 <-> 3 <-> 2 <-> 4`:
- At node 1: `last = null`, `back = 3`, `next = null`. Move to 3.
- At node 3: `last = 1`, `back = 2`, `next = 1`. Move to 2.
- At node 2: `last = 3`, `back = 4`, `next = 3`. Move to 4.
- At node 4: `last = 2`, `back = null`, `next = 2`. Move to null.
- The loop ends with `last = 2`, so the new head is `last->back` = **4**.

**Complexity:** O(n) time (single pass), O(1) space.

**C++**
```cpp
class Node {
public:
    int data;
    Node* next;
    Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* reverseDLL(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;   // 0 or 1 node
    Node* last = nullptr;
    Node* current = head;
    while (current != nullptr) {
        last = current->back;
        current->back = current->next;
        current->next = last;
        current = current->back;          // the old "next"
    }
    return last->back;                    // new head
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    public static Node reverseDLL(Node head) {
        if (head == null || head.next == null) return head;      // 0 or 1 node
        Node last = null, current = head;
        while (current != null) {
            last = current.back;
            current.back = current.next;
            current.next = last;
            current = current.back;           // the old "next"
        }
        return last.back;                     // new head
    }
}
```

#### Edge Cases & Pitfalls
- **Empty or single-node list:** return it unchanged. Otherwise `last` stays null and `last->back` crashes.
- After the swap, advance with `current->back`, not `current->next`.

#### Key Takeaways
- **Interview tip from the video:** don't just recite the four lines. Explain how you got there: consider one node, notice its `next` and `back` must swap, recall the a/b swap with a temporary, then apply it to every node.
- The interviewer will usually push you from the two-pass stack approach to the one-pass link reversal.

[↑ Contents](#contents) · [← Previous](#p184) · [Next →](#p186)

---

## Logic Building

<a id="p186"></a>

### 22. Add two numbers in Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/add-two-numbers/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/add-two-numbers-linked-lists-reverse-order) | [Watch](https://youtu.be/LBVsXSMOIk4) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Two non-negative integers are stored as linked lists with their digits in **reverse order**, so the head holds the units digit. Return their **sum** as a linked list in the same reversed format (LeetCode 2).

```text
l1 = 2 -> 4 -> 3   (342)
l2 = 5 -> 6 -> 4   (465)          ->  7 -> 0 -> 8   (807)
l1 = 9 -> 9 -> 9 -> 9, l2 = 9 -> 9  ->  8 -> 9 -> 0 -> 0 -> 1
```

#### Approach 1: Brute Force — convert to numbers, add, convert back *(fails on large inputs)*
Read each list into an integer, add them, then write the sum back out digit by digit. It looks simple, but lists can have up to 100 digits, which **overflows** even 64-bit integers. It only works for small inputs, and it shows why a digit-by-digit method is needed.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* addTwoNumbersSmall(ListNode* l1, ListNode* l2) {        // only if values fit in 64 bits
    auto toNum = [](ListNode* h) { long long n = 0, p = 1; for (; h; h = h->next, p *= 10) n += h->val * p; return n; };
    long long s = toNum(l1) + toNum(l2);
    ListNode dummy(-1); ListNode* cur = &dummy;
    do { cur->next = new ListNode(s % 10); cur = cur->next; s /= 10; } while (s > 0);
    return dummy.next;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode addTwoNumbersSmall(ListNode l1, ListNode l2) {   // only if values fit in 64 bits
        long a = 0, b = 0, p = 1;
        for (ListNode h = l1; h != null; h = h.next, p *= 10) a += h.val * p;
        p = 1;
        for (ListNode h = l2; h != null; h = h.next, p *= 10) b += h.val * p;
        long s = a + b;
        ListNode dummy = new ListNode(-1), cur = dummy;
        do { cur.next = new ListNode((int) (s % 10)); cur = cur.next; s /= 10; } while (s > 0);
        return dummy.next;
    }
}
```

#### Approach 2: Optimal — schoolbook addition with a carry and a dummy node
Walk both lists together, like adding numbers by hand from the units digit:
- At each step, `sum = carry + (l1 digit, or 0) + (l2 digit, or 0)`.
- Append a node holding `sum % 10`, then set `carry = sum / 10`.
- Keep going while **either** list still has nodes **or** `carry > 0`. That last condition creates the extra leading digit, as in 999 + 99 = 1098.
- A **dummy** head node avoids special-casing the first node. Return `dummy->next`.

**Complexity:** O(max(n, m)) time, O(max(n, m)) space for the result list (O(1) extra).

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(-1);
    ListNode* cur = dummy;
    int carry = 0;
    while (l1 != nullptr || l2 != nullptr || carry) {
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }
        cur->next = new ListNode(sum % 10);
        cur = cur->next;
        carry = sum / 10;
    }
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(-1), cur = dummy;
        int carry = 0;
        while (l1 != null || l2 != null || carry != 0) {
            int sum = carry;
            if (l1 != null) { sum += l1.val; l1 = l1.next; }
            if (l2 != null) { sum += l2.val; l2 = l2.next; }
            cur.next = new ListNode(sum % 10);
            cur = cur.next;
            carry = sum / 10;
        }
        return dummy.next;
    }
}
```

#### Edge Cases & Pitfalls
- Lists of different lengths: treat missing digits as 0.
- A final carry must become a new node.

#### Key Takeaways
- A **dummy head** removes the "first node" special case. It's useful in every linked-list problem that builds a new list.

[↑ Contents](#contents) · [← Previous](#p185) · [Next →](#p187)

---

<a id="p187"></a>

### 23. Segregate odd and even nodes in Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/odd-even-linked-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/segregate-odd-and-even-nodes-in-linked-list) | [Watch](https://youtu.be/qf6qp7GzD5Q) |

> *The video's captions were a Hindi translation of the English audio; these notes follow it.*

#### Problem Statement
Group all **odd-indexed** nodes (1st, 3rd, 5th, …, 1-indexed) together, followed by all **even-indexed** nodes, keeping the original relative order within each group. Return the head (LeetCode 328). The grouping is by **position**, not by value.

```text
1 -> 3 -> 4 -> 2 -> 5 -> 6   ->   1 -> 4 -> 5 -> 3 -> 2 -> 6
```

#### Approach 1: Brute Force — collect the data, then rewrite it
1. From `head`, jump **two** nodes at a time (`temp = temp->next->next`) and push each value into an array. The loop runs while `temp` and `temp->next` aren't null. After it ends, push the last node too if `temp` isn't null: with an odd length, the final odd node would otherwise be missed.
2. Do the same starting from `head->next` to collect the even positions.
3. Traverse once more and overwrite each node's data with `arr[i++]`.

Handle the empty and single-node lists first.

**Complexity:** about O(n/2 + n/2 + n) = O(2n) time, O(n) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* oddEvenListBrute(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    vector<int> arr;
    ListNode* temp = head;                                  // odd positions
    while (temp != nullptr && temp->next != nullptr) { arr.push_back(temp->val); temp = temp->next->next; }
    if (temp) arr.push_back(temp->val);
    temp = head->next;                                      // even positions
    while (temp != nullptr && temp->next != nullptr) { arr.push_back(temp->val); temp = temp->next->next; }
    if (temp) arr.push_back(temp->val);
    int i = 0;
    for (temp = head; temp != nullptr; temp = temp->next) temp->val = arr[i++];
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode oddEvenListBrute(ListNode head) {
        if (head == null || head.next == null) return head;
        List<Integer> arr = new ArrayList<>();
        ListNode temp = head;                                   // odd positions
        while (temp != null && temp.next != null) { arr.add(temp.val); temp = temp.next.next; }
        if (temp != null) arr.add(temp.val);
        temp = head.next;                                       // even positions
        while (temp != null && temp.next != null) { arr.add(temp.val); temp = temp.next.next; }
        if (temp != null) arr.add(temp.val);
        int i = 0;
        for (temp = head; temp != null; temp = temp.next) temp.val = arr.get(i++);
        return head;
    }
}
```

#### Approach 2: Optimal — relink the odd and even chains in place
Keep `odd = head`, `even = head->next`, and remember `evenHead = head->next`.
- While `even` and `even->next` exist:
  - `odd->next = odd->next->next`, then `odd = odd->next`;
  - `even->next = even->next->next`, then `even = even->next`.
- Finally attach the evens after the last odd node: `odd->next = evenHead`.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = head->next;
    while (even != nullptr && even->next != nullptr) {
        odd->next = odd->next->next;
        even->next = even->next->next;
        odd = odd->next;
        even = even->next;
    }
    odd->next = evenHead;
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode oddEvenList(ListNode head) {
        if (head == null || head.next == null) return head;
        ListNode odd = head, even = head.next, evenHead = head.next;
        while (even != null && even.next != null) {
            odd.next = odd.next.next;
            even.next = even.next.next;
            odd = odd.next;
            even = even.next;
        }
        odd.next = evenHead;
        return head;
    }
}
```

#### Key Takeaways
- Splitting a list into two chains in a single pass, then joining them, is a reusable pattern. The next problem uses it with three chains.

[↑ Contents](#contents) · [← Previous](#p186) · [Next →](#p188)

---

<a id="p188"></a>

### 24. Sort a Linked List of 0's 1's and 2's

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Logic Building | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/sort-linked-list-0s-1s-2s-changing-links) | [Watch](https://youtu.be/gRII7LhdJWc) |

> *The video's captions were a Hindi translation of the English audio; these notes follow it.*

#### Problem Statement
A linked list contains only the values 0, 1 and 2. Sort it so that all 0s come first, then the 1s, then the 2s, and return the head.

```text
1 -> 0 -> 1 -> 2 -> 0 -> 2 -> 1   ->   0 -> 0 -> 1 -> 1 -> 1 -> 2 -> 2
```

#### Approach 1: Brute Force — count, then replace the data (two passes)
1. Count `cnt0`, `cnt1` and `cnt2` in one traversal.
2. Traverse again. Write 0 while `cnt0 > 0` (decrementing it), then 1 while `cnt1 > 0`, then 2.

**Complexity:** O(2n) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* sortListBrute(ListNode* head) {
    int c0 = 0, c1 = 0, c2 = 0;
    for (ListNode* t = head; t; t = t->next) {
        if (t->val == 0) c0++;
        else if (t->val == 1) c1++;
        else c2++;
    }
    for (ListNode* t = head; t; t = t->next) {
        if (c0) { t->val = 0; c0--; }
        else if (c1) { t->val = 1; c1--; }
        else { t->val = 2; c2--; }
    }
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode sortListBrute(ListNode head) {
        int c0 = 0, c1 = 0, c2 = 0;
        for (ListNode t = head; t != null; t = t.next) {
            if (t.val == 0) c0++;
            else if (t.val == 1) c1++;
            else c2++;
        }
        for (ListNode t = head; t != null; t = t.next) {
            if (c0 > 0) { t.val = 0; c0--; }
            else if (c1 > 0) { t.val = 1; c1--; }
            else { t.val = 2; c2--; }
        }
        return head;
    }
}
```

#### Approach 2: Optimal — three dummy lists, relink in one pass
Create three **dummy heads**, `zeroHead`, `oneHead` and `twoHead` (any value that isn't 0, 1 or 2 works, for example −1). Keep tail pointers `zero`, `one` and `two`. No new data nodes are created; existing nodes are just relinked.
1. Traverse once. Append each node to the tail of its list (e.g. `zero->next = temp; zero = temp`).
2. Connect the lists, taking care with empty ones:
   - `zero->next = oneHead->next ? oneHead->next : twoHead->next` (skip the 1s list if it's empty);
   - `one->next = twoHead->next`;
   - `two->next = null`.
3. The new head is `zeroHead->next`. If there are no 0s, that already points at the 1s or 2s, because of step 2. Delete the dummies (C++).

**Complexity:** O(n) time, single pass, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* sortList012(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* zeroHead = new ListNode(-1);
    ListNode* oneHead = new ListNode(-1);
    ListNode* twoHead = new ListNode(-1);
    ListNode *zero = zeroHead, *one = oneHead, *two = twoHead;
    for (ListNode* temp = head; temp != nullptr; temp = temp->next) {
        if (temp->val == 0) { zero->next = temp; zero = temp; }
        else if (temp->val == 1) { one->next = temp; one = temp; }
        else { two->next = temp; two = temp; }
    }
    zero->next = oneHead->next ? oneHead->next : twoHead->next;
    one->next = twoHead->next;
    two->next = nullptr;
    ListNode* newHead = zeroHead->next;
    delete zeroHead; delete oneHead; delete twoHead;
    return newHead;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode sortList012(ListNode head) {
        if (head == null || head.next == null) return head;
        ListNode zeroHead = new ListNode(-1), oneHead = new ListNode(-1), twoHead = new ListNode(-1);
        ListNode zero = zeroHead, one = oneHead, two = twoHead;
        for (ListNode temp = head; temp != null; temp = temp.next) {
            if (temp.val == 0) { zero.next = temp; zero = temp; }
            else if (temp.val == 1) { one.next = temp; one = temp; }
            else { two.next = temp; two = temp; }
        }
        zero.next = oneHead.next != null ? oneHead.next : twoHead.next;
        one.next = twoHead.next;
        two.next = null;
        return zeroHead.next;
    }
}
```

#### Edge Cases & Pitfalls
- If there are no 1s, the 0s list must link directly to the 2s list.
- `two->next = null` is essential. Otherwise the last 2 may still point into the middle of the old list, creating a cycle.

#### Key Takeaways
- Dummy heads make "partition into k lists, then concatenate" clean, because they remove all the empty-list special cases.

[↑ Contents](#contents) · [← Previous](#p187) · [Next →](#p189)

---

<a id="p189"></a>

### 25. Remove Nth node from the back of the LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/remove-the-nth-node-from-the-end-of-a-linked-list) | [Watch](https://youtu.be/3kMKYQ2wNIU) |

#### Problem Statement
Remove the **N-th node from the end** of the list and return the head (LeetCode 19).

```text
1 -> 2 -> 3 -> 4 -> 5, N = 2   ->   1 -> 2 -> 3 -> 5
1 -> 2 -> 3 -> 4 -> 5, N = 5   ->   2 -> 3 -> 4 -> 5    (head removed)
```

#### Approach 1: Brute Force — count, then walk to the (len − N)-th node
1. Count the length `cnt`.
2. If `cnt == N`, the target is the head. Return `head->next` and free the old head.
3. Otherwise walk to the node just **before** the target, which is node number `res = cnt − N`. Start with `temp = head` and decrement `res` at each node; when it hits 0, `temp` is the predecessor.
4. Unlink with `temp->next = temp->next->next`, then free the removed node.

**Complexity:** O(len) + O(len − N), which is about O(2·len) in the worst case (N = 1). O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* removeNthFromEndBrute(ListNode* head, int N) {
    int cnt = 0;
    for (ListNode* t = head; t; t = t->next) cnt++;
    if (cnt == N) {
        ListNode* newHead = head->next;
        delete head;
        return newHead;
    }
    int res = cnt - N;
    ListNode* temp = head;
    while (temp != nullptr) {
        res--;
        if (res == 0) break;
        temp = temp->next;
    }
    ListNode* delNode = temp->next;
    temp->next = temp->next->next;
    delete delNode;
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode removeNthFromEndBrute(ListNode head, int N) {
        int cnt = 0;
        for (ListNode t = head; t != null; t = t.next) cnt++;
        if (cnt == N) return head.next;
        int res = cnt - N;
        ListNode temp = head;
        while (temp != null) {
            res--;
            if (res == 0) break;
            temp = temp.next;
        }
        temp.next = temp.next.next;
        return head;
    }
}
```

#### Approach 2: Optimal — fast pointer N steps ahead, then move both
1. Move `fast` **N steps** from the head.
2. If `fast` is now `null`, then `N == length` and the head is the target. Return `head->next`.
3. Otherwise start `slow` at the head. Move both one step at a time while `fast->next != null`. When `fast` reaches the last node, `slow` is exactly at the node **before** the target, because the gap between them is N.
4. Unlink with `slow->next = slow->next->next`. **Free the removed node only after** changing the link; freeing it first would lose the rest of the list.

**Dry run** `1 → 2 → 3 → 4 → 5`, N = 2:
- `fast` moves two steps to node 3.
- Move both together: `slow` 1→2 while `fast` 3→4, then `slow` 2→3 while `fast` 4→5.
- `fast->next` is null, so stop. Unlink 4.

**Complexity:** O(len) time, since `fast` covers the list exactly once. O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* removeNthFromEnd(ListNode* head, int N) {
    ListNode* fast = head;
    for (int i = 0; i < N; i++) fast = fast->next;
    if (fast == nullptr) {                       // N == length: remove head
        ListNode* newHead = head->next;
        delete head;
        return newHead;
    }
    ListNode* slow = head;
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* delNode = slow->next;
    slow->next = slow->next->next;               // relink first,
    delete delNode;                              // then free
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode removeNthFromEnd(ListNode head, int N) {
        ListNode fast = head;
        for (int i = 0; i < N; i++) fast = fast.next;
        if (fast == null) return head.next;          // N == length: remove head
        ListNode slow = head;
        while (fast.next != null) {
            fast = fast.next;
            slow = slow.next;
        }
        slow.next = slow.next.next;
        return head;
    }
}
```

#### Key Takeaways
- A **fixed gap between two pointers** turns "from the end" into a single pass.
- Removing the head is the special case, signalled by `fast == null` after the first loop.

[↑ Contents](#contents) · [← Previous](#p188) · [Next →](#p190)

---

<a id="p190"></a>

### 26. Reverse a LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/reverse-linked-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/reverse-a-singly-linked-list) | [Watch](https://youtu.be/D2vI2DNJGd8) |

#### Problem Statement
Reverse a singly linked list and return the new head (LeetCode 206).

```text
1 -> 3 -> 2 -> 5 -> null   ->   5 -> 2 -> 3 -> 1 -> null
```

#### Approach 1: Brute Force — stack of values (two passes)
1. Push every value onto a stack.
2. Traverse again from `head`, overwriting each value with `st.top()` and then popping. Last in, first out means the values come back in reverse order.

Only the data moves; the links stay the same.

**Complexity:** O(2n) time, O(n) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* reverseListStack(ListNode* head) {
    stack<int> st;
    for (ListNode* t = head; t; t = t->next) st.push(t->val);
    for (ListNode* t = head; t; t = t->next) { t->val = st.top(); st.pop(); }
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode reverseListStack(ListNode head) {
        Deque<Integer> st = new ArrayDeque<>();
        for (ListNode t = head; t != null; t = t.next) st.push(t.val);
        for (ListNode t = head; t != null; t = t.next) t.val = st.pop();
        return head;
    }
}
```

#### Approach 2: Optimal (iterative) — reverse each link
For each node `temp`, point its `next` back at the previous node. Save the forward node **before** you overwrite the link:

```text
front = temp->next     // preserve the rest of the list
temp->next = prev      // reverse this link
prev = temp            // advance prev
temp = front           // advance temp
```

Start with `prev = null`, so the old head ends up pointing at null. When `temp` becomes null, `prev` is the new head.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* reverseList(ListNode* head) {
    ListNode* temp = head;
    ListNode* prev = nullptr;
    while (temp != nullptr) {
        ListNode* front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }
    return prev;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode reverseList(ListNode head) {
        ListNode temp = head, prev = null;
        while (temp != null) {
            ListNode front = temp.next;
            temp.next = prev;
            prev = temp;
            temp = front;
        }
        return prev;
    }
}
```

#### Approach 3: Recursive
Break the problem into a smaller one: reverse the list starting at `head->next`, then fix up the two nodes at the front.
- **Base case:** if `head` is null or `head->next` is null, return `head`.
- `newHead = reverse(head->next)`. After this call, `head->next` (call it `front`) is the **tail** of the reversed sublist.
- `front->next = head` and `head->next = null`.
- Return `newHead`, which is the original last node, unchanged on the way back up.

**Trace** `1 → 3 → 2 → 5`:
- `rev(5)` returns 5.
- At node 2: `5.next = 2`, `2.next = null`.
- At node 3: `2.next = 3`, `3.next = null`.
- At node 1: `3.next = 1`, `1.next = null`.
- The result is `5 → 2 → 3 → 1`.

**Complexity:** O(n) time, O(n) recursion stack.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* reverseListRec(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* newHead = reverseListRec(head->next);
    ListNode* front = head->next;       // tail of the reversed sublist
    front->next = head;
    head->next = nullptr;
    return newHead;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode reverseListRec(ListNode head) {
        if (head == null || head.next == null) return head;
        ListNode newHead = reverseListRec(head.next);
        ListNode front = head.next;         // tail of the reversed sublist
        front.next = head;
        head.next = null;
        return newHead;
    }
}
```

#### Key Takeaways
- In-place reversal is a three-pointer dance (`prev`, `temp`, `front`). It's a building block for palindrome checks, k-group reversal and add-one.
- The recursive version teaches "solve the smaller list, then fix the front": `head->next->next = head`.

[↑ Contents](#contents) · [← Previous](#p189) · [Next →](#p191)

---

## FAQs (Medium)

<a id="p191"></a>

### 27. Add one to a number represented by LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Medium) | Core | Yes | [LeetCode](https://leetcode.com/problems/plus-one-linked-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/add-one-to-number-linked-list) | [Watch](https://youtu.be/aXQWhbvT3w0) |

#### Problem Statement
A non-negative number is stored in a linked list, **one digit per node, most significant digit first**. Add 1 to it and return the head of the resulting list.

```text
1 -> 5 -> 9        ->  1 -> 6 -> 0          (159 + 1 = 160)
9 -> 9 -> 9 -> 9   ->  1 -> 0 -> 0 -> 0 -> 0 (an extra digit appears)
```

#### Intuition
Addition starts from the **last** digit, but a singly linked list only lets you walk forward. You can get backward access in two ways: **reverse** the list, or let **recursion's backtracking** visit the nodes in reverse order.

#### Approach 1: Reverse, add, reverse back (iterative)
1. Reverse the list, using the Reverse a LL problem.
2. Walk the reversed list with `carry = 1`. At each node, `data += carry`.
   - If `data < 10`, set `carry = 0` and **break**. No later digit can change.
   - Otherwise set `data = 0`, keep `carry = 1` and continue.
3. Reverse the list again.
4. If `carry` is still 1 (every digit was 9), create a new node `1` in front of the head and return it. Otherwise return `head`.

**Complexity:** O(3n) time (reverse, traverse, reverse), O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* reverseLL(ListNode* head) {
    ListNode *prev = nullptr, *temp = head;
    while (temp) { ListNode* front = temp->next; temp->next = prev; prev = temp; temp = front; }
    return prev;
}
ListNode* addOneIterative(ListNode* head) {
    head = reverseLL(head);
    ListNode* temp = head;
    int carry = 1;
    while (temp != nullptr) {
        temp->val += carry;
        if (temp->val < 10) { carry = 0; break; }
        temp->val = 0;
        carry = 1;
        temp = temp->next;
    }
    head = reverseLL(head);
    if (carry == 1) {
        ListNode* newNode = new ListNode(1);
        newNode->next = head;
        return newNode;
    }
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode reverseLL(ListNode head) {
        ListNode prev = null, temp = head;
        while (temp != null) { ListNode front = temp.next; temp.next = prev; prev = temp; temp = front; }
        return prev;
    }
    static ListNode addOneIterative(ListNode head) {
        head = reverseLL(head);
        ListNode temp = head;
        int carry = 1;
        while (temp != null) {
            temp.val += carry;
            if (temp.val < 10) { carry = 0; break; }
            temp.val = 0;
            carry = 1;
            temp = temp.next;
        }
        head = reverseLL(head);
        if (carry == 1) {
            ListNode newNode = new ListNode(1);
            newNode.next = head;
            return newNode;
        }
        return head;
    }
}
```

#### Approach 2: Recursion — add on the way back (no reversal)
`helper(node)` returns the carry coming out of the sublist that starts at `node`.
- **Base case:** `node == null` returns 1. This is the "+1" being added.
- Otherwise `carry = helper(node->next)`, which recurses all the way to the end first. Then, **while backtracking**:
  - `node->data += carry`;
  - if the result is `< 10`, return 0;
  - otherwise set it to 0 and return 1.
- In the main function, if `helper(head)` returns 1, prepend a new node `1`.

**Dry run** `9 → 9 → 9 → 9`:
- The recursion bottoms out at null, which returns 1.
- On the way back, each 9 becomes 10, is set to 0, and returns 1.
- The final carry is 1, so prepend `1`. Result: `1 0 0 0 0`.

**Complexity:** O(n) time, O(n) recursion stack.

*Trade-off mentioned in the video:* the iterative version uses O(1) space but makes three passes. The recursive version makes one pass but uses stack space proportional to the list's length.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
int addHelper(ListNode* temp) {
    if (temp == nullptr) return 1;          // the +1
    int carry = addHelper(temp->next);
    temp->val += carry;
    if (temp->val < 10) return 0;
    temp->val = 0;
    return 1;
}
ListNode* addOne(ListNode* head) {
    int carry = addHelper(head);
    if (carry == 1) {
        ListNode* newNode = new ListNode(1);
        newNode->next = head;
        return newNode;
    }
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static int addHelper(ListNode temp) {
        if (temp == null) return 1;            // the +1
        int carry = addHelper(temp.next);
        temp.val += carry;
        if (temp.val < 10) return 0;
        temp.val = 0;
        return 1;
    }
    public ListNode addOne(ListNode head) {
        int carry = addHelper(head);
        if (carry == 1) {
            ListNode newNode = new ListNode(1);
            newNode.next = head;
            return newNode;
        }
        return head;
    }
}
```

#### Key Takeaways
- To process a singly linked list backwards, either reverse it or use recursion and do the work while backtracking.
- An all-9s number gains a digit, so it needs a new head.

[↑ Contents](#contents) · [← Previous](#p190) · [Next →](#p192)

---

<a id="p192"></a>

### 28. Find Middle of Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Medium) | Basic | No | [LeetCode](https://leetcode.com/problems/middle-of-the-linked-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-middle-of-linked-list) | [Watch](https://youtu.be/7LjQ57RqgEc) |

#### Problem Statement
Return the **middle node** of a linked list (LeetCode 876). If the length is even, there are two middles; return the **second** one.

```text
1 -> 2 -> 3 -> 4 -> 5        ->  node 3
1 -> 2 -> 3 -> 4 -> 5 -> 6   ->  node 4   (second middle)
```

#### Approach 1: Brute Force — count, then walk to node n/2 + 1
1. Count the nodes `n`.
2. The middle is node number `n / 2 + 1` (integer division): node 3 when n = 5, node 4 when n = 6.
3. Walk from `head`, decrementing a counter until it reaches 0, and return that node.

**Complexity:** O(n + n/2) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* middleNodeBrute(ListNode* head) {
    int cnt = 0;
    for (ListNode* t = head; t; t = t->next) cnt++;
    int midNode = cnt / 2 + 1;
    ListNode* temp = head;
    while (temp != nullptr) {
        midNode--;
        if (midNode == 0) break;
        temp = temp->next;
    }
    return temp;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode middleNodeBrute(ListNode head) {
        int cnt = 0;
        for (ListNode t = head; t != null; t = t.next) cnt++;
        int midNode = cnt / 2 + 1;
        ListNode temp = head;
        while (temp != null) {
            midNode--;
            if (midNode == 0) break;
            temp = temp.next;
        }
        return temp;
    }
}
```

#### Approach 2: Optimal — Tortoise and Hare (slow and fast pointers)
Start `slow` and `fast` at the head. Repeatedly move `slow` one step and `fast` two steps. Stop when `fast` is **null** (even length) or `fast` is on the **last node** (odd length). At that point `slow` is the middle.

**Why it works:** `fast` moves at twice the speed of `slow`, so when `fast` has covered the whole list, `slow` has covered half of it. With an odd length, `fast` passes only through odd positions (1, 3, 5, …) and lands on the last node. With an even length, it jumps past the end to null.

**Complexity:** O(n/2) iterations, O(1) space, one pass.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode middleNode(ListNode head) {
        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }
}
```

#### Key Takeaways
- Tortoise and hare: one pointer at speed 1 and one at speed 2 finds the middle in one pass. The same idea appears in cycle detection, palindrome checks and deleting the middle node.
- The loop condition `fast && fast->next` covers both odd and even lengths.

[↑ Contents](#contents) · [← Previous](#p191) · [Next →](#p193)

---

<a id="p193"></a>

### 29. Delete the middle node in LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/delete-the-middle-node-of-a-linked-list) | [Watch](https://youtu.be/ePpV-_pfOeI) |

#### Problem Statement
Delete the **middle node** of a linked list and return the head (LeetCode 2095). For even lengths, delete the **second** middle. A single-node list becomes empty.

```text
1 -> 2 -> 3 -> 4 -> 5   ->  1 -> 2 -> 4 -> 5
1 -> 2 -> 3 -> 4        ->  1 -> 2 -> 4
```

#### Intuition
To unlink a node, you need to stand on the node **before** it (`prev->next = prev->next->next`). So the goal is to reach the node just before the middle, not the middle itself. That's node number `n / 2` (integer division) in both the odd and even cases.

#### Approach 1: Brute Force — count, then walk to node n/2
1. Handle the edge cases: an empty list, or a single node (return `null`).
2. Count `n`, then walk to node `n / 2`.
3. Save `middle = temp->next`, relink `temp->next = temp->next->next`, and free `middle` (C++).

**Complexity:** O(n + n/2) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* deleteMiddleBrute(ListNode* head) {
    if (head == nullptr || head->next == nullptr) { delete head; return nullptr; }
    int n = 0;
    for (ListNode* t = head; t; t = t->next) n++;
    int res = n / 2;
    ListNode* temp = head;
    while (temp != nullptr) {
        res--;
        if (res == 0) {
            ListNode* middle = temp->next;
            temp->next = temp->next->next;
            delete middle;
            break;
        }
        temp = temp->next;
    }
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode deleteMiddleBrute(ListNode head) {
        if (head == null || head.next == null) return null;
        int n = 0;
        for (ListNode t = head; t != null; t = t.next) n++;
        int res = n / 2;
        ListNode temp = head;
        while (temp != null) {
            res--;
            if (res == 0) { temp.next = temp.next.next; break; }
            temp = temp.next;
        }
        return head;
    }
}
```

#### Approach 2: Optimal — Tortoise and Hare, but skip slow's first step
Standard tortoise and hare would leave `slow` **on** the middle. To stop one node **earlier**, move only `fast` (two steps) on the first round, then run the usual loop. That one skipped step leaves `slow` exactly one node behind the middle.

**Dry run** `1 → 2 → 3 → 4 → 5`:
- `slow` = 1. `fast` moves to 3 (`slow` skips its first step).
- `slow` moves to 2 and `fast` moves to 5. `fast->next` is null, so stop.
- `slow` is node 2, so unlink node 3.

**Complexity:** O(n/2) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* deleteMiddle(ListNode* head) {
    if (head == nullptr || head->next == nullptr) { delete head; return nullptr; }
    ListNode* slow = head;
    ListNode* fast = head->next->next;          // slow skips one step
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* middle = slow->next;
    slow->next = slow->next->next;              // relink first, then free
    delete middle;
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode deleteMiddle(ListNode head) {
        if (head == null || head.next == null) return null;
        ListNode slow = head, fast = head.next.next;   // slow skips one step
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        slow.next = slow.next.next;
        return head;
    }
}
```

#### Key Takeaways
- To delete a node, reach its predecessor. Giving `fast` a head start of one round shifts `slow` back by one node.

[↑ Contents](#contents) · [← Previous](#p192) · [Next →](#p194)

---

<a id="p194"></a>

### 30. Check if LL is palindrome or not

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/palindrome-linked-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-if-a-linked-list-is-a-palindrome) | [Watch](https://youtu.be/lRY_G-u_8jk) |

#### Problem Statement
Return true if the linked list reads the same forwards and backwards (LeetCode 234).

```text
1 -> 2 -> 3 -> 2 -> 1   ->  true
1 -> 2 -> 2 -> 1        ->  true
1 -> 2 -> 3 -> 2 -> 3   ->  false
```

#### Approach 1: Brute Force — stack
1. Push every value onto a stack.
2. Traverse again from `head`. Compare each value with `st.top()`; if they differ, return false. Otherwise pop and move on.

The stack is LIFO, so it gives back the values from the end of the list first.

**Complexity:** O(2n) time, O(n) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
bool isPalindromeStack(ListNode* head) {
    stack<int> st;
    for (ListNode* t = head; t; t = t->next) st.push(t->val);
    for (ListNode* t = head; t; t = t->next) {
        if (t->val != st.top()) return false;
        st.pop();
    }
    return true;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static boolean isPalindromeStack(ListNode head) {
        Deque<Integer> st = new ArrayDeque<>();
        for (ListNode t = head; t != null; t = t.next) st.push(t.val);
        for (ListNode t = head; t != null; t = t.next)
            if (t.val != st.pop()) return false;
        return true;
    }
}
```

#### Approach 2: Optimal — find the middle, reverse the second half, compare, restore
We want to compare the first half with the second half read backwards. A singly linked list can't walk backwards, so **reverse the second half**.
1. **Find the middle** with the tortoise and hare. Stop at the **first** middle for even lengths, which means looping while `fast->next && fast->next->next`. For odd lengths `slow` stops at the exact centre; for even lengths it stops at middle 1.
2. **Reverse** the list starting at `slow->next`. Call its new head `newHead`.
3. **Compare** `first` (starting from `head`) with `second` (starting from `newHead`), until `second` is null.
4. **Restore** the list by reversing `newHead` again, both before returning false and before returning true. Interviewers don't want you to leave the input modified.

**Complexity:** about n/2 to find the middle, n/2 to reverse, n/2 to compare and n/2 to restore, so O(2n) ≈ O(n) time and O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* reverseLL(ListNode* head) {
    ListNode *prev = nullptr, *temp = head;
    while (temp) { ListNode* front = temp->next; temp->next = prev; prev = temp; temp = front; }
    return prev;
}
bool isPalindrome(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return true;
    ListNode *slow = head, *fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {   // stop at first middle
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* newHead = reverseLL(slow->next);
    ListNode *first = head, *second = newHead;
    while (second != nullptr) {
        if (first->val != second->val) {
            reverseLL(newHead);                // restore before returning
            return false;
        }
        first = first->next;
        second = second->next;
    }
    reverseLL(newHead);                        // restore
    return true;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode reverseLL(ListNode head) {
        ListNode prev = null, temp = head;
        while (temp != null) { ListNode front = temp.next; temp.next = prev; prev = temp; temp = front; }
        return prev;
    }
    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null) return true;
        ListNode slow = head, fast = head;
        while (fast.next != null && fast.next.next != null) {    // stop at first middle
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode newHead = reverseLL(slow.next);
        ListNode first = head, second = newHead;
        while (second != null) {
            if (first.val != second.val) {
                reverseLL(newHead);              // restore before returning
                return false;
            }
            first = first.next;
            second = second.next;
        }
        reverseLL(newHead);                      // restore
        return true;
    }
}
```

#### Edge Cases & Pitfalls
- Reversing `slow->next` leaves `slow->next` still pointing at the old first node of the second half, which is now its tail. That's fine, because the comparison stops when `second` becomes null.
- The video reuses its recursive reverse. The iterative version shown here avoids recursion stack space.

#### Key Takeaways
- Find the middle, reverse half, compare, restore. These steps solve many "compare halves" problems on linked lists.

[↑ Contents](#contents) · [← Previous](#p193) · [Next →](#p195)

---

<a id="p195"></a>

### 31. Find the intersection point of Y LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/intersection-of-two-linked-lists/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/intersection-of-two-linked-lists) | [Watch](https://youtu.be/0DYoPz2Tpt4) |

#### Problem Statement
Two singly linked lists may merge into a **Y shape**: from some node onwards they share the same nodes. Return the **first common node**, or null if they never intersect (LeetCode 160). Compare **nodes**, not values. Two different nodes can both hold the value 4.

```text
A: 3 -> 1 -> 4 -> 6 -> 2
B: 1 -> 2 -> 4 -> 5 -> 4 -> 6 -> 2      (the 4 -> 6 -> 2 tail is shared)  ->  node 4
```

#### Approach 1: Brute Force — hash set of nodes
1. Traverse list A and insert every **node address** (pointer) into a set or map.
2. Traverse list B. The first node already in the set is the intersection. If B ends first, return null.

**Complexity:** O(N1 + N2) time, multiplied by the cost of a map operation (log or O(1)). O(N1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* getIntersectionHash(ListNode* headA, ListNode* headB) {
    unordered_set<ListNode*> seen;
    for (ListNode* t = headA; t; t = t->next) seen.insert(t);
    for (ListNode* t = headB; t; t = t->next)
        if (seen.count(t)) return t;
    return nullptr;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode getIntersectionHash(ListNode headA, ListNode headB) {
        Set<ListNode> seen = new HashSet<>();
        for (ListNode t = headA; t != null; t = t.next) seen.add(t);
        for (ListNode t = headB; t != null; t = t.next)
            if (seen.contains(t)) return t;
        return null;
    }
}
```

#### Approach 2: Better — align by length difference
1. Count both lengths, `N1` and `N2`.
2. Advance the head of the **longer** list by `d = |N1 − N2|` nodes, so both pointers are the same distance from the end.
3. Move both one step at a time until they're equal. That's the intersection, or null if they never meet.

A helper `collisionPoint(shorter, longer, d)` avoids duplicating the logic.

**Complexity:** O(N1 + 2·N2) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* collisionPoint(ListNode* t1, ListNode* t2, int d) {   // t2 is the longer list
    while (d--) t2 = t2->next;
    while (t1 != t2) { t1 = t1->next; t2 = t2->next; }
    return t1;                                                   // node or nullptr
}
ListNode* getIntersectionLength(ListNode* headA, ListNode* headB) {
    int n1 = 0, n2 = 0;
    for (ListNode* t = headA; t; t = t->next) n1++;
    for (ListNode* t = headB; t; t = t->next) n2++;
    if (n1 < n2) return collisionPoint(headA, headB, n2 - n1);
    return collisionPoint(headB, headA, n1 - n2);
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode collisionPoint(ListNode t1, ListNode t2, int d) {   // t2 is the longer list
        while (d-- > 0) t2 = t2.next;
        while (t1 != t2) { t1 = t1.next; t2 = t2.next; }
        return t1;
    }
    static ListNode getIntersectionLength(ListNode headA, ListNode headB) {
        int n1 = 0, n2 = 0;
        for (ListNode t = headA; t != null; t = t.next) n1++;
        for (ListNode t = headB; t != null; t = t.next) n2++;
        if (n1 < n2) return collisionPoint(headA, headB, n2 - n1);
        return collisionPoint(headB, headA, n1 - n2);
    }
}
```

#### Approach 3: Optimal — two pointers that switch lists
Start `t1` at headA and `t2` at headB, and move both one step at a time. When a pointer **runs off the end** of its list, redirect it to the **head of the other list**. Stop when `t1 == t2`.

**Why they meet:** suppose B is longer by `d`, so when `t1` reaches the end of A, `t2` is still `d` nodes behind it. `t1` jumps to headB, and `t2` keeps going, `d` nodes behind. When `t2` reaches the end of B, it jumps to headA. By then `t1` has walked `d` nodes into B, so both are now the same distance from the end and stay in step.

In total each pointer walks `N1 + N2` steps. They meet at the intersection, or both become null at the same moment if the lists never meet. Equal-length lists meet without switching at all.

**Complexity:** O(N1 + N2) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (headA == nullptr || headB == nullptr) return nullptr;
    ListNode *t1 = headA, *t2 = headB;
    while (t1 != t2) {
        t1 = t1->next;
        t2 = t2->next;
        if (t1 == t2) return t1;             // collision (or both nullptr)
        if (t1 == nullptr) t1 = headB;
        if (t2 == nullptr) t2 = headA;
    }
    return t1;                               // heads were the same node
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if (headA == null || headB == null) return null;
        ListNode t1 = headA, t2 = headB;
        while (t1 != t2) {
            t1 = t1.next;
            t2 = t2.next;
            if (t1 == t2) return t1;             // collision (or both null)
            if (t1 == null) t1 = headB;
            if (t2 == null) t2 = headA;
        }
        return t1;                               // heads were the same node
    }
}
```

#### Edge Cases & Pitfalls
- Check `t1 == t2` **before** switching lists. If the lists never meet, both pointers become null on the same step, and that check returns null.
- If the two heads are the same node, the loop never runs and that head is returned.

#### Key Takeaways
- Switching lists makes both pointers travel the same total distance, `N1 + N2`. They line up without anyone computing the lengths.

[↑ Contents](#contents) · [← Previous](#p194) · [Next →](#p196)

---

<a id="p196"></a>

### 32. Detect a loop in LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/linked-list-cycle/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/detect-cycle-linked-list) | [Watch](https://youtu.be/wiOo4DC5GGA) |

#### Problem Statement
Return true if the linked list contains a **cycle**, meaning at least one node from which following `next` pointers eventually leads back to that same node (LeetCode 141).

```text
1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> (back to 3)   ->  true
1 -> 2 -> 3 -> 4 -> null                                  ->  false
```

#### Approach 1: Brute Force — hashing visited nodes
Traverse the list, storing each **node** (its address or object reference, not its value) in a set or map. Before storing a node, check whether it is already there. A repeated node means there's a loop. Reaching null means the list is linear. Values can repeat in a list, which is why you store nodes and not values.

**Complexity:** O(n · 2 · cost of a map operation) time, O(n) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
bool hasCycleHash(ListNode* head) {
    unordered_set<ListNode*> seen;
    for (ListNode* temp = head; temp != nullptr; temp = temp->next) {
        if (seen.count(temp)) return true;
        seen.insert(temp);
    }
    return false;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static boolean hasCycleHash(ListNode head) {
        Set<ListNode> seen = new HashSet<>();
        for (ListNode temp = head; temp != null; temp = temp.next) {
            if (seen.contains(temp)) return true;
            seen.add(temp);
        }
        return false;
    }
}
```

#### Approach 2: Optimal — Tortoise and Hare (Floyd's cycle detection)
Move `slow` by 1 and `fast` by 2. If they ever land on the same node, there's a cycle. If `fast` (or `fast->next`) becomes null, the list is linear.

**Why they must meet and can't jump over each other:**
- Once both pointers are inside the loop, let `d` be the distance from `fast` forward to `slow`.
- Each step, `fast` closes 2 nodes of that gap and `slow` opens it by 1, so `d` shrinks by exactly 1: d → d−1 → … → 0. They **must** collide.
- That's why the speeds are 1 and 2. A speed difference of 1 always reaches 0. With speeds 1 and 3, for example, the gap shrinks by 2 and can skip over 0.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
bool hasCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public boolean hasCycle(ListNode head) {
        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) return true;
        }
        return false;
    }
}
```

#### Key Takeaways
- Compare node identity, not values.
- Floyd's algorithm works because the gap shrinks by exactly 1 per step. Be ready to explain that in an interview.

[↑ Contents](#contents) · [← Previous](#p195) · [Next →](#p197)

---

<a id="p197"></a>

### 33. Find the starting point in LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/linked-list-cycle-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-start-of-cycle-linked-list) | [Watch](https://youtu.be/2Kd0KKmmHFc) |

#### Problem Statement
If the linked list has a cycle, return the **node where the cycle begins**. Otherwise return null (LeetCode 142).

```text
1 -> 2 -> 3 -> 15 -> 4 -> 5 -> 6 -> (back to 15)   ->  node 15
```

#### Approach 1: Brute Force — hashing
Traverse the list, storing each node. The **first node you meet twice** is the start of the loop, because every node before it is visited only once. Store whole nodes, not values: a value of 15 could appear more than once.

**Complexity:** O(n × map cost) time, O(n) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* detectCycleHash(ListNode* head) {
    unordered_set<ListNode*> seen;
    for (ListNode* temp = head; temp != nullptr; temp = temp->next) {
        if (seen.count(temp)) return temp;
        seen.insert(temp);
    }
    return nullptr;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode detectCycleHash(ListNode head) {
        Set<ListNode> seen = new HashSet<>();
        for (ListNode temp = head; temp != null; temp = temp.next) {
            if (seen.contains(temp)) return temp;
            seen.add(temp);
        }
        return null;
    }
}
```

#### Approach 2: Optimal — Floyd, then reset one pointer to the head
1. **Detect** the cycle with `slow` and `fast`, as in the previous problem. If there is none, return null.
2. **Find the start:** put `slow` back at `head` and leave `fast` at the meeting point. Move **both one step at a time**. The node where they meet again is the start of the loop.

**Proof (the video's argument):**
- Let `L1` be the distance from the head to the loop start. When `slow` reaches the loop start, it has walked `L1`. `fast` has walked `2·L1`, so it is `L1` nodes into the loop.
- Let `d` be the gap from `fast` forward to `slow`. The gap shrinks by 1 per step, so they collide after `d` more steps. In those `d` steps `slow` moves `d` nodes past the loop start.
- The loop length is `L1 + d`: fast's `L1` nodes into the loop plus the `d`-node gap ahead of it. So from the collision point, it is another `L1` nodes forward to the loop start.
- Both the head and the collision point are therefore `L1` steps from the loop start. Moving both pointers one step at a time makes them meet exactly there.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* detectCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {                 // step 1: loop found
            slow = head;                    // step 2: reset one pointer
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;                    // start of the loop
        }
    }
    return nullptr;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode detectCycle(ListNode head) {
        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {                 // step 1: loop found
                slow = head;                    // step 2: reset one pointer
                while (slow != fast) {
                    slow = slow.next;
                    fast = fast.next;
                }
                return slow;                    // start of the loop
            }
        }
        return null;
    }
}
```

#### Key Takeaways
- After the collision, the head and the collision point are equally far from the loop start. Move both pointers at the same speed and they meet there.
- The video's advice: understand why this works rather than memorising "step 1, step 2".

[↑ Contents](#contents) · [← Previous](#p196) · [Next →](#p198)

---

<a id="p198"></a>

### 34. Length of loop in LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Medium) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/length-of-cycle-linked-list) | [Watch](https://youtu.be/I4g1qbkTPus) |

#### Problem Statement
Return the **number of nodes in the cycle**, or 0 if the list has no cycle.

```text
1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> (back to 3)   ->  7
1 -> 2 -> 3 -> null                                       ->  0
```

#### Approach 1: Brute Force — hash each node with its "timer"
Traverse the list with a counter `timer`, starting at 1, and store `node → timer` in a map. When you reach a node that's already in the map, the loop length is `timer − map[node]`. In the example, node 3 was stored at timer 3 and is revisited at timer 10, so the length is 7. Reaching null means there's no loop, so return 0.

**Complexity:** O(n × map cost) time, O(n) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
int lengthOfLoopHash(ListNode* head) {
    unordered_map<ListNode*, int> visitTime;
    int timer = 1;
    for (ListNode* temp = head; temp != nullptr; temp = temp->next) {
        auto it = visitTime.find(temp);
        if (it != visitTime.end()) return timer - it->second;
        visitTime[temp] = timer++;
    }
    return 0;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static int lengthOfLoopHash(ListNode head) {
        Map<ListNode, Integer> visitTime = new HashMap<>();
        int timer = 1;
        for (ListNode temp = head; temp != null; temp = temp.next) {
            Integer t = visitTime.get(temp);
            if (t != null) return timer - t;
            visitTime.put(temp, timer++);
        }
        return 0;
    }
}
```

#### Approach 2: Optimal — Floyd, then walk the loop once
Detect the meeting point with `slow` and `fast`. That node is **inside** the loop. From there, move one pointer forward, counting steps, until it returns to the meeting node. The count is the loop length.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
int findLength(ListNode* slow, ListNode* fast) {
    int cnt = 1;
    fast = fast->next;
    while (slow != fast) {
        cnt++;
        fast = fast->next;
    }
    return cnt;
}
int lengthOfLoop(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return findLength(slow, fast);
    }
    return 0;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static int findLength(ListNode slow, ListNode fast) {
        int cnt = 1;
        fast = fast.next;
        while (slow != fast) {
            cnt++;
            fast = fast.next;
        }
        return cnt;
    }
    static int lengthOfLoop(ListNode head) {
        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) return findLength(slow, fast);
        }
        return 0;
    }
}
```

#### Key Takeaways
- The Floyd meeting point is guaranteed to be inside the loop, so walking once around from it gives the length.

[↑ Contents](#contents) · [← Previous](#p197) · [Next →](#p199)

---

## FAQs (Hard)

<a id="p199"></a>

### 35. Reverse LL in group of given size K

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/reverse-nodes-in-k-group/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/reverse-linked-list-k-groups) | [Watch](https://youtu.be/lIar1skcQYI) |

#### Problem Statement
Reverse the nodes of the list **k at a time**. If fewer than k nodes remain at the end, leave them as they are. Return the new head (LeetCode 25).

```text
1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10, k = 3
  ->  3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 9 -> 8 -> 7 -> 10
```

#### Approach 1: Brute Force — collect values, reverse each full block, write back *(not in video)*
Copy the values into an array. Reverse each full block of k. Leave the incomplete tail block unchanged. Write the values back into the nodes.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* reverseKGroupArray(ListNode* head, int k) {
    vector<int> vals;
    for (ListNode* t = head; t; t = t->next) vals.push_back(t->val);
    for (int i = 0; i + k <= (int)vals.size(); i += k) reverse(vals.begin() + i, vals.begin() + i + k);
    int i = 0;
    for (ListNode* t = head; t; t = t->next) t->val = vals[i++];
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode reverseKGroupArray(ListNode head, int k) {
        List<Integer> vals = new ArrayList<>();
        for (ListNode t = head; t != null; t = t.next) vals.add(t.val);
        for (int i = 0; i + k <= vals.size(); i += k) Collections.reverse(vals.subList(i, i + k));
        int i = 0;
        for (ListNode t = head; t != null; t = t.next) t.val = vals.get(i++);
        return head;
    }
}
```

#### Approach 2: Optimal — detach each k-group, reverse it, reconnect (as in the video)
Use the existing **Reverse a LL** function. It reverses a whole list, so turn each k-group into its own list first:
1. `temp` points to the first node of the current group, and `prevLast` points to the last node of the previously processed group.
2. `kthNode = getKthNode(temp, k)`, i.e. walk k−1 steps.
   - If it's **null**, fewer than k nodes remain. If `prevLast` exists, set `prevLast->next = temp` to attach the remainder unchanged, then stop.
3. Save `nextNode = kthNode->next`, then **cut**: `kthNode->next = null`.
4. `reverse(temp)`. Afterwards the group runs from `kthNode` (new front) to `temp` (new end).
5. If this is the **first** group (`temp == head`), the overall head becomes `kthNode`. Otherwise link `prevLast->next = kthNode`.
6. Set `prevLast = temp` (the end of this reversed group) and `temp = nextNode`.

**Dry run** with k = 3:
- Group 1, `[1 2 3]`: reversed to `3 2 1`, and the head becomes 3.
- Group 2, `[4 5 6]`: reversed to `6 5 4`, and `1->next = 6`.
- Group 3, `[7 8 9]`: reversed to `9 8 7`, and `4->next = 9`.
- Group 4, `[10]`: has fewer than 3 nodes, so `7->next = 10`.

**Complexity:** O(2n) time, since finding each k-th node is O(n) overall and the reversals are O(n) overall. O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* reverseLL(ListNode* head) {
    ListNode *prev = nullptr, *temp = head;
    while (temp) { ListNode* front = temp->next; temp->next = prev; prev = temp; temp = front; }
    return prev;
}
ListNode* getKthNode(ListNode* temp, int k) {
    k -= 1;
    while (temp != nullptr && k > 0) { k--; temp = temp->next; }
    return temp;
}
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* temp = head;
    ListNode* prevLast = nullptr;
    while (temp != nullptr) {
        ListNode* kthNode = getKthNode(temp, k);
        if (kthNode == nullptr) {                 // fewer than k nodes left
            if (prevLast) prevLast->next = temp;
            break;
        }
        ListNode* nextNode = kthNode->next;
        kthNode->next = nullptr;                  // detach this group
        reverseLL(temp);
        if (temp == head) head = kthNode;         // first group: new head
        else prevLast->next = kthNode;            // link previous group
        prevLast = temp;                          // temp is now the group's tail
        temp = nextNode;
    }
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode reverseLL(ListNode head) {
        ListNode prev = null, temp = head;
        while (temp != null) { ListNode front = temp.next; temp.next = prev; prev = temp; temp = front; }
        return prev;
    }
    static ListNode getKthNode(ListNode temp, int k) {
        k -= 1;
        while (temp != null && k > 0) { k--; temp = temp.next; }
        return temp;
    }
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode temp = head, prevLast = null;
        while (temp != null) {
            ListNode kthNode = getKthNode(temp, k);
            if (kthNode == null) {                    // fewer than k nodes left
                if (prevLast != null) prevLast.next = temp;
                break;
            }
            ListNode nextNode = kthNode.next;
            kthNode.next = null;                      // detach this group
            reverseLL(temp);
            if (temp == head) head = kthNode;         // first group: new head
            else prevLast.next = kthNode;             // link previous group
            prevLast = temp;                          // temp is now the group's tail
            temp = nextNode;
        }
        return head;
    }
}
```

#### Edge Cases & Pitfalls
- A list shorter than k is returned unchanged. In that case `prevLast` is null, so there's nothing to attach.
- The "first group" check must use the original `head`, before it gets updated.

#### Key Takeaways
- To reverse a segment of a linked list, detach it, reverse it as a whole list, and reattach it. Keep `prevLast` and `nextNode` so you can reconnect.

[↑ Contents](#contents) · [← Previous](#p198) · [Next →](#p200)

---

<a id="p200"></a>

### 36. Rotate a LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Hard) | Core | No | [LeetCode](https://leetcode.com/problems/rotate-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/rotate-linked-list-right-k-places) | [Watch](https://youtu.be/uT7YI7XbTY8) |

#### Problem Statement
Rotate the list **to the right by k places**: each rotation moves the last node to the front. Return the new head (LeetCode 61). `k` can be much larger than the length.

```text
1 -> 2 -> 3 -> 4 -> 5, k = 2   ->  4 -> 5 -> 1 -> 2 -> 3
1 -> 2 -> 3,           k = 4   ->  3 -> 1 -> 2        (4 % 3 = 1)
```

#### Approach 1: Brute Force — rotate one step at a time *(not in video)*
Repeat `k % len` times: detach the tail and make it the new head. Each rotation walks the whole list.

**Complexity:** O(len · (k % len)) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* rotateRightBrute(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) return head;
    int len = 0;
    for (ListNode* t = head; t; t = t->next) len++;
    k %= len;
    while (k--) {
        ListNode* prev = head;
        while (prev->next->next) prev = prev->next;   // second last
        ListNode* tail = prev->next;
        prev->next = nullptr;
        tail->next = head;
        head = tail;
    }
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode rotateRightBrute(ListNode head, int k) {
        if (head == null || head.next == null || k == 0) return head;
        int len = 0;
        for (ListNode t = head; t != null; t = t.next) len++;
        k %= len;
        while (k-- > 0) {
            ListNode prev = head;
            while (prev.next.next != null) prev = prev.next;   // second last
            ListNode tail = prev.next;
            prev.next = null;
            tail.next = head;
            head = tail;
        }
        return head;
    }
}
```

#### Approach 2: Optimal — make it circular, then cut (as in the video)
After `k` rotations, the last `k` nodes move to the front. Only two links change:
1. **One traversal** finds the `tail` and the length `len`, starting with `len = 1` at the head.
2. **Large k:** rotating `len` times gives back the original list. So set `k %= len`, and if `k == 0`, return `head`.
3. Set `tail->next = head`. The list is now a circle.
4. The **new last node** is node number `len − k`. Find it with an "n-th node" helper. Then the new `head = newLast->next`, and cut the circle with `newLast->next = null`.

**Complexity:** O(len) to find the tail, plus at most O(len) to find the new last node. That's O(2n) time and O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* findNthNode(ListNode* temp, int k) {
    int cnt = 1;
    while (temp != nullptr) {
        if (cnt == k) return temp;
        cnt++;
        temp = temp->next;
    }
    return temp;
}
ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr || k == 0) return head;
    ListNode* tail = head;
    int len = 1;
    while (tail->next != nullptr) { tail = tail->next; len++; }
    if (k % len == 0) return head;
    k %= len;
    tail->next = head;                              // make it circular
    ListNode* newLastNode = findNthNode(head, len - k);
    head = newLastNode->next;
    newLastNode->next = nullptr;                    // cut
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode findNthNode(ListNode temp, int k) {
        int cnt = 1;
        while (temp != null) {
            if (cnt == k) return temp;
            cnt++;
            temp = temp.next;
        }
        return temp;
    }
    public ListNode rotateRight(ListNode head, int k) {
        if (head == null || k == 0) return head;
        ListNode tail = head;
        int len = 1;
        while (tail.next != null) { tail = tail.next; len++; }
        if (k % len == 0) return head;
        k %= len;
        tail.next = head;                               // make it circular
        ListNode newLastNode = findNthNode(head, len - k);
        head = newLastNode.next;
        newLastNode.next = null;                        // cut
        return head;
    }
}
```

#### Key Takeaways
- Rotation only changes the starting point. Close the circle, then cut it at node `len − (k % len)`.
- Always reduce `k` modulo the length.

[↑ Contents](#contents) · [← Previous](#p199) · [Next →](#p201)

---

<a id="p201"></a>

### 37. Merge two Sorted Lists

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Hard) | Basic | No | [LeetCode](https://leetcode.com/problems/merge-two-sorted-lists/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/merge-two-sorted-linked-lists) | [Watch](https://youtu.be/Xb4slcp1U38) |

#### Problem Statement
Merge two **sorted** linked lists into one sorted list and return its head (LeetCode 21).

```text
l1 = 1 -> 2 -> 4,  l2 = 1 -> 3 -> 4   ->  1 -> 1 -> 2 -> 3 -> 4 -> 4
l1 = 5 -> 7 -> 9,  l2 = 3 -> 4 -> 8 -> 10   ->  3 -> 4 -> 5 -> 7 -> 8 -> 9 -> 10
```

> Ask the interviewer whether you may create new nodes. The video starts with an external-space version, then does it **in place**.

#### Approach 1: Brute Force — build a new list (external space)
Walk both lists and compare their heads. Copy the smaller value into a **new** node appended after a **dummy** node. When one list runs out, copy the rest of the other. Return `dummy->next`.

**Complexity:** O(n1 + n2) time, O(n1 + n2) space for the new nodes.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* mergeNewList(ListNode* l1, ListNode* l2) {
    ListNode dummy(-1);
    ListNode* cur = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { cur->next = new ListNode(l1->val); l1 = l1->next; }
        else { cur->next = new ListNode(l2->val); l2 = l2->next; }
        cur = cur->next;
    }
    for (ListNode* rest = l1 ? l1 : l2; rest; rest = rest->next) { cur->next = new ListNode(rest->val); cur = cur->next; }
    return dummy.next;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode mergeNewList(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(-1), cur = dummy;
        while (l1 != null && l2 != null) {
            if (l1.val <= l2.val) { cur.next = new ListNode(l1.val); l1 = l1.next; }
            else { cur.next = new ListNode(l2.val); l2 = l2.next; }
            cur = cur.next;
        }
        for (ListNode rest = l1 != null ? l1 : l2; rest != null; rest = rest.next) { cur.next = new ListNode(rest.val); cur = cur.next; }
        return dummy.next;
    }
}
```

#### Approach 2: In place — the video's swap method
1. If either list is empty, return the other.
2. Make `l1` the list with the **smaller head** (swap if needed). Save `res = l1`; it's the merged head.
3. While both are non-null:
   - Walk `l1` forward while `l1->val <= l2->val`, remembering the last such node in `temp`.
   - Then `temp->next = l2`. That splices in the other list at the right point.
   - **Swap** `l1` and `l2`. Now `l1` again holds the smaller current value.
4. Return `res`.

**Complexity:** O(n1 + n2) time, O(1) space, with no new nodes.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* mergeTwoListsSwap(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
    if (l1->val > l2->val) swap(l1, l2);
    ListNode* res = l1;
    while (l1 != nullptr && l2 != nullptr) {
        ListNode* temp = nullptr;
        while (l1 != nullptr && l1->val <= l2->val) { temp = l1; l1 = l1->next; }
        temp->next = l2;
        swap(l1, l2);
    }
    return res;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode mergeTwoListsSwap(ListNode l1, ListNode l2) {
        if (l1 == null) return l2;
        if (l2 == null) return l1;
        if (l1.val > l2.val) { ListNode t = l1; l1 = l2; l2 = t; }
        ListNode res = l1;
        while (l1 != null && l2 != null) {
            ListNode temp = null;
            while (l1 != null && l1.val <= l2.val) { temp = l1; l1 = l1.next; }
            temp.next = l2;
            ListNode t = l1; l1 = l2; l2 = t;     // swap
        }
        return res;
    }
}
```

#### Approach 3: In place with a dummy node *(not in video; the common interview form)*
Keep a `tail` pointer starting at a dummy node. Always attach the smaller head, then advance that list. At the end, attach whichever list is left over.

**Complexity:** O(n1 + n2) time, O(1) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(-1);
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(-1), tail = dummy;
        while (l1 != null && l2 != null) {
            if (l1.val <= l2.val) { tail.next = l1; l1 = l1.next; }
            else { tail.next = l2; l2 = l2.next; }
            tail = tail.next;
        }
        tail.next = (l1 != null) ? l1 : l2;
        return dummy.next;
    }
}
```

#### Key Takeaways
- Merging two sorted lists is the core step of merge sort on linked lists (see Sort LL) and of flattening (next problem).
- A dummy node removes the "who is the head?" special case.

[↑ Contents](#contents) · [← Previous](#p200) · [Next →](#p202)

---

<a id="p202"></a>

### 38. Flattening of LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/merge-k-sorted-lists/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/flatten-linked-list) | [Watch](https://youtu.be/ykelywHJWLg) |

#### Problem Statement
Each node has two pointers: `next`, which links the "horizontal" list of heads, and `child` (called `bottom` on GfG), which leads down a **vertically sorted** sub-list. **Flatten** everything into one sorted list linked only through `child`, with every `next` set to null. Return the head.

```text
3 -> 2 -> 1 -> 4 -> 5          (next pointers)
     |    |    |    |
     10   7    9    6
          |         |
          11        8
          |
          12
->  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 11 -> 12   (via child)
```

#### Approach 1: Brute Force — collect, sort, rebuild
1. Traverse with `temp` along `next`. For each node, walk `t2` down the `child` pointers, pushing every value into an array.
2. Sort the array.
3. Build a **new** vertical list from it, linking the nodes through `child`.

Let N be the number of horizontal nodes and M the length of each vertical list.

**Complexity:** O(2·N·M + NM·log(NM)) time, O(2·N·M) space (the array plus the new list).

**C++**
```cpp
struct Node {
    int data; Node* next; Node* child;
    Node(int d) : data(d), next(nullptr), child(nullptr) {}
};
Node* convertArrToVertical(vector<int>& arr) {
    if (arr.empty()) return nullptr;
    Node* head = new Node(arr[0]);
    Node* temp = head;
    for (int i = 1; i < (int)arr.size(); i++) {
        temp->child = new Node(arr[i]);
        temp = temp->child;
    }
    return head;
}
Node* flattenBrute(Node* head) {
    vector<int> arr;
    for (Node* temp = head; temp; temp = temp->next)
        for (Node* t2 = temp; t2; t2 = t2->child) arr.push_back(t2->data);
    sort(arr.begin(), arr.end());
    return convertArrToVertical(arr);
}
```

**Java**
```java
class Node {
    int data; Node next, child;
    Node(int d) { data = d; }
}
class Solution {
    static Node convertArrToVertical(List<Integer> arr) {
        if (arr.isEmpty()) return null;
        Node head = new Node(arr.get(0)), temp = head;
        for (int i = 1; i < arr.size(); i++) {
            temp.child = new Node(arr.get(i));
            temp = temp.child;
        }
        return head;
    }
    static Node flattenBrute(Node head) {
        List<Integer> arr = new ArrayList<>();
        for (Node temp = head; temp != null; temp = temp.next)
            for (Node t2 = temp; t2 != null; t2 = t2.child) arr.add(t2.data);
        Collections.sort(arr);
        return convertArrToVertical(arr);
    }
}
```

#### Approach 2: Optimal — recursively merge vertical lists (no sorting, reuse nodes)
This approach uses the fact that every vertical list is already sorted, and it reuses the existing nodes.
- **Merge two vertical lists:** same as Merge Two Sorted Lists, but along `child`. Use a dummy node, attach the smaller node, and **set every attached node's `next` to null**.
- **Flatten:** `flatten(head)`:
  - base case: if `head` or `head->next` is null, return `head`;
  - `mergedHead = flatten(head->next)`, which flattens everything to the right;
  - return `merge(head, mergedHead)`.

The recursion goes to the last vertical list first. On the way back it merges right to left: (5,6,8) with (4,9) gives `4 5 6 8 9`. That merges with (1,7,11,12), then (2,10), then (3).

**Complexity:**
- Time: each of the N merges walks up to about 2·M·(depth) nodes, so roughly O(N · 2M). The video gives about O(2·N·M) for equal-length lists.
- Space: O(N) recursion depth, and no new data nodes.

**C++**
```cpp
struct Node {
    int data; Node* next; Node* child;
    Node(int d) : data(d), next(nullptr), child(nullptr) {}
};
Node* mergeVertical(Node* l1, Node* l2) {
    Node dummy(-1);
    Node* res = &dummy;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->data < l2->data) { res->child = l1; res = l1; l1 = l1->child; }
        else { res->child = l2; res = l2; l2 = l2->child; }
        res->next = nullptr;
    }
    res->child = l1 ? l1 : l2;
    if (dummy.child) dummy.child->next = nullptr;
    return dummy.child;
}
Node* flattenLinkedList(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    Node* mergedHead = flattenLinkedList(head->next);
    head->next = nullptr;                     // detach before merging
    return mergeVertical(head, mergedHead);
}
```

**Java**
```java
class Node {
    int data; Node next, child;
    Node(int d) { data = d; }
}
class Solution {
    static Node mergeVertical(Node l1, Node l2) {
        Node dummy = new Node(-1), res = dummy;
        while (l1 != null && l2 != null) {
            if (l1.data < l2.data) { res.child = l1; res = l1; l1 = l1.child; }
            else { res.child = l2; res = l2; l2 = l2.child; }
            res.next = null;
        }
        res.child = (l1 != null) ? l1 : l2;
        if (dummy.child != null) dummy.child.next = null;
        return dummy.child;
    }
    static Node flattenLinkedList(Node head) {
        if (head == null || head.next == null) return head;
        Node mergedHead = flattenLinkedList(head.next);
        head.next = null;                         // detach before merging
        return mergeVertical(head, mergedHead);
    }
}
```

#### Edge Cases & Pitfalls
- Every node in the result must have `next == null`. Clear `next` as you attach each node. Also detach `head->next` before merging. If the right part's nodes are all smaller, `head` is attached as a leftover tail without passing through the loop. *(not in video)*
- On GfG the vertical pointer is called `bottom`. Rename `child` accordingly.

#### Key Takeaways
- Flattening is a chain of "merge two sorted lists" calls. Recursion supplies the order: merge the right part first, then fold it into the current list.
- Reusing nodes avoids the O(N·M) extra space of the brute force.

[↑ Contents](#contents) · [← Previous](#p201) · [Next →](#p203)

---

<a id="p203"></a>

### 39. Sort LL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Hard) | Core | No | [LeetCode](https://leetcode.com/problems/sort-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/sort-a-linked-list-using-merge-sort) | [Watch](https://youtu.be/8ocB7a_c-Cc) |

#### Problem Statement
Sort a linked list in ascending order and return its head (LeetCode 148). The target is O(n log n) time with O(1) extra space, apart from recursion.

```text
3 -> 4 -> 2 -> 1 -> 5   ->   1 -> 2 -> 3 -> 4 -> 5
```

#### Approach 1: Brute Force — copy to an array, sort, write back
1. Traverse the list, pushing every value into an array.
2. Sort the array (merge sort or quick sort).
3. Traverse again, overwriting the values in order. The same nodes are reused, so the head doesn't change.

**Complexity:** O(n + n log n + n) time, O(n) space.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* sortListBrute(ListNode* head) {
    vector<int> arr;
    for (ListNode* t = head; t; t = t->next) arr.push_back(t->val);
    sort(arr.begin(), arr.end());
    int i = 0;
    for (ListNode* t = head; t; t = t->next) t->val = arr[i++];
    return head;
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode sortListBrute(ListNode head) {
        List<Integer> arr = new ArrayList<>();
        for (ListNode t = head; t != null; t = t.next) arr.add(t.val);
        Collections.sort(arr);
        int i = 0;
        for (ListNode t = head; t != null; t = t.next) t.val = arr.get(i++);
        return head;
    }
}
```

#### Approach 2: Optimal — merge sort on the list itself
This mirrors merge sort on arrays: split at the middle, sort each half recursively, then merge. Merging linked lists needs **no extra array**, because the nodes are relinked in place.
- **Base case:** an empty list or a single node is already sorted.
- **Split:** find the **first** middle with tortoise and hare, starting `fast = head->next`. For even lengths this stops `slow` at the first middle, so `[3,4] [2,1]` splits correctly. Set `rightHead = middle->next`, then cut the list with `middle->next = null`.
- **Recurse:** `left = sortList(head)` and `right = sortList(rightHead)`.
- **Merge:** use Merge Two Sorted Lists with a dummy node. **Return** the merged head. Arrays don't need a return because they're modified in place, but a linked list's head can change.

**Complexity:** O(log n) levels, each doing O(n) merging plus O(n/2) to find the middle, so O(n log n) time. O(1) extra space apart from the O(log n) recursion stack.

**C++**
```cpp
struct ListNode { int val; ListNode* next; ListNode(int x) : val(x), next(nullptr) {} };
ListNode* mergeTwo(ListNode* l1, ListNode* l2) {
    ListNode dummy(-1);
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}
ListNode* findMiddle(ListNode* head) {          // first middle for even length
    ListNode *slow = head, *fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* middle = findMiddle(head);
    ListNode* rightHead = middle->next;
    middle->next = nullptr;                     // split
    ListNode* left = sortList(head);
    ListNode* right = sortList(rightHead);
    return mergeTwo(left, right);
}
```

**Java**
```java
class ListNode { int val; ListNode next; ListNode(int x) { val = x; } }
class Solution {
    static ListNode mergeTwo(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(-1), tail = dummy;
        while (l1 != null && l2 != null) {
            if (l1.val <= l2.val) { tail.next = l1; l1 = l1.next; }
            else { tail.next = l2; l2 = l2.next; }
            tail = tail.next;
        }
        tail.next = (l1 != null) ? l1 : l2;
        return dummy.next;
    }
    static ListNode findMiddle(ListNode head) {         // first middle for even length
        ListNode slow = head, fast = head.next;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }
    public ListNode sortList(ListNode head) {
        if (head == null || head.next == null) return head;
        ListNode middle = findMiddle(head);
        ListNode rightHead = middle.next;
        middle.next = null;                             // split
        ListNode left = sortList(head);
        ListNode right = sortList(rightHead);
        return mergeTwo(left, right);
    }
}
```

#### Edge Cases & Pitfalls
- **Use the first middle.** With the standard second middle, a two-node list never splits: the left half stays at two nodes, and the recursion never ends.

#### Key Takeaways
- Merge sort suits linked lists well, because merging is O(1) extra space and needs no random access. Quick sort is harder to implement on a list.

[↑ Contents](#contents) · [← Previous](#p202) · [Next →](#p204)

---

<a id="p204"></a>

### 40. Clone a LL with random and next pointer

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQs (Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/copy-list-with-random-pointer/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/clone-linked-list-random-pointer) | [Watch](https://youtu.be/q570bKdrnlw) |

#### Problem Statement
Each node has `val`, `next` and a `random` pointer, which points to any node or to null. Return a **deep copy**: brand-new nodes whose `next` and `random` pointers mirror the original structure, with no pointers back into the original list (LeetCode 138).

```text
[7,null] -> [13,0] -> [11,4] -> [10,2] -> [1,0]     ([val, index of random])
->  an identical but independent list
```

#### Why the usual copy fails
Copying a plain list is easy: walk it and create nodes as you go. With `random`, though, a pointer may refer to a node that **hasn't been created yet**. So first create every copy node, then wire up the pointers.

#### Approach 1: Hash map original → copy (two passes)
1. **Pass 1:** for every original node, create `new Node(val)` and store `map[orig] = copy`.
2. **Pass 2:** set `copy->next = map[orig->next]` and `copy->random = map[orig->random]`. `map[null]` should give null.
3. Return `map[head]`.

**Complexity:** O(2n) time, assuming O(1) map operations. O(n) for the map, plus O(n) for the copy, which the problem requires anyway.

**C++**
```cpp
class Node {
public:
    int val; Node* next; Node* random;
    Node(int v) : val(v), next(nullptr), random(nullptr) {}
};
Node* copyRandomListMap(Node* head) {
    unordered_map<Node*, Node*> mpp;
    for (Node* t = head; t; t = t->next) mpp[t] = new Node(t->val);
    for (Node* t = head; t; t = t->next) {
        mpp[t]->next = t->next ? mpp[t->next] : nullptr;
        mpp[t]->random = t->random ? mpp[t->random] : nullptr;
    }
    return head ? mpp[head] : nullptr;
}
```

**Java**
```java
class Node {
    int val; Node next, random;
    Node(int v) { val = v; }
}
class Solution {
    static Node copyRandomListMap(Node head) {
        Map<Node, Node> mpp = new HashMap<>();
        for (Node t = head; t != null; t = t.next) mpp.put(t, new Node(t.val));
        for (Node t = head; t != null; t = t.next) {
            mpp.get(t).next = mpp.get(t.next);        // get(null) -> null
            mpp.get(t).random = mpp.get(t.random);
        }
        return mpp.get(head);
    }
}
```

#### Approach 2: Optimal — interleave copies, then separate (O(1) extra space)
Store each copy **right after** its original instead of in a map. Then `orig->next` is always `orig`'s copy.
1. **Insert copies:** for every node `t`, create `copy(t->val)`, set `copy->next = t->next` and `t->next = copy`. Move on with `t = t->next->next`.
   The list becomes `7 7' 13 13' 11 11' …`.
2. **Set the random pointers:** for every original `t`, `t->next->random = t->random ? t->random->next : null`. The copy of `t->random` sits right after `t->random`.
3. **Separate the lists:** walk with a dummy node for the copies. Take each `t->next` (the copy) into the result, and restore `t->next = t->next->next` so the original list is unchanged.

**Complexity:** O(3n) time, O(1) extra space besides the required copy.

**C++**
```cpp
class Node {
public:
    int val; Node* next; Node* random;
    Node(int v) : val(v), next(nullptr), random(nullptr) {}
};
Node* copyRandomList(Node* head) {
    // 1. insert copy nodes in between
    for (Node* t = head; t; t = t->next->next) {
        Node* copy = new Node(t->val);
        copy->next = t->next;
        t->next = copy;
    }
    // 2. connect random pointers of the copies
    for (Node* t = head; t; t = t->next->next)
        t->next->random = t->random ? t->random->next : nullptr;
    // 3. separate the two lists (and restore the original)
    Node dummy(-1);
    Node* res = &dummy;
    for (Node* t = head; t; t = t->next) {
        res->next = t->next;          // copy node
        res = res->next;
        t->next = t->next->next;      // restore original link
    }
    return dummy.next;
}
```

**Java**
```java
class Node {
    int val; Node next, random;
    Node(int v) { val = v; }
}
class Solution {
    public Node copyRandomList(Node head) {
        for (Node t = head; t != null; t = t.next.next) {        // 1. insert copies
            Node copy = new Node(t.val);
            copy.next = t.next;
            t.next = copy;
        }
        for (Node t = head; t != null; t = t.next.next)          // 2. random pointers
            t.next.random = (t.random != null) ? t.random.next : null;
        Node dummy = new Node(-1), res = dummy;
        for (Node t = head; t != null; t = t.next) {             // 3. separate
            res.next = t.next;
            res = res.next;
            t.next = t.next.next;
        }
        return dummy.next;
    }
}
```

#### Edge Cases & Pitfalls
- `random` can be null. Guard it before reading `t->random->next`.
- **Restore** the original list during step 3. A deep copy must leave the input untouched.

#### Key Takeaways
- To copy a graph-like structure, create all the nodes first, then wire the pointers. A map gives O(n) space; interleaving copies inside the original list gives O(1).

[↑ Contents](#contents) · [← Previous](#p203) · [Next →](#p205)

---

## FAQS (DLL)

<a id="p205"></a>

### 41. Delete all occurrences of a key in DLL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQS (DLL) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/delete-all-occurrences-of-a-key-in-a-doubly-linked-list) | [Watch](https://youtu.be/Mh0NH_SD92k) |

#### Problem Statement
Delete **every** node whose value equals `key` from a doubly linked list, and return the (possibly new) head.

```text
10 <-> 4 <-> 10 <-> 10 <-> 6 <-> 10, key = 10   ->   4 <-> 6
```

#### Approach: Single traversal with careful relinking (as in the video)
Traverse with `temp`, the usual way. When `temp->data == key`:
1. If `temp` is the **head**, move `head = head->next`.
2. Let `nextNode = temp->next` and `prevNode = temp->back`.
3. If `nextNode` exists, set `nextNode->back = prevNode`. If `prevNode` exists, set `prevNode->next = nextNode`. Both null checks matter: without them you'd dereference null when deleting the head or the tail.
4. Free `temp` (C++ only; Java's garbage collector handles it). Continue from `temp = nextNode`.

Otherwise, just move `temp = temp->next`.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
class Node {
public:
    int data; Node* next; Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* deleteAllOccurrences(Node* head, int key) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == key) {
            if (temp == head) head = head->next;
            Node* nextNode = temp->next;
            Node* prevNode = temp->back;
            if (nextNode) nextNode->back = prevNode;
            if (prevNode) prevNode->next = nextNode;
            delete temp;
            temp = nextNode;
        } else {
            temp = temp->next;
        }
    }
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node deleteAllOccurrences(Node head, int key) {
        Node temp = head;
        while (temp != null) {
            if (temp.data == key) {
                if (temp == head) head = head.next;
                Node nextNode = temp.next, prevNode = temp.back;
                if (nextNode != null) nextNode.back = prevNode;
                if (prevNode != null) prevNode.next = nextNode;
                temp = nextNode;
            } else {
                temp = temp.next;
            }
        }
        return head;
    }
}
```

#### Key Takeaways
- Unlinking a DLL node is two guarded assignments: `next->back = prev` and `prev->next = next`. Update `head` when the head itself is deleted.

[↑ Contents](#contents) · [← Previous](#p204) · [Next →](#p206)

---

<a id="p206"></a>

### 42. Remove duplicates from sorted DLL

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQS (DLL) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/remove-duplicates-from-a-sorted-doubly-linked-list) | [Watch](https://youtu.be/YJKVTnOJXSY) |

#### Problem Statement
Remove duplicates from a **sorted** doubly linked list so that each value appears once. Return the head.

```text
1 <-> 1 <-> 1 <-> 2 <-> 3 <-> 3 <-> 4   ->   1 <-> 2 <-> 3 <-> 4
```

#### Approach: Skip each run of equal values
Because the list is sorted, duplicates are **contiguous**.
- Standing at `temp`, move `nextNode` forward while `nextNode->data == temp->data`. In C++, free each duplicate as you pass it.
- `nextNode` is now the first node with a different value, or null. Link `temp->next = nextNode`, and if `nextNode` isn't null, set `nextNode->back = temp`.
- Advance `temp = temp->next`. Stop when `temp` is null or is the last node.

When there are no duplicates, the relinking rewrites links to the nodes they already point to, which is harmless. No special case is needed.

**Complexity:**
- Time: O(n). There are two nested loops, but every node is visited once in total. The inner loop visits the duplicates and the outer loop only lands on distinct values.
- Space: O(1).

**C++**
```cpp
class Node {
public:
    int data; Node* next; Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* removeDuplicates(Node* head) {
    Node* temp = head;
    while (temp != nullptr && temp->next != nullptr) {
        Node* nextNode = temp->next;
        while (nextNode != nullptr && nextNode->data == temp->data) {
            Node* duplicate = nextNode;
            nextNode = nextNode->next;
            delete duplicate;                       // free (C++)
        }
        temp->next = nextNode;
        if (nextNode) nextNode->back = temp;
        temp = temp->next;
    }
    return head;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node removeDuplicates(Node head) {
        Node temp = head;
        while (temp != null && temp.next != null) {
            Node nextNode = temp.next;
            while (nextNode != null && nextNode.data == temp.data) nextNode = nextNode.next;
            temp.next = nextNode;
            if (nextNode != null) nextNode.back = temp;
            temp = temp.next;
        }
        return head;
    }
}
```

#### Key Takeaways
- In sorted data, duplicates are adjacent, so "skip the run" gives a linear solution.
- Nested loops aren't automatically O(n²). Count how many times each node is actually touched.

[↑ Contents](#contents) · [← Previous](#p205) · [Next →](#p207)

---

<a id="p207"></a>

### 43. Find Pairs with Given Sum in Doubly Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Linked-List › FAQS (DLL) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-pairs-with-given-sum-in-doubly-linked-list) | [Watch](https://youtu.be/YitR4dQsddE) |

#### Problem Statement
Given a **sorted** doubly linked list of distinct values and a target `sum`, return **all pairs** `(a, b)` of node values with `a + b == sum`.

```text
1 <-> 2 <-> 3 <-> 4 <-> 9, sum = 5   ->   [(1, 4), (2, 3)]
```

#### Approach 1: Brute Force — nested traversal with early stop
For each `t1`, move `t2` from `t1->next` forward while `t1->data + t2->data <= sum`. Record the pairs that hit `sum` exactly. Because the list is sorted, you can stop the inner loop as soon as the sum exceeds the target.

**Complexity:** about O(n²) time in the worst case, O(1) extra space besides the output.

**C++**
```cpp
class Node {
public:
    int data; Node* next; Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
vector<pair<int, int>> findPairsBrute(Node* head, int sum) {
    vector<pair<int, int>> ans;
    for (Node* t1 = head; t1 != nullptr; t1 = t1->next)
        for (Node* t2 = t1->next; t2 != nullptr && t1->data + t2->data <= sum; t2 = t2->next)
            if (t1->data + t2->data == sum) ans.push_back({t1->data, t2->data});
    return ans;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static List<int[]> findPairsBrute(Node head, int sum) {
        List<int[]> ans = new ArrayList<>();
        for (Node t1 = head; t1 != null; t1 = t1.next)
            for (Node t2 = t1.next; t2 != null && t1.data + t2.data <= sum; t2 = t2.next)
                if (t1.data + t2.data == sum) ans.add(new int[]{t1.data, t2.data});
        return ans;
    }
}
```

#### Approach 2: Optimal — two pointers from both ends
A DLL can move **backwards**, so the array two-sum technique works directly:
- Put `left` at the head and `right` at the **tail**. Finding the tail takes one traversal.
- While `left->data < right->data`:
  - If `left + right == sum`, record the pair and move both pointers inward.
  - If the sum is **too small**, move `left` forward.
  - If it's **too large**, move `right` backward.
- Stop when the pointers meet or cross.

**Dry run:**
- (1, 9) sums to 10, which is more than 5, so move `right` back.
- (1, 4) sums to 5, so record it and move both.
- (2, 3) sums to 5, so record it and move both.
- Now `left` is 3 and `right` is 2. They've crossed, so stop.

**Complexity:** O(n) to find the tail plus O(n) for the scan, so O(2n). O(1) space besides the output.

**C++**
```cpp
class Node {
public:
    int data; Node* next; Node* back;
    Node(int d, Node* n = nullptr, Node* b = nullptr) : data(d), next(n), back(b) {}
};
Node* findTail(Node* head) {
    Node* tail = head;
    while (tail->next != nullptr) tail = tail->next;
    return tail;
}
vector<pair<int, int>> findPairsWithGivenSum(Node* head, int sum) {
    vector<pair<int, int>> ans;
    if (head == nullptr) return ans;
    Node* left = head;
    Node* right = findTail(head);
    while (left->data < right->data) {
        int s = left->data + right->data;
        if (s == sum) {
            ans.push_back({left->data, right->data});
            left = left->next;
            right = right->back;
        } else if (s < sum) left = left->next;
        else right = right->back;
    }
    return ans;
}
```

**Java**
```java
class Node {
    int data; Node next, back;
    Node(int d) { data = d; }
    Node(int d, Node n, Node b) { data = d; next = n; back = b; }
}
class Solution {
    static Node findTail(Node head) {
        Node tail = head;
        while (tail.next != null) tail = tail.next;
        return tail;
    }
    static List<int[]> findPairsWithGivenSum(Node head, int sum) {
        List<int[]> ans = new ArrayList<>();
        if (head == null) return ans;
        Node left = head, right = findTail(head);
        while (left.data < right.data) {
            int s = left.data + right.data;
            if (s == sum) {
                ans.add(new int[]{left.data, right.data});
                left = left.next;
                right = right.back;
            } else if (s < sum) left = left.next;
            else right = right.back;
        }
        return ans;
    }
}
```

#### Key Takeaways
- Sortedness plus backward links makes the classic two-pointer two-sum work on a DLL in linear time.
- The stop condition `left->data < right->data` works because the values are distinct and sorted: the pointers have met or crossed exactly when that comparison fails.

[↑ Contents](#contents) · [← Previous](#p206)

---
