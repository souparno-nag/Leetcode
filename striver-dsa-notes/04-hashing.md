# Hashing — Striver's A2Z DSA Sheet Notes

Section 4 of 20 · 5 problems · 5 with video, 0 without · [All sections](00-index.md)

[← Arrays](03-arrays.md) | [Binary Search →](05-binary-search.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**FAQs**

1. [Longest Consecutive Sequence in an Array](#p100) — Core
2. [Longest subarray with sum K](#p101) — Core
3. [Largest Subarray with Sum 0](#p102) — Core · *video not transcribed*
4. [Count subarrays with given sum](#p103) — Core
5. [Count subarrays with given xor K](#p104) — Pro

---

## FAQs

<a id="p100"></a>

### 1. Longest Consecutive Sequence in an Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Hashing › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/longest-consecutive-sequence/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/longest-consecutive-sequence-in-an-array) | [Watch](https://youtu.be/oO5uLE7EUlM) |

#### Problem Statement
Return the length of the longest sequence of **consecutive integers** that can be formed from the array's elements (order in the array doesn't matter) (LeetCode 128).

```text
[102, 4, 100, 1, 101, 3, 2, 1, 1] -> 4   (1, 2, 3, 4)
```

#### Approach 1: Brute force — extend each element with linear search
For each `x = a[i]`, repeatedly linear-search for `x + 1`, `x + 2`, … while found, counting the run; keep the maximum.

**Complexity:** ≈ O(n²) time (each extension is a linear search), O(1) space.

**C++**
```cpp
bool linearSearch(vector<int>& a, int num) {
    for (int x : a) if (x == num) return true;
    return false;
}
int longestConsecutiveBrute(vector<int>& a) {
    int n = a.size(), longest = (n > 0);
    for (int i = 0; i < n; i++) {
        int x = a[i], cnt = 1;
        while (linearSearch(a, x + 1)) { x++; cnt++; }
        longest = max(longest, cnt);
    }
    return longest;
}
```

**Java**
```java
class Solution {
    static boolean linearSearch(int[] a, int num) {
        for (int x : a) if (x == num) return true;
        return false;
    }
    static int longestConsecutiveBrute(int[] a) {
        int n = a.length, longest = n > 0 ? 1 : 0;
        for (int i = 0; i < n; i++) {
            int x = a[i], cnt = 1;
            while (linearSearch(a, x + 1)) { x++; cnt++; }
            longest = Math.max(longest, cnt);
        }
        return longest;
    }
}
```

#### Approach 2: Better — sort, then scan
After sorting, consecutive numbers sit next to each other. Track `lastSmaller` (last element of the current run, initially −∞) and `cnt`:
- `a[i] − 1 == lastSmaller` → extends the run: `cnt++`, `lastSmaller = a[i]`;
- `a[i] == lastSmaller` → duplicate: skip;
- otherwise → start a new run: `cnt = 1`, `lastSmaller = a[i]`.
Update `longest = max(longest, cnt)` each step.

**Complexity:** O(n log n) + O(n). Space O(1) — but the input is **modified** (sorted); the interviewer may object.

**C++**
```cpp
int longestConsecutiveSort(vector<int> a) {
    if (a.empty()) return 0;
    sort(a.begin(), a.end());
    int longest = 1, cnt = 0;
    long long lastSmaller = LLONG_MIN;
    for (int x : a) {
        if (x - 1LL == lastSmaller) { cnt++; lastSmaller = x; }
        else if (x != lastSmaller) { cnt = 1; lastSmaller = x; }
        longest = max(longest, cnt);
    }
    return longest;
}
```

**Java**
```java
class Solution {
    static int longestConsecutiveSort(int[] arr) {
        if (arr.length == 0) return 0;
        int[] a = arr.clone();
        Arrays.sort(a);
        int longest = 1, cnt = 0;
        long lastSmaller = Long.MIN_VALUE;
        for (int x : a) {
            if (x - 1L == lastSmaller) { cnt++; lastSmaller = x; }
            else if (x != lastSmaller) { cnt = 1; lastSmaller = x; }
            longest = Math.max(longest, cnt);
        }
        return longest;
    }
}
```

#### Approach 3: Optimal — hash set, start only at sequence beginnings
1. Insert everything into an `unordered_set` / `HashSet`.
2. For each `x` in the set: if `x − 1` is **also** in the set, `x` is not the start of a sequence → skip it (starting from the middle would repeat work). Otherwise count upward `x + 1`, `x + 2`, … while present.

**Why it's linear:** every element is visited once by the outer loop, and each element is counted inside a `while` loop only once (as part of the single run that starts at its sequence's first element) → about 3n operations in total, not n².

**Complexity:** Time O(3n) assuming O(1) set operations (unordered set: average/best case; in the rare worst case of many collisions it degrades — then the sorting approach is safer). Space O(n).

**C++**
```cpp
int longestConsecutive(vector<int>& nums) {
    if (nums.empty()) return 0;
    unordered_set<int> st(nums.begin(), nums.end());
    int longest = 1;
    for (int x : st) {
        if (st.find(x - 1) == st.end()) {
            int cnt = 1, cur = x;
            while (st.find(cur + 1) != st.end()) { cur++; cnt++; }
            longest = max(longest, cnt);
        }
    }
    return longest;
}
```

**Java**
```java
class Solution {
    public int longestConsecutive(int[] nums) {
        if (nums.length == 0) return 0;
        Set<Integer> st = new HashSet<>();
        for (int x : nums) st.add(x);
        int longest = 1;
        for (int x : st) {
            if (!st.contains(x - 1)) {
                int cnt = 1, cur = x;
                while (st.contains(cur + 1)) { cur++; cnt++; }
                longest = Math.max(longest, cnt);
            }
        }
        return longest;
    }
}
```

#### Key Takeaways
- "Only start counting at the beginning of a run" turns a quadratic scan into a linear one.
- State the hashing assumption (O(1) average) to the interviewer.

[↑ Contents](#contents) · [Next →](#p101)

---

<a id="p101"></a>

### 2. Longest subarray with sum K

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Hashing › FAQs | Core | Yes | [LeetCode](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/) | [Watch](https://youtu.be/frf7qxiN2qU) |

#### Problem Statement
Given an array `a` of `n` integers and an integer `k`, return the **length of the longest subarray** whose elements add up to exactly `k`. Return 0 if no such subarray exists. (LeetCode 325 "Maximum Size Subarray Sum Equals k" allows negatives; the GfG/Codestudio variant has only positives.)

A **subarray** is a *contiguous* part of the array. `[1, 2, 3]` taken from consecutive positions is a subarray; picking non-adjacent elements gives a *subsequence*, not a subarray. The whole array is also a subarray.

```text
a = [1, 2, 3, 1, 1, 1, 1, 4, 2, 3], k = 3  ->  3   ([1, 1, 1])
a = [2, 0, 0, 3], k = 3                      ->  3   ([0, 0, 3])
a = [-1, 1, 1], k = 1                        ->  3   ([-1, 1, 1])
```

#### Intuition
There are about n²/2 subarrays, so checking every one is the obvious start. To do better, think about **prefix sums**: if the sum of `a[0..i]` is `x` and some earlier prefix `a[0..j]` had sum `x − k`, then the part in between, `a[j+1..i]`, sums to exactly `k`. A hash map of "first index where each prefix sum appeared" answers that question in O(1). When the array has **no negatives**, sums only grow as the window widens, which allows an O(1)-space two-pointer window instead.

#### Approach 1: Brute Force — generate every subarray
Fix a start `i`, then extend the end `j` from `i` to `n−1`.

- The naïve version recomputes each subarray's sum with a third loop `for t in i..j` → about **O(n³)**.
- **Improved brute:** when `j` moves one step right, only one new element joins the subarray, so keep a running `s += a[j]`. That removes the third loop → **O(n²)**.

Whenever `s == k`, update `maxLen = max(maxLen, j − i + 1)`.

**Complexity:** Time O(n²) (O(n³) for the triple-loop version), Space O(1).

**C++**
```cpp
// O(n^3): third loop recomputes the sum
int longestSubarrayCubic(vector<int>& a, long long k) {
    int n = a.size(), len = 0;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            long long s = 0;
            for (int t = i; t <= j; t++) s += a[t];
            if (s == k) len = max(len, j - i + 1);
        }
    return len;
}

// O(n^2): running sum as j extends
int longestSubarrayBrute(vector<int>& a, long long k) {
    int n = a.size(), len = 0;
    for (int i = 0; i < n; i++) {
        long long s = 0;
        for (int j = i; j < n; j++) {
            s += a[j];
            if (s == k) len = max(len, j - i + 1);
        }
    }
    return len;
}
```

**Java**
```java
class Solution {
    // O(n^3): third loop recomputes the sum
    static int longestSubarrayCubic(int[] a, long k) {
        int n = a.length, len = 0;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++) {
                long s = 0;
                for (int t = i; t <= j; t++) s += a[t];
                if (s == k) len = Math.max(len, j - i + 1);
            }
        return len;
    }

    // O(n^2): running sum as j extends
    static int longestSubarrayBrute(int[] a, long k) {
        int n = a.length, len = 0;
        for (int i = 0; i < n; i++) {
            long s = 0;
            for (int j = i; j < n; j++) {
                s += a[j];
                if (s == k) len = Math.max(len, j - i + 1);
            }
        }
        return len;
    }
}
```

#### Approach 2: Better — prefix sum + hash map (optimal when negatives are allowed)
**Reverse maths.** Look at the subarrays that *end* at index `i`. Let the prefix sum up to `i` be `x`. If some subarray ending at `i` sums to `k`, the prefix in front of it must sum to `x − k`. So for each `i` we only ask: *did a prefix sum of `x − k` occur earlier, and where?*

Algorithm (one pass, map `prefix sum → first index where it occurred`):
1. `sum += a[i]`.
2. If `sum == k`, the whole prefix `a[0..i]` works → `maxLen = max(maxLen, i + 1)`.
3. Let `rem = sum − k`. If `rem` is in the map, the subarray `(map[rem] + 1 .. i)` works → `maxLen = max(maxLen, i − map[rem])`.
4. Store `sum → i` **only if `sum` is not already in the map.**

**Dry run** `a = [1, 2, 3, 1, 1, 1, 1, 4, 2, 3]`, `k = 3`:

| i | a[i] | sum | rem = sum−3 | found? | maxLen | map after |
|---|---|---|---|---|---|---|
| 0 | 1 | 1 | −2 | no | 0 | {1:0} |
| 1 | 2 | 3 | 0 | sum == k → len 2 | 2 | {1:0, 3:1} |
| 2 | 3 | 6 | 3 | at 1 → len 1 | 2 | +6:2 |
| 3 | 1 | 7 | 4 | no | 2 | +7:3 |
| 4 | 1 | 8 | 5 | no | 2 | +8:4 |
| 5 | 1 | 9 | 6 | at 2 → len 3 | **3** | +9:5 |
| … | | | | | | |

**The zeros edge case (why "only store the first occurrence").** Take `a = [2, 0, 0, 3]`, `k = 3`. The prefix sum is 2 at indices 0, 1 and 2. If we overwrite, the map says `2 → 2`. At `i = 3` (sum 5) we look up `rem = 2`, get index 2, and find only `[3]` (length 1). The correct answer is `[0, 0, 3]` (length 3), which needs the **leftmost** index where the prefix sum was 2. Keeping the first occurrence gives the longest subarray. The same reasoning covers negatives, where a prefix sum can repeat.

**Complexity:**
- Time: O(n log n) with `map` / `TreeMap` (ordered). With `unordered_map` / `HashMap` it is O(n) on average, but O(n²) in the worst case when many keys collide.
- Space: O(n), since every prefix sum may be distinct.

For arrays that contain **negatives**, this is the optimal solution; it can't be improved further. Use `long long` / `long` sums, since they can overflow `int`.

**C++**
```cpp
int longestSubarrayWithSumK(vector<int>& a, long long k) {
    map<long long, int> preSumMap;          // prefix sum -> first index
    long long sum = 0;
    int maxLen = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i];
        if (sum == k) maxLen = max(maxLen, i + 1);
        long long rem = sum - k;
        auto it = preSumMap.find(rem);
        if (it != preSumMap.end()) maxLen = max(maxLen, i - it->second);
        if (preSumMap.find(sum) == preSumMap.end()) preSumMap[sum] = i;   // keep leftmost
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int longestSubarrayWithSumK(int[] a, long k) {
        Map<Long, Integer> preSumMap = new HashMap<>();   // prefix sum -> first index
        long sum = 0;
        int maxLen = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
            if (sum == k) maxLen = Math.max(maxLen, i + 1);
            long rem = sum - k;
            Integer j = preSumMap.get(rem);
            if (j != null) maxLen = Math.max(maxLen, i - j);
            preSumMap.putIfAbsent(sum, i);                 // keep leftmost
        }
        return maxLen;
    }
}
```

> *(not in video)* A common equivalent trick is to seed the map with `0 → −1`; then step 2 (`sum == k`) is handled automatically by the lookup of `rem = 0`.

#### Approach 3: Optimal — two pointers / sliding window (positives and zeros only)
If no element is negative, extending the window to the right can only **increase** (or keep) the sum, and dropping elements from the left can only **decrease** it. So we use a variable-size window `[left, right]`:
- Move `right` forward, adding `a[right]`.
- While `sum > k` (and `left <= right`), subtract `a[left]` and move `left` forward (trim from the left).
- If `sum == k`, update `maxLen = max(maxLen, right − left + 1)`.

**Dry run** `a = [1, 2, 3, 1, 1, 1, 1, 3, 3]`, `k = 6`:
- `[1, 2, 3]` gives sum 6 → length 3.
- Adding 1 makes the sum 7 > 6, so drop 1 from the left: `[2, 3, 1]` → 6, length 3.
- Adding 1 makes it 7, so drop 2: `[3, 1, 1]` → 5. Adding 1 gives `[3, 1, 1, 1]` → 6, **length 4**.
- Adding 1 makes it 7, so drop 3: `[1, 1, 1, 1]` → 4. Adding 3 gives 7, so drop 1: `[1, 1, 1, 3]` → 6, length 4.
- Adding 3 gives 9, so drop 1, 1, 1: `[3, 3]` → 6, length 2.

Answer: 4.

**Why it's O(2n), not O(n²):** the inner `while` doesn't run n times on every step. `left` only moves forward, at most n times in total over the whole run. So `right` makes n moves and `left` makes at most n moves, which gives **O(2n)** time and **O(1)** space.

This approach **fails with negatives**, because then shrinking the window could *increase* the sum, so the greedy "trim when too big" rule is no longer valid.

**C++**
```cpp
int longestSubarrayPositives(vector<int>& a, long long k) {
    int n = a.size();
    if (n == 0) return 0;
    int left = 0, right = 0, maxLen = 0;
    long long sum = a[0];
    while (right < n) {
        while (left <= right && sum > k) {    // trim from the left
            sum -= a[left];
            left++;
        }
        if (sum == k) maxLen = max(maxLen, right - left + 1);
        right++;
        if (right < n) sum += a[right];       // add only if still inside the array
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int longestSubarrayPositives(int[] a, long k) {
        int n = a.length;
        if (n == 0) return 0;
        int left = 0, right = 0, maxLen = 0;
        long sum = a[0];
        while (right < n) {
            while (left <= right && sum > k) {    // trim from the left
                sum -= a[left];
                left++;
            }
            if (sum == k) maxLen = Math.max(maxLen, right - left + 1);
            right++;
            if (right < n) sum += a[right];       // add only if still inside the array
        }
        return maxLen;
    }
}
```

#### Edge Cases & Pitfalls
- **Zeros:** with the hash map, never overwrite an existing prefix sum. Otherwise the subarray you find is shorter than the longest one.
- **Negatives:** the two-pointer window gives wrong answers; use the prefix-sum map.
- **Overflow:** sums of up to 10⁵ elements of size 10⁹ overflow `int`, so use `long long` / `long`. The video's first submit failed until the map key was changed to `long long`.
- **Bounds:** in the two-pointer loop, add `a[right]` only after checking `right < n`.
- **Ordered vs unordered map:** `unordered_map` can degrade to O(n) per operation on adversarial inputs. Mention this trade-off to the interviewer.

#### Key Takeaways
- "Subarray sum equals k" means **prefix sum + hash map**: look up `sum − k` at each index.
- To get the *longest* subarray, store the **first** index of each prefix sum. *(Counting problems store frequencies instead; see "Count subarrays with given sum".)*
- If all elements are **non-negative**, a sliding window reaches O(n) time with O(1) space.
- Interview narrative: brute O(n²) → hashing (optimal with negatives) → the zero/negative edge case → two pointers for positives.

[↑ Contents](#contents) · [← Previous](#p100) · [Next →](#p102)

---

<a id="p102"></a>

### 3. Largest Subarray with Sum 0

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Hashing › FAQs | Core | Yes | [LeetCode](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/) | [Watch](https://youtu.be/xmguZ6GbatA) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Given an array `a` of `n` integers containing **both positive and negative** values, return the **length of the longest subarray whose sum is 0**. Return 0 if there is none.

```text
a = [15, -2, 2, -8, 1, 7, 10, 23]  ->  5     ([-2, 2, -8, 1, 7])
a = [1, 2, 3]                      ->  0
a = [1, 0, 3]                      ->  1     ([0])
a = [6, -2, 2, -8, 1, 7, 4, -10]   ->  8     (the whole array)
```

This is the special case `k = 0` of "Longest subarray with sum K" (previous problem). Because zero-sum subarrays need negatives (or zeros), the sliding-window trick doesn't apply, so the hashing solution is the optimal one.

#### Intuition
Let `P(i)` be the prefix sum of `a[0..i]`. A subarray `a[j+1..i]` has sum 0 exactly when `P(i) == P(j)`. So the longest zero-sum subarray ending at `i` starts right after the **first** index where the same prefix sum was seen. Store `prefix sum → first index` in a hash map.

#### Approach 1: Brute Force — every subarray with a running sum
For each start `i`, extend `j` and keep `sum += a[j]`. Whenever `sum == 0`, update `maxLen = max(maxLen, j − i + 1)`.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int maxLenZeroSumBrute(vector<int>& a) {
    int n = a.size(), maxLen = 0;
    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            if (sum == 0) maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int maxLenZeroSumBrute(int[] a) {
        int n = a.length, maxLen = 0;
        for (int i = 0; i < n; i++) {
            long sum = 0;
            for (int j = i; j < n; j++) {
                sum += a[j];
                if (sum == 0) maxLen = Math.max(maxLen, j - i + 1);
            }
        }
        return maxLen;
    }
}
```

#### Approach 2: Optimal — prefix sum + hash map of first occurrences
Traverse once, keeping `sum` = prefix sum up to `i`:
1. If `sum == 0`, the whole prefix `a[0..i]` has sum 0 → `maxLen = i + 1`.
2. Else if `sum` was seen before at index `j`, then `a[j+1..i]` has sum 0 → `maxLen = max(maxLen, i − j)`.
3. Else record `sum → i`. Never overwrite an existing entry, because the earliest index gives the longest subarray.

**Dry run** `a = [15, -2, 2, -8, 1, 7, 10, 23]`:

| i | a[i] | sum | seen before? | maxLen | map after |
|---|---|---|---|---|---|
| 0 | 15 | 15 | no | 0 | {15:0} |
| 1 | −2 | 13 | no | 0 | +13:1 |
| 2 | 2 | 15 | at 0 → len 2 | 2 | — |
| 3 | −8 | 7 | no | 2 | +7:3 |
| 4 | 1 | 8 | no | 2 | +8:4 |
| 5 | 7 | 15 | at 0 → len 5 | **5** | — |
| 6 | 10 | 25 | no | 5 | +25:6 |
| 7 | 23 | 48 | no | 5 | +48:7 |

Answer: 5, which is `a[1..5] = [−2, 2, −8, 1, 7]`.

**Complexity:**
- Time: O(n) on average with `unordered_map` / `HashMap`, or O(n log n) with an ordered `map` / `TreeMap`. With an unordered map, heavy collisions can push the worst case to O(n²).
- Space: O(n) for the map.

**C++**
```cpp
int maxLenZeroSum(vector<int>& a) {
    unordered_map<long long, int> first;   // prefix sum -> first index
    long long sum = 0;
    int maxLen = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i];
        if (sum == 0) maxLen = i + 1;
        else {
            auto it = first.find(sum);
            if (it != first.end()) maxLen = max(maxLen, i - it->second);
            else first[sum] = i;
        }
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int maxLenZeroSum(int[] a) {
        Map<Long, Integer> first = new HashMap<>();   // prefix sum -> first index
        long sum = 0;
        int maxLen = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
            if (sum == 0) maxLen = i + 1;
            else {
                Integer j = first.get(sum);
                if (j != null) maxLen = Math.max(maxLen, i - j);
                else first.put(sum, i);
            }
        }
        return maxLen;
    }
}
```

> **Equivalent formulation:** seed the map with `0 → −1`. Then step 1 is just a special case of step 2 (`i − (−1) = i + 1`).

#### Edge Cases & Pitfalls
- **A single 0** is a zero-sum subarray of length 1. The map handles it, because the prefix sum repeats.
- **The whole array sums to 0:** handled by the `sum == 0 → i + 1` branch, or by the `0 → −1` seed.
- **Overwriting map entries** gives shorter subarrays. Keep the first index only.
- **Overflow:** use `long long` / `long` for the prefix sum with large values.
- **Sliding window does not work** here, because the array has negatives.

#### Key Takeaways
- "Subarray sum = 0" means **a repeated prefix sum**. The distance between the first and the latest occurrence is the length.
- This is the `k = 0` case of the longest-subarray-with-sum-K template (`look up sum − k`, store first index).

[↑ Contents](#contents) · [← Previous](#p101) · [Next →](#p103)

---

<a id="p103"></a>

### 4. Count subarrays with given sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Hashing › FAQs | Core | No | [LeetCode](https://leetcode.com/problems/subarray-sum-equals-k/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-subarrays-with-given-sum) | [Watch](https://youtu.be/xvNwoz-ufXA) |

#### Problem Statement
Given an integer array `a` (it may contain **negatives**) and an integer `k`, return the **number of subarrays** whose sum equals `k` (LeetCode 560). A subarray is a contiguous part of the array. It can be a single element or the whole array, but you can't skip elements (that would be a subsequence).

```text
a = [1, 2, 3, -3, 1, 1, 1, 4, 2, -3], k = 3  ->  8
    [1,2] [1,2,3,-3] [3] [2,3,-3,1] [3,-3,1,1,1] [1,1,1] [4,2,-3] [-3,1,1,1,4,2,-3]
a = [3, -3, 1, 1, 1], k = 3                   ->  3
```

> Prerequisite: "Longest subarray with sum K". This problem uses the same prefix-sum idea, but stores **counts** instead of first indices.

#### Intuition
Every subarray `a[i..j]` sums to `prefix[j] − prefix[i−1]`. Standing at index `j` with prefix sum `s`, the subarrays **ending at `j`** with sum `k` correspond one-to-one with the earlier prefixes whose sum is `s − k`. So if a hash map records **how many times** each prefix sum has occurred, we can add `count[s − k]` at every step.

#### Approach 1: Brute Force — three nested loops
Generate every subarray `(i, j)` and add it up with a third loop. Count the ones equal to `k`.

**Complexity:** ≈ O(n³) time, O(1) space.

**C++**
```cpp
int countSubarraysCubic(vector<int>& a, int k) {
    int n = a.size(), cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            long long s = 0;
            for (int t = i; t <= j; t++) s += a[t];
            if (s == k) cnt++;
        }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countSubarraysCubic(int[] a, int k) {
        int n = a.length, cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++) {
                long s = 0;
                for (int t = i; t <= j; t++) s += a[t];
                if (s == k) cnt++;
            }
        return cnt;
    }
}
```

#### Approach 2: Better — running sum
When `j` moves one step right, the subarray gains exactly one element, `a[j]`. So keep `s += a[j]` instead of re-summing `a[i..j]`. This drops the third loop.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int countSubarraysBetter(vector<int>& a, int k) {
    int n = a.size(), cnt = 0;
    for (int i = 0; i < n; i++) {
        long long s = 0;
        for (int j = i; j < n; j++) {
            s += a[j];
            if (s == k) cnt++;
        }
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countSubarraysBetter(int[] a, int k) {
        int n = a.length, cnt = 0;
        for (int i = 0; i < n; i++) {
            long s = 0;
            for (int j = i; j < n; j++) {
                s += a[j];
                if (s == k) cnt++;
            }
        }
        return cnt;
    }
}
```

#### Approach 3: Optimal — prefix sum + frequency map
Maintain `preSum` (sum of `a[0..i]`) and a map `mpp[prefix sum] = number of times it has occurred so far`.

1. **Seed `mpp[0] = 1`.** This is the "empty prefix", the case where you remove nothing. Without it, subarrays that start at index 0 (where `preSum == k` itself) would be missed.
2. For each element: `preSum += a[i]`. Then `cnt += mpp[preSum − k]`, because each earlier prefix with that sum can be cut off to leave a subarray with sum `k` ending here. Finally `mpp[preSum]++`.

**Dry run** `a = [1, 2, 3, -3, 1, 1, 1, 4, 2, -3]`, `k = 3`:

| i | a[i] | preSum | remove (preSum−3) | its count | cnt | map update |
|---|---|---|---|---|---|---|
| — | | 0 | | | 0 | {0:1} |
| 0 | 1 | 1 | −2 | 0 | 0 | 1:1 |
| 1 | 2 | 3 | 0 | 1 | 1 | 3:1 |
| 2 | 3 | 6 | 3 | 1 | 2 | 6:1 |
| 3 | −3 | 3 | 0 | 1 | 3 | 3:2 |
| 4 | 1 | 4 | 1 | 1 | 4 | 4:1 |
| 5 | 1 | 5 | 2 | 0 | 4 | 5:1 |
| 6 | 1 | 6 | 3 | **2** | 6 | 6:2 |
| 7 | 4 | 10 | 7 | 0 | 6 | 10:1 |
| 8 | 2 | 12 | 9 | 0 | 6 | 12:1 |
| 9 | −3 | 9 | 6 | **2** | **8** | 9:1 |

At `i = 6`, prefix sum 3 occurred twice (after `[1,2]` and after `[1,2,3,−3]`). That gives two subarrays ending here: `[3,−3,1,1,1]` and `[1,1,1]`. This is why we store **counts**.

Try `[3, −3, 1, 1, 1]`, `k = 3` without the `{0:1}` seed: you'd get 1 instead of 3, because the subarrays `[3]` and `[3, −3, 1, 1, 1]` start at index 0.

**Complexity:**
- Time: O(n) on average with `unordered_map` / `HashMap` (O(n²) in the worst case with heavy collisions), or O(n log n) with `map` / `TreeMap`.
- Space: O(n), since all prefix sums may be distinct.

With negatives present, you can't do better than this. A sliding window doesn't work because sums are not monotonic.

**C++**
```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<long long, int> mpp;   // prefix sum -> frequency
    mpp[0] = 1;                          // empty prefix
    long long preSum = 0;
    int cnt = 0;
    for (int x : nums) {
        preSum += x;
        auto it = mpp.find(preSum - k);
        if (it != mpp.end()) cnt += it->second;
        mpp[preSum]++;
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    public int subarraySum(int[] nums, int k) {
        Map<Long, Integer> mpp = new HashMap<>();   // prefix sum -> frequency
        mpp.put(0L, 1);                             // empty prefix
        long preSum = 0;
        int cnt = 0;
        for (int x : nums) {
            preSum += x;
            cnt += mpp.getOrDefault(preSum - k, 0);
            mpp.merge(preSum, 1, Integer::sum);
        }
        return cnt;
    }
}
```

#### Edge Cases & Pitfalls
- **Forgetting `mpp[0] = 1`** undercounts every subarray that starts at index 0.
- **Order matters:** look up `preSum − k` *before* inserting the current `preSum`. Otherwise, when `k == 0`, you count the empty subarray at each step.
- **`k = 0` and zeros:** `[0, 0, 0]` with `k = 0` has 6 subarrays. The frequency map handles this naturally.
- **Overflow:** keep the prefix sum in `long long` / `long` when values are large.
- **Different from the "longest" version:** there you store the *first index* of each prefix sum; here you store its *frequency*.

#### Key Takeaways
- "How many subarrays sum to k" uses **prefix sum + frequency map**: at each index, add `freq[preSum − k]`.
- Seed the map with `{0: 1}`.
- The same template counts subarrays with a given XOR. Replace `−` with `^` (next problem).

[↑ Contents](#contents) · [← Previous](#p102) · [Next →](#p104)

---

<a id="p104"></a>

### 5. Count subarrays with given xor K

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Hashing › FAQs | Pro | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-subarrays-with-a-given-xor-k) | [Watch](https://youtu.be/eZr-6p0B7ME) |

#### Problem Statement
Given an integer array `a` and an integer `k`, count the **subarrays whose XOR** (bitwise exclusive-or of all their elements) **equals `k`**. A subarray is contiguous; picking `a[0]` and `a[4]` without the elements in between does not count.

```text
a = [4, 2, 2, 6, 4], k = 6  ->  4
    [4, 2]             4^2         = 6
    [2, 2, 6]          (2^2)^6     = 0^6 = 6
    [6]                             = 6
    [4, 2, 2, 6, 4]    4s cancel, 2s cancel -> 6
```

XOR facts used below: `x ^ x = 0`, `x ^ 0 = x`, and XOR is associative and commutative. So XOR-ing both sides of an equation by the same value is "undo".

#### Intuition
This is the XOR version of "Count subarrays with given sum". Let `xr` be the XOR of the prefix `a[0..i]`. Split that prefix into a front part with XOR `x` and a back part (ending at `i`) with XOR `k`:

```text
x ^ k = xr   ->   XOR both sides with k   ->   x = xr ^ k
```

So the subarrays ending at `i` with XOR `k` match one-to-one with earlier prefixes whose XOR is `xr ^ k`. Keep a **frequency map of prefix XORs** and add `freq[xr ^ k]` at each index.

#### Approach 1: Brute Force — three nested loops
Generate every subarray `(i, j)` and XOR its elements with a third loop. Count the ones equal to `k`.

**Complexity:** ≈ O(n³) time, O(1) space.

**C++**
```cpp
int countXorCubic(vector<int>& a, int k) {
    int n = a.size(), cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            int xr = 0;
            for (int t = i; t <= j; t++) xr ^= a[t];
            if (xr == k) cnt++;
        }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countXorCubic(int[] a, int k) {
        int n = a.length, cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++) {
                int xr = 0;
                for (int t = i; t <= j; t++) xr ^= a[t];
                if (xr == k) cnt++;
            }
        return cnt;
    }
}
```

#### Approach 2: Better — running XOR
When `j` advances, the subarray gains one element, so `xr ^= a[j]` updates it in O(1).

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int countXorBetter(vector<int>& a, int k) {
    int n = a.size(), cnt = 0;
    for (int i = 0; i < n; i++) {
        int xr = 0;
        for (int j = i; j < n; j++) {
            xr ^= a[j];
            if (xr == k) cnt++;
        }
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countXorBetter(int[] a, int k) {
        int n = a.length, cnt = 0;
        for (int i = 0; i < n; i++) {
            int xr = 0;
            for (int j = i; j < n; j++) {
                xr ^= a[j];
                if (xr == k) cnt++;
            }
        }
        return cnt;
    }
}
```

#### Approach 3: Optimal — prefix XOR + frequency map
1. `mpp[0] = 1`: the empty prefix, so subarrays that start at index 0 get counted.
2. For each element: `xr ^= a[i]`, then `x = xr ^ k`, then `cnt += mpp[x]`, then `mpp[xr]++`. Do the lookup **before** the insert.

**Dry run** `a = [4, 2, 2, 6, 4]`, `k = 6`:

| i | a[i] | xr | x = xr^6 | mpp[x] | cnt | map after |
|---|---|---|---|---|---|---|
| — | | 0 | | | 0 | {0:1} |
| 0 | 4 | 4 | 2 | 0 | 0 | 4:1 |
| 1 | 2 | 6 | 0 | 1 | 1 | 6:1 |
| 2 | 2 | 4 | 2 | 0 | 1 | 4:2 |
| 3 | 6 | 2 | 4 | **2** | 3 | 2:1 |
| 4 | 4 | 6 | 0 | 1 | **4** | 6:2 |

At `i = 3`, prefix XOR 4 has occurred twice (after `[4]` and after `[4, 2, 2]`), so two subarrays end here: `[2, 2, 6]` and `[6]`.

**Complexity:**
- Time: O(n) on average with `unordered_map` / `HashMap` (worse with collisions), or O(n log n) with `map` / `TreeMap`.
- Space: O(n) for the map in the worst case, when all prefix XORs are distinct.

**C++**
```cpp
int subarraysWithXorK(vector<int>& a, int k) {
    unordered_map<int, int> mpp;   // prefix xor -> frequency
    mpp[0] = 1;
    int xr = 0, cnt = 0;
    for (int v : a) {
        xr ^= v;
        int x = xr ^ k;            // front part we need to cut off
        auto it = mpp.find(x);
        if (it != mpp.end()) cnt += it->second;
        mpp[xr]++;
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    public int subarraysWithXorK(int[] a, int k) {
        Map<Integer, Integer> mpp = new HashMap<>();   // prefix xor -> frequency
        mpp.put(0, 1);
        int xr = 0, cnt = 0;
        for (int v : a) {
            xr ^= v;
            int x = xr ^ k;                            // front part we need to cut off
            cnt += mpp.getOrDefault(x, 0);
            mpp.merge(xr, 1, Integer::sum);
        }
        return cnt;
    }
}
```

#### Edge Cases & Pitfalls
- **Forgetting to insert `xr` into the map:** the video's first run failed for exactly this reason. Remember to call `mpp[xr]++` after the lookup.
- **Seed `{0: 1}`**, otherwise the prefixes that themselves XOR to `k` are missed.
- **`k = 0`:** counts the subarrays whose elements cancel out. The template works unchanged.
- **The count can exceed `int`** for large `n` (up to about n²/2). Use `long long` / `long` if the constraints require it.

#### Key Takeaways
- Prefix XOR has the same "cut off the front" logic as prefix sum, because `xr ^ k` undoes `k`.
- Template: `cnt += freq[pref OP⁻¹ k]; freq[pref]++`, with `freq[identity] = 1`.

[↑ Contents](#contents) · [← Previous](#p103)

---
