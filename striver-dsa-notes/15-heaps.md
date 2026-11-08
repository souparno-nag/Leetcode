# Heaps — Striver's A2Z DSA Sheet Notes

Section 15 of 20 · 19 problems · 0 with video, 19 without · [All sections](00-index.md)

[← Binary Search Trees](14-binary-search-trees.md) | [Graphs →](16-graphs.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Theory and Implementation**

1. [Heapify Algorithm](#p322) — Core · *no video*
2. [Build heap from a given Array](#p323) — Core · *no video*
3. [Implement Min Heap](#p324) — Core · *no video*
4. [Implement Max Heap](#p325) — Core · *no video*
5. [Check if an array represents a min heap](#p326) — Core · *no video*
6. [Convert Min Heap to Max Heap](#p327) — Core · *no video*
7. [Heap Sort](#p328) — Pro · *no video*
8. [K-th Largest element in an array](#p329) — Pro · *no video*

**FAQs**

9. [Kth largest element in a stream of running integers](#p330) — Pro · *no video*
10. [Sort a K-Sorted Array](#p331) — — · *no video*
11. [Merge K sorted Lists](#p332) — Pro · *no video*
12. [Replace Elements by Their Rank](#p333) — Core · *no video*
13. [Task Scheduler](#p334) — Core · *no video*
14. [Hand of Straights](#p335) — Core · *no video*
15. [Design Twitter](#p336) — Core · *no video*
16. [Minimum Cost to Connect Sticks](#p337) — Core · *no video*
17. [Maximum Sum Combination](#p338) — Core · *no video*
18. [Find Median from Data Stream](#p339) — Pro · *no video*
19. [Top K Frequent Elements](#p340) — Core · *no video*

---

## Theory and Implementation

<a id="p322"></a>

### 1. Heapify Algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › Theory and Implementation | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

> **Heap basics** (used throughout this section):
> - A **binary heap** is a **complete binary tree** stored in an array (0-indexed): for index `i`, `parent = (i − 1) / 2`, `left = 2i + 1`, `right = 2i + 2`.
> - In a **min-heap** every parent is ≤ its children, so the minimum sits at index 0. A **max-heap** is the reverse.
> - Height = ⌊log₂ n⌋, so moving a value up or down one level at a time costs **O(log n)**.
> - Libraries: C++ `priority_queue<int>` (max-heap) and `priority_queue<int, vector<int>, greater<int>>` (min-heap); Java `PriorityQueue<Integer>` (min-heap) and `new PriorityQueue<>(Collections.reverseOrder())` (max-heap).

#### Problem Statement
Given an array `arr` that is a valid **min-heap**, an index `ind` and a value `val`, set `arr[ind] = val` and **restore the min-heap property** (heapify).

```text
arr = [1, 4, 5, 5, 7, 6], ind = 5, val = 2   ->  [1, 4, 2, 5, 7, 5]   (2 sifts up past 5)
arr = [2, 4, 3, 6, 5],    ind = 0, val = 9   ->  [3, 4, 9, 6, 5]      (9 sifts down)
```

#### Intuition — only one path can be broken
Changing one value can only violate the heap property along a single path:
- if the new value is **smaller** than before, it may be smaller than its parent, so **sift up** (heapify-up);
- if it is **larger**, it may be larger than a child, so **sift down** (heapify-down).

#### Approach 1: Brute Force — rebuild the whole heap
Assign the value, then rebuild the heap from scratch (see "Build heap").

**Complexity:** O(n) time, O(log n) recursion stack.

**C++**
```cpp
void siftDownMin(vector<int>& a, int n, int i) {
    while (true) {
        int smallest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && a[l] < a[smallest]) smallest = l;
        if (r < n && a[r] < a[smallest]) smallest = r;
        if (smallest == i) break;
        swap(a[i], a[smallest]);
        i = smallest;
    }
}
void heapifyRebuild(vector<int>& arr, int ind, int val) {
    arr[ind] = val;
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) siftDownMin(arr, n, i);
}
```

**Java**
```java
class Solution {
    static void siftDownMin(int[] a, int n, int i) {
        while (true) {
            int smallest = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a[l] < a[smallest]) smallest = l;
            if (r < n && a[r] < a[smallest]) smallest = r;
            if (smallest == i) break;
            int t = a[i]; a[i] = a[smallest]; a[smallest] = t;
            i = smallest;
        }
    }
    static void heapifyRebuild(int[] arr, int ind, int val) {
        arr[ind] = val;
        int n = arr.length;
        for (int i = n / 2 - 1; i >= 0; i--) siftDownMin(arr, n, i);
    }
}
```

#### Approach 2: Optimal — sift up or sift down from `ind`
- **Sift up:** while `i > 0` and `a[i] < a[parent]`, swap with the parent and move up.
- **Sift down:** while some child is smaller than `a[i]`, swap with the **smaller** child and move down. Using the smaller child keeps the other subtree valid.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
void siftUpMin(vector<int>& a, int i) {
    while (i > 0 && a[i] < a[(i - 1) / 2]) {
        swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
void siftDownMinOpt(vector<int>& a, int i) {
    int n = a.size();
    while (true) {
        int smallest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && a[l] < a[smallest]) smallest = l;
        if (r < n && a[r] < a[smallest]) smallest = r;
        if (smallest == i) return;
        swap(a[i], a[smallest]);
        i = smallest;
    }
}
void heapify(vector<int>& arr, int ind, int val) {
    int old = arr[ind];
    arr[ind] = val;
    if (val < old) siftUpMin(arr, ind);          // smaller: may violate with its parent
    else siftDownMinOpt(arr, ind);               // larger: may violate with its children
}
```

**Java**
```java
class Solution {
    static void swap(int[] a, int i, int j) { int t = a[i]; a[i] = a[j]; a[j] = t; }
    static void siftUpMin(int[] a, int i) {
        while (i > 0 && a[i] < a[(i - 1) / 2]) {
            swap(a, i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }
    static void siftDownMinOpt(int[] a, int i) {
        int n = a.length;
        while (true) {
            int smallest = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a[l] < a[smallest]) smallest = l;
            if (r < n && a[r] < a[smallest]) smallest = r;
            if (smallest == i) return;
            swap(a, i, smallest);
            i = smallest;
        }
    }
    static void heapify(int[] arr, int ind, int val) {
        int old = arr[ind];
        arr[ind] = val;
        if (val < old) siftUpMin(arr, ind);
        else siftDownMinOpt(arr, ind);
    }
}
```

#### Key Takeaways
- Heapify-up and heapify-down are the two primitives behind every heap operation: insert sifts up, extract sifts down, and decrease/increase-key uses one or the other.

[↑ Contents](#contents) · [Next →](#p323)

---

<a id="p323"></a>

### 2. Build heap from a given Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › Theory and Implementation | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Rearrange an arbitrary array **in place** so that it becomes a **min-heap**. (A max-heap is symmetric.)

```text
arr = [9, 4, 7, 1, -2, 6, 5]   ->  e.g. [-2, 1, 5, 9, 4, 6, 7]   (any valid min-heap)
```

#### Approach 1: Brute Force — insert one element at a time
Treat `arr[0..i−1]` as a heap and add `arr[i]` with sift-up, for i = 1 … n−1.

**Complexity:** O(n log n) time, O(1) space.

**C++**
```cpp
void buildHeapByInsert(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        int j = i;
        while (j > 0 && a[j] < a[(j - 1) / 2]) { swap(a[j], a[(j - 1) / 2]); j = (j - 1) / 2; }
    }
}
```

**Java**
```java
class Solution {
    static void buildHeapByInsert(int[] a) {
        for (int i = 1; i < a.length; i++) {
            int j = i;
            while (j > 0 && a[j] < a[(j - 1) / 2]) {
                int t = a[j]; a[j] = a[(j - 1) / 2]; a[(j - 1) / 2] = t;
                j = (j - 1) / 2;
            }
        }
    }
}
```

#### Approach 2: Optimal — bottom-up heapify (Floyd's method)
- **Leaves are already heaps.** Indices `n/2 … n−1` are leaves, and each is a valid one-element heap.
- **Fix the rest bottom-up.** Call **sift-down** on every internal node from `n/2 − 1` down to `0`. When node `i` is processed, both of its subtrees are already heaps, so a single sift-down fixes the subtree rooted at `i`.
- **Why it's O(n), not O(n log n).** Most nodes are near the bottom and sift down only a little. Summing the heights, Σ (n / 2ʰ⁺¹)·h, gives O(n).

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
void siftDown(vector<int>& a, int n, int i) {
    while (true) {
        int smallest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && a[l] < a[smallest]) smallest = l;
        if (r < n && a[r] < a[smallest]) smallest = r;
        if (smallest == i) return;
        swap(a[i], a[smallest]);
        i = smallest;
    }
}
void buildMinHeap(vector<int>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--) siftDown(a, n, i);   // last internal node -> root
}
```

**Java**
```java
class Solution {
    static void siftDown(int[] a, int n, int i) {
        while (true) {
            int smallest = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a[l] < a[smallest]) smallest = l;
            if (r < n && a[r] < a[smallest]) smallest = r;
            if (smallest == i) return;
            int t = a[i]; a[i] = a[smallest]; a[smallest] = t;
            i = smallest;
        }
    }
    static void buildMinHeap(int[] a) {
        int n = a.length;
        for (int i = n / 2 - 1; i >= 0; i--) siftDown(a, n, i);
    }
}
```

#### Key Takeaways
- Build-heap is O(n) with bottom-up sift-down. This is why `make_heap` and `heapq.heapify` are linear.

[↑ Contents](#contents) · [← Previous](#p322) · [Next →](#p324)

---

<a id="p324"></a>

### 3. Implement Min Heap

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › Theory and Implementation | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Implement a **min-heap** from scratch, without library priority queues, supporting:
- `push(x)`;
- `pop()`, which removes the minimum;
- `top()`, which returns the minimum;
- `size()` and `isEmpty()`.

```text
push 5, push 3, push 8, top -> 3, pop, top -> 5, push 1, top -> 1, size -> 3
```

#### Approach: Array-backed binary heap
| op | how | cost |
|---|---|---|
| `push(x)` | append at the end, then **sift up** | O(log n) |
| `pop()` | move the last element to index 0, shrink by one, then **sift down** from 0 | O(log n) |
| `top()` | `a[0]` | O(1) |
| `size()` / `isEmpty()` | the array length | O(1) |

**Space:** O(n).

**C++**
```cpp
class MinHeap {
    vector<int> a;
    void up(int i) {
        while (i > 0 && a[i] < a[(i - 1) / 2]) { swap(a[i], a[(i - 1) / 2]); i = (i - 1) / 2; }
    }
    void down(int i) {
        int n = a.size();
        while (true) {
            int s = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a[l] < a[s]) s = l;
            if (r < n && a[r] < a[s]) s = r;
            if (s == i) return;
            swap(a[i], a[s]);
            i = s;
        }
    }
public:
    void push(int x) { a.push_back(x); up(a.size() - 1); }
    void pop() {
        if (a.empty()) return;
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) down(0);
    }
    int top() { return a.empty() ? -1 : a[0]; }
    int size() { return a.size(); }
    bool isEmpty() { return a.empty(); }
};
```

**Java**
```java
class MinHeap {
    private final List<Integer> a = new ArrayList<>();
    private void swap(int i, int j) { int t = a.get(i); a.set(i, a.get(j)); a.set(j, t); }
    private void up(int i) {
        while (i > 0 && a.get(i) < a.get((i - 1) / 2)) { swap(i, (i - 1) / 2); i = (i - 1) / 2; }
    }
    private void down(int i) {
        int n = a.size();
        while (true) {
            int s = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a.get(l) < a.get(s)) s = l;
            if (r < n && a.get(r) < a.get(s)) s = r;
            if (s == i) return;
            swap(i, s);
            i = s;
        }
    }
    void push(int x) { a.add(x); up(a.size() - 1); }
    void pop() {
        if (a.isEmpty()) return;
        a.set(0, a.get(a.size() - 1));
        a.remove(a.size() - 1);
        if (!a.isEmpty()) down(0);
    }
    int top() { return a.isEmpty() ? -1 : a.get(0); }
    int size() { return a.size(); }
    boolean isEmpty() { return a.isEmpty(); }
}
```

#### Key Takeaways
- Every heap operation is "fix one path": push sifts up from the bottom, and pop moves the last element to the root and sifts down.

[↑ Contents](#contents) · [← Previous](#p323) · [Next →](#p325)

---

<a id="p325"></a>

### 4. Implement Max Heap

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › Theory and Implementation | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Implement a **max-heap** from scratch, supporting `push`, `pop` (removes the maximum), `top`, `size` and `isEmpty`.

```text
push 5, push 3, push 8, top -> 8, pop, top -> 5
```

#### Approach: Same as the min-heap, with the comparisons flipped
- **Sift up** while the child is **greater** than its parent.
- **Sift down** towards the **larger** child.

An alternative trick is to store negated values in a min-heap.

**Complexity:** O(log n) for push and pop, O(1) for top. O(n) space.

**C++**
```cpp
class MaxHeap {
    vector<int> a;
    void up(int i) {
        while (i > 0 && a[i] > a[(i - 1) / 2]) { swap(a[i], a[(i - 1) / 2]); i = (i - 1) / 2; }
    }
    void down(int i) {
        int n = a.size();
        while (true) {
            int g = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a[l] > a[g]) g = l;
            if (r < n && a[r] > a[g]) g = r;
            if (g == i) return;
            swap(a[i], a[g]);
            i = g;
        }
    }
public:
    void push(int x) { a.push_back(x); up(a.size() - 1); }
    void pop() {
        if (a.empty()) return;
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) down(0);
    }
    int top() { return a.empty() ? -1 : a[0]; }
    int size() { return a.size(); }
    bool isEmpty() { return a.empty(); }
};
```

**Java**
```java
class MaxHeap {
    private final List<Integer> a = new ArrayList<>();
    private void swap(int i, int j) { int t = a.get(i); a.set(i, a.get(j)); a.set(j, t); }
    private void up(int i) {
        while (i > 0 && a.get(i) > a.get((i - 1) / 2)) { swap(i, (i - 1) / 2); i = (i - 1) / 2; }
    }
    private void down(int i) {
        int n = a.size();
        while (true) {
            int g = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a.get(l) > a.get(g)) g = l;
            if (r < n && a.get(r) > a.get(g)) g = r;
            if (g == i) return;
            swap(i, g);
            i = g;
        }
    }
    void push(int x) { a.add(x); up(a.size() - 1); }
    void pop() {
        if (a.isEmpty()) return;
        a.set(0, a.get(a.size() - 1));
        a.remove(a.size() - 1);
        if (!a.isEmpty()) down(0);
    }
    int top() { return a.isEmpty() ? -1 : a.get(0); }
    int size() { return a.size(); }
    boolean isEmpty() { return a.isEmpty(); }
}
```

#### Key Takeaways
- A max-heap is a min-heap with the comparator reversed.

[↑ Contents](#contents) · [← Previous](#p324) · [Next →](#p326)

---

<a id="p326"></a>

### 5. Check if an array represents a min heap

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › Theory and Implementation | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return `true` if an array represents a **min-heap**: for every `i`, `arr[i] ≤ arr[2i+1]` and `arr[i] ≤ arr[2i+2]` wherever those children exist.

```text
[10, 20, 30, 21, 23]  ->  true
[10, 20, 30, 25, 15]  ->  false   (20 > 15, its right child)
```

#### Approach: Check every parent against its children
Only indices `0 … n/2 − 1` have children. Check each of them.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
bool isMinHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= n / 2 - 1; i++) {
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && arr[i] > arr[l]) return false;
        if (r < n && arr[i] > arr[r]) return false;
    }
    return true;
}
```

**Java**
```java
class Solution {
    static boolean isMinHeap(int[] arr) {
        int n = arr.length;
        for (int i = 0; i <= n / 2 - 1; i++) {
            int l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && arr[i] > arr[l]) return false;
            if (r < n && arr[i] > arr[r]) return false;
        }
        return true;
    }
}
```

#### Key Takeaways
- Heap validity is a local property: every parent compared with at most two children.

[↑ Contents](#contents) · [← Previous](#p325) · [Next →](#p327)

---

<a id="p327"></a>

### 6. Convert Min Heap to Max Heap

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › Theory and Implementation | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an array that is a **min-heap**, convert it **in place** into a **max-heap**.

```text
[3, 5, 9, 6, 8, 20, 10, 12, 18, 9]  ->  e.g. [20, 18, 10, 12, 9, 9, 3, 5, 6, 8]
```

#### Intuition
The min-heap ordering doesn't help build a max-heap: the structure is still a complete tree, but the order is reversed. So treat the array as **arbitrary** and run **build-max-heap**.

#### Approach: Bottom-up max-heapify
Sift down from `n/2 − 1` to `0` towards the **larger** child.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
void siftDownMax(vector<int>& a, int n, int i) {
    while (true) {
        int g = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && a[l] > a[g]) g = l;
        if (r < n && a[r] > a[g]) g = r;
        if (g == i) return;
        swap(a[i], a[g]);
        i = g;
    }
}
void convertMinToMaxHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) siftDownMax(arr, n, i);
}
```

**Java**
```java
class Solution {
    static void siftDownMax(int[] a, int n, int i) {
        while (true) {
            int g = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a[l] > a[g]) g = l;
            if (r < n && a[r] > a[g]) g = r;
            if (g == i) return;
            int t = a[i]; a[i] = a[g]; a[g] = t;
            i = g;
        }
    }
    static void convertMinToMaxHeap(int[] arr) {
        int n = arr.length;
        for (int i = n / 2 - 1; i >= 0; i--) siftDownMax(arr, n, i);
    }
}
```

#### Key Takeaways
- Any heap conversion is just build-heap with the other comparator, in O(n).

[↑ Contents](#contents) · [← Previous](#p326) · [Next →](#p328)

---

<a id="p328"></a>

### 7. Heap Sort

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › Theory and Implementation | Pro | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/heap-sort) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Sort an array in ascending order using **heap sort**: in place and O(n log n).

```text
[4, 1, 3, 9, 7]   ->   [1, 3, 4, 7, 9]
```

#### Approach: Build a max-heap, then repeatedly move the max to the end
1. **Build a max-heap** in O(n).
2. **Shrink it one element at a time.** For `end = n−1` down to `1`:
   - swap `a[0]`, the current maximum, with `a[end]`. The maximum is now in its final position;
   - sift down `a[0]` within the heap `a[0 … end−1]`.

**Complexity:** O(n log n) time in every case. O(1) extra space. Not stable.

**C++**
```cpp
void siftDownHS(vector<int>& a, int n, int i) {
    while (true) {
        int g = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && a[l] > a[g]) g = l;
        if (r < n && a[r] > a[g]) g = r;
        if (g == i) return;
        swap(a[i], a[g]);
        i = g;
    }
}
void heapSort(vector<int>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--) siftDownHS(a, n, i);   // build max-heap
    for (int end = n - 1; end > 0; end--) {
        swap(a[0], a[end]);                                     // max goes to its final place
        siftDownHS(a, end, 0);                                  // restore heap on a[0..end-1]
    }
}
```

**Java**
```java
class Solution {
    static void siftDownHS(int[] a, int n, int i) {
        while (true) {
            int g = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a[l] > a[g]) g = l;
            if (r < n && a[r] > a[g]) g = r;
            if (g == i) return;
            int t = a[i]; a[i] = a[g]; a[g] = t;
            i = g;
        }
    }
    static void heapSort(int[] a) {
        int n = a.length;
        for (int i = n / 2 - 1; i >= 0; i--) siftDownHS(a, n, i);
        for (int end = n - 1; end > 0; end--) {
            int t = a[0]; a[0] = a[end]; a[end] = t;
            siftDownHS(a, end, 0);
        }
    }
}
```

#### Key Takeaways
- Heap sort is build-heap plus n extract-max operations. It guarantees O(n log n) with O(1) space, unlike quicksort's O(n²) worst case.

[↑ Contents](#contents) · [← Previous](#p327) · [Next →](#p329)

---

<a id="p329"></a>

### 8. K-th Largest element in an array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › Theory and Implementation | Pro | No | [LeetCode](https://leetcode.com/problems/kth-largest-element-in-an-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/k-th-largest-element-in-an-array) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the **k-th largest** element of an unsorted array. "k-th largest" counts duplicates, so it means the k-th element in sorted descending order.

```text
nums = [3, 2, 1, 5, 6, 4], k = 2            ->  5
nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4   ->  4
```

#### Approach 1: Brute Force — sort
Sort the array and return `nums[n − k]`.

**Complexity:** O(n log n) time, O(1) extra space (or O(log n) for the sort's recursion).

**C++**
```cpp
int findKthLargestSort(vector<int> nums, int k) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() - k];
}
```

**Java**
```java
class Solution {
    static int findKthLargestSort(int[] nums, int k) {
        int[] a = nums.clone();
        Arrays.sort(a);
        return a[a.length - k];
    }
}
```

#### Approach 2: Better — min-heap of size k
- **Keep the k largest seen so far** in a **min-heap**. Push each element, and if the size exceeds `k`, pop the smallest.
- **Read off the answer.** At the end the heap holds the k largest values, and its top, the smallest of them, is the k-th largest.

**Complexity:** O(n log k) time, O(k) space.

**C++**
```cpp
int findKthLargestHeap(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;     // min-heap
    for (int x : nums) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();                  // drop the smallest
    }
    return pq.top();
}
```

**Java**
```java
class Solution {
    static int findKthLargestHeap(int[] nums, int k) {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int x : nums) {
            pq.add(x);
            if (pq.size() > k) pq.poll();
        }
        return pq.peek();
    }
}
```

#### Approach 3: Optimal on average — Quickselect
- **Partition around a pivot,** as in quicksort, so that larger elements go to the left. The pivot then lands at its final position `p` in descending order.
- **Recurse into one side only:**
  - if `p == k − 1`, the pivot is the answer;
  - if `p < k − 1`, search the right part; otherwise search the left part.
- **Pick the pivot at random** so the expected cost stays linear.

**Complexity:** O(n) on average, O(n²) in the worst case (unlikely with a random pivot). O(1) extra space.

**C++**
```cpp
int partitionDesc(vector<int>& a, int lo, int hi) {
    int pivotIdx = lo + rand() % (hi - lo + 1);
    swap(a[pivotIdx], a[hi]);
    int pivot = a[hi], store = lo;
    for (int i = lo; i < hi; i++)
        if (a[i] > pivot) swap(a[i], a[store++]);          // larger elements to the left
    swap(a[store], a[hi]);
    return store;
}
int findKthLargest(vector<int> nums, int k) {
    int lo = 0, hi = nums.size() - 1;
    while (true) {
        int p = partitionDesc(nums, lo, hi);
        if (p == k - 1) return nums[p];
        if (p < k - 1) lo = p + 1;
        else hi = p - 1;
    }
}
```

**Java**
```java
class Solution {
    static final Random RNG = new Random();
    static int partitionDesc(int[] a, int lo, int hi) {
        int pivotIdx = lo + RNG.nextInt(hi - lo + 1);
        int t = a[pivotIdx]; a[pivotIdx] = a[hi]; a[hi] = t;
        int pivot = a[hi], store = lo;
        for (int i = lo; i < hi; i++)
            if (a[i] > pivot) { t = a[i]; a[i] = a[store]; a[store] = t; store++; }
        t = a[store]; a[store] = a[hi]; a[hi] = t;
        return store;
    }
    static int findKthLargest(int[] nums, int k) {
        int[] a = nums.clone();
        int lo = 0, hi = a.length - 1;
        while (true) {
            int p = partitionDesc(a, lo, hi);
            if (p == k - 1) return a[p];
            if (p < k - 1) lo = p + 1;
            else hi = p - 1;
        }
    }
}
```

#### Key Takeaways
- k-th largest: use a **min-heap of size k** (smallest at the top). For k-th smallest, use a max-heap of size k.
- Quickselect gives expected O(n).

[↑ Contents](#contents) · [← Previous](#p328) · [Next →](#p330)

---

## FAQs

<a id="p330"></a>

### 9. Kth largest element in a stream of running integers

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/kth-largest-element-in-a-stream/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/kth-largest-element-stream) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Design `KthLargest(k, nums)` with `add(val)`, which adds `val` to the stream and returns the **current k-th largest** element.

```text
KthLargest(3, [4, 5, 8, 2]);  add(3) -> 4;  add(5) -> 5;  add(10) -> 5;  add(9) -> 8;  add(4) -> 8
```

#### Approach 1: Brute Force — keep a sorted list
Insert each value into a sorted container and read the k-th element from the end.

**Complexity:** O(n) per `add` with a sorted vector and insertion. O(n) space.

**C++**
```cpp
class KthLargestBrute {
    int k;
    vector<int> v;                                  // kept sorted
public:
    KthLargestBrute(int k_, vector<int>& nums) : k(k_), v(nums) { sort(v.begin(), v.end()); }
    int add(int val) {
        v.insert(upper_bound(v.begin(), v.end(), val), val);
        return v[v.size() - k];
    }
};
```

**Java**
```java
class KthLargestBrute {
    private final int k;
    private final List<Integer> v = new ArrayList<>();
    KthLargestBrute(int k, int[] nums) {
        this.k = k;
        for (int x : nums) v.add(x);
        Collections.sort(v);
    }
    int add(int val) {
        int pos = Collections.binarySearch(v, val);
        if (pos < 0) pos = -pos - 1;
        v.add(pos, val);
        return v.get(v.size() - k);
    }
}
```

#### Approach 2: Optimal — min-heap of size k
- **The heap holds the k largest values seen so far.** Its top is the k-th largest.
- **On `add`:** push the value. If the size exceeds k, pop the minimum. Return the top.

**Complexity:**
- Construction: O(n log k).
- `add`: O(log k).
- Space: O(k).

**C++**
```cpp
class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;   // k largest so far
public:
    KthLargest(int k_, vector<int>& nums) : k(k_) {
        for (int x : nums) add(x);
    }
    int add(int val) {
        pq.push(val);
        if ((int)pq.size() > k) pq.pop();
        return pq.top();
    }
};
```

**Java**
```java
class KthLargest {
    private final int k;
    private final PriorityQueue<Integer> pq = new PriorityQueue<>();
    KthLargest(int k, int[] nums) {
        this.k = k;
        for (int x : nums) add(x);
    }
    int add(int val) {
        pq.add(val);
        if (pq.size() > k) pq.poll();
        return pq.peek();
    }
}
```

#### Key Takeaways
- For a streaming k-th largest, maintain a size-k min-heap: every update is O(log k).

[↑ Contents](#contents) · [← Previous](#p329) · [Next →](#p331)

---

<a id="p331"></a>

### 10. Sort a K-Sorted Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | — | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Each element of a **k-sorted** array is at most `k` positions away from where it belongs in sorted order. Sort it efficiently.

```text
arr = [6, 5, 3, 2, 8, 10, 9], k = 3   ->  [2, 3, 5, 6, 8, 9, 10]
```

#### Approach 1: Brute Force — ordinary sort
**Complexity:** O(n log n) time.

**C++**
```cpp
void sortKSortedBrute(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());
}
```

**Java**
```java
class Solution {
    static void sortKSortedBrute(int[] arr, int k) {
        Arrays.sort(arr);
    }
}
```

#### Approach 2: Optimal — min-heap of size k + 1
- **The window of candidates.** The element that belongs at index `i` must lie in `arr[i … i+k]`. So keep a min-heap of the next `k + 1` elements: its minimum is exactly the value for position `i`.
- **Slide the window.** Pop that minimum into position `i`, push the next element, and repeat.

**Complexity:** O(n log k) time, O(k) space.

**C++**
```cpp
void sortKSorted(vector<int>& arr, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    int n = arr.size(), idx = 0;
    for (int i = 0; i < n; i++) {
        pq.push(arr[i]);
        if ((int)pq.size() > k) {                 // window of k+1: min belongs at idx
            arr[idx++] = pq.top();
            pq.pop();
        }
    }
    while (!pq.empty()) { arr[idx++] = pq.top(); pq.pop(); }
}
```

**Java**
```java
class Solution {
    static void sortKSorted(int[] arr, int k) {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        int n = arr.length, idx = 0;
        for (int i = 0; i < n; i++) {
            pq.add(arr[i]);
            if (pq.size() > k) arr[idx++] = pq.poll();
        }
        while (!pq.isEmpty()) arr[idx++] = pq.poll();
    }
}
```

#### Key Takeaways
- Bounded displacement means a bounded candidate window, so a heap of size k+1 sorts in O(n log k).

[↑ Contents](#contents) · [← Previous](#p330) · [Next →](#p332)

---

<a id="p332"></a>

### 11. Merge K sorted Lists

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/merge-k-sorted-lists/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/merge-k-sorted-linked-lists) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Merge `k` sorted linked lists into one sorted list.

```text
lists = [[1,4,5], [1,3,4], [2,6]]   ->  [1,1,2,3,4,4,5,6]
```

#### Approach 1: Brute Force — collect every value, sort, rebuild
**Complexity:** O(N log N) time for N total nodes. O(N) space.

**C++**
```cpp
ListNode* mergeKListsBrute(vector<ListNode*>& lists) {
    vector<int> vals;
    for (ListNode* l : lists)
        for (ListNode* p = l; p; p = p->next) vals.push_back(p->val);
    sort(vals.begin(), vals.end());
    ListNode dummy(0), *tail = &dummy;
    for (int v : vals) { tail->next = new ListNode(v); tail = tail->next; }
    return dummy.next;
}
```

**Java**
```java
class Solution {
    static ListNode mergeKListsBrute(ListNode[] lists) {
        List<Integer> vals = new ArrayList<>();
        for (ListNode l : lists)
            for (ListNode p = l; p != null; p = p.next) vals.add(p.val);
        Collections.sort(vals);
        ListNode dummy = new ListNode(0), tail = dummy;
        for (int v : vals) { tail.next = new ListNode(v); tail = tail.next; }
        return dummy.next;
    }
}
```

#### Approach 2: Better — merge the lists one by one
Fold left: `result = merge2(result, lists[i])`. Each merge is the classic two-list merge.

**Complexity:** about O(N·k) time, because the growing result is re-scanned k times. O(1) extra space.

**C++**
```cpp
ListNode* mergeTwo(ListNode* a, ListNode* b) {
    ListNode dummy(0), *t = &dummy;
    while (a && b) {
        if (a->val <= b->val) { t->next = a; a = a->next; }
        else { t->next = b; b = b->next; }
        t = t->next;
    }
    t->next = a ? a : b;
    return dummy.next;
}
ListNode* mergeKListsSeq(vector<ListNode*>& lists) {
    ListNode* res = nullptr;
    for (ListNode* l : lists) res = mergeTwo(res, l);
    return res;
}
```

**Java**
```java
class Solution {
    static ListNode mergeTwo(ListNode a, ListNode b) {
        ListNode dummy = new ListNode(0), t = dummy;
        while (a != null && b != null) {
            if (a.val <= b.val) { t.next = a; a = a.next; }
            else { t.next = b; b = b.next; }
            t = t.next;
        }
        t.next = (a != null) ? a : b;
        return dummy.next;
    }
    static ListNode mergeKListsSeq(ListNode[] lists) {
        ListNode res = null;
        for (ListNode l : lists) res = mergeTwo(res, l);
        return res;
    }
}
```

#### Approach 3: Optimal — min-heap of list heads
- **Start with every head.** Push the head of each non-empty list into a min-heap keyed by value.
- **Repeatedly take the smallest.** Pop the smallest node, append it to the result, and push that node's `next` if it has one.

The heap always holds at most k nodes, one per list.

**Complexity:** O(N log k) time, O(k) space.

**C++**
```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    for (ListNode* l : lists) if (l) pq.push(l);
    ListNode dummy(0), *tail = &dummy;
    while (!pq.empty()) {
        ListNode* node = pq.top(); pq.pop();
        tail->next = node;
        tail = node;
        if (node->next) pq.push(node->next);
    }
    tail->next = nullptr;
    return dummy.next;
}
```

**Java**
```java
class Solution {
    static ListNode mergeKLists(ListNode[] lists) {
        PriorityQueue<ListNode> pq = new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));
        for (ListNode l : lists) if (l != null) pq.add(l);
        ListNode dummy = new ListNode(0), tail = dummy;
        while (!pq.isEmpty()) {
            ListNode node = pq.poll();
            tail.next = node;
            tail = node;
            if (node.next != null) pq.add(node.next);
        }
        tail.next = null;
        return dummy.next;
    }
}
```

#### Key Takeaways
- K-way merge means a min-heap of the current front of each sequence. The same pattern merges k sorted arrays and finds the smallest range covering k lists.

[↑ Contents](#contents) · [← Previous](#p331) · [Next →](#p333)

---

<a id="p333"></a>

### 12. Replace Elements by Their Rank

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/rank-transform-of-an-array/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Replace every element with its **rank**: 1 for the smallest value, with equal values sharing a rank and ranks consecutive.

```text
arr = [40, 10, 20, 30]          ->  [4, 1, 2, 3]
arr = [100, 100, 100]           ->  [1, 1, 1]
arr = [37, 12, 28, 9, 100, 56, 80, 5, 12]  ->  [5, 3, 4, 2, 8, 6, 7, 1, 3]
```

#### Approach 1: Brute Force — count the distinct smaller values
For each element, its rank is 1 + the number of **distinct** values smaller than it.

**Complexity:** O(n²) time, O(n) space for the set of distinct values.

**C++**
```cpp
vector<int> arrayRankBrute(vector<int>& arr) {
    set<int> distinct(arr.begin(), arr.end());
    vector<int> ans;
    for (int x : arr) {
        int rank = 1;
        for (int d : distinct) if (d < x) rank++;
        ans.push_back(rank);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] arrayRankBrute(int[] arr) {
        TreeSet<Integer> distinct = new TreeSet<>();
        for (int x : arr) distinct.add(x);
        int[] ans = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            int rank = 1;
            for (int d : distinct) if (d < arr[i]) rank++;
            ans[i] = rank;
        }
        return ans;
    }
}
```

#### Approach 2: Optimal — min-heap (or sort) + a rank map
- Pop the values in increasing order from a min-heap, or iterate over a sorted copy.
- Give each **new** distinct value the next rank in a hash map, then map every element through it.

**Complexity:** O(n log n) time, O(n) space.

**C++**
```cpp
vector<int> arrayRankTransform(vector<int>& arr) {
    priority_queue<int, vector<int>, greater<int>> pq(arr.begin(), arr.end());
    unordered_map<int, int> rank;
    int r = 1;
    while (!pq.empty()) {
        int x = pq.top(); pq.pop();
        if (!rank.count(x)) rank[x] = r++;           // each distinct value once
    }
    vector<int> ans;
    for (int x : arr) ans.push_back(rank[x]);
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] arrayRankTransform(int[] arr) {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int x : arr) pq.add(x);
        Map<Integer, Integer> rank = new HashMap<>();
        int r = 1;
        while (!pq.isEmpty()) {
            int x = pq.poll();
            if (!rank.containsKey(x)) rank.put(x, r++);
        }
        int[] ans = new int[arr.length];
        for (int i = 0; i < arr.length; i++) ans[i] = rank.get(arr[i]);
        return ans;
    }
}
```

#### Key Takeaways
- Ranking is coordinate compression: sort (or heap-pop) the distinct values and number them.

[↑ Contents](#contents) · [← Previous](#p332) · [Next →](#p334)

---

<a id="p334"></a>

### 13. Task Scheduler

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/task-scheduler/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/task-scheduler) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Tasks are labelled by letters. Each takes one unit of time. Two executions of the **same** task must be at least `n` units apart, and the CPU may idle. Return the **minimum total time** to finish all tasks.

```text
tasks = [A,A,A,B,B,B], n = 2   ->  8   (A B idle A B idle A B)
tasks = [A,C,A,B,D,B], n = 1   ->  6
tasks = [A,A,A,B,B,B], n = 3   ->  10
```

#### Approach 1: Max-heap simulation (greedy by remaining count)
- **Each cycle is `n + 1` slots.** Fill it with the **most frequent** remaining tasks, one each, popped from a max-heap of counts.
- **Return the leftovers.** Push back the decremented counts that are still positive.
- **Count the time.** If the heap is now empty, the last cycle took only as many slots as tasks were run. Otherwise it took the full `n + 1`.

**Complexity:** O(T log 26), which is effectively O(T) for T tasks. O(26) space.

**C++**
```cpp
int leastIntervalHeap(vector<char>& tasks, int n) {
    int freq[26] = {0};
    for (char c : tasks) freq[c - 'A']++;
    priority_queue<int> pq;
    for (int f : freq) if (f) pq.push(f);
    int time = 0;
    while (!pq.empty()) {
        vector<int> tmp;
        int cycle = n + 1, ran = 0;
        while (cycle-- && !pq.empty()) {             // run up to n+1 distinct tasks
            tmp.push_back(pq.top() - 1);
            pq.pop();
            ran++;
        }
        for (int c : tmp) if (c > 0) pq.push(c);
        time += pq.empty() ? ran : n + 1;            // last cycle needs no idling
    }
    return time;
}
```

**Java**
```java
class Solution {
    static int leastIntervalHeap(char[] tasks, int n) {
        int[] freq = new int[26];
        for (char c : tasks) freq[c - 'A']++;
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
        for (int f : freq) if (f > 0) pq.add(f);
        int time = 0;
        while (!pq.isEmpty()) {
            List<Integer> tmp = new ArrayList<>();
            int cycle = n + 1, ran = 0;
            while (cycle-- > 0 && !pq.isEmpty()) {
                tmp.add(pq.poll() - 1);
                ran++;
            }
            for (int c : tmp) if (c > 0) pq.add(c);
            time += pq.isEmpty() ? ran : n + 1;
        }
        return time;
    }
}
```

#### Approach 2: Optimal — counting formula
- **Build the frame around the busiest task.** Let `maxF` be the highest frequency, shared by `cntMax` tasks. Laying out the busiest task gives `maxF − 1` full gaps of length `n + 1`, then a final row containing the `cntMax` tasks: `(maxF − 1)·(n + 1) + cntMax`.
- **Other tasks fill the idle slots.** If there are more tasks than slots, no idling is needed at all, and the answer is just `len(tasks)`.

  **answer = max(len(tasks), (maxF − 1)·(n + 1) + cntMax)**

**Complexity:** O(T) time, O(26) space.

**C++**
```cpp
int leastInterval(vector<char>& tasks, int n) {
    int freq[26] = {0};
    for (char c : tasks) freq[c - 'A']++;
    int maxF = *max_element(freq, freq + 26);
    int cntMax = count(freq, freq + 26, maxF);
    return max((int)tasks.size(), (maxF - 1) * (n + 1) + cntMax);
}
```

**Java**
```java
class Solution {
    static int leastInterval(char[] tasks, int n) {
        int[] freq = new int[26];
        for (char c : tasks) freq[c - 'A']++;
        int maxF = 0, cntMax = 0;
        for (int f : freq) maxF = Math.max(maxF, f);
        for (int f : freq) if (f == maxF) cntMax++;
        return Math.max(tasks.length, (maxF - 1) * (n + 1) + cntMax);
    }
}
```

#### Key Takeaways
- Greedy: always run the most frequent available task (a max-heap). The arrangement it produces collapses into a closed-form count around the most frequent task.

[↑ Contents](#contents) · [← Previous](#p333) · [Next →](#p335)

---

<a id="p335"></a>

### 14. Hand of Straights

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/hand-of-straights/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given card values `hand` and a group size `groupSize`, can all the cards be split into groups of `groupSize` **consecutive** values?

```text
hand = [1,2,3,6,2,3,4,7,8], groupSize = 3   ->  true   ([1,2,3], [2,3,4], [6,7,8])
hand = [1,2,3,4,5],         groupSize = 4   ->  false
```

#### Intuition — the smallest card must start a group
The smallest remaining card can't be the middle or the end of any group, because nothing smaller remains. So it **must start** a group: `x, x+1, …, x+groupSize−1`, and all of those must be available. Repeat with the next smallest card.

#### Approach 1: Ordered map of counts
- Count every card in an ordered map.
- Repeatedly take the smallest key `x` with count `c`. Remove `c` copies of each value `x … x+groupSize−1`. If any of them has fewer than `c` copies, return `false`.

**Complexity:** O(n log n) time, O(n) space.

**C++**
```cpp
bool isNStraightHandMap(vector<int>& hand, int groupSize) {
    if (hand.size() % groupSize) return false;
    map<int, int> cnt;
    for (int x : hand) cnt[x]++;
    while (!cnt.empty()) {
        int start = cnt.begin()->first, c = cnt.begin()->second;
        for (int v = start; v < start + groupSize; v++) {
            auto it = cnt.find(v);
            if (it == cnt.end() || it->second < c) return false;
            if ((it->second -= c) == 0) cnt.erase(it);
        }
    }
    return true;
}
```

**Java**
```java
class Solution {
    static boolean isNStraightHandMap(int[] hand, int groupSize) {
        if (hand.length % groupSize != 0) return false;
        TreeMap<Integer, Integer> cnt = new TreeMap<>();
        for (int x : hand) cnt.merge(x, 1, Integer::sum);
        while (!cnt.isEmpty()) {
            int start = cnt.firstKey(), c = cnt.get(start);
            for (int v = start; v < start + groupSize; v++) {
                Integer have = cnt.get(v);
                if (have == null || have < c) return false;
                if (have == c) cnt.remove(v); else cnt.put(v, have - c);
            }
        }
        return true;
    }
}
```

#### Approach 2: Min-heap of distinct values + count map
- Put the distinct values in a min-heap and keep their counts in a hash map.
- The heap top is the smallest card. Build a group from it, decrementing counts.
- When a value's count reaches 0, it **must** be the heap's top. If it isn't, a smaller card is still waiting and can never complete a group, so return `false`. Then pop it.

**Complexity:** O(n log n) time, O(n) space.

**C++**
```cpp
bool isNStraightHand(vector<int>& hand, int groupSize) {
    if (hand.size() % groupSize) return false;
    unordered_map<int, int> cnt;
    for (int x : hand) cnt[x]++;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto& [v, c] : cnt) pq.push(v);
    while (!pq.empty()) {
        int first = pq.top();
        for (int v = first; v < first + groupSize; v++) {
            if (!cnt.count(v) || cnt[v] == 0) return false;
            if (--cnt[v] == 0) {
                if (v != pq.top()) return false;        // a smaller card is left stranded
                pq.pop();
            }
        }
    }
    return true;
}
```

**Java**
```java
class Solution {
    static boolean isNStraightHand(int[] hand, int groupSize) {
        if (hand.length % groupSize != 0) return false;
        Map<Integer, Integer> cnt = new HashMap<>();
        for (int x : hand) cnt.merge(x, 1, Integer::sum);
        PriorityQueue<Integer> pq = new PriorityQueue<>(cnt.keySet());
        while (!pq.isEmpty()) {
            int first = pq.peek();
            for (int v = first; v < first + groupSize; v++) {
                Integer c = cnt.get(v);
                if (c == null || c == 0) return false;
                cnt.put(v, c - 1);
                if (c - 1 == 0) {
                    if (v != pq.peek()) return false;
                    pq.poll();
                }
            }
        }
        return true;
    }
}
```

#### Key Takeaways
- Greedy from the smallest element: it must start a group. An ordered structure (map or heap) supplies "smallest remaining" quickly.

[↑ Contents](#contents) · [← Previous](#p334) · [Next →](#p336)

---

<a id="p336"></a>

### 15. Design Twitter

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/design-twitter/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Design a simplified Twitter:
- `postTweet(userId, tweetId)`;
- `getNewsFeed(userId)`, which returns the **10 most recent** tweet ids from the user and the users they follow, newest first;
- `follow(followerId, followeeId)` and `unfollow(followerId, followeeId)`.

```text
postTweet(1,5); getNewsFeed(1) -> [5]; follow(1,2); postTweet(2,6); getNewsFeed(1) -> [6,5];
unfollow(1,2); getNewsFeed(1) -> [5]
```

#### Approach: Per-user tweet lists + follow sets + a heap merge
- **Store:**
  - a global `time` counter;
  - `tweets[user]`, a list of `(time, tweetId)` in posting order;
  - `following[user]`, a set of followee ids.
- **`getNewsFeed(u)`:**
  - **Collect sources.** Gather `u` and everyone `u` follows. Each has a list sorted by time, newest at the end.
  - **Seed the heap.** Push each source's newest tweet into a **max-heap** keyed by time, storing `(time, tweetId, user, index)`.
  - **Pop up to 10 times.** Each pop is the next newest tweet overall. After a pop, push the previous tweet from the same user, if there is one.

  This is "merge k sorted lists", stopping after 10.
- **`follow` / `unfollow`:** set insert and erase. Ignore self-follows.

**Complexity:**
- `postTweet`, `follow`, `unfollow`: O(1).
- `getNewsFeed`: O(F + 10 log F) for F followees.
- Space: O(users + tweets + follows).

**C++**
```cpp
class Twitter {
    int timeStamp = 0;
    unordered_map<int, vector<pair<int, int>>> tweets;    // user -> {time, tweetId}
    unordered_map<int, unordered_set<int>> following;
public:
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timeStamp++, tweetId});
    }
    vector<int> getNewsFeed(int userId) {
        // {time, tweetId, user, index in that user's list}
        priority_queue<tuple<int, int, int, int>> pq;
        auto addSource = [&](int u) {
            auto it = tweets.find(u);
            if (it != tweets.end() && !it->second.empty()) {
                int idx = it->second.size() - 1;
                pq.push({it->second[idx].first, it->second[idx].second, u, idx});
            }
        };
        addSource(userId);
        for (int f : following[userId]) if (f != userId) addSource(f);
        vector<int> feed;
        while (!pq.empty() && feed.size() < 10) {
            auto [t, id, u, idx] = pq.top(); pq.pop();
            feed.push_back(id);
            if (idx > 0) {
                auto& lst = tweets[u];
                pq.push({lst[idx - 1].first, lst[idx - 1].second, u, idx - 1});
            }
        }
        return feed;
    }
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) following[followerId].insert(followeeId);
    }
    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};
```

**Java**
```java
class Twitter {
    private int timeStamp = 0;
    private final Map<Integer, List<int[]>> tweets = new HashMap<>();      // {time, tweetId}
    private final Map<Integer, Set<Integer>> following = new HashMap<>();
    void postTweet(int userId, int tweetId) {
        tweets.computeIfAbsent(userId, k -> new ArrayList<>()).add(new int[]{timeStamp++, tweetId});
    }
    List<Integer> getNewsFeed(int userId) {
        // {time, tweetId, user, index}; max-heap by time
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(b[0], a[0]));
        List<Integer> sources = new ArrayList<>();
        sources.add(userId);
        for (int f : following.getOrDefault(userId, Collections.emptySet())) if (f != userId) sources.add(f);
        for (int u : sources) {
            List<int[]> lst = tweets.get(u);
            if (lst != null && !lst.isEmpty()) {
                int idx = lst.size() - 1;
                pq.add(new int[]{lst.get(idx)[0], lst.get(idx)[1], u, idx});
            }
        }
        List<Integer> feed = new ArrayList<>();
        while (!pq.isEmpty() && feed.size() < 10) {
            int[] top = pq.poll();
            feed.add(top[1]);
            if (top[3] > 0) {
                int[] prev = tweets.get(top[2]).get(top[3] - 1);
                pq.add(new int[]{prev[0], prev[1], top[2], top[3] - 1});
            }
        }
        return feed;
    }
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) following.computeIfAbsent(followerId, k -> new HashSet<>()).add(followeeId);
    }
    void unfollow(int followerId, int followeeId) {
        Set<Integer> s = following.get(followerId);
        if (s != null) s.remove(followeeId);
    }
}
```

#### Edge Cases & Pitfalls
- **The user's own tweets** belong in the feed.
- **Unfollowing someone you don't follow** is a no-op.
- **Use a global clock**, not tweet ids, for ordering. Ids aren't chronological.

#### Key Takeaways
- A news feed is a k-way merge of per-user time-sorted lists, cut off at 10 with a heap.

[↑ Contents](#contents) · [← Previous](#p335) · [Next →](#p337)

---

<a id="p337"></a>

### 16. Minimum Cost to Connect Sticks

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Core | Yes | [LeetCode](https://leetcode.com/problems/minimum-cost-to-connect-sticks/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Connecting two sticks of lengths `x` and `y` costs `x + y` and produces one stick of length `x + y`. Return the **minimum total cost** to connect all sticks into one.

```text
sticks = [2, 4, 3]       ->  14   (2+3 = 5, cost 5; 5+4 = 9, cost 9; total 14)
sticks = [1, 8, 3, 5]    ->  30
sticks = [5]             ->  0
```

#### Intuition — Huffman-style greedy
Every stick's length is added to the cost once **for each merge it takes part in**. So the longest sticks should be merged as few times as possible, which means the **two shortest sticks should always be merged first**.

#### Approach 1: Brute Force — sort and re-sort after each merge
Repeatedly sort, merge the two smallest sticks, and put the result back.

**Complexity:** O(n² log n) time, O(n) space.

**C++**
```cpp
int connectSticksBrute(vector<int> sticks) {
    int cost = 0;
    while (sticks.size() > 1) {
        sort(sticks.begin(), sticks.end());
        int s = sticks[0] + sticks[1];
        cost += s;
        sticks.erase(sticks.begin(), sticks.begin() + 2);
        sticks.push_back(s);
    }
    return cost;
}
```

**Java**
```java
class Solution {
    static int connectSticksBrute(int[] sticksArr) {
        List<Integer> sticks = new ArrayList<>();
        for (int x : sticksArr) sticks.add(x);
        int cost = 0;
        while (sticks.size() > 1) {
            Collections.sort(sticks);
            int s = sticks.get(0) + sticks.get(1);
            cost += s;
            sticks.remove(0);
            sticks.remove(0);
            sticks.add(s);
        }
        return cost;
    }
}
```

#### Approach 2: Optimal — min-heap
Push every stick into a min-heap. While more than one remains, pop the two smallest, add their sum to the cost, and push the sum back.

**Complexity:** O(n log n) time, O(n) space.

**C++**
```cpp
int connectSticks(vector<int>& sticks) {
    priority_queue<int, vector<int>, greater<int>> pq(sticks.begin(), sticks.end());
    int cost = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        cost += a + b;
        pq.push(a + b);
    }
    return cost;
}
```

**Java**
```java
class Solution {
    static int connectSticks(int[] sticks) {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int x : sticks) pq.add(x);
        int cost = 0;
        while (pq.size() > 1) {
            int a = pq.poll(), b = pq.poll();
            cost += a + b;
            pq.add(a + b);
        }
        return cost;
    }
}
```

#### Key Takeaways
- "Repeatedly combine the two smallest" is Huffman coding and optimal merge patterns, and a min-heap makes it O(n log n). The cost can overflow 32 bits for large inputs; use `long long` there.

[↑ Contents](#contents) · [← Previous](#p336) · [Next →](#p338)

---

<a id="p338"></a>

### 17. Maximum Sum Combination

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Core | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given two arrays `A` and `B` of size `n` and an integer `K`, return the **K largest sums** `A[i] + B[j]` over all pairs, in decreasing order. Pairs are distinct by index.

```text
A = [3, 2], B = [1, 4], K = 2            ->  [7, 6]
A = [1, 4, 2, 3], B = [2, 5, 1, 6], K = 4 ->  [10, 9, 9, 8]
```

#### Approach 1: Brute Force — all n² sums
Generate every sum, sort descending, and take K.

**Complexity:** O(n² log n) time, O(n²) space.

**C++**
```cpp
vector<int> maxCombinationsBrute(vector<int>& A, vector<int>& B, int K) {
    vector<int> sums;
    for (int a : A) for (int b : B) sums.push_back(a + b);
    sort(sums.rbegin(), sums.rend());
    return vector<int>(sums.begin(), sums.begin() + K);
}
```

**Java**
```java
class Solution {
    static List<Integer> maxCombinationsBrute(int[] A, int[] B, int K) {
        List<Integer> sums = new ArrayList<>();
        for (int a : A) for (int b : B) sums.add(a + b);
        sums.sort(Collections.reverseOrder());
        return new ArrayList<>(sums.subList(0, K));
    }
}
```

#### Approach 2: Optimal — sort descending + max-heap over the index grid
- **Sort both arrays in descending order.** The largest sum is `A[0] + B[0]`.
- **Neighbours are the next candidates.** If `(i, j)` has been taken, the next candidates from it are `(i+1, j)` and `(i, j+1)`. Picture an n × n grid whose values decrease to the right and downwards.
- **Run a best-first search:**
  - keep a max-heap of `(sum, i, j)` and a `visited` set of index pairs;
  - pop the top K times;
  - after each pop, push the unvisited neighbours.

**Complexity:** O(n log n + K log K) time, O(K) space.

**C++**
```cpp
vector<int> maxCombinations(vector<int> A, vector<int> B, int K) {
    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());
    int n = A.size();
    priority_queue<tuple<int, int, int>> pq;               // {sum, i, j}
    set<pair<int, int>> visited;
    pq.push({A[0] + B[0], 0, 0});
    visited.insert({0, 0});
    vector<int> ans;
    while ((int)ans.size() < K && !pq.empty()) {
        auto [s, i, j] = pq.top(); pq.pop();
        ans.push_back(s);
        if (i + 1 < n && !visited.count({i + 1, j})) { pq.push({A[i + 1] + B[j], i + 1, j}); visited.insert({i + 1, j}); }
        if (j + 1 < n && !visited.count({i, j + 1})) { pq.push({A[i] + B[j + 1], i, j + 1}); visited.insert({i, j + 1}); }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> maxCombinations(int[] A0, int[] B0, int K) {
        Integer[] A = Arrays.stream(A0).boxed().sorted(Collections.reverseOrder()).toArray(Integer[]::new);
        Integer[] B = Arrays.stream(B0).boxed().sorted(Collections.reverseOrder()).toArray(Integer[]::new);
        int n = A.length;
        PriorityQueue<int[]> pq = new PriorityQueue<>((x, y) -> Integer.compare(y[0], x[0]));   // {sum, i, j}
        Set<Long> visited = new HashSet<>();
        pq.add(new int[]{A[0] + B[0], 0, 0});
        visited.add(0L);
        List<Integer> ans = new ArrayList<>();
        while (ans.size() < K && !pq.isEmpty()) {
            int[] top = pq.poll();
            int i = top[1], j = top[2];
            ans.add(top[0]);
            if (i + 1 < n && visited.add((long) (i + 1) * n + j)) pq.add(new int[]{A[i + 1] + B[j], i + 1, j});
            if (j + 1 < n && visited.add((long) i * n + j + 1)) pq.add(new int[]{A[i] + B[j + 1], i, j + 1});
        }
        return ans;
    }
}
```

#### Key Takeaways
- Top-K over a sorted 2-D grid is best-first search with a heap plus a visited set. It's the same idea as "k-th smallest in a sorted matrix" and "k pairs with the smallest sums".

[↑ Contents](#contents) · [← Previous](#p337) · [Next →](#p339)

---

<a id="p339"></a>

### 18. Find Median from Data Stream

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/find-median-from-data-stream/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-median-data-stream) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Design `MedianFinder` with:
- `addNum(num)`;
- `findMedian()`, which returns the median of all numbers added so far. For an even count, it's the mean of the two middle values.

```text
addNum(1); addNum(2); findMedian() -> 1.5; addNum(3); findMedian() -> 2.0
```

#### Approach 1: Brute Force — keep a sorted list
Insert each number into a sorted vector (binary search, then shift). The median is read from the middle.

**Complexity:** O(n) per `addNum`, O(1) per `findMedian`. O(n) space.

**C++**
```cpp
class MedianFinderBrute {
    vector<int> v;
public:
    void addNum(int num) { v.insert(upper_bound(v.begin(), v.end(), num), num); }
    double findMedian() {
        int n = v.size();
        return n % 2 ? v[n / 2] : (v[n / 2 - 1] + (double)v[n / 2]) / 2.0;
    }
};
```

**Java**
```java
class MedianFinderBrute {
    private final List<Integer> v = new ArrayList<>();
    void addNum(int num) {
        int pos = Collections.binarySearch(v, num);
        if (pos < 0) pos = -pos - 1;
        v.add(pos, num);
    }
    double findMedian() {
        int n = v.size();
        return n % 2 == 1 ? v.get(n / 2) : (v.get(n / 2 - 1) + (double) v.get(n / 2)) / 2.0;
    }
}
```

#### Approach 2: Optimal — two heaps
- **Split the numbers in half:**
  - `lo` is a **max-heap** holding the smaller half;
  - `hi` is a **min-heap** holding the larger half.
- **Keep the halves balanced:** `lo.size() == hi.size()` or `lo.size() == hi.size() + 1`.
- **`addNum(x)`:**
  1. push `x` into `lo`;
  2. move `lo`'s top into `hi`, which keeps every value in `lo` ≤ every value in `hi`;
  3. if `hi` becomes larger than `lo`, move `hi`'s top back to `lo`.
- **`findMedian()`:** `lo.top()` if the sizes differ, otherwise the mean of the two tops.

**Complexity:** O(log n) per `addNum`, O(1) per `findMedian`. O(n) space.

**C++**
```cpp
class MedianFinder {
    priority_queue<int> lo;                                   // max-heap: smaller half
    priority_queue<int, vector<int>, greater<int>> hi;        // min-heap: larger half
public:
    void addNum(int num) {
        lo.push(num);
        hi.push(lo.top()); lo.pop();                          // keep lo <= hi
        if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }   // rebalance
    }
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + (double)hi.top()) / 2.0;
    }
};
```

**Java**
```java
class MedianFinder {
    private final PriorityQueue<Integer> lo = new PriorityQueue<>(Collections.reverseOrder());
    private final PriorityQueue<Integer> hi = new PriorityQueue<>();
    void addNum(int num) {
        lo.add(num);
        hi.add(lo.poll());
        if (hi.size() > lo.size()) lo.add(hi.poll());
    }
    double findMedian() {
        if (lo.size() > hi.size()) return lo.peek();
        return (lo.peek() + (double) hi.peek()) / 2.0;
    }
}
```

#### Edge Cases & Pitfalls
- **Compute the mean in floating point** (or 64-bit). `INT_MAX + INT_MAX` overflows an int.

#### Key Takeaways
- Running median: a max-heap of the lower half and a min-heap of the upper half, kept balanced. The median sits at the tops.

[↑ Contents](#contents) · [← Previous](#p338) · [Next →](#p340)

---

<a id="p340"></a>

### 19. Top K Frequent Elements

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Heaps › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/top-k-frequent-elements/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/top-k-frequent-elements) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the `k` most frequent elements, in any order.

```text
nums = [1,1,1,2,2,3], k = 2   ->  [1, 2]
nums = [1], k = 1             ->  [1]
```

#### Approach 1: Brute Force — count, then sort by frequency
**Complexity:** O(n + m log m) time for m distinct values. O(m) space.

**C++**
```cpp
vector<int> topKFrequentSort(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
    vector<pair<int, int>> v(freq.begin(), freq.end());          // {value, count}
    sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.second > b.second; });
    vector<int> ans;
    for (int i = 0; i < k; i++) ans.push_back(v[i].first);
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] topKFrequentSort(int[] nums, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int x : nums) freq.merge(x, 1, Integer::sum);
        List<Map.Entry<Integer, Integer>> v = new ArrayList<>(freq.entrySet());
        v.sort((a, b) -> Integer.compare(b.getValue(), a.getValue()));
        int[] ans = new int[k];
        for (int i = 0; i < k; i++) ans[i] = v.get(i).getKey();
        return ans;
    }
}
```

#### Approach 2: Better — min-heap of size k on frequency
Push `(count, value)` pairs into a min-heap and pop whenever its size exceeds k. What remains are the k most frequent.

**Complexity:** O(n + m log k) time, O(m + k) space.

**C++**
```cpp
vector<int> topKFrequentHeap(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;   // {count, value}
    for (auto& [v, c] : freq) {
        pq.push({c, v});
        if ((int)pq.size() > k) pq.pop();
    }
    vector<int> ans;
    while (!pq.empty()) { ans.push_back(pq.top().second); pq.pop(); }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] topKFrequentHeap(int[] nums, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int x : nums) freq.merge(x, 1, Integer::sum);
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));   // {count, value}
        for (Map.Entry<Integer, Integer> e : freq.entrySet()) {
            pq.add(new int[]{e.getValue(), e.getKey()});
            if (pq.size() > k) pq.poll();
        }
        int[] ans = new int[k];
        for (int i = 0; i < k; i++) ans[i] = pq.poll()[1];
        return ans;
    }
}
```

#### Approach 3: Optimal — bucket sort by frequency
Frequencies lie in `1 … n`. Put each value into `bucket[freq]`, then read the buckets from `n` down until k values are collected.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
    int n = nums.size();
    vector<vector<int>> bucket(n + 1);
    for (auto& [v, c] : freq) bucket[c].push_back(v);
    vector<int> ans;
    for (int c = n; c >= 1 && (int)ans.size() < k; c--)
        for (int v : bucket[c]) {
            ans.push_back(v);
            if ((int)ans.size() == k) break;
        }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int x : nums) freq.merge(x, 1, Integer::sum);
        int n = nums.length;
        List<List<Integer>> bucket = new ArrayList<>();
        for (int i = 0; i <= n; i++) bucket.add(new ArrayList<>());
        for (Map.Entry<Integer, Integer> e : freq.entrySet()) bucket.get(e.getValue()).add(e.getKey());
        int[] ans = new int[k];
        int idx = 0;
        for (int c = n; c >= 1 && idx < k; c--)
            for (int v : bucket.get(c)) {
                ans[idx++] = v;
                if (idx == k) break;
            }
        return ans;
    }
}
```

#### Key Takeaways
- For top-k by some key, a size-k heap gives O(n log k). When the keys are small integers, such as frequencies, bucket sort gives O(n).

[↑ Contents](#contents) · [← Previous](#p339)

---
