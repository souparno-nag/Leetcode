# Binary Trees — Striver's A2Z DSA Sheet Notes

Section 13 of 20 · 31 problems · 31 with video, 0 without · [All sections](00-index.md)

[← Stack / Queues](12-stack-queues.md) | [Binary Search Trees →](14-binary-search-trees.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Theory/Traversals**

1. [Inorder Traversal](#p277) — Basic
2. [Preorder Traversal](#p278) — Basic
3. [Postorder Traversal](#p279) — Basic
4. [Level Order Traversal](#p280) — Core
5. [Pre, Post, Inorder in one traversal](#p281) — Core · *video not transcribed*

**Medium Problems**

6. [Maximum Depth in BT](#p282) — Core
7. [Check if two trees are identical or not](#p283) — Core
8. [Check for balanced binary tree](#p284) — Core
9. [Diameter of Binary Tree](#p285) — Core
10. [Maximum path sum](#p286) — Pro
11. [Check for symmetrical BTs](#p287) — Core
12. [Children Sum Property in Binary Tree](#p288) — Core · *video not transcribed*

**FAQs**

13. [Zig Zag or Spiral Traversal](#p289) — Core
14. [Boundary Traversal](#p290) — Core
15. [Vertical Order Traversal](#p291) — Pro
16. [Top View of BT](#p292) — Core
17. [Bottom view of BT](#p293) — Core
18. [Right/Left View of BT](#p294) — Core
19. [Print root to leaf path in BT](#p295) — Core
20. [Lowest Common Ancestor in BT](#p296) — Pro · *video not transcribed*
21. [Maximum Width of BT](#p297) — Pro
22. [Print all nodes at a distance of K in BT](#p298) — Pro
23. [Minimum time taken to burn the BT from a given Node](#p299) — Pro
24. [Count total nodes in a complete BT](#p300) — Core
25. [Flatten Binary Tree to Linked List](#p301) — Pro

**Construction Problems**

26. [Requirements needed to construct a unique BT](#p302) — Core · *video not transcribed*
27. [Construct a BT from Preorder and Inorder](#p303) — Core
28. [Construct a BT from Postorder and Inorder](#p304) — Core
29. [Serialize and De-serialize BT](#p305) — Pro

**Traversal in Constant Space**

30. [Morris Inorder Traversal](#p306) — Pro · *video not transcribed*
31. [Morris Preorder Traversal](#p307) — Pro · *video not transcribed*

---

## Theory/Traversals

<a id="p277"></a>

### 1. Inorder Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Theory/Traversals | Basic | No | [LeetCode](https://leetcode.com/problems/binary-tree-inorder-traversal/) | [Watch](https://youtu.be/lxTGsVXjwvM) |

> Node type used throughout this section (LeetCode style): `struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };`. In Java it's `class TreeNode { int val; TreeNode left, right; }`.

#### Problem Statement
Return the **inorder** traversal of a binary tree: **Left → Root → Right**.

```text
        1
       / \
      2   3
     / \
    4   5
   / \
  6   7          inorder = [6, 4, 7, 2, 5, 1, 3]
```

#### Approach 1: Recursive (from L6, Z_NEgBgbRVI)
`inorder(node)`: if `node` is null, return. Otherwise recurse on the left subtree, record `node`, then recurse on the right subtree.

**Complexity:** O(n) time. O(h) auxiliary stack space, which is O(n) for a skewed tree.

**C++**
```cpp
void inorderRec(TreeNode* node, vector<int>& ans) {
    if (node == nullptr) return;
    inorderRec(node->left, ans);
    ans.push_back(node->val);
    inorderRec(node->right, ans);
}
vector<int> inorderTraversalRec(TreeNode* root) {
    vector<int> ans;
    inorderRec(root, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    static void inorderRec(TreeNode node, List<Integer> ans) {
        if (node == null) return;
        inorderRec(node.left, ans);
        ans.add(node.val);
        inorderRec(node.right, ans);
    }
    static List<Integer> inorderTraversalRec(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        inorderRec(root, ans);
        return ans;
    }
}
```

#### Approach 2: Iterative with an explicit stack (as in the video, L10)
The interviewer asks for it without recursion, so simulate the recursion stack yourself:
- `node = root`. Loop:
  - if `node` is **not null**: push it and go **left**, just as the recursion keeps going left;
  - if `node` is **null**:
    - if the stack is empty, you're done;
    - otherwise pop, **record** it (it's the "root" step), and go to its **right**.

Dry run on the tree above:
- Push 1, 2, 4, 6. Left of 6 is null, so pop 6, record **6**, and go to its right (null).
- Pop 4, record **4**, go right to 7. Push 7; its left is null. Pop and record **7**.
- Pop 2, record **2**, go right to 5, and so on.

**Complexity:** O(n) time, O(h) space for the stack.

**C++**
```cpp
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> st;
    TreeNode* node = root;
    while (true) {
        if (node != nullptr) {
            st.push(node);
            node = node->left;              // go as far left as possible
        } else {
            if (st.empty()) break;
            node = st.top(); st.pop();
            ans.push_back(node->val);       // left done -> visit root
            node = node->right;             // then the right subtree
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Deque<TreeNode> st = new ArrayDeque<>();
        TreeNode node = root;
        while (true) {
            if (node != null) {
                st.push(node);
                node = node.left;
            } else {
                if (st.isEmpty()) break;
                node = st.pop();
                ans.add(node.val);
                node = node.right;
            }
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Empty tree.** Both versions return `[]`.
- **O(1) space.** For constant extra space, use **Morris inorder traversal** (end of this section).

#### Key Takeaways
- Inorder is left, root, right. Iteratively: dive left pushing nodes, pop and visit, then switch to the right child.
- For a BST, inorder gives the values in sorted order.

[↑ Contents](#contents) · [Next →](#p278)

---

<a id="p278"></a>

### 2. Preorder Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Theory/Traversals | Basic | No | [LeetCode](https://leetcode.com/problems/binary-tree-preorder-traversal/) | [Watch](https://youtu.be/RlUu72JrOCQ) |

#### Problem Statement
Return the **preorder** traversal of a binary tree: **Root → Left → Right**.

```text
        1
       / \
      2   3
     / \   \
    4   5   7          preorder = [1, 2, 4, 5, 3, 7]
```

#### Approach 1: Recursive (as in the video, L5)
`preorder(node)`: if `node` is null, return. Otherwise record `node`, recurse left, then recurse right.

**Complexity:** O(n) time, O(h) recursion stack.

**C++**
```cpp
void preorderRec(TreeNode* node, vector<int>& ans) {
    if (node == nullptr) return;
    ans.push_back(node->val);
    preorderRec(node->left, ans);
    preorderRec(node->right, ans);
}
vector<int> preorderTraversalRec(TreeNode* root) {
    vector<int> ans;
    preorderRec(root, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    static void preorderRec(TreeNode node, List<Integer> ans) {
        if (node == null) return;
        ans.add(node.val);
        preorderRec(node.left, ans);
        preorderRec(node.right, ans);
    }
    static List<Integer> preorderTraversalRec(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        preorderRec(root, ans);
        return ans;
    }
}
```

#### Approach 2: Iterative with a stack (Striver's L9, Bfqd8BsPVuw; captions not usable, written from the standard method)
- Push the root.
- While the stack is non-empty: pop a node and record it, then push its **right** child **before** its **left**. The stack is LIFO, so the left child is processed first.

**Complexity:** O(n) time, O(h) space. That's O(n) in the worst case, e.g. a tree where every right child must wait.

**C++**
```cpp
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top(); st.pop();
        ans.push_back(node->val);
        if (node->right) st.push(node->right);   // right first ...
        if (node->left) st.push(node->left);     // ... so left is processed first
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;
        Deque<TreeNode> st = new ArrayDeque<>();
        st.push(root);
        while (!st.isEmpty()) {
            TreeNode node = st.pop();
            ans.add(node.val);
            if (node.right != null) st.push(node.right);
            if (node.left != null) st.push(node.left);
        }
        return ans;
    }
}
```

#### Key Takeaways
- Preorder is root, left, right. Iteratively: pop, visit, push right, then push left.

[↑ Contents](#contents) · [← Previous](#p277) · [Next →](#p279)

---

<a id="p279"></a>

### 3. Postorder Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Theory/Traversals | Basic | No | [LeetCode](https://leetcode.com/problems/binary-tree-postorder-traversal/) | [Watch](https://youtu.be/2YBhNLodD8Q) |

#### Problem Statement
Return the **postorder** traversal of a binary tree: **Left → Right → Root**.

```text
        1
       / \
      2   3
     / \
    4   5            postorder = [4, 5, 2, 3, 1]
```

#### Approach 1: Recursive (from L7, COQOU6klsBg)
**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
void postorderRec(TreeNode* node, vector<int>& ans) {
    if (node == nullptr) return;
    postorderRec(node->left, ans);
    postorderRec(node->right, ans);
    ans.push_back(node->val);
}
vector<int> postorderTraversalRec(TreeNode* root) {
    vector<int> ans;
    postorderRec(root, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    static void postorderRec(TreeNode node, List<Integer> ans) {
        if (node == null) return;
        postorderRec(node.left, ans);
        postorderRec(node.right, ans);
        ans.add(node.val);
    }
    static List<Integer> postorderTraversalRec(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        postorderRec(root, ans);
        return ans;
    }
}
```

#### Approach 2: Iterative with two stacks (as in the video, L11)
- **The trick.** Doing "root, right, left", a mirrored preorder, and then **reversing** it gives "left, right, root".
- **The steps:**
  1. Push the root onto `st1`.
  2. While `st1` is non-empty: pop a node, push it onto `st2`, then push its **left** child and then its **right** child onto `st1`.
  3. Finally, pop everything from `st2`. That order is the postorder.

**Complexity:** O(n) time, O(2n) space for two stacks.

**C++**
```cpp
vector<int> postorderTwoStacks(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    stack<TreeNode*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        TreeNode* node = st1.top(); st1.pop();
        st2.push(node);
        if (node->left) st1.push(node->left);
        if (node->right) st1.push(node->right);
    }
    while (!st2.empty()) { ans.push_back(st2.top()->val); st2.pop(); }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> postorderTwoStacks(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;
        Deque<TreeNode> st1 = new ArrayDeque<>(), st2 = new ArrayDeque<>();
        st1.push(root);
        while (!st1.isEmpty()) {
            TreeNode node = st1.pop();
            st2.push(node);
            if (node.left != null) st1.push(node.left);
            if (node.right != null) st1.push(node.right);
        }
        while (!st2.isEmpty()) ans.add(st2.pop().val);
        return ans;
    }
}
```

#### Approach 3: Iterative with one stack (Striver's L12, NzIGLLwZBS8)
Go left as far as possible, pushing nodes. When you can't go further left:
- look at the top's **right** child (`temp = st.top()->right`);
- if it's **null**, the top's subtrees are done. Pop it and record it, and keep popping while the node you just popped was its parent's **right** child, because those parents are now complete too;
- otherwise, move to `temp` and continue diving left.

**Complexity:** O(2n) time, since each node is touched about twice. O(h) space.

**C++**
```cpp
vector<int> postorderOneStack(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur != nullptr || !st.empty()) {
        if (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        } else {
            TreeNode* temp = st.top()->right;
            if (temp == nullptr) {
                temp = st.top(); st.pop();
                ans.push_back(temp->val);
                while (!st.empty() && temp == st.top()->right) {   // finished right subtrees
                    temp = st.top(); st.pop();
                    ans.push_back(temp->val);
                }
            } else {
                cur = temp;
            }
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> postorderOneStack(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Deque<TreeNode> st = new ArrayDeque<>();
        TreeNode cur = root;
        while (cur != null || !st.isEmpty()) {
            if (cur != null) {
                st.push(cur);
                cur = cur.left;
            } else {
                TreeNode temp = st.peek().right;
                if (temp == null) {
                    temp = st.pop();
                    ans.add(temp.val);
                    while (!st.isEmpty() && temp == st.peek().right) {
                        temp = st.pop();
                        ans.add(temp.val);
                    }
                } else {
                    cur = temp;
                }
            }
        }
        return ans;
    }
}
```

#### Key Takeaways
- Postorder is left, right, root.
- Two stacks: a reversed "root, right, left" traversal.
- One stack: track whether you're returning from a right child.

[↑ Contents](#contents) · [← Previous](#p278) · [Next →](#p280)

---

<a id="p280"></a>

### 4. Level Order Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Theory/Traversals | Core | No | [LeetCode](https://leetcode.com/problems/binary-tree-level-order-traversal/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/binary-tree-level-order-traversal) | [Watch](https://youtu.be/EoAsWbO7sqg) |

#### Problem Statement
Return the **level-order** traversal (BFS) of a binary tree: the nodes **level by level**, left to right, with each level as its own list.

```text
        3
       / \
      9   20
         /  \
        15   7          ->  [[3], [9, 20], [15, 7]]
```

#### Approach: BFS with a queue
- Push the root into a queue.
- While the queue is non-empty:
  - `size = q.size()`. This is exactly the number of nodes on the current level.
  - Pop `size` nodes, recording each and pushing its left and right children.
  - The recorded values form one level.

**Complexity:** O(n) time. O(n) space: the queue holds up to a full level, about n/2 for a complete tree.

**C++**
```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (root == nullptr) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        ans.push_back(level);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root == null) return ans;
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> level = new ArrayList<>();
            for (int i = 0; i < size; i++) {
                TreeNode node = q.remove();
                level.add(node.val);
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
            ans.add(level);
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Snapshot the level size first.** Capture `q.size()` **before** the inner loop, because the queue grows while you process the level.

#### Key Takeaways
- BFS with a "size snapshot" processes one level at a time. This template underlies zig-zag, right view, maximum width, burn time and more.

[↑ Contents](#contents) · [← Previous](#p279) · [Next →](#p281)

---

<a id="p281"></a>

### 5. Pre, Post, Inorder in one traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Theory/Traversals | Core | No | — | [Watch](https://youtu.be/ySp2epYvgTE) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Produce the **preorder, inorder and postorder** traversals of a binary tree in a **single** traversal.

```text
        1
       / \
      2   3
     / \
    4   5
pre = [1,2,4,5,3], in = [4,2,5,1,3], post = [4,5,2,3,1]
```

#### Intuition — each node is visited three times
In the recursion, every node is "seen" three times: on arrival (preorder), after returning from the left subtree (inorder), and after returning from the right subtree (postorder). Simulate that with a stack of **(node, state)** pairs.

#### Approach: Stack of (node, state)
Push `(root, 1)`. Pop `(node, s)`:
- **s == 1:** record it in **preorder**, push `(node, 2)`, then push `(left, 1)` if the left child exists;
- **s == 2:** record it in **inorder**, push `(node, 3)`, then push `(right, 1)` if the right child exists;
- **s == 3:** record it in **postorder**, and don't push it back.

**Complexity:** O(3n) time, since each node is pushed and popped three times. O(4n) space: three output lists plus a stack of O(h).

**C++**
```cpp
vector<vector<int>> allTraversals(TreeNode* root) {
    vector<int> pre, in, post;
    if (root == nullptr) return {pre, in, post};
    stack<pair<TreeNode*, int>> st;
    st.push({root, 1});
    while (!st.empty()) {
        auto [node, s] = st.top(); st.pop();
        if (s == 1) {                        // first visit: preorder
            pre.push_back(node->val);
            st.push({node, 2});
            if (node->left) st.push({node->left, 1});
        } else if (s == 2) {                 // back from left: inorder
            in.push_back(node->val);
            st.push({node, 3});
            if (node->right) st.push({node->right, 1});
        } else {                             // back from right: postorder
            post.push_back(node->val);
        }
    }
    return {pre, in, post};
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> allTraversals(TreeNode root) {
        List<Integer> pre = new ArrayList<>(), in = new ArrayList<>(), post = new ArrayList<>();
        List<List<Integer>> res = new ArrayList<>(Arrays.asList(pre, in, post));
        if (root == null) return res;
        Deque<Object[]> st = new ArrayDeque<>();
        st.push(new Object[]{root, 1});
        while (!st.isEmpty()) {
            Object[] top = st.pop();
            TreeNode node = (TreeNode) top[0];
            int s = (Integer) top[1];
            if (s == 1) {
                pre.add(node.val);
                st.push(new Object[]{node, 2});
                if (node.left != null) st.push(new Object[]{node.left, 1});
            } else if (s == 2) {
                in.add(node.val);
                st.push(new Object[]{node, 3});
                if (node.right != null) st.push(new Object[]{node.right, 1});
            } else {
                post.add(node.val);
            }
        }
        return res;
    }
}
```

#### Key Takeaways
- Preorder, inorder and postorder are the 1st, 2nd and 3rd visits of the same DFS. A `(node, state)` stack reproduces all three at once.

[↑ Contents](#contents) · [← Previous](#p280) · [Next →](#p282)

---

## Medium Problems

<a id="p282"></a>

### 6. Maximum Depth in BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Medium Problems | Core | No | [LeetCode](https://leetcode.com/problems/maximum-depth-of-binary-tree/) | [Watch](https://youtu.be/eD3tmO66aBA) |

#### Problem Statement
Return the **maximum depth** (height) of a binary tree: the number of nodes on the longest root-to-leaf path.

```text
        1
       / \
      2   3
         / \
        4   5
             \
              6        ->  4
```

#### Approach 1: Recursive (as in the video)
`depth(node) = 0` if `node` is null, else `1 + max(depth(left), depth(right))`. The "1" counts the node itself.

**Complexity:** O(n) time. O(h) auxiliary stack, which is O(n) for a skewed tree.

**C++**
```cpp
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return 1 + max(lh, rh);
}
```

**Java**
```java
class Solution {
    static int maxDepth(TreeNode root) {
        if (root == null) return 0;
        int lh = maxDepth(root.left);
        int rh = maxDepth(root.right);
        return 1 + Math.max(lh, rh);
    }
}
```

#### Approach 2: Level-order traversal — count the levels (mentioned in the video)
The depth equals the number of BFS levels.

**Complexity:** O(n) time. O(n) space for the queue, since a full last level holds about n/2 nodes. The video prefers recursion for this problem: on balanced trees it uses only O(log n) stack, while BFS can hold O(n).

**C++**
```cpp
int maxDepthBFS(TreeNode* root) {
    if (root == nullptr) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int levels = 0;
    while (!q.empty()) {
        int size = q.size();
        levels++;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return levels;
}
```

**Java**
```java
class Solution {
    static int maxDepthBFS(TreeNode root) {
        if (root == null) return 0;
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        int levels = 0;
        while (!q.isEmpty()) {
            int size = q.size();
            levels++;
            for (int i = 0; i < size; i++) {
                TreeNode node = q.remove();
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
        }
        return levels;
    }
}
```

#### Key Takeaways
- Height = 1 + max(left height, right height). This one-liner is reused in the next three problems.

[↑ Contents](#contents) · [← Previous](#p281) · [Next →](#p283)

---

<a id="p283"></a>

### 7. Check if two trees are identical or not

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Medium Problems | Core | No | [LeetCode](https://leetcode.com/problems/same-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-identical-binary-trees) | [Watch](https://youtu.be/BhuvF_-PWS0) |

#### Problem Statement
Given the roots of two binary trees, return `true` if they are **identical**: the same structure and the same values at every node.

```text
  1        1
 / \      / \
2   3    2   3    ->  true

  1        1
 /          \
2            2    ->  false
```

#### Approach: Simultaneous traversal (as in the video)
Traverse both trees together with any traversal; the video uses preorder.
- If both are null, they're identical here: `true`.
- If exactly one is null, they differ: `false`.
- Otherwise the values must match, and both left subtrees and both right subtrees must be identical.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr || q == nullptr) return p == q;       // both null -> true
    return p->val == q->val
        && isSameTree(p->left, q->left)
        && isSameTree(p->right, q->right);
}
```

**Java**
```java
class Solution {
    static boolean isSameTree(TreeNode p, TreeNode q) {
        if (p == null || q == null) return p == q;
        return p.val == q.val && isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
    }
}
```

#### Key Takeaways
- The `p == q` trick handles all three null cases in one line.

[↑ Contents](#contents) · [← Previous](#p282) · [Next →](#p284)

---

<a id="p284"></a>

### 8. Check for balanced binary tree

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Medium Problems | Core | No | [LeetCode](https://leetcode.com/problems/balanced-binary-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-if-a-binary-tree-is-height-balanced) | [Watch](https://youtu.be/Yt50Jfbd8Po) |

#### Problem Statement
A binary tree is **height-balanced** if, for **every** node, the heights of its left and right subtrees differ by at most 1. Return whether the tree is balanced.

```text
    3
   / \
  9  20
     / \
    15  7      -> true

      1
     / \
    2   2
   / \
  3   3
 / \
4   4          -> false   (at the root: left height 3, right height 1)
```

#### Approach 1: Brute Force — compute the heights at every node (as in the video)
For each node, compute `lh` and `rh` from scratch with the height function. If `|lh − rh| > 1`, return `false`; otherwise check both children recursively.

**Complexity:** O(n²) time, because each node recomputes O(n) heights. O(h) stack.

**C++**
```cpp
int heightOf(TreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + max(heightOf(node->left), heightOf(node->right));
}
bool isBalancedBrute(TreeNode* root) {
    if (root == nullptr) return true;
    int lh = heightOf(root->left), rh = heightOf(root->right);
    if (abs(lh - rh) > 1) return false;
    return isBalancedBrute(root->left) && isBalancedBrute(root->right);
}
```

**Java**
```java
class Solution {
    static int heightOf(TreeNode node) {
        if (node == null) return 0;
        return 1 + Math.max(heightOf(node.left), heightOf(node.right));
    }
    static boolean isBalancedBrute(TreeNode root) {
        if (root == null) return true;
        int lh = heightOf(root.left), rh = heightOf(root.right);
        if (Math.abs(lh - rh) > 1) return false;
        return isBalancedBrute(root.left) && isBalancedBrute(root.right);
    }
}
```

#### Approach 2: Optimal — the height function returns −1 for "unbalanced"
- **Combine the two checks.** Modify the O(n) height function so it returns the **height** if the subtree is balanced, and **−1** otherwise.
- **The rules:**
  - if either child returns −1, propagate −1;
  - if `|lh − rh| > 1`, return −1;
  - else return `1 + max(lh, rh)`.
- The tree is balanced iff the root's result is not −1.

**Complexity:** O(n) time, since each node is visited once. O(h) stack.

**C++**
```cpp
int dfsHeight(TreeNode* node) {
    if (node == nullptr) return 0;
    int lh = dfsHeight(node->left);
    if (lh == -1) return -1;
    int rh = dfsHeight(node->right);
    if (rh == -1) return -1;
    if (abs(lh - rh) > 1) return -1;               // unbalanced here
    return 1 + max(lh, rh);
}
bool isBalanced(TreeNode* root) {
    return dfsHeight(root) != -1;
}
```

**Java**
```java
class Solution {
    static int dfsHeight(TreeNode node) {
        if (node == null) return 0;
        int lh = dfsHeight(node.left);
        if (lh == -1) return -1;
        int rh = dfsHeight(node.right);
        if (rh == -1) return -1;
        if (Math.abs(lh - rh) > 1) return -1;
        return 1 + Math.max(lh, rh);
    }
    static boolean isBalanced(TreeNode root) {
        return dfsHeight(root) != -1;
    }
}
```

#### Key Takeaways
- To compute a property and a validity flag in one pass, return a **sentinel** (−1) from the height function. The same "piggyback on the height recursion" trick gives the diameter next.

[↑ Contents](#contents) · [← Previous](#p283) · [Next →](#p285)

---

<a id="p285"></a>

### 9. Diameter of Binary Tree

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Medium Problems | Core | No | [LeetCode](https://leetcode.com/problems/diameter-of-binary-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/diameter-of-a-binary-tree) | [Watch](https://youtu.be/Rezetez59Nk) |

#### Problem Statement
The **diameter** of a binary tree is the number of **edges** on the longest path between any two nodes. The path may or may not pass through the root.

```text
        1
       / \
      2   3
     / \
    4   5          ->  3   (4-2-1-3 or 5-2-1-3)
```

#### Intuition
- **The highest node of the path.** Any longest path has a single "highest" node. Through that node, the path goes down the left side as far as possible and down the right side as far as possible.
- **The length.** In edges, that's `lh + rh`, where `lh` and `rh` are the subtree heights counted in nodes.
- **The answer** is `max(lh + rh)` over every node.

#### Approach 1: Brute Force — compute `lh + rh` at every node (as in the video)
Traverse every node, compute its subtree heights from scratch, and track the maximum.

**Complexity:** O(n²) time, O(h) stack.

**C++**
```cpp
int heightOfNode(TreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + max(heightOfNode(node->left), heightOfNode(node->right));
}
void diaBrute(TreeNode* node, int& maxi) {
    if (node == nullptr) return;
    maxi = max(maxi, heightOfNode(node->left) + heightOfNode(node->right));
    diaBrute(node->left, maxi);
    diaBrute(node->right, maxi);
}
int diameterBrute(TreeNode* root) {
    int maxi = 0;
    diaBrute(root, maxi);
    return maxi;
}
```

**Java**
```java
class Solution {
    static int heightOfNode(TreeNode node) {
        if (node == null) return 0;
        return 1 + Math.max(heightOfNode(node.left), heightOfNode(node.right));
    }
    static int maxiB;
    static void diaBrute(TreeNode node) {
        if (node == null) return;
        maxiB = Math.max(maxiB, heightOfNode(node.left) + heightOfNode(node.right));
        diaBrute(node.left);
        diaBrute(node.right);
    }
    static int diameterBrute(TreeNode root) {
        maxiB = 0;
        diaBrute(root);
        return maxiB;
    }
}
```

#### Approach 2: Optimal — update the diameter inside the height function
The height recursion already computes `lh` and `rh` at every node. So add one line, `maxi = max(maxi, lh + rh)`, before returning `1 + max(lh, rh)`. Pass `maxi` by reference; in Java use an array or a field.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
int heightDia(TreeNode* node, int& maxi) {
    if (node == nullptr) return 0;
    int lh = heightDia(node->left, maxi);
    int rh = heightDia(node->right, maxi);
    maxi = max(maxi, lh + rh);                       // path bending at this node
    return 1 + max(lh, rh);
}
int diameterOfBinaryTree(TreeNode* root) {
    int maxi = 0;
    heightDia(root, maxi);
    return maxi;
}
```

**Java**
```java
class Solution {
    static int heightDia(TreeNode node, int[] maxi) {
        if (node == null) return 0;
        int lh = heightDia(node.left, maxi);
        int rh = heightDia(node.right, maxi);
        maxi[0] = Math.max(maxi[0], lh + rh);
        return 1 + Math.max(lh, rh);
    }
    static int diameterOfBinaryTree(TreeNode root) {
        int[] maxi = new int[1];
        heightDia(root, maxi);
        return maxi[0];
    }
}
```

#### Edge Cases & Pitfalls
- **Edges vs nodes.** LeetCode counts edges, which is `lh + rh`. Some versions (GfG) count **nodes**, which is `lh + rh + 1`.
- **The root may not be on the diameter.** That's why the maximum is taken over every node, not just the root.

#### Key Takeaways
- Diameter is max over nodes of (left height + right height). Compute it during the single height pass, using a by-reference accumulator.

[↑ Contents](#contents) · [← Previous](#p284) · [Next →](#p286)

---

<a id="p286"></a>

### 10. Maximum path sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Medium Problems | Pro | No | [LeetCode](https://leetcode.com/problems/binary-tree-maximum-path-sum/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/binary-tree-maximum-path-sum) | [Watch](https://youtu.be/WszrfSwMz58) |

#### Problem Statement
A **path** is any sequence of nodes connected by edges, with each node used at most once. It doesn't need to pass through the root, and it doesn't need to start or end at a leaf. Return the **maximum path sum**. Node values may be negative.

```text
      -10
      /  \
     9    20
         /  \
        15   7        ->  42   (15 + 20 + 7)

   -3                 ->  -3   (a single node is a valid path)
```

#### Intuition — the same template as the diameter
Every path has a highest node where it "bends". At that node, the best path through it is:

  **node.val + bestDownward(left) + bestDownward(right)**

where `bestDownward(child)` is the best sum of a path going **down** from the child. If that sum is negative, take 0: just don't extend into that side.

The recursive function **returns** the best *downward* path from a node, `node.val + max(left, right)`, because a path can continue upward through only **one** side. Meanwhile it **updates a global maximum** with the bent path, just as the diameter used `lh + rh`.

#### Approach: DFS returning the best downward sum (as in the video)
**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
int maxDown(TreeNode* node, int& maxi) {
    if (node == nullptr) return 0;
    int left = max(0, maxDown(node->left, maxi));     // drop negative branches
    int right = max(0, maxDown(node->right, maxi));
    maxi = max(maxi, node->val + left + right);       // path bending here
    return node->val + max(left, right);              // only one side can continue upward
}
int maxPathSum(TreeNode* root) {
    int maxi = INT_MIN;
    maxDown(root, maxi);
    return maxi;
}
```

**Java**
```java
class Solution {
    static int maxDown(TreeNode node, int[] maxi) {
        if (node == null) return 0;
        int left = Math.max(0, maxDown(node.left, maxi));
        int right = Math.max(0, maxDown(node.right, maxi));
        maxi[0] = Math.max(maxi[0], node.val + left + right);
        return node.val + Math.max(left, right);
    }
    static int maxPathSum(TreeNode root) {
        int[] maxi = {Integer.MIN_VALUE};
        maxDown(root, maxi);
        return maxi[0];
    }
}
```

#### Edge Cases & Pitfalls
- **All-negative trees.** Initialise `maxi` to **−∞** (`INT_MIN`), not 0. With 0, a tree of only negative values would wrongly return 0, but the answer must be the largest single node.
- **Clamping at 0.** `max(0, child)` applies only to the *branches*. The node itself is always included.

#### Key Takeaways
- Return what the parent can use (a one-sided path), and record what's optimal here (the two-sided path). This dual role is the pattern behind diameter, max path sum and similar "best path anywhere" tree problems.

[↑ Contents](#contents) · [← Previous](#p285) · [Next →](#p287)

---

<a id="p287"></a>

### 11. Check for symmetrical BTs

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Medium Problems | Core | No | [LeetCode](https://leetcode.com/problems/symmetric-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/symmetric-binary-tree) | [Watch](https://youtu.be/nKggNAiEpBE) |

#### Problem Statement
Return `true` if a binary tree is **symmetric**: a mirror image of itself around its centre.

```text
      1
     / \
    2   2
   / \ / \
  3  4 4  3     -> true

      1
     / \
    2   2
     \   \
      3   3     -> false
```

#### Intuition — the mirror property
In a mirror, your left looks at its right and your right looks at its left. Ignoring the root, the **left subtree** and the **right subtree** must mirror each other: roots equal, `left.left` mirrors `right.right`, and `left.right` mirrors `right.left`. Equivalently, a "root, left, right" walk of the left subtree must match a "root, right, left" walk of the right subtree.

#### Approach: Simultaneous mirrored recursion (as in the video)
`isMirror(a, b)`:
- if either is null, return `a == b`;
- otherwise return `a.val == b.val && isMirror(a.left, b.right) && isMirror(a.right, b.left)`.

The answer is `isMirror(root.left, root.right)`.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
bool isMirror(TreeNode* a, TreeNode* b) {
    if (a == nullptr || b == nullptr) return a == b;
    return a->val == b->val
        && isMirror(a->left, b->right)
        && isMirror(a->right, b->left);
}
bool isSymmetric(TreeNode* root) {
    return root == nullptr || isMirror(root->left, root->right);
}
```

**Java**
```java
class Solution {
    static boolean isMirror(TreeNode a, TreeNode b) {
        if (a == null || b == null) return a == b;
        return a.val == b.val && isMirror(a.left, b.right) && isMirror(a.right, b.left);
    }
    static boolean isSymmetric(TreeNode root) {
        return root == null || isMirror(root.left, root.right);
    }
}
```

#### Key Takeaways
- Symmetric is "identical trees" with one subtree mirrored: compare `left↔right` and `right↔left`.

[↑ Contents](#contents) · [← Previous](#p286) · [Next →](#p288)

---

<a id="p288"></a>

### 12. Children Sum Property in Binary Tree

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Medium Problems | Core | No | — | [Watch](https://youtu.be/fnmisPM6cVo) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
**Children Sum Property:** every node's value equals the **sum of its children's values**. Leaves are exempt; a missing child counts as 0.
1. **Check** whether a tree satisfies it.
2. **Convert** any tree so that it satisfies it, using only **increments** of node values (any node, any number of times). Decrements aren't allowed.

```text
input:         50                 after convert:       200
              /  \                                    /    \
             7    2                                 100    100
            / \  / \                               /  \   /  \
           3  5 1  30                             50  50 50  50
(every internal node now equals the sum of its children; no value decreased)
```

#### Approach 1: Check the property
Recursively verify each internal node against its children's sum.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
bool isSumProperty(TreeNode* root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) return true;
    int sum = 0;
    if (root->left) sum += root->left->val;
    if (root->right) sum += root->right->val;
    return root->val == sum && isSumProperty(root->left) && isSumProperty(root->right);
}
```

**Java**
```java
class Solution {
    static boolean isSumProperty(TreeNode root) {
        if (root == null || (root.left == null && root.right == null)) return true;
        int sum = 0;
        if (root.left != null) sum += root.left.val;
        if (root.right != null) sum += root.right.val;
        return root.val == sum && isSumProperty(root.left) && isSumProperty(root.right);
    }
}
```

#### Approach 2: Convert in O(n) — push down, then fix up
**Why the obvious fix fails.** If a node is **bigger** than its children's sum, we can't shrink the node. So we **raise the children first**, on the way down, so that their subtrees can later sum up to at least the parent.

**On the way down (preorder):**
- Let `child = left + right`, counting a missing child as 0.
- If `child ≥ node`, set `node = child`. That only increases the node.
- Else, set each existing child's value to `node`. Raising both to the node's value keeps every option open.

**Recurse** into both children.

**On the way back (postorder):** set `node = left + right` if the node has any child. The children have only grown, so this never decreases the node below its earlier value.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
void changeTree(TreeNode* root) {
    if (root == nullptr) return;
    int child = 0;
    if (root->left) child += root->left->val;
    if (root->right) child += root->right->val;
    if (child >= root->val) root->val = child;
    else {                                        // raise children so subtrees can catch up
        if (root->left) root->left->val = root->val;
        if (root->right) root->right->val = root->val;
    }
    changeTree(root->left);
    changeTree(root->right);
    int tot = 0;
    if (root->left) tot += root->left->val;
    if (root->right) tot += root->right->val;
    if (root->left || root->right) root->val = tot;   // fix up on the way back
}
```

**Java**
```java
class Solution {
    static void changeTree(TreeNode root) {
        if (root == null) return;
        int child = 0;
        if (root.left != null) child += root.left.val;
        if (root.right != null) child += root.right.val;
        if (child >= root.val) root.val = child;
        else {
            if (root.left != null) root.left.val = root.val;
            if (root.right != null) root.right.val = root.val;
        }
        changeTree(root.left);
        changeTree(root.right);
        int tot = 0;
        if (root.left != null) tot += root.left.val;
        if (root.right != null) tot += root.right.val;
        if (root.left != null || root.right != null) root.val = tot;
    }
}
```

#### Edge Cases & Pitfalls
- **Leaves keep their (possibly raised) value.** Don't overwrite them with 0 in the fix-up step.
- **Why it never decreases.** In the else-branch the node is later set to the sum of children that are each ≥ its old value, so the sum can only be equal or larger. In the if-branch the node only increases.

#### Key Takeaways
- When you may only increase values, push the constraint down first, then aggregate on the way up. That's one DFS with preorder and postorder steps.

[↑ Contents](#contents) · [← Previous](#p287) · [Next →](#p289)

---

## FAQs

<a id="p289"></a>

### 13. Zig Zag or Spiral Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/) | [Watch](https://youtu.be/3OXWEdlIGl4) |

#### Problem Statement
Return the **zig-zag level order** traversal: level 0 left→right, level 1 right→left, level 2 left→right, and so on.

```text
        1
       / \
      2   3
     / \   \
    4   5   6        ->  [[1], [3, 2], [4, 5, 6]]
```

#### Approach: Level-order BFS + a direction flag (as in the video)
Run the normal level-order BFS. Keep a flag `leftToRight`, starting `true`. For each level of size `s`, allocate `row(s)` and place the `i`-th popped node at:
- `i` if the flag says left to right;
- `s − 1 − i` if it says right to left.

Flip the flag after each level. This avoids reversing anything.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (root == nullptr) return ans;
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    while (!q.empty()) {
        int size = q.size();
        vector<int> row(size);
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            int idx = leftToRight ? i : size - 1 - i;    // place according to direction
            row[idx] = node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        leftToRight = !leftToRight;                       // flip after every level
        ans.push_back(row);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root == null) return ans;
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        boolean leftToRight = true;
        while (!q.isEmpty()) {
            int size = q.size();
            Integer[] row = new Integer[size];
            for (int i = 0; i < size; i++) {
                TreeNode node = q.remove();
                int idx = leftToRight ? i : size - 1 - i;
                row[idx] = node.val;
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
            leftToRight = !leftToRight;
            ans.add(Arrays.asList(row));
        }
        return ans;
    }
}
```

#### Key Takeaways
- Zig-zag is level order plus a direction flag. Writing each value into its final index is cleaner than reversing alternate levels.

[↑ Contents](#contents) · [← Previous](#p288) · [Next →](#p290)

---

<a id="p290"></a>

### 14. Boundary Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Core | Yes | [LeetCode](https://leetcode.com/problems/boundary-of-binary-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/boundary-traversal-of-a-binary-tree) | [Watch](https://youtu.be/0ca1nvR0be4) |

#### Problem Statement
Return the **anticlockwise boundary traversal** of a binary tree:
1. the **root**;
2. the **left boundary**, top to bottom, **excluding leaves**;
3. all **leaves**, left to right;
4. the **right boundary**, bottom to top, **excluding leaves**.

```text
            1
          /   \
         2     7
        /       \
       3         8
        \       /
         4     9
        / \   / \
       5   6 10  11     ->  [1, 2, 3, 4, 5, 6, 10, 11, 9, 8, 7]
```

#### Approach: Three helper traversals (as in the video)
- **Left boundary:** start at `root.left`. While the node isn't a leaf, record it, then move to its **left** child if it exists, otherwise to its **right** child.
- **Leaves:** any DFS order that visits left before right (preorder or inorder) and records only leaves.
- **Right boundary:** start at `root.right`. While the node isn't a leaf, record it, then move to its **right** child if it exists, otherwise to its **left**. Record these into a temporary list and append it **reversed**.
- **The root** is added first, unless it is itself a leaf, in which case the leaf step adds it.

**Complexity:** O(n) time: the boundaries cost O(h) and the leaves O(n). O(h) space besides the output.

**C++**
```cpp
bool isLeaf(TreeNode* n) { return n->left == nullptr && n->right == nullptr; }
void addLeftBoundary(TreeNode* root, vector<int>& res) {
    TreeNode* cur = root->left;
    while (cur) {
        if (!isLeaf(cur)) res.push_back(cur->val);
        cur = cur->left ? cur->left : cur->right;
    }
}
void addLeaves(TreeNode* node, vector<int>& res) {
    if (isLeaf(node)) { res.push_back(node->val); return; }
    if (node->left) addLeaves(node->left, res);
    if (node->right) addLeaves(node->right, res);
}
void addRightBoundary(TreeNode* root, vector<int>& res) {
    TreeNode* cur = root->right;
    vector<int> tmp;
    while (cur) {
        if (!isLeaf(cur)) tmp.push_back(cur->val);
        cur = cur->right ? cur->right : cur->left;
    }
    for (int i = (int)tmp.size() - 1; i >= 0; i--) res.push_back(tmp[i]);   // reversed
}
vector<int> boundaryTraversal(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) return res;
    if (!isLeaf(root)) res.push_back(root->val);
    addLeftBoundary(root, res);
    addLeaves(root, res);
    addRightBoundary(root, res);
    return res;
}
```

**Java**
```java
class Solution {
    static boolean isLeaf(TreeNode n) { return n.left == null && n.right == null; }
    static void addLeftBoundary(TreeNode root, List<Integer> res) {
        TreeNode cur = root.left;
        while (cur != null) {
            if (!isLeaf(cur)) res.add(cur.val);
            cur = (cur.left != null) ? cur.left : cur.right;
        }
    }
    static void addLeaves(TreeNode node, List<Integer> res) {
        if (isLeaf(node)) { res.add(node.val); return; }
        if (node.left != null) addLeaves(node.left, res);
        if (node.right != null) addLeaves(node.right, res);
    }
    static void addRightBoundary(TreeNode root, List<Integer> res) {
        TreeNode cur = root.right;
        List<Integer> tmp = new ArrayList<>();
        while (cur != null) {
            if (!isLeaf(cur)) tmp.add(cur.val);
            cur = (cur.right != null) ? cur.right : cur.left;
        }
        for (int i = tmp.size() - 1; i >= 0; i--) res.add(tmp.get(i));
    }
    static List<Integer> boundaryTraversal(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        if (root == null) return res;
        if (!isLeaf(root)) res.add(root.val);
        addLeftBoundary(root, res);
        addLeaves(root, res);
        addRightBoundary(root, res);
        return res;
    }
}
```

#### Edge Cases & Pitfalls
- **Excluding leaves** from both boundaries prevents them from being printed twice.
- **A root with no left child** has an empty left boundary. The root itself is not part of it.
- **Clockwise variant:** root, then the right boundary top-down, then the leaves right-to-left, then the left boundary bottom-up.

#### Key Takeaways
- Break a composite traversal into simple pieces (left edge, leaves, reversed right edge) and concatenate them.

[↑ Contents](#contents) · [← Previous](#p289) · [Next →](#p291)

---

<a id="p291"></a>

### 15. Vertical Order Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/vertical-order-traversal-of-a-binary-tree) | [Watch](https://youtu.be/q_a6lpbKJdw) |

#### Problem Statement
Assign every node coordinates: the root is at **(vertical 0, level 0)**, a left child at `(v − 1, level + 1)` and a right child at `(v + 1, level + 1)`. Return the nodes column by column, from the left-most vertical to the right-most. Within a column, order by **level**, and break ties at the same level and vertical (overlapping nodes) by **value**.

```text
          1
        /   \
       2     3
      / \   / \
     4   10 9  10
      \
       5
        \
         6        ->  [[4], [2, 5], [1, 9, 10, 6], [3], [10]]
   (vertical 0 has 1 (level 0), then 9 and 10 overlapping at level 2 in sorted order, then 6 at level 4)
```

#### Approach: BFS with (node, vertical, level) + nested sorted maps (as in the video)
Store `nodes[vertical][level] = multiset of values`:
- an ordered outer map sorts the verticals;
- an ordered inner map sorts the levels;
- a multiset sorts overlapping values and keeps duplicates.

Fill it with BFS or DFS carrying `(node, v, level)`. Then read it out column by column.

**Complexity:** O(n log n) time for the ordered-map and multiset insertions. O(n) space.

**C++**
```cpp
vector<vector<int>> verticalTraversal(TreeNode* root) {
    map<int, map<int, multiset<int>>> nodes;              // vertical -> level -> values
    queue<pair<TreeNode*, pair<int, int>>> q;             // node, {vertical, level}
    if (root) q.push({root, {0, 0}});
    while (!q.empty()) {
        auto [node, vl] = q.front(); q.pop();
        int v = vl.first, lvl = vl.second;
        nodes[v][lvl].insert(node->val);
        if (node->left) q.push({node->left, {v - 1, lvl + 1}});
        if (node->right) q.push({node->right, {v + 1, lvl + 1}});
    }
    vector<vector<int>> ans;
    for (auto& [v, levels] : nodes) {
        vector<int> col;
        for (auto& [lvl, vals] : levels) col.insert(col.end(), vals.begin(), vals.end());
        ans.push_back(col);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> verticalTraversal(TreeNode root) {
        TreeMap<Integer, TreeMap<Integer, PriorityQueue<Integer>>> nodes = new TreeMap<>();
        Queue<Object[]> q = new LinkedList<>();               // {node, vertical, level}
        if (root != null) q.add(new Object[]{root, 0, 0});
        while (!q.isEmpty()) {
            Object[] cur = q.remove();
            TreeNode node = (TreeNode) cur[0];
            int v = (Integer) cur[1], lvl = (Integer) cur[2];
            nodes.computeIfAbsent(v, k -> new TreeMap<>())
                 .computeIfAbsent(lvl, k -> new PriorityQueue<>())
                 .add(node.val);
            if (node.left != null) q.add(new Object[]{node.left, v - 1, lvl + 1});
            if (node.right != null) q.add(new Object[]{node.right, v + 1, lvl + 1});
        }
        List<List<Integer>> ans = new ArrayList<>();
        for (TreeMap<Integer, PriorityQueue<Integer>> levels : nodes.values()) {
            List<Integer> col = new ArrayList<>();
            for (PriorityQueue<Integer> pq : levels.values())
                while (!pq.isEmpty()) col.add(pq.poll());
            ans.add(col);
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Use a multiset, not a set.** Overlapping nodes can have equal values, and both must appear.
- **LeetCode 987 sorts overlapping nodes by value.** Some GfG versions keep BFS order instead; for those, use a plain list per vertical filled in BFS order.

#### Key Takeaways
- Attach coordinates to nodes during traversal and let ordered containers do the sorting. Top view and bottom view (next) are simplified versions.

[↑ Contents](#contents) · [← Previous](#p290) · [Next →](#p292)

---

<a id="p292"></a>

### 16. Top View of BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/top-view-of-binary-tree) | [Watch](https://youtu.be/Et9OCDNvJ78) |

#### Problem Statement
Return the **top view** of a binary tree: the nodes visible when looking from above, ordered from the left-most vertical to the right-most. On each vertical line, the **topmost** node is visible.

```text
          1
        /   \
       2     3
      / \   / \
     4   5 6   7       ->  [4, 2, 1, 3, 7]   (5 and 6 are hidden under 1)
```

#### Approach: Level-order BFS with verticals + an ordered map (as in the video)
- **Coordinates.** Assign verticals as in Vertical Order Traversal: root 0, left −1, right +1.
- **Why BFS.** It visits nodes **top to bottom**, so the **first** node seen on each vertical is the topmost. Insert into `map[v]` only if `v` isn't already present.
- **Why an ordered map.** It returns the verticals left to right. Don't use `unordered_map`.

The video explains why it doesn't use recursion: a DFS can reach a deeper node on a vertical before a shallower one. Making DFS work requires tracking levels too.

**Complexity:** O(n log n) time with an ordered map; O(n) if you track min/max verticals with an array instead. O(n) space.

**C++**
```cpp
vector<int> topView(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    map<int, int> mpp;                                   // vertical -> topmost value
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [node, v] = q.front(); q.pop();
        if (mpp.find(v) == mpp.end()) mpp[v] = node->val;   // first seen = topmost
        if (node->left) q.push({node->left, v - 1});
        if (node->right) q.push({node->right, v + 1});
    }
    for (auto& [v, val] : mpp) ans.push_back(val);
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> topView(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;
        TreeMap<Integer, Integer> mpp = new TreeMap<>();
        Queue<Object[]> q = new LinkedList<>();
        q.add(new Object[]{root, 0});
        while (!q.isEmpty()) {
            Object[] cur = q.remove();
            TreeNode node = (TreeNode) cur[0];
            int v = (Integer) cur[1];
            mpp.putIfAbsent(v, node.val);
            if (node.left != null) q.add(new Object[]{node.left, v - 1});
            if (node.right != null) q.add(new Object[]{node.right, v + 1});
        }
        ans.addAll(mpp.values());
        return ans;
    }
}
```

#### Key Takeaways
- Top view is BFS plus "first node per vertical".

[↑ Contents](#contents) · [← Previous](#p291) · [Next →](#p293)

---

<a id="p293"></a>

### 17. Bottom view of BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/bottom-view-of-binary-tree) | [Watch](https://youtu.be/0FtVY6I4pB8) |

#### Problem Statement
Return the **bottom view**: for each vertical line from left to right, the **bottom-most** node. When nodes overlap at the same depth, take the **later** one in level order, i.e. the right-most.

```text
          20
         /  \
        8    22
       / \     \
      5   3     25
         / \
        10  14        ->  [5, 10, 3, 14, 25]
```

#### Approach: BFS with verticals; overwrite on every visit (as in the video)
This is identical to the top view, except you **always overwrite** `map[v] = node.val`. BFS goes top to bottom and left to right within a level, so the **last** write on each vertical is the bottom-most node, with the right-most winning ties.

**Complexity:** O(n log n) time, O(n) space.

**C++**
```cpp
vector<int> bottomView(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    map<int, int> mpp;                                   // vertical -> last seen value
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [node, v] = q.front(); q.pop();
        mpp[v] = node->val;                              // keep replacing
        if (node->left) q.push({node->left, v - 1});
        if (node->right) q.push({node->right, v + 1});
    }
    for (auto& [v, val] : mpp) ans.push_back(val);
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> bottomView(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;
        TreeMap<Integer, Integer> mpp = new TreeMap<>();
        Queue<Object[]> q = new LinkedList<>();
        q.add(new Object[]{root, 0});
        while (!q.isEmpty()) {
            Object[] cur = q.remove();
            TreeNode node = (TreeNode) cur[0];
            int v = (Integer) cur[1];
            mpp.put(v, node.val);
            if (node.left != null) q.add(new Object[]{node.left, v - 1});
            if (node.right != null) q.add(new Object[]{node.right, v + 1});
        }
        ans.addAll(mpp.values());
        return ans;
    }
}
```

#### Key Takeaways
- Bottom view is BFS plus "last node per vertical". Top and bottom views differ by a single condition.

[↑ Contents](#contents) · [← Previous](#p292) · [Next →](#p294)

---

<a id="p294"></a>

### 18. Right/Left View of BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/binary-tree-right-side-view/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/left-and-right-views-of-a-binary-tree) | [Watch](https://youtu.be/KV4mRzTjlAk) |

#### Problem Statement
Return the **right view** of a binary tree: the last node of each level, top to bottom. The **left view** is the first node of each level.

```text
        1
       / \
      2   3
     / \   \
    4   5   7
       /
      6           right view = [1, 3, 7, 6],  left view = [1, 2, 4, 6]
```

#### Approach 1: Level-order traversal — take the last node of each level
**Complexity:** O(n) time, O(n) space. The video points out that the queue can hold a whole level, about n/2 nodes for a complete tree.

**C++**
```cpp
vector<int> rightSideViewBFS(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            if (i == size - 1) ans.push_back(node->val);    // last of the level
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> rightSideViewBFS(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        while (!q.isEmpty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode node = q.remove();
                if (i == size - 1) ans.add(node.val);
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
        }
        return ans;
    }
}
```

#### Approach 2: Recursive — reverse preorder (root, right, left) (as in the video)
- **Visit right before left.** In **root → right → left** order, the first node reached at each level is that level's right-most node.
- **Record the first visit per level.** Record a node when `level == ans.size()`, which is true exactly once per level.
- **Left view.** Use normal preorder (root → left → right) with the same check.

**Complexity:** O(n) time. O(h) stack, which is better than BFS on balanced trees.

**C++**
```cpp
void rightView(TreeNode* node, int level, vector<int>& ans) {
    if (node == nullptr) return;
    if (level == (int)ans.size()) ans.push_back(node->val);   // first time at this level
    rightView(node->right, level + 1, ans);
    rightView(node->left, level + 1, ans);
}
vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    rightView(root, 0, ans);
    return ans;
}
void leftView(TreeNode* node, int level, vector<int>& ans) {
    if (node == nullptr) return;
    if (level == (int)ans.size()) ans.push_back(node->val);
    leftView(node->left, level + 1, ans);
    leftView(node->right, level + 1, ans);
}
vector<int> leftSideView(TreeNode* root) {
    vector<int> ans;
    leftView(root, 0, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    static void rightView(TreeNode node, int level, List<Integer> ans) {
        if (node == null) return;
        if (level == ans.size()) ans.add(node.val);
        rightView(node.right, level + 1, ans);
        rightView(node.left, level + 1, ans);
    }
    static List<Integer> rightSideView(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        rightView(root, 0, ans);
        return ans;
    }
    static void leftView(TreeNode node, int level, List<Integer> ans) {
        if (node == null) return;
        if (level == ans.size()) ans.add(node.val);
        leftView(node.left, level + 1, ans);
        leftView(node.right, level + 1, ans);
    }
    static List<Integer> leftSideView(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        leftView(root, 0, ans);
        return ans;
    }
}
```

#### Key Takeaways
- "First node seen at each depth" in the right DFS order gives the side views. `level == ans.size()` is the neat test for "new level".

[↑ Contents](#contents) · [← Previous](#p293) · [Next →](#p295)

---

<a id="p295"></a>

### 19. Print root to leaf path in BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/print-root-to-leaf-path-in-binary-tree) | [Watch](https://youtu.be/fmflMqVOC7k) |

#### Problem Statement
Two related tasks:
1. **Root-to-node path** (the video's problem): given a target value, return the path from the root to that node.
2. **All root-to-leaf paths** (the sheet's title): return every path from the root to a leaf.

```text
        1
       / \
      2   3
     / \
    4   5
   / \
  6   7
path to 7 = [1, 2, 4, 7];   root-to-leaf paths = [[1,2,4,6], [1,2,4,7], [1,2,5], [1,3]]
```

#### Approach 1: Root-to-node path — DFS with backtracking (as in the video)
`getPath(node, target, path)`:
- if `node` is null, return `false`;
- **push** `node`;
- if `node` is the target, return `true`;
- if the left **or** right recursion returns `true`, return `true`, because the path is complete;
- otherwise **pop** `node` (it's not on the path) and return `false`.

**Complexity:** O(n) time, O(h) space.

**C++**
```cpp
bool getPath(TreeNode* node, int target, vector<int>& path) {
    if (node == nullptr) return false;
    path.push_back(node->val);
    if (node->val == target) return true;
    if (getPath(node->left, target, path) || getPath(node->right, target, path)) return true;
    path.pop_back();                                 // not on this branch: backtrack
    return false;
}
vector<int> rootToNodePath(TreeNode* root, int target) {
    vector<int> path;
    if (!getPath(root, target, path)) path.clear();
    return path;
}
```

**Java**
```java
class Solution {
    static boolean getPath(TreeNode node, int target, List<Integer> path) {
        if (node == null) return false;
        path.add(node.val);
        if (node.val == target) return true;
        if (getPath(node.left, target, path) || getPath(node.right, target, path)) return true;
        path.remove(path.size() - 1);
        return false;
    }
    static List<Integer> rootToNodePath(TreeNode root, int target) {
        List<Integer> path = new ArrayList<>();
        if (!getPath(root, target, path)) path.clear();
        return path;
    }
}
```

#### Approach 2: All root-to-leaf paths — the same backtracking, recording at leaves
Push the node. If it's a leaf, copy the current path into the answer. Recurse into both children, then pop.

**Complexity:** O(n · h) time, because copying each path costs O(h). O(h) recursion space plus the output.

**C++**
```cpp
void allPaths(TreeNode* node, vector<int>& path, vector<vector<int>>& ans) {
    if (node == nullptr) return;
    path.push_back(node->val);
    if (node->left == nullptr && node->right == nullptr) ans.push_back(path);
    allPaths(node->left, path, ans);
    allPaths(node->right, path, ans);
    path.pop_back();
}
vector<vector<int>> rootToLeafPaths(TreeNode* root) {
    vector<vector<int>> ans;
    vector<int> path;
    allPaths(root, path, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    static void allPaths(TreeNode node, List<Integer> path, List<List<Integer>> ans) {
        if (node == null) return;
        path.add(node.val);
        if (node.left == null && node.right == null) ans.add(new ArrayList<>(path));
        allPaths(node.left, path, ans);
        allPaths(node.right, path, ans);
        path.remove(path.size() - 1);
    }
    static List<List<Integer>> rootToLeafPaths(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        allPaths(root, new ArrayList<>(), ans);
        return ans;
    }
}
```

#### Key Takeaways
- Push on entry and pop on exit (backtracking). Returning `true` early stops the search once the target is found. Root-to-node paths are also a brute force for LCA.

[↑ Contents](#contents) · [← Previous](#p294) · [Next →](#p296)

---

<a id="p296"></a>

### 20. Lowest Common Ancestor in BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/lowest-common-ancestor-in-a-binary-tree) | [Watch](https://youtu.be/_-QHfMDde90) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Given a binary tree and two nodes `p` and `q`, return their **lowest common ancestor (LCA)**: the deepest node that has both `p` and `q` as descendants. A node counts as a descendant of itself.

```text
            3
          /   \
         5     1
        / \   / \
       6   2 0   8
          / \
         7   4
LCA(5, 1) = 3;   LCA(5, 4) = 5;   LCA(7, 4) = 2
```

#### Approach 1: Brute Force — compare root-to-node paths
Find the root-to-`p` path and the root-to-`q` path (see "Print root to node path"). Walk both from the root. The **last common node** is the LCA.

**Complexity:** O(n) time, plus O(n) space for the two paths in the worst case.

**C++**
```cpp
bool pathTo(TreeNode* node, TreeNode* target, vector<TreeNode*>& path) {
    if (node == nullptr) return false;
    path.push_back(node);
    if (node == target) return true;
    if (pathTo(node->left, target, path) || pathTo(node->right, target, path)) return true;
    path.pop_back();
    return false;
}
TreeNode* lcaBrute(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> a, b;
    pathTo(root, p, a);
    pathTo(root, q, b);
    TreeNode* lca = nullptr;
    for (size_t i = 0; i < a.size() && i < b.size() && a[i] == b[i]; i++) lca = a[i];
    return lca;
}
```

**Java**
```java
class Solution {
    static boolean pathTo(TreeNode node, TreeNode target, List<TreeNode> path) {
        if (node == null) return false;
        path.add(node);
        if (node == target) return true;
        if (pathTo(node.left, target, path) || pathTo(node.right, target, path)) return true;
        path.remove(path.size() - 1);
        return false;
    }
    static TreeNode lcaBrute(TreeNode root, TreeNode p, TreeNode q) {
        List<TreeNode> a = new ArrayList<>(), b = new ArrayList<>();
        pathTo(root, p, a);
        pathTo(root, q, b);
        TreeNode lca = null;
        for (int i = 0; i < a.size() && i < b.size() && a.get(i) == b.get(i); i++) lca = a.get(i);
        return lca;
    }
}
```

#### Approach 2: Optimal — single DFS returning "found" nodes
`lca(node)`:
- if `node` is null, or `node` is `p` or `q`, return `node`;
- `left = lca(node.left)`, `right = lca(node.right)`;
- if **both** are non-null, `p` and `q` were found in different subtrees, so `node` is the LCA;
- otherwise return whichever side is non-null (or null if neither is).

Returning `node` as soon as it matches `p` covers the case where `q` lies below `p`: then `p` itself is the LCA.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    return root;                                   // p and q on different sides
}
```

**Java**
```java
class Solution {
    static TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null || root == p || root == q) return root;
        TreeNode left = lowestCommonAncestor(root.left, p, q);
        TreeNode right = lowestCommonAncestor(root.right, p, q);
        if (left == null) return right;
        if (right == null) return left;
        return root;
    }
}
```

#### Edge Cases & Pitfalls
- **Both nodes must exist.** The optimal version assumes `p` and `q` are both in the tree, as LeetCode guarantees. If one might be missing, verify separately.

#### Key Takeaways
- "Split point" recursion: the LCA is the first node where `p` and `q` come from different subtrees.

[↑ Contents](#contents) · [← Previous](#p295) · [Next →](#p297)

---

<a id="p297"></a>

### 21. Maximum Width of BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/maximum-width-of-binary-tree/) | [Watch](https://youtu.be/ZbybYvcVLks) |

#### Problem Statement
The **width** of a level is the number of positions between its left-most and right-most non-null nodes, **including the null gaps** in between, as if the tree were complete. Return the **maximum width** over all levels.

```text
          1
         / \
        3   2
       /     \
      5       9
     /         \
    6           7        ->  8   (last level: positions 0 ... 7)
```

#### Intuition — index the nodes like a heap
- **Heap indexing.** With 0-based indexing, a node at index `i` has children at `2i + 1` and `2i + 2`. Positions now count the gaps.
- **Width of a level.** It's `lastIndex − firstIndex + 1`.
- **Avoiding overflow.** Indices double every level and overflow quickly on a deep, skewed tree. The fix from the video: **subtract the minimum index of the level** before computing children, so each level's indices start from 0.

#### Approach: BFS with (node, index), normalised per level (as in the video)
For each level:
- `mmin` = the index of the first node in the queue;
- for each node, `cur = idx − mmin`;
- the first and last `cur` give the width;
- push the children with `2·cur + 1` and `2·cur + 2`.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int widthOfBinaryTree(TreeNode* root) {
    if (root == nullptr) return 0;
    long long ans = 0;
    queue<pair<TreeNode*, long long>> q;
    q.push({root, 0});
    while (!q.empty()) {
        int size = q.size();
        long long mmin = q.front().second;          // normalise to avoid overflow
        long long first = 0, last = 0;
        for (int i = 0; i < size; i++) {
            auto [node, idx] = q.front(); q.pop();
            long long cur = idx - mmin;
            if (i == 0) first = cur;
            if (i == size - 1) last = cur;
            if (node->left) q.push({node->left, 2 * cur + 1});
            if (node->right) q.push({node->right, 2 * cur + 2});
        }
        ans = max(ans, last - first + 1);
    }
    return (int)ans;
}
```

**Java**
```java
class Solution {
    static int widthOfBinaryTree(TreeNode root) {
        if (root == null) return 0;
        long ans = 0;
        Queue<Object[]> q = new LinkedList<>();
        q.add(new Object[]{root, 0L});
        while (!q.isEmpty()) {
            int size = q.size();
            long mmin = (Long) q.peek()[1];
            long first = 0, last = 0;
            for (int i = 0; i < size; i++) {
                Object[] cur0 = q.remove();
                TreeNode node = (TreeNode) cur0[0];
                long cur = (Long) cur0[1] - mmin;
                if (i == 0) first = cur;
                if (i == size - 1) last = cur;
                if (node.left != null) q.add(new Object[]{node.left, 2 * cur + 1});
                if (node.right != null) q.add(new Object[]{node.right, 2 * cur + 2});
            }
            ans = Math.max(ans, last - first + 1);
        }
        return (int) ans;
    }
}
```

#### Key Takeaways
- Width counts phantom null positions, so use heap indices. Re-basing indices each level keeps them small.

[↑ Contents](#contents) · [← Previous](#p296) · [Next →](#p298)

---

<a id="p298"></a>

### 22. Print all nodes at a distance of K in BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/nodes-distance-k-binary-tree) | [Watch](https://youtu.be/i9ORlEy6EsI) |

#### Problem Statement
Given a binary tree, a `target` node and an integer `k`, return all nodes at **distance `k`** (in edges) from the target.

```text
            3
          /   \
         5     1
        / \   / \
       6   2 0   8
          / \
         7   4         target = 5, k = 2  ->  [7, 4, 1]
```

#### Intuition — make the tree an undirected graph
Distance can go **up** through parents as well as down. Trees only have child pointers, so first record **parent pointers** in a hash map. Then BFS from the target, moving to `left`, `right` and `parent`. Use a `visited` set so you never walk back. After `k` levels, the queue holds the answer.

#### Approach: Parent map + BFS from the target (as in the video)
**Complexity:** O(n) to build the parents plus O(n) for the BFS, so O(2n) time. O(n) space for the map, the visited set and the queue.

**C++**
```cpp
void markParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parent) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (node->left) { parent[node->left] = node; q.push(node->left); }
        if (node->right) { parent[node->right] = node; q.push(node->right); }
    }
}
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    unordered_map<TreeNode*, TreeNode*> parent;
    markParents(root, parent);
    unordered_set<TreeNode*> visited;
    queue<TreeNode*> q;
    q.push(target);
    visited.insert(target);
    int dist = 0;
    while (!q.empty() && dist < k) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            for (TreeNode* nxt : {node->left, node->right, parent.count(node) ? parent[node] : nullptr}) {
                if (nxt && !visited.count(nxt)) { visited.insert(nxt); q.push(nxt); }
            }
        }
        dist++;
    }
    vector<int> ans;
    while (!q.empty()) { ans.push_back(q.front()->val); q.pop(); }
    return ans;
}
```

**Java**
```java
class Solution {
    static void markParents(TreeNode root, Map<TreeNode, TreeNode> parent) {
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        while (!q.isEmpty()) {
            TreeNode node = q.remove();
            if (node.left != null) { parent.put(node.left, node); q.add(node.left); }
            if (node.right != null) { parent.put(node.right, node); q.add(node.right); }
        }
    }
    static List<Integer> distanceK(TreeNode root, TreeNode target, int k) {
        Map<TreeNode, TreeNode> parent = new HashMap<>();
        markParents(root, parent);
        Set<TreeNode> visited = new HashSet<>();
        Queue<TreeNode> q = new LinkedList<>();
        q.add(target);
        visited.add(target);
        int dist = 0;
        while (!q.isEmpty() && dist < k) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode node = q.remove();
                for (TreeNode nxt : new TreeNode[]{node.left, node.right, parent.get(node)}) {
                    if (nxt != null && !visited.contains(nxt)) { visited.add(nxt); q.add(nxt); }
                }
            }
            dist++;
        }
        List<Integer> ans = new ArrayList<>();
        for (TreeNode node : q) ans.add(node.val);
        return ans;
    }
}
```

#### Key Takeaways
- Anything involving distance "up and down" a tree calls for parent pointers, which turn the tree into a graph. Then BFS level by level. The same machinery solves "burn the tree" next.

[↑ Contents](#contents) · [← Previous](#p297) · [Next →](#p299)

---

<a id="p299"></a>

### 23. Minimum time taken to burn the BT from a given Node

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Pro | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/minimum-time-burn-binary-tree) | [Watch](https://youtu.be/2r5wLmQfD6g) |

#### Problem Statement
Fire starts at a given node and spreads every second to all **adjacent** nodes: left child, right child and parent. Return the **minimum time** to burn the whole tree.

```text
          1
         / \
        2   3
       /   / \
      4   5   6
       \
        7          start = 2  ->  3  (t1: 1,4,  t2: 3,7,  t3: 5,6)
```

#### Approach: Parent map + BFS by levels; count the levels (as in the video)
- Build parent pointers with a BFS, finding the start node by value along the way.
- BFS from the start, moving to left, right and parent with a visited set.
- Each BFS level is one second. Increment the timer **only if the level burned at least one new node**.

The answer is the number of such levels.

**Complexity:** O(2n) time, O(n) space.

**C++**
```cpp
int amountOfTime(TreeNode* root, int start) {
    unordered_map<TreeNode*, TreeNode*> parent;
    TreeNode* src = nullptr;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {                              // parent pointers + locate start
        TreeNode* node = q.front(); q.pop();
        if (node->val == start) src = node;
        if (node->left) { parent[node->left] = node; q.push(node->left); }
        if (node->right) { parent[node->right] = node; q.push(node->right); }
    }
    unordered_set<TreeNode*> visited;
    q.push(src);
    visited.insert(src);
    int time = 0;
    while (!q.empty()) {
        int size = q.size();
        bool burned = false;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            for (TreeNode* nxt : {node->left, node->right, parent.count(node) ? parent[node] : nullptr}) {
                if (nxt && !visited.count(nxt)) { visited.insert(nxt); q.push(nxt); burned = true; }
            }
        }
        if (burned) time++;
    }
    return time;
}
```

**Java**
```java
class Solution {
    static int amountOfTime(TreeNode root, int start) {
        Map<TreeNode, TreeNode> parent = new HashMap<>();
        TreeNode src = null;
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        while (!q.isEmpty()) {
            TreeNode node = q.remove();
            if (node.val == start) src = node;
            if (node.left != null) { parent.put(node.left, node); q.add(node.left); }
            if (node.right != null) { parent.put(node.right, node); q.add(node.right); }
        }
        Set<TreeNode> visited = new HashSet<>();
        q.add(src);
        visited.add(src);
        int time = 0;
        while (!q.isEmpty()) {
            int size = q.size();
            boolean burned = false;
            for (int i = 0; i < size; i++) {
                TreeNode node = q.remove();
                for (TreeNode nxt : new TreeNode[]{node.left, node.right, parent.get(node)}) {
                    if (nxt != null && !visited.contains(nxt)) { visited.add(nxt); q.add(nxt); burned = true; }
                }
            }
            if (burned) time++;
        }
        return time;
    }
}
```

#### Key Takeaways
- Burn time is the BFS eccentricity of the start node in the undirected tree: the same parent-pointer BFS as distance-K, counting levels instead of collecting them.

[↑ Contents](#contents) · [← Previous](#p298) · [Next →](#p300)

---

<a id="p300"></a>

### 24. Count total nodes in a complete BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/count-complete-tree-nodes/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-nodes-in-a-complete-binary-tree) | [Watch](https://youtu.be/u-yWemKGWO0) |

#### Problem Statement
Count the nodes of a **complete** binary tree, where every level except possibly the last is full and the last level is filled from the left, in **less than O(n)** time.

```text
        1
       / \
      2   3
     / \  /
    4  5 6        ->  6
```

#### Approach 1: Brute Force — any traversal
Count every node, e.g. with an inorder traversal.

**Complexity:** O(n) time. O(log n) stack, because a complete tree has height log n.

**C++**
```cpp
int countNodesBrute(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodesBrute(root->left) + countNodesBrute(root->right);
}
```

**Java**
```java
class Solution {
    static int countNodesBrute(TreeNode root) {
        if (root == null) return 0;
        return 1 + countNodesBrute(root.left) + countNodesBrute(root.right);
    }
}
```

#### Approach 2: Optimal — perfect subtrees have 2ʰ − 1 nodes
- **Measure both edges.** Compute the **left height** by walking left edges only, and the **right height** by walking right edges only.
- **Equal heights mean a perfect subtree.** It then has exactly **2ʰ − 1** nodes, and we return that without traversing it.
- **Otherwise recurse.** Return `1 + count(left) + count(right)`. In a complete tree, at least one of the two children is perfect, so each step down does O(log n) work and the recursion has depth O(log n).

**Complexity:** O((log n)²) time, O(log n) stack.

**C++**
```cpp
int leftHeight(TreeNode* node) {
    int h = 0;
    while (node) { h++; node = node->left; }
    return h;
}
int rightHeight(TreeNode* node) {
    int h = 0;
    while (node) { h++; node = node->right; }
    return h;
}
int countNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    int lh = leftHeight(root), rh = rightHeight(root);
    if (lh == rh) return (1 << lh) - 1;           // perfect subtree
    return 1 + countNodes(root->left) + countNodes(root->right);
}
```

**Java**
```java
class Solution {
    static int leftHeight(TreeNode node) {
        int h = 0;
        while (node != null) { h++; node = node.left; }
        return h;
    }
    static int rightHeight(TreeNode node) {
        int h = 0;
        while (node != null) { h++; node = node.right; }
        return h;
    }
    static int countNodes(TreeNode root) {
        if (root == null) return 0;
        int lh = leftHeight(root), rh = rightHeight(root);
        if (lh == rh) return (1 << lh) - 1;
        return 1 + countNodes(root.left) + countNodes(root.right);
    }
}
```

#### Key Takeaways
- Exploit the shape guarantee: equal left and right spine heights mean a perfect tree, which has a closed-form count.

[↑ Contents](#contents) · [← Previous](#p299) · [Next →](#p301)

---

<a id="p301"></a>

### 25. Flatten Binary Tree to Linked List

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/flatten-binary-tree-to-linked-list) | [Watch](https://youtu.be/sWf7k1x9XR4) |

#### Problem Statement
Flatten a binary tree **in place** into a "linked list" that uses the `right` pointers, in **preorder** order, with every `left` set to null.

```text
      1
     / \
    2   5
   / \   \
  3   4   6        ->  1 -> 2 -> 3 -> 4 -> 5 -> 6   (all via right pointers)
```

#### Approach 1: Recursive — reverse postorder with a `prev` pointer (as in the video)
Traverse in **right → left → root** order, a reverse postorder, keeping `prev`, the previously processed node:
- set `node.right = prev` and `node.left = null`;
- then `prev = node`.

Because the nodes are processed in exactly the **reverse** of preorder, each node gets linked to its preorder successor.

**Complexity:** O(n) time, O(h) stack.

**C++**
```cpp
void flattenRec(TreeNode* node, TreeNode*& prev) {
    if (node == nullptr) return;
    flattenRec(node->right, prev);
    flattenRec(node->left, prev);
    node->right = prev;                     // link to preorder successor
    node->left = nullptr;
    prev = node;
}
void flattenRecursive(TreeNode* root) {
    TreeNode* prev = nullptr;
    flattenRec(root, prev);
}
```

**Java**
```java
class Solution {
    static TreeNode prev;
    static void flattenRec(TreeNode node) {
        if (node == null) return;
        flattenRec(node.right);
        flattenRec(node.left);
        node.right = prev;
        node.left = null;
        prev = node;
    }
    static void flattenRecursive(TreeNode root) {
        prev = null;
        flattenRec(root);
    }
}
```

#### Approach 2: Iterative — stack (as in the video)
- Push the root. Pop a node, then push its **right** child followed by its **left** child, so left is processed first, as in preorder.
- Set `node.right = st.top()`, the next node in preorder (if the stack is non-empty), and `node.left = null`.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
void flattenStack(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        if (cur->right) st.push(cur->right);
        if (cur->left) st.push(cur->left);
        if (!st.empty()) cur->right = st.top();     // next in preorder
        cur->left = nullptr;
    }
}
```

**Java**
```java
class Solution {
    static void flattenStack(TreeNode root) {
        if (root == null) return;
        Deque<TreeNode> st = new ArrayDeque<>();
        st.push(root);
        while (!st.isEmpty()) {
            TreeNode cur = st.pop();
            if (cur.right != null) st.push(cur.right);
            if (cur.left != null) st.push(cur.left);
            if (!st.isEmpty()) cur.right = st.peek();
            cur.left = null;
        }
    }
}
```

#### Approach 3: Optimal — Morris-style, O(1) space (as in the video)
For each `cur` with a left subtree:
- find the **right-most node** of the left subtree, `pred`, which is the last node of that subtree in preorder;
- connect `pred.right = cur.right`;
- move the left subtree to the right: `cur.right = cur.left`, `cur.left = null`.

Then `cur = cur.right`.

**Complexity:** O(n) time, since each edge is walked a constant number of times. O(1) space.

**C++**
```cpp
void flatten(TreeNode* root) {
    TreeNode* cur = root;
    while (cur) {
        if (cur->left) {
            TreeNode* pred = cur->left;
            while (pred->right) pred = pred->right;   // last node of the left subtree
            pred->right = cur->right;
            cur->right = cur->left;
            cur->left = nullptr;
        }
        cur = cur->right;
    }
}
```

**Java**
```java
class Solution {
    static void flatten(TreeNode root) {
        TreeNode cur = root;
        while (cur != null) {
            if (cur.left != null) {
                TreeNode pred = cur.left;
                while (pred.right != null) pred = pred.right;
                pred.right = cur.right;
                cur.right = cur.left;
                cur.left = null;
            }
            cur = cur.right;
        }
    }
}
```

#### Key Takeaways
- Three levels of solution: reverse-postorder recursion with `prev`, a stack-based preorder, then Morris-style threading for O(1) space.

[↑ Contents](#contents) · [← Previous](#p300) · [Next →](#p302)

---

## Construction Problems

<a id="p302"></a>

### 26. Requirements needed to construct a unique BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Construction Problems | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/requirements-needed-to-construct-a-unique-binary-tree) | [Watch](https://youtu.be/9GMECGQgWrQ) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Given **two** traversal types, chosen from preorder (1), inorder (2) and postorder (3), can they always identify a **unique** binary tree? Return `true` or `false`.

```text
(1, 2) pre + in    -> true
(2, 3) in + post   -> true
(1, 3) pre + post  -> false
(2, 2) in + in     -> false
```

#### Intuition — why inorder is required
- **Preorder and postorder tell you the root**: the first element of preorder, the last of postorder. But they **don't** tell you which nodes lie to its left and which to its right.
- **Inorder tells you exactly that**: everything before the root in inorder is the left subtree, everything after is the right subtree.

So you need **inorder plus one of (preorder, postorder, level order)**. Preorder and postorder together are ambiguous. Example: the trees "1 with left child 2" and "1 with right child 2" both have preorder `1 2` and postorder `2 1`. Two copies of the same traversal add no information.

#### Approach: Check the rule
The answer is `true` iff exactly one of the two is inorder (2), and the other is a different traversal.

**Complexity:** O(1) time and space.

**C++**
```cpp
bool isPossible(int a, int b) {
    // 1 = preorder, 2 = inorder, 3 = postorder
    if (a == b) return false;                 // same traversal twice is never enough
    return a == 2 || b == 2;                  // inorder must be one of them
}
```

**Java**
```java
class Solution {
    static boolean isPossible(int a, int b) {
        if (a == b) return false;
        return a == 2 || b == 2;
    }
}
```

#### Edge Cases & Pitfalls
- **The exception for pre + post.** They *do* determine a unique tree when the tree is known to be **full**, i.e. every node has 0 or 2 children (LeetCode 889). In general they don't.

#### Key Takeaways
- Unique construction needs inorder, for the left/right split, plus a root-identifying traversal. The next two problems build exactly these.

[↑ Contents](#contents) · [← Previous](#p301) · [Next →](#p303)

---

<a id="p303"></a>

### 27. Construct a BT from Preorder and Inorder

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Construction Problems | Core | No | [LeetCode](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/construct-a-binary-tree-from-preorder-and-inorder) | [Watch](https://youtu.be/aZNaLrVebKQ) |

#### Problem Statement
Build the binary tree from its **preorder** and **inorder** traversals. All values are unique.

```text
preorder = [3, 9, 20, 15, 7], inorder = [9, 3, 15, 20, 7]
->      3
       / \
      9   20
         /  \
        15   7
```

#### Intuition
- **Find the root.** It's the first element of preorder, `3`.
- **Split inorder at the root.** The left part `[9]` is the left subtree; the right part `[15,20,7]` is the right subtree.
- **Split preorder by size.** The left subtree has `numsLeft = inRoot − inStart` elements, so in preorder they are the **next** `numsLeft` elements after the root. The rest belong to the right subtree.
- **Recurse on index ranges**, never copying arrays.

#### Approach: Recursion on index ranges + hash map of inorder positions (as in the video)
- Hash each value to its inorder index, so finding `inRoot` is O(1).
- `build(preStart, preEnd, inStart, inEnd)`:
  - if `preStart > preEnd` or `inStart > inEnd`, return null;
  - `root = pre[preStart]`, `inRoot = inMap[root]`, `numsLeft = inRoot − inStart`;
  - `root.left = build(preStart+1, preStart+numsLeft, inStart, inRoot−1)`;
  - `root.right = build(preStart+numsLeft+1, preEnd, inRoot+1, inEnd)`.

**Complexity:** O(n) time, or O(n log n) with an ordered map. O(n) space for the map plus O(h) recursion.

**C++**
```cpp
TreeNode* buildPI(vector<int>& pre, int preStart, int preEnd,
                  vector<int>& in, int inStart, int inEnd, unordered_map<int, int>& inMap) {
    if (preStart > preEnd || inStart > inEnd) return nullptr;
    TreeNode* root = new TreeNode(pre[preStart]);
    int inRoot = inMap[root->val];
    int numsLeft = inRoot - inStart;
    root->left = buildPI(pre, preStart + 1, preStart + numsLeft, in, inStart, inRoot - 1, inMap);
    root->right = buildPI(pre, preStart + numsLeft + 1, preEnd, in, inRoot + 1, inEnd, inMap);
    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> inMap;
    for (int i = 0; i < (int)inorder.size(); i++) inMap[inorder[i]] = i;
    return buildPI(preorder, 0, (int)preorder.size() - 1, inorder, 0, (int)inorder.size() - 1, inMap);
}
```

**Java**
```java
class Solution {
    static TreeNode buildPI(int[] pre, int preStart, int preEnd,
                            int[] in, int inStart, int inEnd, Map<Integer, Integer> inMap) {
        if (preStart > preEnd || inStart > inEnd) return null;
        TreeNode root = new TreeNode(pre[preStart]);
        int inRoot = inMap.get(root.val);
        int numsLeft = inRoot - inStart;
        root.left = buildPI(pre, preStart + 1, preStart + numsLeft, in, inStart, inRoot - 1, inMap);
        root.right = buildPI(pre, preStart + numsLeft + 1, preEnd, in, inRoot + 1, inEnd, inMap);
        return root;
    }
    static TreeNode buildTree(int[] preorder, int[] inorder) {
        Map<Integer, Integer> inMap = new HashMap<>();
        for (int i = 0; i < inorder.length; i++) inMap.put(inorder[i], i);
        return buildPI(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1, inMap);
    }
}
```

#### Edge Cases & Pitfalls
- **Duplicate values break the method.** The root's inorder position becomes ambiguous, which is why the problem guarantees unique values.

#### Key Takeaways
- Preorder gives the root, inorder gives the split, and the left subtree's size maps the split back onto preorder.

[↑ Contents](#contents) · [← Previous](#p302) · [Next →](#p304)

---

<a id="p304"></a>

### 28. Construct a BT from Postorder and Inorder

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Construction Problems | Core | No | [LeetCode](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/) | [Watch](https://youtu.be/LgLRTaEMRVc) |

#### Problem Statement
Build the binary tree from its **inorder** and **postorder** traversals. All values are unique.

```text
inorder = [9, 3, 15, 20, 7], postorder = [9, 15, 7, 20, 3]   ->  same tree as above (root 3)
```

#### Approach: Mirror of the previous problem (as in the video)
- **The root is the last element** of the current postorder range.
- **Split inorder at the root.** `numsLeft = inRoot − inStart`.
- **Ranges in postorder:**
  - the left subtree is the **first** `numsLeft` elements: `postStart … postStart+numsLeft−1`;
  - the right subtree is `postStart+numsLeft … postEnd−1`, excluding the root at `postEnd`.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
TreeNode* buildIP(vector<int>& in, int inStart, int inEnd,
                  vector<int>& post, int postStart, int postEnd, unordered_map<int, int>& inMap) {
    if (postStart > postEnd || inStart > inEnd) return nullptr;
    TreeNode* root = new TreeNode(post[postEnd]);
    int inRoot = inMap[root->val];
    int numsLeft = inRoot - inStart;
    root->left = buildIP(in, inStart, inRoot - 1, post, postStart, postStart + numsLeft - 1, inMap);
    root->right = buildIP(in, inRoot + 1, inEnd, post, postStart + numsLeft, postEnd - 1, inMap);
    return root;
}
TreeNode* buildTreeInPost(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> inMap;
    for (int i = 0; i < (int)inorder.size(); i++) inMap[inorder[i]] = i;
    return buildIP(inorder, 0, (int)inorder.size() - 1, postorder, 0, (int)postorder.size() - 1, inMap);
}
```

**Java**
```java
class Solution {
    static TreeNode buildIP(int[] in, int inStart, int inEnd,
                            int[] post, int postStart, int postEnd, Map<Integer, Integer> inMap) {
        if (postStart > postEnd || inStart > inEnd) return null;
        TreeNode root = new TreeNode(post[postEnd]);
        int inRoot = inMap.get(root.val);
        int numsLeft = inRoot - inStart;
        root.left = buildIP(in, inStart, inRoot - 1, post, postStart, postStart + numsLeft - 1, inMap);
        root.right = buildIP(in, inRoot + 1, inEnd, post, postStart + numsLeft, postEnd - 1, inMap);
        return root;
    }
    static TreeNode buildTreeInPost(int[] inorder, int[] postorder) {
        Map<Integer, Integer> inMap = new HashMap<>();
        for (int i = 0; i < inorder.length; i++) inMap.put(inorder[i], i);
        return buildIP(inorder, 0, inorder.length - 1, postorder, 0, postorder.length - 1, inMap);
    }
}
```

#### Key Takeaways
- Compared with the preorder version, only the root position (last instead of first) and the index arithmetic change.

[↑ Contents](#contents) · [← Previous](#p303) · [Next →](#p305)

---

<a id="p305"></a>

### 29. Serialize and De-serialize BT

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Construction Problems | Pro | No | [LeetCode](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/serialize-and-deserialize-a-binary-tree) | [Watch](https://youtu.be/-YbXySKJsX8) |

#### Problem Statement
Design `serialize(root) → string` and `deserialize(string) → root` so that a tree survives a round trip.

```text
    1
   / \
  2   3
     / \
    4   5      serialize -> "1,2,3,#,#,4,5,#,#,#,#,"   deserialize -> the same tree
```

#### Approach: Level-order with null markers (as in the video)
- **Serialize:** BFS from the root.
  - For each dequeued slot, append the node's value followed by `,`, or `#,` if the slot is null.
  - For non-null nodes, enqueue **both** children, even null ones, so the structure is recorded.
- **Deserialize:** split on commas. The first token is the root; put it in a queue.
  - For each node taken from the queue, the **next two tokens** are its left and right children.
  - `#` means null. Non-null children are created and enqueued.

**Complexity:** O(n) time and O(n) space for both directions.

**C++**
```cpp
string serialize(TreeNode* root) {
    if (root == nullptr) return "";
    string s;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (node == nullptr) { s += "#,"; continue; }
        s += to_string(node->val) + ",";
        q.push(node->left);                       // push nulls too
        q.push(node->right);
    }
    return s;
}
TreeNode* deserialize(string data) {
    if (data.empty()) return nullptr;
    stringstream ss(data);
    string tok;
    getline(ss, tok, ',');
    TreeNode* root = new TreeNode(stoi(tok));
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (!getline(ss, tok, ',')) break;
        if (tok != "#") { node->left = new TreeNode(stoi(tok)); q.push(node->left); }
        if (!getline(ss, tok, ',')) break;
        if (tok != "#") { node->right = new TreeNode(stoi(tok)); q.push(node->right); }
    }
    return root;
}
```

**Java**
```java
class Solution {
    static String serialize(TreeNode root) {
        if (root == null) return "";
        StringBuilder sb = new StringBuilder();
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        while (!q.isEmpty()) {
            TreeNode node = q.remove();
            if (node == null) { sb.append("#,"); continue; }
            sb.append(node.val).append(',');
            q.add(node.left);                    // LinkedList accepts nulls
            q.add(node.right);
        }
        return sb.toString();
    }
    static TreeNode deserialize(String data) {
        if (data.isEmpty()) return null;
        String[] tok = data.split(",");
        TreeNode root = new TreeNode(Integer.parseInt(tok[0]));
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        int i = 1;
        while (!q.isEmpty() && i < tok.length) {
            TreeNode node = q.remove();
            if (!tok[i].equals("#")) { node.left = new TreeNode(Integer.parseInt(tok[i])); q.add(node.left); }
            i++;
            if (i < tok.length && !tok[i].equals("#")) { node.right = new TreeNode(Integer.parseInt(tok[i])); q.add(node.right); }
            i++;
        }
        return root;
    }
}
```

#### Edge Cases & Pitfalls
- **Negative values and multi-digit numbers** work because tokens are comma-separated.
- **In Java, use `LinkedList` as the queue.** `ArrayDeque` rejects `null` elements.
- **A preorder DFS with `#` markers** is an equally valid serialisation.

#### Key Takeaways
- Any traversal plus explicit null markers is enough to reconstruct a tree. Level order maps naturally to "the next two tokens are my children".

[↑ Contents](#contents) · [← Previous](#p304) · [Next →](#p306)

---

## Traversal in Constant Space

<a id="p306"></a>

### 30. Morris Inorder Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Traversal in Constant Space | Pro | No | [LeetCode](https://leetcode.com/problems/binary-tree-inorder-traversal/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/morris-inorder-traversal) | [Watch](https://youtu.be/80Zug6D1_r4) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Return the inorder traversal using **O(1) extra space**: no recursion and no stack.

```text
        1
       / \
      2   3
     / \   \
    4   5   6
             \
              7      inorder = [4, 2, 5, 1, 3, 6, 7]
```

#### Intuition — threaded binary tree (Morris traversal)
- **What the stack was for.** Recursion and stacks remember where to return after finishing a left subtree.
- **Use a spare pointer instead.** Morris stores that return address inside the tree. The **right-most node of the left subtree**, `cur`'s inorder predecessor, has a null right pointer. Temporarily set it to `cur`: a **thread**.
- **Two kinds of node:**
  - **no left child:** visit `cur` and go right;
  - **has a left child:** find the predecessor `prev`, the right-most node of the left subtree, stopping if `prev.right == cur`:
    - if `prev.right == null`, create the thread `prev.right = cur` and go left (first time here);
    - if `prev.right == cur`, the left subtree is finished. **Remove** the thread, **visit** `cur`, and go right.

#### Approach: Morris inorder
**Complexity:** O(n) time, because each edge is walked at most about 3 times. O(1) extra space. The tree is restored by the end.

**C++**
```cpp
vector<int> morrisInorder(TreeNode* root) {
    vector<int> ans;
    TreeNode* cur = root;
    while (cur) {
        if (cur->left == nullptr) {
            ans.push_back(cur->val);
            cur = cur->right;
        } else {
            TreeNode* prev = cur->left;
            while (prev->right && prev->right != cur) prev = prev->right;
            if (prev->right == nullptr) {         // create thread, go left
                prev->right = cur;
                cur = cur->left;
            } else {                              // thread found: left done
                prev->right = nullptr;
                ans.push_back(cur->val);
                cur = cur->right;
            }
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> morrisInorder(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        TreeNode cur = root;
        while (cur != null) {
            if (cur.left == null) {
                ans.add(cur.val);
                cur = cur.right;
            } else {
                TreeNode prev = cur.left;
                while (prev.right != null && prev.right != cur) prev = prev.right;
                if (prev.right == null) {
                    prev.right = cur;
                    cur = cur.left;
                } else {
                    prev.right = null;
                    ans.add(cur.val);
                    cur = cur.right;
                }
            }
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Always remove the thread** when you see it the second time. Otherwise the tree stays modified and later traversals loop.
- **The predecessor search must stop at `cur`.** Without the `prev->right != cur` condition, the loop would follow the thread forever.

#### Key Takeaways
- Morris traversal replaces the stack with temporary threads from each inorder predecessor. It's O(1) space and leaves the tree unchanged afterwards.

[↑ Contents](#contents) · [← Previous](#p305) · [Next →](#p307)

---

<a id="p307"></a>

### 31. Morris Preorder Traversal

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Trees › Traversal in Constant Space | Pro | No | [LeetCode](https://leetcode.com/problems/binary-tree-preorder-traversal/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/morris-preorder-traversal) | [Watch](https://youtu.be/80Zug6D1_r4) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Return the **preorder** traversal using **O(1) extra space** (Morris).

```text
        1
       / \
      2   3
     / \
    4   5        preorder = [1, 2, 4, 5, 3]
```

#### Approach: Morris preorder — record the node when *creating* the thread
This is the same threading as Morris inorder. The only change is **when** a node with a left child is visited:
- in preorder, the root comes first, so visit `cur` **when the thread is created**, before going left;
- when the thread is found again, just remove it and go right, without visiting.

A node with no left child is visited and then you go right, exactly as in inorder.

**Complexity:** O(n) time, O(1) extra space.

**C++**
```cpp
vector<int> morrisPreorder(TreeNode* root) {
    vector<int> ans;
    TreeNode* cur = root;
    while (cur) {
        if (cur->left == nullptr) {
            ans.push_back(cur->val);
            cur = cur->right;
        } else {
            TreeNode* prev = cur->left;
            while (prev->right && prev->right != cur) prev = prev->right;
            if (prev->right == nullptr) {
                prev->right = cur;
                ans.push_back(cur->val);          // visit BEFORE going left (preorder)
                cur = cur->left;
            } else {
                prev->right = nullptr;            // left subtree done: just unthread
                cur = cur->right;
            }
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> morrisPreorder(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        TreeNode cur = root;
        while (cur != null) {
            if (cur.left == null) {
                ans.add(cur.val);
                cur = cur.right;
            } else {
                TreeNode prev = cur.left;
                while (prev.right != null && prev.right != cur) prev = prev.right;
                if (prev.right == null) {
                    prev.right = cur;
                    ans.add(cur.val);
                    cur = cur.left;
                } else {
                    prev.right = null;
                    cur = cur.right;
                }
            }
        }
        return ans;
    }
}
```

#### Key Takeaways
- Morris inorder visits a node when its thread is **removed**; Morris preorder visits it when the thread is **created**. Everything else is identical.

[↑ Contents](#contents) · [← Previous](#p306)

---
