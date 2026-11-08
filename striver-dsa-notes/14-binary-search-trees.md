# Binary Search Trees — Striver's A2Z DSA Sheet Notes

Section 14 of 20 · 14 problems · 13 with video, 1 without · [All sections](00-index.md)

[← Binary Trees](13-binary-trees.md) | [Heaps →](15-heaps.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Theory and Basics**

1. [Search in BST](#p308) — Basic
2. [Floor and Ceil in a BST](#p309) — Core
3. [Minimum and Maximum in BST](#p310) — — · *no video*

**Medium**

4. [Insert a given node in BST](#p311) — Core
5. [Delete a node in BST](#p312) — Core · *video not transcribed*
6. [Kth Smallest and Largest element in BST](#p313) — Core
7. [Check if a tree is a BST or not](#p314) — Core · *video not transcribed*
8. [LCA in BST](#p315) — Core
9. [Construct a BST from a preorder traversal](#p316) — Core
10. [Inorder successor and predecessor in BST](#p317) — Core

**FAQs**

11. [BST iterator](#p318) — Core
12. [Two sum in BST](#p319) — Core
13. [Correct BST with two nodes swapped](#p320) — Pro
14. [Largest BST in Binary Tree](#p321) — Pro

---

## Theory and Basics

<a id="p308"></a>

### 1. Search in BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Theory and Basics | Basic | No | [LeetCode](https://leetcode.com/problems/search-in-a-binary-search-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/search-in-a-binary-search-tree) | [Watch](https://youtu.be/KcNt6v_56cc) |

> **BST property** (used throughout this section): for every node, all values in the **left** subtree are **smaller** and all values in the **right** subtree are **greater**. Duplicates are usually not allowed. Inorder traversal of a BST is **sorted**. Search, insert and delete take O(h), which is O(log n) when the tree is balanced.

#### Problem Statement
Return the node whose value is `val` in a BST, or null if it's absent.

```text
        4
       / \
      2   7        val = 2  ->  subtree rooted at 2   (val = 5 -> null)
     / \
    1   3
```

#### Approach: Walk down using the BST property (as in the video)
Start at the root. If `val < node.val` go left, if `val > node.val` go right, and if they're equal you've found it. Each step discards a whole subtree, just like binary search.

**Complexity:** O(h) time, i.e. O(log n) when balanced and O(n) when skewed. O(1) space for the iterative version.

**C++**
```cpp
TreeNode* searchBST(TreeNode* root, int val) {
    while (root != nullptr && root->val != val)
        root = (val < root->val) ? root->left : root->right;
    return root;
}
```

**Java**
```java
class Solution {
    static TreeNode searchBST(TreeNode root, int val) {
        while (root != null && root.val != val)
            root = (val < root.val) ? root.left : root.right;
        return root;
    }
}
```

#### Key Takeaways
- BST search is binary search on a tree: compare, then go left or right.

[↑ Contents](#contents) · [Next →](#p309)

---

<a id="p309"></a>

### 2. Floor and Ceil in a BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Theory and Basics | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/floor-and-ceil-in-a-bst) | [Watch](https://youtu.be/xm_W1ub-K-w) |

#### Problem Statement
For a BST and a `key`:
- **floor:** the largest value `≤ key`;
- **ceil:** the smallest value `≥ key`.

Return −1 if none exists.

```text
            10
           /  \
          5    13
         / \   / \
        3   6 11  14
       / \   \
      2   4   9        key = 8 -> floor 6, ceil 9;   key = 11 -> floor 11, ceil 11
```

#### Approach: One downward walk, recording candidates (as in the video)
**Ceil:**
- If `node.val == key`, it's the answer.
- If `node.val > key`, it's a **candidate** (`ceil = node.val`), and something smaller but still ≥ key may lie to the **left**. Go left.
- Otherwise go right.

**Floor** is the mirror image:
- If `node.val ≤ key`, it's a candidate. Record it and go right.
- Otherwise go left.

**Complexity:** O(h) time, O(1) space.

**C++**
```cpp
int findCeil(TreeNode* root, int key) {
    int ceil = -1;
    while (root) {
        if (root->val == key) return key;
        if (root->val > key) { ceil = root->val; root = root->left; }
        else root = root->right;
    }
    return ceil;
}
int findFloor(TreeNode* root, int key) {
    int floor = -1;
    while (root) {
        if (root->val == key) return key;
        if (root->val < key) { floor = root->val; root = root->right; }
        else root = root->left;
    }
    return floor;
}
```

**Java**
```java
class Solution {
    static int findCeil(TreeNode root, int key) {
        int ceil = -1;
        while (root != null) {
            if (root.val == key) return key;
            if (root.val > key) { ceil = root.val; root = root.left; }
            else root = root.right;
        }
        return ceil;
    }
    static int findFloor(TreeNode root, int key) {
        int floor = -1;
        while (root != null) {
            if (root.val == key) return key;
            if (root.val < key) { floor = root.val; root = root.right; }
            else root = root.left;
        }
        return floor;
    }
}
```

#### Key Takeaways
- Floor and ceil are the BST analogue of lower bound in a sorted array: record the candidate, then move towards a tighter one.

[↑ Contents](#contents) · [← Previous](#p308) · [Next →](#p310)

---

<a id="p310"></a>

### 3. Minimum and Maximum in BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Theory and Basics | — | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the **minimum** and **maximum** values in a BST.

```text
        8
       / \
      5   12
     / \    \
    2   6    15        ->  min 2, max 15
```

#### Approach 1: Brute Force — traverse every node
This works for any binary tree but ignores the BST property.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
void minMaxAll(TreeNode* node, int& mn, int& mx) {
    if (node == nullptr) return;
    mn = min(mn, node->val);
    mx = max(mx, node->val);
    minMaxAll(node->left, mn, mx);
    minMaxAll(node->right, mn, mx);
}
```

**Java**
```java
class Solution {
    static int[] minMaxAll(TreeNode root) {        // {min, max}
        int[] res = {Integer.MAX_VALUE, Integer.MIN_VALUE};
        Deque<TreeNode> st = new ArrayDeque<>();
        if (root != null) st.push(root);
        while (!st.isEmpty()) {
            TreeNode n = st.pop();
            res[0] = Math.min(res[0], n.val);
            res[1] = Math.max(res[1], n.val);
            if (n.left != null) st.push(n.left);
            if (n.right != null) st.push(n.right);
        }
        return res;
    }
}
```

#### Approach 2: Optimal — walk the left and right spines
- The **minimum** is the **left-most** node: keep going left.
- The **maximum** is the **right-most** node: keep going right.

**Complexity:** O(h) time, O(1) space.

**C++**
```cpp
int minValue(TreeNode* root) {
    if (root == nullptr) return -1;
    while (root->left) root = root->left;
    return root->val;
}
int maxValue(TreeNode* root) {
    if (root == nullptr) return -1;
    while (root->right) root = root->right;
    return root->val;
}
```

**Java**
```java
class Solution {
    static int minValue(TreeNode root) {
        if (root == null) return -1;
        while (root.left != null) root = root.left;
        return root.val;
    }
    static int maxValue(TreeNode root) {
        if (root == null) return -1;
        while (root.right != null) root = root.right;
        return root.val;
    }
}
```

#### Key Takeaways
- In a BST, min and max sit at the ends of the left and right spines. You never need a full traversal.

[↑ Contents](#contents) · [← Previous](#p309) · [Next →](#p311)

---

## Medium

<a id="p311"></a>

### 4. Insert a given node in BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Medium | Core | No | [LeetCode](https://leetcode.com/problems/insert-into-a-binary-search-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/insert-into-a-binary-search-tree) | [Watch](https://youtu.be/FiFiNvM29ps) |

#### Problem Statement
Insert `val`, which isn't already present, into a BST and return the root. Any valid BST is accepted.

```text
        4                       4
       / \      insert 5       / \
      2   7       ->          2   7
     / \                     / \  /
    1   3                   1  3 5
```

#### Approach: Walk to the correct null slot and attach a new leaf (as in the video)
Insert as a **leaf**; there's no need to restructure.
- Go left if `val < node.val`, right otherwise.
- When the next step would be null, attach `new Node(val)` there.

**Complexity:** O(h) time, O(1) space.

**C++**
```cpp
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == nullptr) return new TreeNode(val);
    TreeNode* cur = root;
    while (true) {
        if (val < cur->val) {
            if (cur->left) cur = cur->left;
            else { cur->left = new TreeNode(val); break; }
        } else {
            if (cur->right) cur = cur->right;
            else { cur->right = new TreeNode(val); break; }
        }
    }
    return root;
}
```

**Java**
```java
class Solution {
    static TreeNode insertIntoBST(TreeNode root, int val) {
        if (root == null) return new TreeNode(val);
        TreeNode cur = root;
        while (true) {
            if (val < cur.val) {
                if (cur.left != null) cur = cur.left;
                else { cur.left = new TreeNode(val); break; }
            } else {
                if (cur.right != null) cur = cur.right;
                else { cur.right = new TreeNode(val); break; }
            }
        }
        return root;
    }
}
```

#### Key Takeaways
- Insertion is search followed by attaching a leaf at the first null.

[↑ Contents](#contents) · [← Previous](#p310) · [Next →](#p312)

---

<a id="p312"></a>

### 5. Delete a node in BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Medium | Core | No | [LeetCode](https://leetcode.com/problems/delete-node-in-a-bst/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/delete-node-in-a-bst) | [Watch](https://youtu.be/kouxiP_H5WE) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Delete the node with value `key` from a BST, if it's present, and return the (possibly new) root.

```text
        5                          5
       / \       delete 3         / \
      3   6        ->            4   6
     / \   \                    /     \
    2   4   7                  2       7
```

#### Approach: Find the node, then splice its subtrees
**Find the node and its parent** with a normal BST walk.

**Replace the node by `helper(node)`:**
- if `node.left` is null, return `node.right`;
- if `node.right` is null, return `node.left`;
- with **two** children, attach the right subtree to the **right-most node of the left subtree** (the node's inorder predecessor). Every value in the right subtree is larger than everything in the left subtree, so it fits there. Then return `node.left`.

**Re-link the parent**, or return the result as the new root if the root itself was deleted.

This is the "attach right subtree under predecessor" variant. The common alternative copies the inorder successor's value into the node and deletes the successor. Both are valid.

**Complexity:** O(h) time, O(1) extra space.

**C++**
```cpp
TreeNode* lastRight(TreeNode* node) {
    while (node->right) node = node->right;
    return node;
}
TreeNode* helperDelete(TreeNode* node) {
    if (node->left == nullptr) return node->right;
    if (node->right == nullptr) return node->left;
    TreeNode* rightChild = node->right;
    lastRight(node->left)->right = rightChild;      // hang right subtree under predecessor
    return node->left;
}
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return nullptr;
    if (root->val == key) return helperDelete(root);
    TreeNode* cur = root;
    while (cur) {
        if (key < cur->val) {
            if (cur->left && cur->left->val == key) { cur->left = helperDelete(cur->left); break; }
            cur = cur->left;
        } else {
            if (cur->right && cur->right->val == key) { cur->right = helperDelete(cur->right); break; }
            cur = cur->right;
        }
    }
    return root;
}
```

**Java**
```java
class Solution {
    static TreeNode lastRight(TreeNode node) {
        while (node.right != null) node = node.right;
        return node;
    }
    static TreeNode helperDelete(TreeNode node) {
        if (node.left == null) return node.right;
        if (node.right == null) return node.left;
        TreeNode rightChild = node.right;
        lastRight(node.left).right = rightChild;
        return node.left;
    }
    static TreeNode deleteNode(TreeNode root, int key) {
        if (root == null) return null;
        if (root.val == key) return helperDelete(root);
        TreeNode cur = root;
        while (cur != null) {
            if (key < cur.val) {
                if (cur.left != null && cur.left.val == key) { cur.left = helperDelete(cur.left); break; }
                cur = cur.left;
            } else {
                if (cur.right != null && cur.right.val == key) { cur.right = helperDelete(cur.right); break; }
                cur = cur.right;
            }
        }
        return root;
    }
}
```

#### Edge Cases & Pitfalls
- **Deleting the root** must return the new root.
- **The tree may become taller.** This variant can increase the height. The successor-copy variant keeps the shape more balanced, but both are O(h) per operation.

#### Key Takeaways
- Deletion has three cases: leaf, one child, two children. With two children, connect one subtree to the boundary node of the other.

[↑ Contents](#contents) · [← Previous](#p311) · [Next →](#p313)

---

<a id="p313"></a>

### 6. Kth Smallest and Largest element in BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Medium | Core | No | [LeetCode](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/kth-smallest-and-largest-elements-in-a-bst) | [Watch](https://youtu.be/9TJYWh0adfk) |

#### Problem Statement
Return the **k-th smallest** value in a BST (1-indexed), and similarly the **k-th largest**.

```text
        5
       / \
      3   6
     / \
    2   4
   /
  1          k = 3 -> 3rd smallest = 3;   3rd largest = 4
```

#### Approach 1: Brute Force — store the inorder traversal (as in the video)
Inorder gives the sorted values, so return `inorder[k−1]`. For the k-th largest, return `inorder[n−k]`.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
void inorderStore(TreeNode* node, vector<int>& v) {
    if (!node) return;
    inorderStore(node->left, v);
    v.push_back(node->val);
    inorderStore(node->right, v);
}
int kthSmallestBrute(TreeNode* root, int k) {
    vector<int> v;
    inorderStore(root, v);
    return v[k - 1];
}
int kthLargestBrute(TreeNode* root, int k) {
    vector<int> v;
    inorderStore(root, v);
    return v[v.size() - k];
}
```

**Java**
```java
class Solution {
    static void inorderStore(TreeNode node, List<Integer> v) {
        if (node == null) return;
        inorderStore(node.left, v);
        v.add(node.val);
        inorderStore(node.right, v);
    }
    static int kthSmallestBrute(TreeNode root, int k) {
        List<Integer> v = new ArrayList<>();
        inorderStore(root, v);
        return v.get(k - 1);
    }
    static int kthLargestBrute(TreeNode root, int k) {
        List<Integer> v = new ArrayList<>();
        inorderStore(root, v);
        return v.get(v.size() - k);
    }
}
```

#### Approach 2: Better — inorder with a counter, stopping at k (as in the video)
- **Count instead of storing.** During the inorder traversal, increment a counter on each visit and stop when it reaches `k`.
- **The k-th largest:**
  - it is the **(n − k + 1)-th smallest**, but that needs `n` first;
  - more simply, run a **reverse inorder** (right, root, left) and count to `k`.

**Complexity:** O(n) time. O(h) recursion space, or O(1) with Morris inorder.

**C++**
```cpp
void kthHelper(TreeNode* node, int k, int& cnt, int& ans) {
    if (!node || cnt >= k) return;
    kthHelper(node->left, k, cnt, ans);
    if (++cnt == k) { ans = node->val; return; }
    kthHelper(node->right, k, cnt, ans);
}
int kthSmallest(TreeNode* root, int k) {
    int cnt = 0, ans = -1;
    kthHelper(root, k, cnt, ans);
    return ans;
}
void kthLargeHelper(TreeNode* node, int k, int& cnt, int& ans) {   // reverse inorder
    if (!node || cnt >= k) return;
    kthLargeHelper(node->right, k, cnt, ans);
    if (++cnt == k) { ans = node->val; return; }
    kthLargeHelper(node->left, k, cnt, ans);
}
int kthLargest(TreeNode* root, int k) {
    int cnt = 0, ans = -1;
    kthLargeHelper(root, k, cnt, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    static int cnt, ans;
    static void kthHelper(TreeNode node, int k) {
        if (node == null || cnt >= k) return;
        kthHelper(node.left, k);
        if (++cnt == k) { ans = node.val; return; }
        kthHelper(node.right, k);
    }
    static int kthSmallest(TreeNode root, int k) {
        cnt = 0; ans = -1;
        kthHelper(root, k);
        return ans;
    }
    static void kthLargeHelper(TreeNode node, int k) {
        if (node == null || cnt >= k) return;
        kthLargeHelper(node.right, k);
        if (++cnt == k) { ans = node.val; return; }
        kthLargeHelper(node.left, k);
    }
    static int kthLargest(TreeNode root, int k) {
        cnt = 0; ans = -1;
        kthLargeHelper(root, k);
        return ans;
    }
}
```

#### Key Takeaways
- k-th smallest is the k-th node in inorder; k-th largest is the k-th node in reverse inorder.
- Morris traversal removes the recursion stack for O(1) space.

[↑ Contents](#contents) · [← Previous](#p312) · [Next →](#p314)

---

<a id="p314"></a>

### 7. Check if a tree is a BST or not

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Medium | Core | No | [LeetCode](https://leetcode.com/problems/validate-binary-search-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/validate-binary-search-tree) | [Watch](https://youtu.be/f-sj7I5oXEI) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Return `true` if a binary tree is a **valid BST**: every node's left subtree holds only **smaller** values, its right subtree only **greater** values, and both subtrees are BSTs.

```text
    5
   / \
  1   7
     / \
    4   8       -> false   (4 is in 5's right subtree but 4 < 5)
```

#### Approach 1: Brute Force — inorder must be strictly increasing
Collect the inorder traversal and check that it's strictly increasing.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
void inorderVals(TreeNode* node, vector<long long>& v) {
    if (!node) return;
    inorderVals(node->left, v);
    v.push_back(node->val);
    inorderVals(node->right, v);
}
bool isValidBSTInorder(TreeNode* root) {
    vector<long long> v;
    inorderVals(root, v);
    for (size_t i = 1; i < v.size(); i++) if (v[i] <= v[i - 1]) return false;
    return true;
}
```

**Java**
```java
class Solution {
    static void inorderVals(TreeNode node, List<Integer> v) {
        if (node == null) return;
        inorderVals(node.left, v);
        v.add(node.val);
        inorderVals(node.right, v);
    }
    static boolean isValidBSTInorder(TreeNode root) {
        List<Integer> v = new ArrayList<>();
        inorderVals(root, v);
        for (int i = 1; i < v.size(); i++) if (v.get(i) <= v.get(i - 1)) return false;
        return true;
    }
}
```

#### Approach 2: Optimal — pass down a valid range (min, max)
- **Every node has a permitted range.** The root may be anything in (−∞, +∞).
- **Going left** narrows the **upper** bound to the node's value: `(min, node.val)`.
- **Going right** narrows the **lower** bound: `(node.val, max)`.
- **The check.** A node outside its range makes the tree invalid. This catches the "4 under 7 under 5" case that a parent–child-only check would miss.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
bool validate(TreeNode* node, long long lo, long long hi) {
    if (node == nullptr) return true;
    if (node->val <= lo || node->val >= hi) return false;
    return validate(node->left, lo, node->val) && validate(node->right, node->val, hi);
}
bool isValidBST(TreeNode* root) {
    return validate(root, LLONG_MIN, LLONG_MAX);
}
```

**Java**
```java
class Solution {
    static boolean validate(TreeNode node, long lo, long hi) {
        if (node == null) return true;
        if (node.val <= lo || node.val >= hi) return false;
        return validate(node.left, lo, node.val) && validate(node.right, node.val, hi);
    }
    static boolean isValidBST(TreeNode root) {
        return validate(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }
}
```

#### Edge Cases & Pitfalls
- **Use 64-bit bounds.** A node with value `INT_MIN` or `INT_MAX` must be allowed, so `int` sentinels would wrongly reject it.
- **Checking only parent and child is wrong.** The constraint applies to **all ancestors**.

#### Key Takeaways
- Validate a BST by passing down the (min, max) window each node must fall in, or by checking that inorder is strictly increasing.

[↑ Contents](#contents) · [← Previous](#p313) · [Next →](#p315)

---

<a id="p315"></a>

### 8. LCA in BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Medium | Core | No | [LeetCode](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/lowest-common-ancestor-of-a-binary-search-tree) | [Watch](https://youtu.be/cX_kPV_foZc) |

#### Problem Statement
Given a BST and two nodes `p` and `q`, return their lowest common ancestor.

```text
            6
          /   \
         2     8
        / \   / \
       0   4 7   9
          / \
         3   5        LCA(2, 8) = 6;  LCA(2, 4) = 2;  LCA(3, 5) = 4
```

#### Approach: Use the ordering to find the split point (as in the video)
Start at the root:
- if both `p` and `q` are **smaller** than `node`, the LCA is in the left subtree, so go left;
- if both are **greater**, go right;
- otherwise they lie on different sides, or one of them *is* `node`, so `node` is the LCA.

**Complexity:** O(h) time, O(1) space for the iterative version. That's better than the general binary-tree LCA's O(n).

**C++**
```cpp
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val) root = root->left;
        else if (p->val > root->val && q->val > root->val) root = root->right;
        else return root;                          // split point
    }
    return nullptr;
}
```

**Java**
```java
class Solution {
    static TreeNode lowestCommonAncestorBST(TreeNode root, TreeNode p, TreeNode q) {
        while (root != null) {
            if (p.val < root.val && q.val < root.val) root = root.left;
            else if (p.val > root.val && q.val > root.val) root = root.right;
            else return root;
        }
        return null;
    }
}
```

#### Key Takeaways
- In a BST, the LCA is the first node whose value lies between `p` and `q`, inclusive.

[↑ Contents](#contents) · [← Previous](#p314) · [Next →](#p316)

---

<a id="p316"></a>

### 9. Construct a BST from a preorder traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Medium | Core | No | [LeetCode](https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/construct-a-bst-from-preorder-traversal) | [Watch](https://youtu.be/UmJT3j26t1I) |

#### Problem Statement
Construct a BST from its **preorder** traversal; all values are distinct. Return the root.

```text
preorder = [8, 5, 1, 7, 10, 12]   ->        8
                                           / \
                                          5   10
                                         / \    \
                                        1   7    12
```

#### Approach 1: Brute Force — insert the values one by one (as in the video)
Start with `pre[0]` as the root and insert every following value with the standard BST insert.

**Complexity:** O(n²) in the worst case, e.g. for sorted input (a skewed tree). O(h) space.

**C++**
```cpp
TreeNode* insertBST(TreeNode* root, int v) {
    if (!root) return new TreeNode(v);
    if (v < root->val) root->left = insertBST(root->left, v);
    else root->right = insertBST(root->right, v);
    return root;
}
TreeNode* bstFromPreorderBrute(vector<int>& preorder) {
    TreeNode* root = nullptr;
    for (int v : preorder) root = insertBST(root, v);
    return root;
}
```

**Java**
```java
class Solution {
    static TreeNode insertBST(TreeNode root, int v) {
        if (root == null) return new TreeNode(v);
        if (v < root.val) root.left = insertBST(root.left, v);
        else root.right = insertBST(root.right, v);
        return root;
    }
    static TreeNode bstFromPreorderBrute(int[] preorder) {
        TreeNode root = null;
        for (int v : preorder) root = insertBST(root, v);
        return root;
    }
}
```

#### Approach 2: Better — sort to get the inorder, then build from preorder + inorder (as in the video)
A BST's inorder is the **sorted** preorder. So sort a copy and reuse "Construct BT from Preorder and Inorder".

**Complexity:** O(n log n + n) time, O(n) space.

**C++**
```cpp
TreeNode* buildPreIn(vector<int>& pre, int ps, int pe, int is, int ie, unordered_map<int, int>& pos) {
    if (ps > pe || is > ie) return nullptr;
    TreeNode* root = new TreeNode(pre[ps]);
    int ir = pos[root->val], left = ir - is;
    root->left = buildPreIn(pre, ps + 1, ps + left, is, ir - 1, pos);
    root->right = buildPreIn(pre, ps + left + 1, pe, ir + 1, ie, pos);
    return root;
}
TreeNode* bstFromPreorderSort(vector<int>& preorder) {
    vector<int> in = preorder;
    sort(in.begin(), in.end());
    unordered_map<int, int> pos;
    for (int i = 0; i < (int)in.size(); i++) pos[in[i]] = i;
    return buildPreIn(preorder, 0, (int)preorder.size() - 1, 0, (int)in.size() - 1, pos);
}
```

**Java**
```java
class Solution {
    static TreeNode buildPreIn(int[] pre, int ps, int pe, int is, int ie, Map<Integer, Integer> pos) {
        if (ps > pe || is > ie) return null;
        TreeNode root = new TreeNode(pre[ps]);
        int ir = pos.get(root.val), left = ir - is;
        root.left = buildPreIn(pre, ps + 1, ps + left, is, ir - 1, pos);
        root.right = buildPreIn(pre, ps + left + 1, pe, ir + 1, ie, pos);
        return root;
    }
    static TreeNode bstFromPreorderSort(int[] preorder) {
        int[] in = preorder.clone();
        Arrays.sort(in);
        Map<Integer, Integer> pos = new HashMap<>();
        for (int i = 0; i < in.length; i++) pos.put(in[i], i);
        return buildPreIn(preorder, 0, preorder.length - 1, 0, in.length - 1, pos);
    }
}
```

#### Approach 3: Optimal — one pass with an upper bound (as in the video)
- **Consume preorder left to right** with a shared index `i`.
- **`build(bound)`** creates a node only if `pre[i] < bound`. Otherwise that value belongs to some ancestor's right side, so return null.
- **The children's bounds:**
  - `node.left = build(node.val)`, since everything in the left subtree is smaller than the node;
  - `node.right = build(bound)`, the parent's bound.
- **Why no lower bound is needed:** preorder visits a node's left subtree before reaching anything larger, so any value too small would already have been placed further up.

**Complexity:** O(n) time, since every node is visited a constant number of times (the video says O(3n)). O(h) stack.

**C++**
```cpp
TreeNode* buildBound(vector<int>& pre, int& i, int bound) {
    if (i == (int)pre.size() || pre[i] > bound) return nullptr;
    TreeNode* root = new TreeNode(pre[i++]);
    root->left = buildBound(pre, i, root->val);    // left values < root
    root->right = buildBound(pre, i, bound);       // right values < parent's bound
    return root;
}
TreeNode* bstFromPreorder(vector<int>& preorder) {
    int i = 0;
    return buildBound(preorder, i, INT_MAX);
}
```

**Java**
```java
class Solution {
    static int idx;
    static TreeNode buildBound(int[] pre, int bound) {
        if (idx == pre.length || pre[idx] > bound) return null;
        TreeNode root = new TreeNode(pre[idx++]);
        root.left = buildBound(pre, root.val);
        root.right = buildBound(pre, bound);
        return root;
    }
    static TreeNode bstFromPreorder(int[] preorder) {
        idx = 0;
        return buildBound(preorder, Integer.MAX_VALUE);
    }
}
```

#### Key Takeaways
- Preorder plus an upper bound rebuilds a BST in one pass. The same "pass down a bound" idea validates a BST.

[↑ Contents](#contents) · [← Previous](#p315) · [Next →](#p317)

---

<a id="p317"></a>

### 10. Inorder successor and predecessor in BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › Medium | Core | Yes | [LeetCode](https://leetcode.com/problems/inorder-successor-in-bst/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/inorder-successor-and-predecessor-in-a-bst) | [Watch](https://youtu.be/SXKAD2svfmI) |

#### Problem Statement
Given a BST and a key (the node may or may not exist), find its **inorder successor**, the smallest value greater than the key, and its **inorder predecessor**, the largest value smaller than the key. Return null or −1 if none exists.

```text
            5
          /   \
         3     7
        / \   / \
       2   4 6   9
      /         /
     1         8         key = 4 -> predecessor 3, successor 5
```

#### Approach 1: Brute Force — inorder array, then search it (as in the video)
Store the inorder traversal. The successor is the first value `> key`, and the predecessor is the last value `< key`.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
void inorderList(TreeNode* node, vector<int>& v) {
    if (!node) return;
    inorderList(node->left, v);
    v.push_back(node->val);
    inorderList(node->right, v);
}
pair<int, int> predSuccBrute(TreeNode* root, int key) {     // {pred, succ}, -1 if none
    vector<int> v;
    inorderList(root, v);
    int pred = -1, succ = -1;
    for (int x : v) {
        if (x < key) pred = x;
        if (x > key && succ == -1) succ = x;
    }
    return {pred, succ};
}
```

**Java**
```java
class Solution {
    static void inorderList(TreeNode node, List<Integer> v) {
        if (node == null) return;
        inorderList(node.left, v);
        v.add(node.val);
        inorderList(node.right, v);
    }
    static int[] predSuccBrute(TreeNode root, int key) {
        List<Integer> v = new ArrayList<>();
        inorderList(root, v);
        int pred = -1, succ = -1;
        for (int x : v) {
            if (x < key) pred = x;
            if (x > key && succ == -1) succ = x;
        }
        return new int[]{pred, succ};
    }
}
```

#### Approach 2: Optimal — one downward walk each (as in the video)
**Successor:**
- If `key < node.val`, the node is a candidate. Record it and go **left** to look for a smaller one.
- Otherwise go right.

**Predecessor** is the mirror:
- If `key > node.val`, record the node and go right.
- Otherwise go left.

This is the same pattern as ceil and floor, but **strict**.

**Complexity:** O(h) time, O(1) space.

**C++**
```cpp
TreeNode* inorderSuccessor(TreeNode* root, int key) {
    TreeNode* succ = nullptr;
    while (root) {
        if (key < root->val) { succ = root; root = root->left; }
        else root = root->right;
    }
    return succ;
}
TreeNode* inorderPredecessor(TreeNode* root, int key) {
    TreeNode* pred = nullptr;
    while (root) {
        if (key > root->val) { pred = root; root = root->right; }
        else root = root->left;
    }
    return pred;
}
```

**Java**
```java
class Solution {
    static TreeNode inorderSuccessor(TreeNode root, int key) {
        TreeNode succ = null;
        while (root != null) {
            if (key < root.val) { succ = root; root = root.left; }
            else root = root.right;
        }
        return succ;
    }
    static TreeNode inorderPredecessor(TreeNode root, int key) {
        TreeNode pred = null;
        while (root != null) {
            if (key > root.val) { pred = root; root = root.right; }
            else root = root.left;
        }
        return pred;
    }
}
```

#### Key Takeaways
- Successor and predecessor are strict ceil and strict floor, found in a single O(h) walk.

[↑ Contents](#contents) · [← Previous](#p316) · [Next →](#p318)

---

## FAQs

<a id="p318"></a>

### 11. BST iterator

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/binary-search-tree-iterator/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/binary-search-tree-iterator) | [Watch](https://youtu.be/D2jMcmxU4bs) |

#### Problem Statement
Implement `BSTIterator` over a BST's **inorder** sequence:
- `next()` returns the next smallest value;
- `hasNext()` reports whether more values remain.

Both should take **O(1) on average** with **O(h) memory**.

```text
BST: 7 / (3, 15 / (9, 20))   next() 3, next() 7, hasNext() true, next() 9, next() 15, next() 20, hasNext() false
```

#### Approach 1: Brute Force — precompute the inorder list *(not the intended solution)*
Store the whole inorder traversal and walk an index through it.

**Complexity:** O(1) per call, but O(n) memory, which violates the O(h) requirement.

**C++**
```cpp
class BSTIteratorList {
    vector<int> v;
    size_t idx = 0;
    void fill(TreeNode* n) { if (!n) return; fill(n->left); v.push_back(n->val); fill(n->right); }
public:
    BSTIteratorList(TreeNode* root) { fill(root); }
    int next() { return v[idx++]; }
    bool hasNext() { return idx < v.size(); }
};
```

**Java**
```java
class BSTIteratorList {
    private final List<Integer> v = new ArrayList<>();
    private int idx = 0;
    private void fill(TreeNode n) { if (n == null) return; fill(n.left); v.add(n.val); fill(n.right); }
    BSTIteratorList(TreeNode root) { fill(root); }
    int next() { return v.get(idx++); }
    boolean hasNext() { return idx < v.size(); }
}
```

#### Approach 2: Optimal — controlled iterative inorder with a stack (as in the video)
Borrow the iterative inorder traversal and pause it between calls:
- **Constructor:** push the root and **all of its left descendants**, so the stack top is the smallest value.
- **`next()`:** pop the top. That's the answer. Then push its **right** child and all of that child's left descendants.
- **`hasNext()`:** the stack is non-empty.

**Complexity:** amortised O(1) per call, because each node is pushed and popped exactly once over the full iteration. O(h) space.

**C++**
```cpp
class BSTIterator {
    stack<TreeNode*> st;
    void pushAll(TreeNode* node) {
        for (; node; node = node->left) st.push(node);
    }
public:
    BSTIterator(TreeNode* root) { pushAll(root); }
    int next() {
        TreeNode* node = st.top(); st.pop();
        pushAll(node->right);                     // next smallest values come from the right subtree
        return node->val;
    }
    bool hasNext() { return !st.empty(); }
};
```

**Java**
```java
class BSTIterator {
    private final Deque<TreeNode> st = new ArrayDeque<>();
    private void pushAll(TreeNode node) {
        for (; node != null; node = node.left) st.push(node);
    }
    BSTIterator(TreeNode root) { pushAll(root); }
    int next() {
        TreeNode node = st.pop();
        pushAll(node.right);
        return node.val;
    }
    boolean hasNext() { return !st.isEmpty(); }
}
```

#### Key Takeaways
- An iterator is a traversal you can pause. The stack holds the "left spine still to visit".
- The mirrored version, pushing right spines, gives descending order. It's used in Two Sum in BST next.

[↑ Contents](#contents) · [← Previous](#p317) · [Next →](#p319)

---

<a id="p319"></a>

### 12. Two sum in BST

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/two-sum-in-bst) | [Watch](https://youtu.be/ssL3sHwPeb4) |

#### Problem Statement
Given a BST and a target `k`, return `true` if there are **two distinct nodes** whose values sum to `k`.

```text
        5
       / \
      3   6
     / \   \
    2   4   7       k = 9 -> true (2+7, 3+6, 4+5);   k = 28 -> false
```

#### Approach 1: Brute Force — inorder array + two pointers (as in the video)
Inorder gives a sorted array. Run the classic two-pointer two-sum on it:
- `l = 0`, `r = n − 1`;
- if the sum is too small, `l++`; if too large, `r−−`.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
void inorderArr(TreeNode* node, vector<int>& v) {
    if (!node) return;
    inorderArr(node->left, v);
    v.push_back(node->val);
    inorderArr(node->right, v);
}
bool findTargetBrute(TreeNode* root, int k) {
    vector<int> v;
    inorderArr(root, v);
    int l = 0, r = (int)v.size() - 1;
    while (l < r) {
        int s = v[l] + v[r];
        if (s == k) return true;
        if (s < k) l++; else r--;
    }
    return false;
}
```

**Java**
```java
class Solution {
    static void inorderArr(TreeNode node, List<Integer> v) {
        if (node == null) return;
        inorderArr(node.left, v);
        v.add(node.val);
        inorderArr(node.right, v);
    }
    static boolean findTargetBrute(TreeNode root, int k) {
        List<Integer> v = new ArrayList<>();
        inorderArr(root, v);
        int l = 0, r = v.size() - 1;
        while (l < r) {
            int s = v.get(l) + v.get(r);
            if (s == k) return true;
            if (s < k) l++; else r--;
        }
        return false;
    }
}
```

#### Approach 2: Optimal — two BST iterators, `next` and `before` (as in the video)
Replace the array with two iterators over the tree:
- `next()` walks ascending, pushing **left** spines;
- `before()` walks descending, pushing **right** spines.

Run two pointers on them: `i = next()`, `j = before()`. While `i < j`, compare `i + j` with `k` and advance the appropriate iterator.

**Complexity:** O(n) time, O(h) space for two stacks of height h.

**C++**
```cpp
class BSTIter {
    stack<TreeNode*> st;
    bool reverse;                                // false: ascending (next), true: descending (before)
    void pushAll(TreeNode* node) {
        while (node) { st.push(node); node = reverse ? node->right : node->left; }
    }
public:
    BSTIter(TreeNode* root, bool isReverse) : reverse(isReverse) { pushAll(root); }
    int next() {
        TreeNode* node = st.top(); st.pop();
        pushAll(reverse ? node->left : node->right);
        return node->val;
    }
};
bool findTarget(TreeNode* root, int k) {
    if (!root) return false;
    BSTIter l(root, false), r(root, true);
    int i = l.next(), j = r.next();
    while (i < j) {
        if (i + j == k) return true;
        if (i + j < k) i = l.next();
        else j = r.next();
    }
    return false;
}
```

**Java**
```java
class BSTIter {
    private final Deque<TreeNode> st = new ArrayDeque<>();
    private final boolean reverse;
    BSTIter(TreeNode root, boolean isReverse) { reverse = isReverse; pushAll(root); }
    private void pushAll(TreeNode node) {
        while (node != null) { st.push(node); node = reverse ? node.right : node.left; }
    }
    int next() {
        TreeNode node = st.pop();
        pushAll(reverse ? node.left : node.right);
        return node.val;
    }
}
class Solution {
    static boolean findTarget(TreeNode root, int k) {
        if (root == null) return false;
        BSTIter l = new BSTIter(root, false), r = new BSTIter(root, true);
        int i = l.next(), j = r.next();
        while (i < j) {
            if (i + j == k) return true;
            if (i + j < k) i = l.next();
            else j = r.next();
        }
        return false;
    }
}
```

#### Edge Cases & Pitfalls
- **The loop never runs dry.** `i < j` stops before either iterator is exhausted, because the two pointers meet first. Two distinct nodes are required, and the strict inequality ensures that.

#### Key Takeaways
- Turn a BST into two sorted streams (ascending and descending iterators) and apply array techniques with O(h) memory.

[↑ Contents](#contents) · [← Previous](#p318) · [Next →](#p320)

---

<a id="p320"></a>

### 13. Correct BST with two nodes swapped

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/recover-binary-search-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/recover-binary-search-tree) | [Watch](https://youtu.be/ZWGW7FminDM) |

#### Problem Statement
Exactly **two nodes** of a BST were swapped by mistake. **Recover** the tree by swapping their values back, without changing its structure.

```text
input:     1           output:    3
          /                      /
         3                      1
          \                      \
           2                      2      (1 and 3 were swapped)
```

#### Approach 1: Brute Force — sort the inorder values and rewrite them (as in the video)
- Collect the inorder values and sort them. This gives the correct inorder.
- Traverse inorder again, overwriting each node with the next sorted value.

**Complexity:** O(2n + n log n) time, O(n) space.

**C++**
```cpp
void collectIn(TreeNode* n, vector<int>& v) {
    if (!n) return;
    collectIn(n->left, v);
    v.push_back(n->val);
    collectIn(n->right, v);
}
void rewriteIn(TreeNode* n, vector<int>& v, int& i) {
    if (!n) return;
    rewriteIn(n->left, v, i);
    n->val = v[i++];
    rewriteIn(n->right, v, i);
}
void recoverTreeBrute(TreeNode* root) {
    vector<int> v;
    collectIn(root, v);
    sort(v.begin(), v.end());
    int i = 0;
    rewriteIn(root, v, i);
}
```

**Java**
```java
class Solution {
    static void collectIn(TreeNode n, List<Integer> v) {
        if (n == null) return;
        collectIn(n.left, v);
        v.add(n.val);
        collectIn(n.right, v);
    }
    static int wi;
    static void rewriteIn(TreeNode n, List<Integer> v) {
        if (n == null) return;
        rewriteIn(n.left, v);
        n.val = v.get(wi++);
        rewriteIn(n.right, v);
    }
    static void recoverTreeBrute(TreeNode root) {
        List<Integer> v = new ArrayList<>();
        collectIn(root, v);
        Collections.sort(v);
        wi = 0;
        rewriteIn(root, v);
    }
}
```

#### Approach 2: Optimal — find the violations during one inorder pass (as in the video)
In a sorted sequence with two swapped elements, there are either **two** places where `prev > cur`, when the swapped elements aren't adjacent, or **one**, when they are. During the inorder traversal, track `prev`:
- **first violation:** `first = prev` and `middle = cur`;
- **second violation, if any:** `last = cur`.

At the end:
- if `last` exists, swap `first` and `last` (non-adjacent case);
- otherwise swap `first` and `middle` (adjacent case).

**Complexity:** O(n) time, O(h) stack. It's O(1) with Morris traversal.

**C++**
```cpp
TreeNode *firstN, *middleN, *lastN, *prevN;
void inorderFix(TreeNode* root) {
    if (!root) return;
    inorderFix(root->left);
    if (prevN && root->val < prevN->val) {        // violation
        if (!firstN) { firstN = prevN; middleN = root; }
        else lastN = root;
    }
    prevN = root;
    inorderFix(root->right);
}
void recoverTree(TreeNode* root) {
    firstN = middleN = lastN = prevN = nullptr;
    inorderFix(root);
    if (firstN && lastN) swap(firstN->val, lastN->val);       // non-adjacent swap
    else if (firstN && middleN) swap(firstN->val, middleN->val);   // adjacent swap
}
```

**Java**
```java
class Solution {
    static TreeNode firstN, middleN, lastN, prevN;
    static void inorderFix(TreeNode root) {
        if (root == null) return;
        inorderFix(root.left);
        if (prevN != null && root.val < prevN.val) {
            if (firstN == null) { firstN = prevN; middleN = root; }
            else lastN = root;
        }
        prevN = root;
        inorderFix(root.right);
    }
    static void recoverTree(TreeNode root) {
        firstN = middleN = lastN = prevN = null;
        inorderFix(root);
        if (firstN != null && lastN != null) { int t = firstN.val; firstN.val = lastN.val; lastN.val = t; }
        else if (firstN != null && middleN != null) { int t = firstN.val; firstN.val = middleN.val; middleN.val = t; }
    }
}
```

#### Key Takeaways
- Two swapped elements in a sorted sequence create one or two "descents". Remember (first, middle) at the first and (last) at the second.

[↑ Contents](#contents) · [← Previous](#p319) · [Next →](#p321)

---

<a id="p321"></a>

### 14. Largest BST in Binary Tree

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search Trees › FAQs | Pro | Yes | [LeetCode](https://leetcode.com/problems/largest-bst-subtree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/largest-bst-in-binary-tree) | [Watch](https://youtu.be/X0oXMdtUDwo) |

#### Problem Statement
Return the **size** (number of nodes) of the largest subtree of a binary tree that is a valid BST. A subtree here means a node with **all** of its descendants.

```text
        10
       /  \
      5    15
     / \     \
    1   8     7       ->  3   (the subtree 5 / (1, 8))
```

#### Approach 1: Brute Force — validate the subtree at every node (as in the video)
For each node, run "Validate BST" on its subtree. If it's valid, count its nodes.

**Complexity:** O(n²) time, O(h) stack.

**C++**
```cpp
bool validRange(TreeNode* n, long long lo, long long hi) {
    if (!n) return true;
    if (n->val <= lo || n->val >= hi) return false;
    return validRange(n->left, lo, n->val) && validRange(n->right, n->val, hi);
}
int countAll(TreeNode* n) { return n ? 1 + countAll(n->left) + countAll(n->right) : 0; }
int largestBSTBrute(TreeNode* root) {
    if (!root) return 0;
    if (validRange(root, LLONG_MIN, LLONG_MAX)) return countAll(root);
    return max(largestBSTBrute(root->left), largestBSTBrute(root->right));
}
```

**Java**
```java
class Solution {
    static boolean validRange(TreeNode n, long lo, long hi) {
        if (n == null) return true;
        if (n.val <= lo || n.val >= hi) return false;
        return validRange(n.left, lo, n.val) && validRange(n.right, n.val, hi);
    }
    static int countAll(TreeNode n) { return n == null ? 0 : 1 + countAll(n.left) + countAll(n.right); }
    static int largestBSTBrute(TreeNode root) {
        if (root == null) return 0;
        if (validRange(root, Long.MIN_VALUE, Long.MAX_VALUE)) return countAll(root);
        return Math.max(largestBSTBrute(root.left), largestBSTBrute(root.right));
    }
}
```

#### Approach 2: Optimal — postorder returning (min, max, size) (as in the video)
- **What each subtree reports.** Process the children first, then report `{minVal, maxVal, size}` for the subtree.
- **An empty subtree** reports `{+∞, −∞, 0}`, which any parent accepts.
- **A valid BST at `node`** needs `left.max < node.val < right.min`. Then report `{min(left.min, node.val), max(right.max, node.val), left.size + right.size + 1}`.
- **An invalid subtree** reports `{−∞, +∞, max(left.size, right.size)}`. That range can't fit inside any parent, so every ancestor becomes invalid too, while the best size found so far is still carried up.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
struct NodeInfo { long long minVal, maxVal; int size; };
NodeInfo largestHelper(TreeNode* node) {
    if (!node) return {LLONG_MAX, LLONG_MIN, 0};
    NodeInfo L = largestHelper(node->left), R = largestHelper(node->right);
    if (L.maxVal < node->val && node->val < R.minVal)       // valid BST here
        return {min<long long>(L.minVal, node->val), max<long long>(R.maxVal, node->val), L.size + R.size + 1};
    return {LLONG_MIN, LLONG_MAX, max(L.size, R.size)};     // invalid: poison the range
}
int largestBST(TreeNode* root) {
    return largestHelper(root).size;
}
```

**Java**
```java
class Solution {
    static long[] largestHelper(TreeNode node) {              // {min, max, size}
        if (node == null) return new long[]{Long.MAX_VALUE, Long.MIN_VALUE, 0};
        long[] L = largestHelper(node.left), R = largestHelper(node.right);
        if (L[1] < node.val && node.val < R[0])
            return new long[]{Math.min(L[0], node.val), Math.max(R[1], node.val), L[2] + R[2] + 1};
        return new long[]{Long.MIN_VALUE, Long.MAX_VALUE, Math.max(L[2], R[2])};
    }
    static int largestBST(TreeNode root) {
        return (int) largestHelper(root)[2];
    }
}
```

#### Key Takeaways
- Bottom-up DP on trees: each subtree reports a small summary (min, max, size) from which the parent decides its own validity in O(1).

[↑ Contents](#contents) · [← Previous](#p320)

---
