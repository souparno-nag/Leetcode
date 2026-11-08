# Arrays — Striver's A2Z DSA Sheet Notes

Section 3 of 20 · 32 problems · 31 with video, 1 without · [All sections](00-index.md)

[← Sorting](02-sorting.md) | [Hashing →](04-hashing.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Fundamentals**

1. [Linear Search](#p68) — Basic
2. [Largest Element](#p69) — Basic
3. [Second Largest Element](#p70) — Basic
4. [Maximum Consecutive Ones](#p71) — Basic
5. [Left Rotate Array by One](#p72) — Basic
6. [Left Rotate Array by K Places](#p73) — Core

**Logic Building**

7. [Move Zeros to End](#p74) — Basic
8. [Remove duplicates from sorted array](#p75) — Basic
9. [Find missing number](#p76) — Basic
10. [Union of two sorted arrays](#p77) — Core
11. [Intersection of two sorted arrays](#p78) — Core

**FAQs(Medium)**

12. [Majority Element-I](#p79) — Core
13. [Leaders in an Array](#p80) — Core
14. [Rearrange array elements by sign](#p81) — Core
15. [Print the matrix in spiral manner](#p82) — Core
16. [Pascal's Triangle I](#p83) — Core
17. [Pascal's Triangle II](#p84) — Core
18. [Pascal's Triangle III](#p85) — Core
19. [Rotate matrix by 90 degrees](#p86) — Core
20. [Set Matrix Zeroes](#p87) — Core
21. [Two Sum](#p88) — Basic
22. [3 Sum](#p89) — Core
23. [4 Sum](#p90) — Pro
24. [Sort an array of 0's 1's and 2's](#p91) — Core
25. [Kadane's Algorithm](#p92) — Core
26. [Next Permutation](#p93) — Core

**FAQs(Hard)**

27. [Majority Element-II](#p94) — Core
28. [Find the repeating and missing number](#p95) — Core
29. [Count Inversions](#p96) — Pro
30. [Reverse Pairs](#p97) — Pro
31. [Maximum Product Subarray in an Array](#p98) — Core · *no video*
32. [Merge two sorted arrays without extra space](#p99) — Core

---

## Fundamentals

<a id="p68"></a>

### 1. Linear Search

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Fundamentals | Basic | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/linear-search-algorithm) | [Watch from 41:05](https://youtu.be/wvcQg43_V8U?t=2465) |

#### Problem Statement
Given an array `arr` and a number `num`, return the index of the **first occurrence** of `num` (0-based), or −1 if it is not present.

```text
arr = [1, 2, 3, 4, 5], num = 4  -> 3
arr = [1, 2, 3, 4, 5], num = 10 -> -1
```

#### Approach: Linear search (from the video)
Walk the array from left to right; the first index where `arr[i] == num` is the answer. If the loop finishes without returning, the number is absent → return −1.
- For the **last** occurrence, iterate from the end instead.
- For **all** occurrences, collect every matching index in a list instead of returning.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
int linearSearch(vector<int>& arr, int num) {
    for (int i = 0; i < (int)arr.size(); i++)
        if (arr[i] == num) return i;
    return -1;
}
```

**Java**
```java
class Solution {
    static int linearSearch(int[] arr, int num) {
        for (int i = 0; i < arr.length; i++)
            if (arr[i] == num) return i;
        return -1;
    }
}
```

#### Key Takeaways
- Linear search works on any array; if the array is sorted, binary search (O(log n)) is better.

[↑ Contents](#contents) · [Next →](#p69)

---

<a id="p69"></a>

### 2. Largest Element

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Fundamentals | Basic | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-the-largest-element-in-an-array) | [Watch from 8:46](https://youtu.be/37E9ckMDdTk?t=526) |

#### Problem Statement
Return the largest element of an integer array.

```text
[3, 2, 1, 5, 2] -> 5
```

#### Interview pattern (from the video)
For every problem, present **brute → better → optimal**, even when the jump is small — it shows your thought process.

#### Approach 1: Brute force — sort
Sort ascending; the largest element is `arr[n − 1]`.

**Complexity:** Time O(n log n) (merge/quick sort), Space O(1) with an in-place sort.

**C++**
```cpp
int largestBrute(vector<int> arr) {
    sort(arr.begin(), arr.end());
    return arr[arr.size() - 1];
}
```

**Java**
```java
class Solution {
    static int largestBrute(int[] arr) {
        int[] a = arr.clone();
        Arrays.sort(a);
        return a[a.length - 1];
    }
}
```

#### Approach 2: Optimal — one pass
No "better" approach exists here. Assume `largest = arr[0]`, then for every element, if it is greater than `largest`, update `largest`.

**Dry run:** largest = 3 → 2 no → 1 no → 5 yes (largest = 5) → 2 no → answer 5.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
int largestElement(vector<int>& arr) {
    int largest = arr[0];
    for (int i = 1; i < (int)arr.size(); i++)
        if (arr[i] > largest) largest = arr[i];
    return largest;
}
```

**Java**
```java
class Solution {
    static int largestElement(int[] arr) {
        int largest = arr[0];
        for (int i = 1; i < arr.length; i++)
            if (arr[i] > largest) largest = arr[i];
        return largest;
    }
}
```

#### Key Takeaways
- Initialise the running maximum with an actual element (`arr[0]`) — not 0 — so negative arrays work.

[↑ Contents](#contents) · [← Previous](#p68) · [Next →](#p70)

---

<a id="p70"></a>

### 3. Second Largest Element

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Fundamentals | Basic | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/second-largest-element) | [Watch from 13:30](https://youtu.be/37E9ckMDdTk?t=810) |

#### Problem Statement
Return the **second largest distinct** element of an array (or −1 if it doesn't exist). The video also asks for the second smallest.

```text
[1, 2, 4, 7, 7, 5] -> second largest 5, second smallest 2
[7, 7, 7]          -> -1 (no second largest)
```

#### Approach 1: Brute force — sort, then scan from the back
After sorting, `arr[n − 1]` is the largest. The second largest is **not** necessarily `arr[n − 2]` (duplicates of the max, e.g. [1, 2, 4, 5, 7, 7]). Scan from `n − 2` down to 0 and return the first element different from the largest.

**Complexity:** O(n log n) for sorting + O(n) scan in the worst case (e.g. [1, 7, 7, 7, 7]). Space O(1).

**C++**
```cpp
int secondLargestBrute(vector<int> arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    int largest = arr[n - 1];
    for (int i = n - 2; i >= 0; i--)
        if (arr[i] != largest) return arr[i];
    return -1;
}
```

**Java**
```java
class Solution {
    static int secondLargestBrute(int[] arr) {
        int n = arr.length;
        int[] a = arr.clone();
        Arrays.sort(a);
        int largest = a[n - 1];
        for (int i = n - 2; i >= 0; i--)
            if (a[i] != largest) return a[i];
        return -1;
    }
}
```

#### Approach 2: Better — two passes
Pass 1: find `largest`. Pass 2: `secondLargest = max` of all elements that are **not equal to** `largest` (start it at −1, or `INT_MIN` if negatives are allowed).

**Complexity:** Time O(2n) = O(n), Space O(1). Say "two passes" explicitly in an interview.

**C++**
```cpp
int secondLargestBetter(vector<int>& arr) {
    int largest = arr[0];
    for (int x : arr) largest = max(largest, x);
    int second = -1;
    for (int x : arr)
        if (x > second && x != largest) second = x;
    return second;
}
```

**Java**
```java
class Solution {
    static int secondLargestBetter(int[] arr) {
        int largest = arr[0];
        for (int x : arr) largest = Math.max(largest, x);
        int second = -1;
        for (int x : arr)
            if (x > second && x != largest) second = x;
        return second;
    }
}
```

#### Approach 3: Optimal — one pass
Keep `largest = arr[0]`, `second = −1` (or `INT_MIN`). For each element `x`:
- if `x > largest`: the old largest becomes second (**update `second` first**), then `largest = x` — like a topper being pushed to second place;
- else if `x < largest && x > second`: `second = x`;
- if `x == largest`: do nothing.

Second smallest is symmetric: `smallest = arr[0]`, `second = INT_MAX`; if `x < smallest` → `second = smallest, smallest = x`; else if `x != smallest && x < second` → `second = x`.

**Dry run ([1, 2, 4, 7, 7, 5]):** (L, S) = (1, −1) → 2: (2, 1) → 4: (4, 2) → 7: (7, 4) → 7: equal, skip → 5: 5 < 7 and 5 > 4 → (7, 5).

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
int secondLargest(vector<int>& arr) {
    int largest = arr[0], second = INT_MIN;
    for (int i = 1; i < (int)arr.size(); i++) {
        if (arr[i] > largest) {
            second = largest;
            largest = arr[i];
        } else if (arr[i] < largest && arr[i] > second) {
            second = arr[i];
        }
    }
    return second == INT_MIN ? -1 : second;
}

int secondSmallest(vector<int>& arr) {
    int smallest = arr[0], second = INT_MAX;
    for (int i = 1; i < (int)arr.size(); i++) {
        if (arr[i] < smallest) {
            second = smallest;
            smallest = arr[i];
        } else if (arr[i] != smallest && arr[i] < second) {
            second = arr[i];
        }
    }
    return second == INT_MAX ? -1 : second;
}
```

**Java**
```java
class Solution {
    static int secondLargest(int[] arr) {
        int largest = arr[0], second = Integer.MIN_VALUE;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > largest) {
                second = largest;
                largest = arr[i];
            } else if (arr[i] < largest && arr[i] > second) {
                second = arr[i];
            }
        }
        return second == Integer.MIN_VALUE ? -1 : second;
    }

    static int secondSmallest(int[] arr) {
        int smallest = arr[0], second = Integer.MAX_VALUE;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < smallest) {
                second = smallest;
                smallest = arr[i];
            } else if (arr[i] != smallest && arr[i] < second) {
                second = arr[i];
            }
        }
        return second == Integer.MAX_VALUE ? -1 : second;
    }
}
```

#### Edge Cases & Pitfalls
- All elements equal → no second largest; say so to the interviewer.
- With negative numbers, −1 is not a safe "empty" value — use `INT_MIN`/`INT_MAX`.
- (The video's on-screen second-smallest function accidentally returned `smallest`; return the *second* variable.)

#### Key Takeaways
- "Top-2 tracking" in one pass: when a new best appears, demote the old best to second.

[↑ Contents](#contents) · [← Previous](#p69) · [Next →](#p71)

---

<a id="p71"></a>

### 4. Maximum Consecutive Ones

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Fundamentals | Basic | No | [LeetCode](https://leetcode.com/problems/max-consecutive-ones/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/maximum-consecutive-ones-in-a-binary-array) | [Watch from 18:44](https://youtu.be/bYWLJb3vCWY?t=1124) |

#### Problem Statement
Given a binary array (0s and 1s), return the maximum number of consecutive 1s (LeetCode 485).

```text
[1, 1, 0, 1, 1, 1, 0, 1, 1] -> 3
```

#### Approach: Single pass with a running counter (from the video)
The video skips brute/better because the optimal solution is direct:
- `cnt` = length of the current run of 1s; `maxi` = best so far.
- On a 1: `cnt++`, `maxi = max(maxi, cnt)`.
- On a 0: the run is broken → `cnt = 0`.

**Dry run:** 1→cnt 1 (max 1), 1→2 (2), 0→0, 1→1, 1→2, 1→3 (max 3), 0→0, 1→1, 1→2 → answer 3.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
int findMaxConsecutiveOnes(vector<int>& nums) {
    int maxi = 0, cnt = 0;
    for (int x : nums) {
        if (x == 1) { cnt++; maxi = max(maxi, cnt); }
        else cnt = 0;
    }
    return maxi;
}
```

**Java**
```java
class Solution {
    public int findMaxConsecutiveOnes(int[] nums) {
        int maxi = 0, cnt = 0;
        for (int x : nums) {
            if (x == 1) { cnt++; maxi = Math.max(maxi, cnt); }
            else cnt = 0;
        }
        return maxi;
    }
}
```

#### Key Takeaways
- "Longest run" problems: a counter that grows on success and resets on failure.

[↑ Contents](#contents) · [← Previous](#p70) · [Next →](#p72)

---

<a id="p72"></a>

### 5. Left Rotate Array by One

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Fundamentals | Basic | No | [LeetCode](https://leetcode.com/problems/rotate-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/left-rotate-array-by-one) | [Watch from 1:01](https://youtu.be/wvcQg43_V8U?t=61) |

#### Problem Statement
Left-rotate an array by **one** place, in place.

```text
[1, 2, 3, 4, 5] -> [2, 3, 4, 5, 1]
```

#### Approach: Optimal — save the first element, shift the rest (from the video)
The video goes straight to the optimal solution (a brute force with an extra array is not needed here):
1. `temp = arr[0]`.
2. For `i = 1..n−1`: `arr[i − 1] = arr[i]` (everyone moves one step left).
3. `arr[n − 1] = temp`.

**Complexity:** Time O(n). **Extra** space O(1).
> Interview tip from the video: distinguish *extra* space (O(1) here) from the space the *algorithm uses* (the input array, O(n)) — say both clearly.

**C++**
```cpp
void leftRotateByOne(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;
    int temp = arr[0];
    for (int i = 1; i < n; i++) arr[i - 1] = arr[i];
    arr[n - 1] = temp;
}
```

**Java**
```java
class Solution {
    static void leftRotateByOne(int[] arr) {
        int n = arr.length;
        if (n == 0) return;
        int temp = arr[0];
        for (int i = 1; i < n; i++) arr[i - 1] = arr[i];
        arr[n - 1] = temp;
    }
}
```

#### Key Takeaways
- Rotation by one = remember the element that wraps around, shift the others.

[↑ Contents](#contents) · [← Previous](#p71) · [Next →](#p73)

---

<a id="p73"></a>

### 6. Left Rotate Array by K Places

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Fundamentals | Core | No | [LeetCode](https://leetcode.com/problems/rotate-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/left-rotate-array-by-k-places) | [Watch from 8:05](https://youtu.be/wvcQg43_V8U?t=485) |

#### Problem Statement
Left-rotate an array by `d` places, in place. (LeetCode 189, linked on the sheet, asks for a **right** rotation by `k` — covered at the end.)

```text
arr = [1, 2, 3, 4, 5, 6, 7], d = 2 -> [3, 4, 5, 6, 7, 1, 2]
arr = [1, 2, 3, 4, 5, 6, 7], d = 3 -> [4, 5, 6, 7, 1, 2, 3]
```

#### First observation: reduce `d`
Rotating an array of size `n` by `n` places brings it back to the original. So rotating by 8 = 7 + 1 is the same as rotating by 1, and by 15 = 7 + 7 + 1 also 1. Always do `d = d % n` first.

#### Approach 1: Brute force — temporary array of the first `d` elements
1. Copy `arr[0..d−1]` into `temp`.
2. Shift: for `i = d..n−1`, `arr[i − d] = arr[i]`.
3. Put back: for `i = n−d..n−1`, `arr[i] = temp[i − (n − d)]` (the base index `n − d` maps to `temp[0]`).

**Complexity:** Time O(d) + O(n − d) + O(d) = O(n + d). Extra space O(d).

**C++**
```cpp
void leftRotateBrute(vector<int>& arr, int d) {
    int n = arr.size();
    if (n == 0) return;
    d %= n;
    vector<int> temp(arr.begin(), arr.begin() + d);
    for (int i = d; i < n; i++) arr[i - d] = arr[i];
    for (int i = n - d; i < n; i++) arr[i] = temp[i - (n - d)];
}
```

**Java**
```java
class Solution {
    static void leftRotateBrute(int[] arr, int d) {
        int n = arr.length;
        if (n == 0) return;
        d %= n;
        int[] temp = Arrays.copyOfRange(arr, 0, d);
        for (int i = d; i < n; i++) arr[i - d] = arr[i];
        for (int i = n - d; i < n; i++) arr[i] = temp[i - (n - d)];
    }
}
```

#### Approach 2: Optimal — three reversals
Observation on [1 2 3 | 4 5 6 7] with d = 3:
1. Reverse the first `d`: [3 2 1 | 4 5 6 7].
2. Reverse the remaining `n − d`: [3 2 1 | 7 6 5 4].
3. Reverse the whole array: **[4 5 6 7 1 2 3]**.

**Complexity:** Time O(d) + O(n − d) + O(n) = O(2n). Extra space **O(1)** — that's the gain over the brute force. If your language has no built-in reverse, write a manual two-pointer `reverse(arr, start, end)`.

**C++**
```cpp
void reverseRange(vector<int>& arr, int s, int e) {
    while (s < e) swap(arr[s++], arr[e--]);
}
void leftRotate(vector<int>& arr, int d) {
    int n = arr.size();
    if (n == 0) return;
    d %= n;
    reverseRange(arr, 0, d - 1);
    reverseRange(arr, d, n - 1);
    reverseRange(arr, 0, n - 1);
}
```

**Java**
```java
class Solution {
    static void reverseRange(int[] arr, int s, int e) {
        while (s < e) { int t = arr[s]; arr[s] = arr[e]; arr[e] = t; s++; e--; }
    }
    static void leftRotate(int[] arr, int d) {
        int n = arr.length;
        if (n == 0) return;
        d %= n;
        reverseRange(arr, 0, d - 1);
        reverseRange(arr, d, n - 1);
        reverseRange(arr, 0, n - 1);
    }
}
```

#### Right rotation by `k` — the video's assignment / LeetCode 189 *(not solved in video)*
Right-rotating by `k` = left-rotating by `n − k`. With reversals: reverse the whole array, then the first `k`, then the rest.

**C++**
```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
```

**Java**
```java
class Solution {
    private void rev(int[] a, int s, int e) {
        while (s < e) { int t = a[s]; a[s] = a[e]; a[e] = t; s++; e--; }
    }
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k %= n;
        rev(nums, 0, n - 1);
        rev(nums, 0, k - 1);
        rev(nums, k, n - 1);
    }
}
```

#### Key Takeaways
- `d % n` first, always.
- Three reversals rotate an array in place — a classic, worth memorising.

[↑ Contents](#contents) · [← Previous](#p72) · [Next →](#p74)

---

## Logic Building

<a id="p74"></a>

### 7. Move Zeros to End

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Logic Building | Basic | No | [LeetCode](https://leetcode.com/problems/move-zeroes/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/move-zeros-to-the-end-of-an-array) | [Watch from 27:13](https://youtu.be/wvcQg43_V8U?t=1633) |

#### Problem Statement
Move all zeros to the end of the array while keeping the relative order of the non-zero elements, in place (LeetCode 283).

```text
[1, 0, 2, 3, 2, 0, 0, 4, 5, 1] -> [1, 2, 3, 2, 4, 5, 1, 0, 0, 0]
```

#### Approach 1: Brute force — temporary array of non-zeros
1. Copy every non-zero element into `temp` (size `x`).
2. Copy `temp` back into `arr[0..x−1]`.
3. Fill `arr[x..n−1]` with zeros.

**Complexity:** Time O(n) + O(x) + O(n − x) = O(2n). Extra space O(x), O(n) in the worst case (no zeros at all).

**C++**
```cpp
void moveZerosBrute(vector<int>& arr) {
    vector<int> temp;
    for (int x : arr) if (x != 0) temp.push_back(x);
    for (int i = 0; i < (int)temp.size(); i++) arr[i] = temp[i];
    for (int i = temp.size(); i < (int)arr.size(); i++) arr[i] = 0;
}
```

**Java**
```java
class Solution {
    static void moveZerosBrute(int[] arr) {
        List<Integer> temp = new ArrayList<>();
        for (int x : arr) if (x != 0) temp.add(x);
        for (int i = 0; i < temp.size(); i++) arr[i] = temp.get(i);
        for (int i = temp.size(); i < arr.length; i++) arr[i] = 0;
    }
}
```

#### Approach 2: Optimal — two pointers
1. Find the first zero; call its index `j`. If there is no zero, return.
2. For `i = j + 1..n−1`: if `arr[i] != 0`, swap `arr[i]` and `arr[j]`, then `j++`.
   `j` always points at the leftmost zero; `i` scans for the next non-zero to pull forward.

**Dry run ([1, 0, 2, 3, 2, 0, 0, 4, 5, 1]):** j = 1. i = 2 (2): swap → [1, 2, 0, 3, …], j = 2; i = 3 (3): swap, j = 3; i = 4 (2): swap, j = 4; i = 5, 6 are zeros → skip; i = 7 (4): swap with index 4, j = 5; i = 8 (5): j = 6; i = 9 (1): j = 7 → [1, 2, 3, 2, 4, 5, 1, 0, 0, 0].

**Complexity:** Time O(x) + O(n − x) = O(n). Extra space O(1).

**C++**
```cpp
void moveZeroes(vector<int>& arr) {
    int n = arr.size(), j = -1;
    for (int i = 0; i < n; i++)
        if (arr[i] == 0) { j = i; break; }
    if (j == -1) return;
    for (int i = j + 1; i < n; i++) {
        if (arr[i] != 0) {
            swap(arr[i], arr[j]);
            j++;
        }
    }
}
```

**Java**
```java
class Solution {
    public void moveZeroes(int[] arr) {
        int n = arr.length, j = -1;
        for (int i = 0; i < n; i++)
            if (arr[i] == 0) { j = i; break; }
        if (j == -1) return;
        for (int i = j + 1; i < n; i++) {
            if (arr[i] != 0) {
                int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
                j++;
            }
        }
    }
}
```

#### Key Takeaways
- Two pointers — one marks the "slot" (first zero), one scans — partition an array in place while preserving order.

[↑ Contents](#contents) · [← Previous](#p73) · [Next →](#p75)

---

<a id="p75"></a>

### 8. Remove duplicates from sorted array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Logic Building | Basic | No | [LeetCode](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/remove-duplicates-from-a-sorted-array-in-place) | [Watch from 31:27](https://youtu.be/37E9ckMDdTk?t=1887) |

#### Problem Statement
Given a **sorted** array, remove duplicates **in place** so that the first `k` positions hold the `k` unique elements in order; return `k`. What remains after index `k − 1` doesn't matter (LeetCode 26).

```text
[1, 1, 2, 2, 2, 3, 3] -> k = 3, array starts with [1, 2, 3, ...]
```

#### Approach 1: Brute force — set
Insert every element into a `set` (unique + ordered), then write the set back into the array from index 0; `k` = set size.
(C++: use `set`, not `unordered_set`, so the order is kept.)

**Complexity:** Time O(n log n) for insertions + O(n) to copy back. Extra space O(n) (all elements unique).

**C++**
```cpp
int removeDuplicatesBrute(vector<int>& arr) {
    set<int> st(arr.begin(), arr.end());
    int index = 0;
    for (int x : st) arr[index++] = x;
    return index;
}
```

**Java**
```java
class Solution {
    static int removeDuplicatesBrute(int[] arr) {
        TreeSet<Integer> st = new TreeSet<>();
        for (int x : arr) st.add(x);
        int index = 0;
        for (int x : st) arr[index++] = x;
        return index;
    }
}
```

#### Approach 2: Optimal — two pointers
Because the array is sorted, equal elements are adjacent. Keep `i` at the last unique element placed (start `i = 0`; the first element is always unique). Scan with `j = 1..n−1`: when `arr[j] != arr[i]`, it is a new unique element → place it right after `i`: `arr[i + 1] = arr[j]`, `i++`. Return `i + 1`.

**Dry run:** i = 0 (1). j = 1: 1 == 1 skip. j = 2: 2 ≠ 1 → arr[1] = 2, i = 1. j = 3, 4: 2 skip. j = 5: 3 ≠ 2 → arr[2] = 3, i = 2. j = 6: skip → return 3.

**Complexity:** Time O(n), Extra space O(1).

**C++**
```cpp
int removeDuplicates(vector<int>& arr) {
    if (arr.empty()) return 0;
    int i = 0;
    for (int j = 1; j < (int)arr.size(); j++) {
        if (arr[j] != arr[i]) {
            arr[i + 1] = arr[j];
            i++;
        }
    }
    return i + 1;
}
```

**Java**
```java
class Solution {
    public int removeDuplicates(int[] arr) {
        if (arr.length == 0) return 0;
        int i = 0;
        for (int j = 1; j < arr.length; j++) {
            if (arr[j] != arr[i]) {
                arr[i + 1] = arr[j];
                i++;
            }
        }
        return i + 1;
    }
}
```

#### Key Takeaways
- "Unique elements" suggests a set (brute force); "sorted + in place" suggests two pointers (optimal).

[↑ Contents](#contents) · [← Previous](#p74) · [Next →](#p76)

---

<a id="p76"></a>

### 9. Find missing number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Logic Building | Basic | No | [LeetCode](https://leetcode.com/problems/missing-number/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/missing-number-solutions) | [Watch from 0:50](https://youtu.be/bYWLJb3vCWY?t=50) |

#### Problem Statement
Given `n` and an array of `n − 1` distinct numbers from `1..n`, find the missing number. (LeetCode 268 uses `0..n` with `n` numbers; the same ideas apply.)

```text
n = 5, arr = [1, 2, 4, 5] -> 3
```
> The sheet doesn't attach a video to this problem, but it is covered at the start of the "Arrays Part 3" lecture, which these notes follow.

#### Approach 1: Brute force — linear search for each candidate
For each `i` in `1..n`, scan the array for `i`; the first `i` not found is the answer.

**Complexity:** Time O(n²) in the worst case, Space O(1).

**C++**
```cpp
int missingBrute(vector<int>& arr, int n) {
    for (int i = 1; i <= n; i++) {
        bool found = false;
        for (int x : arr) if (x == i) { found = true; break; }
        if (!found) return i;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int missingBrute(int[] arr, int n) {
        for (int i = 1; i <= n; i++) {
            boolean found = false;
            for (int x : arr) if (x == i) { found = true; break; }
            if (!found) return i;
        }
        return -1;
    }
}
```

#### Approach 2: Better — hashing
Mark each present value in a hash array of size `n + 1`, then return the index in `1..n` still marked 0.

**Complexity:** Time O(2n), Space O(n).

**C++**
```cpp
int missingHash(vector<int>& arr, int n) {
    vector<int> hash(n + 1, 0);
    for (int x : arr) hash[x] = 1;
    for (int i = 1; i <= n; i++) if (hash[i] == 0) return i;
    return -1;
}
```

**Java**
```java
class Solution {
    static int missingHash(int[] arr, int n) {
        int[] hash = new int[n + 1];
        for (int x : arr) hash[x] = 1;
        for (int i = 1; i <= n; i++) if (hash[i] == 0) return i;
        return -1;
    }
}
```

#### Approach 3: Optimal 1 — sum formula
`1 + 2 + … + n = n(n + 1)/2`. Subtract the sum of the array; the difference is the missing number. (15 − 12 = 3 in the example.)

**Complexity:** Time O(n), Space O(1). The sum is about n²/2 — for n = 10⁵ that is ~5·10⁹, which overflows `int`, so use `long`.

**C++**
```cpp
int missingSum(vector<int>& arr, int n) {
    long long sum = 1LL * n * (n + 1) / 2, s2 = 0;
    for (int x : arr) s2 += x;
    return (int)(sum - s2);
}
```

**Java**
```java
class Solution {
    static int missingSum(int[] arr, int n) {
        long sum = (long) n * (n + 1) / 2, s2 = 0;
        for (int x : arr) s2 += x;
        return (int) (sum - s2);
    }
}
```

#### Approach 4: Optimal 2 — XOR
XOR facts: `a ^ a = 0`, `a ^ 0 = a`. XOR all numbers `1..n` together with all array elements — every present number appears twice and cancels, leaving the missing one. Do it in one loop: for `i = 0..n−2`, `xor1 ^= (i + 1)` and `xor2 ^= arr[i]`; finally `xor1 ^= n`.

**Why it's slightly better than the sum:** XOR never exceeds the largest number, so plain `int` suffices — no overflow concerns.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
int missingXor(vector<int>& arr, int n) {
    int xor1 = 0, xor2 = 0;
    for (int i = 0; i < n - 1; i++) {
        xor2 ^= arr[i];
        xor1 ^= (i + 1);
    }
    xor1 ^= n;
    return xor1 ^ xor2;
}
```

**Java**
```java
class Solution {
    static int missingXor(int[] arr, int n) {
        int xor1 = 0, xor2 = 0;
        for (int i = 0; i < n - 1; i++) {
            xor2 ^= arr[i];
            xor1 ^= (i + 1);
        }
        xor1 ^= n;
        return xor1 ^ xor2;
    }
}
```

#### Key Takeaways
- Walk the interviewer through brute → hashing → sum → XOR, and explain why XOR avoids overflow.

[↑ Contents](#contents) · [← Previous](#p75) · [Next →](#p77)

---

<a id="p77"></a>

### 10. Union of two sorted arrays

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Logic Building | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/union-of-two-sorted-arrays) | [Watch from 43:04](https://youtu.be/wvcQg43_V8U?t=2584) |

#### Problem Statement
Return the **union** of two sorted arrays (which may contain duplicates): all distinct elements present in either array, in sorted order.

```text
a = [1, 1, 2, 3, 4, 5], b = [2, 3, 4, 4, 5, 6] -> [1, 2, 3, 4, 5, 6]
```

#### Approach 1: Brute force — ordered set
Insert all elements of both arrays into a `set` (C++ `set`, Java `TreeSet` — not the unordered versions, which lose the order), then copy the set into the result.

**Complexity:** Time O(n1 log n + n2 log n) for insertions (n = set size) + O(n1 + n2) to copy. Space O(n1 + n2) for the set, plus O(n1 + n2) for the answer (that one is for *returning* the answer, not for solving — say so in interviews).

**C++**
```cpp
vector<int> unionBrute(vector<int>& a, vector<int>& b) {
    set<int> st;
    for (int x : a) st.insert(x);
    for (int x : b) st.insert(x);
    return vector<int>(st.begin(), st.end());
}
```

**Java**
```java
class Solution {
    static List<Integer> unionBrute(int[] a, int[] b) {
        TreeSet<Integer> st = new TreeSet<>();
        for (int x : a) st.add(x);
        for (int x : b) st.add(x);
        return new ArrayList<>(st);
    }
}
```

#### Approach 2: Optimal — two pointers (merge-like)
Pointers `i` on `a`, `j` on `b`. The next union element is the smaller of `a[i]`, `b[j]`. Append it only if the result is empty or its last element differs (that removes duplicates), then advance that pointer. When one array is exhausted, process the rest of the other with the same "differs from last" check.

**Dry run:** 1 (from a) → 1 again: same as last, skip → 2 (a) → 2 (b) skip → 3 → 3 skip → 4 → 4, 4 skip → 5 → 5 skip → a exhausted → 6 from b → [1, 2, 3, 4, 5, 6].

**Complexity:** Time O(n1 + n2) (every element is visited once). Space O(n1 + n2) only for the returned answer.

**C++**
```cpp
vector<int> findUnion(vector<int>& a, vector<int>& b) {
    int n1 = a.size(), n2 = b.size(), i = 0, j = 0;
    vector<int> uni;
    while (i < n1 && j < n2) {
        if (a[i] <= b[j]) {
            if (uni.empty() || uni.back() != a[i]) uni.push_back(a[i]);
            i++;
        } else {
            if (uni.empty() || uni.back() != b[j]) uni.push_back(b[j]);
            j++;
        }
    }
    while (j < n2) {
        if (uni.empty() || uni.back() != b[j]) uni.push_back(b[j]);
        j++;
    }
    while (i < n1) {
        if (uni.empty() || uni.back() != a[i]) uni.push_back(a[i]);
        i++;
    }
    return uni;
}
```

**Java**
```java
class Solution {
    static List<Integer> findUnion(int[] a, int[] b) {
        int n1 = a.length, n2 = b.length, i = 0, j = 0;
        List<Integer> uni = new ArrayList<>();
        while (i < n1 && j < n2) {
            if (a[i] <= b[j]) {
                if (uni.isEmpty() || uni.get(uni.size() - 1) != a[i]) uni.add(a[i]);
                i++;
            } else {
                if (uni.isEmpty() || uni.get(uni.size() - 1) != b[j]) uni.add(b[j]);
                j++;
            }
        }
        while (j < n2) {
            if (uni.isEmpty() || uni.get(uni.size() - 1) != b[j]) uni.add(b[j]);
            j++;
        }
        while (i < n1) {
            if (uni.isEmpty() || uni.get(uni.size() - 1) != a[i]) uni.add(a[i]);
            i++;
        }
        return uni;
    }
}
```
(Java note: `uni.get(...) != a[i]` compares an `Integer` with an `int`, which unboxes — safe. Comparing two `Integer` objects with `!=` would not be.)

#### Key Takeaways
- Sorted inputs → two pointers can replace a set and give linear time.

[↑ Contents](#contents) · [← Previous](#p76) · [Next →](#p78)

---

<a id="p78"></a>

### 11. Intersection of two sorted arrays

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › Logic Building | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/intersection-of-two-arrays) | [Watch from 58:30](https://youtu.be/wvcQg43_V8U?t=3510) |

#### Problem Statement
Return the **intersection** of two sorted arrays: elements present in both, **including repeats** as many times as they match (each element can pair with only one partner).

```text
a = [1, 2, 2, 3, 3, 4, 5, 6], b = [2, 3, 3, 5, 6, 6, 7] -> [2, 3, 3, 5, 6]
```
> The sheet doesn't attach a video here, but intersection is taught right after Union in the same lecture (from ~58:30), which these notes follow.

#### Approach 1: Brute force — visited array
For each `a[i]`, scan `b` for an equal element that hasn't been used yet (`vis[j] == 0`); when found, add it, mark `vis[j] = 1`, and break. Because `b` is sorted, stop scanning once `b[j] > a[i]`.

**Complexity:** Time O(n1 × n2) worst case, Space O(n2) for `vis` (put the visited array on the smaller array to minimise space).

**C++**
```cpp
vector<int> intersectionBrute(vector<int>& a, vector<int>& b) {
    int n1 = a.size(), n2 = b.size();
    vector<int> ans, vis(n2, 0);
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (a[i] == b[j] && vis[j] == 0) {
                ans.push_back(a[i]);
                vis[j] = 1;
                break;
            }
            if (b[j] > a[i]) break;
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> intersectionBrute(int[] a, int[] b) {
        int n1 = a.length, n2 = b.length;
        List<Integer> ans = new ArrayList<>();
        int[] vis = new int[n2];
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                if (a[i] == b[j] && vis[j] == 0) {
                    ans.add(a[i]);
                    vis[j] = 1;
                    break;
                }
                if (b[j] > a[i]) break;
            }
        }
        return ans;
    }
}
```

#### Approach 2: Optimal — two pointers
- `a[i] < b[j]` → `a[i]` can't have a partner (everything ahead in `b` is larger) → `i++`.
- `b[j] < a[i]` → `j++`.
- Equal → they "pair up": add the value, move **both** pointers.
Stop when either array runs out.

**Complexity:** Time O(n1 + n2), Extra space O(1) (besides the answer).

**C++**
```cpp
vector<int> findIntersection(vector<int>& a, vector<int>& b) {
    int n1 = a.size(), n2 = b.size(), i = 0, j = 0;
    vector<int> ans;
    while (i < n1 && j < n2) {
        if (a[i] < b[j]) i++;
        else if (b[j] < a[i]) j++;
        else { ans.push_back(a[i]); i++; j++; }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> findIntersection(int[] a, int[] b) {
        int n1 = a.length, n2 = b.length, i = 0, j = 0;
        List<Integer> ans = new ArrayList<>();
        while (i < n1 && j < n2) {
            if (a[i] < b[j]) i++;
            else if (b[j] < a[i]) j++;
            else { ans.add(a[i]); i++; j++; }
        }
        return ans;
    }
}
```

#### Key Takeaways
- Union keeps everything once; intersection keeps only matched pairs — both are two-pointer merges on sorted arrays.

[↑ Contents](#contents) · [← Previous](#p77) · [Next →](#p79)

---

## FAQs(Medium)

<a id="p79"></a>

### 12. Majority Element-I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/majority-element/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/majority-element-n-by-2) | [Watch](https://youtu.be/nP_ns3uSh80) |

#### Problem Statement
Return the element that appears **more than ⌊n/2⌋ times** (strictly more — not equal) (LeetCode 169).

```text
[2, 2, 3, 3, 1, 2, 2] -> 2   (n = 7, 2 appears 4 > 3 times)
```

#### Approach 1: Brute force — count every element
For each `arr[i]`, count its occurrences with a nested loop; return it as soon as the count exceeds n/2. Return −1 if none.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
int majorityBrute(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) if (v[j] == v[i]) cnt++;
        if (cnt > n / 2) return v[i];
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int majorityBrute(int[] v) {
        int n = v.length;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) if (v[j] == v[i]) cnt++;
            if (cnt > n / 2) return v[i];
        }
        return -1;
    }
}
```

#### Approach 2: Better — hashing
Count frequencies in a map (element → count), then return the key whose count exceeds n/2.

**Complexity:** Time O(n log n) with an ordered map (O(n) average with `unordered_map`, but O(n²) in its worst case) + O(n) to scan the map. Space O(n) (all elements distinct).

**C++**
```cpp
int majorityHash(vector<int>& v) {
    map<int, int> mpp;
    for (int x : v) mpp[x]++;
    for (auto& it : mpp)
        if (it.second > (int)v.size() / 2) return it.first;
    return -1;
}
```

**Java**
```java
class Solution {
    static int majorityHash(int[] v) {
        Map<Integer, Integer> mpp = new HashMap<>();
        for (int x : v) mpp.merge(x, 1, Integer::sum);
        for (Map.Entry<Integer, Integer> e : mpp.entrySet())
            if (e.getValue() > v.length / 2) return e.getKey();
        return -1;
    }
}
```

#### Approach 3: Optimal — Moore's Voting Algorithm
You can't invent this in an interview — but you must explain its **intuition**, not just recite it.

Keep `el` (current candidate) and `cnt`:
- if `cnt == 0`: start a new section — `el = arr[i]`, `cnt = 1`;
- else if `arr[i] == el`: `cnt++`;
- else: `cnt--`.

**Intuition:** `cnt` is not the frequency of `el`. When it drops to 0 at some index, the prefix so far contains `el` exactly as many times as *other* elements — so `el` cannot be the majority **of that prefix**, and we discard the prefix and start afresh. A true majority element (more than half of all elements) can never be fully cancelled out, so it survives as the final `el`.

**Dry run ([7, 7, 5, 7, 5, 1, 5, 7, 5, 5, 7, 7, 5, 5, 5, 5]):** sections [7 7 5 7 5 1] (cnt → 0), [5 7] (→ 0), [5 5 7 7] (→ 0), then 5 survives with cnt 4 → candidate 5.

**Step 2 — verify:** if the problem doesn't guarantee a majority exists, count `el` once more and check `> n/2` (in the example 5 appears 9 > 8 times). If a majority is guaranteed (as on LeetCode), skip this pass.

**Complexity:** Time O(n) (+ O(n) for verification), Space O(1).

**C++**
```cpp
int majorityElement(vector<int>& v) {
    int cnt = 0, el = 0, n = v.size();
    for (int i = 0; i < n; i++) {
        if (cnt == 0) { cnt = 1; el = v[i]; }
        else if (v[i] == el) cnt++;
        else cnt--;
    }
    int cnt1 = 0;
    for (int x : v) if (x == el) cnt1++;
    return cnt1 > n / 2 ? el : -1;
}
```

**Java**
```java
class Solution {
    public int majorityElement(int[] v) {
        int cnt = 0, el = 0, n = v.length;
        for (int i = 0; i < n; i++) {
            if (cnt == 0) { cnt = 1; el = v[i]; }
            else if (v[i] == el) cnt++;
            else cnt--;
        }
        int cnt1 = 0;
        for (int x : v) if (x == el) cnt1++;
        return cnt1 > n / 2 ? el : -1;
    }
}
```

#### Key Takeaways
- Moore's voting = pairwise cancellation. Explain "cnt reaching 0 discards a prefix where the candidate isn't a majority".

[↑ Contents](#contents) · [← Previous](#p78) · [Next →](#p80)

---

<a id="p80"></a>

### 13. Leaders in an Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | Yes | [LeetCode](https://leetcode.com/problems/buildings-with-an-ocean-view/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/leaders-in-an-array) | [Watch](https://youtu.be/cHrH9CQ8pmY) |

#### Problem Statement
An element is a **leader** if it is **greater than every element to its right**. The last element is always a leader. Return all leaders (the required order depends on the platform: array order, or sorted).

```text
[10, 22, 12, 3, 0, 6] -> leaders 22, 12, 6
```

#### Approach 1: Brute force
For each `i`, scan `j = i+1..n−1`; if any `arr[j] > arr[i]`, `arr[i]` is not a leader.

**Complexity:** Time ≈ O(n²), Space O(1) to solve (O(n) worst case to *return* the answer, e.g. [5, 4, 3, 2, 1] where everyone is a leader — tell the interviewer this explicitly).

**C++**
```cpp
vector<int> leadersBrute(vector<int>& arr) {
    vector<int> ans;
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        bool leader = true;
        for (int j = i + 1; j < n; j++)
            if (arr[j] > arr[i]) { leader = false; break; }
        if (leader) ans.push_back(arr[i]);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> leadersBrute(int[] arr) {
        List<Integer> ans = new ArrayList<>();
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            boolean leader = true;
            for (int j = i + 1; j < n; j++)
                if (arr[j] > arr[i]) { leader = false; break; }
            if (leader) ans.add(arr[i]);
        }
        return ans;
    }
}
```

#### Approach 2: Optimal — scan from the right with a running maximum
If `arr[i]` is greater than the **maximum of everything to its right**, it is greater than all of them. Traverse right-to-left keeping `maxi` (initially `INT_MIN`):
- if `arr[i] > maxi` → leader;
- then `maxi = max(maxi, arr[i])`.

Leaders are collected in reverse order (6, 12, 22): **reverse** the list for array order, or **sort** it if the platform wants sorted output (O(n log n) worst case).

**Dry run:** 6 > −∞ → leader, max 6; 0 no; 3 no; 12 > 6 → leader, max 12; 22 > 12 → leader, max 22; 10 no.

**Complexity:** Time O(n) (+ O(n) reverse or O(n log n) sort). Extra space O(1) beyond the answer.

**C++**
```cpp
vector<int> leaders(vector<int>& arr) {
    vector<int> ans;
    int maxi = INT_MIN;
    for (int i = (int)arr.size() - 1; i >= 0; i--) {
        if (arr[i] > maxi) ans.push_back(arr[i]);
        maxi = max(maxi, arr[i]);
    }
    reverse(ans.begin(), ans.end());   // array order; use sort() if sorted output is required
    return ans;
}
```

**Java**
```java
class Solution {
    static List<Integer> leaders(int[] arr) {
        List<Integer> ans = new ArrayList<>();
        int maxi = Integer.MIN_VALUE;
        for (int i = arr.length - 1; i >= 0; i--) {
            if (arr[i] > maxi) ans.add(arr[i]);
            maxi = Math.max(maxi, arr[i]);
        }
        Collections.reverse(ans);
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- "Greater" vs "greater than or equal": some platforms count equal elements as leaders (use `>=`). LeetCode 1762 (Buildings With an Ocean View, linked) returns **indices** with strictly greater-to-the-right logic.

#### Key Takeaways
- "Compare with everything on the right" → maintain a suffix maximum while scanning from the right.

[↑ Contents](#contents) · [← Previous](#p79) · [Next →](#p81)

---

<a id="p81"></a>

### 14. Rearrange array elements by sign

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/rearrange-array-elements-by-sign/) | [Watch](https://youtu.be/h4aBagy4Uok) |

#### Problem Statement
**Variety 1 (LeetCode 2149):** the array has equal numbers of positives and negatives. Rearrange so that signs alternate, starting with a positive, keeping the relative order of positives and of negatives.

```text
[3, 1, -2, -5, 2, -4] -> [3, -2, 1, -5, 2, -4]
```
**Variety 2:** the counts may differ; alternate as long as possible, then append the leftover elements in their original order.

```text
[1, 2, -4, -5, 3, 4] -> [1, -4, 2, -5, 3, 4]
```

#### Approach 1 (Variety 1): Brute force — split, then interleave
Collect positives and negatives into two lists (order preserved). Positives go to even indices, negatives to odd: `arr[2i] = pos[i]`, `arr[2i + 1] = neg[i]` for `i < n/2`.

**Complexity:** Time O(n + n/2), Space O(n).

**C++**
```cpp
vector<int> rearrangeBrute(vector<int> arr) {
    vector<int> pos, neg;
    for (int x : arr) (x > 0 ? pos : neg).push_back(x);
    for (int i = 0; i < (int)arr.size() / 2; i++) {
        arr[2 * i] = pos[i];
        arr[2 * i + 1] = neg[i];
    }
    return arr;
}
```

**Java**
```java
class Solution {
    static int[] rearrangeBrute(int[] arr) {
        List<Integer> pos = new ArrayList<>(), neg = new ArrayList<>();
        for (int x : arr) { if (x > 0) pos.add(x); else neg.add(x); }
        int[] res = arr.clone();
        for (int i = 0; i < arr.length / 2; i++) {
            res[2 * i] = pos.get(i);
            res[2 * i + 1] = neg.get(i);
        }
        return res;
    }
}
```

#### Approach 2 (Variety 1): Optimal — one pass with two write indices
Answer array of size `n`; `posIndex = 0`, `negIndex = 1`. For each element: a positive goes to `ans[posIndex]` (`posIndex += 2`), a negative to `ans[negIndex]` (`negIndex += 2`).

**Complexity:** Time O(n) (one pass), Space O(n) for the answer. Only a small improvement over the brute force, but it's a single pass.

**C++**
```cpp
vector<int> rearrangeArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    int posIndex = 0, negIndex = 1;
    for (int x : nums) {
        if (x < 0) { ans[negIndex] = x; negIndex += 2; }
        else { ans[posIndex] = x; posIndex += 2; }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    public int[] rearrangeArray(int[] nums) {
        int n = nums.length;
        int[] ans = new int[n];
        int posIndex = 0, negIndex = 1;
        for (int x : nums) {
            if (x < 0) { ans[negIndex] = x; negIndex += 2; }
            else { ans[posIndex] = x; posIndex += 2; }
        }
        return ans;
    }
}
```

#### Approach 3 (Variety 2): Fall back to the brute force
The optimal trick relies on equal counts, so go back to the split approach — the video stresses that falling back confidently is the right move:
1. Split into `pos` and `neg`.
2. Interleave the first `min(|pos|, |neg|)` pairs at indices `2i` and `2i + 1`.
3. Append the leftovers of the longer list starting at index `2 × min`.

**Complexity:** Time O(n) + O(min) + O(leftovers) — overall O(2n) in the worst case (e.g. all positives). Space O(n).

**C++**
```cpp
vector<int> alternateNumbers(vector<int>& a) {
    vector<int> pos, neg;
    for (int x : a) (x > 0 ? pos : neg).push_back(x);
    int p = pos.size(), q = neg.size();
    if (p > q) {
        for (int i = 0; i < q; i++) { a[2 * i] = pos[i]; a[2 * i + 1] = neg[i]; }
        int index = 2 * q;
        for (int i = q; i < p; i++) a[index++] = pos[i];
    } else {
        for (int i = 0; i < p; i++) { a[2 * i] = pos[i]; a[2 * i + 1] = neg[i]; }
        int index = 2 * p;
        for (int i = p; i < q; i++) a[index++] = neg[i];
    }
    return a;
}
```

**Java**
```java
class Solution {
    static int[] alternateNumbers(int[] a) {
        List<Integer> pos = new ArrayList<>(), neg = new ArrayList<>();
        for (int x : a) { if (x > 0) pos.add(x); else neg.add(x); }
        int p = pos.size(), q = neg.size();
        if (p > q) {
            for (int i = 0; i < q; i++) { a[2 * i] = pos.get(i); a[2 * i + 1] = neg.get(i); }
            int index = 2 * q;
            for (int i = q; i < p; i++) a[index++] = pos.get(i);
        } else {
            for (int i = 0; i < p; i++) { a[2 * i] = pos.get(i); a[2 * i + 1] = neg.get(i); }
            int index = 2 * p;
            for (int i = p; i < q; i++) a[index++] = neg.get(i);
        }
        return a;
    }
}
```

#### Key Takeaways
- Index patterns (even/odd slots) turn interleaving into direct placement.
- When a follow-up breaks the optimal solution's assumption, falling back to the simpler approach is a strength, not a weakness.

[↑ Contents](#contents) · [← Previous](#p80) · [Next →](#p82)

---

<a id="p82"></a>

### 15. Print the matrix in spiral manner

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/spiral-matrix/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/spiral-traversal-of-a-matrix) | [Watch](https://youtu.be/3Zv-s9UUrFM) |

#### Problem Statement
Return all elements of an `n × m` matrix in **spiral order** (LeetCode 54).

```text
1  2  3  4
5  6  7  8        -> 1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10
9  10 11 12
13 14 15 16
```

#### Why it's asked (from the video)
There is only one approach (it is already optimal). The interviewer is testing **implementation skill** and **clean code**.

#### Intuition
Print layer by layer: **right → bottom → left → top**, then move inward. Keep four boundaries:
`top = 0`, `bottom = n − 1`, `left = 0`, `right = m − 1`.

1. **Right:** row `top`, columns `left..right`; then `top++`.
2. **Bottom (down):** column `right`, rows `top..bottom`; then `right--`.
3. **Left:** row `bottom`, columns `right..left`; then `bottom--` — only **if `top <= bottom`** (a row still remains).
4. **Top (up):** column `left`, rows `bottom..top`; then `left++` — only **if `left <= right`** (a column still remains).

Repeat while `top <= bottom && left <= right`.

**Why the two extra checks:** with a single remaining row, step 1 prints it and `top` passes `bottom`; without the check, step 3 would print the same row again backwards. Likewise for a single remaining column in step 4. Steps 1 and 2 don't need checks: the `while` condition and the `for` bounds already cover them.

**Complexity:** Time O(n × m) — every cell is printed exactly once. Space O(n × m) for the answer list (only used for returning).

**C++**
```cpp
vector<int> spiralOrder(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    int left = 0, right = m - 1, top = 0, bottom = n - 1;
    vector<int> ans;
    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) ans.push_back(mat[top][i]);
        top++;
        for (int i = top; i <= bottom; i++) ans.push_back(mat[i][right]);
        right--;
        if (top <= bottom) {
            for (int i = right; i >= left; i--) ans.push_back(mat[bottom][i]);
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--) ans.push_back(mat[i][left]);
            left++;
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    public List<Integer> spiralOrder(int[][] mat) {
        int n = mat.length, m = mat[0].length;
        int left = 0, right = m - 1, top = 0, bottom = n - 1;
        List<Integer> ans = new ArrayList<>();
        while (top <= bottom && left <= right) {
            for (int i = left; i <= right; i++) ans.add(mat[top][i]);
            top++;
            for (int i = top; i <= bottom; i++) ans.add(mat[i][right]);
            right--;
            if (top <= bottom) {
                for (int i = right; i >= left; i--) ans.add(mat[bottom][i]);
                bottom--;
            }
            if (left <= right) {
                for (int i = bottom; i >= top; i--) ans.add(mat[i][left]);
                left++;
            }
        }
        return ans;
    }
}
```

#### Key Takeaways
- Boundary-shrinking with four pointers is the standard pattern for spiral/layer traversal.
- `n = mat.size()` (number of rows), `m = mat[0].size()` (number of columns).

[↑ Contents](#contents) · [← Previous](#p81) · [Next →](#p83)

---

<a id="p83"></a>

### 16. Pascal's Triangle I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/pascals-triangle/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/pascals-triangle-first-n-rows) | [Watch](https://youtu.be/bR7mQgwQ_o8) |

#### Problem Statement
Pascal's triangle: each row starts and ends with 1, and every inner element is the sum of the two elements above it.

```text
row 1:         1
row 2:        1 1
row 3:       1 2 1
row 4:      1 3 3 1
row 5:     1 4 6 4 1
row 6:   1 5 10 10 5 1
```
The video covers three interview variants:
1. **Type 1 (this problem):** given row `r` and column `c` (1-indexed), return the element. e.g. r = 5, c = 3 → **6**.
2. Type 2: print the n-th row → see *Pascal's Triangle II*.
3. Type 3: print the first n rows → see *Pascal's Triangle III* (this is what LeetCode 118, linked on the sheet, asks).

#### Approach 1: Generate the triangle *(brute force)*
Build all rows up to `r` and read the value — O(r²). Wasteful when only one element is needed.

#### Approach 2: Optimal — the combination formula
The element at row `r`, column `c` is **C(r − 1, c − 1)** (n choose k). Example: r = 5, c = 3 → C(4, 2) = 4!/(2!·2!) = 6.

Computing three factorials is O(n) and overflows quickly. Shortcut: C(n, r) = [n·(n−1)·…·(n−r+1)] / [1·2·…·r], i.e. r terms on top and r on the bottom (C(10, 3) = 10·9·8 / 1·2·3). Compute it incrementally:
`res = res * (n − i) / (i + 1)` for `i = 0..r−1`. After every step `res` is itself a binomial coefficient, so the division is always exact. Use 64-bit integers.

**Complexity:** Time O(c), Space O(1).

**C++**
```cpp
long long nCr(int n, int r) {
    long long res = 1;
    for (int i = 0; i < r; i++) {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return res;
}
long long pascalElement(int r, int c) {
    return nCr(r - 1, c - 1);
}
```

**Java**
```java
class Solution {
    static long nCr(int n, int r) {
        long res = 1;
        for (int i = 0; i < r; i++) {
            res = res * (n - i);
            res = res / (i + 1);
        }
        return res;
    }
    static long pascalElement(int r, int c) {
        return nCr(r - 1, c - 1);
    }
}
```

#### Edge Cases & Pitfalls
- Multiply **before** dividing at each step (`res * (n − i) / (i + 1)`), never divide first.
- Use `C(n, r) = C(n, n − r)` to loop over the smaller of `r` and `n − r` *(not in video)*.

#### Key Takeaways
- Element of Pascal's triangle = binomial coefficient; compute nCr in O(r) without factorials.

[↑ Contents](#contents) · [← Previous](#p82) · [Next →](#p84)

---

<a id="p84"></a>

### 17. Pascal's Triangle II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/pascals-triangle-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/pascal-triangle-ii) | [Watch from 10:40](https://youtu.be/bR7mQgwQ_o8?t=640) |

#### Problem Statement
Return the **n-th row** of Pascal's triangle (1-indexed). (LeetCode 119 uses a 0-indexed `rowIndex`.)

```text
n = 6 -> [1, 5, 10, 10, 5, 1]
```
> The sheet links no video to this problem; the Pascal's-triangle lecture covers it as "Type 2" (from ~10:40).

#### Approach 1: Brute force — nCr for every column
Row `n` has `n` elements; element `c` is `C(n − 1, c − 1)`. Calling the O(c) nCr function for every column costs O(n · r).

**Complexity:** Time ≈ O(n²), Space O(1) extra.

**C++**
```cpp
long long nCr(int n, int r) {
    long long res = 1;
    for (int i = 0; i < r; i++) { res = res * (n - i); res = res / (i + 1); }
    return res;
}
vector<long long> pascalRowBrute(int n) {
    vector<long long> row;
    for (int c = 1; c <= n; c++) row.push_back(nCr(n - 1, c - 1));
    return row;
}
```

**Java**
```java
class Solution {
    static long nCr(int n, int r) {
        long res = 1;
        for (int i = 0; i < r; i++) { res = res * (n - i); res = res / (i + 1); }
        return res;
    }
    static List<Long> pascalRowBrute(int n) {
        List<Long> row = new ArrayList<>();
        for (int c = 1; c <= n; c++) row.add(nCr(n - 1, c - 1));
        return row;
    }
}
```

#### Approach 2: Optimal — build each element from the previous one
Look at row 6 with 0-based columns: `1, 5/1, 5·4/(1·2), 5·4·3/(1·2·3), …`. Each element = previous element × `(n − col)` / `col`:
- col 1: 1 × 5/1 = 5
- col 2: 5 × 4/2 = 10
- col 3: 10 × 3/3 = 10
- col 4: 10 × 2/4 = 5
- col 5: 5 × 1/5 = 1

So: `ans = 1`; output it; for `col = 1..n−1`: `ans = ans * (n − col) / col`; output.

**Complexity:** Time O(n), Space O(1) extra.

**C++**
```cpp
vector<long long> generateRow(int row) {
    long long ans = 1;
    vector<long long> ansRow;
    ansRow.push_back(1);
    for (int col = 1; col < row; col++) {
        ans = ans * (row - col);
        ans = ans / col;
        ansRow.push_back(ans);
    }
    return ansRow;
}
```

**Java**
```java
class Solution {
    static List<Long> generateRow(int row) {
        long ans = 1;
        List<Long> ansRow = new ArrayList<>();
        ansRow.add(1L);
        for (int col = 1; col < row; col++) {
            ans = ans * (row - col);
            ans = ans / col;
            ansRow.add(ans);
        }
        return ansRow;
    }
}
```

**LeetCode 119 adaptation:** `getRow(rowIndex)` = `generateRow(rowIndex + 1)` (convert to `int` if required).

#### Key Takeaways
- Neighbouring binomial coefficients differ by a simple ratio; use it to generate a row in O(n).

[↑ Contents](#contents) · [← Previous](#p83) · [Next →](#p85)

---

<a id="p85"></a>

### 18. Pascal's Triangle III

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/pascals-triangle-first-n-rows) | [Watch from 19:20](https://youtu.be/bR7mQgwQ_o8?t=1160) |

#### Problem Statement
Return the first `n` rows of Pascal's triangle as a list of lists (LeetCode 118).

```text
n = 5 -> [[1], [1,1], [1,2,1], [1,3,3,1], [1,4,6,4,1]]
```
> The sheet links no video here; this is "Type 3" in the Pascal's-triangle lecture (from ~19:20).

#### Approach 1: Brute force — nCr for every cell
For each row `r = 1..n` and column `c = 1..r`, compute `C(r − 1, c − 1)` with the O(c) function.

**Complexity:** ≈ O(n³). Space: only the output.

**C++**
```cpp
long long nCr(int n, int r) {
    long long res = 1;
    for (int i = 0; i < r; i++) { res = res * (n - i); res = res / (i + 1); }
    return res;
}
vector<vector<long long>> pascalBrute(int n) {
    vector<vector<long long>> ans;
    for (int r = 1; r <= n; r++) {
        vector<long long> temp;
        for (int c = 1; c <= r; c++) temp.push_back(nCr(r - 1, c - 1));
        ans.push_back(temp);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static long nCr(int n, int r) {
        long res = 1;
        for (int i = 0; i < r; i++) { res = res * (n - i); res = res / (i + 1); }
        return res;
    }
    static List<List<Long>> pascalBrute(int n) {
        List<List<Long>> ans = new ArrayList<>();
        for (int r = 1; r <= n; r++) {
            List<Long> temp = new ArrayList<>();
            for (int c = 1; c <= r; c++) temp.add(nCr(r - 1, c - 1));
            ans.add(temp);
        }
        return ans;
    }
}
```

#### Approach 2: Optimal — generate each row in O(row) (reuse Type 2)
Call the O(n) `generateRow` for every row 1..n. The video stresses **code quality**: keep row generation in its own readable function instead of inlining everything.

**Complexity:** Time O(n²) (total cells), Space O(1) extra besides the answer.

**C++**
```cpp
vector<int> generateRow(int row) {
    long long ans = 1;
    vector<int> ansRow;
    ansRow.push_back(1);
    for (int col = 1; col < row; col++) {
        ans = ans * (row - col);
        ans = ans / col;
        ansRow.push_back((int)ans);
    }
    return ansRow;
}
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    for (int row = 1; row <= numRows; row++) ans.push_back(generateRow(row));
    return ans;
}
```

**Java**
```java
class Solution {
    private List<Integer> generateRow(int row) {
        long ans = 1;
        List<Integer> ansRow = new ArrayList<>();
        ansRow.add(1);
        for (int col = 1; col < row; col++) {
            ans = ans * (row - col);
            ans = ans / col;
            ansRow.add((int) ans);
        }
        return ansRow;
    }
    public List<List<Integer>> generate(int numRows) {
        List<List<Integer>> ans = new ArrayList<>();
        for (int row = 1; row <= numRows; row++) ans.add(generateRow(row));
        return ans;
    }
}
```

#### Alternative: build from the previous row *(not in video)*
`row[i][j] = row[i−1][j−1] + row[i−1][j]` with 1s at the ends — also O(n²) and avoids multiplication/overflow concerns.

#### Key Takeaways
- Type 3 = Type 2 applied to every row; break code into well-named helper functions in interviews.

[↑ Contents](#contents) · [← Previous](#p84) · [Next →](#p86)

---

<a id="p86"></a>

### 19. Rotate matrix by 90 degrees

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/rotate-image/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/rotate-matrix-90-degrees-clockwise) | [Watch](https://youtu.be/Z0R2u6gd3GU) |

#### Problem Statement
Rotate an `n × n` matrix by 90° **clockwise** (LeetCode 48 "Rotate Image" requires doing it in place).

```text
 1  2  3  4        13  9  5  1
 5  6  7  8   ->   14 10  6  2
 9 10 11 12        15 11  7  3
13 14 15 16        16 12  8  4
```

#### Approach 1: Brute force — answer matrix
Observation: the first row becomes the last column, the second row the second-last column, etc. Mapping indices: element `(i, j)` goes to **`(j, n − 1 − i)`** (e.g. (0,0)→(0,3), (0,1)→(1,3), (1,0)→(0,2)).

**Complexity:** Time O(n²), Space O(n²) for the extra matrix.

**C++**
```cpp
vector<vector<int>> rotateBrute(vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans[j][n - 1 - i] = mat[i][j];
    return ans;
}
```

**Java**
```java
class Solution {
    static int[][] rotateBrute(int[][] mat) {
        int n = mat.length;
        int[][] ans = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ans[j][n - 1 - i] = mat[i][j];
        return ans;
    }
}
```

#### Approach 2: Optimal — transpose, then reverse every row (in place)
Observation: the first **column** (1, 5, 9, 13) appears as the first **row** of the answer, but reversed (13, 9, 5, 1). That suggests:
1. **Transpose** (rows become columns): swap `mat[i][j]` with `mat[j][i]` for the upper triangle only — `i = 0..n−2`, `j = i+1..n−1`. Diagonal elements stay where they are; swapping both triangles would undo the transpose.
2. **Reverse each row.**

**Complexity:** Time ≈ O(n²/2) for the transpose + O(n · n/2) for the reversals → O(n²). Space O(1).

**C++**
```cpp
void rotate(vector<vector<int>>& mat) {
    int n = mat.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            swap(mat[i][j], mat[j][i]);
    for (int i = 0; i < n; i++)
        reverse(mat[i].begin(), mat[i].end());
}
```

**Java**
```java
class Solution {
    public void rotate(int[][] mat) {
        int n = mat.length;
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++) {
                int t = mat[i][j]; mat[i][j] = mat[j][i]; mat[j][i] = t;
            }
        for (int i = 0; i < n; i++)
            for (int l = 0, r = n - 1; l < r; l++, r--) {
                int t = mat[i][l]; mat[i][l] = mat[i][r]; mat[i][r] = t;
            }
    }
}
```

#### Key Takeaways
- Clockwise 90° = transpose + reverse rows. (Anticlockwise = transpose + reverse columns *(not in video)*.)

[↑ Contents](#contents) · [← Previous](#p85) · [Next →](#p87)

---

<a id="p87"></a>

### 20. Set Matrix Zeroes

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/set-matrix-zeroes/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/set-matrix-zeroes) | [Watch](https://youtu.be/N0MgLvceX7M) |

#### Problem Statement
For every 0 in an `n × m` matrix, set its entire row and column to 0 — but only for the zeros **originally** present, not the ones you create (LeetCode 73).

```text
1 1 1 1        1 0 0 1
1 0 0 1   ->   0 0 0 0
1 1 0 1        0 0 0 0
1 1 1 1        1 0 0 1
```

#### Approach 1: Brute force — mark with −1 *(binary matrix)*
The video's version is a 0/1 matrix. Writing zeros immediately is wrong: a newly-created 0 would later be treated as an original one and wipe more rows/columns. So for each original 0, mark the **non-zero** cells in its row and column as −1; afterwards convert every −1 to 0. (Don't turn zeros into −1 — they still have to do their own marking.)

**Complexity:** Time O(n·m·(n + m)) + O(n·m) ≈ O(n³). Space O(1).
> −1 is only a safe marker when the matrix contains no −1 values (true for a binary matrix; not for LeetCode's general integers).

**C++**
```cpp
void markRow(vector<vector<int>>& mat, int i) {
    for (int j = 0; j < (int)mat[0].size(); j++) if (mat[i][j] != 0) mat[i][j] = -1;
}
void markCol(vector<vector<int>>& mat, int j) {
    for (int i = 0; i < (int)mat.size(); i++) if (mat[i][j] != 0) mat[i][j] = -1;
}
void setZeroesBrute(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0) { markRow(mat, i); markCol(mat, j); }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == -1) mat[i][j] = 0;
}
```

**Java**
```java
class Solution {
    static void markRow(int[][] mat, int i) {
        for (int j = 0; j < mat[0].length; j++) if (mat[i][j] != 0) mat[i][j] = -1;
    }
    static void markCol(int[][] mat, int j) {
        for (int i = 0; i < mat.length; i++) if (mat[i][j] != 0) mat[i][j] = -1;
    }
    static void setZeroesBrute(int[][] mat) {
        int n = mat.length, m = mat[0].length;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (mat[i][j] == 0) { markRow(mat, i); markCol(mat, j); }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (mat[i][j] == -1) mat[i][j] = 0;
    }
}
```

#### Approach 2: Better — row and column marker arrays
A cell ends up 0 iff **its row or its column contains at least one original 0**. So we don't need to paint rows/columns eagerly — just remember which rows/columns are affected:
1. `row[n]`, `col[m]` all 0. For every 0 at `(i, j)`: `row[i] = 1`, `col[j] = 1`.
2. Second pass: if `row[i] == 1 || col[j] == 1`, set `mat[i][j] = 0`.

**Complexity:** Time O(2·n·m), Space O(n + m).

**C++**
```cpp
void setZeroesBetter(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    vector<int> row(n, 0), col(m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0) { row[i] = 1; col[j] = 1; }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (row[i] || col[j]) mat[i][j] = 0;
}
```

**Java**
```java
class Solution {
    static void setZeroesBetter(int[][] mat) {
        int n = mat.length, m = mat[0].length;
        int[] row = new int[n], col = new int[m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (mat[i][j] == 0) { row[i] = 1; col[j] = 1; }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (row[i] == 1 || col[j] == 1) mat[i][j] = 0;
    }
}
```

#### Approach 3: Optimal — store the markers inside the matrix
Time can't beat O(n·m) (we must look at every cell), so optimise space: use the matrix's **first row** as the column-marker array and its **first column** as the row-marker array. They overlap at `mat[0][0]`, so `mat[0][0]` marks row 0, and a separate variable **`col0`** marks column 0.

1. **Mark:** for every 0 at `(i, j)`: `mat[i][0] = 0`; and if `j != 0`, `mat[0][j] = 0`, else `col0 = 0`.
2. **Fill the inner cells** `(1..n−1, 1..m−1)`: if `mat[i][j] != 0` and (`mat[i][0] == 0` or `mat[0][j] == 0`) → 0. Do these first: changing the marker row/column early would corrupt the markers.
3. **First row:** if `mat[0][0] == 0`, zero all of row 0. (Must happen before step 4, because step 4 may change `mat[0][0]`.)
4. **First column:** if `col0 == 0`, zero all of column 0.

**Complexity:** Time O(2·n·m), Space **O(1)**.

**C++**
```cpp
void setZeroes(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    int col0 = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0) {
                mat[i][0] = 0;
                if (j != 0) mat[0][j] = 0;
                else col0 = 0;
            }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (mat[i][j] != 0 && (mat[i][0] == 0 || mat[0][j] == 0)) mat[i][j] = 0;
    if (mat[0][0] == 0)
        for (int j = 0; j < m; j++) mat[0][j] = 0;
    if (col0 == 0)
        for (int i = 0; i < n; i++) mat[i][0] = 0;
}
```

**Java**
```java
class Solution {
    public void setZeroes(int[][] mat) {
        int n = mat.length, m = mat[0].length;
        int col0 = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (mat[i][j] == 0) {
                    mat[i][0] = 0;
                    if (j != 0) mat[0][j] = 0;
                    else col0 = 0;
                }
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                if (mat[i][j] != 0 && (mat[i][0] == 0 || mat[0][j] == 0)) mat[i][j] = 0;
        if (mat[0][0] == 0)
            for (int j = 0; j < m; j++) mat[0][j] = 0;
        if (col0 == 0)
            for (int i = 0; i < n; i++) mat[i][0] = 0;
    }
}
```

#### Key Takeaways
- Better → optimal by moving auxiliary arrays **into** the input; handle the overlapping cell with one extra variable and process in the right order.

[↑ Contents](#contents) · [← Previous](#p86) · [Next →](#p88)

---

<a id="p88"></a>

### 21. Two Sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Basic | No | [LeetCode](https://leetcode.com/problems/two-sum/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/two-sum) | [Watch](https://youtu.be/UXDSeD9mN-k) |

#### Problem Statement
Given an array and a `target`, there are two varieties (both covered in the video):
1. **Variety 1:** return "YES" if two **different** elements sum to `target`, else "NO".
2. **Variety 2 (LeetCode 1):** a solution is guaranteed — return the **indices** of the two elements.

```text
arr = [2, 6, 5, 8, 11], target = 14 -> YES / indices [1, 3]  (6 + 8)
arr = [2, 6, 5, 8, 11], target = 15 -> NO
```

#### Approach 1: Brute force — try every pair
For each `i`, check every `j`. Optimisation from the video: pairs are symmetric, so start `j` from `i + 1` (no need to re-check (6, 2) after (2, 6), and it also guarantees `i != j`). Still ≈ O(n²).

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
vector<int> twoSumBrute(vector<int>& arr, int target) {
    int n = arr.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] + arr[j] == target) return {i, j};
    return {-1, -1};
}
```

**Java**
```java
class Solution {
    static int[] twoSumBrute(int[] arr, int target) {
        int n = arr.length;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (arr[i] + arr[j] == target) return new int[]{i, j};
        return new int[]{-1, -1};
    }
}
```

#### Approach 2: Better — hashing (optimal for Variety 2)
To go linear, iterate once: at element `a`, the partner needed is `more = target − a`. Look it up in a hash map of **previously seen** elements (value → index). If present, done; otherwise store `a` with its index and continue. Checking before inserting guarantees the partner is a different element.

**Dry run (target 14):** 2 → need 12, absent, store {2:0}; 6 → need 8, absent, store {6:1}; 5 → need 9, absent, store; 8 → need 6 → present at 1 → answer [1, 3].

**Complexity:** Time O(n) with `unordered_map` (average; worst case O(n²)) or O(n log n) with `map`. Space O(n).

**C++**
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mpp;
    for (int i = 0; i < (int)nums.size(); i++) {
        int more = target - nums[i];
        if (mpp.find(more) != mpp.end()) return {mpp[more], i};
        mpp[nums[i]] = i;
    }
    return {-1, -1};
}
```

**Java**
```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> mpp = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int more = target - nums[i];
            if (mpp.containsKey(more)) return new int[]{mpp.get(more), i};
            mpp.put(nums[i], i);
        }
        return new int[]{-1, -1};
    }
}
```

#### Approach 3: Two pointers after sorting (Variety 1 without a map)
If the interviewer forbids a map: sort the array, put `left = 0`, `right = n − 1`.
- `sum == target` → YES.
- `sum < target` → need a bigger sum → `left++` (moving right would only shrink it).
- `sum > target` → `right--`.
Stop when the pointers cross → NO.

For Variety 2 you'd have to sort `(value, index)` pairs to keep the original indices — extra O(n) space, so hashing is preferred there.

**Complexity:** O(n log n) to sort + O(n) scan. Extra space O(1) (the input is reordered — mention that to the interviewer).

**C++**
```cpp
string twoSumExists(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) return "YES";
        else if (sum < target) left++;
        else right--;
    }
    return "NO";
}
```

**Java**
```java
class Solution {
    static String twoSumExists(int[] arr, int target) {
        int[] a = arr.clone();
        Arrays.sort(a);
        int left = 0, right = a.length - 1;
        while (left < right) {
            int sum = a[left] + a[right];
            if (sum == target) return "YES";
            else if (sum < target) left++;
            else right--;
        }
        return "NO";
    }
}
```

#### Key Takeaways
- "Find a partner" → store what you've seen in a hash map and look up `target − x`.
- Sorted data → two pointers converging from both ends.

[↑ Contents](#contents) · [← Previous](#p87) · [Next →](#p89)

---

<a id="p89"></a>

### 22. 3 Sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/3sum/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/3sum) | [Watch](https://youtu.be/DhFh8Kw7ymk) |

#### Problem Statement
Return all **unique** triplets `[a[i], a[j], a[k]]` with `i, j, k` distinct and `a[i] + a[j] + a[k] = 0` (LeetCode 15). Triplets with the same values in a different order count as duplicates.

```text
[-1, 0, 1, 2, -1, -4] -> [[-1, -1, 2], [-1, 0, 1]]
```

#### Approach 1: Brute force — three loops + set
Try every triplet with `i < j < k`. When the sum is 0, **sort** the triplet (so [−1, 2, −1] and [−1, −1, 2] look identical) and insert it into a `set` to discard duplicates.

**Complexity:** Time O(n³ · log(#unique triplets)) — gets TLE. Space O(2 × #triplets) (set + answer).

**C++**
```cpp
vector<vector<int>> threeSumBrute(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> temp = {nums[i], nums[j], nums[k]};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
    return vector<vector<int>>(st.begin(), st.end());
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> threeSumBrute(int[] nums) {
        int n = nums.length;
        Set<List<Integer>> st = new HashSet<>();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        List<Integer> temp = Arrays.asList(nums[i], nums[j], nums[k]);
                        Collections.sort(temp);
                        st.add(temp);
                    }
        return new ArrayList<>(st);
    }
}
```

#### Approach 2: Better — two loops + hashing
Remove the third loop: for fixed `i` and `j`, the needed value is `third = −(a[i] + a[j])`. Look it up in a hash set that contains **only the elements strictly between `i` and `j`** — so the third element is always a different index. Implementation: for each `i`, start with an empty set; as `j` advances, first check for `third`, then insert `a[j]`.

**Complexity:** Time ≈ O(n² · log m) (m = hash-set size; ~O(n²) with an unordered set). Space O(n) for the hash set + O(2 × #triplets).

**C++**
```cpp
vector<vector<int>> threeSumBetter(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++) {
        unordered_set<int> hashset;
        for (int j = i + 1; j < n; j++) {
            int third = -(nums[i] + nums[j]);
            if (hashset.find(third) != hashset.end()) {
                vector<int> temp = {nums[i], nums[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hashset.insert(nums[j]);
        }
    }
    return vector<vector<int>>(st.begin(), st.end());
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> threeSumBetter(int[] nums) {
        int n = nums.length;
        Set<List<Integer>> st = new HashSet<>();
        for (int i = 0; i < n; i++) {
            Set<Integer> hashset = new HashSet<>();
            for (int j = i + 1; j < n; j++) {
                int third = -(nums[i] + nums[j]);
                if (hashset.contains(third)) {
                    List<Integer> temp = Arrays.asList(nums[i], nums[j], third);
                    Collections.sort(temp);
                    st.add(temp);
                }
                hashset.add(nums[j]);
            }
        }
        return new ArrayList<>(st);
    }
}
```

#### Approach 3: Optimal — sort + two pointers
Get rid of the set by **sorting the whole array** first, so triplets come out already sorted and duplicates can be skipped while scanning.
1. Fix `i` (skip it if `a[i] == a[i − 1]` — that value was already handled as the first element).
2. `j = i + 1`, `k = n − 1`. While `j < k`: `sum = a[i] + a[j] + a[k]`.
   - `sum < 0` → `j++` (need bigger); `sum > 0` → `k--` (need smaller).
   - `sum == 0` → record `[a[i], a[j], a[k]]`, then `j++`, `k--`, and keep moving `j` while `a[j] == a[j − 1]` and `k` while `a[k] == a[k + 1]` to skip duplicates.

**Dry run (sorted [−2, −2, −2, −1, −1, −1, 0, 0, 0, 2, 2, 2, 2]):** i = −2: j/k move until [−2, 0, 2]; skip repeated 0s and 2s; i moves past the other −2s; i = −1: [−1, −1, 2]; skip; i = 0: [0, 0, 0]. Result: 3 triplets, no set needed.

**Complexity:** Time O(n log n) + O(n²). Space O(1) extra (only the answer list).

**C++**
```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ans;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int j = i + 1, k = n - 1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum < 0) j++;
            else if (sum > 0) k--;
            else {
                ans.push_back({nums[i], nums[j], nums[k]});
                j++; k--;
                while (j < k && nums[j] == nums[j - 1]) j++;
                while (j < k && nums[k] == nums[k + 1]) k--;
            }
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        int n = nums.length;
        Arrays.sort(nums);
        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int j = i + 1, k = n - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum < 0) j++;
                else if (sum > 0) k--;
                else {
                    ans.add(Arrays.asList(nums[i], nums[j], nums[k]));
                    j++; k--;
                    while (j < k && nums[j] == nums[j - 1]) j++;
                    while (j < k && nums[k] == nums[k + 1]) k--;
                }
            }
        }
        return ans;
    }
}
```

#### Key Takeaways
- Brute: all triplets + set; Better: hash the third element (only between i and j); Optimal: sort + fix one + two pointers + skip duplicates.

[↑ Contents](#contents) · [← Previous](#p88) · [Next →](#p90)

---

<a id="p90"></a>

### 23. 4 Sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Pro | No | [LeetCode](https://leetcode.com/problems/4sum/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/4sum) | [Watch](https://youtu.be/eD95WRfh81c) |

#### Problem Statement
Return all **unique** quadruplets `[a, b, c, d]` from **four distinct indices** whose sum equals `target` (LeetCode 18). Watch 3Sum first — 4Sum follows the same three steps.

```text
nums = [1, 0, -1, 0, -2, 2], target = 0 -> [[-2,-1,1,2], [-2,0,0,2], [-1,0,0,1]]
```

#### Approach 1: Brute force — four loops + set
Try every quadruplet `i < j < k < l`; when the sum equals `target`, sort it and insert into a set (unique), then copy the set into the answer.
**Overflow:** add the four numbers one at a time into a `long long` — writing `nums[i] + nums[j] + nums[k] + nums[l]` evaluates in `int` first and can overflow before any cast.

**Complexity:** Time O(n⁴), Space O(2 × #quads).

**C++**
```cpp
vector<vector<int>> fourSumBrute(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                for (int l = k + 1; l < n; l++) {
                    long long sum = nums[i];
                    sum += nums[j]; sum += nums[k]; sum += nums[l];
                    if (sum == target) {
                        vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
    return vector<vector<int>>(st.begin(), st.end());
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> fourSumBrute(int[] nums, int target) {
        int n = nums.length;
        Set<List<Integer>> st = new HashSet<>();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                    for (int l = k + 1; l < n; l++) {
                        long sum = (long) nums[i] + nums[j] + nums[k] + nums[l];
                        if (sum == target) {
                            List<Integer> temp = Arrays.asList(nums[i], nums[j], nums[k], nums[l]);
                            Collections.sort(temp);
                            st.add(temp);
                        }
                    }
        return new ArrayList<>(st);
    }
}
```

#### Approach 2: Better — three loops + hash set
The fourth value must be `target − (a[i] + a[j] + a[k])`. Look it up in a hash set containing **only elements between `j` and `k`** (cleared for every new `j`, filled as `k` moves) — so the fourth index is always distinct from `i`, `j`, `k`.

**Complexity:** Time O(n³ · log m) (≈ O(n³) with an unordered set). Space O(n) for the hash set + O(2 × #quads).

**C++**
```cpp
vector<vector<int>> fourSumBetter(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            set<long long> hashset;
            for (int k = j + 1; k < n; k++) {
                long long sum = nums[i];
                sum += nums[j]; sum += nums[k];
                long long fourth = target - sum;
                if (hashset.find(fourth) != hashset.end()) {
                    vector<int> temp = {nums[i], nums[j], nums[k], (int)fourth};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                hashset.insert(nums[k]);
            }
        }
    return vector<vector<int>>(st.begin(), st.end());
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> fourSumBetter(int[] nums, int target) {
        int n = nums.length;
        Set<List<Integer>> st = new HashSet<>();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                Set<Long> hashset = new HashSet<>();
                for (int k = j + 1; k < n; k++) {
                    long sum = (long) nums[i] + nums[j] + nums[k];
                    long fourth = target - sum;
                    if (hashset.contains(fourth)) {
                        List<Integer> temp = Arrays.asList(nums[i], nums[j], nums[k], (int) fourth);
                        Collections.sort(temp);
                        st.add(temp);
                    }
                    hashset.add((long) nums[k]);
                }
            }
        return new ArrayList<>(st);
    }
}
```

#### Approach 3: Optimal — sort, fix two, two pointers
1. Sort the array.
2. Fix `i`; skip if `i > 0 && a[i] == a[i − 1]`.
3. Fix `j = i + 1..`; skip if `j > i + 1 && a[j] == a[j − 1]` (the first `j` after `i` is always allowed).
4. `k = j + 1`, `l = n − 1`; while `k < l`: compute the sum (in `long long`):
   - equal → record, `k++`, `l--`, then skip equal values for `k` (compare with previous) and `l` (compare with next);
   - smaller → `k++`; larger → `l--`.

The quadruplets come out sorted, so no set is needed.

**Complexity:** Time O(n³) (two fixed loops × linear two-pointer scan). Space O(1) extra besides the answer.

**C++**
```cpp
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        for (int j = i + 1; j < n; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            int k = j + 1, l = n - 1;
            while (k < l) {
                long long sum = nums[i];
                sum += nums[j]; sum += nums[k]; sum += nums[l];
                if (sum == target) {
                    ans.push_back({nums[i], nums[j], nums[k], nums[l]});
                    k++; l--;
                    while (k < l && nums[k] == nums[k - 1]) k++;
                    while (k < l && nums[l] == nums[l + 1]) l--;
                } else if (sum < target) k++;
                else l--;
            }
        }
    }
    return ans;
}
```

**Java**
```java
class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        int n = nums.length;
        List<List<Integer>> ans = new ArrayList<>();
        Arrays.sort(nums);
        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                int k = j + 1, l = n - 1;
                while (k < l) {
                    long sum = (long) nums[i] + nums[j] + nums[k] + nums[l];
                    if (sum == target) {
                        ans.add(Arrays.asList(nums[i], nums[j], nums[k], nums[l]));
                        k++; l--;
                        while (k < l && nums[k] == nums[k - 1]) k++;
                        while (k < l && nums[l] == nums[l + 1]) l--;
                    } else if (sum < target) k++;
                    else l--;
                }
            }
        }
        return ans;
    }
}
```

#### Key Takeaways
- k-Sum pattern: sort, fix k−2 elements with duplicate-skipping loops, finish with two pointers.
- In the video, forgetting to sort first produced a wrong answer — the two-pointer step relies on sorted order.

[↑ Contents](#contents) · [← Previous](#p89) · [Next →](#p91)

---

<a id="p91"></a>

### 24. Sort an array of 0's 1's and 2's

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/sort-colors/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/sort-array-0s-1s-2s) | [Watch](https://youtu.be/tp8JIuCXBaU) |

#### Problem Statement
Sort an array containing only 0s, 1s and 2s, in place (LeetCode 75 "Sort Colors").

```text
[0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0] -> [0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2]
```

#### Approach 1: Brute force — any sorting algorithm
Merge sort: O(n log n) time, O(n) space for the temporary array.

**C++**
```cpp
void sortBrute(vector<int>& nums) { sort(nums.begin(), nums.end()); }
```

**Java**
```java
class Solution {
    static void sortBrute(int[] nums) { Arrays.sort(nums); }
}
```

#### Approach 2: Better — count, then overwrite
Count zeros, ones and twos in one pass, then overwrite: the first `cnt0` cells with 0, the next `cnt1` with 1, the remaining `cnt2` with 2.

**Complexity:** Time O(2n) (count pass + fill pass; the three fill loops total n). Space O(1).

**C++**
```cpp
void sortCount(vector<int>& nums) {
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    for (int x : nums) {
        if (x == 0) cnt0++;
        else if (x == 1) cnt1++;
        else cnt2++;
    }
    int n = nums.size();
    for (int i = 0; i < cnt0; i++) nums[i] = 0;
    for (int i = cnt0; i < cnt0 + cnt1; i++) nums[i] = 1;
    for (int i = cnt0 + cnt1; i < n; i++) nums[i] = 2;
}
```

**Java**
```java
class Solution {
    static void sortCount(int[] nums) {
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        for (int x : nums) {
            if (x == 0) cnt0++;
            else if (x == 1) cnt1++;
            else cnt2++;
        }
        int n = nums.length;
        for (int i = 0; i < cnt0; i++) nums[i] = 0;
        for (int i = cnt0; i < cnt0 + cnt1; i++) nums[i] = 1;
        for (int i = cnt0 + cnt1; i < n; i++) nums[i] = 2;
    }
}
```

#### Approach 3: Optimal — Dutch National Flag algorithm (one pass)
Three pointers `low`, `mid`, `high` maintain these invariants:
- `[0 .. low−1]` are all **0**
- `[low .. mid−1]` are all **1**
- `[mid .. high]` are **unsorted** (still to process)
- `[high+1 .. n−1]` are all **2**

Initially `low = mid = 0`, `high = n − 1` (everything is unsorted). Look at `a[mid]`:
- **0:** it belongs at the end of the zeros. Swap `a[low]` (the first 1, or `mid` itself) with `a[mid]`; both regions grow → `low++`, `mid++`.
- **1:** already right after the ones → `mid++`.
- **2:** it belongs just before the twos. Swap `a[mid]` with `a[high]`; `high--`. **Don't move `mid`** — the element swapped in from `high` is unprocessed and must be examined.

Stop when `mid > high` (the unsorted region is empty).

**Why O(n):** every step either moves `mid` right or `high` left, shrinking the unsorted region by one; it starts with n elements.

**Complexity:** Time O(n) (single pass), Space O(1).

**C++**
```cpp
void sortColors(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++; mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}
```

**Java**
```java
class Solution {
    public void sortColors(int[] nums) {
        int low = 0, mid = 0, high = nums.length - 1;
        while (mid <= high) {
            if (nums[mid] == 0) {
                int t = nums[low]; nums[low] = nums[mid]; nums[mid] = t;
                low++; mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                int t = nums[mid]; nums[mid] = nums[high]; nums[high] = t;
                high--;
            }
        }
    }
}
```

#### Key Takeaways
- Explain the **invariants** (the three/four regions), not just the code — that's what interviewers probe.
- After swapping with `high`, keep `mid` where it is.

[↑ Contents](#contents) · [← Previous](#p90) · [Next →](#p92)

---

<a id="p92"></a>

### 25. Kadane's Algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/maximum-subarray/) | [Watch](https://youtu.be/AHZpyENo7k4) |

#### Problem Statement
Return the maximum sum of a **subarray** (a contiguous, non-empty part of the array) (LeetCode 53). Follow-up: print one subarray with that maximum sum.

```text
[-2, -3, 4, -1, -2, 1, 5, -3] -> 7   (subarray [4, -1, -2, 1, 5])
```
A subarray must be contiguous; picking `[-1, -2]` and then `5` (skipping an element) is a subsequence, not a subarray.

#### Approach 1: Brute force — all subarrays, sum each (three loops)
`i` = start, `j` = end, inner `k` loop sums `a[i..j]`.

**Complexity:** ≈ O(n³), Space O(1).

**C++**
```cpp
int maxSubarrayBrute(vector<int>& a) {
    int n = a.size(), maxi = INT_MIN;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) sum += a[k];
            maxi = max(maxi, sum);
        }
    return maxi;
}
```

**Java**
```java
class Solution {
    static int maxSubarrayBrute(int[] a) {
        int n = a.length, maxi = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++) {
                int sum = 0;
                for (int k = i; k <= j; k++) sum += a[k];
                maxi = Math.max(maxi, sum);
            }
        return maxi;
    }
}
```

#### Approach 2: Better — extend the running sum (two loops)
The sum of `a[i..j]` = sum of `a[i..j−1]` + `a[j]`, so keep one running sum as `j` advances — no third loop.

**Complexity:** O(n²), Space O(1).

**C++**
```cpp
int maxSubarrayBetter(vector<int>& a) {
    int n = a.size(), maxi = INT_MIN;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            maxi = max(maxi, sum);
        }
    }
    return maxi;
}
```

**Java**
```java
class Solution {
    static int maxSubarrayBetter(int[] a) {
        int n = a.length, maxi = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = i; j < n; j++) {
                sum += a[j];
                maxi = Math.max(maxi, sum);
            }
        }
        return maxi;
    }
}
```

#### Approach 3: Optimal — Kadane's algorithm
Iterate once, adding each element to `sum` and updating `maxi`. **If `sum` becomes negative, reset it to 0** — carrying a negative prefix into the future can only lower every later sum, so it's better to start a fresh subarray at the next element. A positive prefix (even one that contains negatives, like 4 + (−1) + (−2) + 1 = 2) is always worth carrying.

**Dry run:** −2 → maxi −2, reset; −3 → reset; 4 → maxi 4; −1 → 3; −2 → 1; 1 → 2; 5 → **7** (maxi 7); −3 → 4. Answer 7.

**Variant from the video's platform:** if an *empty* subarray is allowed (sum 0), return `max(maxi, 0)`.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
long long maxSubArray(vector<int>& a) {
    long long maxi = LLONG_MIN, sum = 0;
    for (int x : a) {
        sum += x;
        if (sum > maxi) maxi = sum;
        if (sum < 0) sum = 0;
    }
    return maxi;
}
```

**Java**
```java
class Solution {
    public int maxSubArray(int[] a) {
        long maxi = Long.MIN_VALUE, sum = 0;
        for (int x : a) {
            sum += x;
            if (sum > maxi) maxi = sum;
            if (sum < 0) sum = 0;
        }
        return (int) maxi;
    }
}
```

#### Follow-up: print the maximum-sum subarray
A new candidate subarray always begins where `sum == 0` (at the start, or right after a reset). So: when `sum == 0` before adding `a[i]`, set `start = i`; whenever `sum > maxi`, record `ansStart = start`, `ansEnd = i`.

**Complexity:** still O(n) time, O(1) space.

**C++**
```cpp
vector<int> maxSubArrayPrint(vector<int>& a) {
    long long maxi = LLONG_MIN, sum = 0;
    int start = 0, ansStart = -1, ansEnd = -1;
    for (int i = 0; i < (int)a.size(); i++) {
        if (sum == 0) start = i;
        sum += a[i];
        if (sum > maxi) { maxi = sum; ansStart = start; ansEnd = i; }
        if (sum < 0) sum = 0;
    }
    return vector<int>(a.begin() + ansStart, a.begin() + ansEnd + 1);
}
```

**Java**
```java
class Solution {
    static int[] maxSubArrayPrint(int[] a) {
        long maxi = Long.MIN_VALUE, sum = 0;
        int start = 0, ansStart = -1, ansEnd = -1;
        for (int i = 0; i < a.length; i++) {
            if (sum == 0) start = i;
            sum += a[i];
            if (sum > maxi) { maxi = sum; ansStart = start; ansEnd = i; }
            if (sum < 0) sum = 0;
        }
        return Arrays.copyOfRange(a, ansStart, ansEnd + 1);
    }
}
```

#### Key Takeaways
- Kadane: "drop the running sum when it goes negative". Initialise the answer to the minimum value so all-negative arrays work.

[↑ Contents](#contents) · [← Previous](#p91) · [Next →](#p93)

---

<a id="p93"></a>

### 26. Next Permutation

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Medium) | Core | No | [LeetCode](https://leetcode.com/problems/next-permutation/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/next-permutation) | [Watch](https://youtu.be/JDOXKqF60RQ) |

#### Problem Statement
Rearrange the array into the **next lexicographically greater permutation**; if it's already the largest, return the smallest (sorted ascending) permutation. In place (LeetCode 31).

```text
[3, 1, 2] -> [3, 2, 1]     (permutations in order: 123, 132, 213, 231, 312, 321)
[3, 2, 1] -> [1, 2, 3]     (last permutation wraps around)
[2, 1, 5, 4, 3, 0, 0] -> [2, 3, 0, 0, 1, 4, 5]
```

#### Approach 1: Brute force — generate all permutations
Generate every permutation in sorted order (recursion), linear-search the current one, return the next (or the first if it's last). In an interview, **describe** this at a high level — don't code it (it wastes time).

**Complexity:** at least O(n! × n) — for n = 15 that's ~10¹² operations. Hopeless.

**C++**
```cpp
void permute(vector<int>& a, int idx, set<vector<int>>& all) {
    if (idx == (int)a.size()) { all.insert(a); return; }
    for (int i = idx; i < (int)a.size(); i++) {
        swap(a[idx], a[i]);
        permute(a, idx + 1, all);
        swap(a[idx], a[i]);
    }
}
vector<int> nextPermBrute(vector<int> a) {
    set<vector<int>> all;                 // sorted + unique
    vector<int> copy = a;
    permute(copy, 0, all);
    auto it = all.find(a);
    ++it;
    if (it == all.end()) return *all.begin();
    return *it;
}
```

**Java**
```java
class Solution {
    static void permute(int[] a, int idx, TreeSet<List<Integer>> all) {
        if (idx == a.length) {
            List<Integer> p = new ArrayList<>();
            for (int x : a) p.add(x);
            all.add(p);
            return;
        }
        for (int i = idx; i < a.length; i++) {
            int t = a[idx]; a[idx] = a[i]; a[i] = t;
            permute(a, idx + 1, all);
            t = a[idx]; a[idx] = a[i]; a[i] = t;
        }
    }
    static List<Integer> nextPermBrute(int[] a) {
        TreeSet<List<Integer>> all = new TreeSet<>((x, y) -> {
            for (int i = 0; i < x.size(); i++)
                if (!x.get(i).equals(y.get(i))) return x.get(i) - y.get(i);
            return 0;
        });
        permute(a.clone(), 0, all);
        List<Integer> cur = new ArrayList<>();
        for (int x : a) cur.add(x);
        List<Integer> nxt = all.higher(cur);
        return nxt == null ? all.first() : nxt;
    }
}
```

#### Approach 2: "Better" — C++ STL `next_permutation`
C++ users can mention `next_permutation(a.begin(), a.end())`, which does exactly this in place (and returns `false` + sorts when wrapping). The interviewer will then ask you to implement it → optimal approach.

**C++**
```cpp
void nextPermutationSTL(vector<int>& nums) {
    next_permutation(nums.begin(), nums.end());
}
```

**Java:** there is no built-in equivalent in the Java standard library, so Java users go straight to the optimal implementation below.

#### Approach 3: Optimal — three observations
Think of a dictionary: "raj" < "rax" < "rbx" — the next word shares the **longest possible prefix** with the current one.

1. **Find the break point.** From the right, the array is increasing (0, 0, 3, 4, 5 in the example) until some index `ind` where `a[ind] < a[ind + 1]` (here `1 < 5`). Everything after `ind` is already the largest arrangement of those elements, so the prefix up to `ind − 1` can stay and position `ind` must increase. If no break point exists (`ind = −1`), the array is the last permutation → **reverse the whole array** and return.
2. **Swap with the smallest greater element.** Scanning from the right, find the first `a[i] > a[ind]` — because the suffix is increasing from the right, this is the smallest element greater than `a[ind]` — and swap them. (1 ↔ 3 → [2, 3, 5, 4, 1, 0, 0].)
3. **Make the suffix as small as possible.** The prefix is now already greater, so the suffix should be the smallest arrangement, i.e. ascending. It is still in descending order after the swap, so just **reverse** `a[ind+1 .. n−1]` → [2, 3, 0, 0, 1, 4, 5].

**Complexity:** Time O(3n) worst case, Space O(1) (the input is modified in place).

**C++**
```cpp
void nextPermutation(vector<int>& a) {
    int n = a.size(), ind = -1;
    for (int i = n - 2; i >= 0; i--)
        if (a[i] < a[i + 1]) { ind = i; break; }
    if (ind == -1) {
        reverse(a.begin(), a.end());
        return;
    }
    for (int i = n - 1; i > ind; i--)
        if (a[i] > a[ind]) { swap(a[i], a[ind]); break; }
    reverse(a.begin() + ind + 1, a.end());
}
```

**Java**
```java
class Solution {
    private void reverse(int[] a, int l, int r) {
        while (l < r) { int t = a[l]; a[l] = a[r]; a[r] = t; l++; r--; }
    }
    public void nextPermutation(int[] a) {
        int n = a.length, ind = -1;
        for (int i = n - 2; i >= 0; i--)
            if (a[i] < a[i + 1]) { ind = i; break; }
        if (ind == -1) { reverse(a, 0, n - 1); return; }
        for (int i = n - 1; i > ind; i--)
            if (a[i] > a[ind]) { int t = a[i]; a[i] = a[ind]; a[ind] = t; break; }
        reverse(a, ind + 1, n - 1);
    }
}
```

#### Key Takeaways
- Break point (first dip from the right) → swap with the next-larger element from the right → reverse the suffix.
- Explain the intuition (longest common prefix, smallest possible increase), not just the steps.

[↑ Contents](#contents) · [← Previous](#p92) · [Next →](#p94)

---

## FAQs(Hard)

<a id="p94"></a>

### 27. Majority Element-II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Hard) | Core | No | [LeetCode](https://leetcode.com/problems/majority-element-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/majority-element-ii-n-by-3) | [Watch](https://youtu.be/vwZj1K0e9U8) |

#### Problem Statement
Return all elements that appear **more than ⌊n/3⌋ times** (LeetCode 229). (Watch Majority Element I first — this reuses Moore's voting intuition.)

```text
[1, 1, 1, 3, 3, 2, 2, 2] (n = 8, ⌊8/3⌋ = 2) -> [1, 2]   (each appears 3 > 2 times)
```

#### Key observation: at most 2 answers
More than ⌊n/3⌋ means at least ⌊n/3⌋ + 1 occurrences. Three such elements would need ≥ 3·(⌊n/3⌋ + 1) > n elements — impossible. So the answer has **0, 1 or 2** elements.

#### Approach 1: Brute force — count each candidate
For each `a[i]` not already in the answer, count it over the array; add it if count > n/3. Stop once the answer has 2 elements.

**Complexity:** Time O(n²), Space O(1) (answer has ≤ 2 elements).

**C++**
```cpp
vector<int> majority3Brute(vector<int>& v) {
    int n = v.size();
    vector<int> ls;
    for (int i = 0; i < n; i++) {
        if (ls.empty() || ls[0] != v[i]) {
            int cnt = 0;
            for (int j = 0; j < n; j++) if (v[j] == v[i]) cnt++;
            if (cnt > n / 3) ls.push_back(v[i]);
        }
        if (ls.size() == 2) break;
    }
    return ls;
}
```

**Java**
```java
class Solution {
    static List<Integer> majority3Brute(int[] v) {
        int n = v.length;
        List<Integer> ls = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (ls.isEmpty() || ls.get(0) != v[i]) {
                int cnt = 0;
                for (int j = 0; j < n; j++) if (v[j] == v[i]) cnt++;
                if (cnt > n / 3) ls.add(v[i]);
            }
            if (ls.size() == 2) break;
        }
        return ls;
    }
}
```

#### Approach 2: Better — hashing in a single pass
Count with a hash map; the moment an element's count **becomes exactly** `n/3 + 1` (the minimum qualifying count), add it to the answer — so each element is added once, and you can stop when the answer has 2 elements.

**Complexity:** Time O(n) (unordered map, average) or O(n log n) (ordered map). Space O(n).

**C++**
```cpp
vector<int> majority3Hash(vector<int>& v) {
    int n = v.size(), mini = n / 3 + 1;
    unordered_map<int, int> mpp;
    vector<int> ls;
    for (int x : v) {
        mpp[x]++;
        if (mpp[x] == mini) ls.push_back(x);
        if (ls.size() == 2) break;
    }
    sort(ls.begin(), ls.end());
    return ls;
}
```

**Java**
```java
class Solution {
    static List<Integer> majority3Hash(int[] v) {
        int n = v.length, mini = n / 3 + 1;
        Map<Integer, Integer> mpp = new HashMap<>();
        List<Integer> ls = new ArrayList<>();
        for (int x : v) {
            mpp.merge(x, 1, Integer::sum);
            if (mpp.get(x) == mini) ls.add(x);
            if (ls.size() == 2) break;
        }
        Collections.sort(ls);
        return ls;
    }
}
```

#### Approach 3: Optimal — extended Moore's voting (two candidates)
Keep `(el1, cnt1)` and `(el2, cnt2)`:
- `cnt1 == 0 && a[i] != el2` → `el1 = a[i]`, `cnt1 = 1`
- else `cnt2 == 0 && a[i] != el1` → `el2 = a[i]`, `cnt2 = 1`
- else `a[i] == el1` → `cnt1++`; else `a[i] == el2` → `cnt2++`
- else → `cnt1--`, `cnt2--` (an element different from both cancels one of each)

**Why the extra `!= el2` / `!= el1` checks:** on [2, 1, 1, 3, 1, …], after a cancellation `cnt1` may hit 0 while `el2` is 1; without the check a new 1 would be assigned to `el1` as well, so the same value would occupy both slots.

The candidates are only *possible* answers — **verify** by counting both (`> n/3`) in a second pass. Sort the result if the platform requires.

**Complexity:** Time O(2n), Space O(1).

**C++**
```cpp
vector<int> majorityElement(vector<int>& v) {
    int n = v.size();
    int cnt1 = 0, cnt2 = 0, el1 = INT_MIN, el2 = INT_MIN;
    for (int x : v) {
        if (cnt1 == 0 && x != el2) { cnt1 = 1; el1 = x; }
        else if (cnt2 == 0 && x != el1) { cnt2 = 1; el2 = x; }
        else if (x == el1) cnt1++;
        else if (x == el2) cnt2++;
        else { cnt1--; cnt2--; }
    }
    cnt1 = 0; cnt2 = 0;
    for (int x : v) {
        if (x == el1) cnt1++;
        if (x == el2) cnt2++;
    }
    vector<int> ls;
    int mini = n / 3 + 1;
    if (cnt1 >= mini) ls.push_back(el1);
    if (cnt2 >= mini && el2 != el1) ls.push_back(el2);
    sort(ls.begin(), ls.end());
    return ls;
}
```

**Java**
```java
class Solution {
    public List<Integer> majorityElement(int[] v) {
        int n = v.length;
        int cnt1 = 0, cnt2 = 0, el1 = Integer.MIN_VALUE, el2 = Integer.MIN_VALUE;
        for (int x : v) {
            if (cnt1 == 0 && x != el2) { cnt1 = 1; el1 = x; }
            else if (cnt2 == 0 && x != el1) { cnt2 = 1; el2 = x; }
            else if (x == el1) cnt1++;
            else if (x == el2) cnt2++;
            else { cnt1--; cnt2--; }
        }
        cnt1 = 0; cnt2 = 0;
        for (int x : v) {
            if (x == el1) cnt1++;
            if (x == el2) cnt2++;
        }
        List<Integer> ls = new ArrayList<>();
        int mini = n / 3 + 1;
        if (cnt1 >= mini) ls.add(el1);
        if (cnt2 >= mini && el2 != el1) ls.add(el2);
        Collections.sort(ls);
        return ls;
    }
}
```

#### Key Takeaways
- n/k majority → at most k−1 candidates → Moore's voting with k−1 counters + verification pass.

[↑ Contents](#contents) · [← Previous](#p93) · [Next →](#p95)

---

<a id="p95"></a>

### 28. Find the repeating and missing number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Hard) | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-the-missing-and-repeating-numbers-in-an-array) | [Watch](https://youtu.be/2D0D8HE6uak) |

#### Problem Statement
An array of size `n` contains numbers from `1..n`; one number **A** appears twice and one number **B** is missing. Return `[A, B]` (repeating, missing).

```text
[4, 3, 6, 2, 1, 1] -> [1, 5]
```

#### Approach 1: Brute force — count each number 1..n
For each `i` in `1..n`, count its occurrences: count 2 → repeating, count 0 → missing; stop once both are found.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
vector<int> findTwoBrute(vector<int>& a) {
    int n = a.size(), rep = -1, miss = -1;
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int x : a) if (x == i) cnt++;
        if (cnt == 2) rep = i;
        else if (cnt == 0) miss = i;
        if (rep != -1 && miss != -1) break;
    }
    return {rep, miss};
}
```

**Java**
```java
class Solution {
    static int[] findTwoBrute(int[] a) {
        int n = a.length, rep = -1, miss = -1;
        for (int i = 1; i <= n; i++) {
            int cnt = 0;
            for (int x : a) if (x == i) cnt++;
            if (cnt == 2) rep = i;
            else if (cnt == 0) miss = i;
            if (rep != -1 && miss != -1) break;
        }
        return new int[]{rep, miss};
    }
}
```

#### Approach 2: Better — hash array
Count frequencies in an array of size `n + 1`; frequency 2 → repeating, 0 → missing.

**Complexity:** Time O(2n), Space O(n).

**C++**
```cpp
vector<int> findTwoHash(vector<int>& a) {
    int n = a.size(), rep = -1, miss = -1;
    vector<int> hash(n + 1, 0);
    for (int x : a) hash[x]++;
    for (int i = 1; i <= n; i++) {
        if (hash[i] == 2) rep = i;
        else if (hash[i] == 0) miss = i;
        if (rep != -1 && miss != -1) break;
    }
    return {rep, miss};
}
```

**Java**
```java
class Solution {
    static int[] findTwoHash(int[] a) {
        int n = a.length, rep = -1, miss = -1;
        int[] hash = new int[n + 1];
        for (int x : a) hash[x]++;
        for (int i = 1; i <= n; i++) {
            if (hash[i] == 2) rep = i;
            else if (hash[i] == 0) miss = i;
            if (rep != -1 && miss != -1) break;
        }
        return new int[]{rep, miss};
    }
}
```

#### Approach 3: Optimal 1 — two equations from sums
Let `x` = repeating, `y` = missing.
1. `S − Sn` where `S` = array sum and `Sn = n(n+1)/2` — everything cancels except `x − y`. (Example: 17 − 21 = −4 = 1 − 5.)
2. `S2 − S2n` where `S2` = sum of squares of the array and `S2n = n(n+1)(2n+1)/6` — gives `x² − y² = (x − y)(x + y)`. (Example: −24.) So `x + y = (S2 − S2n) / (x − y)` = −24/−4 = 6.
3. Solve: `x = ((x − y) + (x + y)) / 2`, `y = x − (x − y)`.

Use `long long` throughout — the square sums overflow `int`. Cast `a[i]` to `long long` **before** squaring.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
vector<int> findMissingRepeatingNumbers(vector<int>& a) {
    long long n = a.size();
    long long SN = n * (n + 1) / 2;
    long long S2N = n * (n + 1) * (2 * n + 1) / 6;
    long long S = 0, S2 = 0;
    for (int i = 0; i < n; i++) {
        S += a[i];
        S2 += (long long)a[i] * (long long)a[i];
    }
    long long val1 = S - SN;          // x - y
    long long val2 = S2 - S2N;        // x^2 - y^2
    val2 = val2 / val1;               // x + y
    long long x = (val1 + val2) / 2;
    long long y = x - val1;
    return {(int)x, (int)y};
}
```

**Java**
```java
class Solution {
    static int[] findMissingRepeatingNumbers(int[] a) {
        long n = a.length;
        long SN = n * (n + 1) / 2;
        long S2N = n * (n + 1) * (2 * n + 1) / 6;
        long S = 0, S2 = 0;
        for (int i = 0; i < n; i++) {
            S += a[i];
            S2 += (long) a[i] * (long) a[i];
        }
        long val1 = S - SN;
        long val2 = S2 - S2N;
        val2 = val2 / val1;
        long x = (val1 + val2) / 2;
        long y = x - val1;
        return new int[]{(int) x, (int) y};
    }
}
```

#### Approach 4: Optimal 2 — XOR (harder; good for showing bit-manipulation skill)
1. XOR all array elements and all numbers `1..n`: pairs cancel, leaving `xr = x ^ y` (≠ 0 because x ≠ y). Example: 1 ^ 5 = 4 (binary 100).
2. Find a bit where `x` and `y` differ: any set bit of `xr`, e.g. the rightmost one: `xr & ~(xr − 1)`.
3. Split every number (array elements **and** 1..n) into two groups by that bit, XOR within each group. All other numbers appear an even number of times and cancel; `x` (appears 3 times in total) and `y` (once) end up alone, one per group → `zero` and `one`.
4. Count `zero` in the array: if it appears twice it is the repeating number; otherwise swap.

**Complexity:** Time O(n) (a few passes), Space O(1).

**C++**
```cpp
vector<int> findTwoXor(vector<int>& a) {
    int n = a.size();
    int xr = 0;
    for (int i = 0; i < n; i++) {
        xr ^= a[i];
        xr ^= (i + 1);
    }
    int number = xr & ~(xr - 1);          // rightmost differentiating bit
    int zero = 0, one = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] & number) one ^= a[i];
        else zero ^= a[i];
        if ((i + 1) & number) one ^= (i + 1);
        else zero ^= (i + 1);
    }
    int cnt = 0;
    for (int x : a) if (x == zero) cnt++;
    if (cnt == 2) return {zero, one};
    return {one, zero};
}
```

**Java**
```java
class Solution {
    static int[] findTwoXor(int[] a) {
        int n = a.length;
        int xr = 0;
        for (int i = 0; i < n; i++) {
            xr ^= a[i];
            xr ^= (i + 1);
        }
        int number = xr & ~(xr - 1);
        int zero = 0, one = 0;
        for (int i = 0; i < n; i++) {
            if ((a[i] & number) != 0) one ^= a[i];
            else zero ^= a[i];
            if (((i + 1) & number) != 0) one ^= (i + 1);
            else zero ^= (i + 1);
        }
        int cnt = 0;
        for (int x : a) if (x == zero) cnt++;
        if (cnt == 2) return new int[]{zero, one};
        return new int[]{one, zero};
    }
}
```

#### Key Takeaways
- Two unknowns need two equations: sum and sum of squares.
- XOR route: total XOR → differentiating bit → split into two buckets → verify which is which.

[↑ Contents](#contents) · [← Previous](#p94) · [Next →](#p96)

---

<a id="p96"></a>

### 29. Count Inversions

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Hard) | Pro | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-inversions-in-an-array-using-merge-sort) | [Watch](https://youtu.be/AseUmwVNaoY) |

#### Problem Statement
Count the pairs `(i, j)` with `i < j` and `a[i] > a[j]` (inversions). (Prerequisite: merge sort.)

```text
[5, 3, 2, 4, 1] -> 8
pairs: (5,3) (5,2) (5,4) (5,1) (3,2) (3,1) (2,1) (4,1)
```

#### Approach 1: Brute force — check every pair
For each `i`, check every `j > i`.

**Complexity:** ≈ O(n²), Space O(1).

**C++**
```cpp
long long inversionsBrute(vector<int>& a) {
    int n = a.size();
    long long cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) cnt++;
    return cnt;
}
```

**Java**
```java
class Solution {
    static long inversionsBrute(int[] a) {
        int n = a.length;
        long cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (a[i] > a[j]) cnt++;
        return cnt;
    }
}
```

#### Intuition for the optimal solution: counting across two sorted arrays
Take two **sorted** arrays, left `[2, 3, 5, 6]` and right `[2, 2, 4, 4, 8]`, and count pairs (x from left, y from right) with `x > y`. Merge them with two pointers: whenever the right element is smaller (`left[i] > right[j]`), then **every element from `left[i]` to the end of the left array** is also greater than `right[j]` (the left array is sorted) — add that whole count at once and move `j`. This takes one linear pass.

Merge sort produces exactly this situation: at every merge, the left half `[low..mid]` and right half `[mid+1..high]` are each sorted. Pairs **inside** each half were already counted at deeper levels, so each merge only needs to count the cross pairs.

#### Approach 2: Optimal — modified merge sort
In `merge`, when taking `a[right]` because `a[left] > a[right]`, add `mid − left + 1` (number of remaining elements in the left half). Make `mergeSort` return the count: count(left half) + count(right half) + count from this merge. (Avoid a global counter in interviews.)

**Dry run highlight:** merging [2, 3, 5] with [1, 4]: 1 < 2 → all 3 left elements form pairs with 1 → +3; then 2, 3 taken; 4 < 5 → +1. Together with the inner merges (5,3)+1, (3,5)+(2) +2, (4,1) +1 → total 8.

**Complexity:** Time O(n log n), Space O(n) (temporary array). The input array gets **sorted (modified)** — mention this; copy it first if the original must be preserved.

**C++**
```cpp
long long mergeCount(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low, right = mid + 1;
    long long cnt = 0;
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) temp.push_back(arr[left++]);
        else {
            cnt += (mid - left + 1);          // all remaining left elements > arr[right]
            temp.push_back(arr[right++]);
        }
    }
    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);
    for (int i = low; i <= high; i++) arr[i] = temp[i - low];
    return cnt;
}
long long mergeSortCount(vector<int>& arr, int low, int high) {
    long long cnt = 0;
    if (low >= high) return cnt;
    int mid = (low + high) / 2;
    cnt += mergeSortCount(arr, low, mid);
    cnt += mergeSortCount(arr, mid + 1, high);
    cnt += mergeCount(arr, low, mid, high);
    return cnt;
}
long long numberOfInversions(vector<int> a) {
    return mergeSortCount(a, 0, a.size() - 1);
}
```

**Java**
```java
class Solution {
    static long mergeCount(int[] arr, int low, int mid, int high) {
        List<Integer> temp = new ArrayList<>();
        int left = low, right = mid + 1;
        long cnt = 0;
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) temp.add(arr[left++]);
            else {
                cnt += (mid - left + 1);
                temp.add(arr[right++]);
            }
        }
        while (left <= mid) temp.add(arr[left++]);
        while (right <= high) temp.add(arr[right++]);
        for (int i = low; i <= high; i++) arr[i] = temp.get(i - low);
        return cnt;
    }
    static long mergeSortCount(int[] arr, int low, int high) {
        long cnt = 0;
        if (low >= high) return cnt;
        int mid = (low + high) / 2;
        cnt += mergeSortCount(arr, low, mid);
        cnt += mergeSortCount(arr, mid + 1, high);
        cnt += mergeCount(arr, low, mid, high);
        return cnt;
    }
    static long numberOfInversions(int[] a) {
        return mergeSortCount(a.clone(), 0, a.length - 1);
    }
}
```

#### Key Takeaways
- "Count pairs (i < j) with a condition" on unsorted data → think of counting during merge sort.

[↑ Contents](#contents) · [← Previous](#p95) · [Next →](#p97)

---

<a id="p97"></a>

### 30. Reverse Pairs

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/reverse-pairs/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-reverse-pairs) | [Watch](https://youtu.be/0e4bZaP3MDI) |

#### Problem Statement
Count **reverse pairs**: `(i, j)` with `i < j` and `a[i] > 2 · a[j]` (LeetCode 493). (Prerequisites: merge sort and Count Inversions.)

```text
[40, 25, 19, 12, 9, 6, 2] -> 15
[1, 3, 2, 3, 1]           -> 2
```

#### Approach 1: Brute force — check every pair
**Complexity:** ≈ O(n²), Space O(1).

**C++**
```cpp
int reversePairsBrute(vector<int>& a) {
    int n = a.size(), cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ((long long)a[i] > 2LL * a[j]) cnt++;
    return cnt;
}
```

**Java**
```java
class Solution {
    static int reversePairsBrute(int[] a) {
        int n = a.length, cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if ((long) a[i] > 2L * a[j]) cnt++;
        return cnt;
    }
}
```

#### Why the Count-Inversions trick doesn't transfer directly
In Count Inversions, while merging, if `left[i] > right[j]` then all later left elements also beat `right[j]`, and pairs are counted as a side effect of the merge order. Here the condition is `left[i] > 2 · right[j]`: an element failing the condition (6 vs 3) doesn't tell you anything about whether larger right elements were skipped correctly — you'd miss pairs. So counting must be a **separate pass before the merge**.

#### The separate counting pass (two sorted halves)
For left `[6, 13, 21, 25]` and right `[1, 2, 3, 4, 4, 5, 9, 11, 13]`:
- For 6: move `right` while `6 > 2·right` → passes 1, 2 → **2** pairs.
- For 13: **don't restart** — continue from where 6 stopped: passes 3, 4, 4, 5 → total 6 pairs for 13.
- For 21: continues past 9 → 7; for 25: past 11 → 8.

Because the left half is sorted, whatever worked for a smaller left element works for a larger one, so `right` only moves forward: the pass is linear, O(n1 + n2).

#### Approach 2: Optimal — merge sort + countPairs before each merge
```
mergeSort(low, high):
    cnt = mergeSort(low, mid) + mergeSort(mid+1, high)
    cnt += countPairs(low, mid, high)    // before merging
    merge(low, mid, high)
countPairs: right = mid + 1
    for i in low..mid:
        while right <= high and a[i] > 2·a[right]: right++
        cnt += right − (mid + 1)
```
Compute `2 · a[right]` in 64-bit — `2 * INT_MAX` overflows.

**Complexity:** Time O(2n log n) (count pass + merge at each level), Space O(n). The input array gets sorted — tell the interviewer (or work on a copy).

**C++**
```cpp
class Solution {
    void merge(vector<int>& arr, int low, int mid, int high) {
        vector<int> temp;
        int left = low, right = mid + 1;
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) temp.push_back(arr[left++]);
            else temp.push_back(arr[right++]);
        }
        while (left <= mid) temp.push_back(arr[left++]);
        while (right <= high) temp.push_back(arr[right++]);
        for (int i = low; i <= high; i++) arr[i] = temp[i - low];
    }
    int countPairs(vector<int>& arr, int low, int mid, int high) {
        int right = mid + 1, cnt = 0;
        for (int i = low; i <= mid; i++) {
            while (right <= high && (long long)arr[i] > 2LL * arr[right]) right++;
            cnt += right - (mid + 1);
        }
        return cnt;
    }
    int mergeSort(vector<int>& arr, int low, int high) {
        int cnt = 0;
        if (low >= high) return cnt;
        int mid = (low + high) / 2;
        cnt += mergeSort(arr, low, mid);
        cnt += mergeSort(arr, mid + 1, high);
        cnt += countPairs(arr, low, mid, high);
        merge(arr, low, mid, high);
        return cnt;
    }
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }
};
```

**Java**
```java
class Solution {
    private void merge(int[] arr, int low, int mid, int high) {
        List<Integer> temp = new ArrayList<>();
        int left = low, right = mid + 1;
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) temp.add(arr[left++]);
            else temp.add(arr[right++]);
        }
        while (left <= mid) temp.add(arr[left++]);
        while (right <= high) temp.add(arr[right++]);
        for (int i = low; i <= high; i++) arr[i] = temp.get(i - low);
    }
    private int countPairs(int[] arr, int low, int mid, int high) {
        int right = mid + 1, cnt = 0;
        for (int i = low; i <= mid; i++) {
            while (right <= high && (long) arr[i] > 2L * arr[right]) right++;
            cnt += right - (mid + 1);
        }
        return cnt;
    }
    private int mergeSort(int[] arr, int low, int high) {
        int cnt = 0;
        if (low >= high) return cnt;
        int mid = (low + high) / 2;
        cnt += mergeSort(arr, low, mid);
        cnt += mergeSort(arr, mid + 1, high);
        cnt += countPairs(arr, low, mid, high);
        merge(arr, low, mid, high);
        return cnt;
    }
    public int reversePairs(int[] nums) {
        return mergeSort(nums, 0, nums.length - 1);
    }
}
```

#### Key Takeaways
- When the pair condition isn't a plain comparison, count in a dedicated linear pass over the two sorted halves, then merge.

[↑ Contents](#contents) · [← Previous](#p96) · [Next →](#p98)

---

<a id="p98"></a>

### 31. Maximum Product Subarray in an Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Hard) | Core | No | [LeetCode](https://leetcode.com/problems/maximum-product-subarray/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/maximum-product-subarray) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the maximum product of a contiguous **subarray** (LeetCode 152).

```text
[2, 3, -2, 4]      -> 6     ([2, 3])
[-2, 0, -1]        -> 0
[3, 2, -1, 4, -6, 3, -2, 6] -> 864   ([4, -6, 3, -2, 6])
```

#### Approach 1: Brute force — every subarray
Fix the start `i`, extend the end `j`, keep a running product (two loops instead of three).

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int maxProductBrute(vector<int>& a) {
    int n = a.size();
    long long best = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        long long prod = 1;
        for (int j = i; j < n; j++) {
            prod *= a[j];
            best = max(best, prod);
        }
    }
    return (int)best;
}
```

**Java**
```java
class Solution {
    static int maxProductBrute(int[] a) {
        int n = a.length;
        long best = Long.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            long prod = 1;
            for (int j = i; j < n; j++) {
                prod *= a[j];
                best = Math.max(best, prod);
            }
        }
        return (int) best;
    }
}
```

#### Approach 2: Optimal — prefix and suffix products
Observations:
- If all numbers are positive, or the count of negatives is **even**, the whole array's product is the answer.
- If the count of negatives is **odd**, exactly one negative must be dropped: the best subarray is either a **prefix** ending before some negative or a **suffix** starting after it — so the answer is the max over all prefix and suffix products.
- **Zeros** split the array into independent parts: whenever a running product becomes 0, restart it at 1 (the 0 itself is still a candidate answer since we take max after multiplying).

Scan once, maintaining `pre` (left-to-right product) and `suf` (right-to-left product) simultaneously; `ans = max(ans, pre, suf)` each step.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
int maxProduct(vector<int>& a) {
    int n = a.size();
    double pre = 1, suf = 1, ans = -1e18;      // double avoids overflow on long products
    for (int i = 0; i < n; i++) {
        if (pre == 0) pre = 1;
        if (suf == 0) suf = 1;
        pre *= a[i];
        suf *= a[n - i - 1];
        ans = max(ans, max(pre, suf));
    }
    return (int)ans;
}
```

**Java**
```java
class Solution {
    public int maxProduct(int[] a) {
        int n = a.length;
        double pre = 1, suf = 1, ans = -1e18;
        for (int i = 0; i < n; i++) {
            if (pre == 0) pre = 1;
            if (suf == 0) suf = 1;
            pre *= a[i];
            suf *= a[n - i - 1];
            ans = Math.max(ans, Math.max(pre, suf));
        }
        return (int) ans;
    }
}
```

#### Approach 3: Kadane-style — track max and min ending here
A negative number turns the smallest (most negative) product into the largest. Keep both `maxEnd` and `minEnd`; at each element, the new values are the max/min of `a[i]`, `a[i]·maxEnd`, `a[i]·minEnd`.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
int maxProductKadane(vector<int>& a) {
    long long maxEnd = a[0], minEnd = a[0], ans = a[0];
    for (int i = 1; i < (int)a.size(); i++) {
        long long x = a[i];
        long long c1 = x * maxEnd, c2 = x * minEnd;
        maxEnd = max({x, c1, c2});
        minEnd = min({x, c1, c2});
        ans = max(ans, maxEnd);
    }
    return (int)ans;
}
```

**Java**
```java
class Solution {
    static int maxProductKadane(int[] a) {
        long maxEnd = a[0], minEnd = a[0], ans = a[0];
        for (int i = 1; i < a.length; i++) {
            long x = a[i];
            long c1 = x * maxEnd, c2 = x * minEnd;
            maxEnd = Math.max(x, Math.max(c1, c2));
            minEnd = Math.min(x, Math.min(c1, c2));
            ans = Math.max(ans, maxEnd);
        }
        return (int) ans;
    }
}
```

#### Edge Cases & Pitfalls
- Single negative element (`[-3]`) → answer −3; initialise with the first element / −∞, not 0.
- Zeros reset the running products.

#### Key Takeaways
- Products differ from sums because a negative can flip min to max: either track both, or reason with prefix/suffix products.

[↑ Contents](#contents) · [← Previous](#p97) · [Next →](#p99)

---

<a id="p99"></a>

### 32. Merge two sorted arrays without extra space

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Arrays › FAQs(Hard) | Core | No | [LeetCode](https://leetcode.com/problems/merge-sorted-array/) | [Watch](https://youtu.be/n7uwj04E0I4) |

#### Problem Statement
Two sorted arrays `a` (size n) and `b` (size m). **Without using extra space**, rearrange so that `a` holds the smallest n elements and `b` the remaining m, both sorted.

```text
a = [1, 3, 5, 7], b = [0, 2, 6, 8, 9] -> a = [0, 1, 2, 3], b = [5, 6, 7, 8, 9]
```
(LeetCode 88, linked on the sheet, is a different setup — see the end.)

#### Approach 1: Brute force — third array
Merge with two pointers into `c` of size n + m (standard merge), then copy back: `c[i]` to `a[i]` for `i < n`, and to `b[i − n]` otherwise.

**Complexity:** Time O(n + m) + O(n + m), Space O(n + m) — not allowed by the problem, but the natural first answer.

**C++**
```cpp
void mergeBrute(vector<long long>& a, vector<long long>& b) {
    int n = a.size(), m = b.size();
    vector<long long> c(n + m);
    int left = 0, right = 0, idx = 0;
    while (left < n && right < m) {
        if (a[left] <= b[right]) c[idx++] = a[left++];
        else c[idx++] = b[right++];
    }
    while (left < n) c[idx++] = a[left++];
    while (right < m) c[idx++] = b[right++];
    for (int i = 0; i < n + m; i++) {
        if (i < n) a[i] = c[i];
        else b[i - n] = c[i];
    }
}
```

**Java**
```java
class Solution {
    static void mergeBrute(long[] a, long[] b) {
        int n = a.length, m = b.length;
        long[] c = new long[n + m];
        int left = 0, right = 0, idx = 0;
        while (left < n && right < m) {
            if (a[left] <= b[right]) c[idx++] = a[left++];
            else c[idx++] = b[right++];
        }
        while (left < n) c[idx++] = a[left++];
        while (right < m) c[idx++] = b[right++];
        for (int i = 0; i < n + m; i++) {
            if (i < n) a[i] = c[i];
            else b[i - n] = c[i];
        }
    }
}
```

#### Approach 2: Optimal 1 — swap from the meeting ends, then sort each
`a[n−1]` is the largest of `a`; `b[0]` the smallest of `b`. Compare them with `left = n − 1`, `right = 0`:
- if `a[left] > b[right]`: they're on the wrong sides → swap, `left--`, `right++`;
- otherwise everything is already on the correct side → stop.

Now `a` contains exactly the n smallest values and `b` the rest, just not in order → sort both.

**Dry run:** 7 > 0 swap; 5 > 2 swap; 3 < 6 stop → a = [1, 3, 2, 0], b = [7, 5, 6, 8, 9] → sort → [0, 1, 2, 3], [5, 6, 7, 8, 9].

**Complexity:** Time O(min(n, m)) + O(n log n) + O(m log m). Space O(1).

**C++**
```cpp
void mergeOptimal1(vector<long long>& a, vector<long long>& b) {
    int n = a.size(), m = b.size();
    int left = n - 1, right = 0;
    while (left >= 0 && right < m) {
        if (a[left] > b[right]) {
            swap(a[left], b[right]);
            left--; right++;
        } else break;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
}
```

**Java**
```java
class Solution {
    static void mergeOptimal1(long[] a, long[] b) {
        int n = a.length, m = b.length;
        int left = n - 1, right = 0;
        while (left >= 0 && right < m) {
            if (a[left] > b[right]) {
                long t = a[left]; a[left] = b[right]; b[right] = t;
                left--; right++;
            } else break;
        }
        Arrays.sort(a);
        Arrays.sort(b);
    }
}
```

#### Approach 3: Optimal 2 — Gap method (from Shell sort)
Treat `a` and `b` as one virtual array of length `len = n + m`.
1. `gap = ceil(len / 2)` (computed as `len/2 + len%2`).
2. With `left = 0`, `right = left + gap`, while `right < len`: compare the two positions and swap if out of order; `left++`, `right++`. Position `p` maps to `a[p]` if `p < n`, else `b[p − n]`. Three cases: (a, b), (b, b), (a, a).
3. If `gap == 1`, stop; otherwise `gap = ceil(gap / 2)` and repeat.

**Dry run (len 9):** gap 5 → no swaps; gap 3 → swaps (3, 0), (5, 2); gap 2 → swap (7, 5); gap 1 → swaps (5, 3), (7, 6) → sorted.

**Complexity:** Time O(log₂(n + m) × (n + m)). Space O(1).

**C++**
```cpp
void swapIfGreater(vector<long long>& x, vector<long long>& y, int i, int j) {
    if (x[i] > y[j]) swap(x[i], y[j]);
}
void mergeGap(vector<long long>& a, vector<long long>& b) {
    int n = a.size(), m = b.size();
    int len = n + m;
    int gap = len / 2 + len % 2;
    while (gap > 0) {
        int left = 0, right = left + gap;
        while (right < len) {
            if (left < n && right >= n) swapIfGreater(a, b, left, right - n);
            else if (left >= n) swapIfGreater(b, b, left - n, right - n);
            else swapIfGreater(a, a, left, right);
            left++; right++;
        }
        if (gap == 1) break;
        gap = gap / 2 + gap % 2;
    }
}
```

**Java**
```java
class Solution {
    static void swapIfGreater(long[] x, long[] y, int i, int j) {
        if (x[i] > y[j]) { long t = x[i]; x[i] = y[j]; y[j] = t; }
    }
    static void mergeGap(long[] a, long[] b) {
        int n = a.length, m = b.length;
        int len = n + m;
        int gap = len / 2 + len % 2;
        while (gap > 0) {
            int left = 0, right = left + gap;
            while (right < len) {
                if (left < n && right >= n) swapIfGreater(a, b, left, right - n);
                else if (left >= n) swapIfGreater(b, b, left - n, right - n);
                else swapIfGreater(a, a, left, right);
                left++; right++;
            }
            if (gap == 1) break;
            gap = gap / 2 + gap % 2;
        }
    }
}
```

#### LeetCode 88 variant *(not in video)*
`nums1` has length m + n with the last n slots empty; merge `nums2` into it. Fill from the **back** with three pointers (largest first) — O(m + n), no extra space.

**C++**
```cpp
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
}
```

**Java**
```java
class Solution {
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
            else nums1[k--] = nums2[j--];
        }
    }
}
```

#### Key Takeaways
- Both optimal methods are accepted in interviews; the swap-then-sort one is easier to code, the Gap method avoids the sorts.

[↑ Contents](#contents) · [← Previous](#p98)

---
