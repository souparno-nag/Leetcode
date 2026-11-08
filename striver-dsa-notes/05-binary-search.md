# Binary Search — Striver's A2Z DSA Sheet Notes

Section 5 of 20 · 32 problems · 32 with video, 0 without · [All sections](00-index.md)

[← Hashing](04-hashing.md) | [Strings (Basic and Medium) →](06-strings-basic-and-medium.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Fundamentals**

1. [Search X in sorted array](#p105) — Basic
2. [Lower Bound](#p106) — Core
3. [Upper Bound](#p107) — Core

**Logic Building**

4. [Search insert position](#p108) — Basic
5. [Floor and Ceil in Sorted Array](#p109) — Core
6. [First and last occurrence](#p110) — Core
7. [Search in rotated sorted array-I](#p111) — Core · *video not transcribed*
8. [Search in rotated sorted array-II](#p112) — Core
9. [Find minimum in Rotated Sorted Array](#p113) — Core
10. [Find out how many times the array is rotated](#p114) — Core
11. [Single element in sorted array](#p115) — Core
12. [Count Occurrences in a Sorted Array](#p116) — Core

**On answers**

13. [Find square root of a number](#p117) — Core
14. [Find Nth root of a number](#p118) — Core
15. [Find the smallest divisor](#p119) — Core
16. [Koko eating bananas](#p120) — Pro
17. [Minimum days to make M bouquets](#p121) — Pro
18. [Capacity to Ship Packages Within D Days](#p122) — Pro
19. [Kth Missing Positive Number](#p123) — Pro
20. [Painter's Partition](#p124) — Pro

**FAQs**

21. [Aggressive Cows](#p125) — Pro
22. [Book Allocation Problem](#p126) — Pro
23. [Find peak element](#p127) — Core
24. [Median of 2 sorted arrays](#p128) — Pro
25. [Kth element of 2 sorted arrays](#p129) — Pro
26. [Minimize Max Distance to Gas Station](#p130) — Pro
27. [Split array - largest sum](#p131) — Pro

**2D Arrays**

28. [Find row with maximum 1's](#p132) — Core
29. [Search in a 2D Matrix](#p133) — Core
30. [Search in 2D matrix - II](#p134) — Core
31. [Find Peak Element - II](#p135) — Core
32. [Matrix Median](#p136) — Pro

---

## Fundamentals

<a id="p105"></a>

### 1. Search X in sorted array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Fundamentals | Basic | No | [LeetCode](https://leetcode.com/problems/binary-search/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/binary-search-algorithm) | [Watch](https://youtu.be/MHf6awe89xw) |

#### Problem Statement
Given a **sorted** array `nums` of **distinct** integers and a `target`, return the index of `target`, or `−1` if it is not present (LeetCode 704).

```text
nums = [3, 4, 6, 7, 9, 12, 16, 17], target = 6   ->  2
nums = [3, 4, 6, 7, 9, 12, 16, 17], target = 13  ->  -1
```

#### Intuition — what binary search is
Binary search is a search algorithm for a **sorted search space**. The video's real-life example is looking up the word "Raj" in a dictionary. You don't scan page by page (that's *linear search*, O(n)). You open the dictionary in the middle. If the words there start with "s", then "Raj" can only be in the **left** half, so you discard the right half and repeat on what's left.

The search space doesn't have to be an array. Any **monotonic / sorted** space works (an answer range, page numbers, …). Later problems in this section use binary search "on answers".

#### Approach 1: Linear search (baseline)
Scan from left to right until you find `target`. This takes O(n) time, and the worst case is when `target` is last or absent.

**C++**
```cpp
int linearSearch(vector<int>& nums, int target) {
    for (int i = 0; i < (int)nums.size(); i++)
        if (nums[i] == target) return i;
    return -1;
}
```

**Java**
```java
class Solution {
    static int linearSearch(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++)
            if (nums[i] == target) return i;
        return -1;
    }
}
```

#### Approach 2: Binary search — iterative
Keep two pointers, `low = 0` and `high = n − 1`. **Everything between `low` and `high` (inclusive) is the search space.** While `low <= high`:
1. `mid = (low + high) / 2`.
2. If `nums[mid] == target`, return `mid`.
3. If `target > nums[mid]`, the target can only be on the right, so `low = mid + 1`.
4. Otherwise it can only be on the left, so `high = mid − 1`.

When `high < low`, the search space is empty and the target is absent, so return −1.

**Dry run** `target = 13` on `[3, 4, 6, 7, 9, 12, 16, 17]`:
- `low = 0, high = 7`: mid = 3, value 7. 13 > 7, so `low = 4`.
- `low = 4, high = 7`: mid = 5, value 12. 13 > 12, so `low = 6`.
- `low = 6, high = 7`: mid = 6, value 16. 13 < 16, so `high = 5`.
- `high < low`: the space is exhausted, so return −1.

For `target = 6`: mid = 3 (7), so `high = 2`; then mid = 1 (4), so `low = 2`; then mid = 2 (6). Found at index 2.

**C++**
```cpp
int search(vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        else if (target > nums[mid]) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    public int search(int[] nums, int target) {
        int low = 0, high = nums.length - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) return mid;
            else if (target > nums[mid]) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }
}
```

#### Approach 3: Binary search — recursive
Every step does the same thing on a smaller range, so the search can be written as recursion over `(low, high)`:
- **Base case:** if `low > high`, the search space is exhausted, so return −1.
- Compute `mid`. If `nums[mid] == target`, return `mid`.
- If `target > nums[mid]`, return `f(mid + 1, high)`; otherwise return `f(low, mid − 1)`.

For `target = 13`, the calls are `f(0,7) → f(4,7) → f(6,7) → f(6,5)`. The last call hits the base case and returns −1, and that −1 propagates back up through every frame.

**Complexity:** O(log n) time, plus O(log n) recursion-stack space.

**C++**
```cpp
int bs(vector<int>& nums, int low, int high, int target) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (nums[mid] == target) return mid;
    if (target > nums[mid]) return bs(nums, mid + 1, high, target);
    return bs(nums, low, mid - 1, target);
}
int searchRecursive(vector<int>& nums, int target) {
    return bs(nums, 0, (int)nums.size() - 1, target);
}
```

**Java**
```java
class Solution {
    static int bs(int[] nums, int low, int high, int target) {
        if (low > high) return -1;
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        if (target > nums[mid]) return bs(nums, mid + 1, high, target);
        return bs(nums, low, mid - 1, target);
    }
    static int searchRecursive(int[] nums, int target) {
        return bs(nums, 0, nums.length - 1, target);
    }
}
```

#### Time complexity — why O(log₂ n)
Each step does O(1) work and roughly halves the search space: 32 → 16 → 8 → 4 → 2 → 1. Sometimes slightly less than half remains, but never more. That's 5 halvings, and 32 = 2⁵. For 64 = 2⁶ it takes 6 halvings. So the number of steps is about `log₂ n`, and binary search runs in **O(log n)** time. The iterative version uses O(1) space.

#### The overflow case (important in interviews)
`mid = (low + high) / 2` can overflow when the search space is huge, not just an array index. Suppose the space is `[0, INT_MAX]` and both `low` and `high` approach `INT_MAX`. Then `low + high ≈ 2·INT_MAX` doesn't fit in an `int`. There are two fixes:
1. Use `long long` / `long` for `low`, `high` and `mid`.
2. Use `mid = low + (high − low) / 2`. This is algebraically the same value, but it never exceeds `high`, so it can't overflow when the range lies within `[0, INT_MAX]`.

#### Edge Cases & Pitfalls
- The loop condition is `low <= high`, not `<`. With `<`, a single-element search space would never be checked.
- Always move past `mid` (`mid + 1` / `mid − 1`); otherwise the loop may never end.
- The array must be sorted, and here we assume distinct values. With duplicates, use lower/upper bound to get the first or last occurrence.

#### Key Takeaways
- Binary search keeps `[low, high]` as the live search space and discards half of it each step.
- O(log n) time; iterative O(1) space, recursive O(log n) stack.
- Write `mid = low + (high − low) / 2` by habit.

[↑ Contents](#contents) · [Next →](#p106)

---

<a id="p106"></a>

### 2. Lower Bound

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Fundamentals | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/lower-bound-in-sorted-array) | [Watch](https://youtu.be/6zhGS79oQ4k) |

#### Problem Statement
Given a sorted array `arr` of size `n` (duplicates allowed) and a number `x`, find the **lower bound**: the **smallest index `i` such that `arr[i] >= x`**. If no element is `>= x`, return `n`, the "hypothetical index" just past the end.

```text
arr = [3, 5, 8, 15, 19]:  x = 8 -> 2,  x = 9 -> 3,  x = 16 -> 4,  x = 20 -> 5 (= n)
arr = [3, 5, 8, 15, 19, 19, 19, 90]:  x = 19 -> 4   (smallest index with value >= 19)
```

#### Approach 1: Linear scan
Walk from the left and return the first `i` with `arr[i] >= x`, or `n` if there is none. This takes O(n).

**C++**
```cpp
int lowerBoundLinear(vector<int>& arr, int x) {
    int n = arr.size();
    for (int i = 0; i < n; i++)
        if (arr[i] >= x) return i;
    return n;
}
```

**Java**
```java
class Solution {
    static int lowerBoundLinear(int[] arr, int x) {
        int n = arr.length;
        for (int i = 0; i < n; i++)
            if (arr[i] >= x) return i;
        return n;
    }
}
```

#### Approach 2: Binary search with an `ans` variable
The array is sorted and we're searching, so we use binary search. The trick (used throughout this playlist) is to keep an **`ans`** variable, initialised to `n`, which holds the best candidate found so far.
- If `arr[mid] >= x`, then `mid` **may** be the answer. Store `ans = mid`, then look for a **smaller** index on the left: `high = mid − 1`.
- Otherwise, `mid` and everything to its left are too small. Go right: `low = mid + 1`.

Unlike plain binary search there's no separate "equal" branch. Each `mid` either *may be* an answer or *cannot be* one.

**Dry run** `arr = [1, 2, 3, 3, 5, 8, 8, 10, 10, 11]`, `x = 9` (initially `ans = 10`):
- low 0, high 9: mid 4, value 5. 5 < 9 → `low = 5`.
- low 5, high 9: mid 7, value 10. 10 ≥ 9 → `ans = 7`, `high = 6`.
- low 5, high 6: mid 5, value 8. 8 < 9 → `low = 6`.
- low 6, high 6: mid 6, value 8. 8 < 9 → `low = 7`. Now `low > high`, so stop.

Answer: 7. With `x = 1`, `ans` shrinks 4 → 1 → 0. Because we always move left after a hit, every new candidate is smaller than the last.

**Complexity:** O(log₂ n) time, O(1) space.

**C++**
```cpp
int lowerBound(vector<int>& arr, int x) {
    int n = arr.size(), low = 0, high = n - 1, ans = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= x) { ans = mid; high = mid - 1; }   // may be the answer, look left
        else low = mid + 1;                                 // too small, look right
    }
    return ans;
}

// STL: returns an iterator; subtract begin() to get the index
int lowerBoundSTL(vector<int>& arr, int x) {
    return lower_bound(arr.begin(), arr.end(), x) - arr.begin();
}
```

**Java**
```java
class Solution {
    static int lowerBound(int[] arr, int x) {
        int n = arr.length, low = 0, high = n - 1, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= x) { ans = mid; high = mid - 1; }   // may be the answer, look left
            else low = mid + 1;                                 // too small, look right
        }
        return ans;
    }
}
```

**STL notes (C++):**
- `lower_bound(v.begin(), v.end(), x) - v.begin()` gives the index.
- For a plain array, use `lower_bound(a, a + n, x) - a`.
- To search only indices 2…6, use `lower_bound(a + 2, a + 7, x) - a`. The end pointer is exclusive.

Java has no direct equivalent. `Arrays.binarySearch` does not guarantee the *first* match among duplicates, so write it yourself. *(not in video: `Collections.binarySearch` / `TreeSet.ceiling` exist, but `ceiling` returns a value, not an index.)*

#### Edge Cases & Pitfalls
- If every element is `< x`, the answer is `n`. Initialise `ans = n`, not −1.
- With duplicates, the result is the **first** element `>= x`, because a hit always moves the search left.
- *Expert note from the video:* when the loop ends, `low` itself equals the answer, so the `ans` variable is optional. Keep it until you're confident.

#### Key Takeaways
- Lower bound means the first index with `arr[i] >= x`.
- Template: on a hit, store `ans` and move toward the side you want to minimise. Lower bound is the foundation for search insert, floor/ceil, first occurrence and counting occurrences.

[↑ Contents](#contents) · [← Previous](#p105) · [Next →](#p107)

---

<a id="p107"></a>

### 3. Upper Bound

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Fundamentals | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/upper-bound-in-sorted-array) | [Watch](https://youtu.be/6zhGS79oQ4k) |

#### Problem Statement
Find the **upper bound** of `x` in a sorted array: the **smallest index `i` such that `arr[i] > x`** (strictly greater). If no element is greater than `x`, return `n`.

```text
arr = [2, 3, 6, 7, 8, 8, 11, 11, 11, 12]   (n = 10)
x = 6  -> 3    (7 is the first value > 6)
x = 11 -> 9    (lower bound would be 6; upper bound skips all the 11s)
x = 12 -> 10,  x = 13 -> 10,  x = 0 -> 0
```

#### Approach 1: Linear scan
Return the first `i` with `arr[i] > x`, or `n`. This takes O(n).

**C++**
```cpp
int upperBoundLinear(vector<int>& arr, int x) {
    int n = arr.size();
    for (int i = 0; i < n; i++)
        if (arr[i] > x) return i;
    return n;
}
```

**Java**
```java
class Solution {
    static int upperBoundLinear(int[] arr, int x) {
        int n = arr.length;
        for (int i = 0; i < n; i++)
            if (arr[i] > x) return i;
        return n;
    }
}
```

#### Approach 2: Binary search — same template, strict comparison
This is identical to the lower-bound code except that `>=` becomes `>`:
- If `arr[mid] > x`, then `ans = mid` and `high = mid − 1`.
- Otherwise `low = mid + 1`.

**Complexity:** O(log₂ n) time, O(1) space.

**C++**
```cpp
int upperBound(vector<int>& arr, int x) {
    int n = arr.size(), low = 0, high = n - 1, ans = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] > x) { ans = mid; high = mid - 1; }
        else low = mid + 1;
    }
    return ans;
}

int upperBoundSTL(vector<int>& arr, int x) {
    return upper_bound(arr.begin(), arr.end(), x) - arr.begin();
}
```

**Java**
```java
class Solution {
    static int upperBound(int[] arr, int x) {
        int n = arr.length, low = 0, high = n - 1, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] > x) { ans = mid; high = mid - 1; }
            else low = mid + 1;
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- If `x` is at least the maximum element, the answer is `n`.
- `upperBound(x) − lowerBound(x)` equals the **number of occurrences** of `x`. This is used later in "Count Occurrences".

#### Key Takeaways
- Upper bound means the first index with `arr[i] > x`. It's the lower-bound code with `>=` replaced by `>`.
- In C++ the STL call is `upper_bound(...)`.

[↑ Contents](#contents) · [← Previous](#p106) · [Next →](#p108)

---

## Logic Building

<a id="p108"></a>

### 4. Search insert position

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Basic | No | [LeetCode](https://leetcode.com/problems/search-insert-position/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/search-insert-position) | [Watch](https://youtu.be/6zhGS79oQ4k) |

#### Problem Statement
Given a sorted array of **distinct** integers and a target `m`, return the index of `m` if it is present. Otherwise return the index where `m` would be inserted to keep the array sorted (LeetCode 35).

```text
arr = [1, 2, 4, 7], m = 6  ->  3    (1, 2, 4, [6], 7)
arr = [1, 2, 4, 7], m = 2  ->  1    (present)
arr = [1, 2, 4, 7], m = 9  ->  4    (insert at the end)
```

#### Intuition — it's exactly the lower bound
If `m` is present, the answer is its index, which is the first index with `arr[i] >= m`. If it's absent, it goes just before the first element greater than `m`. That is also the first index with `arr[i] >= m`. If everything is smaller, the answer is `n`. In all three cases the answer is **`lowerBound(arr, m)`**.

#### Approach 1: Linear scan
Return the first `i` with `arr[i] >= m`, or `n`. This takes O(n).

**C++**
```cpp
int searchInsertLinear(vector<int>& arr, int m) {
    for (int i = 0; i < (int)arr.size(); i++)
        if (arr[i] >= m) return i;
    return arr.size();
}
```

**Java**
```java
class Solution {
    static int searchInsertLinear(int[] arr, int m) {
        for (int i = 0; i < arr.length; i++)
            if (arr[i] >= m) return i;
        return arr.length;
    }
}
```

#### Approach 2: Optimal — lower bound with binary search
**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int searchInsert(vector<int>& arr, int m) {
    int n = arr.size(), low = 0, high = n - 1, ans = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= m) { ans = mid; high = mid - 1; }
        else low = mid + 1;
    }
    return ans;
}
```

**Java**
```java
class Solution {
    public int searchInsert(int[] arr, int m) {
        int n = arr.length, low = 0, high = n - 1, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= m) { ans = mid; high = mid - 1; }
            else low = mid + 1;
        }
        return ans;
    }
}
```

#### Key Takeaways
- "Search insert position" is lower bound under another name. In the video, the lower-bound code was pasted in and accepted after renaming the variables.

[↑ Contents](#contents) · [← Previous](#p107) · [Next →](#p109)

---

<a id="p109"></a>

### 5. Floor and Ceil in Sorted Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Core | No | — | [Watch](https://youtu.be/6zhGS79oQ4k) |

#### Problem Statement
Given a sorted array `arr` and a number `x`, find:
- the **floor** of `x`: the **largest element `<= x`**;
- the **ceil** of `x`: the **smallest element `>= x`**.

Return −1 for whichever one doesn't exist. (Most versions of this problem ask for the **values**; some ask for indices, so read the statement.)

```text
arr = [10, 20, 30, 40, 50], x = 25  ->  floor 20, ceil 30
arr = [10, 20, 25, 30, 40], x = 25  ->  floor 25, ceil 25
arr = [10, 20, 30],         x = 5   ->  floor -1, ceil 10
```

#### Intuition
- **Ceil** is the smallest number `>= x`, which is exactly the element at the **lower bound**. Use the same binary search, but store the *value* `arr[mid]` instead of the index.
- **Floor** mirrors it. If `arr[mid] <= x`, then `arr[mid]` may be the floor, so store it and look **right** for a larger candidate (`low = mid + 1`). Otherwise go left.

You never need to compare candidates with `max` / `min`. Each time we store a value we move toward bigger (or smaller) values, so every new candidate automatically beats the previous one.

#### Approach 1: Linear scan
One pass works: the last element `<= x` is the floor, and the first element `>= x` is the ceil. This takes O(n).

**C++**
```cpp
pair<int, int> floorCeilLinear(vector<int>& arr, int x) {
    int fl = -1, ce = -1;
    for (int v : arr) {
        if (v <= x) fl = v;               // sorted: last such v is the largest
        if (v >= x && ce == -1) ce = v;   // first such v is the smallest
    }
    return {fl, ce};
}
```

**Java**
```java
class Solution {
    static int[] floorCeilLinear(int[] arr, int x) {
        int fl = -1, ce = -1;
        for (int v : arr) {
            if (v <= x) fl = v;               // sorted: last such v is the largest
            if (v >= x && ce == -1) ce = v;   // first such v is the smallest
        }
        return new int[]{fl, ce};
    }
}
```

#### Approach 2: Optimal — two binary searches
**Complexity:** O(log n) for each search, O(1) space.

**C++**
```cpp
int findFloor(vector<int>& arr, int x) {
    int low = 0, high = (int)arr.size() - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= x) { ans = arr[mid]; low = mid + 1; }   // may be floor, look right
        else high = mid - 1;
    }
    return ans;
}
int findCeil(vector<int>& arr, int x) {
    int low = 0, high = (int)arr.size() - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= x) { ans = arr[mid]; high = mid - 1; }  // may be ceil, look left
        else low = mid + 1;
    }
    return ans;
}
pair<int, int> getFloorAndCeil(vector<int>& arr, int x) {
    return {findFloor(arr, x), findCeil(arr, x)};
}
```

**Java**
```java
class Solution {
    static int findFloor(int[] arr, int x) {
        int low = 0, high = arr.length - 1, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] <= x) { ans = arr[mid]; low = mid + 1; }   // may be floor, look right
            else high = mid - 1;
        }
        return ans;
    }
    static int findCeil(int[] arr, int x) {
        int low = 0, high = arr.length - 1, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= x) { ans = arr[mid]; high = mid - 1; }  // may be ceil, look left
            else low = mid + 1;
        }
        return ans;
    }
    static int[] getFloorAndCeil(int[] arr, int x) {
        return new int[]{findFloor(arr, x), findCeil(arr, x)};
    }
}
```

#### Edge Cases & Pitfalls
- No floor exists when `x` is smaller than everything; no ceil exists when `x` is larger than everything. Both return −1 here.
- **Value or index?** Return what the problem asks for. If it wants indices, store `mid` instead of `arr[mid]`.
- *From the video:* when the loop ends, either `low` or `high` points at the answer, so the `ans` variable can be dropped once you're comfortable. For the floor it's `high`; for the ceil it's `low`.

#### Key Takeaways
- Ceil is the value at the lower bound. Floor is the same search with the comparison flipped (`<=`) and the direction flipped (move right on a hit).
- Every "smallest index / value such that …" or "largest … such that …" question uses the same answer-variable binary-search template.

[↑ Contents](#contents) · [← Previous](#p108) · [Next →](#p110)

---

<a id="p110"></a>

### 6. First and last occurrence

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/last-occurrence-in-a-sorted-array) | [Watch](https://youtu.be/hjR1IYVx9lY) |

#### Problem Statement
Given a sorted array (with duplicates) and a number `x`, return the **first and last index** at which `x` occurs, or `[-1, -1]` if it doesn't occur (LeetCode 34).

```text
arr = [2, 4, 6, 8, 8, 8, 11, 13]
x = 8   ->  [3, 5]
x = 10  ->  [-1, -1]
x = 11  ->  [6, 6]     (single occurrence: first = last)
```

#### Approach 1: Brute Force — linear scan
Start with `first = last = −1` and scan the array. On each `arr[i] == x`, set `first = i` if it's still −1, and always set `last = i`. Because the array is sorted, the values found are the first and last occurrences.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
vector<int> firstLastLinear(vector<int>& arr, int x) {
    int first = -1, last = -1;
    for (int i = 0; i < (int)arr.size(); i++)
        if (arr[i] == x) {
            if (first == -1) first = i;
            last = i;
        }
    return {first, last};
}
```

**Java**
```java
class Solution {
    static int[] firstLastLinear(int[] arr, int x) {
        int first = -1, last = -1;
        for (int i = 0; i < arr.length; i++)
            if (arr[i] == x) {
                if (first == -1) first = i;
                last = i;
            }
        return new int[]{first, last};
    }
}
```

#### Approach 2: Better — lower bound and upper bound
- `lb = lowerBound(x)` is the first index with `arr[i] >= x`. If `x` is present, that's its first occurrence.
- `upperBound(x) − 1` is the index just before the first element `> x`, which is the last occurrence.

**Edge case:** if `lb == n` (every element is `< x`) or `arr[lb] != x` (e.g. `x = 10` lands on 11), then `x` is absent, so return `[-1, -1]`.

**Complexity:** 2 × O(log n) time, O(1) space.

**C++**
```cpp
int lowerBound(vector<int>& a, int x) {
    int n = a.size(), low = 0, high = n - 1, ans = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] >= x) { ans = mid; high = mid - 1; } else low = mid + 1;
    }
    return ans;
}
int upperBound(vector<int>& a, int x) {
    int n = a.size(), low = 0, high = n - 1, ans = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] > x) { ans = mid; high = mid - 1; } else low = mid + 1;
    }
    return ans;
}
vector<int> firstLastBounds(vector<int>& a, int x) {
    int lb = lowerBound(a, x);
    if (lb == (int)a.size() || a[lb] != x) return {-1, -1};
    return {lb, upperBound(a, x) - 1};
}
```

**Java**
```java
class Solution {
    static int lowerBound(int[] a, int x) {
        int n = a.length, low = 0, high = n - 1, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] >= x) { ans = mid; high = mid - 1; } else low = mid + 1;
        }
        return ans;
    }
    static int upperBound(int[] a, int x) {
        int n = a.length, low = 0, high = n - 1, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] > x) { ans = mid; high = mid - 1; } else low = mid + 1;
        }
        return ans;
    }
    static int[] firstLastBounds(int[] a, int x) {
        int lb = lowerBound(a, x);
        if (lb == a.length || a[lb] != x) return new int[]{-1, -1};
        return new int[]{lb, upperBound(a, x) - 1};
    }
}
```

#### Approach 3: Optimal (interview version) — plain binary search, written twice
Some interviewers won't accept "lower/upper bound" and ask for raw binary search. One search can't find both ends, so write two:
- **First occurrence:** if `arr[mid] == x`, set `first = mid` and keep looking **left** (`high = mid − 1`) for an earlier index. If `arr[mid] < x`, go right. Otherwise go left.
- **Last occurrence:** if `arr[mid] == x`, set `last = mid` and keep looking **right** (`low = mid + 1`). If `arr[mid] < x`, go right. Otherwise go left.

**Dry run** `x = 8` on `[2, 4, 6, 8, 8, 8, 11, 13]`:
- *First:*
  - mid 3 is 8 → first = 3, high = 2.
  - mid 1 is 4 < 8 → low = 2.
  - mid 2 is 6 < 8 → low = 3. Now low > high, so first = 3.
- *Last:*
  - mid 3 is 8 → last = 3, low = 4.
  - mid 5 is 8 → last = 5, low = 6.
  - mid 6 is 11 > 8 → high = 5. Stop: last = 5.

**Small optimisation:** compute `first` first. If it's −1, return `[-1, -1]` immediately and skip the second O(log n) search.

**Complexity:** 2 × O(log n) time, O(1) space.

**C++**
```cpp
int firstOccurrence(vector<int>& a, int x) {
    int low = 0, high = (int)a.size() - 1, first = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == x) { first = mid; high = mid - 1; }   // keep looking left
        else if (a[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return first;
}
int lastOccurrence(vector<int>& a, int x) {
    int low = 0, high = (int)a.size() - 1, last = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == x) { last = mid; low = mid + 1; }     // keep looking right
        else if (a[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return last;
}
vector<int> searchRange(vector<int>& nums, int target) {
    int first = firstOccurrence(nums, target);
    if (first == -1) return {-1, -1};
    return {first, lastOccurrence(nums, target)};
}
```

**Java**
```java
class Solution {
    static int firstOccurrence(int[] a, int x) {
        int low = 0, high = a.length - 1, first = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == x) { first = mid; high = mid - 1; }   // keep looking left
            else if (a[mid] < x) low = mid + 1;
            else high = mid - 1;
        }
        return first;
    }
    static int lastOccurrence(int[] a, int x) {
        int low = 0, high = a.length - 1, last = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == x) { last = mid; low = mid + 1; }     // keep looking right
            else if (a[mid] < x) low = mid + 1;
            else high = mid - 1;
        }
        return last;
    }
    public int[] searchRange(int[] nums, int target) {
        int first = firstOccurrence(nums, target);
        if (first == -1) return new int[]{-1, -1};
        return new int[]{first, lastOccurrence(nums, target)};
    }
}
```

#### Edge Cases & Pitfalls
- In the bounds version, check both `lb == n` and `arr[lb] != x` before trusting `lb`.
- Don't `return mid` on equality, as plain binary search does. Record it and keep searching in the useful direction.
- Empty array: both searches return −1 straight away.

#### Key Takeaways
- First occurrence is `lowerBound` (when `x` exists), and last occurrence is `upperBound − 1`.
- With raw binary search, "record and keep going" in the right direction turns plain search into first/last occurrence.

[↑ Contents](#contents) · [← Previous](#p109) · [Next →](#p111)

---

<a id="p111"></a>

### 7. Search in rotated sorted array-I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/search-in-rotated-sorted-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/search-in-rotated-sorted-array) | [Watch](https://youtu.be/r3pMQ8-Ad5s) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
A sorted array of **distinct** integers has been rotated at an unknown pivot. For example, `[0, 1, 2, 4, 5, 6, 7]` might become `[4, 5, 6, 7, 0, 1, 2]`. Given a `target`, return its index or −1, in **O(log n)** (LeetCode 33).

```text
nums = [7, 8, 9, 1, 2, 3, 4, 5, 6], target = 1  ->  3
nums = [4, 5, 6, 7, 0, 1, 2],       target = 3  ->  -1
nums = [1],                          target = 1  ->  0
```

#### Intuition
Plain binary search fails because the array as a whole isn't sorted. The key observation: **at any `mid`, at least one of the two halves `[low..mid]` and `[mid..high]` is sorted.** The rotation point lies in at most one of them.
- If `nums[low] <= nums[mid]`, the **left half is sorted**. If `nums[low] <= target < nums[mid]`, the target must be there (`high = mid − 1`). Otherwise eliminate the left half (`low = mid + 1`).
- Otherwise the **right half is sorted**. If `nums[mid] < target <= nums[high]`, go right (`low = mid + 1`). Otherwise go left (`high = mid − 1`).

So the method is: find the sorted half, check whether the target falls inside its range, and discard one half.

#### Approach 1: Brute Force — linear search
Scan for the target. This takes O(n) time and O(1) space.

**C++**
```cpp
int searchLinear(vector<int>& nums, int target) {
    for (int i = 0; i < (int)nums.size(); i++)
        if (nums[i] == target) return i;
    return -1;
}
```

**Java**
```java
class Solution {
    static int searchLinear(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++)
            if (nums[i] == target) return i;
        return -1;
    }
}
```

#### Approach 2: Optimal — binary search on the sorted half
**Dry run** `[7, 8, 9, 1, 2, 3, 4, 5, 6]`, `target = 1`:
- low 0, high 8: mid 4 holds 2. `nums[0] = 7 > 2`, so the right half `[2..6]` is sorted. 1 isn't in `(2, 6]`, so go left: `high = 3`.
- low 0, high 3: mid 1 holds 8. `7 <= 8`, so the left half `[7, 8]` is sorted. 1 isn't in `[7, 8)`, so go right: `low = 2`.
- low 2, high 3: mid 2 holds 9. `9 <= 9`, so the left half `[9]` is sorted. 1 isn't in it, so `low = 3`.
- low 3, high 3: mid 3 holds 1. Found at index **3**.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int search(vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        if (nums[low] <= nums[mid]) {                       // left half sorted
            if (nums[low] <= target && target < nums[mid]) high = mid - 1;
            else low = mid + 1;
        } else {                                            // right half sorted
            if (nums[mid] < target && target <= nums[high]) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}
```

**Java**
```java
class Solution {
    public int search(int[] nums, int target) {
        int low = 0, high = nums.length - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) return mid;
            if (nums[low] <= nums[mid]) {                       // left half sorted
                if (nums[low] <= target && target < nums[mid]) high = mid - 1;
                else low = mid + 1;
            } else {                                            // right half sorted
                if (nums[mid] < target && target <= nums[high]) low = mid + 1;
                else high = mid - 1;
            }
        }
        return -1;
    }
}
```

#### Edge Cases & Pitfalls
- Use `<=` in `nums[low] <= nums[mid]`. When `low == mid`, the one-element left half counts as sorted.
- The range checks must be inclusive on the outer end: `nums[low] <= target` and `target <= nums[high]`.
- An array that isn't rotated at all works too: the left half is always sorted.
- This version assumes **distinct** elements. With duplicates, `nums[low] == nums[mid] == nums[high]` makes it impossible to tell which half is sorted. That's the next problem.

#### Key Takeaways
- In a rotated sorted array, one half around `mid` is always sorted. Find it, then check whether the target lies in its range.
- This "identify the sorted half" idea also drives "minimum in rotated array" and "how many times rotated".

[↑ Contents](#contents) · [← Previous](#p110) · [Next →](#p112)

---

<a id="p112"></a>

### 8. Search in rotated sorted array-II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/search-in-rotated-sorted-array-ii) | [Watch](https://youtu.be/w2G2W8l__pc) |

#### Problem Statement
Same as "Search in Rotated Sorted Array I", but the array **may contain duplicates**. Return **true/false**: does `target` exist? (LeetCode 81.) We return a boolean, not an index, because the target may occur at several indices.

```text
nums = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], target = 3  ->  true
nums = [3, 1, 2, 3, 3, 3, 3],          target = 1  ->  true
nums = [2, 5, 6, 0, 0, 1, 2],          target = 3  ->  false
```

#### Intuition — where Part I breaks
Part I works by **identifying the sorted half** through comparisons of `nums[low]`, `nums[mid]` and `nums[high]`. Duplicates usually don't get in the way. In `[1, 2, 3, 4, 4, 5, 6, 7]`, for example, the comparisons still say which side is sorted.

The only failing case is **`nums[low] == nums[mid] == nums[high]`**. Take `[3, 1, 2, 3, 3, 3, 3]`: low, mid and high all hold 3, so the comparisons can't say which half is sorted, and the 1 could be on either side.

**Fix: shrink the search space.** We have already checked `nums[mid] != target`. Since `nums[low]` and `nums[high]` hold the same value, they aren't the target either. So do `low++`, `high--` and `continue`, repeating until the three values are no longer all equal. After that, the Part I logic applies unchanged.

#### Approach 1: Brute Force — linear search
Scan for the target. This takes O(n) time.

**C++**
```cpp
bool searchLinear(vector<int>& nums, int target) {
    for (int x : nums) if (x == target) return true;
    return false;
}
```

**Java**
```java
class Solution {
    static boolean searchLinear(int[] nums, int target) {
        for (int x : nums) if (x == target) return true;
        return false;
    }
}
```

#### Approach 2: Optimal — Part I plus the shrink step
**Complexity:**
- Average: O(log n).
- Worst case: about **O(n/2)**, which is O(n), on inputs like `[3, 3, 1, 3, 3, 3, 3]`, where you mostly shrink one element from each end.
- Space: O(1).

**C++**
```cpp
bool search(vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return true;
        if (nums[low] == nums[mid] && nums[mid] == nums[high]) {   // can't tell the sorted half
            low++; high--;
            continue;
        }
        if (nums[low] <= nums[mid]) {                               // left half sorted
            if (nums[low] <= target && target < nums[mid]) high = mid - 1;
            else low = mid + 1;
        } else {                                                    // right half sorted
            if (nums[mid] < target && target <= nums[high]) low = mid + 1;
            else high = mid - 1;
        }
    }
    return false;
}
```

**Java**
```java
class Solution {
    public boolean search(int[] nums, int target) {
        int low = 0, high = nums.length - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) return true;
            if (nums[low] == nums[mid] && nums[mid] == nums[high]) {   // can't tell the sorted half
                low++; high--;
                continue;
            }
            if (nums[low] <= nums[mid]) {                               // left half sorted
                if (nums[low] <= target && target < nums[mid]) high = mid - 1;
                else low = mid + 1;
            } else {                                                    // right half sorted
                if (nums[mid] < target && target <= nums[high]) low = mid + 1;
                else high = mid - 1;
            }
        }
        return false;
    }
}
```

#### Edge Cases & Pitfalls
- You need `continue` after shrinking. The new `low`, `mid`, `high` may be all equal again, so re-run the checks from the top.
- The shrink is only safe because `nums[mid]` has already been compared with the target.
- When all elements are equal and the target is absent, the loop degrades to linear time. That's unavoidable for this problem.

#### Key Takeaways
- To handle duplicates, start from the unique-element solution, find the exact condition that breaks it (`low == mid == high`), and patch only that case.
- Expect a worst case of O(n) once duplicates are allowed in rotated-array searches.

[↑ Contents](#contents) · [← Previous](#p111) · [Next →](#p113)

---

<a id="p113"></a>

### 9. Find minimum in Rotated Sorted Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-minimum-in-rotated-sorted-array) | [Watch](https://youtu.be/nhEMDKMB44g) |

#### Problem Statement
Given a rotated sorted array of **distinct** integers, return its **minimum element** (LeetCode 153).

```text
[4, 5, 6, 7, 0, 1, 2]  ->  0
[3, 4, 5, 1, 2]        ->  1
[4, 5, 1, 2, 3]        ->  1
[1, 2, 3, 4, 5]        ->  1   (not rotated)
```

#### Approach 1: Brute Force — linear minimum
One pass that keeps the smallest value seen. This takes O(n) time and O(1) space.

**C++**
```cpp
int findMinLinear(vector<int>& nums) {
    int mn = INT_MAX;
    for (int x : nums) mn = min(mn, x);
    return mn;
}
```

**Java**
```java
class Solution {
    static int findMinLinear(int[] nums) {
        int mn = Integer.MAX_VALUE;
        for (int x : nums) mn = Math.min(mn, x);
        return mn;
    }
}
```

#### Approach 2: Optimal — binary search, take the minimum of the sorted half
As in "Search in Rotated Sorted Array", **one half around `mid` is always sorted**. The unsorted half contains the rotation point, which is where the minimum sits. But the sorted half **may also** contain the minimum. In `[4, 5, 1, 2, 3]` the right half `[1, 2, 3]` is sorted and holds the 1, and in `[1, 2]` the sorted left half holds the minimum too. So we can't simply discard the sorted half.

The video's solution: **take the minimum of the sorted half, then eliminate that half.**
- If the left half is sorted (`nums[low] <= nums[mid]`), its smallest element is `nums[low]`. Set `ans = min(ans, nums[low])` and discard the left half: `low = mid + 1`.
- Otherwise the right half is sorted, and its smallest element is `nums[mid]`. Set `ans = min(ans, nums[mid])` and discard the right half: `high = mid − 1`.

**Dry run** `[4, 5, 6, 7, 0, 1, 2]` with `ans = ∞`:
- low 0, high 6: mid 3 holds 7. The left `[4..7]` is sorted, so `ans = 4` and `low = 4`.
- low 4, high 6: mid 5 holds 1. The left `[0, 1]` is sorted, so `ans = 0` and `low = 6`.
- low 6, high 6: mid 6 holds 2. The left `[2]` is sorted, so `ans` stays 0 and `low = 7`. Stop.

Answer: **0**.

**Optional optimisation.** If `nums[low] <= nums[high]`, the whole current search space is sorted. Then `nums[low]` is its minimum: take it and `break`. This happens once you've moved past the rotation point.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int findMin(vector<int>& nums) {
    int low = 0, high = (int)nums.size() - 1, ans = INT_MAX;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[low] <= nums[high]) {          // whole search space sorted
            ans = min(ans, nums[low]);
            break;
        }
        if (nums[low] <= nums[mid]) {           // left half sorted: its min is nums[low]
            ans = min(ans, nums[low]);
            low = mid + 1;
        } else {                                // right half sorted: its min is nums[mid]
            ans = min(ans, nums[mid]);
            high = mid - 1;
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    public int findMin(int[] nums) {
        int low = 0, high = nums.length - 1, ans = Integer.MAX_VALUE;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[low] <= nums[high]) {          // whole search space sorted
                ans = Math.min(ans, nums[low]);
                break;
            }
            if (nums[low] <= nums[mid]) {           // left half sorted: its min is nums[low]
                ans = Math.min(ans, nums[low]);
                low = mid + 1;
            } else {                                // right half sorted: its min is nums[mid]
                ans = Math.min(ans, nums[mid]);
                high = mid - 1;
            }
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- Use `nums[low] <= nums[mid]` with `<=`. For a one-element left half (`low == mid`), the half still counts as sorted.
- An array that isn't rotated triggers the "fully sorted" early break straight away.
- **Duplicates** (LeetCode 154) are left as homework in the video. Add the `low == mid == high → low++, high--` shrink from Search in Rotated Sorted Array II. *(not in video)* In that case also record `ans = min(ans, nums[low])` before shrinking, so the minimum isn't skipped.
- *From the video:* Striver keeps one consistent template (`low <= high`, `mid ± 1`) rather than the `low < high`, `high = mid` variants seen in forums.

#### Key Takeaways
- Whichever half is sorted, its first element is its minimum: record that minimum, then eliminate the half.
- If `nums[low] <= nums[high]`, the current range is already sorted and you can stop early.

[↑ Contents](#contents) · [← Previous](#p112) · [Next →](#p114)

---

<a id="p114"></a>

### 10. Find out how many times the array is rotated

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/rotation-count-sorted-array) | [Watch](https://youtu.be/jtSiWTPLwd0) |

#### Problem Statement
A sorted array of **distinct** integers has been rotated (right-rotated) some number of times. Find **how many times** it was rotated.

```text
[3, 4, 5, 1, 2]     ->  3   (sorted [1, 2, 3, 4, 5] rotated 3 times)
[1, 2, 4, 5, 7]     ->  0
[4, 5, 6, 7, 0, 1, 2] -> 4
```

#### Intuition
After `k` rotations, the original first element (the minimum) sits at index `k`. So **the number of rotations equals the index of the minimum element.** This is "Find Minimum in Rotated Sorted Array" plus tracking the *index* of the minimum.

#### Approach 1: Brute Force — linear scan for the minimum's index
This takes O(n) time and O(1) space.

**C++**
```cpp
int findKRotationLinear(vector<int>& arr) {
    int idx = 0;
    for (int i = 1; i < (int)arr.size(); i++)
        if (arr[i] < arr[idx]) idx = i;
    return idx;
}
```

**Java**
```java
class Solution {
    static int findKRotationLinear(int[] arr) {
        int idx = 0;
        for (int i = 1; i < arr.length; i++)
            if (arr[i] < arr[idx]) idx = i;
        return idx;
    }
}
```

#### Approach 2: Optimal — minimum-in-rotated-array binary search, tracking the index
Take the previous problem's code. Replace each `ans = min(ans, x)` with an explicit `if (x < ans) { ans = x; index = position; }`, and return `index`.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int findKRotation(vector<int>& arr) {
    int low = 0, high = (int)arr.size() - 1, ans = INT_MAX, index = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[low] <= arr[high]) {                 // search space already sorted
            if (arr[low] < ans) { ans = arr[low]; index = low; }
            break;
        }
        if (arr[low] <= arr[mid]) {                  // left half sorted
            if (arr[low] < ans) { ans = arr[low]; index = low; }
            low = mid + 1;
        } else {                                     // right half sorted
            if (arr[mid] < ans) { ans = arr[mid]; index = mid; }
            high = mid - 1;
        }
    }
    return index;
}
```

**Java**
```java
class Solution {
    static int findKRotation(int[] arr) {
        int low = 0, high = arr.length - 1, ans = Integer.MAX_VALUE, index = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[low] <= arr[high]) {                 // search space already sorted
                if (arr[low] < ans) { ans = arr[low]; index = low; }
                break;
            }
            if (arr[low] <= arr[mid]) {                  // left half sorted
                if (arr[low] < ans) { ans = arr[low]; index = low; }
                low = mid + 1;
            } else {                                     // right half sorted
                if (arr[mid] < ans) { ans = arr[mid]; index = mid; }
                high = mid - 1;
            }
        }
        return index;
    }
}
```

#### Edge Cases & Pitfalls
- A non-rotated array returns 0, because the minimum is at index 0.
- **Duplicates:** the video says to extend the solution with the shrink trick from Search in Rotated Sorted Array II. When shrinking, take care to keep the *first* index of the minimum.
- If the array was **left**-rotated, the count is `(n − index) % n`. *(not in video)*

#### Key Takeaways
- Number of rotations = index of the minimum.
- A small change to an earlier solution often solves a "new" problem.

[↑ Contents](#contents) · [← Previous](#p113) · [Next →](#p115)

---

<a id="p115"></a>

### 11. Single element in sorted array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Core | No | [LeetCode](https://leetcode.com/problems/single-element-in-a-sorted-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/single-element-in-a-sorted-array) | [Watch](https://youtu.be/AZOmHuHadxQ) |

#### Problem Statement
In a **sorted** array, every element appears exactly **twice** (so the copies are adjacent), except one element that appears **once**. Find that single element (LeetCode 540). Target: O(log n) time and O(1) space.

```text
[1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6]  ->  4
[3, 3, 7, 7, 10, 11, 11]           ->  10
[1]                                 ->  1
```

#### Approach 1: Brute Force — check neighbours
`arr[i]` is the single element when it differs from both neighbours. Handle the ends separately so indices `−1` and `n` are never read:
- `n == 1`: the answer is `arr[0]`.
- `i == 0`: single if `arr[0] != arr[1]`.
- `i == n−1`: single if `arr[n−1] != arr[n−2]`.
- Otherwise: single if `arr[i] != arr[i−1]` and `arr[i] != arr[i+1]`.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int singleNonDuplicateBrute(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return arr[0];
    for (int i = 0; i < n; i++) {
        if (i == 0) { if (arr[i] != arr[i + 1]) return arr[i]; }
        else if (i == n - 1) { if (arr[i] != arr[i - 1]) return arr[i]; }
        else if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1]) return arr[i];
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int singleNonDuplicateBrute(int[] arr) {
        int n = arr.length;
        if (n == 1) return arr[0];
        for (int i = 0; i < n; i++) {
            if (i == 0) { if (arr[i] != arr[i + 1]) return arr[i]; }
            else if (i == n - 1) { if (arr[i] != arr[i - 1]) return arr[i]; }
            else if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1]) return arr[i];
        }
        return -1;
    }
}
```

> *(not in video)* XOR-ing all the elements also gives the answer in O(n), because pairs cancel out: `x ^ x = 0`. This works even for unsorted input, but it ignores the sortedness that binary search exploits.

**C++**
```cpp
int singleNonDuplicateXor(vector<int>& arr) {
    int x = 0;
    for (int v : arr) x ^= v;
    return x;
}
```

**Java**
```java
class Solution {
    static int singleNonDuplicateXor(int[] arr) {
        int x = 0;
        for (int v : arr) x ^= v;
        return x;
    }
}
```

#### Approach 2: Optimal — binary search on the index parity
**Observation.** Write down the indices of `[1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6]`:
- **Left** of the single element, pairs sit at **(even, odd)** indices: (0,1), (2,3), (4,5).
- **Right** of it, the single element has shifted everything by one, so pairs sit at **(odd, even)**: (7,8), (9,10).

So at any `mid`:
- If `mid` is **odd** and `arr[mid−1] == arr[mid]`, or `mid` is **even** and `arr[mid] == arr[mid+1]`, we're on the **left** half. The single element is to the right, so `low = mid + 1`.
- Otherwise we're on the right half, so `high = mid − 1`.
- Before eliminating, **search**: if `arr[mid]` differs from both neighbours, it's the answer.

**Cleaner code by shrinking the search space.** Checking `mid−1` and `mid+1` would need bounds checks at indices 0 and n−1. Instead, test `arr[0]` and `arr[n−1]` separately up front, then binary search on `[1, n−2]`, where both neighbours always exist.

**Dry run** on the example above (n = 11, search space [1, 9]):
- low 1, high 9: mid 5 holds 3. Its left neighbour is 3, so it's not single. mid is odd and `arr[4] == arr[5]`, so we're on the left half: `low = 6`.
- low 6, high 9: mid 7 holds 5. Its right neighbour is 5, so it's not single. mid is odd, but `arr[6] = 4 ≠ 5`, so we're on the right half: `high = 6`.
- low 6, high 6: mid 6 holds 4, which differs from both 3 and 5. Answer: **4**.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int singleNonDuplicate(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n - 1] != arr[n - 2]) return arr[n - 1];
    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1]) return arr[mid];
        // on the left half -> eliminate it
        if ((mid % 2 == 1 && arr[mid] == arr[mid - 1]) ||
            (mid % 2 == 0 && arr[mid] == arr[mid + 1]))
            low = mid + 1;
        else
            high = mid - 1;      // on the right half -> eliminate it
    }
    return -1;                   // never reached for valid input
}
```

**Java**
```java
class Solution {
    public int singleNonDuplicate(int[] arr) {
        int n = arr.length;
        if (n == 1) return arr[0];
        if (arr[0] != arr[1]) return arr[0];
        if (arr[n - 1] != arr[n - 2]) return arr[n - 1];
        int low = 1, high = n - 2;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1]) return arr[mid];
            // on the left half -> eliminate it
            if ((mid % 2 == 1 && arr[mid] == arr[mid - 1]) ||
                (mid % 2 == 0 && arr[mid] == arr[mid + 1]))
                low = mid + 1;
            else
                high = mid - 1;      // on the right half -> eliminate it
        }
        return -1;                   // never reached for valid input
    }
}
```

#### Edge Cases & Pitfalls
- `n == 1`, or the single element sitting at index 0 or n−1, are handled before the loop.
- The final `return −1` is just a dummy so the function compiles. A valid input always returns inside the loop.
- Keep the template consistent: `low <= high`, `mid ± 1`. Forum solutions often use `low < high` / `high = mid` variants.

#### Key Takeaways
- The single element breaks the (even, odd) pairing. Before it pairs are (even, odd), after it they're (odd, even), and that tells you which half to drop.
- Shrinking the search space to `[1, n−2]` removes the boundary checks and makes the code cleaner.

[↑ Contents](#contents) · [← Previous](#p114) · [Next →](#p116)

---

<a id="p116"></a>

### 12. Count Occurrences in a Sorted Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › Logic Building | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-occurrences-in-a-sorted-array) | [Watch](https://youtu.be/hjR1IYVx9lY) |

#### Problem Statement
Given a sorted array (with duplicates) and a number `x`, return **how many times `x` occurs**.

```text
arr = [1, 1, 2, 2, 2, 2, 3], x = 2  ->  4
arr = [1, 1, 2, 2, 2, 2, 3], x = 4  ->  0
```

#### Approach 1: Brute Force — linear count
Count the elements equal to `x`. This takes O(n) time and O(1) space.

**C++**
```cpp
int countLinear(vector<int>& arr, int x) {
    int cnt = 0;
    for (int v : arr) if (v == x) cnt++;
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countLinear(int[] arr, int x) {
        int cnt = 0;
        for (int v : arr) if (v == x) cnt++;
        return cnt;
    }
}
```

#### Approach 2: Optimal — first and last occurrence
Reuse the previous problem: **count = last − first + 1**, or 0 if `first == −1`. Equivalently, `upperBound(x) − lowerBound(x)`.

**Complexity:** 2 × O(log n) time, O(1) space.

**C++**
```cpp
int firstOcc(vector<int>& a, int x) {
    int low = 0, high = (int)a.size() - 1, first = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == x) { first = mid; high = mid - 1; }
        else if (a[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return first;
}
int lastOcc(vector<int>& a, int x) {
    int low = 0, high = (int)a.size() - 1, last = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == x) { last = mid; low = mid + 1; }
        else if (a[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return last;
}
int countOccurrences(vector<int>& arr, int x) {
    int first = firstOcc(arr, x);
    if (first == -1) return 0;
    return lastOcc(arr, x) - first + 1;
}

// One-liner with the STL
int countOccurrencesSTL(vector<int>& arr, int x) {
    return upper_bound(arr.begin(), arr.end(), x) - lower_bound(arr.begin(), arr.end(), x);
}
```

**Java**
```java
class Solution {
    static int firstOcc(int[] a, int x) {
        int low = 0, high = a.length - 1, first = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == x) { first = mid; high = mid - 1; }
            else if (a[mid] < x) low = mid + 1;
            else high = mid - 1;
        }
        return first;
    }
    static int lastOcc(int[] a, int x) {
        int low = 0, high = a.length - 1, last = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == x) { last = mid; low = mid + 1; }
            else if (a[mid] < x) low = mid + 1;
            else high = mid - 1;
        }
        return last;
    }
    static int countOccurrences(int[] arr, int x) {
        int first = firstOcc(arr, x);
        if (first == -1) return 0;
        return lastOcc(arr, x) - first + 1;
    }
}
```

#### Key Takeaways
- Count of `x` in a sorted array = `last − first + 1` = `upperBound − lowerBound`.
- The video solves this with the previous problem's code, which shows why lower and upper bound are worth memorising.

[↑ Contents](#contents) · [← Previous](#p115) · [Next →](#p117)

---

## On answers

<a id="p117"></a>

### 13. Find square root of a number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › On answers | Core | No | [LeetCode](https://leetcode.com/problems/sqrtx/) | [Watch](https://youtu.be/Bsv3FPUX_BA) |

#### Problem Statement
Given a non-negative integer `n`, return **⌊√n⌋**, the floor of its square root, without using `sqrt` (LeetCode 69).

```text
n = 25 -> 5     n = 30 -> 5     n = 35 -> 5     n = 36 -> 6     n = 28 -> 5
```

Equivalently: find the **maximum integer `x` with `x · x <= n`**.

#### Approach 1: Brute Force — linear search over candidates
Try `i = 1, 2, 3, …`. While `i · i <= n`, record `ans = i`. Stop at the first `i` with `i · i > n`; nothing larger can work either.

**Complexity:** O(√n) iterations (the video loosely calls it "near about O(n)"), O(1) space.

**C++**
```cpp
int floorSqrtLinear(int n) {
    long long ans = 0;
    for (long long i = 1; i <= n; i++) {
        if (i * i <= n) ans = i;
        else break;
    }
    return (int)ans;
}
```

**Java**
```java
class Solution {
    static int floorSqrtLinear(int n) {
        long ans = 0;
        for (long i = 1; i <= n; i++) {
            if (i * i <= n) ans = i;
            else break;
        }
        return (int) ans;
    }
}
```

#### Approach 2: Optimal — Binary Search on Answers
**The pattern.** Lay out the candidates 1, 2, …, n. For `n = 28`, the values 1–5 are **possible** (`x² <= 28`) and 6, 7, … are **not possible**. Whenever the answers are possible up to some point and impossible after it (a monotonic yes/no), and you want the max or min such value, **binary search on the answer range**.

- Search space `[low, high] = [1, n]`. The answer can never exceed `n`.
- `mid · mid <= n` means `mid` is possible. Store it and look for something **bigger**: `low = mid + 1`.
- Otherwise `mid` is impossible, and so is everything above it: `high = mid − 1`.

**Dry run** `n = 28`:
- [1, 28]: mid 14. 196 > 28 → high = 13.
- [1, 13]: mid 7. 49 > 28 → high = 6.
- [1, 6]: mid 3. 9 ≤ 28 → ans = 3, low = 4.
- [4, 6]: mid 5. 25 ≤ 28 → ans = 5, low = 6.
- [6, 6]: mid 6. 36 > 28 → high = 5. Stop. Answer: **5**.

**Why `high` ends on the answer.** `low` starts in the possible zone and `high` in the impossible zone. They move toward each other until they cross. At that point `high` sits on the last possible value (the answer), and `low` on the first impossible one. So you can return `high` and skip the `ans` variable.

**Overflow:** `mid · mid` overflows `int` when `n ≈ 10⁹`. Compute it in `long long` / `long`.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int floorSqrt(int n) {
    long long low = 1, high = n;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (mid * mid <= n) low = mid + 1;   // possible -> look for a bigger one
        else high = mid - 1;                 // not possible -> go smaller
    }
    return (int)high;                        // high ends on the last possible value
}
```

**Java**
```java
class Solution {
    public int mySqrt(int n) {
        long low = 1, high = n;
        while (low <= high) {
            long mid = low + (high - low) / 2;
            if (mid * mid <= n) low = mid + 1;   // possible -> look for a bigger one
            else high = mid - 1;                 // not possible -> go smaller
        }
        return (int) high;                       // high ends on the last possible value
    }
}
```

#### Edge Cases & Pitfalls
- `n = 0`: the loop never runs (`low = 1 > high = 0`), so `high = 0` is returned, which is correct.
- `n = 1` returns 1.
- Use 64-bit for `mid * mid`.

#### Key Takeaways — "Binary Search on Answers"
- Use it when you know the **range** of possible answers and the problem asks for the **min/max value satisfying a condition**, where the condition is monotonic over that range.
- The template is: binary search over the range, then a **check function** (here `mid² <= n`) decides which half to drop.
- The next ten or so problems (Nth root, Koko, bouquets, ship capacity, …) all reuse this template with a different check function.

[↑ Contents](#contents) · [← Previous](#p116) · [Next →](#p118)

---

<a id="p118"></a>

### 14. Find Nth root of a number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › On answers | Core | Yes | — | [Watch](https://youtu.be/WjpswYrS2nY) |

#### Problem Statement
Given integers `n` and `m`, find the **n-th root of `m`**.
- **Sheet / takeuforward version:** return the integer `x` with `xⁿ = m`, or −1 if `m` is not a perfect n-th power.
- **Version solved in this video:** return the real n-th root to a given number of decimal places.

```text
n = 3, m = 27  ->  3
n = 4, m = 69  ->  -1          (integer version: no integer x with x^4 = 69)
n = 4, m = 15  ->  1.96798...  (decimal version, 5 places)
```

#### Intuition
`f(x) = xⁿ` is **monotonically increasing** for x ≥ 1: 1³ = 1, 2³ = 8, 3³ = 27, 4³ = 64, … Binary search works on *any* monotonic search space, not only arrays. The answer lies in `[1, m]`, because even the 1st root of `m` is `m` itself. So we binary search that range and compare `midⁿ` with `m`.

#### Approach 1: Brute Force — try every integer (integer version) *(not in video)*
For `x = 1, 2, …`, compute `xⁿ`. Return `x` if it equals `m`. Stop as soon as it exceeds `m`.

**Complexity:** O(m^(1/n) · n) time, O(1) space.

**C++**
```cpp
int nthRootLinear(int n, int m) {
    for (long long x = 1; x <= m; x++) {
        long long p = 1;
        for (int i = 0; i < n && p <= m; i++) p *= x;
        if (p == m) return (int)x;
        if (p > m) break;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int nthRootLinear(int n, int m) {
        for (long x = 1; x <= m; x++) {
            long p = 1;
            for (int i = 0; i < n && p <= m; i++) p *= x;
            if (p == m) return (int) x;
            if (p > m) break;
        }
        return -1;
    }
}
```

#### Approach 2: Binary search on real numbers (decimal answer) — as in the video
- Search space: `low = 1`, `high = m`.
- Repeat while `high − low > ε`. Use `ε = 1e−6` for an answer correct to 5 decimal places, i.e. one digit more precision than required.
- `mid = (low + high) / 2.0`. Compute `midⁿ` with a `multiply` loop that runs `n` times.
  - If `midⁿ < m`, the root is larger: `low = mid`.
  - Otherwise: `high = mid`.
- With real numbers we assign `mid` itself (not `mid ± 1`), and the loop stops when the interval is tiny. At that point `low` and `high` agree to the required precision.

**Dry run** (`n = 3`, `m = 27`): [1, 27] → mid 14, 14³ > 27 → [1, 14] → mid 7.5 → [1, 7.5] → mid 4.25 → [1, 4.25] → mid 2.625, 2.625³ < 27 → [2.625, 4.25] → mid 3.4375 → [2.625, 3.4375] → … converges to 3.

**Complexity:** treat the space as `m · 10ᵈ` discrete points for `d` decimal places. That's `log₂(m · 10ᵈ)` iterations, each doing `n` multiplications, so **O(n · log₂(m · 10ᵈ))** time and O(1) space.

**C++**
```cpp
double multiply(double x, int n) {
    double ans = 1.0;
    for (int i = 0; i < n; i++) ans *= x;
    return ans;
}
double nthRootReal(int n, int m) {
    double low = 1, high = m, eps = 1e-6;
    if (m < 1) low = m, high = 1;            // roots of values in (0,1) lie in (m,1)  (not in video)
    while (high - low > eps) {
        double mid = (low + high) / 2.0;
        if (multiply(mid, n) < m) low = mid;
        else high = mid;
    }
    return low;                               // low ≈ high to ~6 decimals
}
```

**Java**
```java
class Solution {
    static double multiply(double x, int n) {
        double ans = 1.0;
        for (int i = 0; i < n; i++) ans *= x;
        return ans;
    }
    static double nthRootReal(int n, int m) {
        double low = 1, high = m, eps = 1e-6;
        if (m < 1) { low = m; high = 1; }     // roots of values in (0,1) lie in (m,1)  (not in video)
        while (high - low > eps) {
            double mid = (low + high) / 2.0;
            if (multiply(mid, n) < m) low = mid;
            else high = mid;
        }
        return low;                            // low ≈ high to ~6 decimals
    }
}
```

#### Approach 3: Binary search on integers (sheet version) *(not in video — the integer variant in the newer playlist)*
This is the standard integer template on `[1, m]`. The check function computes `midⁿ` but **stops multiplying as soon as the product exceeds `m`**. That avoids overflow (e.g. `mid = 10⁵`, `n = 10`) and saves work. It returns 1 if `midⁿ == m`, 0 if `midⁿ < m`, 2 if `midⁿ > m`.

**Complexity:** O(n · log m) time, O(1) space.

**C++**
```cpp
// 1 -> mid^n == m, 0 -> mid^n < m, 2 -> mid^n > m
int powCheck(long long mid, int n, long long m) {
    long long ans = 1;
    for (int i = 0; i < n; i++) {
        ans *= mid;
        if (ans > m) return 2;      // early exit: no overflow
    }
    return ans == m ? 1 : 0;
}
int NthRoot(int n, int m) {
    long long low = 1, high = m;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        int r = powCheck(mid, n, m);
        if (r == 1) return (int)mid;
        if (r == 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    // 1 -> mid^n == m, 0 -> mid^n < m, 2 -> mid^n > m
    static int powCheck(long mid, int n, long m) {
        long ans = 1;
        for (int i = 0; i < n; i++) {
            ans *= mid;
            if (ans > m) return 2;      // early exit: no overflow
        }
        return ans == m ? 1 : 0;
    }
    public int NthRoot(int n, int m) {
        long low = 1, high = m;
        while (low <= high) {
            long mid = low + (high - low) / 2;
            int r = powCheck(mid, n, m);
            if (r == 1) return (int) mid;
            if (r == 0) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }
}
```

#### Edge Cases & Pitfalls
- **Overflow:** never compute `midⁿ` in full with integers. Exit early once the product exceeds `m`. `pow()` with doubles can also be off by rounding for large values.
- **Real version:** use `mid` (not `mid ± 1`) and stop on `high − low > ε`. Pick ε one decimal place finer than the precision you need.
- `m = 1` returns 1 for any `n`. If `m = 0` is allowed, handle it separately (the root is 0).

#### Key Takeaways
- Binary search applies to any **monotonic** function over a known range. For real-valued answers, shrink the interval until it's smaller than ε.
- For integer roots, use a check function with an early break. The same idea (stop once the result "exceeds") recurs throughout binary search on answers.

[↑ Contents](#contents) · [← Previous](#p117) · [Next →](#p119)

---

<a id="p119"></a>

### 15. Find the smallest divisor

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › On answers | Core | No | [LeetCode](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-the-smallest-divisor-given-a-threshold) | [Watch](https://youtu.be/UvBKTVaG6U8) |

#### Problem Statement
Given an array `nums` of positive integers and an integer `threshold`, pick a **positive divisor `d`**. Divide every element by `d`, round each result **up** (ceil), and add them up. Return the **smallest `d`** for which this sum is `<= threshold` (LeetCode 1283).

```text
nums = [1, 2, 5, 9], threshold = 6  ->  5
  d = 4: ceil(1/4)+ceil(2/4)+ceil(5/4)+ceil(9/4) = 1+1+2+3 = 7 > 6   x
  d = 5: 1+1+1+2 = 5 <= 6                                           ✓ (smallest)
nums = [1, 2, 5, 9], threshold = 7  ->  3
```

#### Intuition — the answer range and monotonicity
- `d >= 1`. Division by 0 isn't allowed, and negative divisors aren't part of the problem.
- With `d = max(nums)`, every term is 1, so the sum is `n`, the minimum possible. A larger `d` can't reduce it further. So the answer lies in **`[1, max(nums)]`**.
- As `d` grows, the sum can only shrink or stay the same. That makes the outcome monotonic: not possible, not possible, …, possible, possible. For threshold 7 the results go ✗ ✗ ✓ ✓ ✓ …, so we want the **first possible** value, and binary search on answers fits.

#### Approach 1: Brute Force — try every divisor
For `d = 1 … max`, compute the sum of ceilings and return the first `d` whose sum is `<= threshold`.

**Complexity:** O(max · n) time, O(1) space.

**C++**
```cpp
long long sumOfDivisions(vector<int>& nums, int d) {
    long long s = 0;
    for (int x : nums) s += (x + d - 1) / d;        // integer ceil(x / d)
    return s;
}
int smallestDivisorBrute(vector<int>& nums, int threshold) {
    int mx = *max_element(nums.begin(), nums.end());
    for (int d = 1; d <= mx; d++)
        if (sumOfDivisions(nums, d) <= threshold) return d;
    return -1;
}
```

**Java**
```java
class Solution {
    static long sumOfDivisions(int[] nums, int d) {
        long s = 0;
        for (int x : nums) s += (x + d - 1) / d;    // integer ceil(x / d)
        return s;
    }
    static int smallestDivisorBrute(int[] nums, int threshold) {
        int mx = Arrays.stream(nums).max().getAsInt();
        for (int d = 1; d <= mx; d++)
            if (sumOfDivisions(nums, d) <= threshold) return d;
        return -1;
    }
}
```

#### Approach 2: Optimal — binary search on the divisor
- Search space: `low = 1`, `high = max`.
- If `sum(mid) <= threshold`, then `mid` is possible. Record it and look for a **smaller** divisor: `high = mid − 1`.
- Otherwise `mid` is too small, so `low = mid + 1`.

When the loop ends, `low` has landed on the first possible divisor. This is the "opposite polarity" idea: `low` started in the impossible zone and finishes in the possible zone. So return `low` (or the stored `ans`).

**Dry run** `[1, 2, 5, 9]`, `threshold = 7`:
- [1, 9]: mid 5, sum 5 ≤ 7, possible → ans 5, high 4.
- [1, 4]: mid 2, sum 1+1+3+5 = 10 > 7 → low 3.
- [3, 4]: mid 3, sum 1+1+2+3 = 7 ≤ 7 → ans 3, high 2. Stop.

Answer: **3**.

**Complexity:** O(n · log(max)) time, O(1) space.

**C++**
```cpp
long long sumDiv(vector<int>& nums, int d) {
    long long s = 0;
    for (int x : nums) s += (x + d - 1) / d;
    return s;
}
int smallestDivisor(vector<int>& nums, int threshold) {
    if ((int)nums.size() > threshold) return -1;        // even d = max gives sum n
    int low = 1, high = *max_element(nums.begin(), nums.end());
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (sumDiv(nums, mid) <= threshold) high = mid - 1;   // possible -> try smaller
        else low = mid + 1;
    }
    return low;                                         // first possible divisor
}
```

**Java**
```java
class Solution {
    static long sumDiv(int[] nums, int d) {
        long s = 0;
        for (int x : nums) s += (x + d - 1) / d;
        return s;
    }
    public int smallestDivisor(int[] nums, int threshold) {
        if (nums.length > threshold) return -1;             // even d = max gives sum n
        int low = 1, high = 0;
        for (int x : nums) high = Math.max(high, x);
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (sumDiv(nums, mid) <= threshold) high = mid - 1;   // possible -> try smaller
            else low = mid + 1;
        }
        return low;                                         // first possible divisor
    }
}
```

#### Edge Cases & Pitfalls
- **Ceil division:** `ceil(x / d)` with ints truncates first. Either cast to double (`ceil((double)x / d)`, as in the video) or use `(x + d − 1) / d`.
- **Impossible case:** the smallest achievable sum is `n`, at `d = max`. If `n > threshold`, no divisor works. LeetCode guarantees an answer, but interviewers may ask you to return −1.
- Accumulate the sum in `long long` / `long` to be safe.

#### Key Takeaways
- Use binary search on answers when you're asked for the smallest `d` satisfying a monotonic condition, with a known range `[1, max]`.
- The check function is "sum of ceilings ≤ threshold". Koko Eating Bananas is the same problem with a different story.

[↑ Contents](#contents) · [← Previous](#p118) · [Next →](#p120)

---

<a id="p120"></a>

### 16. Koko eating bananas

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › On answers | Pro | No | [LeetCode](https://leetcode.com/problems/koko-eating-bananas/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/koko-eating-bananas) | [Watch](https://youtu.be/qyfekrNni90) |

#### Problem Statement
There are `n` piles of bananas, `piles[i]` in pile `i`, and the guards return in `h` hours. Koko chooses an eating speed `k` (bananas per hour). Each hour she eats `k` bananas from **one** pile. If the pile has fewer than `k`, she finishes it and **waits out the rest of that hour**; she can't move to the next pile in the same hour. Return the **minimum integer `k`** that lets her finish every pile within `h` hours (LeetCode 875).

```text
piles = [3, 6, 7, 11], h = 8  ->  4
  k = 2: ceil(3/2)+ceil(6/2)+ceil(7/2)+ceil(11/2) = 2+3+4+6 = 15 > 8   x
  k = 3: 1+2+3+4 = 10 > 8                                            x
  k = 4: 1+2+2+3 = 8 <= 8                                            ✓ (minimum)
piles = [30, 11, 23, 4, 20], h = 5  ->  30
```

#### Intuition
- Pile `i` takes **`ceil(piles[i] / k)`** hours. With 3 bananas at 2 per hour, that's 1.5 hours, but the leftover half-hour can't be carried over, so it counts as 2.
- **Range of answers:** at least 1. At most `max(piles)`: at that speed every pile takes exactly 1 hour, and a faster speed (13, 14, …) still takes 1 hour per pile. So `k ∈ [1, max(piles)]`.
- **Monotonic:** a higher speed never needs more hours. For `[3, 6, 7, 11]`, `h = 8`, the speeds 1–3 are not possible and 4, 5, …, 11 are. We want the first possible one, so binary search on answers applies.
- Choose the **tightest** range you can justify. Binary search would still work on `[1, 100]`, but the range length sets the cost.

#### Approach 1: Brute Force — try every speed
For `k = 1 … max`, compute the total hours. Return the first `k` whose total is `<= h`.

**Complexity:** O(max(piles) · n) time, which gets TLE on large inputs. O(1) space.

**C++**
```cpp
long long totalHours(vector<int>& piles, int k) {
    long long hrs = 0;
    for (int p : piles) hrs += (p + (long long)k - 1) / k;   // ceil(p / k)
    return hrs;
}
int minEatingSpeedBrute(vector<int>& piles, int h) {
    int mx = *max_element(piles.begin(), piles.end());
    for (int k = 1; k <= mx; k++)
        if (totalHours(piles, k) <= h) return k;
    return mx;
}
```

**Java**
```java
class Solution {
    static long totalHours(int[] piles, int k) {
        long hrs = 0;
        for (int p : piles) hrs += (p + (long) k - 1) / k;   // ceil(p / k)
        return hrs;
    }
    static int minEatingSpeedBrute(int[] piles, int h) {
        int mx = 0;
        for (int p : piles) mx = Math.max(mx, p);
        for (int k = 1; k <= mx; k++)
            if (totalHours(piles, k) <= h) return k;
        return mx;
    }
}
```

#### Approach 2: Optimal — binary search on the speed
- `low = 1`, `high = max(piles)`.
- `mid` is possible if `totalHours(mid) <= h`. Record it and try **smaller**: `high = mid − 1`.
- Otherwise she's too slow, so `low = mid + 1`.

**Dry run** `[3, 6, 7, 11]`, `h = 8`:
- [1, 11]: mid 6, hours 1+1+2+2 = 6 ≤ 8, possible → ans 6, high 5.
- [1, 5]: mid 3, hours 10 > 8 → low 4.
- [4, 5]: mid 4, hours 8 ≤ 8 → ans 4, high 3. Stop.

Answer: **4**.

**Opposite polarity:** `low` starts in the "not possible" zone and `high` in the "possible" zone. When they cross, they've swapped roles, so `low` points at the first possible speed. Return `low`; there's no need for an `ans` variable.

**Complexity:** O(n · log(max(piles))) time, O(1) space.

**C++**
```cpp
long long hoursAt(vector<int>& piles, int k) {
    long long hrs = 0;
    for (int p : piles) hrs += (p + (long long)k - 1) / k;
    return hrs;
}
int minEatingSpeed(vector<int>& piles, int h) {
    int low = 1, high = *max_element(piles.begin(), piles.end());
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (hoursAt(piles, mid) <= h) high = mid - 1;   // possible -> try slower
        else low = mid + 1;                             // too slow -> speed up
    }
    return low;
}
```

**Java**
```java
class Solution {
    static long hoursAt(int[] piles, int k) {
        long hrs = 0;
        for (int p : piles) hrs += (p + (long) k - 1) / k;
        return hrs;
    }
    public int minEatingSpeed(int[] piles, int h) {
        int low = 1, high = 0;
        for (int p : piles) high = Math.max(high, p);
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hoursAt(piles, mid) <= h) high = mid - 1;   // possible -> try slower
            else low = mid + 1;                             // too slow -> speed up
        }
        return low;
    }
}
```

#### Edge Cases & Pitfalls
- **Ceil with integers:** `p / k` truncates. Cast to double before `ceil` (as in the video), or use `(p + k − 1) / k`.
- **Overflow:** the total hours can exceed `int`, since there are up to 10⁴ piles of up to 10⁹ each at `k = 1`. Accumulate in `long long` / `long`.
- `h >= n` is guaranteed, so `k = max` always works and an answer always exists.

#### Key Takeaways
- This is "Smallest Divisor ≤ Threshold" with bananas: minimise `k` subject to `Σ ceil(pᵢ / k) ≤ h`.
- Recipe for binary search on answers: find the range, write the check function, binary search for the first or last "possible" value, and return `low` or `high` by the opposite-polarity rule.

[↑ Contents](#contents) · [← Previous](#p119) · [Next →](#p121)

---

<a id="p121"></a>

### 17. Minimum days to make M bouquets

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › On answers | Pro | No | [LeetCode](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/minimum-days-to-make-m-bouquets) | [Watch](https://youtu.be/TXAuxeYBTdg) |

#### Problem Statement
`bloomDay[i]` is the day flower `i` blooms. To make **one bouquet** you need **`k` adjacent** bloomed flowers, and each flower can be used once. Return the **minimum number of days** to wait so you can make **`m` bouquets**, or −1 if that's impossible (LeetCode 1482).

```text
bloomDay = [7, 7, 7, 7, 13, 11, 12, 7], m = 2, k = 3  ->  12
  day 12: bloomed = Y Y Y Y _ Y Y Y   -> runs 4 and 3 -> 4/3 + 3/3 = 2 bouquets ✓
  day 11: bloomed = Y Y Y Y _ Y _ Y   -> runs 4, 1, 1 -> 1 bouquet            x
bloomDay = [1, 10, 3, 10, 2], m = 3, k = 2           ->  -1   (needs 6 flowers, only 5 exist)
```

#### Intuition
- **Impossible case:** you need `m · k` flowers. If `m · k > n`, it can't be done even after every flower blooms, so return −1. In every other case it is possible: by day `max(bloomDay)` everything has bloomed, and you can just take adjacent runs.
- **Range:** before day `min(bloomDay)` nothing has bloomed, and by day `max(bloomDay)` everything has. So the answer lies in `[min, max]`. Keep the range as tight as possible; a looser one also works but costs more.
- **Monotonic:** if day `d` works, every later day works too, because more flowers have bloomed. So the days go not-possible, …, possible, possible, and we want the first possible day.

**Check function `possible(day)`:** walk through the array counting **consecutive** flowers with `bloomDay[i] <= day`. When you hit an unbloomed flower, add `cnt / k` bouquets and reset `cnt = 0`. **After the loop, add `cnt / k` once more** for the final run. Return whether `bouquets >= m`.

#### Approach 1: Brute Force — try every day from min to max
**Complexity:** O((max − min + 1) · n) time, O(1) space.

**C++**
```cpp
bool possible(vector<int>& bloomDay, int day, int m, int k) {
    int cnt = 0;
    long long bouquets = 0;
    for (int b : bloomDay) {
        if (b <= day) cnt++;
        else { bouquets += cnt / k; cnt = 0; }
    }
    bouquets += cnt / k;                         // last run
    return bouquets >= m;
}
int minDaysBrute(vector<int>& bloomDay, int m, int k) {
    if ((long long)m * k > (long long)bloomDay.size()) return -1;
    int mn = *min_element(bloomDay.begin(), bloomDay.end());
    int mx = *max_element(bloomDay.begin(), bloomDay.end());
    for (int d = mn; d <= mx; d++)
        if (possible(bloomDay, d, m, k)) return d;
    return -1;
}
```

**Java**
```java
class Solution {
    static boolean possible(int[] bloomDay, int day, int m, int k) {
        int cnt = 0;
        long bouquets = 0;
        for (int b : bloomDay) {
            if (b <= day) cnt++;
            else { bouquets += cnt / k; cnt = 0; }
        }
        bouquets += cnt / k;                         // last run
        return bouquets >= m;
    }
    static int minDaysBrute(int[] bloomDay, int m, int k) {
        if ((long) m * k > bloomDay.length) return -1;
        int mn = Integer.MAX_VALUE, mx = Integer.MIN_VALUE;
        for (int b : bloomDay) { mn = Math.min(mn, b); mx = Math.max(mx, b); }
        for (int d = mn; d <= mx; d++)
            if (possible(bloomDay, d, m, k)) return d;
        return -1;
    }
}
```

#### Approach 2: Optimal — binary search on the day
- `low = min`, `high = max`.
- If `possible(mid)`, then `mid` may be the answer. Look for an earlier day: `high = mid − 1`.
- Otherwise `low = mid + 1`.
- Return `low`. By opposite polarity it ends on the first possible day.

**Dry run** `[7, 7, 7, 7, 13, 11, 12, 7]`, `m = 2`, `k = 3`:
- [7, 13]: mid 10, not possible → low 11.
- [11, 13]: mid 12, possible → high 11.
- [11, 11]: mid 11, not possible → low 12. Stop. Answer: **12**.

**Complexity:** O(n · log(max − min + 1)) time, O(1) space.

**C++**
```cpp
bool canMake(vector<int>& bloomDay, int day, int m, int k) {
    int cnt = 0;
    long long bouquets = 0;
    for (int b : bloomDay) {
        if (b <= day) cnt++;
        else { bouquets += cnt / k; cnt = 0; }
    }
    bouquets += cnt / k;
    return bouquets >= m;
}
int minDays(vector<int>& bloomDay, int m, int k) {
    if ((long long)m * k > (long long)bloomDay.size()) return -1;   // impossible
    int low = *min_element(bloomDay.begin(), bloomDay.end());
    int high = *max_element(bloomDay.begin(), bloomDay.end());
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canMake(bloomDay, mid, m, k)) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}
```

**Java**
```java
class Solution {
    static boolean canMake(int[] bloomDay, int day, int m, int k) {
        int cnt = 0;
        long bouquets = 0;
        for (int b : bloomDay) {
            if (b <= day) cnt++;
            else { bouquets += cnt / k; cnt = 0; }
        }
        bouquets += cnt / k;
        return bouquets >= m;
    }
    public int minDays(int[] bloomDay, int m, int k) {
        if ((long) m * k > bloomDay.length) return -1;   // impossible
        int low = Integer.MAX_VALUE, high = Integer.MIN_VALUE;
        for (int b : bloomDay) { low = Math.min(low, b); high = Math.max(high, b); }
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canMake(bloomDay, mid, m, k)) high = mid - 1;
            else low = mid + 1;
        }
        return low;
    }
}
```

#### Edge Cases & Pitfalls
- **Overflow in `m · k`:** both can be up to 10⁶, so cast to `long long` / `long` before multiplying (the video points this out).
- **Don't forget the final run** after the loop. In the example, the last three flowers form the second bouquet.
- **Adjacency matters:** count consecutive bloomed flowers, not the total number bloomed.

#### Key Takeaways
- Answer range `[min, max]`, monotonic check "can I make m bouquets by day d?", and we want the first possible day.
- Handle the impossible case first (`m · k > n`). After that, an answer is guaranteed and `low` holds it.

[↑ Contents](#contents) · [← Previous](#p120) · [Next →](#p122)

---

<a id="p122"></a>

### 18. Capacity to Ship Packages Within D Days

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › On answers | Pro | No | [LeetCode](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/capacity-to-ship-packages-within-d-days) | [Watch](https://youtu.be/MG-Ac4TAvTY) |

#### Problem Statement
Packages with weights `weights[i]` must be shipped **in the given order** within `days` days. The ship sails once per day and is loaded with a contiguous run of packages, never more than its capacity. Return the **least ship capacity** that ships everything within `days` (LeetCode 1011).

```text
weights = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], days = 5  ->  15
  capacity 10: [1,2,3,4] [5] [6] [7] [8] [9] [10]          -> 7 days  x
  capacity 15: [1,2,3,4,5] [6,7] [8] [9] [10]              -> 5 days  ✓
```

#### Intuition
- **Range:**
  - The capacity must be at least `max(weights)`. Otherwise the heaviest package can never be loaded.
  - It never needs to exceed `sum(weights)`, because that capacity ships everything in one day.
  - So the answer lies in **`[max, sum]`**.
- **Monotonic:** a bigger ship never needs more days. The capacities go not-possible …, then possible …. We want the first possible one, so we binary search on the answer.

**Check function `daysRequired(cap)`:** start with `days = 1` and `load = 0`. For each weight `w`, if `load + w > cap`, start a new day (`days++`, `load = w`); otherwise `load += w`.

#### Approach 1: Brute Force — try every capacity from max to sum
**Complexity:** O((sum − max + 1) · n) time, which is roughly quadratic. O(1) space.

**C++**
```cpp
int daysRequired(vector<int>& weights, int cap) {
    int days = 1, load = 0;
    for (int w : weights) {
        if (load + w > cap) { days++; load = w; }   // ship sails, start a new day
        else load += w;
    }
    return days;
}
int shipWithinDaysBrute(vector<int>& weights, int days) {
    int mx = *max_element(weights.begin(), weights.end());
    int sum = accumulate(weights.begin(), weights.end(), 0);
    for (int cap = mx; cap <= sum; cap++)
        if (daysRequired(weights, cap) <= days) return cap;
    return sum;
}
```

**Java**
```java
class Solution {
    static int daysRequired(int[] weights, int cap) {
        int days = 1, load = 0;
        for (int w : weights) {
            if (load + w > cap) { days++; load = w; }   // ship sails, start a new day
            else load += w;
        }
        return days;
    }
    static int shipWithinDaysBrute(int[] weights, int days) {
        int mx = 0, sum = 0;
        for (int w : weights) { mx = Math.max(mx, w); sum += w; }
        for (int cap = mx; cap <= sum; cap++)
            if (daysRequired(weights, cap) <= days) return cap;
        return sum;
    }
}
```

#### Approach 2: Optimal — binary search on capacity
- `low = max`, `high = sum`.
- If `daysRequired(mid) <= days`, then `mid` is possible. Try smaller: `high = mid − 1`.
- Otherwise `low = mid + 1`.
- Return `low` (opposite polarity: it ends on the first possible capacity).

**Dry run** with the example (`low = 10`, `high = 55`):
- [10, 55]: mid 32, possible → high 31.
- [10, 31]: mid 20, possible → high 19.
- [10, 19]: mid 14, 6 days, not possible → low 15.
- [15, 19]: mid 17, possible → high 16.
- [15, 16]: mid 15, possible → high 14. Stop.

Answer: `low` = **15**.

**Complexity:** O(n · log(sum − max + 1)) time, O(1) space.

**C++**
```cpp
int daysNeeded(vector<int>& weights, int cap) {
    int days = 1, load = 0;
    for (int w : weights) {
        if (load + w > cap) { days++; load = w; }
        else load += w;
    }
    return days;
}
int shipWithinDays(vector<int>& weights, int days) {
    int low = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (daysNeeded(weights, mid) <= days) high = mid - 1;   // possible -> smaller ship
        else low = mid + 1;
    }
    return low;
}
```

**Java**
```java
class Solution {
    static int daysNeeded(int[] weights, int cap) {
        int days = 1, load = 0;
        for (int w : weights) {
            if (load + w > cap) { days++; load = w; }
            else load += w;
        }
        return days;
    }
    public int shipWithinDays(int[] weights, int days) {
        int low = 0, high = 0;
        for (int w : weights) { low = Math.max(low, w); high += w; }
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (daysNeeded(weights, mid) <= days) high = mid - 1;   // possible -> smaller ship
            else low = mid + 1;
        }
        return low;
    }
}
```

#### Edge Cases & Pitfalls
- **The low end must be `max(weights)`, not 1.** With a smaller capacity, the check function would put an oversized package alone on a day and wrongly report success.
- Packages must stay **in order**. You can't rearrange them to fill days better.
- If the sum of weights could exceed `int`, use 64-bit. Under LeetCode's limits (5·10⁴ packages × 500) an `int` is fine.

#### Key Takeaways
- The answer range is `[max, sum]`, and the check function greedily fills each day.
- The same structure is behind Book Allocation, Painter's Partition and Split Array Largest Sum (all later in this section): minimise the maximum load subject to a limit on the number of groups.

[↑ Contents](#contents) · [← Previous](#p121) · [Next →](#p123)

---

<a id="p123"></a>

### 19. Kth Missing Positive Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › On answers | Pro | No | [LeetCode](https://leetcode.com/problems/kth-missing-positive-number/) | [Watch](https://youtu.be/uZ0N_hZpyps) |

#### Problem Statement
Given a **strictly increasing** array of positive integers `arr` and an integer `k`, return the **k-th positive integer missing** from the array (LeetCode 1539).

```text
arr = [2, 3, 4, 7, 11], k = 5   ->  9     (missing: 1, 5, 6, 8, 9, 10, ...)
arr = [5, 7, 10, 12],   k = 4   ->  4     (1..4 all missing)
arr = [5, 7, 10, 12],   k = 6   ->  8     (missing: 1, 2, 3, 4, 6, 8, ...)
arr = [4, 7, 9],        k = 3   ->  3
```

#### Approach 1: Brute Force — push `k` past smaller elements
Walk through the array. Each element `<= k` takes one slot from the numbers 1, 2, …, so the k-th missing number moves one step right: `k++`. Stop at the first element `> k`, then return `k`.

For `[2, 3, 4, 7, 11]` with `k = 5`: 2 makes k = 6, 3 makes k = 7, 4 makes k = 8, 7 makes k = 9. Then 11 > 9, so stop. Answer: **9**.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int findKthPositiveBrute(vector<int>& arr, int k) {
    for (int x : arr) {
        if (x <= k) k++;       // x occupies a slot before the k-th missing number
        else break;
    }
    return k;
}
```

**Java**
```java
class Solution {
    static int findKthPositiveBrute(int[] arr, int k) {
        for (int x : arr) {
            if (x <= k) k++;       // x occupies a slot before the k-th missing number
            else break;
        }
        return k;
    }
}
```

#### Approach 2: Optimal — binary search on "missing count"
We need better than O(n) on a sorted array, which points to binary search. This isn't a plain search (the answer isn't in the array) and it isn't search on answers either. Instead, we find the **two neighbouring indices** that the answer lies between.

**Missing count at index `i`:** with nothing missing, `arr[i]` would equal `i + 1`. So the number of positives missing before `arr[i]` is **`missing(i) = arr[i] − (i + 1)`**. For `[2, 3, 4, 7, 11]` that gives `[1, 1, 1, 3, 6]`, which is non-decreasing, so we can binary search on it.
- If `missing(mid) < k`, the answer lies to the right: `low = mid + 1`.
- Otherwise: `high = mid − 1`.

At the end, by opposite polarity, `high` is the last index with `missing < k` and `low = high + 1`.

**Deriving the answer.** The answer is `arr[high] + more`, where `more = k − missing(high)`. So
`arr[high] + k − (arr[high] − high − 1) = high + 1 + k = low + k`.

Use the formula rather than `arr[high] + more`, because `high` can end at −1. With `[4, 7, 9]` and `k = 3`, the answer comes before the first element, and the formula gives `−1 + 1 + 3 = 3`. This is the reason behind the `return low + k` found in many solutions.

**Dry run** `[2, 3, 4, 7, 11]`, `k = 5`:
- [0, 4]: mid 2, missing 1 < 5 → low 3.
- [3, 4]: mid 3, missing 3 < 5 → low 4.
- [4, 4]: mid 4, missing 6 ≥ 5 → high 3. Stop.

Answer: `high + 1 + k` = 3 + 1 + 5 = **9**.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int findKthPositive(vector<int>& arr, int k) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int missing = arr[mid] - (mid + 1);
        if (missing < k) low = mid + 1;
        else high = mid - 1;
    }
    return high + 1 + k;          // == low + k
}
```

**Java**
```java
class Solution {
    public int findKthPositive(int[] arr, int k) {
        int low = 0, high = arr.length - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int missing = arr[mid] - (mid + 1);
            if (missing < k) low = mid + 1;
            else high = mid - 1;
        }
        return high + 1 + k;          // == low + k
    }
}
```

#### Edge Cases & Pitfalls
- The answer can come before `arr[0]` (`high = −1`) or after the last element (`high = n − 1`). The formula `high + 1 + k` covers both cases.
- Compare with `missing < k` (strict). Ties go left so that `high` stays strictly below `k`.

#### Key Takeaways
- `arr[i] − (i + 1)` is the number of missing positives before index `i`, and it's monotonic, so binary search applies.
- The final formula `low + k` comes from `arr[high] + (k − missing(high))`.

[↑ Contents](#contents) · [← Previous](#p122) · [Next →](#p124)

---

<a id="p124"></a>

### 20. Painter's Partition

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › On answers | Pro | No | [LeetCode](https://leetcode.com/problems/split-array-largest-sum/) | [Watch](https://youtu.be/thUd_WJn6wk) |

#### Problem Statement
A wall has `n` boards, and board `i` takes `boards[i]` units of time to paint. There are `k` painters. Each painter paints a **contiguous** group of boards, at least one board each, and all painters work **simultaneously**. Return the **minimum time** needed to paint all the boards. That time is the largest total any single painter gets, so we want the minimum possible maximum.

```text
boards = [10, 20, 30, 40], k = 2  ->  60
  [10] | [20, 30, 40]   -> max(10, 90)  = 90
  [10, 20] | [30, 40]   -> max(30, 70)  = 70
  [10, 20, 30] | [40]   -> max(60, 40)  = 60   <- minimum
```

#### Intuition — the same problem as Book Allocation
Compare this with Book Allocation:
- Each painter gets at least one board, just as each student gets at least one book.
- No board is split between two painters, just as no book is split.
- Each painter's boards are contiguous, just as each student's books are.
- The goal is to minimise the maximum load, which is the same goal as before.

So the solution is identical: **binary search the maximum time** over `[max(boards), sum(boards)]`. The check counts how many painters are needed when nobody may exceed `mid`. In the video, the Book Allocation code was pasted in unchanged and accepted. The same holds for Split Array Largest Sum.

#### Approach 1: Brute Force — try every time limit
Try each limit from `max` upward. The first one that needs `<= k` painters is the answer.

**Complexity:** O((sum − max + 1) · n) time.

**C++**
```cpp
int paintersNeeded(vector<int>& boards, long long limit) {
    int painters = 1;
    long long t = 0;
    for (int b : boards) {
        if (t + b <= limit) t += b;
        else { painters++; t = b; }
    }
    return painters;
}
long long minTimeBrute(vector<int>& boards, int k) {
    long long mx = *max_element(boards.begin(), boards.end());
    long long sum = accumulate(boards.begin(), boards.end(), 0LL);
    for (long long lim = mx; lim <= sum; lim++)
        if (paintersNeeded(boards, lim) <= k) return lim;
    return sum;
}
```

**Java**
```java
class Solution {
    static int paintersNeeded(int[] boards, long limit) {
        int painters = 1;
        long t = 0;
        for (int b : boards) {
            if (t + b <= limit) t += b;
            else { painters++; t = b; }
        }
        return painters;
    }
    static long minTimeBrute(int[] boards, int k) {
        long mx = 0, sum = 0;
        for (int b : boards) { mx = Math.max(mx, b); sum += b; }
        for (long lim = mx; lim <= sum; lim++)
            if (paintersNeeded(boards, lim) <= k) return lim;
        return sum;
    }
}
```

#### Approach 2: Optimal — binary search on the time limit
Binary search the limit over `[max, sum]`. If the painters needed at `mid` are `<= k`, set `high = mid − 1`; otherwise set `low = mid + 1`. Return `low`.

**Complexity:** O(n · log(sum − max + 1)) time, O(1) space.

**C++**
```cpp
int countPainters(vector<int>& boards, long long limit) {
    int painters = 1;
    long long t = 0;
    for (int b : boards) {
        if (t + b <= limit) t += b;
        else { painters++; t = b; }
    }
    return painters;
}
long long findLargestMinDistance(vector<int>& boards, int k) {
    long long low = *max_element(boards.begin(), boards.end());
    long long high = accumulate(boards.begin(), boards.end(), 0LL);
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (countPainters(boards, mid) <= k) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}
```

**Java**
```java
class Solution {
    static int countPainters(int[] boards, long limit) {
        int painters = 1;
        long t = 0;
        for (int b : boards) {
            if (t + b <= limit) t += b;
            else { painters++; t = b; }
        }
        return painters;
    }
    public static long findLargestMinDistance(int[] boards, int k) {
        long low = 0, high = 0;
        for (int b : boards) { low = Math.max(low, b); high += b; }
        while (low <= high) {
            long mid = low + (high - low) / 2;
            if (countPainters(boards, mid) <= k) high = mid - 1;
            else low = mid + 1;
        }
        return low;
    }
}
```

#### Edge Cases & Pitfalls
- `k >= n`: every painter can take one board, so the answer is `max(boards)`. The search finds this automatically, because `low` starts at `max`.
- **Interview advice from the video:** don't reuse a function named `findPages`. Write the logic inside the function the problem asks for.

#### Key Takeaways
- Painter's Partition, Book Allocation and Split Array Largest Sum share one solution: **minimise the maximum contiguous-part sum with k parts**.
- In an interview, the key skill is recognising the pattern behind the story.

[↑ Contents](#contents) · [← Previous](#p123) · [Next →](#p125)

---

## FAQs

<a id="p125"></a>

### 21. Aggressive Cows

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › FAQs | Pro | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/aggressive-cows) | [Watch](https://youtu.be/R_Mfw4ew-Vo) |

#### Problem Statement
You are given `n` stall positions, `stalls[i]` (unsorted), and `k` cows with `k >= 2`. Place all `k` cows in distinct stalls so that the **minimum distance between any two cows is as large as possible**. Return that largest possible minimum distance.

```text
stalls = [0, 3, 4, 7, 10, 9], k = 4  ->  3
  sorted: 0 3 4 7 9 10
  e.g. cows at 0, 3, 7, 10 -> gaps 3, 4, 3 -> min = 3 (no placement does better)
```

This opens the **"max of min / min of max"** family of binary search on answers.

#### Intuition
- For a given placement, the minimum distance always occurs between **consecutive** cows. So sort the stalls and look only at neighbouring gaps.
- **Check `canPlace(dist)`:** can all `k` cows be placed with every gap `>= dist`? Use a greedy approach. Put the first cow in the first stall, which leaves the most room for the rest. Then put each next cow in the first stall that is at least `dist` from the last cow. Return true once `k` cows are placed.
- **Monotonic:** if `dist` is achievable, so is every smaller distance. If it isn't, nothing larger is either. For the example, distances 1, 2, 3 are possible and 4, 5, … are not. We want the **last possible** value.
- **Range:** from 1 up to `max − min`. That upper bound is the k = 2 case, with cows at both ends.

#### Approach 1: Brute Force — try every distance from 1 upward
Return the last `d` for which `canPlace(d)` is true. In other words, stop at the first failure and return `d − 1`.

**Complexity:** O(n log n) to sort, plus O((max − min) · n) for the checks. O(1) extra space.

**C++**
```cpp
bool canPlace(vector<int>& stalls, int dist, int cows) {
    int cnt = 1, last = stalls[0];            // first cow at the first stall
    for (int i = 1; i < (int)stalls.size(); i++) {
        if (stalls[i] - last >= dist) {
            cnt++; last = stalls[i];
            if (cnt >= cows) return true;
        }
    }
    return cnt >= cows;
}
int aggressiveCowsBrute(vector<int> stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int limit = stalls.back() - stalls[0];
    for (int d = 1; d <= limit; d++)
        if (!canPlace(stalls, d, k)) return d - 1;
    return limit;
}
```

**Java**
```java
class Solution {
    static boolean canPlace(int[] stalls, int dist, int cows) {
        int cnt = 1, last = stalls[0];            // first cow at the first stall
        for (int i = 1; i < stalls.length; i++) {
            if (stalls[i] - last >= dist) {
                cnt++; last = stalls[i];
                if (cnt >= cows) return true;
            }
        }
        return cnt >= cows;
    }
    static int aggressiveCowsBrute(int[] arr, int k) {
        int[] stalls = arr.clone();
        Arrays.sort(stalls);
        int limit = stalls[stalls.length - 1] - stalls[0];
        for (int d = 1; d <= limit; d++)
            if (!canPlace(stalls, d, k)) return d - 1;
        return limit;
    }
}
```

#### Approach 2: Optimal — binary search on the distance
- Sort the stalls. Set `low = 1` and `high = max − min`.
- If `canPlace(mid)`, then `mid` is possible. Try **larger**: `low = mid + 1`.
- Otherwise `high = mid − 1`.
- Return **`high`**. By opposite polarity, `high` started in the impossible zone and ends on the last possible distance.

**Dry run** on the sorted example `[0, 3, 4, 7, 9, 10]`, k = 4, range [1, 10]:
- mid 5 → not possible, so high = 4.
- mid 2 → possible, so low = 3.
- mid 3 → possible, so low = 4.
- mid 4 → not possible, so high = 3. Stop.

Answer: **3**.

**Complexity:** O(n log n) + O(n · log(max − min)). O(1) extra space.

**C++**
```cpp
bool canWePlace(vector<int>& stalls, int dist, int cows) {
    int cnt = 1, last = stalls[0];
    for (int i = 1; i < (int)stalls.size(); i++) {
        if (stalls[i] - last >= dist) {
            cnt++; last = stalls[i];
            if (cnt >= cows) return true;
        }
    }
    return cnt >= cows;
}
int aggressiveCows(vector<int> stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int low = 1, high = stalls.back() - stalls[0];
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canWePlace(stalls, mid, k)) low = mid + 1;   // possible -> try larger
        else high = mid - 1;
    }
    return high;                                        // last possible distance
}
```

**Java**
```java
class Solution {
    static boolean canWePlace(int[] stalls, int dist, int cows) {
        int cnt = 1, last = stalls[0];
        for (int i = 1; i < stalls.length; i++) {
            if (stalls[i] - last >= dist) {
                cnt++; last = stalls[i];
                if (cnt >= cows) return true;
            }
        }
        return cnt >= cows;
    }
    public static int aggressiveCows(int[] arr, int k) {
        int[] stalls = arr.clone();
        Arrays.sort(stalls);
        int low = 1, high = stalls[stalls.length - 1] - stalls[0];
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canWePlace(stalls, mid, k)) low = mid + 1;   // possible -> try larger
            else high = mid - 1;
        }
        return high;                                        // last possible distance
    }
}
```

#### Edge Cases & Pitfalls
- **Sort first.** The input isn't sorted, and both the greedy check and the range depend on sorted order.
- You must place **exactly `k`** cows. Putting 2 cows at the two ends isn't valid when `k = 4`.
- `low` could start at the minimum consecutive gap. That shrinks the range slightly but doesn't change the complexity, so the video keeps 1.

#### Key Takeaways
- For "maximise the minimum" problems: binary search the answer, check feasibility greedily, and return `high`, the last feasible value.
- The greedy "place as early as possible" is optimal for a fixed minimum gap.

[↑ Contents](#contents) · [← Previous](#p124) · [Next →](#p126)

---

<a id="p126"></a>

### 22. Book Allocation Problem

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/split-array-largest-sum/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/book-allocation-problem) | [Watch](https://youtu.be/gYmWHvRHu-s) |

#### Problem Statement
`arr[i]` is the number of pages in book `i`, and there are `m` students. Allocate **all** the books so that:
1. each book goes to exactly one student (a book can't be split);
2. every student gets **at least one** book;
3. each student gets a **contiguous** block of books.

Among all valid allocations, **minimise the maximum** number of pages any one student gets, and return that value. If `m > n`, return −1.

```text
arr = [12, 34, 67, 90], m = 2  ->  113
  [12] | [34, 67, 90]   -> max(12, 191)  = 191
  [12, 34] | [67, 90]   -> max(46, 157)  = 157
  [12, 34, 67] | [90]   -> max(113, 90)  = 113   <- minimum of the maxima
```

#### Approach 1: Recursion / DP — try every partition (not recommended)
You could try every cut position recursively. That's exponential, and memoization brings it to about O(n²·m). The video advises skipping this in an interview and going straight to binary search, since this route uses up the time you'd need to optimise.

#### Approach 2: Brute Force — try every "barrier" *(not in this video; linear version of the check)*
Given a barrier `maxPages`, a greedy check counts how many students are needed: give books to the current student until the next book would exceed the barrier, then start a new student. The smallest barrier that needs `<= m` students is the answer. Try barriers from `max(arr)` up to `sum(arr)`.

**Complexity:** O((sum − max + 1) · n) time.

**C++**
```cpp
int studentsNeeded(vector<int>& arr, int barrier) {
    int students = 1;
    long long pages = 0;
    for (int p : arr) {
        if (pages + p <= barrier) pages += p;
        else { students++; pages = p; }
    }
    return students;
}
int findPagesBrute(vector<int>& arr, int m) {
    if (m > (int)arr.size()) return -1;
    int mx = *max_element(arr.begin(), arr.end());
    int sum = accumulate(arr.begin(), arr.end(), 0);
    for (int b = mx; b <= sum; b++)
        if (studentsNeeded(arr, b) <= m) return b;
    return -1;
}
```

**Java**
```java
class Solution {
    static int studentsNeeded(int[] arr, int barrier) {
        int students = 1;
        long pages = 0;
        for (int p : arr) {
            if (pages + p <= barrier) pages += p;
            else { students++; pages = p; }
        }
        return students;
    }
    static int findPagesBrute(int[] arr, int m) {
        if (m > arr.length) return -1;
        int mx = 0, sum = 0;
        for (int p : arr) { mx = Math.max(mx, p); sum += p; }
        for (int b = mx; b <= sum; b++)
            if (studentsNeeded(arr, b) <= m) return b;
        return -1;
    }
}
```

#### Approach 3: Optimal — binary search on the barrier (max pages per student)
- **Search space:** the answer lies between a lower bound and `sum(arr)`. With one student, they get everything.
  - The video uses `min(arr)` as the lower bound. That's always safe because `isPossible` returns false when a single book exceeds the barrier.
  - The tighter bound is **`max(arr)`**, since some student has to hold the largest book. *(The newer playlist uses `max`.)*
- **`isPossible(barrier)`:**
  - If any book has more pages than the barrier, return false.
  - Otherwise allocate greedily, opening a new student whenever adding the next book would cross the barrier.
  - Return `students <= m`.
- **Monotonic:** if barrier `b` works, every larger barrier works. If it doesn't, every smaller one fails.
- If possible: record it and try smaller, `high = mid − 1`. Otherwise `low = mid + 1`. The answer is `low` (or the recorded `res`).

**Dry run** `[12, 34, 67, 90]`, `m = 2`, search `[12, 203]`:

| low–high | mid | allocation | students | verdict |
|---|---|---|---|---|
| 12–203 | 107 | [12,34] [67] [90] | 3 | ✗ → low 108 |
| 108–203 | 155 | [12,34,67] [90] | 2 | ✓ res 155 → high 154 |
| 108–154 | 131 | [12,34,67] [90] | 2 | ✓ res 131 → high 130 |
| 108–130 | 119 | [12,34,67] [90] | 2 | ✓ res 119 → high 118 |
| 108–118 | 113 | [12,34,67] [90] | 2 | ✓ res 113 → high 112 |
| 108–112 | 110 | [12,34] [67] [90] | 3 | ✗ → low 111 |
| 111–112 | 111 | 3 students | | ✗ → low 112 |
| 112–112 | 112 | 3 students | | ✗ → low 113 |

The loop stops with `low = 113`, which is the answer.

**Complexity:** O(n · log(sum − max + 1)) time, O(1) space.

**C++**
```cpp
bool isPossible(vector<int>& arr, int m, int barrier) {
    int students = 1;
    long long pages = 0;
    for (int p : arr) {
        if (p > barrier) return false;               // a single book exceeds the barrier
        if (pages + p > barrier) { students++; pages = p; }
        else pages += p;
    }
    return students <= m;
}
int findPages(vector<int>& arr, int m) {
    if (m > (int)arr.size()) return -1;              // each student needs >= 1 book
    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isPossible(arr, m, mid)) high = mid - 1; // feasible -> try a smaller maximum
        else low = mid + 1;
    }
    return low;
}
```

**Java**
```java
class Solution {
    static boolean isPossible(int[] arr, int m, int barrier) {
        int students = 1;
        long pages = 0;
        for (int p : arr) {
            if (p > barrier) return false;               // a single book exceeds the barrier
            if (pages + p > barrier) { students++; pages = p; }
            else pages += p;
        }
        return students <= m;
    }
    public static int findPages(int[] arr, int m) {
        if (m > arr.length) return -1;                   // each student needs >= 1 book
        int low = 0, high = 0;
        for (int p : arr) { low = Math.max(low, p); high += p; }
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (isPossible(arr, m, mid)) high = mid - 1; // feasible -> try a smaller maximum
            else low = mid + 1;
        }
        return low;
    }
}
```

#### Edge Cases & Pitfalls
- **`m > n`:** some student would get no book, so return −1. *(not in video)*
- Why is "≤ m students" enough when every student must get a book? *(not in video)* If an allocation with barrier `b` uses fewer than `m` students and `m <= n`, you can split off single books to new students without raising anyone's total. So feasibility with ≤ m implies feasibility with exactly m.
- If the page sum can exceed `int`, use 64-bit types.

#### Key Takeaways
- To minimise the maximum under contiguous partitioning: binary search on the maximum load, check greedily, and return the first feasible value.
- Painter's Partition and Split Array Largest Sum are the same problem with different stories.

[↑ Contents](#contents) · [← Previous](#p125) · [Next →](#p127)

---

<a id="p127"></a>

### 23. Find peak element

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/find-peak-element/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-a-peak-element-in-an-array) | [Watch](https://youtu.be/cXxmbemS6XM) |

#### Problem Statement
A **peak** is an element **strictly greater** than both of its neighbours. Imagine `−∞` beyond both ends of the array, so `arr[−1] = arr[n] = −∞`. Adjacent elements are never equal. Return the index of **any** peak, in O(log n) (LeetCode 162).

```text
[1, 2, 3, 4, 5, 6, 7, 8, 5, 1]  ->  7      (value 8)
[1, 2, 1, 3, 5, 6, 4]           ->  1 or 5 (values 2 or 6; any peak is fine)
[1, 2, 3, 4, 5]                 ->  4      (last element: 5 > 4 and > -inf)
[5, 4, 3, 2, 1]                 ->  0
```

#### Approach 1: Brute Force — check every index
`arr[i]` is a peak if (`i == 0` or `arr[i−1] < arr[i]`) and (`i == n−1` or `arr[i] > arr[i+1]`).

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int findPeakLinear(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        bool left = (i == 0) || arr[i - 1] < arr[i];
        bool right = (i == n - 1) || arr[i] > arr[i + 1];
        if (left && right) return i;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int findPeakLinear(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            boolean left = (i == 0) || arr[i - 1] < arr[i];
            boolean right = (i == n - 1) || arr[i] > arr[i + 1];
            if (left && right) return i;
        }
        return -1;
    }
}
```

#### Approach 2: Optimal — binary search on the slope
**Why binary search?** We need better than O(n), we're *searching* for something, and the array has a "sorted tendency": it goes up, then down, possibly several times.

**Single peak first.** Picture the array as a mountain: an increasing slope, the peak, then a decreasing slope. At any `mid` there are three cases:
- `arr[mid−1] < arr[mid] > arr[mid+1]` means `mid` **is** the peak.
- `arr[mid−1] < arr[mid]` means we're on the **increasing** slope, so the peak is to the right: `low = mid + 1`.
- Otherwise we're on the **decreasing** slope, so the peak is to the left: `high = mid − 1`.

**Avoiding the edge checks.** Comparing with `mid−1` and `mid+1` would read out of bounds at the two ends. So handle the ends up front:
- If `n == 1`, return 0.
- If `arr[0] > arr[1]`, return 0.
- If `arr[n−1] > arr[n−2]`, return n−1.

Then binary search only `[1, n−2]`.

**Multiple peaks.** The same rules still work. On an increasing slope you may discard a left half that contains peaks, but the right side is guaranteed to contain one too, because the slope must eventually come down to `−∞`. The mirror argument covers the decreasing slope. Keep shrinking and you end up inside a region with a single peak.

**The one extra case is a valley** (`arr[mid−1] > arr[mid] < arr[mid+1]`). It isn't on either slope. Both sides contain a peak, so you can go either way. Writing the last branch as a plain `else` (go left) covers this case. Otherwise a valley can lead to an infinite loop.

**Dry run** `[1, 2, 3, 4, 5, 6, 7, 8, 5, 1]` (search space [1, 8]):
- mid 4 holds 5. 4 < 5 < 6, so we're on the increasing slope: `low = 5`.
- mid 6 holds 7, also increasing: `low = 7`.
- mid 7 holds 8, and 7 < 8 > 5, so it's the **peak**. Return 7.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int findPeakElement(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return 0;
    if (arr[0] > arr[1]) return 0;
    if (arr[n - 1] > arr[n - 2]) return n - 1;
    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) return mid;   // peak
        if (arr[mid] > arr[mid - 1]) low = mid + 1;   // increasing slope -> peak on the right
        else high = mid - 1;                          // decreasing slope or valley -> go left
    }
    return -1;                                        // never reached
}
```

**Java**
```java
class Solution {
    public int findPeakElement(int[] arr) {
        int n = arr.length;
        if (n == 1) return 0;
        if (arr[0] > arr[1]) return 0;
        if (arr[n - 1] > arr[n - 2]) return n - 1;
        int low = 1, high = n - 2;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) return mid;   // peak
            if (arr[mid] > arr[mid - 1]) low = mid + 1;   // increasing slope -> peak on the right
            else high = mid - 1;                          // decreasing slope or valley -> go left
        }
        return -1;                                        // never reached
    }
}
```

#### Edge Cases & Pitfalls
- **Valleys:** if you write `else if (arr[mid] > arr[mid+1]) high = mid − 1` with no final `else`, a valley matches neither branch, and the loop never progresses.
- The final `return −1` is only there so the code compiles. A peak always exists because of the `−∞` boundaries.
- If you'd rather search `[0, n−1]`, you need explicit bounds checks for `mid − 1` and `mid + 1`. Trimming the range avoids them.

#### Key Takeaways
- Binary search doesn't need full sortedness, only a rule that guarantees the answer is in the half you keep. Here the rule is "climb uphill".
- Visualising the array as up and down slopes makes the elimination argument clear.

[↑ Contents](#contents) · [← Previous](#p126) · [Next →](#p128)

---

<a id="p128"></a>

### 24. Median of 2 sorted arrays

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/median-of-two-sorted-arrays/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/median-of-2-sorted-arrays) | [Watch](https://youtu.be/NTop3VTjmxk) |

#### Problem Statement
Given two **sorted** arrays `a` (size n1) and `b` (size n2), return the **median** of the combined sorted array. If the combined length is even, the median is the average of the two middle elements. LeetCode 4 requires O(log(min(n1, n2))).

```text
a = [1, 3, 4, 7, 10, 12], b = [2, 3, 6, 15]  ->  5.0   (merged 1 2 3 3 4 | 6 7 10 12 15 -> (4+6)/2)
a = [1, 3],              b = [4, 5, 6]       ->  4.0   (merged 1 3 4 5 6 -> middle 4)
a = [7, 12, 14, 15],     b = [1, 2, 3, 4, 9, 11] -> 8.0
```

#### Approach 1: Brute Force — merge, then take the middle
Merge the two arrays with the two-pointer merge step from merge sort. The median is the middle element (odd length) or the average of the two middle elements (even length).

**Complexity:** O(n1 + n2) time, O(n1 + n2) space.

**C++**
```cpp
double medianBrute(vector<int>& a, vector<int>& b) {
    vector<int> m;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) m.push_back(a[i] <= b[j] ? a[i++] : b[j++]);
    while (i < (int)a.size()) m.push_back(a[i++]);
    while (j < (int)b.size()) m.push_back(b[j++]);
    int n = m.size();
    if (n % 2 == 1) return m[n / 2];
    return (m[n / 2 - 1] + (double)m[n / 2]) / 2.0;
}
```

**Java**
```java
class Solution {
    static double medianBrute(int[] a, int[] b) {
        int[] m = new int[a.length + b.length];
        int i = 0, j = 0, k = 0;
        while (i < a.length && j < b.length) m[k++] = a[i] <= b[j] ? a[i++] : b[j++];
        while (i < a.length) m[k++] = a[i++];
        while (j < b.length) m[k++] = b[j++];
        int n = m.length;
        if (n % 2 == 1) return m[n / 2];
        return (m[n / 2 - 1] + (double) m[n / 2]) / 2.0;
    }
}
```

#### Approach 2: Better — merge "virtually" with a counter
We only need the elements at positions `n/2 − 1` and `n/2`. Run the same merge without storing anything: keep a counter of how many elements have been taken, and record the two elements whose positions are `n/2 − 1` and `n/2`.

**Complexity:** O(n1 + n2) time, **O(1)** space.

**C++**
```cpp
double medianBetter(vector<int>& a, vector<int>& b) {
    int n1 = a.size(), n2 = b.size(), n = n1 + n2;
    int idx2 = n / 2, idx1 = idx2 - 1, cnt = 0;
    int el1 = -1, el2 = -1, i = 0, j = 0;
    auto take = [&](int v) {
        if (cnt == idx1) el1 = v;
        if (cnt == idx2) el2 = v;
        cnt++;
    };
    while (i < n1 && j < n2) take(a[i] <= b[j] ? a[i++] : b[j++]);
    while (i < n1) take(a[i++]);
    while (j < n2) take(b[j++]);
    if (n % 2 == 1) return el2;
    return (el1 + (double)el2) / 2.0;
}
```

**Java**
```java
class Solution {
    static double medianBetter(int[] a, int[] b) {
        int n1 = a.length, n2 = b.length, n = n1 + n2;
        int idx2 = n / 2, idx1 = idx2 - 1, cnt = 0;
        int el1 = -1, el2 = -1, i = 0, j = 0;
        while (i < n1 || j < n2) {
            int v;
            if (j >= n2 || (i < n1 && a[i] <= b[j])) v = a[i++];
            else v = b[j++];
            if (cnt == idx1) el1 = v;
            if (cnt == idx2) el2 = v;
            cnt++;
        }
        if (n % 2 == 1) return el2;
        return (el1 + (double) el2) / 2.0;
    }
}
```

#### Approach 3: Optimal — binary search on the partition
**Idea.** In the merged array, the median splits the elements into a **left half** of `(n1 + n2 + 1) / 2` elements and a right half holding the rest. This formula works for both even and odd totals. The left half is made of some prefix of `a` (`cut1` elements) plus some prefix of `b` (`cut2 = leftSize − cut1` elements). So we only need to choose `cut1`.

**Validity.** Define:
- `l1 = a[cut1 − 1]`, the last element taken from `a`;
- `r1 = a[cut1]`, the first element of `a` left over;
- `l2`, `r2`, the same pair for `b`.

Within each array, order is already guaranteed. So the partition is correct exactly when the **cross conditions** hold: `l1 <= r2` and `l2 <= r1`.
- If `l1 > r2`, we took too many from `a`. Move the cut left: `high = cut1 − 1`.
- Otherwise (`l2 > r1`), we took too few from `a`. Move it right: `low = cut1 + 1`.
- If a side is empty, use `−∞` for a missing `l` and `+∞` for a missing `r`.

**Median from a valid partition:**
- odd total: `max(l1, l2)`;
- even total: `(max(l1, l2) + min(r1, r2)) / 2`.

**Binary search on the smaller array**, with `cut1 ∈ [0, n1]`. This makes the cost `log(min(n1, n2))` and keeps `cut2` within the bounds of `b`.

**Dry run** `a = [7, 12, 14, 15]` (smaller), `b = [1, 2, 3, 4, 9, 11]`, left size 5:
- low 0, high 4: cut1 = 2, cut2 = 3. l1 = 12, r1 = 14, l2 = 3, r2 = 4. `12 > 4`, so move left: high = 1.
- low 0, high 1: cut1 = 0, cut2 = 5. l1 = −∞, r1 = 7, l2 = 9, r2 = 11. `9 > 7`, so move right: low = 1.
- low 1, high 1: cut1 = 1, cut2 = 4. l1 = 7, r1 = 12, l2 = 4, r2 = 9. Both `7 ≤ 9` and `4 ≤ 12` hold, so the partition is valid. The total is even, so the median is `(max(7, 4) + min(12, 9)) / 2 = (7 + 9) / 2` = **8**.

**Complexity:** O(log(min(n1, n2))) time, O(1) space.

**C++**
```cpp
double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
    int n1 = a.size(), n2 = b.size();
    if (n1 > n2) return findMedianSortedArrays(b, a);     // binary search on the smaller array
    int n = n1 + n2, leftSize = (n + 1) / 2;
    int low = 0, high = n1;
    while (low <= high) {
        int cut1 = low + (high - low) / 2;
        int cut2 = leftSize - cut1;
        int l1 = cut1 > 0 ? a[cut1 - 1] : INT_MIN;
        int l2 = cut2 > 0 ? b[cut2 - 1] : INT_MIN;
        int r1 = cut1 < n1 ? a[cut1] : INT_MAX;
        int r2 = cut2 < n2 ? b[cut2] : INT_MAX;
        if (l1 <= r2 && l2 <= r1) {                        // valid partition
            if (n % 2 == 1) return max(l1, l2);
            return ((double)max(l1, l2) + min(r1, r2)) / 2.0;
        }
        if (l1 > r2) high = cut1 - 1;                      // took too many from a
        else low = cut1 + 1;                               // took too few from a
    }
    return 0.0;                                            // unreachable for sorted input
}
```

**Java**
```java
class Solution {
    public double findMedianSortedArrays(int[] a, int[] b) {
        int n1 = a.length, n2 = b.length;
        if (n1 > n2) return findMedianSortedArrays(b, a);     // binary search on the smaller array
        int n = n1 + n2, leftSize = (n + 1) / 2;
        int low = 0, high = n1;
        while (low <= high) {
            int cut1 = low + (high - low) / 2;
            int cut2 = leftSize - cut1;
            int l1 = cut1 > 0 ? a[cut1 - 1] : Integer.MIN_VALUE;
            int l2 = cut2 > 0 ? b[cut2 - 1] : Integer.MIN_VALUE;
            int r1 = cut1 < n1 ? a[cut1] : Integer.MAX_VALUE;
            int r2 = cut2 < n2 ? b[cut2] : Integer.MAX_VALUE;
            if (l1 <= r2 && l2 <= r1) {                        // valid partition
                if (n % 2 == 1) return Math.max(l1, l2);
                return ((double) Math.max(l1, l2) + Math.min(r1, r2)) / 2.0;
            }
            if (l1 > r2) high = cut1 - 1;                      // took too many from a
            else low = cut1 + 1;                               // took too few from a
        }
        return 0.0;                                            // unreachable for sorted input
    }
}
```

#### Edge Cases & Pitfalls
- **Empty sides:** `cut = 0` gives `l = −∞`, and `cut = size` gives `r = +∞`. This is the edge case people most often miss.
- **Search the smaller array**, otherwise `cut2` can go negative or past the end of `b`.
- Average as a `double`: `(max + min) / 2.0`. Integer addition can overflow, so cast before adding.
- One array may be empty. The recursion swap makes `a` the empty one, so `cut1 = 0` always.

#### Key Takeaways
- The median is a partition problem: choose how many elements come from `a`, and the rest of the left half comes from `b`.
- A partition is valid when `l1 ≤ r2` and `l2 ≤ r1`, and the direction of the violation tells you which way to move.
- The same partition idea solves "K-th element of two sorted arrays", the next problem.

[↑ Contents](#contents) · [← Previous](#p127) · [Next →](#p129)

---

<a id="p129"></a>

### 25. Kth element of 2 sorted arrays

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › FAQs | Pro | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/kth-element-of-two-sorted-arrays) | [Watch](https://youtu.be/nv7F4PiLUzo) |

#### Problem Statement
Given two sorted arrays `a` (size n) and `b` (size m) and an integer `k` (1-indexed, `1 ≤ k ≤ n + m`), return the **k-th smallest element** of their merged sorted order.

```text
a = [1, 3, 4, 7, 10, 12], b = [2, 3, 6, 15],      k = 5  ->  4    (1 2 3 3 [4] 6 7 ...)
a = [7, 12, 14, 15],      b = [1, 2, 3, 4, 9, 11], k = 5  ->  7
```

The video targets **O(log min(n, m))** time and O(1) space, which is better than the commonly cited O(log n + log m) divide-and-conquer approach.

#### Approach 1: Brute Force — merge with a counter
Run the merge step with two pointers. Take the smaller head each time and increment a counter. When the counter reaches `k`, the element just taken is the answer. No extra array is needed.

**Complexity:** O(k) time, O(1) space.

**C++**
```cpp
int kthElementBrute(vector<int>& a, vector<int>& b, int k) {
    int i = 0, j = 0, cnt = 0, n = a.size(), m = b.size();
    while (i < n || j < m) {
        int v;
        if (j >= m || (i < n && a[i] <= b[j])) v = a[i++];
        else v = b[j++];
        if (++cnt == k) return v;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int kthElementBrute(int[] a, int[] b, int k) {
        int i = 0, j = 0, cnt = 0, n = a.length, m = b.length;
        while (i < n || j < m) {
            int v;
            if (j >= m || (i < n && a[i] <= b[j])) v = a[i++];
            else v = b[j++];
            if (++cnt == k) return v;
        }
        return -1;
    }
}
```

#### Approach 2: Optimal — binary search on the partition
This is the median idea with a left half of size **`k`** instead of `(n + m + 1) / 2`.
- Take `cut1` elements from `a` and `cut2 = k − cut1` from `b`.
- Define the boundary values:
  - `l1 = a[cut1 − 1]`, `r1 = a[cut1]`;
  - `l2 = b[cut2 − 1]`, `r2 = b[cut2]`;
  - a missing `l` is `−∞` and a missing `r` is `+∞`.
- The partition is **valid** when `l1 ≤ r2` and `l2 ≤ r1`. Then the answer is the largest element of the left half, **`max(l1, l2)`**.
- If `l1 > r2`, take fewer from `a`: `high = cut1 − 1`. Otherwise take more: `low = cut1 + 1`.

**Bounds on `cut1` (the edge cases highlighted in the video):**
- `high = min(k, n)`: you can't take more than `k` elements, or more than `a` has.
- `low = max(0, k − m)`: if `k > m`, then `b` alone can't fill the left half, so at least `k − m` elements must come from `a`.

Always binary search on the **smaller** array; swap the arguments if needed.

**Dry run** `a = [7, 12, 14, 15]`, `b = [1, 2, 3, 4, 9, 11]`, `k = 5`. The bounds are `low = 0`, `high = 4`.
- cut1 = 2, cut2 = 3: l1 = 12, l2 = 3, r1 = 14, r2 = 4. Since 12 > 4, set high = 1.
- cut1 = 0, cut2 = 5: l1 = −∞, l2 = 9, r1 = 7, r2 = 11. Since 9 > 7, set low = 1.
- cut1 = 1, cut2 = 4: l1 = 7, l2 = 4, r1 = 12, r2 = 9. Both 7 ≤ 9 and 4 ≤ 12 hold, so the partition is valid. Answer: max(7, 4) = **7**.

**Complexity:** O(log min(n, m)) time, O(1) space.

**C++**
```cpp
int kthElement(vector<int>& a, vector<int>& b, int k) {
    int n = a.size(), m = b.size();
    if (n > m) return kthElement(b, a, k);           // binary search on the smaller array
    int low = max(0, k - m), high = min(k, n);
    while (low <= high) {
        int cut1 = (low + high) >> 1;
        int cut2 = k - cut1;
        int l1 = cut1 == 0 ? INT_MIN : a[cut1 - 1];
        int l2 = cut2 == 0 ? INT_MIN : b[cut2 - 1];
        int r1 = cut1 == n ? INT_MAX : a[cut1];
        int r2 = cut2 == m ? INT_MAX : b[cut2];
        if (l1 <= r2 && l2 <= r1) return max(l1, l2);
        if (l1 > r2) high = cut1 - 1;
        else low = cut1 + 1;
    }
    return -1;                                       // unreachable for valid input
}
```

**Java**
```java
class Solution {
    public static int kthElement(int[] a, int[] b, int k) {
        int n = a.length, m = b.length;
        if (n > m) return kthElement(b, a, k);           // binary search on the smaller array
        int low = Math.max(0, k - m), high = Math.min(k, n);
        while (low <= high) {
            int cut1 = (low + high) >> 1;
            int cut2 = k - cut1;
            int l1 = cut1 == 0 ? Integer.MIN_VALUE : a[cut1 - 1];
            int l2 = cut2 == 0 ? Integer.MIN_VALUE : b[cut2 - 1];
            int r1 = cut1 == n ? Integer.MAX_VALUE : a[cut1];
            int r2 = cut2 == m ? Integer.MAX_VALUE : b[cut2];
            if (l1 <= r2 && l2 <= r1) return Math.max(l1, l2);
            if (l1 > r2) high = cut1 - 1;
            else low = cut1 + 1;
        }
        return -1;                                       // unreachable for valid input
    }
}
```

#### Edge Cases & Pitfalls
- **Bounds:** `low = max(0, k − m)` and `high = min(k, n)`. Without them, `cut2` can go negative or past the end of `b`.
- Use `INT_MIN` for an empty left side and `INT_MAX` for an empty right side.
- `>> 1` is simply division by 2 (the video uses it as a micro-optimisation).

#### Key Takeaways
- The k-th element is the median partition with the left half fixed at `k` elements. The answer is `max(l1, l2)`.
- Clamp the partition range to what's feasible before searching.

[↑ Contents](#contents) · [← Previous](#p128) · [Next →](#p130)

---

<a id="p130"></a>

### 26. Minimize Max Distance to Gas Station

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › FAQs | Pro | Yes | [LeetCode](https://leetcode.com/problems/minimize-max-distance-to-gas-station/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/minimize-maximum-distance-between-gas-stations) | [Watch](https://youtu.be/kMSBvlZ-_HA) |

#### Problem Statement
`arr` holds the **sorted** positions of `n` gas stations. Add **`k` new stations**, at any real positions (fractional coordinates are allowed), so that the **maximum distance between adjacent stations is as small as possible**. Return that minimised maximum distance as a double. Answers within `10⁻⁶` of the true value are accepted.

```text
arr = [1, 2, 3, 4, 5], k = 4      ->  0.5    (place at 1.5, 2.5, 3.5, 4.5)
arr = [1, 13, 17, 23], k = 5      ->  3.0    (3 stations in [1,13] -> gaps of 3; 1 in [13,17] -> 2; 1 in [17,23] -> 3)
```

**About "within 10⁻⁶":** the judge compares your output with its reference answer only up to about 6 decimal places. Computing more precision than that just wastes time and risks TLE.

#### Intuition
- New stations **outside** `[arr[0], arr[n−1]]` never help. They don't shorten any existing gap. So every new station goes inside one of the `n − 1` existing gaps.
- If gap `i` has length `d` and receives `c` new stations spread **evenly**, it splits into `c + 1` equal sections of length `d / (c + 1)`.
- So the problem reduces to: **how many new stations does each gap receive?** That allocation decides the answer.

#### Approach 1: Brute Force — greedy, one station at a time (linear scan for the max)
Keep `howMany[i]`, the number of stations placed in gap `i`. Repeat `k` times: find the gap whose current section length `(arr[i+1] − arr[i]) / (howMany[i] + 1)` is largest, and add one station to it. At the end, the answer is the largest section length.

For `[1, 13, 17, 23]` with `k = 5`, the sections evolve as follows:
- Start: 12 | 4 | 6.
- Station 1 goes into gap 0: 6,6 | 4 | 6.
- Station 2 goes into gap 2: 6,6 | 4 | 3,3.
- Station 3 goes into gap 0, re-spaced evenly: 4,4,4 | 4 | 3,3.
- Station 4 goes into gap 1: 4,4,4 | 2,2 | 3,3.
- Station 5 goes into gap 0: 3,3,3,3 | 2,2 | 3,3.

The maximum is **3**.

**Complexity:** O(k · n) time, which gets TLE on large inputs. O(n) space.

**C++**
```cpp
long double minimiseMaxDistanceBrute(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> howMany(n - 1, 0);
    for (int gs = 1; gs <= k; gs++) {
        long double maxSection = -1; int maxInd = -1;
        for (int i = 0; i < n - 1; i++) {
            long double diff = arr[i + 1] - arr[i];
            long double sectionLength = diff / (long double)(howMany[i] + 1);
            if (sectionLength > maxSection) { maxSection = sectionLength; maxInd = i; }
        }
        howMany[maxInd]++;
    }
    long double maxAns = -1;
    for (int i = 0; i < n - 1; i++) {
        long double diff = arr[i + 1] - arr[i];
        maxAns = max(maxAns, diff / (long double)(howMany[i] + 1));
    }
    return maxAns;
}
```

**Java**
```java
class Solution {
    static double minimiseMaxDistanceBrute(int[] arr, int k) {
        int n = arr.length;
        int[] howMany = new int[n - 1];
        for (int gs = 1; gs <= k; gs++) {
            double maxSection = -1; int maxInd = -1;
            for (int i = 0; i < n - 1; i++) {
                double diff = arr[i + 1] - arr[i];
                double sectionLength = diff / (double) (howMany[i] + 1);
                if (sectionLength > maxSection) { maxSection = sectionLength; maxInd = i; }
            }
            howMany[maxInd]++;
        }
        double maxAns = -1;
        for (int i = 0; i < n - 1; i++) {
            double diff = arr[i + 1] - arr[i];
            maxAns = Math.max(maxAns, diff / (double) (howMany[i] + 1));
        }
        return maxAns;
    }
}
```

#### Approach 2: Better — same greedy with a max-heap (priority queue)
The O(n) "find the maximum section" step is the bottleneck. A **max-heap** of `(sectionLength, gapIndex)` returns it in O(log n):
1. Push `(arr[i+1] − arr[i], i)` for every gap.
2. Repeat `k` times: pop the top `(len, i)`, increment `howMany[i]`, and push `((arr[i+1] − arr[i]) / (howMany[i] + 1), i)`.
3. The heap's top length is the answer.

**Complexity:** O(n log n + k log n) time, O(n) space (the heap and `howMany`).

**C++**
```cpp
long double minimiseMaxDistanceHeap(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> howMany(n - 1, 0);
    priority_queue<pair<long double, int>> pq;             // (section length, gap index)
    for (int i = 0; i < n - 1; i++) pq.push({(long double)(arr[i + 1] - arr[i]), i});
    for (int gs = 1; gs <= k; gs++) {
        auto tp = pq.top(); pq.pop();
        int secInd = tp.second;
        howMany[secInd]++;
        long double inidiff = arr[secInd + 1] - arr[secInd];
        long double newSecLen = inidiff / (long double)(howMany[secInd] + 1);
        pq.push({newSecLen, secInd});
    }
    return pq.top().first;
}
```

**Java**
```java
class Solution {
    static double minimiseMaxDistanceHeap(int[] arr, int k) {
        int n = arr.length;
        int[] howMany = new int[n - 1];
        PriorityQueue<double[]> pq = new PriorityQueue<>((x, y) -> Double.compare(y[0], x[0]));  // max-heap
        for (int i = 0; i < n - 1; i++) pq.add(new double[]{arr[i + 1] - arr[i], i});
        for (int gs = 1; gs <= k; gs++) {
            double[] tp = pq.poll();
            int secInd = (int) tp[1];
            howMany[secInd]++;
            double inidiff = arr[secInd + 1] - arr[secInd];
            pq.add(new double[]{inidiff / (howMany[secInd] + 1), secInd});
        }
        return pq.peek()[0];
    }
}
```

#### Approach 3: Optimal — binary search on the (real-valued) answer
We're asked to **minimise a maximum**, so binary search on the answer `dist`. The check is: **how many new stations are needed so that no section exceeds `dist`?** For a gap of length `d`, you need `⌊d / dist⌋` stations. When `d / dist` is an **exact integer**, you need one fewer, because `d / dist` equal sections need only `d / dist − 1` stations between them. For example, gap 1 with dist 0.5 needs 1 station, not 2.
- If `needed > k`, `dist` is too small, so `low = mid`.
- Otherwise `dist` is achievable, so `high = mid`, and look for something smaller.

**Range:** the answer lies in `[0, max gap]`. It's 0 when all stations coincide, and never more than the current largest gap.

**Binary search on doubles** changes the template:
- The loop condition is `while (high − low > 1e−6)`, not `low <= high`.
- Use `low = mid` / `high = mid`, not `mid ± 1`, which would skip over real values.
- Return `high`, the last feasible value. The "opposite polarity" rule doesn't apply here, because there's no ±1 step.

**Complexity:** O(n · log(maxGap / 10⁻⁶)) for the search, plus O(n) to find `maxGap`. O(1) space.

**C++**
```cpp
int stationsNeeded(long double dist, vector<int>& arr) {
    int cnt = 0;
    for (int i = 1; i < (int)arr.size(); i++) {
        long double gap = arr[i] - arr[i - 1];
        if (gap == 0) continue;                            // duplicate positions need nothing
        int inBetween = (int)(gap / dist);
        if (gap == dist * inBetween) inBetween--;          // exact division: one fewer needed
        cnt += inBetween;
    }
    return cnt;
}
long double minimiseMaxDistance(vector<int>& arr, int k) {
    long double low = 0, high = 0;
    for (int i = 0; i + 1 < (int)arr.size(); i++)
        high = max(high, (long double)(arr[i + 1] - arr[i]));
    long double diff = 1e-6;
    while (high - low > diff) {
        long double mid = (low + high) / 2.0;
        if (stationsNeeded(mid, arr) > k) low = mid;   // too many stations -> distance too small
        else high = mid;                               // feasible -> try smaller
    }
    return high;
}
```

**Java**
```java
class Solution {
    static int stationsNeeded(double dist, int[] arr) {
        int cnt = 0;
        for (int i = 1; i < arr.length; i++) {
            double gap = arr[i] - arr[i - 1];
            if (gap == 0) continue;                            // duplicate positions need nothing
            int inBetween = (int) (gap / dist);
            if (gap == dist * inBetween) inBetween--;          // exact division: one fewer needed
            cnt += inBetween;
        }
        return cnt;
    }
    public static double minimiseMaxDistance(int[] arr, int k) {
        double low = 0, high = 0;
        for (int i = 0; i + 1 < arr.length; i++)
            high = Math.max(high, arr[i + 1] - arr[i]);
        double diff = 1e-6;
        while (high - low > diff) {
            double mid = (low + high) / 2.0;
            if (stationsNeeded(mid, arr) > k) low = mid;   // too many stations -> distance too small
            else high = mid;                               // feasible -> try smaller
        }
        return high;
    }
}
```

#### Edge Cases & Pitfalls
- **Type casting:** divide in `long double` / `double`. An integer division like `diff / (howMany + 1)` silently truncates.
- **The exact-division case** in `stationsNeeded`. Without the `−1`, you over-count by one.
- **Duplicate positions** (a gap of 0) would make the exact-division rule subtract 1 from 0. Skip zero gaps. *(not in video; usually positions are strictly increasing)*
- The binary search never calls `stationsNeeded` with `mid = 0`, because `mid > low >= 0` and the loop stops while `high − low > 1e−6`.
- The video ranks this among the hardest binary-search interview questions. Interviewers rarely ask it, but the doubles pattern is worth knowing.

#### Key Takeaways
- Greedy: always split the currently largest section. A heap brings each step from O(n) to O(log n).
- Binary search on a real-valued answer: `while (high − low > ε)`, set `low = mid` / `high = mid`, and return `high`.

[↑ Contents](#contents) · [← Previous](#p129) · [Next →](#p131)

---

<a id="p131"></a>

### 27. Split array - largest sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › FAQs | Pro | No | [LeetCode](https://leetcode.com/problems/split-array-largest-sum/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/split-array-largest-sum) | [Watch](https://youtu.be/thUd_WJn6wk) |

#### Problem Statement
Split `nums` into **`k` non-empty contiguous subarrays** so that the **largest subarray sum is as small as possible**. Return that minimised largest sum (LeetCode 410).

```text
nums = [10, 20, 30, 40], k = 2  ->  60     ([10, 20, 30] | [40])
nums = [7, 2, 5, 10, 8],  k = 2  ->  18     ([7, 2, 5] | [10, 8])
```

#### Intuition
This is the "min of max" pattern again, identical to Book Allocation and Painter's Partition. Each subarray corresponds to a student or painter, and each subarray's sum to their load. Binary search the maximum allowed subarray sum over `[max(nums), sum(nums)]`. Greedily count how many subarrays are needed. If that's `<= k`, the value is feasible. The video solves it by pasting in the Book Allocation code.

#### Approach 1: Brute Force — try every limit
**Complexity:** O((sum − max + 1) · n) time.

**C++**
```cpp
int partsNeeded(vector<int>& nums, long long limit) {
    int parts = 1;
    long long s = 0;
    for (int x : nums) {
        if (s + x <= limit) s += x;
        else { parts++; s = x; }
    }
    return parts;
}
int splitArrayBrute(vector<int>& nums, int k) {
    long long mx = *max_element(nums.begin(), nums.end());
    long long sum = accumulate(nums.begin(), nums.end(), 0LL);
    for (long long lim = mx; lim <= sum; lim++)
        if (partsNeeded(nums, lim) <= k) return (int)lim;
    return (int)sum;
}
```

**Java**
```java
class Solution {
    static int partsNeeded(int[] nums, long limit) {
        int parts = 1;
        long s = 0;
        for (int x : nums) {
            if (s + x <= limit) s += x;
            else { parts++; s = x; }
        }
        return parts;
    }
    static int splitArrayBrute(int[] nums, int k) {
        long mx = 0, sum = 0;
        for (int x : nums) { mx = Math.max(mx, x); sum += x; }
        for (long lim = mx; lim <= sum; lim++)
            if (partsNeeded(nums, lim) <= k) return (int) lim;
        return (int) sum;
    }
}
```

#### Approach 2: Optimal — binary search on the largest sum
**Complexity:** O(n · log(sum − max + 1)) time, O(1) space.

**C++**
```cpp
int countParts(vector<int>& nums, long long limit) {
    int parts = 1;
    long long s = 0;
    for (int x : nums) {
        if (s + x <= limit) s += x;
        else { parts++; s = x; }
    }
    return parts;
}
int splitArray(vector<int>& nums, int k) {
    long long low = *max_element(nums.begin(), nums.end());
    long long high = accumulate(nums.begin(), nums.end(), 0LL);
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (countParts(nums, mid) <= k) high = mid - 1;   // feasible -> try smaller
        else low = mid + 1;
    }
    return (int)low;
}
```

**Java**
```java
class Solution {
    static int countParts(int[] nums, long limit) {
        int parts = 1;
        long s = 0;
        for (int x : nums) {
            if (s + x <= limit) s += x;
            else { parts++; s = x; }
        }
        return parts;
    }
    public int splitArray(int[] nums, int k) {
        long low = 0, high = 0;
        for (int x : nums) { low = Math.max(low, x); high += x; }
        while (low <= high) {
            long mid = low + (high - low) / 2;
            if (countParts(nums, mid) <= k) high = mid - 1;   // feasible -> try smaller
            else low = mid + 1;
        }
        return (int) low;
    }
}
```

#### Key Takeaways
- Checking `<= k` parts is enough: a split into fewer parts can always be divided further without raising the maximum, as long as `k <= n`.
- After this problem the playlist moves on to binary search on doubles (Minimise Max Distance to Gas Station).

[↑ Contents](#contents) · [← Previous](#p130) · [Next →](#p132)

---

## 2D Arrays

<a id="p132"></a>

### 28. Find row with maximum 1's

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › 2D Arrays | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-the-row-with-maximum-1s-in-a-sorted-binary-matrix) | [Watch](https://youtu.be/SCz-1TtYxDI) |

#### Problem Statement
An `n × m` binary matrix has **every row sorted**: all of a row's 0s come before its 1s. Return the index of the **row with the most 1s**. If several rows tie, return the smallest index. If no row contains a 1, return −1.

```text
mat = [[0,0,1,1,1],
       [0,0,0,0,0],
       [0,1,1,1,1],
       [0,0,0,0,0],
       [0,1,1,1,1]]   ->  2     (rows 2 and 4 both have four 1s; the smaller index wins)
```

#### Approach 1: Brute Force — count every row
Sum each row, since the sum of a binary row is its number of 1s. Update the answer only when the count is **strictly greater** than the best so far, so ties keep the smaller index.

**Complexity:** O(n · m) time, O(1) space.

**C++**
```cpp
int rowWithMax1sBrute(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size(), maxCnt = 0, index = -1;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++) cnt += mat[i][j];
        if (cnt > maxCnt) { maxCnt = cnt; index = i; }
    }
    return index;
}
```

**Java**
```java
class Solution {
    static int rowWithMax1sBrute(int[][] mat) {
        int n = mat.length, m = mat[0].length, maxCnt = 0, index = -1;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) cnt += mat[i][j];
            if (cnt > maxCnt) { maxCnt = cnt; index = i; }
        }
        return index;
    }
}
```

#### Approach 2: Optimal (per video) — lower bound of 1 in each row
You still have to visit every row. What can be sped up is counting within a row. A sorted row is a sorted 1-D array, so its count of 1s is **`m − lowerBound(row, 1)`**, the length minus the index of the first 1. `upperBound(row, 0)` or "first occurrence of 1" give the same index.

Start with `maxCnt = 0`, so a matrix with no 1s returns −1. That was the test case that failed in the video until this was fixed.

**Complexity:** O(n · log m) time, O(1) space.

**C++**
```cpp
int lowerBound(vector<int>& arr, int m, int x) {
    int low = 0, high = m - 1, ans = m;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= x) { ans = mid; high = mid - 1; }
        else low = mid + 1;
    }
    return ans;
}
int rowWithMax1s(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size(), maxCnt = 0, index = -1;
    for (int i = 0; i < n; i++) {
        int cnt = m - lowerBound(mat[i], m, 1);
        if (cnt > maxCnt) { maxCnt = cnt; index = i; }
    }
    return index;
}
```

**Java**
```java
class Solution {
    static int lowerBound(int[] arr, int m, int x) {
        int low = 0, high = m - 1, ans = m;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= x) { ans = mid; high = mid - 1; }
            else low = mid + 1;
        }
        return ans;
    }
    static int rowWithMax1s(int[][] mat) {
        int n = mat.length, m = mat[0].length, maxCnt = 0, index = -1;
        for (int i = 0; i < n; i++) {
            int cnt = m - lowerBound(mat[i], m, 1);
            if (cnt > maxCnt) { maxCnt = cnt; index = i; }
        }
        return index;
    }
}
```

#### Approach 3: Staircase walk, O(n + m) *(not in video)*
Start at the top-right cell, with column `j = m − 1`.
- While `mat[i][j] == 1`, move **left**. Each step left means this row has more 1s than any earlier row, so record row `i`.
- When you hit a 0, move **down** to the next row.

Column `j` never moves right, so the walk takes at most `n + m` steps. A tie never moves `j`, so the earlier row is kept.

**C++**
```cpp
int rowWithMax1sStair(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size(), j = m - 1, index = -1;
    for (int i = 0; i < n; i++)
        while (j >= 0 && mat[i][j] == 1) { j--; index = i; }
    return index;
}
```

**Java**
```java
class Solution {
    static int rowWithMax1sStair(int[][] mat) {
        int n = mat.length, m = mat[0].length, j = m - 1, index = -1;
        for (int i = 0; i < n; i++)
            while (j >= 0 && mat[i][j] == 1) { j--; index = i; }
        return index;
    }
}
```

#### Edge Cases & Pitfalls
- **No 1s anywhere:** return −1, so initialise `maxCnt = 0`, not −1.
- **Ties:** use `>`, not `>=`, so the smallest row index wins.

#### Key Takeaways
- In matrix problems, you usually can't avoid visiting every row. Binary search speeds up the work done *inside* each sorted row.
- In a sorted binary row, the count of 1s is `m − (index of the first 1)`.

[↑ Contents](#contents) · [← Previous](#p131) · [Next →](#p133)

---

<a id="p133"></a>

### 29. Search in a 2D Matrix

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › 2D Arrays | Core | No | [LeetCode](https://leetcode.com/problems/search-a-2d-matrix/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/search-in-sorted-2d-matrix) | [Watch](https://youtu.be/ZYpYur0znng) |

#### Problem Statement
Given an `n × m` matrix where every row is sorted **and** the first integer of each row is greater than the last integer of the previous row, decide whether `target` is present (LeetCode 74).

```text
mat = [[ 1,  3,  5,  7],
       [10, 11, 16, 20],
       [23, 30, 34, 50]]
target = 30 -> true  (at row 2, col 1)
target = 13 -> false
```

> **Ask the interviewer first:** does each row's first element exceed the previous row's last element (this problem), or is the matrix only sorted by row and by column (the next problem, Search in 2D Matrix II)?

#### Approach 1: Brute Force — scan every cell
**Complexity:** O(n · m) time, O(1) space.

**C++**
```cpp
bool searchMatrixBrute(vector<vector<int>>& mat, int target) {
    for (auto& row : mat)
        for (int x : row)
            if (x == target) return true;
    return false;
}
```

**Java**
```java
class Solution {
    static boolean searchMatrixBrute(int[][] mat, int target) {
        for (int[] row : mat)
            for (int x : row)
                if (x == target) return true;
        return false;
    }
}
```

#### Approach 2: Better — binary search in each row
Each row is sorted, so run a binary search on every row. *(An extra improvement, not in the video: only the one row with `row[0] <= target <= row[m−1]` can contain the target, so you could search just that row.)*

**Complexity:** O(n · log m) time, O(1) space.

**C++**
```cpp
bool binarySearchRow(vector<int>& row, int target) {
    int low = 0, high = (int)row.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (row[mid] == target) return true;
        if (row[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}
bool searchMatrixBetter(vector<vector<int>>& mat, int target) {
    for (auto& row : mat)
        if (binarySearchRow(row, target)) return true;
    return false;
}
```

**Java**
```java
class Solution {
    static boolean binarySearchRow(int[] row, int target) {
        int low = 0, high = row.length - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (row[mid] == target) return true;
            if (row[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return false;
    }
    static boolean searchMatrixBetter(int[][] mat, int target) {
        for (int[] row : mat)
            if (binarySearchRow(row, target)) return true;
        return false;
    }
}
```

#### Approach 3: Optimal — treat the matrix as one sorted array (imaginary indices)
Because each row continues where the previous one ended, reading the matrix row by row gives **one sorted array of `n·m` elements**. We don't build that array. We binary search over the *imaginary* index range `[0, n·m − 1]` and convert each index back to a cell:

`row = idx / m`, `col = idx % m` (divide by the number of **columns**).

**Dry run** `target = 30`, with n = 3 and m = 4, so the range is [0, 11]:
- mid 5 → (1, 1) = 11 < 30 → low 6.
- mid 8 → (2, 0) = 23 < 30 → low 9.
- mid 10 → (2, 2) = 34 > 30 → high 9.
- mid 9 → (2, 1) = 30 → **found**.

**Complexity:** O(log(n · m)) time, O(1) space.

**C++**
```cpp
bool searchMatrix(vector<vector<int>>& mat, int target) {
    if (mat.empty() || mat[0].empty()) return false;
    int n = mat.size(), m = mat[0].size();
    int low = 0, high = n * m - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = mid / m, col = mid % m;          // imaginary index -> cell
        if (mat[row][col] == target) return true;
        if (mat[row][col] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}
```

**Java**
```java
class Solution {
    public boolean searchMatrix(int[][] mat, int target) {
        if (mat.length == 0 || mat[0].length == 0) return false;
        int n = mat.length, m = mat[0].length;
        int low = 0, high = n * m - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int row = mid / m, col = mid % m;          // imaginary index -> cell
            if (mat[row][col] == target) return true;
            if (mat[row][col] < target) low = mid + 1;
            else high = mid - 1;
        }
        return false;
    }
}
```

#### Edge Cases & Pitfalls
- Convert with `/ m` and `% m`, where `m` is the number of **columns**, not `n`.
- If `n · m` could overflow `int`, use `long long` / `long` for the index range.
- The staircase search from the top-right corner (next problem) also works here, in O(n + m), but it's slower than O(log(n·m)).

#### Key Takeaways
- A row-major sorted matrix is a 1-D sorted array in disguise. Binary search its flattened indices, mapping `idx → (idx / m, idx % m)`.

[↑ Contents](#contents) · [← Previous](#p132) · [Next →](#p134)

---

<a id="p134"></a>

### 30. Search in 2D matrix - II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › 2D Arrays | Core | No | [LeetCode](https://leetcode.com/problems/search-a-2d-matrix-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/search-in-a-row-and-column-wise-sorted-matrix) | [Watch](https://youtu.be/9ZbB397jU4k) |

#### Problem Statement
In an `n × m` matrix, every **row is sorted left to right** and every **column is sorted top to bottom**. The matrix as a whole is not row-major sorted: a row can start with a smaller value than the previous row ends with. Find `target` and return its position, or `(−1, −1)`. LeetCode 240 asks only for true/false.

```text
mat = [[ 1,  4,  7, 11, 15],
       [ 2,  5,  8, 12, 19],
       [ 3,  6,  9, 16, 22],
       [10, 13, 14, 17, 24],
       [18, 21, 23, 26, 30]]
target = 14 -> (3, 2)        target = 20 -> (-1, -1)
```

#### Approach 1: Brute Force — check every cell
**Complexity:** O(n · m) time, O(1) space.

**C++**
```cpp
pair<int, int> searchMatrixIIBrute(vector<vector<int>>& mat, int target) {
    for (int i = 0; i < (int)mat.size(); i++)
        for (int j = 0; j < (int)mat[i].size(); j++)
            if (mat[i][j] == target) return {i, j};
    return {-1, -1};
}
```

**Java**
```java
class Solution {
    static int[] searchMatrixIIBrute(int[][] mat, int target) {
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[i].length; j++)
                if (mat[i][j] == target) return new int[]{i, j};
        return new int[]{-1, -1};
    }
}
```

#### Approach 2: Better — binary search in every row
Treat each row as a sorted 1-D array and binary search it for the target.

**Complexity:** O(n · log m) time, O(1) space.

**C++**
```cpp
int bsRow(vector<int>& row, int target) {
    int low = 0, high = (int)row.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (row[mid] == target) return mid;
        if (row[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
pair<int, int> searchMatrixIIBetter(vector<vector<int>>& mat, int target) {
    for (int i = 0; i < (int)mat.size(); i++) {
        int j = bsRow(mat[i], target);
        if (j != -1) return {i, j};
    }
    return {-1, -1};
}
```

**Java**
```java
class Solution {
    static int bsRow(int[] row, int target) {
        int low = 0, high = row.length - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (row[mid] == target) return mid;
            if (row[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }
    static int[] searchMatrixIIBetter(int[][] mat, int target) {
        for (int i = 0; i < mat.length; i++) {
            int j = bsRow(mat[i], target);
            if (j != -1) return new int[]{i, j};
        }
        return new int[]{-1, -1};
    }
}
```

#### Approach 3: Optimal — staircase elimination from the top-right corner
**Where to start.**
- At the **top-left** corner, values increase both rightward and downward, so a comparison tells you nothing.
- At the **bottom-right** corner, both directions decrease, which has the same problem.
- At the **top-right** corner, moving left decreases and moving down increases. Reading along that row and column gives one sorted sequence, so each comparison eliminates something.

From `(row = 0, col = m − 1)`:
- If `mat[row][col] == target`, it's found.
- If `mat[row][col] < target`, everything to its left in this row is smaller still, so **discard the row**: `row++`.
- If `mat[row][col] > target`, everything below it in this column is larger still, so **discard the column**: `col−−`.

**Dry run** `target = 14`:
- (0,4) = 15 > 14 → col 3.
- (0,3) = 11 < 14 → row 1.
- (1,3) = 12 < 14 → row 2.
- (2,3) = 16 > 14 → col 2.
- (2,2) = 9 < 14 → row 3.
- (3,2) = 14 → found at **(3, 2)**.

Starting from the **bottom-left** corner works too, by symmetry: go up if the value is bigger, right if it is smaller.

**Complexity:** each step removes a whole row or a whole column, so there are at most `n + m` steps. **O(n + m)** time, O(1) space. This is still a binary-search idea (eliminate part of the search space at each step), just not the textbook halving.

**C++**
```cpp
pair<int, int> searchMatrixII(vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    int row = 0, col = m - 1;
    while (row < n && col >= 0) {
        if (mat[row][col] == target) return {row, col};
        if (mat[row][col] < target) row++;   // this row's remaining cells are all smaller
        else col--;                          // this column's remaining cells are all larger
    }
    return {-1, -1};
}
```

**Java**
```java
class Solution {
    public static int[] searchMatrixII(int[][] mat, int target) {
        int n = mat.length, m = mat[0].length;
        int row = 0, col = m - 1;
        while (row < n && col >= 0) {
            if (mat[row][col] == target) return new int[]{row, col};
            if (mat[row][col] < target) row++;   // this row's remaining cells are all smaller
            else col--;                          // this column's remaining cells are all larger
        }
        return new int[]{-1, -1};
    }
}
```

#### Edge Cases & Pitfalls
- The loop bounds are `row < n` and `col >= 0`. Leaving the matrix means the target is absent.
- Flattening the matrix (the previous problem's trick) does **not** work here, because the matrix isn't row-major sorted.

#### Key Takeaways
- Start from a corner where one direction increases and the other decreases, then eliminate a row or a column per comparison.
- Binary-search thinking means eliminating search space, even when there's no `mid`.

[↑ Contents](#contents) · [← Previous](#p133) · [Next →](#p135)

---

<a id="p135"></a>

### 31. Find Peak Element - II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › 2D Arrays | Core | No | [LeetCode](https://leetcode.com/problems/find-a-peak-element-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-peak-element-2d-matrix) | [Watch](https://youtu.be/nGGp5XBzC4g) |

#### Problem Statement
In an `n × m` matrix, no two adjacent cells hold equal values. A **peak** is a cell strictly greater than its top, bottom, left and right neighbours, where anything outside the matrix counts as −1. Return the `[row, col]` of **any** peak in better than O(n·m) (LeetCode 1901).

```text
mat = [[10, 20, 15],
       [21, 30, 14],
       [ 7, 16, 32]]   ->  [1, 1] (30) or [2, 2] (32)
mat = [[1, 4],
       [3, 2]]         ->  [0, 1] (4) or [1, 0] (3)
```

#### Approach 1: Brute Force — check every cell, or return the global maximum
- Checking all 4 neighbours of every cell costs O(4·n·m) in the worst case.
- The video's simplification: the **global maximum** is always a peak, so one O(n·m) scan for the maximum is enough. This costs O(n·m) even in the best case, but the worst case improves.

**Complexity:** O(n · m) time, O(1) space.

**C++**
```cpp
vector<int> findPeakGridBrute(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size(), r = 0, c = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] > mat[r][c]) { r = i; c = j; }
    return {r, c};                         // the global maximum is always a peak
}
```

**Java**
```java
class Solution {
    static int[] findPeakGridBrute(int[][] mat) {
        int n = mat.length, m = mat[0].length, r = 0, c = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (mat[i][j] > mat[r][c]) { r = i; c = j; }
        return new int[]{r, c};                // the global maximum is always a peak
    }
}
```

#### Approach 2: Optimal — binary search on columns, take the maximum of the mid column
This extends Peak Element I. Binary search over the **columns** `[0, m − 1]`. For column `mid`:
1. Find the row `r` holding that column's **maximum**. That value already beats its top and bottom neighbours, so the problem reduces to the 1-D case: compare it only with its left and right neighbours.
2. Let `left = mat[r][mid−1]` (or −1 off the edge) and `right = mat[r][mid+1]` (or −1).
   - If `mat[r][mid] > left` and `mat[r][mid] > right`, it's a **peak**. Return `[r, mid]`.
   - If `mat[r][mid] < left`, the slope rises to the left, so a peak exists there: `high = mid − 1`.
   - Otherwise the slope rises to the right: `low = mid + 1`.

**Why discarding is safe.** Suppose `left > mat[r][mid]`. Then `left` is larger than **every** element of column `mid`, because `mat[r][mid]` is that column's maximum. Climbing from `left` toward ever-larger values can never cross back into column `mid`, so the left half must contain a peak.

**Dry run** on the 3×3 example. The search is over columns, with low 0 and high 2:
- mid = 1: column 1 is [20, 30, 16], so its maximum is 30 at row 1.
  - Its left neighbour is 21 and its right neighbour is 14. 30 beats both, so **[1, 1]** is a peak.

**Complexity:** O(n · log m) time, O(1) space. If `n > m`, you can binary search over rows instead to get O(m · log n). *(not in video)*

**C++**
```cpp
int maxRowInColumn(vector<vector<int>>& mat, int col) {
    int idx = 0;
    for (int i = 1; i < (int)mat.size(); i++)
        if (mat[i][col] > mat[idx][col]) idx = i;
    return idx;
}
vector<int> findPeakGrid(vector<vector<int>>& mat) {
    int m = mat[0].size(), low = 0, high = m - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int r = maxRowInColumn(mat, mid);
        int left = mid - 1 >= 0 ? mat[r][mid - 1] : -1;
        int right = mid + 1 < m ? mat[r][mid + 1] : -1;
        if (mat[r][mid] > left && mat[r][mid] > right) return {r, mid};
        if (mat[r][mid] < left) high = mid - 1;     // rises to the left
        else low = mid + 1;                         // rises to the right
    }
    return {-1, -1};                                // never reached
}
```

**Java**
```java
class Solution {
    static int maxRowInColumn(int[][] mat, int col) {
        int idx = 0;
        for (int i = 1; i < mat.length; i++)
            if (mat[i][col] > mat[idx][col]) idx = i;
        return idx;
    }
    public int[] findPeakGrid(int[][] mat) {
        int m = mat[0].length, low = 0, high = m - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int r = maxRowInColumn(mat, mid);
            int left = mid - 1 >= 0 ? mat[r][mid - 1] : -1;
            int right = mid + 1 < m ? mat[r][mid + 1] : -1;
            if (mat[r][mid] > left && mat[r][mid] > right) return new int[]{r, mid};
            if (mat[r][mid] < left) high = mid - 1;     // rises to the left
            else low = mid + 1;                         // rises to the right
        }
        return new int[]{-1, -1};                       // never reached
    }
}
```

#### Edge Cases & Pitfalls
- Off-matrix neighbours count as −1. That's safe because all values are ≥ 1.
- You must take the column **maximum**. A random element of the column might still lose to its top or bottom neighbour.
- The final `return {−1, −1}` is just a placeholder so the code compiles. A peak always exists.

#### Key Takeaways
- Taking the maximum of a column turns the 2-D problem into the 1-D peak problem.
- Binary search over one dimension and scan the other: O(n log m).

[↑ Contents](#contents) · [← Previous](#p134) · [Next →](#p136)

---

<a id="p136"></a>

### 32. Matrix Median

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Binary Search › 2D Arrays | Pro | Yes | [LeetCode](https://leetcode.com/problems/median-of-a-row-wise-sorted-matrix/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/median-of-a-row-wise-sorted-matrix) | [Watch](https://youtu.be/Q9wXgdxJq48) |

#### Problem Statement
Given an `n × m` matrix whose **rows are each sorted**, with `n · m` **odd**, return the **median** of all its elements, meaning the middle value in sorted order.

```text
mat = [[1, 5, 7,  9, 11],
       [2, 3, 4,  5, 10],
       [9, 10, 12, 14, 16]]
sorted: 1 2 3 4 5 5 7 [9] 9 10 10 11 12 14 16   ->  9   (7 elements on each side)
```

#### Approach 1: Brute Force — flatten, sort, take the middle
Copy every element into a list, sort it, and return `list[(n·m) / 2]`.

**Complexity:** O(n·m + n·m·log(n·m)) time, O(n·m) space.

**C++**
```cpp
int medianBrute(vector<vector<int>>& mat) {
    vector<int> all;
    for (auto& row : mat) for (int x : row) all.push_back(x);
    sort(all.begin(), all.end());
    return all[all.size() / 2];
}
```

**Java**
```java
class Solution {
    static int medianBrute(int[][] mat) {
        int n = mat.length, m = mat[0].length, k = 0;
        int[] all = new int[n * m];
        for (int[] row : mat) for (int x : row) all[k++] = x;
        Arrays.sort(all);
        return all[all.length / 2];
    }
}
```

Dropping only the `log` factor wouldn't be a meaningful improvement. To really beat O(n·m), we must avoid looking at every element. The input is sorted and we're searching for a value, which points to binary search.

#### Approach 2: Optimal — binary search on the value, count with upper bound
**Key observation.**
- Let `req = (n·m) / 2`, which is 7 in the example. The median has `req` elements before it in sorted order.
- Let `count(x)` be the number of elements `<= x`. Duplicates of the median complicate things, but this rule always holds: **the median is the smallest `x` with `count(x) > req`**.
- For every value below the median, `count(x) <= req`.

**Search space:** the answer lies in `[min, max]`.
- The minimum is the smallest element of column 0.
- The maximum is the largest element of column `m−1`.

So binary search on values:
- If `count(mid) <= req`, the median is larger: `low = mid + 1`.
- Otherwise: `high = mid − 1`.

When the loop ends, `low` is the answer, by opposite polarity.

**The "black box" `count(x)`:** each row is sorted, so `upperBound(row, x)` (the index of the first element `> x`) equals the number of elements `<= x` in that row. Add this up over all rows. That costs O(n log m) instead of O(n·m).

**Dry run** with `req = 7` and the range [1, 16]:
- mid 8: count is 3 + 4 + 0 = 7 ≤ 7 → low 9.
- mid 12: count is 13 > 7 → high 11.
- mid 10: count is 11 > 7 → high 9.
- mid 9: count is 9 > 7 → high 8. Stop: `low = 9`, which is the median.

**Complexity:** O(log(max − min) · n · log m). Values go up to 10⁹, so that's about 30 · n · log m. O(1) space.

**C++**
```cpp
int upperBound(vector<int>& arr, int x) {
    int low = 0, high = (int)arr.size() - 1, ans = arr.size();
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] > x) { ans = mid; high = mid - 1; }
        else low = mid + 1;
    }
    return ans;
}
int countSmallEqual(vector<vector<int>>& mat, int x) {
    int cnt = 0;
    for (auto& row : mat) cnt += upperBound(row, x);     // elements <= x in this row
    return cnt;
}
int median(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    int low = INT_MAX, high = INT_MIN;
    for (int i = 0; i < n; i++) {
        low = min(low, mat[i][0]);
        high = max(high, mat[i][m - 1]);
    }
    int req = (n * m) / 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (countSmallEqual(mat, mid) <= req) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}
```

**Java**
```java
class Solution {
    static int upperBound(int[] arr, int x) {
        int low = 0, high = arr.length - 1, ans = arr.length;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] > x) { ans = mid; high = mid - 1; }
            else low = mid + 1;
        }
        return ans;
    }
    static int countSmallEqual(int[][] mat, int x) {
        int cnt = 0;
        for (int[] row : mat) cnt += upperBound(row, x);     // elements <= x in this row
        return cnt;
    }
    static int median(int[][] mat) {
        int n = mat.length, m = mat[0].length;
        int low = Integer.MAX_VALUE, high = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            low = Math.min(low, mat[i][0]);
            high = Math.max(high, mat[i][m - 1]);
        }
        int req = (n * m) / 2;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (countSmallEqual(mat, mid) <= req) low = mid + 1;
            else high = mid - 1;
        }
        return low;
    }
}
```

#### Edge Cases & Pitfalls
- The condition is `count(mid) <= req`, so ties go **right**. This is what makes `low` land on the first value whose count is greater than `req`, even with duplicates of the median.
- `low` always ends on an actual matrix element. The smallest `x` with `count(x) > req` must itself be present in the matrix, otherwise `count(x − 1)` would be the same.
- `n · m` is odd by the constraints. For even sizes, the median would need the two middle values.

#### Key Takeaways
- Binary search on the **answer value** with a monotone count function `count(x)`. The median is the first `x` with `count(x) > (n·m)/2`.
- Upper bound counts the elements `<= x` in a sorted row in O(log m). Reuse it rather than rewriting it.

[↑ Contents](#contents) · [← Previous](#p135)

---
