# Dynamic Programming — Striver's A2Z DSA Sheet Notes

Section 17 of 20 · 52 problems · 50 with video, 2 without · [All sections](00-index.md)

[← Graphs](16-graphs.md) | [Tries →](18-tries.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**1D DP**

1. [Climbing stairs](#p385) — Core
2. [Frog Jump](#p386) — Core
3. [Frog jump with K distances](#p387) — Core
4. [Maximum sum of non adjacent elements](#p388) — Core
5. [House robber](#p389) — Core

**2D DP**

6. [Ninja's training](#p390) — Core

**DP on grids**

7. [Grid unique paths](#p391) — Core
8. [Unique paths II](#p392) — Pro
9. [Minimum Falling Path Sum](#p393) — Core
10. [Triangle](#p394) — Core
11. [Cherry pickup II](#p395) — Pro
12. [Count Square Submatrices with All Ones](#p396) — —

**DP on stocks**

13. [Best time to buy and sell stock](#p397) — Core
14. [Best time to buy and sell stock II](#p398) — Core
15. [Best time to buy and sell stock III](#p399) — Pro
16. [Best time to buy and sell stock IV](#p400) — Pro
17. [Best time to buy and sell stock with transaction fees](#p401) — Core
18. [Best Time to Buy and Sell Stock with Cooldown](#p402) — Core

**DP on subsequences**

19. [Subset sum equals to target](#p403) — Core
20. [Partition equal subset sum](#p404) — Core
21. [Partition a set into two subsets with minimum absolute sum difference](#p405) — Pro
22. [Count subsets with sum K](#p406) — Core
23. [Count partitions with given difference](#p407) — Core
24. [0 and 1 Knapsack](#p408) — Core
25. [Minimum coins](#p409) — Core
26. [Target sum](#p410) — Core
27. [Coin change II](#p411) — Pro
28. [Unbounded knapsack](#p412) — Core
29. [Rod cutting problem](#p413) — Pro

**LIS**

30. [Longest Increasing Subsequence](#p414) — Core
31. [Print Longest Increasing Subsequence](#p415) — Pro
32. [Largest Divisible Subset](#p416) — Core
33. [Longest String Chain](#p417) — Core
34. [Longest Bitonic Subsequence](#p418) — Core
35. [Number of Longest Increasing Subsequences](#p419) — Core

**DP on strings**

36. [Longest common subsequence](#p420) — Core
37. [Longest common substring](#p421) — Core
38. [Longest palindromic subsequence](#p422) — Core
39. [Minimum insertions to make string palindrome](#p423) — Pro
40. [Minimum insertions or deletions to convert string A to B](#p424) — Core
41. [Shortest common supersequence](#p425) — Pro
42. [Distinct subsequences](#p426) — Pro
43. [Edit distance](#p427) — Pro
44. [Wildcard matching](#p428) — Pro
45. [Word Break](#p429) — Core · *no video*
46. [Count Palindromic Subsequences](#p430) — Pro · *no video*

**MCM DP**

47. [Matrix chain multiplication](#p431) — Pro
48. [Burst balloons](#p432) — Pro
49. [Palindrome partitioning II](#p433) — Pro
50. [Partition Array for Maximum Sum](#p434) — Pro
51. [Minimum cost to cut the stick](#p435) — Pro
52. [Different Ways to Evaluate a Boolean Expression](#p436) — Pro

---

## 1D DP

<a id="p385"></a>

### 1. Climbing stairs

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › 1D DP | Core | No | [LeetCode](https://leetcode.com/problems/climbing-stairs/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/climbing-stairs) | [Watch](https://youtu.be/mLfjzJsN8us) |

> **How DP notes are organised in this section** (following Striver's DP series): every problem goes **Recursion → Memoization (top-down) → Tabulation (bottom-up) → Space optimisation**.
> - **Recursion:** express the problem in terms of an index (or indices), try all choices, and return the best or the count.
> - **Memoization:** cache `f(state)` in a `dp` table so each state is computed once.
> - **Tabulation:** fill the same table iteratively from the base cases upwards.
> - **Space optimisation:** keep only the previous row(s) or the last few values that the recurrence actually reads.

#### Problem Statement
You can climb **1 or 2** steps at a time. In how many distinct ways can you reach the top of an `n`-step staircase? (This is the Fibonacci recurrence.)

```text
n = 2  ->  2   (1+1, 2)
n = 3  ->  3   (1+1+1, 1+2, 2+1)
n = 5  ->  8
```

#### Intuition — the recurrence
The last move onto step `n` came either from `n−1` (a 1-step) or from `n−2` (a 2-step). So:

  **f(n) = f(n−1) + f(n−2)**, with f(0) = 1 (one way: do nothing) and f(1) = 1.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int climbRec(int n) {
    if (n <= 1) return 1;
    return climbRec(n - 1) + climbRec(n - 2);
}
```

**Java**
```java
class Solution {
    static int climbRec(int n) {
        if (n <= 1) return 1;
        return climbRec(n - 1) + climbRec(n - 2);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n) time, O(n) for dp plus O(n) stack.

**C++**
```cpp
int climbMemo(int n, vector<int>& dp) {
    if (n <= 1) return 1;
    if (dp[n] != -1) return dp[n];
    return dp[n] = climbMemo(n - 1, dp) + climbMemo(n - 2, dp);
}
int climbStairsMemo(int n) {
    vector<int> dp(n + 1, -1);
    return climbMemo(n, dp);
}
```

**Java**
```java
class Solution {
    static int climbMemo(int n, int[] dp) {
        if (n <= 1) return 1;
        if (dp[n] != -1) return dp[n];
        return dp[n] = climbMemo(n - 1, dp) + climbMemo(n - 2, dp);
    }
    static int climbStairsMemo(int n) {
        int[] dp = new int[n + 1];
        Arrays.fill(dp, -1);
        return climbMemo(n, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int climbStairsTab(int n) {
    vector<int> dp(n + 1);
    dp[0] = 1;
    if (n >= 1) dp[1] = 1;
    for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}
```

**Java**
```java
class Solution {
    static int climbStairsTab(int n) {
        int[] dp = new int[n + 1];
        dp[0] = 1;
        if (n >= 1) dp[1] = 1;
        for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];
        return dp[n];
    }
}
```

#### Approach 4: Space optimisation — two variables
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int climbStairs(int n) {
    int prev2 = 1, prev = 1;                 // f(0), f(1)
    for (int i = 2; i <= n; i++) {
        int cur = prev + prev2;
        prev2 = prev;
        prev = cur;
    }
    return prev;
}
```

**Java**
```java
class Solution {
    static int climbStairs(int n) {
        int prev2 = 1, prev = 1;
        for (int i = 2; i <= n; i++) {
            int cur = prev + prev2;
            prev2 = prev;
            prev = cur;
        }
        return prev;
    }
}
```

#### Key Takeaways
- The canonical DP progression is: exponential recursion → O(n) memoization → O(n) table → O(1) rolling variables.
- Recognising "count the ways by the last move" gives the Fibonacci recurrence.

[↑ Contents](#contents) · [Next →](#p386)

---

<a id="p386"></a>

### 2. Frog Jump

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › 1D DP | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/frog-jump-minimum-energy) | [Watch](https://youtu.be/EgG3jsGoPvQ) |

#### Problem Statement
A frog is on stair `0` and wants to reach stair `n−1`. From stair `i` it can jump to `i+1` or `i+2`, paying `|height[i] − height[j]|` energy. Return the minimum total energy.

```text
height = [10, 20, 30, 10]   ->  20   (0 -> 1 -> 3: 10 + 10)
height = [10, 50, 10]       ->  0    (0 -> 2)
```

#### Intuition
Let `f(i)` be the minimum energy to reach stair `i`. The frog arrived either from `i−1` or from `i−2`:

  **f(i) = min(f(i−1) + |h[i]−h[i−1]|, f(i−2) + |h[i]−h[i−2]|)**, with f(0) = 0.

Greedy (always take the cheaper next jump) fails, so try both choices.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int frogRec(int i, vector<int>& h) {
    if (i == 0) return 0;
    int one = frogRec(i - 1, h) + abs(h[i] - h[i - 1]);
    int two = INT_MAX;
    if (i > 1) two = frogRec(i - 2, h) + abs(h[i] - h[i - 2]);
    return min(one, two);
}
int frogJumpRec(vector<int>& h) { return frogRec(h.size() - 1, h); }
```

**Java**
```java
class Solution {
    static int frogRec(int i, int[] h) {
        if (i == 0) return 0;
        int one = frogRec(i - 1, h) + Math.abs(h[i] - h[i - 1]);
        int two = Integer.MAX_VALUE;
        if (i > 1) two = frogRec(i - 2, h) + Math.abs(h[i] - h[i - 2]);
        return Math.min(one, two);
    }
    static int frogJumpRec(int[] h) { return frogRec(h.length - 1, h); }
}
```

#### Approach 2: Memoization
**Complexity:** O(n) time, O(n) + O(n) stack.

**C++**
```cpp
int frogMemo(int i, vector<int>& h, vector<int>& dp) {
    if (i == 0) return 0;
    if (dp[i] != -1) return dp[i];
    int one = frogMemo(i - 1, h, dp) + abs(h[i] - h[i - 1]);
    int two = INT_MAX;
    if (i > 1) two = frogMemo(i - 2, h, dp) + abs(h[i] - h[i - 2]);
    return dp[i] = min(one, two);
}
int frogJumpMemo(vector<int>& h) {
    vector<int> dp(h.size(), -1);
    return frogMemo(h.size() - 1, h, dp);
}
```

**Java**
```java
class Solution {
    static int frogMemo(int i, int[] h, int[] dp) {
        if (i == 0) return 0;
        if (dp[i] != -1) return dp[i];
        int one = frogMemo(i - 1, h, dp) + Math.abs(h[i] - h[i - 1]);
        int two = Integer.MAX_VALUE;
        if (i > 1) two = frogMemo(i - 2, h, dp) + Math.abs(h[i] - h[i - 2]);
        return dp[i] = Math.min(one, two);
    }
    static int frogJumpMemo(int[] h) {
        int[] dp = new int[h.length];
        Arrays.fill(dp, -1);
        return frogMemo(h.length - 1, h, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int frogJumpTab(vector<int>& h) {
    int n = h.size();
    vector<int> dp(n, 0);
    for (int i = 1; i < n; i++) {
        int one = dp[i - 1] + abs(h[i] - h[i - 1]);
        int two = INT_MAX;
        if (i > 1) two = dp[i - 2] + abs(h[i] - h[i - 2]);
        dp[i] = min(one, two);
    }
    return dp[n - 1];
}
```

**Java**
```java
class Solution {
    static int frogJumpTab(int[] h) {
        int n = h.length;
        int[] dp = new int[n];
        for (int i = 1; i < n; i++) {
            int one = dp[i - 1] + Math.abs(h[i] - h[i - 1]);
            int two = Integer.MAX_VALUE;
            if (i > 1) two = dp[i - 2] + Math.abs(h[i] - h[i - 2]);
            dp[i] = Math.min(one, two);
        }
        return dp[n - 1];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int frogJump(vector<int>& h) {
    int n = h.size(), prev = 0, prev2 = 0;
    for (int i = 1; i < n; i++) {
        int one = prev + abs(h[i] - h[i - 1]);
        int two = INT_MAX;
        if (i > 1) two = prev2 + abs(h[i] - h[i - 2]);
        int cur = min(one, two);
        prev2 = prev;
        prev = cur;
    }
    return prev;
}
```

**Java**
```java
class Solution {
    static int frogJump(int[] h) {
        int n = h.length, prev = 0, prev2 = 0;
        for (int i = 1; i < n; i++) {
            int one = prev + Math.abs(h[i] - h[i - 1]);
            int two = Integer.MAX_VALUE;
            if (i > 1) two = prev2 + Math.abs(h[i] - h[i - 2]);
            int cur = Math.min(one, two);
            prev2 = prev;
            prev = cur;
        }
        return prev;
    }
}
```

#### Key Takeaways
- "Try all ways" (recursion) is safer than greedy whenever a cheap step now can cost more later.

[↑ Contents](#contents) · [← Previous](#p385) · [Next →](#p387)

---

<a id="p387"></a>

### 3. Frog jump with K distances

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › 1D DP | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/frog-jump-with-k-distances) | [Watch](https://youtu.be/Kmh3rhyEtB8) |

#### Problem Statement
Same as Frog Jump, but from stair `i` the frog may jump to any of `i+1 … i+k`.

```text
height = [10, 30, 40, 50, 20], k = 3   ->  30   (0 -> 1 -> 4: 20 + 10)
height = [10, 20, 10], k = 1           ->  20
```

#### Intuition
**f(i) = min over j = 1 … k (with i−j ≥ 0) of f(i−j) + |h[i] − h[i−j]|**, with f(0) = 0.

#### Approach 1: Recursion
**Complexity:** O(kⁿ) time, O(n) stack.

**C++**
```cpp
int frogKRec(int i, vector<int>& h, int k) {
    if (i == 0) return 0;
    int best = INT_MAX;
    for (int j = 1; j <= k && i - j >= 0; j++)
        best = min(best, frogKRec(i - j, h, k) + abs(h[i] - h[i - j]));
    return best;
}
```

**Java**
```java
class Solution {
    static int frogKRec(int i, int[] h, int k) {
        if (i == 0) return 0;
        int best = Integer.MAX_VALUE;
        for (int j = 1; j <= k && i - j >= 0; j++)
            best = Math.min(best, frogKRec(i - j, h, k) + Math.abs(h[i] - h[i - j]));
        return best;
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·k) time, O(n) + O(n) stack.

**C++**
```cpp
int frogKMemo(int i, vector<int>& h, int k, vector<int>& dp) {
    if (i == 0) return 0;
    if (dp[i] != -1) return dp[i];
    int best = INT_MAX;
    for (int j = 1; j <= k && i - j >= 0; j++)
        best = min(best, frogKMemo(i - j, h, k, dp) + abs(h[i] - h[i - j]));
    return dp[i] = best;
}
int frogJumpKMemo(vector<int>& h, int k) {
    vector<int> dp(h.size(), -1);
    return frogKMemo(h.size() - 1, h, k, dp);
}
```

**Java**
```java
class Solution {
    static int frogKMemo(int i, int[] h, int k, int[] dp) {
        if (i == 0) return 0;
        if (dp[i] != -1) return dp[i];
        int best = Integer.MAX_VALUE;
        for (int j = 1; j <= k && i - j >= 0; j++)
            best = Math.min(best, frogKMemo(i - j, h, k, dp) + Math.abs(h[i] - h[i - j]));
        return dp[i] = best;
    }
    static int frogJumpKMemo(int[] h, int k) {
        int[] dp = new int[h.length];
        Arrays.fill(dp, -1);
        return frogKMemo(h.length - 1, h, k, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·k) time, O(n) space.

**C++**
```cpp
int frogJumpK(vector<int>& h, int k) {
    int n = h.size();
    vector<int> dp(n, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= k && i - j >= 0; j++)
            dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
    return dp[n - 1];
}
```

**Java**
```java
class Solution {
    static int frogJumpK(int[] h, int k) {
        int n = h.length;
        int[] dp = new int[n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;
        for (int i = 1; i < n; i++)
            for (int j = 1; j <= k && i - j >= 0; j++)
                dp[i] = Math.min(dp[i], dp[i - j] + Math.abs(h[i] - h[i - j]));
        return dp[n - 1];
    }
}
```

#### Approach 4: Space optimisation — a window of the last k values
Only `dp[i−k … i−1]` is needed, so a circular buffer of size `k` gives O(k) space. (The video points out this can't shrink to O(1) the way plain Frog Jump does, because k values must be remembered.)

**Complexity:** O(n·k) time, O(k) space.

**C++**
```cpp
int frogJumpKSpace(vector<int>& h, int k) {
    int n = h.size();
    vector<int> win(k, INT_MAX);              // win[i % k] = dp[i]
    win[0] = 0;
    for (int i = 1; i < n; i++) {
        int best = INT_MAX;
        for (int j = 1; j <= k && i - j >= 0; j++)
            best = min(best, win[(i - j) % k] + abs(h[i] - h[i - j]));
        win[i % k] = best;
    }
    return win[(n - 1) % k];
}
```

**Java**
```java
class Solution {
    static int frogJumpKSpace(int[] h, int k) {
        int n = h.length;
        int[] win = new int[k];
        Arrays.fill(win, Integer.MAX_VALUE);
        win[0] = 0;
        for (int i = 1; i < n; i++) {
            int best = Integer.MAX_VALUE;
            for (int j = 1; j <= k && i - j >= 0; j++)
                best = Math.min(best, win[(i - j) % k] + Math.abs(h[i] - h[i - j]));
            win[i % k] = best;
        }
        return win[(n - 1) % k];
    }
}
```

#### Key Takeaways
- Generalising from 2 choices to k choices adds a loop over the choices. The space needed is the length of the recurrence's look-back window.

[↑ Contents](#contents) · [← Previous](#p386) · [Next →](#p388)

---

<a id="p388"></a>

### 4. Maximum sum of non adjacent elements

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › 1D DP | Core | No | [LeetCode](https://leetcode.com/problems/house-robber/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/maximum-sum-of-non-adjacent-elements) | [Watch](https://youtu.be/GrMBfJNk_NY) |

#### Problem Statement
Return the maximum sum of a subsequence with **no two adjacent** elements.

```text
nums = [2, 1, 4, 9]      ->  11   (2 + 9)
nums = [1, 2, 4]         ->  5    (1 + 4)
nums = [2, 7, 9, 3, 1]   ->  12   (2 + 9 + 1)
```

#### Intuition — pick or not pick
At index `i`:
- **pick** it: `nums[i] + f(i−2)`, since you can't take its neighbour;
- **not pick** it: `f(i−1)`.

So **f(i) = max(nums[i] + f(i−2), f(i−1))**, with f(0) = nums[0] and f(negative) = 0.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int nonAdjRec(int i, vector<int>& a) {
    if (i == 0) return a[0];
    if (i < 0) return 0;
    int pick = a[i] + nonAdjRec(i - 2, a);
    int notPick = nonAdjRec(i - 1, a);
    return max(pick, notPick);
}
```

**Java**
```java
class Solution {
    static int nonAdjRec(int i, int[] a) {
        if (i == 0) return a[0];
        if (i < 0) return 0;
        int pick = a[i] + nonAdjRec(i - 2, a);
        int notPick = nonAdjRec(i - 1, a);
        return Math.max(pick, notPick);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n) time, O(n) + O(n) stack.

**C++**
```cpp
int nonAdjMemo(int i, vector<int>& a, vector<int>& dp) {
    if (i == 0) return a[0];
    if (i < 0) return 0;
    if (dp[i] != -1) return dp[i];
    return dp[i] = max(a[i] + nonAdjMemo(i - 2, a, dp), nonAdjMemo(i - 1, a, dp));
}
int maximumNonAdjacentSumMemo(vector<int>& a) {
    vector<int> dp(a.size(), -1);
    return nonAdjMemo(a.size() - 1, a, dp);
}
```

**Java**
```java
class Solution {
    static int nonAdjMemo(int i, int[] a, int[] dp) {
        if (i == 0) return a[0];
        if (i < 0) return 0;
        if (dp[i] != -1) return dp[i];
        return dp[i] = Math.max(a[i] + nonAdjMemo(i - 2, a, dp), nonAdjMemo(i - 1, a, dp));
    }
    static int maximumNonAdjacentSumMemo(int[] a) {
        int[] dp = new int[a.length];
        Arrays.fill(dp, -1);
        return nonAdjMemo(a.length - 1, a, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int maximumNonAdjacentSumTab(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n);
    dp[0] = a[0];
    for (int i = 1; i < n; i++) {
        int pick = a[i] + (i > 1 ? dp[i - 2] : 0);
        dp[i] = max(pick, dp[i - 1]);
    }
    return dp[n - 1];
}
```

**Java**
```java
class Solution {
    static int maximumNonAdjacentSumTab(int[] a) {
        int n = a.length;
        int[] dp = new int[n];
        dp[0] = a[0];
        for (int i = 1; i < n; i++) {
            int pick = a[i] + (i > 1 ? dp[i - 2] : 0);
            dp[i] = Math.max(pick, dp[i - 1]);
        }
        return dp[n - 1];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int maximumNonAdjacentSum(vector<int>& a) {
    int prev = a[0], prev2 = 0;
    for (size_t i = 1; i < a.size(); i++) {
        int cur = max(a[i] + prev2, prev);
        prev2 = prev;
        prev = cur;
    }
    return prev;
}
```

**Java**
```java
class Solution {
    static int maximumNonAdjacentSum(int[] a) {
        int prev = a[0], prev2 = 0;
        for (int i = 1; i < a.length; i++) {
            int cur = Math.max(a[i] + prev2, prev);
            prev2 = prev;
            prev = cur;
        }
        return prev;
    }
}
```

#### Key Takeaways
- Pick or not pick is the template for subsequence DP. This is LeetCode 198, House Robber.

[↑ Contents](#contents) · [← Previous](#p387) · [Next →](#p389)

---

<a id="p389"></a>

### 5. House robber

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › 1D DP | Core | No | [LeetCode](https://leetcode.com/problems/house-robber/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/house-robber-ii) | [Watch](https://youtu.be/3WaxQMELSkw) |

#### Problem Statement
**House Robber II:** the houses stand in a **circle**, so the first and last houses are adjacent. Return the maximum loot without robbing two adjacent houses. Striver's DP 6 covers this circular version.

```text
nums = [2, 3, 2]         ->  3
nums = [1, 2, 3, 1]      ->  4
nums = [1, 5, 1, 2, 6]   ->  11   (5 + 6)
```

#### Intuition
The first and last houses can't **both** be robbed, so solve the linear problem twice and take the larger answer:
- once **excluding the last** house: `nums[0 … n−2]`;
- once **excluding the first** house: `nums[1 … n−1]`.

Edge case: a single house means you just rob it.

#### Approach 1: Recursion (linear helper on a range)
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int robRangeRec(int i, int lo, vector<int>& a) {     // best in a[lo..i]
    if (i < lo) return 0;
    if (i == lo) return a[lo];
    return max(a[i] + robRangeRec(i - 2, lo, a), robRangeRec(i - 1, lo, a));
}
int robCircularRec(vector<int>& a) {
    int n = a.size();
    if (n == 1) return a[0];
    vector<int> skipFirst(a.begin() + 1, a.end()), skipLast(a.begin(), a.end() - 1);
    return max(robRangeRec(n - 2, 0, skipFirst), robRangeRec(n - 2, 0, skipLast));
}
```

**Java**
```java
class Solution {
    static int robRangeRec(int i, int lo, int[] a) {
        if (i < lo) return 0;
        if (i == lo) return a[lo];
        return Math.max(a[i] + robRangeRec(i - 2, lo, a), robRangeRec(i - 1, lo, a));
    }
    static int robCircularRec(int[] a) {
        int n = a.length;
        if (n == 1) return a[0];
        return Math.max(robRangeRec(n - 1, 1, a), robRangeRec(n - 2, 0, a));
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int robMemo(int i, vector<int>& a, vector<int>& dp) {
    if (i == 0) return a[0];
    if (i < 0) return 0;
    if (dp[i] != -1) return dp[i];
    return dp[i] = max(a[i] + robMemo(i - 2, a, dp), robMemo(i - 1, a, dp));
}
int robCircularMemo(vector<int>& a) {
    int n = a.size();
    if (n == 1) return a[0];
    vector<int> t1(a.begin() + 1, a.end()), t2(a.begin(), a.end() - 1);
    vector<int> d1(n - 1, -1), d2(n - 1, -1);
    return max(robMemo(n - 2, t1, d1), robMemo(n - 2, t2, d2));
}
```

**Java**
```java
class Solution {
    static int robMemo(int i, int[] a, int[] dp) {
        if (i == 0) return a[0];
        if (i < 0) return 0;
        if (dp[i] != -1) return dp[i];
        return dp[i] = Math.max(a[i] + robMemo(i - 2, a, dp), robMemo(i - 1, a, dp));
    }
    static int robCircularMemo(int[] a) {
        int n = a.length;
        if (n == 1) return a[0];
        int[] t1 = Arrays.copyOfRange(a, 1, n), t2 = Arrays.copyOfRange(a, 0, n - 1);
        int[] d1 = new int[n - 1], d2 = new int[n - 1];
        Arrays.fill(d1, -1); Arrays.fill(d2, -1);
        return Math.max(robMemo(n - 2, t1, d1), robMemo(n - 2, t2, d2));
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int robLinearTab(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n);
    dp[0] = a[0];
    for (int i = 1; i < n; i++) dp[i] = max(a[i] + (i > 1 ? dp[i - 2] : 0), dp[i - 1]);
    return dp[n - 1];
}
int robCircularTab(vector<int>& a) {
    int n = a.size();
    if (n == 1) return a[0];
    vector<int> t1(a.begin() + 1, a.end()), t2(a.begin(), a.end() - 1);
    return max(robLinearTab(t1), robLinearTab(t2));
}
```

**Java**
```java
class Solution {
    static int robLinearTab(int[] a) {
        int n = a.length;
        int[] dp = new int[n];
        dp[0] = a[0];
        for (int i = 1; i < n; i++) dp[i] = Math.max(a[i] + (i > 1 ? dp[i - 2] : 0), dp[i - 1]);
        return dp[n - 1];
    }
    static int robCircularTab(int[] a) {
        int n = a.length;
        if (n == 1) return a[0];
        return Math.max(robLinearTab(Arrays.copyOfRange(a, 1, n)), robLinearTab(Arrays.copyOfRange(a, 0, n - 1)));
    }
}
```

#### Approach 4: Space optimisation (as in the video)
**Complexity:** O(n) time, O(1) extra space (plus the O(n) copies, which you can avoid by passing index ranges).

**C++**
```cpp
long long robLinear(const vector<int>& a, int lo, int hi) {   // inclusive range
    long long prev = a[lo], prev2 = 0;
    for (int i = lo + 1; i <= hi; i++) {
        long long cur = max(a[i] + prev2, prev);
        prev2 = prev;
        prev = cur;
    }
    return prev;
}
long long robCircular(vector<int>& a) {
    int n = a.size();
    if (n == 1) return a[0];
    return max(robLinear(a, 1, n - 1), robLinear(a, 0, n - 2));
}
```

**Java**
```java
class Solution {
    static long robLinear(int[] a, int lo, int hi) {
        long prev = a[lo], prev2 = 0;
        for (int i = lo + 1; i <= hi; i++) {
            long cur = Math.max(a[i] + prev2, prev);
            prev2 = prev;
            prev = cur;
        }
        return prev;
    }
    static long robCircular(int[] a) {
        int n = a.length;
        if (n == 1) return a[0];
        return Math.max(robLinear(a, 1, n - 1), robLinear(a, 0, n - 2));
    }
}
```

#### Key Takeaways
- Break a circular constraint into two linear cases: skip the first element, or skip the last.

[↑ Contents](#contents) · [← Previous](#p388) · [Next →](#p390)

---

## 2D DP

<a id="p390"></a>

### 6. Ninja's training

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › 2D DP | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/ninjas-training) | [Watch](https://youtu.be/AE39gJYuRog) |

#### Problem Statement
**Ninja's training:** for `n` days, the ninja does one of 3 activities each day, with `points[day][activity]` merit points. The same activity can't be done on **two consecutive days**. Maximise the total points.

```text
points = [[1,2,5],[3,1,1],[3,3,3]]   ->  11   (5 + 3 + 3)
points = [[10,40,70],[20,50,80],[30,60,90]]   ->  210   (70 + 50 + 90)
```

#### Intuition — the state needs to include the last activity
- **Why greedy fails.** Taking the best activity each day can block a bigger gain the next day.
- **The state.** `f(day, last)` is the maximum points for days `0 … day`, given that the activity done on `day + 1` is `last`. `last = 3` means "no restriction".

  **f(day, last) = max over task ≠ last of points[day][task] + f(day−1, task)**
- **The base case** is `f(0, last)`, the maximum over `task ≠ last` of `points[0][task]`.

#### Approach 1: Recursion
**Complexity:** O(3ⁿ) time, O(n) stack.

**C++**
```cpp
int ninjaRec(int day, int last, vector<vector<int>>& p) {
    int best = 0;
    for (int task = 0; task < 3; task++) {
        if (task == last) continue;
        int pts = p[day][task] + (day == 0 ? 0 : ninjaRec(day - 1, task, p));
        best = max(best, pts);
    }
    return best;
}
int ninjaTrainingRec(vector<vector<int>>& p) { return ninjaRec(p.size() - 1, 3, p); }
```

**Java**
```java
class Solution {
    static int ninjaRec(int day, int last, int[][] p) {
        int best = 0;
        for (int task = 0; task < 3; task++) {
            if (task == last) continue;
            int pts = p[day][task] + (day == 0 ? 0 : ninjaRec(day - 1, task, p));
            best = Math.max(best, pts);
        }
        return best;
    }
    static int ninjaTrainingRec(int[][] p) { return ninjaRec(p.length - 1, 3, p); }
}
```

#### Approach 2: Memoization — dp[n][4]
**Complexity:** O(n·4·3) time, O(n·4) + O(n) stack.

**C++**
```cpp
int ninjaMemo(int day, int last, vector<vector<int>>& p, vector<vector<int>>& dp) {
    if (dp[day][last] != -1) return dp[day][last];
    int best = 0;
    for (int task = 0; task < 3; task++) {
        if (task == last) continue;
        int pts = p[day][task] + (day == 0 ? 0 : ninjaMemo(day - 1, task, p, dp));
        best = max(best, pts);
    }
    return dp[day][last] = best;
}
int ninjaTrainingMemo(vector<vector<int>>& p) {
    vector<vector<int>> dp(p.size(), vector<int>(4, -1));
    return ninjaMemo(p.size() - 1, 3, p, dp);
}
```

**Java**
```java
class Solution {
    static int ninjaMemo(int day, int last, int[][] p, int[][] dp) {
        if (dp[day][last] != -1) return dp[day][last];
        int best = 0;
        for (int task = 0; task < 3; task++) {
            if (task == last) continue;
            int pts = p[day][task] + (day == 0 ? 0 : ninjaMemo(day - 1, task, p, dp));
            best = Math.max(best, pts);
        }
        return dp[day][last] = best;
    }
    static int ninjaTrainingMemo(int[][] p) {
        int[][] dp = new int[p.length][4];
        for (int[] r : dp) Arrays.fill(r, -1);
        return ninjaMemo(p.length - 1, 3, p, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·4·3) time, O(n·4) space.

**C++**
```cpp
int ninjaTrainingTab(vector<vector<int>>& p) {
    int n = p.size();
    vector<vector<int>> dp(n, vector<int>(4, 0));
    for (int last = 0; last < 4; last++)
        for (int task = 0; task < 3; task++)
            if (task != last) dp[0][last] = max(dp[0][last], p[0][task]);
    for (int day = 1; day < n; day++)
        for (int last = 0; last < 4; last++)
            for (int task = 0; task < 3; task++)
                if (task != last) dp[day][last] = max(dp[day][last], p[day][task] + dp[day - 1][task]);
    return dp[n - 1][3];
}
```

**Java**
```java
class Solution {
    static int ninjaTrainingTab(int[][] p) {
        int n = p.length;
        int[][] dp = new int[n][4];
        for (int last = 0; last < 4; last++)
            for (int task = 0; task < 3; task++)
                if (task != last) dp[0][last] = Math.max(dp[0][last], p[0][task]);
        for (int day = 1; day < n; day++)
            for (int last = 0; last < 4; last++)
                for (int task = 0; task < 3; task++)
                    if (task != last) dp[day][last] = Math.max(dp[day][last], p[day][task] + dp[day - 1][task]);
        return dp[n - 1][3];
    }
}
```

#### Approach 4: Space optimisation — keep only the previous day's 4 values
**Complexity:** O(n·4·3) time, O(4) space.

**C++**
```cpp
int ninjaTraining(vector<vector<int>>& p) {
    int n = p.size();
    vector<int> prev(4, 0);
    for (int last = 0; last < 4; last++)
        for (int task = 0; task < 3; task++)
            if (task != last) prev[last] = max(prev[last], p[0][task]);
    for (int day = 1; day < n; day++) {
        vector<int> cur(4, 0);
        for (int last = 0; last < 4; last++)
            for (int task = 0; task < 3; task++)
                if (task != last) cur[last] = max(cur[last], p[day][task] + prev[task]);
        prev = cur;
    }
    return prev[3];
}
```

**Java**
```java
class Solution {
    static int ninjaTraining(int[][] p) {
        int n = p.length;
        int[] prev = new int[4];
        for (int last = 0; last < 4; last++)
            for (int task = 0; task < 3; task++)
                if (task != last) prev[last] = Math.max(prev[last], p[0][task]);
        for (int day = 1; day < n; day++) {
            int[] cur = new int[4];
            for (int last = 0; last < 4; last++)
                for (int task = 0; task < 3; task++)
                    if (task != last) cur[last] = Math.max(cur[last], p[day][task] + prev[task]);
            prev = cur;
        }
        return prev[3];
    }
}
```

#### Key Takeaways
- When the previous choice restricts the current one, add it to the state: `(day, last)`. This is the entry point to 2-D DP.

[↑ Contents](#contents) · [← Previous](#p389) · [Next →](#p391)

---

## DP on grids

<a id="p391"></a>

### 7. Grid unique paths

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on grids | Core | No | [LeetCode](https://leetcode.com/problems/unique-paths/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/grid-unique-paths) | [Watch](https://youtu.be/sdE0A2Oxofw) |

#### Problem Statement
A robot starts at the top-left of an `m × n` grid and may move only **right** or **down**. How many unique paths reach the bottom-right?

```text
m = 3, n = 7  ->  28
m = 3, n = 2  ->  3   (R D D, D R D, D D R)
```

#### Intuition
Think backwards from the destination `(m−1, n−1)`. Every path into `(i, j)` came either from **above** `(i−1, j)` or from the **left** `(i, j−1)`:

  **f(i, j) = f(i−1, j) + f(i, j−1)**, with f(0, 0) = 1 and f(out of grid) = 0.

The video sets out the steps for writing any grid DP:
1. Express the problem in terms of `(i, j)`.
2. Do all the moves.
3. Combine the results: sum for "count", min/max for "best".
4. Write the base cases.

#### Approach 1: Recursion
**Complexity:** O(2^(m+n)) time, O(m+n) path-length stack.

**C++**
```cpp
int pathsRec(int i, int j) {
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    return pathsRec(i - 1, j) + pathsRec(i, j - 1);
}
int uniquePathsRec(int m, int n) { return pathsRec(m - 1, n - 1); }
```

**Java**
```java
class Solution {
    static int pathsRec(int i, int j) {
        if (i == 0 && j == 0) return 1;
        if (i < 0 || j < 0) return 0;
        return pathsRec(i - 1, j) + pathsRec(i, j - 1);
    }
    static int uniquePathsRec(int m, int n) { return pathsRec(m - 1, n - 1); }
}
```

#### Approach 2: Memoization
**Complexity:** O(m·n) time, O(m·n) + O(m+n) stack.

**C++**
```cpp
int pathsMemo(int i, int j, vector<vector<int>>& dp) {
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    return dp[i][j] = pathsMemo(i - 1, j, dp) + pathsMemo(i, j - 1, dp);
}
int uniquePathsMemo(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return pathsMemo(m - 1, n - 1, dp);
}
```

**Java**
```java
class Solution {
    static int pathsMemo(int i, int j, int[][] dp) {
        if (i == 0 && j == 0) return 1;
        if (i < 0 || j < 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = pathsMemo(i - 1, j, dp) + pathsMemo(i, j - 1, dp);
    }
    static int uniquePathsMemo(int m, int n) {
        int[][] dp = new int[m][n];
        for (int[] r : dp) Arrays.fill(r, -1);
        return pathsMemo(m - 1, n - 1, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(m·n) time, O(m·n) space.

**C++**
```cpp
int uniquePathsTab(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) { dp[i][j] = 1; continue; }
            int up = i > 0 ? dp[i - 1][j] : 0;
            int left = j > 0 ? dp[i][j - 1] : 0;
            dp[i][j] = up + left;
        }
    return dp[m - 1][n - 1];
}
```

**Java**
```java
class Solution {
    static int uniquePathsTab(int m, int n) {
        int[][] dp = new int[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) { dp[i][j] = 1; continue; }
                int up = i > 0 ? dp[i - 1][j] : 0;
                int left = j > 0 ? dp[i][j - 1] : 0;
                dp[i][j] = up + left;
            }
        return dp[m - 1][n - 1];
    }
}
```

#### Approach 4: Space optimisation — previous row only
`dp[i][j]` reads only the row above (`prev[j]`) and the current row's left cell (`cur[j−1]`).

**Complexity:** O(m·n) time, O(n) space.

**C++**
```cpp
int uniquePaths(int m, int n) {
    vector<int> prev(n, 0);
    for (int i = 0; i < m; i++) {
        vector<int> cur(n, 0);
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) { cur[j] = 1; continue; }
            cur[j] = prev[j] + (j > 0 ? cur[j - 1] : 0);
        }
        prev = cur;
    }
    return prev[n - 1];
}
```

**Java**
```java
class Solution {
    static int uniquePaths(int m, int n) {
        int[] prev = new int[n];
        for (int i = 0; i < m; i++) {
            int[] cur = new int[n];
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) { cur[j] = 1; continue; }
                cur[j] = prev[j] + (j > 0 ? cur[j - 1] : 0);
            }
            prev = cur;
        }
        return prev[n - 1];
    }
}
```

#### Approach 5: Combinatorics — C(m+n−2, m−1)
The video only mentions this one in passing. Every path is a sequence of `m−1` downs and `n−1` rights, and you choose where the downs go. Compute the binomial incrementally to avoid overflow.

**Complexity:** O(min(m, n)) time, O(1) space.

**C++**
```cpp
int uniquePathsNcr(int m, int n) {
    int N = m + n - 2, r = min(m, n) - 1;
    long long res = 1;
    for (int i = 1; i <= r; i++) res = res * (N - r + i) / i;   // stays an integer at every step
    return (int)res;
}
```

**Java**
```java
class Solution {
    static int uniquePathsNcr(int m, int n) {
        int N = m + n - 2, r = Math.min(m, n) - 1;
        long res = 1;
        for (int i = 1; i <= r; i++) res = res * (N - r + i) / i;
        return (int) res;
    }
}
```

#### Edge Cases & Pitfalls
- A 1 × n or m × 1 grid has exactly 1 path.
- In the incremental binomial, multiply **before** dividing so every intermediate value stays an exact integer.

#### Key Takeaways
- Grid DP template: f(i, j) from (up, left); the base is at (0, 0) and out-of-bounds returns a neutral value.

[↑ Contents](#contents) · [← Previous](#p390) · [Next →](#p392)

---

<a id="p392"></a>

### 8. Unique paths II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on grids | Pro | No | [LeetCode](https://leetcode.com/problems/unique-paths-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/unique-paths-ii-obstacles) | [Watch](https://youtu.be/TmhpgXScLyY) |

#### Problem Statement
**Unique Paths II:** same as Unique Paths, but some cells are obstacles (`grid[i][j] = 1` on LeetCode). Paths can't pass through them. Count the paths from top-left to bottom-right.

```text
grid = [[0,0,0],
        [0,1,0],
        [0,0,0]]   ->  2
grid = [[0,1],[0,0]]  ->  1
```

#### Intuition
It's the same recursion as Unique Paths, with one extra base case: **a dead (obstacle) cell contributes 0 paths**. Check it first, before the `(0, 0)` base case, so that an obstacle at the start gives 0.

The video's Code Studio version marks dead cells as `-1` and asks for the answer **mod 1e9+7**. The LeetCode version uses `1` and needs no mod.

#### Approach 1: Recursion
**Complexity:** O(2^(m+n)) time, O(m+n) stack.

**C++**
```cpp
int obsRec(int i, int j, vector<vector<int>>& g) {
    if (i < 0 || j < 0) return 0;
    if (g[i][j] == 1) return 0;                 // dead cell
    if (i == 0 && j == 0) return 1;
    return obsRec(i - 1, j, g) + obsRec(i, j - 1, g);
}
```

**Java**
```java
class Solution {
    static int obsRec(int i, int j, int[][] g) {
        if (i < 0 || j < 0) return 0;
        if (g[i][j] == 1) return 0;
        if (i == 0 && j == 0) return 1;
        return obsRec(i - 1, j, g) + obsRec(i, j - 1, g);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(m·n) time, O(m·n) + O(m+n) stack.

**C++**
```cpp
int obsMemo(int i, int j, vector<vector<int>>& g, vector<vector<int>>& dp) {
    if (i < 0 || j < 0) return 0;
    if (g[i][j] == 1) return 0;
    if (i == 0 && j == 0) return 1;
    if (dp[i][j] != -1) return dp[i][j];
    return dp[i][j] = obsMemo(i - 1, j, g, dp) + obsMemo(i, j - 1, g, dp);
}
int uniquePathsWithObstaclesMemo(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return obsMemo(m - 1, n - 1, g, dp);
}
```

**Java**
```java
class Solution {
    static int obsMemo(int i, int j, int[][] g, int[][] dp) {
        if (i < 0 || j < 0) return 0;
        if (g[i][j] == 1) return 0;
        if (i == 0 && j == 0) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = obsMemo(i - 1, j, g, dp) + obsMemo(i, j - 1, g, dp);
    }
    static int uniquePathsWithObstaclesMemo(int[][] g) {
        int m = g.length, n = g[0].length;
        int[][] dp = new int[m][n];
        for (int[] r : dp) Arrays.fill(r, -1);
        return obsMemo(m - 1, n - 1, g, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(m·n) time, O(m·n) space.

**C++**
```cpp
int uniquePathsWithObstaclesTab(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 1) { dp[i][j] = 0; continue; }
            if (i == 0 && j == 0) { dp[i][j] = 1; continue; }
            dp[i][j] = (i > 0 ? dp[i - 1][j] : 0) + (j > 0 ? dp[i][j - 1] : 0);
        }
    return dp[m - 1][n - 1];
}
```

**Java**
```java
class Solution {
    static int uniquePathsWithObstaclesTab(int[][] g) {
        int m = g.length, n = g[0].length;
        int[][] dp = new int[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (g[i][j] == 1) { dp[i][j] = 0; continue; }
                if (i == 0 && j == 0) { dp[i][j] = 1; continue; }
                dp[i][j] = (i > 0 ? dp[i - 1][j] : 0) + (j > 0 ? dp[i][j - 1] : 0);
            }
        return dp[m - 1][n - 1];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(m·n) time, O(n) space.

**C++**
```cpp
int uniquePathsWithObstacles(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<int> prev(n, 0);
    for (int i = 0; i < m; i++) {
        vector<int> cur(n, 0);
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 1) cur[j] = 0;
            else if (i == 0 && j == 0) cur[j] = 1;
            else cur[j] = prev[j] + (j > 0 ? cur[j - 1] : 0);
        }
        prev = cur;
    }
    return prev[n - 1];
}
```

**Java**
```java
class Solution {
    static int uniquePathsWithObstacles(int[][] g) {
        int m = g.length, n = g[0].length;
        int[] prev = new int[n];
        for (int i = 0; i < m; i++) {
            int[] cur = new int[n];
            for (int j = 0; j < n; j++) {
                if (g[i][j] == 1) cur[j] = 0;
                else if (i == 0 && j == 0) cur[j] = 1;
                else cur[j] = prev[j] + (j > 0 ? cur[j - 1] : 0);
            }
            prev = cur;
        }
        return prev[n - 1];
    }
}
```

#### Edge Cases & Pitfalls
- An obstacle on the start or the end cell means 0 paths, so check the obstacle **before** the `(0, 0)` base case.
- For the Code Studio variant, take `% 1e9+7` every time you add.

#### Key Takeaways
- Obstacles are just one more base case. The rest of the grid DP is unchanged.

[↑ Contents](#contents) · [← Previous](#p391) · [Next →](#p393)

---

<a id="p393"></a>

### 9. Minimum Falling Path Sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on grids | Core | No | [LeetCode](https://leetcode.com/problems/minimum-falling-path-sum/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/minimum-falling-path-sum) | [Watch](https://youtu.be/N_aJ5qQbYA0) |

> **Video note:** the sheet's link for this row points to *DP 10 — Minimum Path Sum in Grid*. The problem named here is covered in *DP 12 — Minimum/Maximum Falling Path Sum*, and these notes follow DP 12. Minimum Path Sum from DP 10 is covered in full at the end, under "Related problem".

#### Problem Statement
Given an `n × m` matrix, start at **any cell of the first row** and end at **any cell of the last row**. From `(i, j)` you may move to `(i+1, j−1)`, `(i+1, j)` or `(i+1, j+1)`. Return the **minimum** path sum. LeetCode 931 asks for the minimum; the video's Code Studio version asks for the maximum and is otherwise identical.

```text
matrix = [[2,1,3],
          [6,5,4],
          [7,8,9]]   ->  13   (1 -> 5 -> 7  or  1 -> 4 -> 8)
```

#### Intuition — variable start and variable end
This is the first grid problem in the series with a **variable starting point and a variable ending point**:
- **Recurrence.** Recurse up from each cell of the last row: f(i, j) = `a[i][j] + min(f(i−1, j), f(i−1, j−1), f(i−1, j+1))`.
- **Base cases.** `i == 0` returns `a[0][j]`. A column outside the grid returns **+∞** (1e9) so that path is never chosen. For the maximum version, return −1e9 instead.
- **Answer.** min over j of f(n−1, j).

#### Approach 1: Recursion
**Complexity:** O(3ⁿ) per start, O(n) stack.

**C++**
```cpp
int fallRec(int i, int j, vector<vector<int>>& a) {
    if (j < 0 || j >= (int)a[0].size()) return 1e9;
    if (i == 0) return a[0][j];
    int up = fallRec(i - 1, j, a), ld = fallRec(i - 1, j - 1, a), rd = fallRec(i - 1, j + 1, a);
    return a[i][j] + min({up, ld, rd});
}
int minFallingPathSumRec(vector<vector<int>>& a) {
    int n = a.size(), m = a[0].size(), best = INT_MAX;
    for (int j = 0; j < m; j++) best = min(best, fallRec(n - 1, j, a));
    return best;
}
```

**Java**
```java
class Solution {
    static int fallRec(int i, int j, int[][] a) {
        if (j < 0 || j >= a[0].length) return (int) 1e9;
        if (i == 0) return a[0][j];
        int up = fallRec(i - 1, j, a), ld = fallRec(i - 1, j - 1, a), rd = fallRec(i - 1, j + 1, a);
        return a[i][j] + Math.min(up, Math.min(ld, rd));
    }
    static int minFallingPathSumRec(int[][] a) {
        int n = a.length, m = a[0].length, best = Integer.MAX_VALUE;
        for (int j = 0; j < m; j++) best = Math.min(best, fallRec(n - 1, j, a));
        return best;
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·m) time, O(n·m) + O(n) stack.

**C++**
```cpp
int fallMemo(int i, int j, vector<vector<int>>& a, vector<vector<int>>& dp) {
    if (j < 0 || j >= (int)a[0].size()) return 1e9;
    if (i == 0) return a[0][j];
    if (dp[i][j] != INT_MIN) return dp[i][j];
    int up = fallMemo(i - 1, j, a, dp), ld = fallMemo(i - 1, j - 1, a, dp), rd = fallMemo(i - 1, j + 1, a, dp);
    return dp[i][j] = a[i][j] + min({up, ld, rd});
}
int minFallingPathSumMemo(vector<vector<int>>& a) {
    int n = a.size(), m = a[0].size(), best = INT_MAX;
    vector<vector<int>> dp(n, vector<int>(m, INT_MIN));   // values can be negative, so don't use -1 as "unset"
    for (int j = 0; j < m; j++) best = min(best, fallMemo(n - 1, j, a, dp));
    return best;
}
```

**Java**
```java
class Solution {
    static int fallMemo(int i, int j, int[][] a, int[][] dp) {
        if (j < 0 || j >= a[0].length) return (int) 1e9;
        if (i == 0) return a[0][j];
        if (dp[i][j] != Integer.MIN_VALUE) return dp[i][j];
        int up = fallMemo(i - 1, j, a, dp), ld = fallMemo(i - 1, j - 1, a, dp), rd = fallMemo(i - 1, j + 1, a, dp);
        return dp[i][j] = a[i][j] + Math.min(up, Math.min(ld, rd));
    }
    static int minFallingPathSumMemo(int[][] a) {
        int n = a.length, m = a[0].length, best = Integer.MAX_VALUE;
        int[][] dp = new int[n][m];
        for (int[] r : dp) Arrays.fill(r, Integer.MIN_VALUE);
        for (int j = 0; j < m; j++) best = Math.min(best, fallMemo(n - 1, j, a, dp));
        return best;
    }
}
```

#### Approach 3: Tabulation
The first row is the base case. Each later cell takes the best of its three upper neighbours.

**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
int minFallingPathSumTab(vector<vector<int>>& a) {
    int n = a.size(), m = a[0].size();
    vector<vector<int>> dp(n, vector<int>(m));
    for (int j = 0; j < m; j++) dp[0][j] = a[0][j];
    for (int i = 1; i < n; i++)
        for (int j = 0; j < m; j++) {
            int up = dp[i - 1][j];
            int ld = j > 0 ? dp[i - 1][j - 1] : 1e9;
            int rd = j + 1 < m ? dp[i - 1][j + 1] : 1e9;
            dp[i][j] = a[i][j] + min({up, ld, rd});
        }
    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
}
```

**Java**
```java
class Solution {
    static int minFallingPathSumTab(int[][] a) {
        int n = a.length, m = a[0].length;
        int[][] dp = new int[n][m];
        for (int j = 0; j < m; j++) dp[0][j] = a[0][j];
        for (int i = 1; i < n; i++)
            for (int j = 0; j < m; j++) {
                int up = dp[i - 1][j];
                int ld = j > 0 ? dp[i - 1][j - 1] : (int) 1e9;
                int rd = j + 1 < m ? dp[i - 1][j + 1] : (int) 1e9;
                dp[i][j] = a[i][j] + Math.min(up, Math.min(ld, rd));
            }
        int best = Integer.MAX_VALUE;
        for (int v : dp[n - 1]) best = Math.min(best, v);
        return best;
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
int minFallingPathSum(vector<vector<int>>& a) {
    int n = a.size(), m = a[0].size();
    vector<int> prev(a[0].begin(), a[0].end());
    for (int i = 1; i < n; i++) {
        vector<int> cur(m);
        for (int j = 0; j < m; j++) {
            int ld = j > 0 ? prev[j - 1] : 1e9;
            int rd = j + 1 < m ? prev[j + 1] : 1e9;
            cur[j] = a[i][j] + min({prev[j], ld, rd});
        }
        prev = cur;
    }
    return *min_element(prev.begin(), prev.end());
}
```

**Java**
```java
class Solution {
    static int minFallingPathSum(int[][] a) {
        int n = a.length, m = a[0].length;
        int[] prev = a[0].clone();
        for (int i = 1; i < n; i++) {
            int[] cur = new int[m];
            for (int j = 0; j < m; j++) {
                int ld = j > 0 ? prev[j - 1] : (int) 1e9;
                int rd = j + 1 < m ? prev[j + 1] : (int) 1e9;
                cur[j] = a[i][j] + Math.min(prev[j], Math.min(ld, rd));
            }
            prev = cur;
        }
        int best = Integer.MAX_VALUE;
        for (int v : prev) best = Math.min(best, v);
        return best;
    }
}
```

#### Related problem: Minimum Path Sum (the DP 10 video the sheet links)
**Problem.** Go from `(0, 0)` to `(n−1, m−1)` moving only **right or down**, and minimise the sum of the cells on the path. For `[[1,3,1],[1,5,1],[4,2,1]]` the answer is `7` (1 → 3 → 1 → 1 → 1). Striver says this was asked in his Microsoft internship interview.

**Recurrence.** f(i, j) = `g[i][j] + min(f(i−1, j), f(i, j−1))`. f(0, 0) = g[0][0], and out of grid = +∞. That big value keeps a path that leaves the grid from ever being chosen. The video stresses using 1e9, not INT_MAX, because adding to INT_MAX overflows.

**Complexity:** recursion O(2^(n+m)); memo and tabulation O(n·m); space-optimised version O(m).

**C++**
```cpp
int mpsRec(int i, int j, vector<vector<int>>& g) {
    if (i == 0 && j == 0) return g[0][0];
    if (i < 0 || j < 0) return 1e9;
    return g[i][j] + min(mpsRec(i - 1, j, g), mpsRec(i, j - 1, g));
}
int mpsMemo(int i, int j, vector<vector<int>>& g, vector<vector<int>>& dp) {
    if (i == 0 && j == 0) return g[0][0];
    if (i < 0 || j < 0) return 1e9;
    if (dp[i][j] != -1) return dp[i][j];
    return dp[i][j] = g[i][j] + min(mpsMemo(i - 1, j, g, dp), mpsMemo(i, j - 1, g, dp));
}
int minPathSumTab(vector<vector<int>>& g) {
    int n = g.size(), m = g[0].size();
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) { dp[i][j] = g[0][0]; continue; }
            int up = i > 0 ? dp[i - 1][j] : 1e9, left = j > 0 ? dp[i][j - 1] : 1e9;
            dp[i][j] = g[i][j] + min(up, left);
        }
    return dp[n - 1][m - 1];
}
int minPathSum(vector<vector<int>>& g) {               // space optimised
    int n = g.size(), m = g[0].size();
    vector<int> prev(m, 1e9);
    for (int i = 0; i < n; i++) {
        vector<int> cur(m);
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) { cur[j] = g[0][0]; continue; }
            int left = j > 0 ? cur[j - 1] : 1e9;
            cur[j] = g[i][j] + min(prev[j], left);
        }
        prev = cur;
    }
    return prev[m - 1];
}
```

**Java**
```java
class Solution {
    static int mpsRec(int i, int j, int[][] g) {
        if (i == 0 && j == 0) return g[0][0];
        if (i < 0 || j < 0) return (int) 1e9;
        return g[i][j] + Math.min(mpsRec(i - 1, j, g), mpsRec(i, j - 1, g));
    }
    static int mpsMemo(int i, int j, int[][] g, int[][] dp) {
        if (i == 0 && j == 0) return g[0][0];
        if (i < 0 || j < 0) return (int) 1e9;
        if (dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = g[i][j] + Math.min(mpsMemo(i - 1, j, g, dp), mpsMemo(i, j - 1, g, dp));
    }
    static int minPathSumTab(int[][] g) {
        int n = g.length, m = g[0].length;
        int[][] dp = new int[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) { dp[i][j] = g[0][0]; continue; }
                int up = i > 0 ? dp[i - 1][j] : (int) 1e9, left = j > 0 ? dp[i][j - 1] : (int) 1e9;
                dp[i][j] = g[i][j] + Math.min(up, left);
            }
        return dp[n - 1][m - 1];
    }
    static int minPathSum(int[][] g) {
        int n = g.length, m = g[0].length;
        int[] prev = new int[m];
        Arrays.fill(prev, (int) 1e9);
        for (int i = 0; i < n; i++) {
            int[] cur = new int[m];
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) { cur[j] = g[0][0]; continue; }
                int left = j > 0 ? cur[j - 1] : (int) 1e9;
                cur[j] = g[i][j] + Math.min(prev[j], left);
            }
            prev = cur;
        }
        return prev[m - 1];
    }
}
```

#### Edge Cases & Pitfalls
- Matrix values can be negative in LC 931, so in the memo table **−1 is a real value**. Use `INT_MIN` (or a separate visited array) to mean "not computed yet".
- Use 1e9, not INT_MAX, for out-of-bounds cells, so that adding a cell value doesn't overflow.
- The maximum variant is the same code with max, −1e9 for out of bounds, and the maximum taken over the last row.

#### Key Takeaways
- With a variable start or end, run the recursion from every candidate end cell, or in tabulation read the whole last row.

[↑ Contents](#contents) · [← Previous](#p392) · [Next →](#p394)

---

<a id="p394"></a>

### 10. Triangle

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on grids | Core | No | [LeetCode](https://leetcode.com/problems/triangle/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/triangle-minimum-path-sum) | [Watch](https://youtu.be/SrP-PiLSYC0) |

#### Problem Statement
**Triangle:** given a triangle array, return the minimum path sum from top to bottom. From row `i`, index `j`, you may move to `j` or `j+1` in row `i+1`.

```text
triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]  ->  11   (2 + 3 + 5 + 1)
triangle = [[-10]]                        ->  -10
```

#### Intuition — fixed start, variable end
The start is fixed at `(0, 0)` but the end can be any cell of the last row. So write the recursion **from the fixed point**, going downwards:

  **f(i, j) = t[i][j] + min(f(i+1, j), f(i+1, j+1))**, base `i == n−1` returns `t[n−1][j]`.

No out-of-bounds checks are needed, because `j+1 ≤ i+1` always exists in the next row. Tabulation therefore runs **bottom-up from the last row**, the opposite direction to the recursion.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int triRec(int i, int j, vector<vector<int>>& t) {
    if (i == (int)t.size() - 1) return t[i][j];
    return t[i][j] + min(triRec(i + 1, j, t), triRec(i + 1, j + 1, t));
}
```

**Java**
```java
class Solution {
    static int triRec(int i, int j, List<List<Integer>> t) {
        if (i == t.size() - 1) return t.get(i).get(j);
        return t.get(i).get(j) + Math.min(triRec(i + 1, j, t), triRec(i + 1, j + 1, t));
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n²) time, O(n²) + O(n) stack.

**C++**
```cpp
int triMemo(int i, int j, vector<vector<int>>& t, vector<vector<int>>& dp) {
    if (i == (int)t.size() - 1) return t[i][j];
    if (dp[i][j] != INT_MIN) return dp[i][j];
    return dp[i][j] = t[i][j] + min(triMemo(i + 1, j, t, dp), triMemo(i + 1, j + 1, t, dp));
}
int minimumTotalMemo(vector<vector<int>>& t) {
    int n = t.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
    return triMemo(0, 0, t, dp);
}
```

**Java**
```java
class Solution {
    static int triMemo(int i, int j, List<List<Integer>> t, Integer[][] dp) {
        if (i == t.size() - 1) return t.get(i).get(j);
        if (dp[i][j] != null) return dp[i][j];
        return dp[i][j] = t.get(i).get(j) + Math.min(triMemo(i + 1, j, t, dp), triMemo(i + 1, j + 1, t, dp));
    }
    static int minimumTotalMemo(List<List<Integer>> t) {
        int n = t.size();
        return triMemo(0, 0, t, new Integer[n][n]);
    }
}
```

#### Approach 3: Tabulation — from the last row up
**Complexity:** O(n²) time, O(n²) space.

**C++**
```cpp
int minimumTotalTab(vector<vector<int>>& t) {
    int n = t.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int j = 0; j < n; j++) dp[n - 1][j] = t[n - 1][j];
    for (int i = n - 2; i >= 0; i--)
        for (int j = i; j >= 0; j--)
            dp[i][j] = t[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
    return dp[0][0];
}
```

**Java**
```java
class Solution {
    static int minimumTotalTab(List<List<Integer>> t) {
        int n = t.size();
        int[][] dp = new int[n][n];
        for (int j = 0; j < n; j++) dp[n - 1][j] = t.get(n - 1).get(j);
        for (int i = n - 2; i >= 0; i--)
            for (int j = i; j >= 0; j--)
                dp[i][j] = t.get(i).get(j) + Math.min(dp[i + 1][j], dp[i + 1][j + 1]);
        return dp[0][0];
    }
}
```

#### Approach 4: Space optimisation — `front` row
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
int minimumTotal(vector<vector<int>>& t) {
    int n = t.size();
    vector<int> front(t[n - 1].begin(), t[n - 1].end());
    for (int i = n - 2; i >= 0; i--) {
        vector<int> cur(i + 1);
        for (int j = i; j >= 0; j--) cur[j] = t[i][j] + min(front[j], front[j + 1]);
        front = cur;
    }
    return front[0];
}
```

**Java**
```java
class Solution {
    static int minimumTotal(List<List<Integer>> t) {
        int n = t.size();
        int[] front = new int[n];
        for (int j = 0; j < n; j++) front[j] = t.get(n - 1).get(j);
        for (int i = n - 2; i >= 0; i--) {
            int[] cur = new int[i + 1];
            for (int j = i; j >= 0; j--) cur[j] = t.get(i).get(j) + Math.min(front[j], front[j + 1]);
            front = cur;
        }
        return front[0];
    }
}
```

#### Edge Cases & Pitfalls
- Values can be negative, so don't use −1 as the "unset" memo marker.
- A single row means the answer is that one element.

#### Key Takeaways
- Write the recursion from the **fixed** end and tabulate from the **variable** end, which is where the base cases are.

[↑ Contents](#contents) · [← Previous](#p393) · [Next →](#p395)

---

<a id="p395"></a>

### 11. Cherry pickup II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on grids | Pro | No | [LeetCode](https://leetcode.com/problems/cherry-pickup-ii/) | [Watch](https://youtu.be/QGfn7JeXK54) |

#### Problem Statement
**Cherry Pickup II / Chocolate Pickup:** in an `r × c` grid, Alice starts at `(0, 0)` and Bob starts at `(0, c−1)`. Each step, **both** move down one row, to column `j−1`, `j` or `j+1`. They collect the value of every cell they visit. If both are on the **same cell**, it is counted **once**. Maximise the total once both reach the last row.

```text
grid = [[3,1,1],
        [2,5,1],
        [1,5,5],
        [2,1,1]]   ->  24   (Alice 3+2+5+2 = 12, Bob 1+5+5+1 = 12)
```

#### Intuition — move both together, 3-D DP
- **Why not solve them separately.** Two independent best paths could double-count shared cells. Move them **simultaneously** instead.
- **The state.** Both are always in the same row `i`, so the state is `(i, j1, j2)`.
- **The transition.** Each step tries 3 × 3 = **9 combinations** of `(dj1, dj2)`.
- **Base cases.**
  - If either column goes out of bounds, return −1e8.
  - At the last row, return `g[i][j1] + g[i][j2]`, counting it once if `j1 == j2`.
- **Recurrence.** f(i, j1, j2) = cell value + max over the 9 moves of f(i+1, j1+d1, j2+d2).

#### Approach 1: Recursion
**Complexity:** O(9ʳ) time, O(r) stack.

**C++**
```cpp
int cherryRec(int i, int j1, int j2, vector<vector<int>>& g) {
    int r = g.size(), c = g[0].size();
    if (j1 < 0 || j1 >= c || j2 < 0 || j2 >= c) return -1e8;
    int here = (j1 == j2) ? g[i][j1] : g[i][j1] + g[i][j2];
    if (i == r - 1) return here;
    int best = -1e8;
    for (int d1 = -1; d1 <= 1; d1++)
        for (int d2 = -1; d2 <= 1; d2++)
            best = max(best, cherryRec(i + 1, j1 + d1, j2 + d2, g));
    return here + best;
}
int cherryPickupRec(vector<vector<int>>& g) { return cherryRec(0, 0, g[0].size() - 1, g); }
```

**Java**
```java
class Solution {
    static int cherryRec(int i, int j1, int j2, int[][] g) {
        int r = g.length, c = g[0].length;
        if (j1 < 0 || j1 >= c || j2 < 0 || j2 >= c) return (int) -1e8;
        int here = (j1 == j2) ? g[i][j1] : g[i][j1] + g[i][j2];
        if (i == r - 1) return here;
        int best = (int) -1e8;
        for (int d1 = -1; d1 <= 1; d1++)
            for (int d2 = -1; d2 <= 1; d2++)
                best = Math.max(best, cherryRec(i + 1, j1 + d1, j2 + d2, g));
        return here + best;
    }
    static int cherryPickupRec(int[][] g) { return cherryRec(0, 0, g[0].length - 1, g); }
}
```

#### Approach 2: Memoization — dp[r][c][c]
**Complexity:** O(r·c·c·9) time, O(r·c·c) + O(r) stack.

**C++**
```cpp
int cherryMemo(int i, int j1, int j2, vector<vector<int>>& g, vector<vector<vector<int>>>& dp) {
    int r = g.size(), c = g[0].size();
    if (j1 < 0 || j1 >= c || j2 < 0 || j2 >= c) return -1e8;
    int here = (j1 == j2) ? g[i][j1] : g[i][j1] + g[i][j2];
    if (i == r - 1) return here;
    if (dp[i][j1][j2] != -1) return dp[i][j1][j2];
    int best = -1e8;
    for (int d1 = -1; d1 <= 1; d1++)
        for (int d2 = -1; d2 <= 1; d2++)
            best = max(best, cherryMemo(i + 1, j1 + d1, j2 + d2, g, dp));
    return dp[i][j1][j2] = here + best;
}
int cherryPickupMemo(vector<vector<int>>& g) {
    int r = g.size(), c = g[0].size();
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));
    return cherryMemo(0, 0, c - 1, g, dp);
}
```

**Java**
```java
class Solution {
    static int cherryMemo(int i, int j1, int j2, int[][] g, int[][][] dp) {
        int r = g.length, c = g[0].length;
        if (j1 < 0 || j1 >= c || j2 < 0 || j2 >= c) return (int) -1e8;
        int here = (j1 == j2) ? g[i][j1] : g[i][j1] + g[i][j2];
        if (i == r - 1) return here;
        if (dp[i][j1][j2] != -1) return dp[i][j1][j2];
        int best = (int) -1e8;
        for (int d1 = -1; d1 <= 1; d1++)
            for (int d2 = -1; d2 <= 1; d2++)
                best = Math.max(best, cherryMemo(i + 1, j1 + d1, j2 + d2, g, dp));
        return dp[i][j1][j2] = here + best;
    }
    static int cherryPickupMemo(int[][] g) {
        int r = g.length, c = g[0].length;
        int[][][] dp = new int[r][c][c];
        for (int[][] a : dp) for (int[] b : a) Arrays.fill(b, -1);
        return cherryMemo(0, 0, c - 1, g, dp);
    }
}
```

#### Approach 3: Tabulation — from the last row up
**Complexity:** O(r·c·c·9) time, O(r·c·c) space.

**C++**
```cpp
int cherryPickupTab(vector<vector<int>>& g) {
    int r = g.size(), c = g[0].size();
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, 0)));
    for (int j1 = 0; j1 < c; j1++)
        for (int j2 = 0; j2 < c; j2++)
            dp[r - 1][j1][j2] = (j1 == j2) ? g[r - 1][j1] : g[r - 1][j1] + g[r - 1][j2];
    for (int i = r - 2; i >= 0; i--)
        for (int j1 = 0; j1 < c; j1++)
            for (int j2 = 0; j2 < c; j2++) {
                int best = -1e8;
                for (int d1 = -1; d1 <= 1; d1++)
                    for (int d2 = -1; d2 <= 1; d2++) {
                        int a = j1 + d1, b = j2 + d2;
                        if (a >= 0 && a < c && b >= 0 && b < c) best = max(best, dp[i + 1][a][b]);
                    }
                int here = (j1 == j2) ? g[i][j1] : g[i][j1] + g[i][j2];
                dp[i][j1][j2] = here + best;
            }
    return dp[0][0][c - 1];
}
```

**Java**
```java
class Solution {
    static int cherryPickupTab(int[][] g) {
        int r = g.length, c = g[0].length;
        int[][][] dp = new int[r][c][c];
        for (int j1 = 0; j1 < c; j1++)
            for (int j2 = 0; j2 < c; j2++)
                dp[r - 1][j1][j2] = (j1 == j2) ? g[r - 1][j1] : g[r - 1][j1] + g[r - 1][j2];
        for (int i = r - 2; i >= 0; i--)
            for (int j1 = 0; j1 < c; j1++)
                for (int j2 = 0; j2 < c; j2++) {
                    int best = (int) -1e8;
                    for (int d1 = -1; d1 <= 1; d1++)
                        for (int d2 = -1; d2 <= 1; d2++) {
                            int a = j1 + d1, b = j2 + d2;
                            if (a >= 0 && a < c && b >= 0 && b < c) best = Math.max(best, dp[i + 1][a][b]);
                        }
                    int here = (j1 == j2) ? g[i][j1] : g[i][j1] + g[i][j2];
                    dp[i][j1][j2] = here + best;
                }
        return dp[0][0][c - 1];
    }
}
```

#### Approach 4: Space optimisation — two 2-D layers (`front`, `cur`)
**Complexity:** O(r·c·c·9) time, O(c·c) space.

**C++**
```cpp
int cherryPickup(vector<vector<int>>& g) {
    int r = g.size(), c = g[0].size();
    vector<vector<int>> front(c, vector<int>(c)), cur(c, vector<int>(c));
    for (int j1 = 0; j1 < c; j1++)
        for (int j2 = 0; j2 < c; j2++)
            front[j1][j2] = (j1 == j2) ? g[r - 1][j1] : g[r - 1][j1] + g[r - 1][j2];
    for (int i = r - 2; i >= 0; i--) {
        for (int j1 = 0; j1 < c; j1++)
            for (int j2 = 0; j2 < c; j2++) {
                int best = -1e8;
                for (int d1 = -1; d1 <= 1; d1++)
                    for (int d2 = -1; d2 <= 1; d2++) {
                        int a = j1 + d1, b = j2 + d2;
                        if (a >= 0 && a < c && b >= 0 && b < c) best = max(best, front[a][b]);
                    }
                cur[j1][j2] = ((j1 == j2) ? g[i][j1] : g[i][j1] + g[i][j2]) + best;
            }
        front = cur;
    }
    return front[0][c - 1];
}
```

**Java**
```java
class Solution {
    static int cherryPickup(int[][] g) {
        int r = g.length, c = g[0].length;
        int[][] front = new int[c][c];
        for (int j1 = 0; j1 < c; j1++)
            for (int j2 = 0; j2 < c; j2++)
                front[j1][j2] = (j1 == j2) ? g[r - 1][j1] : g[r - 1][j1] + g[r - 1][j2];
        for (int i = r - 2; i >= 0; i--) {
            int[][] cur = new int[c][c];
            for (int j1 = 0; j1 < c; j1++)
                for (int j2 = 0; j2 < c; j2++) {
                    int best = (int) -1e8;
                    for (int d1 = -1; d1 <= 1; d1++)
                        for (int d2 = -1; d2 <= 1; d2++) {
                            int a = j1 + d1, b = j2 + d2;
                            if (a >= 0 && a < c && b >= 0 && b < c) best = Math.max(best, front[a][b]);
                        }
                    cur[j1][j2] = ((j1 == j2) ? g[i][j1] : g[i][j1] + g[i][j2]) + best;
                }
            front = cur;
        }
        return front[0][c - 1];
    }
}
```

#### Edge Cases & Pitfalls
- In Java, allocate a **new** `cur` every row, or swap references. Writing `front = cur` and then reusing `cur` would alias the two layers. In C++ `front = cur` copies, so reusing `cur` is fine.
- Count a shared cell only once: `j1 == j2`.
- The out-of-bounds base case returns −1e8, not INT_MIN, so adding to it doesn't overflow.

#### Key Takeaways
- Two agents moving in lockstep share the row index, so the state is `(i, j1, j2)`. A k-agent version needs one column per agent.
- The 2-D → 1-D trick generalises: for 3-D DP, keep two 2-D layers.

[↑ Contents](#contents) · [← Previous](#p394) · [Next →](#p396)

---

<a id="p396"></a>

### 12. Count Square Submatrices with All Ones

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on grids | — | No | [LeetCode](https://leetcode.com/problems/count-square-submatrices-with-all-ones/) | [Watch](https://youtu.be/auS1fynpnjo) |

#### Problem Statement
**Count square submatrices with all ones:** given an `n × m` binary matrix, count every square submatrix that consists only of 1s.

```text
matrix = [[0,1,1,1],
          [1,1,1,1],
          [0,1,1,1]]   ->  15   (10 of size 1, 4 of size 2, 1 of size 3)
matrix = [[1,0,1],
          [1,1,0],
          [1,1,0]]     ->  7    (6 of size 1, 1 of size 2)
```

#### Intuition
Let `dp[i][j]` be the side of the largest all-ones square whose **bottom-right corner** is `(i, j)`. That cell is then the bottom-right corner of exactly `dp[i][j]` squares (sides 1, 2, … dp[i][j]), so **the answer is the sum of all dp values**.
- **If `a[i][j] = 1`:** `dp[i][j] = 1 + min(dp[i−1][j], dp[i][j−1], dp[i−1][j−1])`. A bigger square needs the cells above, to the left, and diagonally above-left to all support it, so the smallest of the three limits it.
- **Otherwise:** `dp[i][j] = 0`.
- **Edges:** the first row and the first column are just `a[i][j]`.

The video presents this directly as tabulation. The recursion, memoization and brute force below aren't in the video and are added for completeness.

#### Approach 1: Brute force — check every square *(not in video)*
For every top-left corner and every side length, extend the square while the new bottom row and right column are all 1s.

**Complexity:** O(n·m·min(n,m)²) time, O(1) space.

**C++**
```cpp
int countSquaresBrute(vector<vector<int>>& a) {
    int n = a.size(), m = a[0].size(), cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; i + k < n && j + k < m; k++) {
                bool ok = true;                       // check new row i+k and new column j+k
                for (int t = 0; t <= k && ok; t++)
                    if (a[i + k][j + t] == 0 || a[i + t][j + k] == 0) ok = false;
                if (!ok) break;
                cnt++;
            }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countSquaresBrute(int[][] a) {
        int n = a.length, m = a[0].length, cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; i + k < n && j + k < m; k++) {
                    boolean ok = true;
                    for (int t = 0; t <= k && ok; t++)
                        if (a[i + k][j + t] == 0 || a[i + t][j + k] == 0) ok = false;
                    if (!ok) break;
                    cnt++;
                }
        return cnt;
    }
}
```

#### Approach 2: Recursion + Memoization — f(i, j) is the largest square ending at (i, j) *(not in video)*
Plain recursion recomputes neighbours exponentially, so it's memoized straight away.

**Complexity:** O(n·m) time, O(n·m) space + stack.

**C++**
```cpp
int sqMemo(int i, int j, vector<vector<int>>& a, vector<vector<int>>& dp) {
    if (i < 0 || j < 0 || a[i][j] == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    return dp[i][j] = 1 + min({sqMemo(i - 1, j, a, dp), sqMemo(i, j - 1, a, dp), sqMemo(i - 1, j - 1, a, dp)});
}
int countSquaresMemo(vector<vector<int>>& a) {
    int n = a.size(), m = a[0].size(), sum = 0;
    vector<vector<int>> dp(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) sum += sqMemo(i, j, a, dp);
    return sum;
}
```

**Java**
```java
class Solution {
    static int sqMemo(int i, int j, int[][] a, int[][] dp) {
        if (i < 0 || j < 0 || a[i][j] == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = 1 + Math.min(sqMemo(i - 1, j, a, dp), Math.min(sqMemo(i, j - 1, a, dp), sqMemo(i - 1, j - 1, a, dp)));
    }
    static int countSquaresMemo(int[][] a) {
        int n = a.length, m = a[0].length, sum = 0;
        int[][] dp = new int[n][m];
        for (int[] r : dp) Arrays.fill(r, -1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) sum += sqMemo(i, j, a, dp);
        return sum;
    }
}
```

#### Approach 3: Tabulation (as in the video)
**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
int countSquaresTab(vector<vector<int>>& a) {
    int n = a.size(), m = a[0].size(), sum = 0;
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int j = 0; j < m; j++) dp[0][j] = a[0][j];
    for (int i = 0; i < n; i++) dp[i][0] = a[i][0];
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            dp[i][j] = a[i][j] == 0 ? 0 : 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) sum += dp[i][j];
    return sum;
}
```

**Java**
```java
class Solution {
    static int countSquaresTab(int[][] a) {
        int n = a.length, m = a[0].length, sum = 0;
        int[][] dp = new int[n][m];
        for (int j = 0; j < m; j++) dp[0][j] = a[0][j];
        for (int i = 0; i < n; i++) dp[i][0] = a[i][0];
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                dp[i][j] = a[i][j] == 0 ? 0 : 1 + Math.min(dp[i - 1][j], Math.min(dp[i][j - 1], dp[i - 1][j - 1]));
        for (int[] r : dp) for (int v : r) sum += v;
        return sum;
    }
}
```

#### Approach 4: Space optimisation — one previous row *(not in video)*
**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
int countSquares(vector<vector<int>>& a) {
    int n = a.size(), m = a[0].size(), sum = 0;
    vector<int> prev(m, 0);
    for (int i = 0; i < n; i++) {
        vector<int> cur(m, 0);
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 0) cur[j] = 0;
            else if (i == 0 || j == 0) cur[j] = 1;
            else cur[j] = 1 + min({prev[j], cur[j - 1], prev[j - 1]});
            sum += cur[j];
        }
        prev = cur;
    }
    return sum;
}
```

**Java**
```java
class Solution {
    static int countSquares(int[][] a) {
        int n = a.length, m = a[0].length, sum = 0;
        int[] prev = new int[m];
        for (int i = 0; i < n; i++) {
            int[] cur = new int[m];
            for (int j = 0; j < m; j++) {
                if (a[i][j] == 0) cur[j] = 0;
                else if (i == 0 || j == 0) cur[j] = 1;
                else cur[j] = 1 + Math.min(prev[j], Math.min(cur[j - 1], prev[j - 1]));
                sum += cur[j];
            }
            prev = cur;
        }
        return sum;
    }
}
```

#### Edge Cases & Pitfalls
- A matrix of all 0s gives 0. A single 1 gives 1.
- The same dp solves **Maximal Square** (LC 221): take the maximum of dp instead of the sum, and the answer is that maximum squared.

#### Key Takeaways
- "The largest square ending here" equals "the number of squares ending here", so summing dp counts every square exactly once.

[↑ Contents](#contents) · [← Previous](#p395) · [Next →](#p397)

---

## DP on stocks

<a id="p397"></a>

### 13. Best time to buy and sell stock

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on stocks | Core | No | [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/best-time-to-buy-and-sell-stock) | [Watch](https://youtu.be/excAOvwF_Wk) |

#### Problem Statement
`prices[i]` is the stock price on day `i`. Buy once and sell once on a **later** day to maximise profit. Return 0 if no profit is possible.

```text
prices = [7,1,5,3,6,4]  ->  5   (buy at 1, sell at 6)
prices = [7,6,4,3,1]    ->  0
```

#### Intuition — "DP is remembering the past"
If you sell on day `i`, the best buying day is the **minimum price before `i`**. So sweep once, keeping a running minimum, and at each day compute `prices[i] − mini`. Striver opens the stocks series with this problem to show that DP is basically **remembering past information** (here, a prefix minimum) instead of recomputing it.

#### Approach 1: Brute force — every pair *(not in video)*
**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int maxProfitBrute(vector<int>& p) {
    int best = 0, n = p.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) best = max(best, p[j] - p[i]);
    return best;
}
```

**Java**
```java
class Solution {
    static int maxProfitBrute(int[] p) {
        int best = 0, n = p.length;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) best = Math.max(best, p[j] - p[i]);
        return best;
    }
}
```

#### Approach 2: Optimal — running minimum (as in the video)
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int maxProfit(vector<int>& p) {
    int mini = p[0], best = 0;
    for (size_t i = 1; i < p.size(); i++) {
        best = max(best, p[i] - mini);      // sell today
        mini = min(mini, p[i]);             // remember the cheapest day so far
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int maxProfit(int[] p) {
        int mini = p[0], best = 0;
        for (int i = 1; i < p.length; i++) {
            best = Math.max(best, p[i] - mini);
            mini = Math.min(mini, p[i]);
        }
        return best;
    }
}
```

#### Key Takeaways
- Whenever an answer at `i` depends on "the best of everything before `i`", carry that best value forward.

[↑ Contents](#contents) · [← Previous](#p396) · [Next →](#p398)

---

<a id="p398"></a>

### 14. Best time to buy and sell stock II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on stocks | Core | No | [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/best-time-to-buy-and-sell-stock-ii) | [Watch](https://youtu.be/nGJmxkUJQGs) |

#### Problem Statement
**Buy and Sell Stock II:** you may make **as many transactions as you like**, but must sell before you buy again (hold at most one share). Maximise profit.

```text
prices = [7,1,5,3,6,4]  ->  7   (1 -> 5: +4, 3 -> 6: +3)
prices = [1,2,3,4,5]    ->  4
```

#### Intuition — the state (index, canBuy)
On each day you either act or skip, and what you may do depends on whether you currently hold a share:
- **`buy = 1` (allowed to buy):** max(`−p[i] + f(i+1, 0)`, `f(i+1, 1)`), meaning buy now or skip.
- **`buy = 0` (holding a share):** max(`+p[i] + f(i+1, 1)`, `f(i+1, 0)`), meaning sell now or skip.
- **Base case:** `f(n, ·) = 0`, since there are no days left.

The answer is `f(0, 1)`. This `(ind, buy)` template carries through the rest of the stock series.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
long long stk2Rec(int i, int buy, vector<int>& p) {
    if (i == (int)p.size()) return 0;
    if (buy) return max(-p[i] + stk2Rec(i + 1, 0, p), stk2Rec(i + 1, 1, p));
    return max(p[i] + stk2Rec(i + 1, 1, p), stk2Rec(i + 1, 0, p));
}
```

**Java**
```java
class Solution {
    static long stk2Rec(int i, int buy, int[] p) {
        if (i == p.length) return 0;
        if (buy == 1) return Math.max(-p[i] + stk2Rec(i + 1, 0, p), stk2Rec(i + 1, 1, p));
        return Math.max(p[i] + stk2Rec(i + 1, 1, p), stk2Rec(i + 1, 0, p));
    }
}
```

#### Approach 2: Memoization — dp[n][2]
**Complexity:** O(n·2) time, O(n·2) + O(n) stack.

**C++**
```cpp
long long stk2Memo(int i, int buy, vector<int>& p, vector<vector<long long>>& dp) {
    if (i == (int)p.size()) return 0;
    if (dp[i][buy] != -1) return dp[i][buy];
    if (buy) return dp[i][buy] = max(-p[i] + stk2Memo(i + 1, 0, p, dp), stk2Memo(i + 1, 1, p, dp));
    return dp[i][buy] = max(p[i] + stk2Memo(i + 1, 1, p, dp), stk2Memo(i + 1, 0, p, dp));
}
long long maxProfitIIMemo(vector<int>& p) {
    vector<vector<long long>> dp(p.size(), vector<long long>(2, -1));
    return stk2Memo(0, 1, p, dp);
}
```

**Java**
```java
class Solution {
    static long stk2Memo(int i, int buy, int[] p, long[][] dp) {
        if (i == p.length) return 0;
        if (dp[i][buy] != -1) return dp[i][buy];
        if (buy == 1) return dp[i][buy] = Math.max(-p[i] + stk2Memo(i + 1, 0, p, dp), stk2Memo(i + 1, 1, p, dp));
        return dp[i][buy] = Math.max(p[i] + stk2Memo(i + 1, 1, p, dp), stk2Memo(i + 1, 0, p, dp));
    }
    static long maxProfitIIMemo(int[] p) {
        long[][] dp = new long[p.length][2];
        for (long[] r : dp) Arrays.fill(r, -1);
        return stk2Memo(0, 1, p, dp);
    }
}
```

#### Approach 3: Tabulation — dp[n+1][2], filled from i = n−1 down
**Complexity:** O(n·2) time, O(n·2) space.

**C++**
```cpp
long long maxProfitIITab(vector<int>& p) {
    int n = p.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));   // dp[n][*] = 0
    for (int i = n - 1; i >= 0; i--) {
        dp[i][1] = max(-p[i] + dp[i + 1][0], dp[i + 1][1]);
        dp[i][0] = max(p[i] + dp[i + 1][1], dp[i + 1][0]);
    }
    return dp[0][1];
}
```

**Java**
```java
class Solution {
    static long maxProfitIITab(int[] p) {
        int n = p.length;
        long[][] dp = new long[n + 1][2];
        for (int i = n - 1; i >= 0; i--) {
            dp[i][1] = Math.max(-p[i] + dp[i + 1][0], dp[i + 1][1]);
            dp[i][0] = Math.max(p[i] + dp[i + 1][1], dp[i + 1][0]);
        }
        return dp[0][1];
    }
}
```

#### Approach 4: Space optimisation — `ahead` and `cur` arrays of size 2, then 4 variables
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
long long maxProfitIISpace(vector<int>& p) {
    int n = p.size();
    vector<long long> ahead(2, 0), cur(2, 0);
    for (int i = n - 1; i >= 0; i--) {
        cur[1] = max(-p[i] + ahead[0], ahead[1]);
        cur[0] = max(p[i] + ahead[1], ahead[0]);
        ahead = cur;
    }
    return ahead[1];
}
long long maxProfitII(vector<int>& p) {                  // the 4-variable version from the video
    long long aheadNotBuy = 0, aheadBuy = 0, curBuy, curNotBuy;
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        curNotBuy = max(p[i] + aheadBuy, aheadNotBuy);
        curBuy = max(-p[i] + aheadNotBuy, aheadBuy);
        aheadBuy = curBuy;
        aheadNotBuy = curNotBuy;
    }
    return aheadBuy;
}
```

**Java**
```java
class Solution {
    static long maxProfitIISpace(int[] p) {
        int n = p.length;
        long[] ahead = new long[2], cur = new long[2];
        for (int i = n - 1; i >= 0; i--) {
            cur[1] = Math.max(-p[i] + ahead[0], ahead[1]);
            cur[0] = Math.max(p[i] + ahead[1], ahead[0]);
            ahead = cur.clone();
        }
        return ahead[1];
    }
    static long maxProfitII(int[] p) {
        long aheadNotBuy = 0, aheadBuy = 0, curBuy, curNotBuy;
        for (int i = p.length - 1; i >= 0; i--) {
            curNotBuy = Math.max(p[i] + aheadBuy, aheadNotBuy);
            curBuy = Math.max(-p[i] + aheadNotBuy, aheadBuy);
            aheadBuy = curBuy;
            aheadNotBuy = curNotBuy;
        }
        return aheadBuy;
    }
}
```

#### Approach 5: Greedy — add every upward step *(not in video)*
Any profitable stretch from low to high can be split into its daily rises, so summing every positive `p[i] − p[i−1]` gives the same answer.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
long long maxProfitIIGreedy(vector<int>& p) {
    long long s = 0;
    for (size_t i = 1; i < p.size(); i++) s += max(0, p[i] - p[i - 1]);
    return s;
}
```

**Java**
```java
class Solution {
    static long maxProfitIIGreedy(int[] p) {
        long s = 0;
        for (int i = 1; i < p.length; i++) s += Math.max(0, p[i] - p[i - 1]);
        return s;
    }
}
```

#### Edge Cases & Pitfalls
- In Java, `ahead = cur` without cloning makes both names point at the same array. Clone it, or keep the four scalar variables.

#### Key Takeaways
- The `(ind, buy)` template solves every stock variant. The variants only add state (a cap, a transaction number) or change the transition (cooldown, fee).

[↑ Contents](#contents) · [← Previous](#p397) · [Next →](#p399)

---

<a id="p399"></a>

### 15. Best time to buy and sell stock III

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on stocks | Pro | No | [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/best-time-to-buy-and-sell-stock-iii) | [Watch](https://youtu.be/-uQGzhYj8BQ) |

#### Problem Statement
**Buy and Sell Stock III:** you may make **at most 2** transactions. Maximise profit.

```text
prices = [3,3,5,0,0,3,1,4]  ->  6   (0 -> 3: +3, 1 -> 4: +3)
prices = [1,2,3,4,5]        ->  4
prices = [7,6,4,3,1]        ->  0
```

#### Intuition — add a capacity to the state
Take Stock II's `(ind, buy)` state and add `cap`, the number of transactions still allowed. Selling completes a transaction, so `cap` decreases **on sell**.
- **Buy:** max(`−p[i] + f(i+1, 0, cap)`, `f(i+1, 1, cap)`).
- **Sell:** max(`p[i] + f(i+1, 1, cap−1)`, `f(i+1, 0, cap)`).
- **Base case:** `i == n` or `cap == 0` returns 0.

The video also shows a second formulation, which the sheet's discussions use: an **n × 4 DP over the transaction number** `t ∈ {0, 1, 2, 3}`, meaning buy, sell, buy, sell.
- An **even** `t` means buy.
- An **odd** `t` means sell.
- Acting moves to `t+1`.
- The base case is `t == 4`.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int stk3Rec(int i, int buy, int cap, vector<int>& p) {
    if (cap == 0 || i == (int)p.size()) return 0;
    if (buy) return max(-p[i] + stk3Rec(i + 1, 0, cap, p), stk3Rec(i + 1, 1, cap, p));
    return max(p[i] + stk3Rec(i + 1, 1, cap - 1, p), stk3Rec(i + 1, 0, cap, p));
}
```

**Java**
```java
class Solution {
    static int stk3Rec(int i, int buy, int cap, int[] p) {
        if (cap == 0 || i == p.length) return 0;
        if (buy == 1) return Math.max(-p[i] + stk3Rec(i + 1, 0, cap, p), stk3Rec(i + 1, 1, cap, p));
        return Math.max(p[i] + stk3Rec(i + 1, 1, cap - 1, p), stk3Rec(i + 1, 0, cap, p));
    }
}
```

#### Approach 2: Memoization — dp[n][2][3]
**Complexity:** O(n·2·3) time, O(n·2·3) + O(n) stack.

**C++**
```cpp
int stk3Memo(int i, int buy, int cap, vector<int>& p, vector<vector<vector<int>>>& dp) {
    if (cap == 0 || i == (int)p.size()) return 0;
    if (dp[i][buy][cap] != -1) return dp[i][buy][cap];
    if (buy) return dp[i][buy][cap] = max(-p[i] + stk3Memo(i + 1, 0, cap, p, dp), stk3Memo(i + 1, 1, cap, p, dp));
    return dp[i][buy][cap] = max(p[i] + stk3Memo(i + 1, 1, cap - 1, p, dp), stk3Memo(i + 1, 0, cap, p, dp));
}
int maxProfitIIIMemo(vector<int>& p) {
    vector<vector<vector<int>>> dp(p.size(), vector<vector<int>>(2, vector<int>(3, -1)));
    return stk3Memo(0, 1, 2, p, dp);
}
```

**Java**
```java
class Solution {
    static int stk3Memo(int i, int buy, int cap, int[] p, int[][][] dp) {
        if (cap == 0 || i == p.length) return 0;
        if (dp[i][buy][cap] != -1) return dp[i][buy][cap];
        if (buy == 1) return dp[i][buy][cap] = Math.max(-p[i] + stk3Memo(i + 1, 0, cap, p, dp), stk3Memo(i + 1, 1, cap, p, dp));
        return dp[i][buy][cap] = Math.max(p[i] + stk3Memo(i + 1, 1, cap - 1, p, dp), stk3Memo(i + 1, 0, cap, p, dp));
    }
    static int maxProfitIIIMemo(int[] p) {
        int[][][] dp = new int[p.length][2][3];
        for (int[][] a : dp) for (int[] b : a) Arrays.fill(b, -1);
        return stk3Memo(0, 1, 2, p, dp);
    }
}
```

#### Approach 3: Tabulation — dp[n+1][2][3]
The base cases (`cap == 0` and `i == n`) are already 0 from initialisation, so loop `cap` from 1 to 2.

**Complexity:** O(n·2·3) time, O(n·2·3) space.

**C++**
```cpp
int maxProfitIIITab(vector<int>& p) {
    int n = p.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
    for (int i = n - 1; i >= 0; i--)
        for (int cap = 1; cap <= 2; cap++) {
            dp[i][1][cap] = max(-p[i] + dp[i + 1][0][cap], dp[i + 1][1][cap]);
            dp[i][0][cap] = max(p[i] + dp[i + 1][1][cap - 1], dp[i + 1][0][cap]);
        }
    return dp[0][1][2];
}
```

**Java**
```java
class Solution {
    static int maxProfitIIITab(int[] p) {
        int n = p.length;
        int[][][] dp = new int[n + 1][2][3];
        for (int i = n - 1; i >= 0; i--)
            for (int cap = 1; cap <= 2; cap++) {
                dp[i][1][cap] = Math.max(-p[i] + dp[i + 1][0][cap], dp[i + 1][1][cap]);
                dp[i][0][cap] = Math.max(p[i] + dp[i + 1][1][cap - 1], dp[i + 1][0][cap]);
            }
        return dp[0][1][2];
    }
}
```

#### Approach 4: Space optimisation — `after[2][3]` and `cur[2][3]`
**Complexity:** O(n·6) time, O(1) space.

**C++**
```cpp
int maxProfitIIISpace(vector<int>& p) {
    int n = p.size();
    vector<vector<int>> after(2, vector<int>(3, 0)), cur(2, vector<int>(3, 0));
    for (int i = n - 1; i >= 0; i--) {
        for (int cap = 1; cap <= 2; cap++) {
            cur[1][cap] = max(-p[i] + after[0][cap], after[1][cap]);
            cur[0][cap] = max(p[i] + after[1][cap - 1], after[0][cap]);
        }
        after = cur;
    }
    return after[1][2];
}
```

**Java**
```java
class Solution {
    static int maxProfitIIISpace(int[] p) {
        int n = p.length;
        int[][] after = new int[2][3];
        for (int i = n - 1; i >= 0; i--) {
            int[][] cur = new int[2][3];
            for (int cap = 1; cap <= 2; cap++) {
                cur[1][cap] = Math.max(-p[i] + after[0][cap], after[1][cap]);
                cur[0][cap] = Math.max(p[i] + after[1][cap - 1], after[0][cap]);
            }
            after = cur;
        }
        return after[1][2];
    }
}
```

#### Approach 5: Transaction-number DP — n × 4 (rec, memo, tab, space)
**Complexity:** O(n·4) time; the memo and table are O(n·4), and the space-optimised version is O(4).

**C++**
```cpp
int stk3TRec(int i, int t, vector<int>& p) {                    // t: 0 = buy, 1 = sell, 2 = buy, 3 = sell
    if (i == (int)p.size() || t == 4) return 0;
    if (t % 2 == 0) return max(-p[i] + stk3TRec(i + 1, t + 1, p), stk3TRec(i + 1, t, p));
    return max(p[i] + stk3TRec(i + 1, t + 1, p), stk3TRec(i + 1, t, p));
}
int stk3TMemo(int i, int t, vector<int>& p, vector<vector<int>>& dp) {
    if (i == (int)p.size() || t == 4) return 0;
    if (dp[i][t] != -1) return dp[i][t];
    if (t % 2 == 0) return dp[i][t] = max(-p[i] + stk3TMemo(i + 1, t + 1, p, dp), stk3TMemo(i + 1, t, p, dp));
    return dp[i][t] = max(p[i] + stk3TMemo(i + 1, t + 1, p, dp), stk3TMemo(i + 1, t, p, dp));
}
int maxProfitIIITranTab(vector<int>& p) {
    int n = p.size();
    vector<vector<int>> dp(n + 1, vector<int>(5, 0));
    for (int i = n - 1; i >= 0; i--)
        for (int t = 3; t >= 0; t--)
            dp[i][t] = (t % 2 == 0) ? max(-p[i] + dp[i + 1][t + 1], dp[i + 1][t])
                                    : max(p[i] + dp[i + 1][t + 1], dp[i + 1][t]);
    return dp[0][0];
}
int maxProfitIII(vector<int>& p) {
    vector<int> after(5, 0), cur(5, 0);
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        for (int t = 3; t >= 0; t--)
            cur[t] = (t % 2 == 0) ? max(-p[i] + after[t + 1], after[t]) : max(p[i] + after[t + 1], after[t]);
        after = cur;
    }
    return after[0];
}
```

**Java**
```java
class Solution {
    static int stk3TRec(int i, int t, int[] p) {
        if (i == p.length || t == 4) return 0;
        if (t % 2 == 0) return Math.max(-p[i] + stk3TRec(i + 1, t + 1, p), stk3TRec(i + 1, t, p));
        return Math.max(p[i] + stk3TRec(i + 1, t + 1, p), stk3TRec(i + 1, t, p));
    }
    static int stk3TMemo(int i, int t, int[] p, int[][] dp) {
        if (i == p.length || t == 4) return 0;
        if (dp[i][t] != -1) return dp[i][t];
        if (t % 2 == 0) return dp[i][t] = Math.max(-p[i] + stk3TMemo(i + 1, t + 1, p, dp), stk3TMemo(i + 1, t, p, dp));
        return dp[i][t] = Math.max(p[i] + stk3TMemo(i + 1, t + 1, p, dp), stk3TMemo(i + 1, t, p, dp));
    }
    static int maxProfitIIITranTab(int[] p) {
        int n = p.length;
        int[][] dp = new int[n + 1][5];
        for (int i = n - 1; i >= 0; i--)
            for (int t = 3; t >= 0; t--)
                dp[i][t] = (t % 2 == 0) ? Math.max(-p[i] + dp[i + 1][t + 1], dp[i + 1][t])
                                        : Math.max(p[i] + dp[i + 1][t + 1], dp[i + 1][t]);
        return dp[0][0];
    }
    static int maxProfitIII(int[] p) {
        int[] after = new int[5];
        for (int i = p.length - 1; i >= 0; i--) {
            int[] cur = new int[5];
            for (int t = 3; t >= 0; t--)
                cur[t] = (t % 2 == 0) ? Math.max(-p[i] + after[t + 1], after[t]) : Math.max(p[i] + after[t + 1], after[t]);
            after = cur;
        }
        return after[0];
    }
}
```

#### Edge Cases & Pitfalls
- `cap` decreases **on sell**, when the transaction completes. Decreasing it on buy also works, as long as the base case changes to match.
- With the transaction number, the table needs width 5 so that `t + 1 = 4` is a valid, all-zero column.

#### Key Takeaways
- "At most k transactions" means one more dimension. Either `(buy, cap)` or a single transaction counter `t ∈ [0, 2k)` encodes it.

[↑ Contents](#contents) · [← Previous](#p398) · [Next →](#p400)

---

<a id="p400"></a>

### 16. Best time to buy and sell stock IV

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on stocks | Pro | No | [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/best-time-to-buy-and-sell-stock-iv) | [Watch](https://youtu.be/IV1dHbk5CDc) |

#### Problem Statement
**Buy and Sell Stock IV:** at most **k** transactions.

```text
k = 2, prices = [2,4,1]        ->  2
k = 2, prices = [3,2,6,5,0,3]  ->  7   (2 -> 6: +4, 0 -> 3: +3)
```

#### Intuition
This is exactly Stock III with `2` replaced by `k`:
- **Capacity approach:** state `(i, buy, cap)` with `cap ∈ [0, k]`, using a DP of size n × 2 × (k+1).
- **Transaction-number approach:** `t ∈ [0, 2k)`, where even means buy and odd means sell, using a DP of size n × 2k.

The video codes both.

#### Approach 1: Recursion (capacity)
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int stk4Rec(int i, int buy, int cap, vector<int>& p) {
    if (cap == 0 || i == (int)p.size()) return 0;
    if (buy) return max(-p[i] + stk4Rec(i + 1, 0, cap, p), stk4Rec(i + 1, 1, cap, p));
    return max(p[i] + stk4Rec(i + 1, 1, cap - 1, p), stk4Rec(i + 1, 0, cap, p));
}
int maxProfitIVRec(int k, vector<int>& p) { return stk4Rec(0, 1, k, p); }
```

**Java**
```java
class Solution {
    static int stk4Rec(int i, int buy, int cap, int[] p) {
        if (cap == 0 || i == p.length) return 0;
        if (buy == 1) return Math.max(-p[i] + stk4Rec(i + 1, 0, cap, p), stk4Rec(i + 1, 1, cap, p));
        return Math.max(p[i] + stk4Rec(i + 1, 1, cap - 1, p), stk4Rec(i + 1, 0, cap, p));
    }
    static int maxProfitIVRec(int k, int[] p) { return stk4Rec(0, 1, k, p); }
}
```

#### Approach 2: Memoization (capacity) — dp[n][2][k+1]
**Complexity:** O(n·2·k) time, O(n·2·k) + O(n) stack.

**C++**
```cpp
int stk4Memo(int i, int buy, int cap, vector<int>& p, vector<vector<vector<int>>>& dp) {
    if (cap == 0 || i == (int)p.size()) return 0;
    int& r = dp[i][buy][cap];
    if (r != -1) return r;
    if (buy) return r = max(-p[i] + stk4Memo(i + 1, 0, cap, p, dp), stk4Memo(i + 1, 1, cap, p, dp));
    return r = max(p[i] + stk4Memo(i + 1, 1, cap - 1, p, dp), stk4Memo(i + 1, 0, cap, p, dp));
}
int maxProfitIVMemo(int k, vector<int>& p) {
    vector<vector<vector<int>>> dp(p.size(), vector<vector<int>>(2, vector<int>(k + 1, -1)));
    return stk4Memo(0, 1, k, p, dp);
}
```

**Java**
```java
class Solution {
    static int stk4Memo(int i, int buy, int cap, int[] p, int[][][] dp) {
        if (cap == 0 || i == p.length) return 0;
        if (dp[i][buy][cap] != -1) return dp[i][buy][cap];
        if (buy == 1) return dp[i][buy][cap] = Math.max(-p[i] + stk4Memo(i + 1, 0, cap, p, dp), stk4Memo(i + 1, 1, cap, p, dp));
        return dp[i][buy][cap] = Math.max(p[i] + stk4Memo(i + 1, 1, cap - 1, p, dp), stk4Memo(i + 1, 0, cap, p, dp));
    }
    static int maxProfitIVMemo(int k, int[] p) {
        int[][][] dp = new int[p.length][2][k + 1];
        for (int[][] a : dp) for (int[] b : a) Arrays.fill(b, -1);
        return stk4Memo(0, 1, k, p, dp);
    }
}
```

#### Approach 3: Tabulation (capacity)
**Complexity:** O(n·2·k) time, O(n·2·k) space.

**C++**
```cpp
int maxProfitIVTab(int k, vector<int>& p) {
    int n = p.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));
    for (int i = n - 1; i >= 0; i--)
        for (int cap = 1; cap <= k; cap++) {
            dp[i][1][cap] = max(-p[i] + dp[i + 1][0][cap], dp[i + 1][1][cap]);
            dp[i][0][cap] = max(p[i] + dp[i + 1][1][cap - 1], dp[i + 1][0][cap]);
        }
    return dp[0][1][k];
}
```

**Java**
```java
class Solution {
    static int maxProfitIVTab(int k, int[] p) {
        int n = p.length;
        int[][][] dp = new int[n + 1][2][k + 1];
        for (int i = n - 1; i >= 0; i--)
            for (int cap = 1; cap <= k; cap++) {
                dp[i][1][cap] = Math.max(-p[i] + dp[i + 1][0][cap], dp[i + 1][1][cap]);
                dp[i][0][cap] = Math.max(p[i] + dp[i + 1][1][cap - 1], dp[i + 1][0][cap]);
            }
        return dp[0][1][k];
    }
}
```

#### Approach 4: Space optimisation (capacity) — `after[2][k+1]`
**Complexity:** O(n·2·k) time, O(k) space.

**C++**
```cpp
int maxProfitIVSpace(int k, vector<int>& p) {
    vector<vector<int>> after(2, vector<int>(k + 1, 0)), cur(2, vector<int>(k + 1, 0));
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        for (int cap = 1; cap <= k; cap++) {
            cur[1][cap] = max(-p[i] + after[0][cap], after[1][cap]);
            cur[0][cap] = max(p[i] + after[1][cap - 1], after[0][cap]);
        }
        after = cur;
    }
    return after[1][k];
}
```

**Java**
```java
class Solution {
    static int maxProfitIVSpace(int k, int[] p) {
        int[][] after = new int[2][k + 1];
        for (int i = p.length - 1; i >= 0; i--) {
            int[][] cur = new int[2][k + 1];
            for (int cap = 1; cap <= k; cap++) {
                cur[1][cap] = Math.max(-p[i] + after[0][cap], after[1][cap]);
                cur[0][cap] = Math.max(p[i] + after[1][cap - 1], after[0][cap]);
            }
            after = cur;
        }
        return after[1][k];
    }
}
```

#### Approach 5: Transaction number — n × 2k (memo and space-optimised)
The recursion is the memo function without the table, exactly as in Stock III, Approach 5.

**Complexity:** O(n·2k) time; the memo is O(n·2k) space and the space-optimised version is O(2k).

**C++**
```cpp
int stk4TMemo(int i, int t, int k, vector<int>& p, vector<vector<int>>& dp) {
    if (i == (int)p.size() || t == 2 * k) return 0;
    if (dp[i][t] != -1) return dp[i][t];
    if (t % 2 == 0) return dp[i][t] = max(-p[i] + stk4TMemo(i + 1, t + 1, k, p, dp), stk4TMemo(i + 1, t, k, p, dp));
    return dp[i][t] = max(p[i] + stk4TMemo(i + 1, t + 1, k, p, dp), stk4TMemo(i + 1, t, k, p, dp));
}
int maxProfitIVTranMemo(int k, vector<int>& p) {
    vector<vector<int>> dp(p.size(), vector<int>(2 * k, -1));
    return stk4TMemo(0, 0, k, p, dp);
}
int maxProfitIV(int k, vector<int>& p) {
    vector<int> after(2 * k + 1, 0), cur(2 * k + 1, 0);
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        for (int t = 2 * k - 1; t >= 0; t--)
            cur[t] = (t % 2 == 0) ? max(-p[i] + after[t + 1], after[t]) : max(p[i] + after[t + 1], after[t]);
        after = cur;
    }
    return after[0];
}
```

**Java**
```java
class Solution {
    static int stk4TMemo(int i, int t, int k, int[] p, int[][] dp) {
        if (i == p.length || t == 2 * k) return 0;
        if (dp[i][t] != -1) return dp[i][t];
        if (t % 2 == 0) return dp[i][t] = Math.max(-p[i] + stk4TMemo(i + 1, t + 1, k, p, dp), stk4TMemo(i + 1, t, k, p, dp));
        return dp[i][t] = Math.max(p[i] + stk4TMemo(i + 1, t + 1, k, p, dp), stk4TMemo(i + 1, t, k, p, dp));
    }
    static int maxProfitIVTranMemo(int k, int[] p) {
        int[][] dp = new int[p.length][2 * k];
        for (int[] r : dp) Arrays.fill(r, -1);
        return stk4TMemo(0, 0, k, p, dp);
    }
    static int maxProfitIV(int k, int[] p) {
        int[] after = new int[2 * k + 1];
        for (int i = p.length - 1; i >= 0; i--) {
            int[] cur = new int[2 * k + 1];
            for (int t = 2 * k - 1; t >= 0; t--)
                cur[t] = (t % 2 == 0) ? Math.max(-p[i] + after[t + 1], after[t]) : Math.max(p[i] + after[t + 1], after[t]);
            after = cur;
        }
        return after[0];
    }
}
```

#### Edge Cases & Pitfalls
- `k = 0` should give 0. With the transaction number, `2k = 0` makes the dp width 0, so guard it (the space-optimised version handles it naturally).
- `k ≥ n/2` is effectively unlimited transactions, so you can fall back to Stock II.

#### Key Takeaways
- Stock I, II, III and IV are one template with different limits on the number of transactions.

[↑ Contents](#contents) · [← Previous](#p399) · [Next →](#p401)

---

<a id="p401"></a>

### 17. Best time to buy and sell stock with transaction fees

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on stocks | Core | No | [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/best-time-to-buy-and-sell-stock-with-transaction-fee) | [Watch](https://youtu.be/k4eK-vEmnKg) |

#### Problem Statement
**With transaction fee:** unlimited transactions, but each completed transaction (buy plus sell) costs `fee`. Maximise profit.

```text
prices = [1,3,2,8,4,9], fee = 2  ->  8   ((8−1−2) + (9−4−2))
prices = [1,3,7,5,10,3], fee = 3 ->  6
```

#### Intuition
This is Stock II with one change: **subtract `fee` when you sell**, so the transaction is charged once. Everything else (recursion, memo, tabulation, space-optimised version) is identical, and the video's coverage takes about five minutes for that reason.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int feeRec(int i, int buy, vector<int>& p, int fee) {
    if (i == (int)p.size()) return 0;
    if (buy) return max(-p[i] + feeRec(i + 1, 0, p, fee), feeRec(i + 1, 1, p, fee));
    return max(p[i] - fee + feeRec(i + 1, 1, p, fee), feeRec(i + 1, 0, p, fee));
}
```

**Java**
```java
class Solution {
    static int feeRec(int i, int buy, int[] p, int fee) {
        if (i == p.length) return 0;
        if (buy == 1) return Math.max(-p[i] + feeRec(i + 1, 0, p, fee), feeRec(i + 1, 1, p, fee));
        return Math.max(p[i] - fee + feeRec(i + 1, 1, p, fee), feeRec(i + 1, 0, p, fee));
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·2) time, O(n·2) + O(n) stack.

**C++**
```cpp
int feeMemo(int i, int buy, vector<int>& p, int fee, vector<vector<int>>& dp) {
    if (i == (int)p.size()) return 0;
    if (dp[i][buy] != -1) return dp[i][buy];
    if (buy) return dp[i][buy] = max(-p[i] + feeMemo(i + 1, 0, p, fee, dp), feeMemo(i + 1, 1, p, fee, dp));
    return dp[i][buy] = max(p[i] - fee + feeMemo(i + 1, 1, p, fee, dp), feeMemo(i + 1, 0, p, fee, dp));
}
int maxProfitFeeMemo(vector<int>& p, int fee) {
    vector<vector<int>> dp(p.size(), vector<int>(2, -1));
    return feeMemo(0, 1, p, fee, dp);
}
```

**Java**
```java
class Solution {
    static int feeMemo(int i, int buy, int[] p, int fee, int[][] dp) {
        if (i == p.length) return 0;
        if (dp[i][buy] != -1) return dp[i][buy];
        if (buy == 1) return dp[i][buy] = Math.max(-p[i] + feeMemo(i + 1, 0, p, fee, dp), feeMemo(i + 1, 1, p, fee, dp));
        return dp[i][buy] = Math.max(p[i] - fee + feeMemo(i + 1, 1, p, fee, dp), feeMemo(i + 1, 0, p, fee, dp));
    }
    static int maxProfitFeeMemo(int[] p, int fee) {
        int[][] dp = new int[p.length][2];
        for (int[] r : dp) Arrays.fill(r, -1);
        return feeMemo(0, 1, p, fee, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·2) time, O(n·2) space.

**C++**
```cpp
int maxProfitFeeTab(vector<int>& p, int fee) {
    int n = p.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][1] = max(-p[i] + dp[i + 1][0], dp[i + 1][1]);
        dp[i][0] = max(p[i] - fee + dp[i + 1][1], dp[i + 1][0]);
    }
    return dp[0][1];
}
```

**Java**
```java
class Solution {
    static int maxProfitFeeTab(int[] p, int fee) {
        int n = p.length;
        int[][] dp = new int[n + 1][2];
        for (int i = n - 1; i >= 0; i--) {
            dp[i][1] = Math.max(-p[i] + dp[i + 1][0], dp[i + 1][1]);
            dp[i][0] = Math.max(p[i] - fee + dp[i + 1][1], dp[i + 1][0]);
        }
        return dp[0][1];
    }
}
```

#### Approach 4: Space optimisation — 4 variables
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int maxProfitFee(vector<int>& p, int fee) {
    int aheadBuy = 0, aheadNotBuy = 0;
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        int curBuy = max(-p[i] + aheadNotBuy, aheadBuy);
        int curNotBuy = max(p[i] - fee + aheadBuy, aheadNotBuy);
        aheadBuy = curBuy;
        aheadNotBuy = curNotBuy;
    }
    return aheadBuy;
}
```

**Java**
```java
class Solution {
    static int maxProfitFee(int[] p, int fee) {
        int aheadBuy = 0, aheadNotBuy = 0;
        for (int i = p.length - 1; i >= 0; i--) {
            int curBuy = Math.max(-p[i] + aheadNotBuy, aheadBuy);
            int curNotBuy = Math.max(p[i] - fee + aheadBuy, aheadNotBuy);
            aheadBuy = curBuy;
            aheadNotBuy = curNotBuy;
        }
        return aheadBuy;
    }
}
```

#### Key Takeaways
- Charge the fee exactly once per transaction, either on sell or on buy, never on both.

[↑ Contents](#contents) · [← Previous](#p400) · [Next →](#p402)

---

<a id="p402"></a>

### 18. Best Time to Buy and Sell Stock with Cooldown

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on stocks | Core | No | [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/best-time-to-buy-and-sell-stock-with-cooldown) | [Watch](https://youtu.be/IGIe46xw3YY) |

#### Problem Statement
**With cooldown:** unlimited transactions, but after you **sell** you can't buy on the next day (a 1-day cooldown).

```text
prices = [1,2,3,0,2]  ->  3   (buy 1, sell 2, cooldown, buy 0, sell 2)
prices = [1]          ->  0
```

#### Intuition
This is Stock II with one change: after selling on day `i`, the next decision happens on day **`i + 2`**, because day `i+1` is the cooldown. So the sell transition becomes `p[i] + f(i+2, 1)`.
- **Recursion:** `i ≥ n` returns 0, which covers `i + 2` jumping past the end.
- **Tabulation:** use size **n + 2**.
- **Space optimisation:** keep `front1` (row `i+1`) and `front2` (row `i+2`).

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int coolRec(int i, int buy, vector<int>& p) {
    if (i >= (int)p.size()) return 0;
    if (buy) return max(-p[i] + coolRec(i + 1, 0, p), coolRec(i + 1, 1, p));
    return max(p[i] + coolRec(i + 2, 1, p), coolRec(i + 1, 0, p));
}
```

**Java**
```java
class Solution {
    static int coolRec(int i, int buy, int[] p) {
        if (i >= p.length) return 0;
        if (buy == 1) return Math.max(-p[i] + coolRec(i + 1, 0, p), coolRec(i + 1, 1, p));
        return Math.max(p[i] + coolRec(i + 2, 1, p), coolRec(i + 1, 0, p));
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·2) time, O(n·2) + O(n) stack.

**C++**
```cpp
int coolMemo(int i, int buy, vector<int>& p, vector<vector<int>>& dp) {
    if (i >= (int)p.size()) return 0;
    if (dp[i][buy] != -1) return dp[i][buy];
    if (buy) return dp[i][buy] = max(-p[i] + coolMemo(i + 1, 0, p, dp), coolMemo(i + 1, 1, p, dp));
    return dp[i][buy] = max(p[i] + coolMemo(i + 2, 1, p, dp), coolMemo(i + 1, 0, p, dp));
}
int maxProfitCoolMemo(vector<int>& p) {
    vector<vector<int>> dp(p.size(), vector<int>(2, -1));
    return coolMemo(0, 1, p, dp);
}
```

**Java**
```java
class Solution {
    static int coolMemo(int i, int buy, int[] p, int[][] dp) {
        if (i >= p.length) return 0;
        if (dp[i][buy] != -1) return dp[i][buy];
        if (buy == 1) return dp[i][buy] = Math.max(-p[i] + coolMemo(i + 1, 0, p, dp), coolMemo(i + 1, 1, p, dp));
        return dp[i][buy] = Math.max(p[i] + coolMemo(i + 2, 1, p, dp), coolMemo(i + 1, 0, p, dp));
    }
    static int maxProfitCoolMemo(int[] p) {
        int[][] dp = new int[p.length][2];
        for (int[] r : dp) Arrays.fill(r, -1);
        return coolMemo(0, 1, p, dp);
    }
}
```

#### Approach 3: Tabulation — dp[n+2][2]
As the video notes, the `buy` loop can be dropped: just write both rows' formulas out directly.

**Complexity:** O(n·2) time, O(n·2) space.

**C++**
```cpp
int maxProfitCoolTab(vector<int>& p) {
    int n = p.size();
    vector<vector<int>> dp(n + 2, vector<int>(2, 0));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][1] = max(-p[i] + dp[i + 1][0], dp[i + 1][1]);
        dp[i][0] = max(p[i] + dp[i + 2][1], dp[i + 1][0]);
    }
    return dp[0][1];
}
```

**Java**
```java
class Solution {
    static int maxProfitCoolTab(int[] p) {
        int n = p.length;
        int[][] dp = new int[n + 2][2];
        for (int i = n - 1; i >= 0; i--) {
            dp[i][1] = Math.max(-p[i] + dp[i + 1][0], dp[i + 1][1]);
            dp[i][0] = Math.max(p[i] + dp[i + 2][1], dp[i + 1][0]);
        }
        return dp[0][1];
    }
}
```

#### Approach 4: Space optimisation — `front1`, `front2`, `cur`
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int maxProfitCool(vector<int>& p) {
    vector<int> front2(2, 0), front1(2, 0), cur(2, 0);
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        cur[1] = max(-p[i] + front1[0], front1[1]);
        cur[0] = max(p[i] + front2[1], front1[0]);
        front2 = front1;
        front1 = cur;
    }
    return front1[1];
}
```

**Java**
```java
class Solution {
    static int maxProfitCool(int[] p) {
        int[] front2 = new int[2], front1 = new int[2];
        for (int i = p.length - 1; i >= 0; i--) {
            int[] cur = new int[2];
            cur[1] = Math.max(-p[i] + front1[0], front1[1]);
            cur[0] = Math.max(p[i] + front2[1], front1[0]);
            front2 = front1;
            front1 = cur;
        }
        return front1[1];
    }
}
```

#### Edge Cases & Pitfalls
- The base case must be `i >= n`, not `i == n`, because `i + 2` can jump past the end.
- Update the rolling arrays in order: `front2 = front1` **before** `front1 = cur`.

#### Key Takeaways
- A cooldown of `c` days means the sell transition jumps to `i + 1 + c`.

[↑ Contents](#contents) · [← Previous](#p401) · [Next →](#p403)

---

## DP on subsequences

<a id="p403"></a>

### 19. Subset sum equals to target

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/subset-sum-equal-to-target) | [Watch](https://youtu.be/rYkfBRtMJr8) |

#### Problem Statement
Given an array of **positive** integers and a target `k`, is there a subset whose sum is exactly `k`?

```text
arr = [1, 2, 3, 4], k = 4   ->  true    ({4} or {1, 3})
arr = [4, 3, 2, 1], k = 5   ->  true
arr = [2, 5, 1, 6, 7], k = 4 ->  false
```

#### Intuition — f(ind, target)
`f(ind, target)` answers: "can some subset of `arr[0 … ind]` sum to `target`?"
- **Not take** `arr[ind]`: `f(ind−1, target)`.
- **Take** it (only if `arr[ind] ≤ target`): `f(ind−1, target − arr[ind])`.
- **Base cases:** `target == 0` returns true (the empty subset), and `ind == 0` returns `arr[0] == target`.

This is the first problem in the "DP on subsequences" pattern. The state is `(index, remaining target)`.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
bool ssRec(int ind, int target, vector<int>& a) {
    if (target == 0) return true;
    if (ind == 0) return a[0] == target;
    bool notTake = ssRec(ind - 1, target, a);
    bool take = a[ind] <= target ? ssRec(ind - 1, target - a[ind], a) : false;
    return take || notTake;
}
bool subsetSumToKRec(int n, int k, vector<int>& a) { return ssRec(n - 1, k, a); }
```

**Java**
```java
class Solution {
    static boolean ssRec(int ind, int target, int[] a) {
        if (target == 0) return true;
        if (ind == 0) return a[0] == target;
        boolean notTake = ssRec(ind - 1, target, a);
        boolean take = a[ind] <= target && ssRec(ind - 1, target - a[ind], a);
        return take || notTake;
    }
    static boolean subsetSumToKRec(int n, int k, int[] a) { return ssRec(n - 1, k, a); }
}
```

#### Approach 2: Memoization — dp[n][k+1] (−1 = unknown, 0/1 = answer)
**Complexity:** O(n·k) time, O(n·k) + O(n) stack.

**C++**
```cpp
bool ssMemo(int ind, int target, vector<int>& a, vector<vector<int>>& dp) {
    if (target == 0) return true;
    if (ind == 0) return a[0] == target;
    if (dp[ind][target] != -1) return dp[ind][target];
    bool notTake = ssMemo(ind - 1, target, a, dp);
    bool take = a[ind] <= target ? ssMemo(ind - 1, target - a[ind], a, dp) : false;
    return dp[ind][target] = take || notTake;
}
bool subsetSumToKMemo(int n, int k, vector<int>& a) {
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));
    return ssMemo(n - 1, k, a, dp);
}
```

**Java**
```java
class Solution {
    static boolean ssMemo(int ind, int target, int[] a, int[][] dp) {
        if (target == 0) return true;
        if (ind == 0) return a[0] == target;
        if (dp[ind][target] != -1) return dp[ind][target] == 1;
        boolean notTake = ssMemo(ind - 1, target, a, dp);
        boolean take = a[ind] <= target && ssMemo(ind - 1, target - a[ind], a, dp);
        dp[ind][target] = (take || notTake) ? 1 : 0;
        return take || notTake;
    }
    static boolean subsetSumToKMemo(int n, int k, int[] a) {
        int[][] dp = new int[n][k + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return ssMemo(n - 1, k, a, dp);
    }
}
```

#### Approach 3: Tabulation — dp[n][k+1] of booleans
Translate the base cases directly:
- `dp[i][0] = true` for every `i`.
- `dp[0][a[0]] = true`, if `a[0] ≤ k`.

**Complexity:** O(n·k) time, O(n·k) space.

**C++**
```cpp
bool subsetSumToKTab(int n, int k, vector<int>& a) {
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));
    for (int i = 0; i < n; i++) dp[i][0] = true;
    if (a[0] <= k) dp[0][a[0]] = true;
    for (int ind = 1; ind < n; ind++)
        for (int t = 1; t <= k; t++) {
            bool notTake = dp[ind - 1][t];
            bool take = a[ind] <= t ? dp[ind - 1][t - a[ind]] : false;
            dp[ind][t] = take || notTake;
        }
    return dp[n - 1][k];
}
```

**Java**
```java
class Solution {
    static boolean subsetSumToKTab(int n, int k, int[] a) {
        boolean[][] dp = new boolean[n][k + 1];
        for (int i = 0; i < n; i++) dp[i][0] = true;
        if (a[0] <= k) dp[0][a[0]] = true;
        for (int ind = 1; ind < n; ind++)
            for (int t = 1; t <= k; t++) {
                boolean notTake = dp[ind - 1][t];
                boolean take = a[ind] <= t && dp[ind - 1][t - a[ind]];
                dp[ind][t] = take || notTake;
            }
        return dp[n - 1][k];
    }
}
```

#### Approach 4: Space optimisation — `prev` and `cur` rows
**Complexity:** O(n·k) time, O(k) space.

**C++**
```cpp
bool subsetSumToK(int n, int k, vector<int>& a) {
    vector<bool> prev(k + 1, false), cur(k + 1, false);
    prev[0] = cur[0] = true;
    if (a[0] <= k) prev[a[0]] = true;
    for (int ind = 1; ind < n; ind++) {
        for (int t = 1; t <= k; t++) {
            bool notTake = prev[t];
            bool take = a[ind] <= t ? prev[t - a[ind]] : false;
            cur[t] = take || notTake;
        }
        prev = cur;
    }
    return prev[k];
}
```

**Java**
```java
class Solution {
    static boolean subsetSumToK(int n, int k, int[] a) {
        boolean[] prev = new boolean[k + 1];
        prev[0] = true;
        if (a[0] <= k) prev[a[0]] = true;
        for (int ind = 1; ind < n; ind++) {
            boolean[] cur = new boolean[k + 1];
            cur[0] = true;
            for (int t = 1; t <= k; t++) {
                boolean notTake = prev[t];
                boolean take = a[ind] <= t && prev[t - a[ind]];
                cur[t] = take || notTake;
            }
            prev = cur;
        }
        return prev[k];
    }
}
```

#### Edge Cases & Pitfalls
- Guard `a[0] ≤ k` before setting `dp[0][a[0]]`, or you'll index out of bounds.
- In Java, the memo has to store three states (unknown / false / true), so use an `int` table rather than `boolean`.

#### Key Takeaways
- Subset sum is the parent of the whole subsequence family: partition, minimum difference, count subsets and knapsack all reuse `f(ind, target)`.
- **The last row of the table says which targets are reachable.** Problem 405 uses exactly that.

[↑ Contents](#contents) · [← Previous](#p402) · [Next →](#p404)

---

<a id="p404"></a>

### 20. Partition equal subset sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Core | No | [LeetCode](https://leetcode.com/problems/partition-equal-subset-sum/) | [Watch](https://youtu.be/7win3dcgo3k) |

#### Problem Statement
**Partition Equal Subset Sum:** can the array be split into **two subsets with equal sums**?

```text
nums = [1, 5, 11, 5]  ->  true   ({1, 5, 5} and {11})
nums = [1, 2, 3, 5]   ->  false
```

#### Intuition
- **Odd total.** If the total `S` is odd, the answer is immediately false.
- **Even total.** Otherwise the question is whether some subset sums to `S/2`; the rest then sums to `S/2` automatically.

So this is **Subset Sum with k = S/2**, and every approach from 403 carries over.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
bool peRec(int ind, int t, vector<int>& a) {
    if (t == 0) return true;
    if (ind == 0) return a[0] == t;
    return peRec(ind - 1, t, a) || (a[ind] <= t && peRec(ind - 1, t - a[ind], a));
}
bool canPartitionRec(vector<int>& a) {
    int s = accumulate(a.begin(), a.end(), 0);
    if (s % 2) return false;
    return peRec(a.size() - 1, s / 2, a);
}
```

**Java**
```java
class Solution {
    static boolean peRec(int ind, int t, int[] a) {
        if (t == 0) return true;
        if (ind == 0) return a[0] == t;
        return peRec(ind - 1, t, a) || (a[ind] <= t && peRec(ind - 1, t - a[ind], a));
    }
    static boolean canPartitionRec(int[] a) {
        int s = 0;
        for (int x : a) s += x;
        if (s % 2 != 0) return false;
        return peRec(a.length - 1, s / 2, a);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·S/2) time, O(n·S/2) + O(n) stack.

**C++**
```cpp
bool peMemo(int ind, int t, vector<int>& a, vector<vector<int>>& dp) {
    if (t == 0) return true;
    if (ind == 0) return a[0] == t;
    if (dp[ind][t] != -1) return dp[ind][t];
    bool res = peMemo(ind - 1, t, a, dp) || (a[ind] <= t && peMemo(ind - 1, t - a[ind], a, dp));
    return dp[ind][t] = res;
}
bool canPartitionMemo(vector<int>& a) {
    int s = accumulate(a.begin(), a.end(), 0);
    if (s % 2) return false;
    vector<vector<int>> dp(a.size(), vector<int>(s / 2 + 1, -1));
    return peMemo(a.size() - 1, s / 2, a, dp);
}
```

**Java**
```java
class Solution {
    static boolean peMemo(int ind, int t, int[] a, int[][] dp) {
        if (t == 0) return true;
        if (ind == 0) return a[0] == t;
        if (dp[ind][t] != -1) return dp[ind][t] == 1;
        boolean res = peMemo(ind - 1, t, a, dp) || (a[ind] <= t && peMemo(ind - 1, t - a[ind], a, dp));
        dp[ind][t] = res ? 1 : 0;
        return res;
    }
    static boolean canPartitionMemo(int[] a) {
        int s = 0;
        for (int x : a) s += x;
        if (s % 2 != 0) return false;
        int[][] dp = new int[a.length][s / 2 + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return peMemo(a.length - 1, s / 2, a, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·S/2) time, O(n·S/2) space.

**C++**
```cpp
bool canPartitionTab(vector<int>& a) {
    int s = accumulate(a.begin(), a.end(), 0), n = a.size();
    if (s % 2) return false;
    int k = s / 2;
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));
    for (int i = 0; i < n; i++) dp[i][0] = true;
    if (a[0] <= k) dp[0][a[0]] = true;
    for (int ind = 1; ind < n; ind++)
        for (int t = 1; t <= k; t++)
            dp[ind][t] = dp[ind - 1][t] || (a[ind] <= t && dp[ind - 1][t - a[ind]]);
    return dp[n - 1][k];
}
```

**Java**
```java
class Solution {
    static boolean canPartitionTab(int[] a) {
        int s = 0, n = a.length;
        for (int x : a) s += x;
        if (s % 2 != 0) return false;
        int k = s / 2;
        boolean[][] dp = new boolean[n][k + 1];
        for (int i = 0; i < n; i++) dp[i][0] = true;
        if (a[0] <= k) dp[0][a[0]] = true;
        for (int ind = 1; ind < n; ind++)
            for (int t = 1; t <= k; t++)
                dp[ind][t] = dp[ind - 1][t] || (a[ind] <= t && dp[ind - 1][t - a[ind]]);
        return dp[n - 1][k];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n·S/2) time, O(S/2) space.

**C++**
```cpp
bool canPartition(vector<int>& a) {
    int s = accumulate(a.begin(), a.end(), 0), n = a.size();
    if (s % 2) return false;
    int k = s / 2;
    vector<bool> prev(k + 1, false);
    prev[0] = true;
    if (a[0] <= k) prev[a[0]] = true;
    for (int ind = 1; ind < n; ind++) {
        vector<bool> cur(k + 1, false);
        cur[0] = true;
        for (int t = 1; t <= k; t++) cur[t] = prev[t] || (a[ind] <= t && prev[t - a[ind]]);
        prev = cur;
    }
    return prev[k];
}
```

**Java**
```java
class Solution {
    static boolean canPartition(int[] a) {
        int s = 0, n = a.length;
        for (int x : a) s += x;
        if (s % 2 != 0) return false;
        int k = s / 2;
        boolean[] prev = new boolean[k + 1];
        prev[0] = true;
        if (a[0] <= k) prev[a[0]] = true;
        for (int ind = 1; ind < n; ind++) {
            boolean[] cur = new boolean[k + 1];
            cur[0] = true;
            for (int t = 1; t <= k; t++) cur[t] = prev[t] || (a[ind] <= t && prev[t - a[ind]]);
            prev = cur;
        }
        return prev[k];
    }
}
```

#### Key Takeaways
- Many problems reduce to subset sum with a **derived target**. Look for an equation linking the two halves.

[↑ Contents](#contents) · [← Previous](#p403) · [Next →](#p405)

---

<a id="p405"></a>

### 21. Partition a set into two subsets with minimum absolute sum difference

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Pro | No | [LeetCode](https://leetcode.com/problems/last-stone-weight-ii/) | [Watch](https://youtu.be/GS_OqZb2CWc) |

#### Problem Statement
Partition an array of **non-negative** integers into two subsets `S1` and `S2` so that `|sum(S1) − sum(S2)|` is minimised. The sheet links **Last Stone Weight II**, which is the same problem: smashing stones is equivalent to assigning each stone a `+` or a `−`.

```text
arr = [1, 2, 3, 4]   ->  0   ({1, 4} vs {2, 3})
arr = [8, 6, 5]      ->  3   ({8} vs {6, 5}, |8 − 11|)
stones = [2,7,4,1,8,1] -> 1
```

#### Intuition — use the last row of the subset-sum table
If one subset sums to `s1`, the other sums to `total − s1`, and the difference is `|total − 2·s1|`. So we need **every reachable `s1`**.
- **Build the table.** Tabulate subset sum with `k = total`.
- **Read the last row.** `dp[n−1][s1]` says whether some subset of the whole array sums to `s1`. The video stresses that **the last row of the DP-14 table** answers this for every target at once.
- **Minimise.** Take the minimum of `|total − 2·s1|` over reachable `s1 ∈ [0, total/2]`.

Memoization works as well, but you'd have to call `f(n−1, s1)` for every `s1` so that the table gets filled. That's why the video prefers tabulation here.

#### Approach 1: Memoization — call f(n−1, s1) for every s1
**Complexity:** O(n·total) time, O(n·total) + O(n) stack.

**C++**
```cpp
bool mdMemo(int ind, int t, vector<int>& a, vector<vector<int>>& dp) {
    if (t == 0) return true;
    if (ind == 0) return a[0] == t;
    if (dp[ind][t] != -1) return dp[ind][t];
    bool res = mdMemo(ind - 1, t, a, dp) || (a[ind] <= t && mdMemo(ind - 1, t - a[ind], a, dp));
    return dp[ind][t] = res;
}
int minSubsetSumDifferenceMemo(vector<int>& a) {
    int n = a.size(), total = accumulate(a.begin(), a.end(), 0), best = INT_MAX;
    vector<vector<int>> dp(n, vector<int>(total + 1, -1));
    for (int s1 = 0; s1 <= total / 2; s1++)
        if (mdMemo(n - 1, s1, a, dp)) best = min(best, abs(total - 2 * s1));
    return best;
}
```

**Java**
```java
class Solution {
    static boolean mdMemo(int ind, int t, int[] a, int[][] dp) {
        if (t == 0) return true;
        if (ind == 0) return a[0] == t;
        if (dp[ind][t] != -1) return dp[ind][t] == 1;
        boolean res = mdMemo(ind - 1, t, a, dp) || (a[ind] <= t && mdMemo(ind - 1, t - a[ind], a, dp));
        dp[ind][t] = res ? 1 : 0;
        return res;
    }
    static int minSubsetSumDifferenceMemo(int[] a) {
        int n = a.length, total = 0, best = Integer.MAX_VALUE;
        for (int x : a) total += x;
        int[][] dp = new int[n][total + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        for (int s1 = 0; s1 <= total / 2; s1++)
            if (mdMemo(n - 1, s1, a, dp)) best = Math.min(best, Math.abs(total - 2 * s1));
        return best;
    }
}
```

#### Approach 2: Tabulation (as in the video)
**Complexity:** O(n·total) time, O(n·total) space.

**C++**
```cpp
int minSubsetSumDifferenceTab(vector<int>& a) {
    int n = a.size(), total = accumulate(a.begin(), a.end(), 0);
    vector<vector<bool>> dp(n, vector<bool>(total + 1, false));
    for (int i = 0; i < n; i++) dp[i][0] = true;
    if (a[0] <= total) dp[0][a[0]] = true;
    for (int ind = 1; ind < n; ind++)
        for (int t = 1; t <= total; t++)
            dp[ind][t] = dp[ind - 1][t] || (a[ind] <= t && dp[ind - 1][t - a[ind]]);
    int best = INT_MAX;
    for (int s1 = 0; s1 <= total / 2; s1++)
        if (dp[n - 1][s1]) best = min(best, abs(total - 2 * s1));
    return best;
}
```

**Java**
```java
class Solution {
    static int minSubsetSumDifferenceTab(int[] a) {
        int n = a.length, total = 0;
        for (int x : a) total += x;
        boolean[][] dp = new boolean[n][total + 1];
        for (int i = 0; i < n; i++) dp[i][0] = true;
        if (a[0] <= total) dp[0][a[0]] = true;
        for (int ind = 1; ind < n; ind++)
            for (int t = 1; t <= total; t++)
                dp[ind][t] = dp[ind - 1][t] || (a[ind] <= t && dp[ind - 1][t - a[ind]]);
        int best = Integer.MAX_VALUE;
        for (int s1 = 0; s1 <= total / 2; s1++)
            if (dp[n - 1][s1]) best = Math.min(best, Math.abs(total - 2 * s1));
        return best;
    }
}
```

#### Approach 3: Space optimisation — keep only the last row
**Complexity:** O(n·total) time, O(total) space.

**C++**
```cpp
int minSubsetSumDifference(vector<int>& a) {
    int n = a.size(), total = accumulate(a.begin(), a.end(), 0);
    vector<bool> prev(total + 1, false);
    prev[0] = true;
    if (a[0] <= total) prev[a[0]] = true;
    for (int ind = 1; ind < n; ind++) {
        vector<bool> cur(total + 1, false);
        cur[0] = true;
        for (int t = 1; t <= total; t++) cur[t] = prev[t] || (a[ind] <= t && prev[t - a[ind]]);
        prev = cur;
    }
    int best = INT_MAX;
    for (int s1 = 0; s1 <= total / 2; s1++)
        if (prev[s1]) best = min(best, abs(total - 2 * s1));
    return best;
}
```

**Java**
```java
class Solution {
    static int minSubsetSumDifference(int[] a) {
        int n = a.length, total = 0;
        for (int x : a) total += x;
        boolean[] prev = new boolean[total + 1];
        prev[0] = true;
        if (a[0] <= total) prev[a[0]] = true;
        for (int ind = 1; ind < n; ind++) {
            boolean[] cur = new boolean[total + 1];
            cur[0] = true;
            for (int t = 1; t <= total; t++) cur[t] = prev[t] || (a[ind] <= t && prev[t - a[ind]]);
            prev = cur;
        }
        int best = Integer.MAX_VALUE;
        for (int s1 = 0; s1 <= total / 2; s1++)
            if (prev[s1]) best = Math.min(best, Math.abs(total - 2 * s1));
        return best;
    }
}
```

#### Edge Cases & Pitfalls
- This only works for **non-negative** numbers. With negatives, the targets aren't in `[0, total]`; LC 2035 then needs meet-in-the-middle.
- Scanning `s1` only up to `total/2` is enough, by symmetry.

#### Key Takeaways
- One tabulation answers "is target t reachable?" for **all** t at once. Use it whenever you need many targets.

[↑ Contents](#contents) · [← Previous](#p404) · [Next →](#p406)

---

<a id="p406"></a>

### 22. Count subsets with sum K

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-subsets-with-sum-k) | [Watch](https://youtu.be/ZHyb-A2Mte4) |

#### Problem Statement
Count the subsets of `arr` whose sum equals `K`, modulo 1e9+7.

```text
arr = [1, 2, 2, 3], K = 3   ->  3   ({1,2}, {1,2'}, {3})
arr = [0, 0, 1],    K = 1   ->  4   (each 0 can be in or out)
```

#### Intuition — counting means returning 1/0 and summing
This is the same recursion as subset sum, with **counts** instead of booleans:
- `f(ind, sum) = f(ind−1, sum) + f(ind−1, sum − arr[ind])`, the second term only when `arr[ind] ≤ sum`.
- **Base case in DP 17**, which assumes positive integers: `sum == 0` returns 1, and `ind == 0` returns `arr[0] == sum`.
- **Fix for zeros, from DP 18.** The DP 17 base case is wrong when the array contains **0s**. Returning early at `sum == 0` ignores the choices of taking or skipping each zero. Instead, make the decision at index 0:
  - `sum == 0 && arr[0] == 0` returns 2 (take the zero, or don't);
  - `sum == 0 || sum == arr[0]` returns 1;
  - anything else returns 0.

  Then tabulation has to start the `sum` loop at **0**, not 1.

The code below uses the zero-safe base case.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
const int MOD = 1e9 + 7;
int csRec(int ind, int sum, vector<int>& a) {
    if (ind == 0) {
        if (sum == 0 && a[0] == 0) return 2;
        if (sum == 0 || sum == a[0]) return 1;
        return 0;
    }
    int notTake = csRec(ind - 1, sum, a);
    int take = a[ind] <= sum ? csRec(ind - 1, sum - a[ind], a) : 0;
    return (notTake + take) % MOD;
}
int findWaysRec(vector<int>& a, int k) { return csRec(a.size() - 1, k, a); }
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int csRec(int ind, int sum, int[] a) {
        if (ind == 0) {
            if (sum == 0 && a[0] == 0) return 2;
            if (sum == 0 || sum == a[0]) return 1;
            return 0;
        }
        int notTake = csRec(ind - 1, sum, a);
        int take = a[ind] <= sum ? csRec(ind - 1, sum - a[ind], a) : 0;
        return (notTake + take) % MOD;
    }
    static int findWaysRec(int[] a, int k) { return csRec(a.length - 1, k, a); }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·K) time, O(n·K) + O(n) stack.

**C++**
```cpp
const int MOD = 1e9 + 7;
int csMemo(int ind, int sum, vector<int>& a, vector<vector<int>>& dp) {
    if (ind == 0) {
        if (sum == 0 && a[0] == 0) return 2;
        if (sum == 0 || sum == a[0]) return 1;
        return 0;
    }
    if (dp[ind][sum] != -1) return dp[ind][sum];
    int notTake = csMemo(ind - 1, sum, a, dp);
    int take = a[ind] <= sum ? csMemo(ind - 1, sum - a[ind], a, dp) : 0;
    return dp[ind][sum] = (notTake + take) % MOD;
}
int findWaysMemo(vector<int>& a, int k) {
    vector<vector<int>> dp(a.size(), vector<int>(k + 1, -1));
    return csMemo(a.size() - 1, k, a, dp);
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int csMemo(int ind, int sum, int[] a, int[][] dp) {
        if (ind == 0) {
            if (sum == 0 && a[0] == 0) return 2;
            if (sum == 0 || sum == a[0]) return 1;
            return 0;
        }
        if (dp[ind][sum] != -1) return dp[ind][sum];
        int notTake = csMemo(ind - 1, sum, a, dp);
        int take = a[ind] <= sum ? csMemo(ind - 1, sum - a[ind], a, dp) : 0;
        return dp[ind][sum] = (notTake + take) % MOD;
    }
    static int findWaysMemo(int[] a, int k) {
        int[][] dp = new int[a.length][k + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return csMemo(a.length - 1, k, a, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·K) time, O(n·K) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
int findWaysTab(vector<int>& a, int k) {
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));
    dp[0][0] = (a[0] == 0) ? 2 : 1;
    if (a[0] != 0 && a[0] <= k) dp[0][a[0]] = 1;
    for (int ind = 1; ind < n; ind++)
        for (int sum = 0; sum <= k; sum++) {                 // starts at 0 because of zeros
            int notTake = dp[ind - 1][sum];
            int take = a[ind] <= sum ? dp[ind - 1][sum - a[ind]] : 0;
            dp[ind][sum] = (notTake + take) % MOD;
        }
    return dp[n - 1][k];
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int findWaysTab(int[] a, int k) {
        int n = a.length;
        int[][] dp = new int[n][k + 1];
        dp[0][0] = (a[0] == 0) ? 2 : 1;
        if (a[0] != 0 && a[0] <= k) dp[0][a[0]] = 1;
        for (int ind = 1; ind < n; ind++)
            for (int sum = 0; sum <= k; sum++) {
                int notTake = dp[ind - 1][sum];
                int take = a[ind] <= sum ? dp[ind - 1][sum - a[ind]] : 0;
                dp[ind][sum] = (notTake + take) % MOD;
            }
        return dp[n - 1][k];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n·K) time, O(K) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
int findWays(vector<int>& a, int k) {
    int n = a.size();
    vector<int> prev(k + 1, 0);
    prev[0] = (a[0] == 0) ? 2 : 1;
    if (a[0] != 0 && a[0] <= k) prev[a[0]] = 1;
    for (int ind = 1; ind < n; ind++) {
        vector<int> cur(k + 1, 0);
        for (int sum = 0; sum <= k; sum++) {
            int take = a[ind] <= sum ? prev[sum - a[ind]] : 0;
            cur[sum] = (prev[sum] + take) % MOD;
        }
        prev = cur;
    }
    return prev[k];
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int findWays(int[] a, int k) {
        int n = a.length;
        int[] prev = new int[k + 1];
        prev[0] = (a[0] == 0) ? 2 : 1;
        if (a[0] != 0 && a[0] <= k) prev[a[0]] = 1;
        for (int ind = 1; ind < n; ind++) {
            int[] cur = new int[k + 1];
            for (int sum = 0; sum <= k; sum++) {
                int take = a[ind] <= sum ? prev[sum - a[ind]] : 0;
                cur[sum] = (prev[sum] + take) % MOD;
            }
            prev = cur;
        }
        return prev[k];
    }
}
```

#### Edge Cases & Pitfalls
- **Zeros:** `[0, 0, 1], K = 1` should give 4. The DP 17 base case (`if sum == 0 return 1` at the top) gives 1.
- Apply the modulo on every addition.

#### Key Takeaways
- For a count, the base cases return 1 or 0 and the choices are **summed**. For existence, they're OR-ed.

[↑ Contents](#contents) · [← Previous](#p405) · [Next →](#p407)

---

<a id="p407"></a>

### 23. Count partitions with given difference

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-partitions-with-a-given-difference) | [Watch](https://youtu.be/zoilQD1kYSg) |

#### Problem Statement
**Count partitions with given difference:** count the ways to split the array into `S1` and `S2` with `sum(S1) ≥ sum(S2)` and `sum(S1) − sum(S2) = D`, modulo 1e9+7. Elements are ≥ 0.

```text
arr = [5, 2, 6, 4], D = 3   ->  1   ({6, 4} vs {5, 2})
arr = [1, 1, 1, 1], D = 0   ->  6
arr = [0, 0, 1],    D = 1   ->  4
```

#### Intuition — reduce to "count subsets with sum K"
With `S1 + S2 = total` and `S1 − S2 = D`:

  **S2 = (total − D) / 2**

So count the subsets whose sum is `(total − D)/2`. That number is valid only if:
- `total − D ≥ 0`, since a sum can't be negative;
- `total − D` is **even**, since the sum must be an integer.

Otherwise the answer is 0. The zero-safe base case from DP 18 matters here because the array may contain 0s.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
const int MOD = 1e9 + 7;
int cpRec(int ind, int sum, vector<int>& a) {
    if (ind == 0) {
        if (sum == 0 && a[0] == 0) return 2;
        if (sum == 0 || sum == a[0]) return 1;
        return 0;
    }
    int take = a[ind] <= sum ? cpRec(ind - 1, sum - a[ind], a) : 0;
    return (cpRec(ind - 1, sum, a) + take) % MOD;
}
int countPartitionsRec(int d, vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    if (total - d < 0 || (total - d) % 2) return 0;
    return cpRec(a.size() - 1, (total - d) / 2, a);
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int cpRec(int ind, int sum, int[] a) {
        if (ind == 0) {
            if (sum == 0 && a[0] == 0) return 2;
            if (sum == 0 || sum == a[0]) return 1;
            return 0;
        }
        int take = a[ind] <= sum ? cpRec(ind - 1, sum - a[ind], a) : 0;
        return (cpRec(ind - 1, sum, a) + take) % MOD;
    }
    static int countPartitionsRec(int d, int[] a) {
        int total = 0;
        for (int x : a) total += x;
        if (total - d < 0 || (total - d) % 2 != 0) return 0;
        return cpRec(a.length - 1, (total - d) / 2, a);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·S2) time, O(n·S2) + O(n) stack.

**C++**
```cpp
const int MOD = 1e9 + 7;
int cpMemo(int ind, int sum, vector<int>& a, vector<vector<int>>& dp) {
    if (ind == 0) {
        if (sum == 0 && a[0] == 0) return 2;
        if (sum == 0 || sum == a[0]) return 1;
        return 0;
    }
    if (dp[ind][sum] != -1) return dp[ind][sum];
    int take = a[ind] <= sum ? cpMemo(ind - 1, sum - a[ind], a, dp) : 0;
    return dp[ind][sum] = (cpMemo(ind - 1, sum, a, dp) + take) % MOD;
}
int countPartitionsMemo(int d, vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    if (total - d < 0 || (total - d) % 2) return 0;
    int k = (total - d) / 2;
    vector<vector<int>> dp(a.size(), vector<int>(k + 1, -1));
    return cpMemo(a.size() - 1, k, a, dp);
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int cpMemo(int ind, int sum, int[] a, int[][] dp) {
        if (ind == 0) {
            if (sum == 0 && a[0] == 0) return 2;
            if (sum == 0 || sum == a[0]) return 1;
            return 0;
        }
        if (dp[ind][sum] != -1) return dp[ind][sum];
        int take = a[ind] <= sum ? cpMemo(ind - 1, sum - a[ind], a, dp) : 0;
        return dp[ind][sum] = (cpMemo(ind - 1, sum, a, dp) + take) % MOD;
    }
    static int countPartitionsMemo(int d, int[] a) {
        int total = 0;
        for (int x : a) total += x;
        if (total - d < 0 || (total - d) % 2 != 0) return 0;
        int k = (total - d) / 2;
        int[][] dp = new int[a.length][k + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return cpMemo(a.length - 1, k, a, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·S2) time, O(n·S2) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
int countPartitionsTab(int d, vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0), n = a.size();
    if (total - d < 0 || (total - d) % 2) return 0;
    int k = (total - d) / 2;
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));
    dp[0][0] = (a[0] == 0) ? 2 : 1;
    if (a[0] != 0 && a[0] <= k) dp[0][a[0]] = 1;
    for (int ind = 1; ind < n; ind++)
        for (int s = 0; s <= k; s++) {
            int take = a[ind] <= s ? dp[ind - 1][s - a[ind]] : 0;
            dp[ind][s] = (dp[ind - 1][s] + take) % MOD;
        }
    return dp[n - 1][k];
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int countPartitionsTab(int d, int[] a) {
        int total = 0, n = a.length;
        for (int x : a) total += x;
        if (total - d < 0 || (total - d) % 2 != 0) return 0;
        int k = (total - d) / 2;
        int[][] dp = new int[n][k + 1];
        dp[0][0] = (a[0] == 0) ? 2 : 1;
        if (a[0] != 0 && a[0] <= k) dp[0][a[0]] = 1;
        for (int ind = 1; ind < n; ind++)
            for (int s = 0; s <= k; s++) {
                int take = a[ind] <= s ? dp[ind - 1][s - a[ind]] : 0;
                dp[ind][s] = (dp[ind - 1][s] + take) % MOD;
            }
        return dp[n - 1][k];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n·S2) time, O(S2) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
int countPartitions(int d, vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0), n = a.size();
    if (total - d < 0 || (total - d) % 2) return 0;
    int k = (total - d) / 2;
    vector<int> prev(k + 1, 0);
    prev[0] = (a[0] == 0) ? 2 : 1;
    if (a[0] != 0 && a[0] <= k) prev[a[0]] = 1;
    for (int ind = 1; ind < n; ind++) {
        vector<int> cur(k + 1, 0);
        for (int s = 0; s <= k; s++) cur[s] = (prev[s] + (a[ind] <= s ? prev[s - a[ind]] : 0)) % MOD;
        prev = cur;
    }
    return prev[k];
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int countPartitions(int d, int[] a) {
        int total = 0, n = a.length;
        for (int x : a) total += x;
        if (total - d < 0 || (total - d) % 2 != 0) return 0;
        int k = (total - d) / 2;
        int[] prev = new int[k + 1];
        prev[0] = (a[0] == 0) ? 2 : 1;
        if (a[0] != 0 && a[0] <= k) prev[a[0]] = 1;
        for (int ind = 1; ind < n; ind++) {
            int[] cur = new int[k + 1];
            for (int s = 0; s <= k; s++) cur[s] = (prev[s] + (a[ind] <= s ? prev[s - a[ind]] : 0)) % MOD;
            prev = cur;
        }
        return prev[k];
    }
}
```

#### Edge Cases & Pitfalls
- Return 0 when `total − D` is negative or odd. The video notes this edge case is easy to forget.
- The video's first submission failed because it forgot the modulo. Apply it on every addition.

#### Key Takeaways
- Turn "two groups with a relation" into "one subset with a derived target" using `S1 + S2 = total`.

[↑ Contents](#contents) · [← Previous](#p406) · [Next →](#p408)

---

<a id="p408"></a>

### 24. 0 and 1 Knapsack

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Core | No | — | [Watch](https://youtu.be/GqOmJHQZivw) |

#### Problem Statement
**0/1 Knapsack:** `n` items with `wt[i]` and `val[i]`, and a bag of capacity `W`. Each item is taken **at most once**. Maximise the total value.

```text
wt = [1, 2, 4, 5], val = [5, 4, 8, 6], W = 5   ->  13   (items 0 and 2)
wt = [4, 5, 1],    val = [1, 2, 3],    W = 4   ->  3
```

#### Intuition
Greedy by value or by ratio fails, because there is no uniformity. So try every option with pick or not pick:
- **Not take:** `f(ind−1, W)`.
- **Take** (if `wt[ind] ≤ W`): `val[ind] + f(ind−1, W − wt[ind])`.
- **Base case:** `ind == 0` returns `val[0]` if `wt[0] ≤ W`, else 0.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int ksRec(int ind, int W, vector<int>& wt, vector<int>& val) {
    if (ind == 0) return wt[0] <= W ? val[0] : 0;
    int notTake = ksRec(ind - 1, W, wt, val);
    int take = wt[ind] <= W ? val[ind] + ksRec(ind - 1, W - wt[ind], wt, val) : INT_MIN;
    return max(take, notTake);
}
int knapsackRec(vector<int>& wt, vector<int>& val, int n, int W) { return ksRec(n - 1, W, wt, val); }
```

**Java**
```java
class Solution {
    static int ksRec(int ind, int W, int[] wt, int[] val) {
        if (ind == 0) return wt[0] <= W ? val[0] : 0;
        int notTake = ksRec(ind - 1, W, wt, val);
        int take = wt[ind] <= W ? val[ind] + ksRec(ind - 1, W - wt[ind], wt, val) : Integer.MIN_VALUE;
        return Math.max(take, notTake);
    }
    static int knapsackRec(int[] wt, int[] val, int n, int W) { return ksRec(n - 1, W, wt, val); }
}
```

#### Approach 2: Memoization — dp[n][W+1]
**Complexity:** O(n·W) time, O(n·W) + O(n) stack.

**C++**
```cpp
int ksMemo(int ind, int W, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp) {
    if (ind == 0) return wt[0] <= W ? val[0] : 0;
    if (dp[ind][W] != -1) return dp[ind][W];
    int notTake = ksMemo(ind - 1, W, wt, val, dp);
    int take = wt[ind] <= W ? val[ind] + ksMemo(ind - 1, W - wt[ind], wt, val, dp) : INT_MIN;
    return dp[ind][W] = max(take, notTake);
}
int knapsackMemo(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return ksMemo(n - 1, W, wt, val, dp);
}
```

**Java**
```java
class Solution {
    static int ksMemo(int ind, int W, int[] wt, int[] val, int[][] dp) {
        if (ind == 0) return wt[0] <= W ? val[0] : 0;
        if (dp[ind][W] != -1) return dp[ind][W];
        int notTake = ksMemo(ind - 1, W, wt, val, dp);
        int take = wt[ind] <= W ? val[ind] + ksMemo(ind - 1, W - wt[ind], wt, val, dp) : Integer.MIN_VALUE;
        return dp[ind][W] = Math.max(take, notTake);
    }
    static int knapsackMemo(int[] wt, int[] val, int n, int W) {
        int[][] dp = new int[n][W + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return ksMemo(n - 1, W, wt, val, dp);
    }
}
```

#### Approach 3: Tabulation
Base row: `dp[0][w] = val[0]` for every `w ≥ wt[0]`.

**Complexity:** O(n·W) time, O(n·W) space.

**C++**
```cpp
int knapsackTab(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));
    for (int w = wt[0]; w <= W; w++) dp[0][w] = val[0];
    for (int ind = 1; ind < n; ind++)
        for (int w = 0; w <= W; w++) {
            int notTake = dp[ind - 1][w];
            int take = wt[ind] <= w ? val[ind] + dp[ind - 1][w - wt[ind]] : INT_MIN;
            dp[ind][w] = max(take, notTake);
        }
    return dp[n - 1][W];
}
```

**Java**
```java
class Solution {
    static int knapsackTab(int[] wt, int[] val, int n, int W) {
        int[][] dp = new int[n][W + 1];
        for (int w = wt[0]; w <= W; w++) dp[0][w] = val[0];
        for (int ind = 1; ind < n; ind++)
            for (int w = 0; w <= W; w++) {
                int notTake = dp[ind - 1][w];
                int take = wt[ind] <= w ? val[ind] + dp[ind - 1][w - wt[ind]] : Integer.MIN_VALUE;
                dp[ind][w] = Math.max(take, notTake);
            }
        return dp[n - 1][W];
    }
}
```

#### Approach 4: Space optimisation — two rows, then a single row (right to left)
`dp[ind][w]` reads `prev[w]` and `prev[w − wt]`, which are at the same column or to its **left**. So if the single array is filled from **right to left**, every value read still belongs to the previous row. The video's final version uses this one array.

**Complexity:** O(n·W) time, O(W) space.

**C++**
```cpp
int knapsackTwoRows(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<int> prev(W + 1, 0), cur(W + 1, 0);
    for (int w = wt[0]; w <= W; w++) prev[w] = val[0];
    for (int ind = 1; ind < n; ind++) {
        for (int w = 0; w <= W; w++) {
            int take = wt[ind] <= w ? val[ind] + prev[w - wt[ind]] : INT_MIN;
            cur[w] = max(take, prev[w]);
        }
        prev = cur;
    }
    return prev[W];
}
int knapsack(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<int> prev(W + 1, 0);
    for (int w = wt[0]; w <= W; w++) prev[w] = val[0];
    for (int ind = 1; ind < n; ind++)
        for (int w = W; w >= 0; w--) {                           // right to left
            int take = wt[ind] <= w ? val[ind] + prev[w - wt[ind]] : INT_MIN;
            prev[w] = max(take, prev[w]);
        }
    return prev[W];
}
```

**Java**
```java
class Solution {
    static int knapsackTwoRows(int[] wt, int[] val, int n, int W) {
        int[] prev = new int[W + 1];
        for (int w = wt[0]; w <= W; w++) prev[w] = val[0];
        for (int ind = 1; ind < n; ind++) {
            int[] cur = new int[W + 1];
            for (int w = 0; w <= W; w++) {
                int take = wt[ind] <= w ? val[ind] + prev[w - wt[ind]] : Integer.MIN_VALUE;
                cur[w] = Math.max(take, prev[w]);
            }
            prev = cur;
        }
        return prev[W];
    }
    static int knapsack(int[] wt, int[] val, int n, int W) {
        int[] prev = new int[W + 1];
        for (int w = wt[0]; w <= W; w++) prev[w] = val[0];
        for (int ind = 1; ind < n; ind++)
            for (int w = W; w >= 0; w--) {
                int take = wt[ind] <= w ? val[ind] + prev[w - wt[ind]] : Integer.MIN_VALUE;
                prev[w] = Math.max(take, prev[w]);
            }
        return prev[W];
    }
}
```

#### Edge Cases & Pitfalls
- In the single-array version, iterating `w` **left to right** would reuse the same item several times, which turns it into the unbounded knapsack.
- `wt[0] > W` means the base row stays 0.

#### Key Takeaways
- 0/1 knapsack: take moves to `ind − 1`. Unbounded knapsack (412): take **stays at `ind`**.
- One-array space optimisation: go right to left for 0/1, and left to right for unbounded.

[↑ Contents](#contents) · [← Previous](#p407) · [Next →](#p409)

---

<a id="p409"></a>

### 25. Minimum coins

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Core | No | [LeetCode](https://leetcode.com/problems/coin-change/) | [Watch](https://youtu.be/myPeWb3Y68A) |

#### Problem Statement
**Minimum Coins / Coin Change:** given coin denominations, with an **infinite supply** of each, return the fewest coins that make up `amount`, or `−1` if it's impossible.

```text
coins = [1, 2, 5], amount = 11  ->  3    (5 + 5 + 1)
coins = [2], amount = 3         ->  -1
coins = [9, 6, 5, 1], amount = 11 -> 2   (6 + 5; greedy 9+1+1 gives 3)
```

#### Intuition — the infinite supply keeps you at the same index
Greedy (largest coin first) fails, as the last example shows. Use pick or not pick, noting that **taking a coin keeps you at `ind`**, so the same coin can be taken again:
- **Not take:** `f(ind−1, T)`.
- **Take** (if `coins[ind] ≤ T`): `1 + f(ind, T − coins[ind])`.
- **Base case:** `ind == 0` returns `T / coins[0]` if `T % coins[0] == 0`, else **1e9** (impossible).

The answer is `f(n−1, amount)`. If it is ≥ 1e9, return −1.

#### Approach 1: Recursion
The time is much worse than O(2ⁿ), because the same index can be revisited many times. The stack depth is up to O(amount), not O(n).

**Complexity:** exponential time, O(amount) stack.

**C++**
```cpp
int mcRec(int ind, int T, vector<int>& c) {
    if (ind == 0) return T % c[0] == 0 ? T / c[0] : 1e9;
    int notTake = mcRec(ind - 1, T, c);
    int take = c[ind] <= T ? 1 + mcRec(ind, T - c[ind], c) : 1e9;
    return min(take, notTake);
}
int coinChangeRec(vector<int>& c, int amount) {
    int r = mcRec(c.size() - 1, amount, c);
    return r >= 1e9 ? -1 : r;
}
```

**Java**
```java
class Solution {
    static int mcRec(int ind, int T, int[] c) {
        if (ind == 0) return T % c[0] == 0 ? T / c[0] : (int) 1e9;
        int notTake = mcRec(ind - 1, T, c);
        int take = c[ind] <= T ? 1 + mcRec(ind, T - c[ind], c) : (int) 1e9;
        return Math.min(take, notTake);
    }
    static int coinChangeRec(int[] c, int amount) {
        int r = mcRec(c.length - 1, amount, c);
        return r >= 1e9 ? -1 : r;
    }
}
```

#### Approach 2: Memoization — dp[n][amount+1]
**Complexity:** O(n·amount) time, O(n·amount) + O(amount) stack.

**C++**
```cpp
int mcMemo(int ind, int T, vector<int>& c, vector<vector<int>>& dp) {
    if (ind == 0) return T % c[0] == 0 ? T / c[0] : 1e9;
    if (dp[ind][T] != -1) return dp[ind][T];
    int notTake = mcMemo(ind - 1, T, c, dp);
    int take = c[ind] <= T ? 1 + mcMemo(ind, T - c[ind], c, dp) : 1e9;
    return dp[ind][T] = min(take, notTake);
}
int coinChangeMemo(vector<int>& c, int amount) {
    vector<vector<int>> dp(c.size(), vector<int>(amount + 1, -1));
    int r = mcMemo(c.size() - 1, amount, c, dp);
    return r >= 1e9 ? -1 : r;
}
```

**Java**
```java
class Solution {
    static int mcMemo(int ind, int T, int[] c, int[][] dp) {
        if (ind == 0) return T % c[0] == 0 ? T / c[0] : (int) 1e9;
        if (dp[ind][T] != -1) return dp[ind][T];
        int notTake = mcMemo(ind - 1, T, c, dp);
        int take = c[ind] <= T ? 1 + mcMemo(ind, T - c[ind], c, dp) : (int) 1e9;
        return dp[ind][T] = Math.min(take, notTake);
    }
    static int coinChangeMemo(int[] c, int amount) {
        int[][] dp = new int[c.length][amount + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        int r = mcMemo(c.length - 1, amount, c, dp);
        return r >= 1e9 ? -1 : r;
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·amount) time, O(n·amount) space.

**C++**
```cpp
int coinChangeTab(vector<int>& c, int amount) {
    int n = c.size();
    vector<vector<int>> dp(n, vector<int>(amount + 1, 0));
    for (int T = 0; T <= amount; T++) dp[0][T] = T % c[0] == 0 ? T / c[0] : 1e9;
    for (int ind = 1; ind < n; ind++)
        for (int T = 0; T <= amount; T++) {
            int notTake = dp[ind - 1][T];
            int take = c[ind] <= T ? 1 + dp[ind][T - c[ind]] : 1e9;    // same row: infinite supply
            dp[ind][T] = min(take, notTake);
        }
    return dp[n - 1][amount] >= 1e9 ? -1 : dp[n - 1][amount];
}
```

**Java**
```java
class Solution {
    static int coinChangeTab(int[] c, int amount) {
        int n = c.length;
        int[][] dp = new int[n][amount + 1];
        for (int T = 0; T <= amount; T++) dp[0][T] = T % c[0] == 0 ? T / c[0] : (int) 1e9;
        for (int ind = 1; ind < n; ind++)
            for (int T = 0; T <= amount; T++) {
                int notTake = dp[ind - 1][T];
                int take = c[ind] <= T ? 1 + dp[ind][T - c[ind]] : (int) 1e9;
                dp[ind][T] = Math.min(take, notTake);
            }
        return dp[n - 1][amount] >= 1e9 ? -1 : dp[n - 1][amount];
    }
}
```

#### Approach 4: Space optimisation — `prev` and `cur`
`take` reads `cur[T − c]`, which is the current row's value to the left, so fill `cur` from left to right.

**Complexity:** O(n·amount) time, O(amount) space.

**C++**
```cpp
int coinChange(vector<int>& c, int amount) {
    int n = c.size();
    vector<int> prev(amount + 1), cur(amount + 1);
    for (int T = 0; T <= amount; T++) prev[T] = T % c[0] == 0 ? T / c[0] : 1e9;
    for (int ind = 1; ind < n; ind++) {
        for (int T = 0; T <= amount; T++) {
            int take = c[ind] <= T ? 1 + cur[T - c[ind]] : 1e9;
            cur[T] = min(take, prev[T]);
        }
        prev = cur;
    }
    return prev[amount] >= 1e9 ? -1 : prev[amount];
}
```

**Java**
```java
class Solution {
    static int coinChange(int[] c, int amount) {
        int n = c.length;
        int[] prev = new int[amount + 1];
        for (int T = 0; T <= amount; T++) prev[T] = T % c[0] == 0 ? T / c[0] : (int) 1e9;
        for (int ind = 1; ind < n; ind++) {
            int[] cur = new int[amount + 1];
            for (int T = 0; T <= amount; T++) {
                int take = c[ind] <= T ? 1 + cur[T - c[ind]] : (int) 1e9;
                cur[T] = Math.min(take, prev[T]);
            }
            prev = cur;
        }
        return prev[amount] >= 1e9 ? -1 : prev[amount];
    }
}
```

#### Edge Cases & Pitfalls
- `amount = 0` gives 0 coins.
- Use 1e9 as "impossible", not INT_MAX, because `1 + INT_MAX` overflows.

#### Key Takeaways
- **Infinite supply means the take branch stays at `ind`.** Only not-take moves to `ind − 1`.

[↑ Contents](#contents) · [← Previous](#p408) · [Next →](#p410)

---

<a id="p410"></a>

### 26. Target sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Core | No | [LeetCode](https://leetcode.com/problems/target-sum/) | [Watch](https://youtu.be/b3GD8263-PQ) |

#### Problem Statement
**Target Sum:** put a `+` or `−` in front of each number so that the expression equals `target`. Count the ways.

```text
nums = [1,1,1,1,1], target = 3   ->  5
nums = [1], target = 1           ->  1
```

#### Intuition — it's DP 18 in disguise
The `+` numbers form `S1` and the `−` numbers form `S2`, so `S1 − S2 = target`. That is exactly **count partitions with difference `target`** (problem 407). So count the subsets with sum **`(total − target)/2`**, provided `total − target ≥ 0` and it is even.
- The recursion over signs is the direct brute force.
- The reduction gives the DP. LeetCode doesn't take a modulo here.
- Zeros matter again: a 0 can take `+` or `−`, which counts as 2 ways. The zero-safe base case handles that.

#### Approach 1: Recursion over signs (brute force)
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int tsSigns(int i, int cur, vector<int>& a, int target) {
    if (i == (int)a.size()) return cur == target ? 1 : 0;
    return tsSigns(i + 1, cur + a[i], a, target) + tsSigns(i + 1, cur - a[i], a, target);
}
int findTargetSumWaysRec(vector<int>& a, int target) { return tsSigns(0, 0, a, target); }
```

**Java**
```java
class Solution {
    static int tsSigns(int i, int cur, int[] a, int target) {
        if (i == a.length) return cur == target ? 1 : 0;
        return tsSigns(i + 1, cur + a[i], a, target) + tsSigns(i + 1, cur - a[i], a, target);
    }
    static int findTargetSumWaysRec(int[] a, int target) { return tsSigns(0, 0, a, target); }
}
```

#### Approach 2: Memoization — count subsets with sum (total − target)/2
**Complexity:** O(n·S2) time, O(n·S2) + O(n) stack.

**C++**
```cpp
int tsMemo(int ind, int sum, vector<int>& a, vector<vector<int>>& dp) {
    if (ind == 0) {
        if (sum == 0 && a[0] == 0) return 2;
        if (sum == 0 || sum == a[0]) return 1;
        return 0;
    }
    if (dp[ind][sum] != -1) return dp[ind][sum];
    int take = a[ind] <= sum ? tsMemo(ind - 1, sum - a[ind], a, dp) : 0;
    return dp[ind][sum] = tsMemo(ind - 1, sum, a, dp) + take;
}
int findTargetSumWaysMemo(vector<int>& a, int target) {
    int total = accumulate(a.begin(), a.end(), 0);
    if (total - target < 0 || (total - target) % 2) return 0;
    int k = (total - target) / 2;
    vector<vector<int>> dp(a.size(), vector<int>(k + 1, -1));
    return tsMemo(a.size() - 1, k, a, dp);
}
```

**Java**
```java
class Solution {
    static int tsMemo(int ind, int sum, int[] a, int[][] dp) {
        if (ind == 0) {
            if (sum == 0 && a[0] == 0) return 2;
            if (sum == 0 || sum == a[0]) return 1;
            return 0;
        }
        if (dp[ind][sum] != -1) return dp[ind][sum];
        int take = a[ind] <= sum ? tsMemo(ind - 1, sum - a[ind], a, dp) : 0;
        return dp[ind][sum] = tsMemo(ind - 1, sum, a, dp) + take;
    }
    static int findTargetSumWaysMemo(int[] a, int target) {
        int total = 0;
        for (int x : a) total += x;
        if (total - target < 0 || (total - target) % 2 != 0) return 0;
        int k = (total - target) / 2;
        int[][] dp = new int[a.length][k + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return tsMemo(a.length - 1, k, a, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·S2) time, O(n·S2) space.

**C++**
```cpp
int findTargetSumWaysTab(vector<int>& a, int target) {
    int total = accumulate(a.begin(), a.end(), 0), n = a.size();
    if (total - target < 0 || (total - target) % 2) return 0;
    int k = (total - target) / 2;
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));
    dp[0][0] = (a[0] == 0) ? 2 : 1;
    if (a[0] != 0 && a[0] <= k) dp[0][a[0]] = 1;
    for (int ind = 1; ind < n; ind++)
        for (int s = 0; s <= k; s++)
            dp[ind][s] = dp[ind - 1][s] + (a[ind] <= s ? dp[ind - 1][s - a[ind]] : 0);
    return dp[n - 1][k];
}
```

**Java**
```java
class Solution {
    static int findTargetSumWaysTab(int[] a, int target) {
        int total = 0, n = a.length;
        for (int x : a) total += x;
        if (total - target < 0 || (total - target) % 2 != 0) return 0;
        int k = (total - target) / 2;
        int[][] dp = new int[n][k + 1];
        dp[0][0] = (a[0] == 0) ? 2 : 1;
        if (a[0] != 0 && a[0] <= k) dp[0][a[0]] = 1;
        for (int ind = 1; ind < n; ind++)
            for (int s = 0; s <= k; s++)
                dp[ind][s] = dp[ind - 1][s] + (a[ind] <= s ? dp[ind - 1][s - a[ind]] : 0);
        return dp[n - 1][k];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n·S2) time, O(S2) space.

**C++**
```cpp
int findTargetSumWays(vector<int>& a, int target) {
    int total = accumulate(a.begin(), a.end(), 0), n = a.size();
    if (total - target < 0 || (total - target) % 2) return 0;
    int k = (total - target) / 2;
    vector<int> prev(k + 1, 0);
    prev[0] = (a[0] == 0) ? 2 : 1;
    if (a[0] != 0 && a[0] <= k) prev[a[0]] = 1;
    for (int ind = 1; ind < n; ind++) {
        vector<int> cur(k + 1, 0);
        for (int s = 0; s <= k; s++) cur[s] = prev[s] + (a[ind] <= s ? prev[s - a[ind]] : 0);
        prev = cur;
    }
    return prev[k];
}
```

**Java**
```java
class Solution {
    static int findTargetSumWays(int[] a, int target) {
        int total = 0, n = a.length;
        for (int x : a) total += x;
        if (total - target < 0 || (total - target) % 2 != 0) return 0;
        int k = (total - target) / 2;
        int[] prev = new int[k + 1];
        prev[0] = (a[0] == 0) ? 2 : 1;
        if (a[0] != 0 && a[0] <= k) prev[a[0]] = 1;
        for (int ind = 1; ind < n; ind++) {
            int[] cur = new int[k + 1];
            for (int s = 0; s <= k; s++) cur[s] = prev[s] + (a[ind] <= s ? prev[s - a[ind]] : 0);
            prev = cur;
        }
        return prev[k];
    }
}
```

#### Edge Cases & Pitfalls
- `target` can be negative. Then `total − target` is larger but still valid, because −target is the mirror image with every sign flipped.
- Zeros double the count: `[0, 0, 1]` with target 1 gives 4.

#### Key Takeaways
- Look for the hidden partition: any "assign + or −" problem is a two-subset difference problem.

[↑ Contents](#contents) · [← Previous](#p409) · [Next →](#p411)

---

<a id="p411"></a>

### 27. Coin change II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Pro | No | [LeetCode](https://leetcode.com/problems/coin-change-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/coin-change-ii-combinations) | [Watch](https://youtu.be/HgyouUi11zk) |

#### Problem Statement
**Coin Change II:** count the **combinations** of coins (infinite supply) that make up `amount`.

```text
amount = 5, coins = [1, 2, 5]  ->  4   (5, 2+2+1, 2+1+1+1, 1+1+1+1+1)
amount = 3, coins = [2]        ->  0
amount = 10, coins = [10]      ->  1
```

#### Intuition
This combines the count pattern from 406 with the infinite supply from 409:
- **Recurrence:** `f(ind, T) = f(ind−1, T) + f(ind, T − coins[ind])`, the second term only when `coins[ind] ≤ T`.
- **Base case:** `ind == 0` returns 1 if `T % coins[0] == 0`, else 0.

Processing coins index by index counts **combinations** (unordered), not permutations.

#### Approach 1: Recursion
**Complexity:** exponential time, O(amount) stack.

**C++**
```cpp
long long cc2Rec(int ind, int T, vector<int>& c) {
    if (ind == 0) return T % c[0] == 0 ? 1 : 0;
    long long notTake = cc2Rec(ind - 1, T, c);
    long long take = c[ind] <= T ? cc2Rec(ind, T - c[ind], c) : 0;
    return take + notTake;
}
long long changeRec(int amount, vector<int>& c) { return cc2Rec(c.size() - 1, amount, c); }
```

**Java**
```java
class Solution {
    static long cc2Rec(int ind, int T, int[] c) {
        if (ind == 0) return T % c[0] == 0 ? 1 : 0;
        long notTake = cc2Rec(ind - 1, T, c);
        long take = c[ind] <= T ? cc2Rec(ind, T - c[ind], c) : 0;
        return take + notTake;
    }
    static long changeRec(int amount, int[] c) { return cc2Rec(c.length - 1, amount, c); }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·amount) time, O(n·amount) + O(amount) stack.

**C++**
```cpp
long long cc2Memo(int ind, int T, vector<int>& c, vector<vector<long long>>& dp) {
    if (ind == 0) return T % c[0] == 0 ? 1 : 0;
    if (dp[ind][T] != -1) return dp[ind][T];
    long long notTake = cc2Memo(ind - 1, T, c, dp);
    long long take = c[ind] <= T ? cc2Memo(ind, T - c[ind], c, dp) : 0;
    return dp[ind][T] = take + notTake;
}
long long changeMemo(int amount, vector<int>& c) {
    vector<vector<long long>> dp(c.size(), vector<long long>(amount + 1, -1));
    return cc2Memo(c.size() - 1, amount, c, dp);
}
```

**Java**
```java
class Solution {
    static long cc2Memo(int ind, int T, int[] c, long[][] dp) {
        if (ind == 0) return T % c[0] == 0 ? 1 : 0;
        if (dp[ind][T] != -1) return dp[ind][T];
        long notTake = cc2Memo(ind - 1, T, c, dp);
        long take = c[ind] <= T ? cc2Memo(ind, T - c[ind], c, dp) : 0;
        return dp[ind][T] = take + notTake;
    }
    static long changeMemo(int amount, int[] c) {
        long[][] dp = new long[c.length][amount + 1];
        for (long[] r : dp) Arrays.fill(r, -1);
        return cc2Memo(c.length - 1, amount, c, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·amount) time, O(n·amount) space.

**C++**
```cpp
long long changeTab(int amount, vector<int>& c) {
    int n = c.size();
    vector<vector<long long>> dp(n, vector<long long>(amount + 1, 0));
    for (int T = 0; T <= amount; T++) dp[0][T] = (T % c[0] == 0);
    for (int ind = 1; ind < n; ind++)
        for (int T = 0; T <= amount; T++)
            dp[ind][T] = dp[ind - 1][T] + (c[ind] <= T ? dp[ind][T - c[ind]] : 0);
    return dp[n - 1][amount];
}
```

**Java**
```java
class Solution {
    static long changeTab(int amount, int[] c) {
        int n = c.length;
        long[][] dp = new long[n][amount + 1];
        for (int T = 0; T <= amount; T++) dp[0][T] = (T % c[0] == 0) ? 1 : 0;
        for (int ind = 1; ind < n; ind++)
            for (int T = 0; T <= amount; T++)
                dp[ind][T] = dp[ind - 1][T] + (c[ind] <= T ? dp[ind][T - c[ind]] : 0);
        return dp[n - 1][amount];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n·amount) time, O(amount) space.

**C++**
```cpp
long long change(int amount, vector<int>& c) {
    int n = c.size();
    vector<long long> prev(amount + 1, 0), cur(amount + 1, 0);
    for (int T = 0; T <= amount; T++) prev[T] = (T % c[0] == 0);
    for (int ind = 1; ind < n; ind++) {
        for (int T = 0; T <= amount; T++)
            cur[T] = prev[T] + (c[ind] <= T ? cur[T - c[ind]] : 0);
        prev = cur;
    }
    return prev[amount];
}
```

**Java**
```java
class Solution {
    static long change(int amount, int[] c) {
        int n = c.length;
        long[] prev = new long[amount + 1];
        for (int T = 0; T <= amount; T++) prev[T] = (T % c[0] == 0) ? 1 : 0;
        for (int ind = 1; ind < n; ind++) {
            long[] cur = new long[amount + 1];
            for (int T = 0; T <= amount; T++)
                cur[T] = prev[T] + (c[ind] <= T ? cur[T - c[ind]] : 0);
            prev = cur;
        }
        return prev[amount];
    }
}
```

#### Edge Cases & Pitfalls
- `amount = 0` gives 1, the empty combination.
- Intermediate counts can exceed `int` even when the final answer fits, so use `long long`. On LeetCode, a 1-D `unsigned` or `long long` dp also works.
- Swapping the loops (amount outside, coins inside) counts **permutations**, which is Combination Sum IV, a different problem.

#### Key Takeaways
- Count + unbounded: sum the branches, and keep `ind` on the take branch.

[↑ Contents](#contents) · [← Previous](#p410) · [Next →](#p412)

---

<a id="p412"></a>

### 28. Unbounded knapsack

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/unbounded-knapsack) | [Watch](https://youtu.be/OgvOZ6OrJoY) |

#### Problem Statement
**Unbounded Knapsack:** same as 0/1 knapsack, but each item may be taken **any number of times**.

```text
W = 10, wt = [2, 4, 6], val = [5, 11, 13]   ->  27   (2 + 4 + 4: 5 + 11 + 11)
W = 8,  wt = [1, 3, 4, 5], val = [10, 40, 50, 70]  ->  110   (3 + 5)
```

#### Intuition
This is 0/1 knapsack with one change: **take stays at `ind`**.
- **Recurrence:** `f(ind, W) = max(f(ind−1, W), val[ind] + f(ind, W − wt[ind]))`.
- **Base case:** `ind == 0` returns `(W / wt[0]) · val[0]`, i.e. take item 0 as many times as it fits.

#### Approach 1: Recursion
**Complexity:** exponential time, O(W) stack.

**C++**
```cpp
int ukRec(int ind, int W, vector<int>& wt, vector<int>& val) {
    if (ind == 0) return (W / wt[0]) * val[0];
    int notTake = ukRec(ind - 1, W, wt, val);
    int take = wt[ind] <= W ? val[ind] + ukRec(ind, W - wt[ind], wt, val) : INT_MIN;
    return max(take, notTake);
}
int unboundedKnapsackRec(int n, int W, vector<int>& val, vector<int>& wt) { return ukRec(n - 1, W, wt, val); }
```

**Java**
```java
class Solution {
    static int ukRec(int ind, int W, int[] wt, int[] val) {
        if (ind == 0) return (W / wt[0]) * val[0];
        int notTake = ukRec(ind - 1, W, wt, val);
        int take = wt[ind] <= W ? val[ind] + ukRec(ind, W - wt[ind], wt, val) : Integer.MIN_VALUE;
        return Math.max(take, notTake);
    }
    static int unboundedKnapsackRec(int n, int W, int[] val, int[] wt) { return ukRec(n - 1, W, wt, val); }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·W) time, O(n·W) + O(W) stack.

**C++**
```cpp
int ukMemo(int ind, int W, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp) {
    if (ind == 0) return (W / wt[0]) * val[0];
    if (dp[ind][W] != -1) return dp[ind][W];
    int notTake = ukMemo(ind - 1, W, wt, val, dp);
    int take = wt[ind] <= W ? val[ind] + ukMemo(ind, W - wt[ind], wt, val, dp) : INT_MIN;
    return dp[ind][W] = max(take, notTake);
}
int unboundedKnapsackMemo(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return ukMemo(n - 1, W, wt, val, dp);
}
```

**Java**
```java
class Solution {
    static int ukMemo(int ind, int W, int[] wt, int[] val, int[][] dp) {
        if (ind == 0) return (W / wt[0]) * val[0];
        if (dp[ind][W] != -1) return dp[ind][W];
        int notTake = ukMemo(ind - 1, W, wt, val, dp);
        int take = wt[ind] <= W ? val[ind] + ukMemo(ind, W - wt[ind], wt, val, dp) : Integer.MIN_VALUE;
        return dp[ind][W] = Math.max(take, notTake);
    }
    static int unboundedKnapsackMemo(int n, int W, int[] val, int[] wt) {
        int[][] dp = new int[n][W + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return ukMemo(n - 1, W, wt, val, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·W) time, O(n·W) space.

**C++**
```cpp
int unboundedKnapsackTab(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));
    for (int w = 0; w <= W; w++) dp[0][w] = (w / wt[0]) * val[0];
    for (int ind = 1; ind < n; ind++)
        for (int w = 0; w <= W; w++) {
            int take = wt[ind] <= w ? val[ind] + dp[ind][w - wt[ind]] : INT_MIN;
            dp[ind][w] = max(take, dp[ind - 1][w]);
        }
    return dp[n - 1][W];
}
```

**Java**
```java
class Solution {
    static int unboundedKnapsackTab(int n, int W, int[] val, int[] wt) {
        int[][] dp = new int[n][W + 1];
        for (int w = 0; w <= W; w++) dp[0][w] = (w / wt[0]) * val[0];
        for (int ind = 1; ind < n; ind++)
            for (int w = 0; w <= W; w++) {
                int take = wt[ind] <= w ? val[ind] + dp[ind][w - wt[ind]] : Integer.MIN_VALUE;
                dp[ind][w] = Math.max(take, dp[ind - 1][w]);
            }
        return dp[n - 1][W];
    }
}
```

#### Approach 4: Space optimisation — two rows, then a single row (left to right)
`take` reads the **current** row to the left, and `notTake` reads the same column of the previous row. A single array filled from **left to right** satisfies both: at column `w`, cells to the left are already updated (the current row) and `prev[w]` still holds the old value.

**Complexity:** O(n·W) time, O(W) space.

**C++**
```cpp
int unboundedKnapsackTwoRows(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<int> prev(W + 1, 0), cur(W + 1, 0);
    for (int w = 0; w <= W; w++) prev[w] = (w / wt[0]) * val[0];
    for (int ind = 1; ind < n; ind++) {
        for (int w = 0; w <= W; w++) {
            int take = wt[ind] <= w ? val[ind] + cur[w - wt[ind]] : INT_MIN;
            cur[w] = max(take, prev[w]);
        }
        prev = cur;
    }
    return prev[W];
}
int unboundedKnapsack(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<int> prev(W + 1, 0);
    for (int w = 0; w <= W; w++) prev[w] = (w / wt[0]) * val[0];
    for (int ind = 1; ind < n; ind++)
        for (int w = 0; w <= W; w++) {
            int take = wt[ind] <= w ? val[ind] + prev[w - wt[ind]] : INT_MIN;
            prev[w] = max(take, prev[w]);
        }
    return prev[W];
}
```

**Java**
```java
class Solution {
    static int unboundedKnapsackTwoRows(int n, int W, int[] val, int[] wt) {
        int[] prev = new int[W + 1];
        for (int w = 0; w <= W; w++) prev[w] = (w / wt[0]) * val[0];
        for (int ind = 1; ind < n; ind++) {
            int[] cur = new int[W + 1];
            for (int w = 0; w <= W; w++) {
                int take = wt[ind] <= w ? val[ind] + cur[w - wt[ind]] : Integer.MIN_VALUE;
                cur[w] = Math.max(take, prev[w]);
            }
            prev = cur;
        }
        return prev[W];
    }
    static int unboundedKnapsack(int n, int W, int[] val, int[] wt) {
        int[] prev = new int[W + 1];
        for (int w = 0; w <= W; w++) prev[w] = (w / wt[0]) * val[0];
        for (int ind = 1; ind < n; ind++)
            for (int w = 0; w <= W; w++) {
                int take = wt[ind] <= w ? val[ind] + prev[w - wt[ind]] : Integer.MIN_VALUE;
                prev[w] = Math.max(take, prev[w]);
            }
        return prev[W];
    }
}
```

#### Key Takeaways
- 0/1 versus unbounded is one character in the recurrence (`ind − 1` versus `ind`) and one loop direction in the 1-D optimisation.

[↑ Contents](#contents) · [← Previous](#p411) · [Next →](#p413)

---

<a id="p413"></a>

### 29. Rod cutting problem

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on subsequences | Pro | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/rod-cutting-problem) | [Watch](https://youtu.be/mO8XpGoJwuo) |

#### Problem Statement
**Rod Cutting:** a rod of length `N`, where `price[i]` is the price of a piece of length `i + 1`. Cut the rod into pieces in any way (or not at all) to maximise the total price.

```text
N = 5, price = [2, 5, 7, 8, 10]   ->  12   (2 + 2 + 1: 5 + 5 + 2)
N = 8, price = [1,5,8,9,10,17,17,20]  ->  22   (2 + 6: 5 + 17)
```

#### Intuition — unbounded knapsack where weight = length
- **The mapping.** Piece length `ind + 1` plays the role of the weight and `price[ind]` the value. Any length can be used repeatedly, and the capacity is `N`.
- **The recurrence.** f(ind, N) = max(f(ind−1, N), price[ind] + f(ind, N − (ind+1))).
- **The base case.** `ind == 0` returns `N · price[0]`, i.e. all pieces of length 1.

#### Approach 1: Recursion
**Complexity:** exponential time, O(N) stack.

**C++**
```cpp
int rodRec(int ind, int N, vector<int>& price) {
    if (ind == 0) return N * price[0];
    int notTake = rodRec(ind - 1, N, price);
    int len = ind + 1;
    int take = len <= N ? price[ind] + rodRec(ind, N - len, price) : INT_MIN;
    return max(take, notTake);
}
int cutRodRec(vector<int>& price, int N) { return rodRec(N - 1, N, price); }
```

**Java**
```java
class Solution {
    static int rodRec(int ind, int N, int[] price) {
        if (ind == 0) return N * price[0];
        int notTake = rodRec(ind - 1, N, price);
        int len = ind + 1;
        int take = len <= N ? price[ind] + rodRec(ind, N - len, price) : Integer.MIN_VALUE;
        return Math.max(take, notTake);
    }
    static int cutRodRec(int[] price, int N) { return rodRec(N - 1, N, price); }
}
```

#### Approach 2: Memoization
**Complexity:** O(N²) time, O(N²) + O(N) stack.

**C++**
```cpp
int rodMemo(int ind, int N, vector<int>& price, vector<vector<int>>& dp) {
    if (ind == 0) return N * price[0];
    if (dp[ind][N] != -1) return dp[ind][N];
    int notTake = rodMemo(ind - 1, N, price, dp);
    int len = ind + 1;
    int take = len <= N ? price[ind] + rodMemo(ind, N - len, price, dp) : INT_MIN;
    return dp[ind][N] = max(take, notTake);
}
int cutRodMemo(vector<int>& price, int N) {
    vector<vector<int>> dp(N, vector<int>(N + 1, -1));
    return rodMemo(N - 1, N, price, dp);
}
```

**Java**
```java
class Solution {
    static int rodMemo(int ind, int N, int[] price, int[][] dp) {
        if (ind == 0) return N * price[0];
        if (dp[ind][N] != -1) return dp[ind][N];
        int notTake = rodMemo(ind - 1, N, price, dp);
        int len = ind + 1;
        int take = len <= N ? price[ind] + rodMemo(ind, N - len, price, dp) : Integer.MIN_VALUE;
        return dp[ind][N] = Math.max(take, notTake);
    }
    static int cutRodMemo(int[] price, int N) {
        int[][] dp = new int[N][N + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return rodMemo(N - 1, N, price, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(N²) time, O(N²) space.

**C++**
```cpp
int cutRodTab(vector<int>& price, int N) {
    vector<vector<int>> dp(N, vector<int>(N + 1, 0));
    for (int L = 0; L <= N; L++) dp[0][L] = L * price[0];
    for (int ind = 1; ind < N; ind++)
        for (int L = 0; L <= N; L++) {
            int len = ind + 1;
            int take = len <= L ? price[ind] + dp[ind][L - len] : INT_MIN;
            dp[ind][L] = max(take, dp[ind - 1][L]);
        }
    return dp[N - 1][N];
}
```

**Java**
```java
class Solution {
    static int cutRodTab(int[] price, int N) {
        int[][] dp = new int[N][N + 1];
        for (int L = 0; L <= N; L++) dp[0][L] = L * price[0];
        for (int ind = 1; ind < N; ind++)
            for (int L = 0; L <= N; L++) {
                int len = ind + 1;
                int take = len <= L ? price[ind] + dp[ind][L - len] : Integer.MIN_VALUE;
                dp[ind][L] = Math.max(take, dp[ind - 1][L]);
            }
        return dp[N - 1][N];
    }
}
```

#### Approach 4: Space optimisation — single array, left to right
**Complexity:** O(N²) time, O(N) space.

**C++**
```cpp
int cutRod(vector<int>& price, int N) {
    vector<int> prev(N + 1, 0);
    for (int L = 0; L <= N; L++) prev[L] = L * price[0];
    for (int ind = 1; ind < N; ind++)
        for (int L = 0; L <= N; L++) {
            int len = ind + 1;
            int take = len <= L ? price[ind] + prev[L - len] : INT_MIN;
            prev[L] = max(take, prev[L]);
        }
    return prev[N];
}
```

**Java**
```java
class Solution {
    static int cutRod(int[] price, int N) {
        int[] prev = new int[N + 1];
        for (int L = 0; L <= N; L++) prev[L] = L * price[0];
        for (int ind = 1; ind < N; ind++)
            for (int L = 0; L <= N; L++) {
                int len = ind + 1;
                int take = len <= L ? price[ind] + prev[L - len] : Integer.MIN_VALUE;
                prev[L] = Math.max(take, prev[L]);
            }
        return prev[N];
    }
}
```

#### Key Takeaways
- Recognising the knapsack in disguise is the whole problem. Here the item weight is the piece length.

[↑ Contents](#contents) · [← Previous](#p412) · [Next →](#p414)

---

## LIS

<a id="p414"></a>

### 30. Longest Increasing Subsequence

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › LIS | Core | No | [LeetCode](https://leetcode.com/problems/longest-increasing-subsequence/) | [Watch](https://youtu.be/on2hvxBXJH4) |

> **Video note:** the sheet links *DP 43 — LIS using Binary Search*. The earlier LIS lectures are summarised here too:
> - *DP 41*: recursion and memoization;
> - *DP 42*: tabulation, space optimisation and the O(n²) 1-D algorithm.
>
> All the LIS approaches are therefore in one place.

#### Problem Statement
**Longest Increasing Subsequence:** return the length of the longest **strictly increasing** subsequence.

```text
nums = [10,9,2,5,3,7,101,18]  ->  4   ([2,3,7,18] or [2,5,7,101])
nums = [0,1,0,3,2,3]          ->  4
nums = [7,7,7,7]              ->  1
```

#### Intuition
- **Recursion (DP 41).** Try all subsequences, but remember the **previous index taken**, since the next element must be larger:
  - state `f(ind, prev)`;
  - not take: `f(ind+1, prev)`;
  - take (if `prev == −1 || a[ind] > a[prev]`): `1 + f(ind+1, ind)`;
  - base case `ind == n` returns 0.

  `prev` ranges over `−1 … n−1`, so the dp is stored with a **coordinate shift of +1**: `dp[ind][prev+1]`.
- **1-D algorithm (DP 42).** `dp[i]` is the length of the LIS **ending** at `i`, equal to `1 + max(dp[j])` over `j < i` with `a[j] < a[i]`. This version is also easy to trace back for printing (415).
- **Binary search (DP 43).** For `n = 10⁵`, n² is too slow:
  - keep `temp`, where `temp[k]` is the smallest tail of any increasing subsequence of length `k+1`;
  - for each `x`: if `x > temp.back()`, append it; otherwise overwrite `*lower_bound(temp, x)` with `x`;
  - `temp.size()` is the answer. `temp` itself is **not** necessarily an LIS; only its length is meaningful.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) time, O(n) stack.

**C++**
```cpp
int lisRec(int ind, int prev, vector<int>& a) {
    if (ind == (int)a.size()) return 0;
    int notTake = lisRec(ind + 1, prev, a);
    int take = 0;
    if (prev == -1 || a[ind] > a[prev]) take = 1 + lisRec(ind + 1, ind, a);
    return max(take, notTake);
}
int lengthOfLISRec(vector<int>& a) { return lisRec(0, -1, a); }
```

**Java**
```java
class Solution {
    static int lisRec(int ind, int prev, int[] a) {
        if (ind == a.length) return 0;
        int notTake = lisRec(ind + 1, prev, a);
        int take = 0;
        if (prev == -1 || a[ind] > a[prev]) take = 1 + lisRec(ind + 1, ind, a);
        return Math.max(take, notTake);
    }
    static int lengthOfLISRec(int[] a) { return lisRec(0, -1, a); }
}
```

#### Approach 2: Memoization — dp[n][n+1] with prev shifted by +1
**Complexity:** O(n²) time, O(n²) + O(n) stack.

**C++**
```cpp
int lisMemo(int ind, int prev, vector<int>& a, vector<vector<int>>& dp) {
    if (ind == (int)a.size()) return 0;
    if (dp[ind][prev + 1] != -1) return dp[ind][prev + 1];
    int notTake = lisMemo(ind + 1, prev, a, dp);
    int take = 0;
    if (prev == -1 || a[ind] > a[prev]) take = 1 + lisMemo(ind + 1, ind, a, dp);
    return dp[ind][prev + 1] = max(take, notTake);
}
int lengthOfLISMemo(vector<int>& a) {
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return lisMemo(0, -1, a, dp);
}
```

**Java**
```java
class Solution {
    static int lisMemo(int ind, int prev, int[] a, int[][] dp) {
        if (ind == a.length) return 0;
        if (dp[ind][prev + 1] != -1) return dp[ind][prev + 1];
        int notTake = lisMemo(ind + 1, prev, a, dp);
        int take = 0;
        if (prev == -1 || a[ind] > a[prev]) take = 1 + lisMemo(ind + 1, ind, a, dp);
        return dp[ind][prev + 1] = Math.max(take, notTake);
    }
    static int lengthOfLISMemo(int[] a) {
        int n = a.length;
        int[][] dp = new int[n][n + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return lisMemo(0, -1, a, dp);
    }
}
```

#### Approach 3: Tabulation — dp[n+1][n+1]
Loop `ind` from `n−1` down to 0, and `prev` from `ind−1` down to −1. Write everything with the `+1` shift for `prev`.

**Complexity:** O(n²) time, O(n²) space.

**C++**
```cpp
int lengthOfLISTab(vector<int>& a) {
    int n = a.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int ind = n - 1; ind >= 0; ind--)
        for (int prev = ind - 1; prev >= -1; prev--) {
            int notTake = dp[ind + 1][prev + 1];
            int take = 0;
            if (prev == -1 || a[ind] > a[prev]) take = 1 + dp[ind + 1][ind + 1];
            dp[ind][prev + 1] = max(take, notTake);
        }
    return dp[0][0];
}
```

**Java**
```java
class Solution {
    static int lengthOfLISTab(int[] a) {
        int n = a.length;
        int[][] dp = new int[n + 1][n + 1];
        for (int ind = n - 1; ind >= 0; ind--)
            for (int prev = ind - 1; prev >= -1; prev--) {
                int notTake = dp[ind + 1][prev + 1];
                int take = 0;
                if (prev == -1 || a[ind] > a[prev]) take = 1 + dp[ind + 1][ind + 1];
                dp[ind][prev + 1] = Math.max(take, notTake);
            }
        return dp[0][0];
    }
}
```

#### Approach 4: Space optimisation — `next` and `cur` of size n+1
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
int lengthOfLISSpace(vector<int>& a) {
    int n = a.size();
    vector<int> next(n + 1, 0), cur(n + 1, 0);
    for (int ind = n - 1; ind >= 0; ind--) {
        for (int prev = ind - 1; prev >= -1; prev--) {
            int notTake = next[prev + 1];
            int take = 0;
            if (prev == -1 || a[ind] > a[prev]) take = 1 + next[ind + 1];
            cur[prev + 1] = max(take, notTake);
        }
        next = cur;
    }
    return next[0];
}
```

**Java**
```java
class Solution {
    static int lengthOfLISSpace(int[] a) {
        int n = a.length;
        int[] next = new int[n + 1];
        for (int ind = n - 1; ind >= 0; ind--) {
            int[] cur = new int[n + 1];
            for (int prev = ind - 1; prev >= -1; prev--) {
                int notTake = next[prev + 1];
                int take = 0;
                if (prev == -1 || a[ind] > a[prev]) take = 1 + next[ind + 1];
                cur[prev + 1] = Math.max(take, notTake);
            }
            next = cur;
        }
        return next[0];
    }
}
```

#### Approach 5: 1-D algorithm — dp[i] = LIS ending at i (DP 42)
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
int lengthOfLIS1D(vector<int>& a) {
    int n = a.size(), best = 1;
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++)
            if (a[prev] < a[i]) dp[i] = max(dp[i], 1 + dp[prev]);
        best = max(best, dp[i]);
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int lengthOfLIS1D(int[] a) {
        int n = a.length, best = 1;
        int[] dp = new int[n];
        Arrays.fill(dp, 1);
        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++)
                if (a[prev] < a[i]) dp[i] = Math.max(dp[i], 1 + dp[prev]);
            best = Math.max(best, dp[i]);
        }
        return best;
    }
}
```

#### Approach 6: Binary search — O(n log n) (DP 43, the linked video)
**Complexity:** O(n log n) time, O(n) space.

**C++**
```cpp
int lengthOfLIS(vector<int>& a) {
    vector<int> temp;
    for (int x : a) {
        if (temp.empty() || x > temp.back()) temp.push_back(x);
        else *lower_bound(temp.begin(), temp.end(), x) = x;   // replace the first element >= x
    }
    return temp.size();
}
```

**Java**
```java
class Solution {
    static int lengthOfLIS(int[] a) {
        ArrayList<Integer> temp = new ArrayList<>();
        for (int x : a) {
            if (temp.isEmpty() || x > temp.get(temp.size() - 1)) { temp.add(x); continue; }
            int lo = 0, hi = temp.size() - 1;                  // lower_bound: first index with temp[i] >= x
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (temp.get(mid) >= x) hi = mid; else lo = mid + 1;
            }
            temp.set(lo, x);
        }
        return temp.size();
    }
}
```

#### Edge Cases & Pitfalls
- **Strictly** increasing needs `lower_bound` (`≥ x`). For non-decreasing, use `upper_bound`.
- `temp` is not the LIS. For `[3, 4, 1]`, `temp = [1, 4]`, which isn't a subsequence.
- The +1 shift for `prev` is what lets `prev = −1` index the table.

#### Key Takeaways
- Three tiers: the `(ind, prev)` DP at O(n²) time and space, the 1-D DP at O(n²) time and O(n) space, and patience sorting at O(n log n).

[↑ Contents](#contents) · [← Previous](#p413) · [Next →](#p415)

---

<a id="p415"></a>

### 31. Print Longest Increasing Subsequence

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › LIS | Pro | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/print-longest-increasing-subsequence) | [Watch](https://youtu.be/IFfYfonAFGc) |

#### Problem Statement
Print one **longest increasing subsequence** (any valid one).

```text
arr = [5, 4, 11, 1, 16, 8]  ->  [5, 11, 16]   (length 3)
arr = [1, 2, 2]             ->  [1, 2]
```

#### Intuition — 1-D dp plus a parent ("hash") array
The video first converts the memoized `(ind, prev)` DP to tabulation (see 414), then introduces the algorithm used in most write-ups:
- **`dp[i]`** is the LIS length **ending** at index `i`.
- **`hash[i]`** is the previous index in that LIS. It starts as `hash[i] = i`, which marks the start of a chain.

Once every `dp[i]` is computed:
- Find `lastIndex = argmax dp`.
- Follow `hash` back until `hash[i] == i`.
- Reverse the collected elements.

The (ind, prev) tables are awkward to trace back, which is why the video switches to this form for printing.

#### Approach 1: Tabulation + parent array
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
vector<int> printLIS(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1), hash(n);
    int best = 1, lastIndex = 0;
    for (int i = 0; i < n; i++) {
        hash[i] = i;
        for (int prev = 0; prev < i; prev++)
            if (a[prev] < a[i] && 1 + dp[prev] > dp[i]) {
                dp[i] = 1 + dp[prev];
                hash[i] = prev;
            }
        if (dp[i] > best) { best = dp[i]; lastIndex = i; }
    }
    vector<int> lis = {a[lastIndex]};
    while (hash[lastIndex] != lastIndex) {
        lastIndex = hash[lastIndex];
        lis.push_back(a[lastIndex]);
    }
    reverse(lis.begin(), lis.end());
    return lis;
}
```

**Java**
```java
class Solution {
    static List<Integer> printLIS(int[] a) {
        int n = a.length;
        int[] dp = new int[n], hash = new int[n];
        int best = 1, lastIndex = 0;
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            hash[i] = i;
            for (int prev = 0; prev < i; prev++)
                if (a[prev] < a[i] && 1 + dp[prev] > dp[i]) {
                    dp[i] = 1 + dp[prev];
                    hash[i] = prev;
                }
            if (dp[i] > best) { best = dp[i]; lastIndex = i; }
        }
        List<Integer> lis = new ArrayList<>();
        lis.add(a[lastIndex]);
        while (hash[lastIndex] != lastIndex) {
            lastIndex = hash[lastIndex];
            lis.add(a[lastIndex]);
        }
        Collections.reverse(lis);
        return lis;
    }
}
```

#### Approach 2: O(n log n) with reconstruction *(not in video)*
Store the **index** of each tail in `tailIdx`, and for every element remember its predecessor (the tail one slot to its left at insertion time).

**Complexity:** O(n log n) time, O(n) space.

**C++**
```cpp
vector<int> printLISFast(vector<int>& a) {
    int n = a.size();
    vector<int> tailIdx, parent(n, -1);
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = tailIdx.size();                         // first tail with a[tail] >= a[i]
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (a[tailIdx[mid]] >= a[i]) hi = mid; else lo = mid + 1;
        }
        if (lo > 0) parent[i] = tailIdx[lo - 1];
        if (lo == (int)tailIdx.size()) tailIdx.push_back(i); else tailIdx[lo] = i;
    }
    vector<int> lis;
    for (int i = tailIdx.empty() ? -1 : tailIdx.back(); i != -1; i = parent[i]) lis.push_back(a[i]);
    reverse(lis.begin(), lis.end());
    return lis;
}
```

**Java**
```java
class Solution {
    static List<Integer> printLISFast(int[] a) {
        int n = a.length;
        int[] tailIdx = new int[n], parent = new int[n];
        Arrays.fill(parent, -1);
        int len = 0;
        for (int i = 0; i < n; i++) {
            int lo = 0, hi = len;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (a[tailIdx[mid]] >= a[i]) hi = mid; else lo = mid + 1;
            }
            if (lo > 0) parent[i] = tailIdx[lo - 1];
            tailIdx[lo] = i;
            if (lo == len) len++;
        }
        List<Integer> lis = new ArrayList<>();
        for (int i = len == 0 ? -1 : tailIdx[len - 1]; i != -1; i = parent[i]) lis.add(a[i]);
        Collections.reverse(lis);
        return lis;
    }
}
```

#### Edge Cases & Pitfalls
- Initialise `hash[i] = i` **before** the inner loop. The backtracking stops at the element that points to itself.
- Ties: updating only on a strict `>` keeps the earliest predecessor. Any LIS is acceptable.

#### Key Takeaways
- To print a DP solution, store the choice made (the parent) alongside the value, then walk back.

[↑ Contents](#contents) · [← Previous](#p414) · [Next →](#p416)

---

<a id="p416"></a>

### 32. Largest Divisible Subset

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › LIS | Core | No | [LeetCode](https://leetcode.com/problems/largest-divisible-subset/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/largest-divisible-subset) | [Watch](https://youtu.be/gDuZwBW9VvM) |

#### Problem Statement
**Largest Divisible Subset:** given distinct positive integers, return the largest subset in which every pair `(a, b)` satisfies `a % b == 0` or `b % a == 0`.

```text
nums = [1, 2, 3]       ->  [1, 2]   (or [1, 3])
nums = [1, 2, 4, 8]    ->  [1, 2, 4, 8]
nums = [1, 16, 7, 8, 4] -> [1, 4, 8, 16]
```

#### Intuition — sort, then run "print LIS" with a divisibility test
- **Subset, not subsequence.** Order is free, so **sort** first.
- **Chains suffice.** In sorted order, if each element divides the next, then every pair divides, because divisibility is transitive.
- **So:**
  - Find the longest chain in which `a[i] % a[prev] == 0`.
  - This is the LIS-printing algorithm (415), with `a[prev] < a[i]` replaced by divisibility.

#### Approach 1: Sort + 1-D dp + parent array (as in the video)
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
vector<int> largestDivisibleSubset(vector<int>& a) {
    sort(a.begin(), a.end());
    int n = a.size(), best = 1, lastIndex = 0;
    vector<int> dp(n, 1), hash(n);
    for (int i = 0; i < n; i++) {
        hash[i] = i;
        for (int prev = 0; prev < i; prev++)
            if (a[i] % a[prev] == 0 && 1 + dp[prev] > dp[i]) {
                dp[i] = 1 + dp[prev];
                hash[i] = prev;
            }
        if (dp[i] > best) { best = dp[i]; lastIndex = i; }
    }
    vector<int> res = {a[lastIndex]};
    while (hash[lastIndex] != lastIndex) {
        lastIndex = hash[lastIndex];
        res.push_back(a[lastIndex]);
    }
    reverse(res.begin(), res.end());
    return res;
}
```

**Java**
```java
class Solution {
    static List<Integer> largestDivisibleSubset(int[] a) {
        Arrays.sort(a);
        int n = a.length, best = 1, lastIndex = 0;
        int[] dp = new int[n], hash = new int[n];
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            hash[i] = i;
            for (int prev = 0; prev < i; prev++)
                if (a[i] % a[prev] == 0 && 1 + dp[prev] > dp[i]) {
                    dp[i] = 1 + dp[prev];
                    hash[i] = prev;
                }
            if (dp[i] > best) { best = dp[i]; lastIndex = i; }
        }
        List<Integer> res = new ArrayList<>();
        res.add(a[lastIndex]);
        while (hash[lastIndex] != lastIndex) {
            lastIndex = hash[lastIndex];
            res.add(a[lastIndex]);
        }
        Collections.reverse(res);
        return res;
    }
}
```

#### Edge Cases & Pitfalls
- Without sorting, the chain condition no longer implies pairwise divisibility.
- A single element is always a valid subset.

#### Key Takeaways
- "Subset with a pairwise transitive relation" becomes "sort, then LIS with that relation".

[↑ Contents](#contents) · [← Previous](#p415) · [Next →](#p417)

---

<a id="p417"></a>

### 33. Longest String Chain

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › LIS | Core | No | [LeetCode](https://leetcode.com/problems/longest-string-chain/) | [Watch](https://youtu.be/YY8iBaYcc4g) |

#### Problem Statement
**Longest String Chain:** `wordA` is a predecessor of `wordB` if inserting **exactly one** letter anywhere in `wordA` gives `wordB`. Return the length of the longest chain `w1 → w2 → … → wk`. Words can be picked in any order.

```text
words = ["a","b","ba","bca","bda","bdca"]   ->  4   (a -> ba -> bda -> bdca)
words = ["xbc","pcxbcf","xb","cxbc","pcxbc"] -> 5
words = ["abcd","dbqca"]                     ->  1
```

#### Intuition — LIS on words sorted by length
- **Order doesn't matter**, so sort the words by length.
- **Then run 1-D LIS**, where the "increasing" test is `compare(longer, shorter)`:
  - the lengths must differ by exactly 1;
  - two pointers walk both words, and the longer word's pointer may skip **one** mismatching character.

#### Approach 1: Sort + 1-D LIS with a custom compare (as in the video)
**Complexity:** O(n²·L) time, where L is the word length, plus O(n log n) for the sort; O(n) space.

**C++**
```cpp
bool isPred(const string& s1, const string& s2) {    // can s2 be formed by deleting one char of s1?
    if (s1.size() != s2.size() + 1) return false;
    size_t i = 0, j = 0;
    while (i < s1.size()) {
        if (j < s2.size() && s1[i] == s2[j]) { i++; j++; }
        else i++;
    }
    return j == s2.size();                           // every char of s2 matched, exactly one skipped
}
int longestStrChain(vector<string>& words) {
    sort(words.begin(), words.end(), [](const string& x, const string& y) { return x.size() < y.size(); });
    int n = words.size(), best = 1;
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++)
            if (isPred(words[i], words[prev]) && 1 + dp[prev] > dp[i]) dp[i] = 1 + dp[prev];
        best = max(best, dp[i]);
    }
    return best;
}
```

**Java**
```java
class Solution {
    static boolean isPred(String s1, String s2) {
        if (s1.length() != s2.length() + 1) return false;
        int i = 0, j = 0;
        while (i < s1.length()) {
            if (j < s2.length() && s1.charAt(i) == s2.charAt(j)) { i++; j++; }
            else i++;
        }
        return j == s2.length();
    }
    static int longestStrChain(String[] words) {
        Arrays.sort(words, (x, y) -> x.length() - y.length());
        int n = words.length, best = 1;
        int[] dp = new int[n];
        Arrays.fill(dp, 1);
        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++)
                if (isPred(words[i], words[prev]) && 1 + dp[prev] > dp[i]) dp[i] = 1 + dp[prev];
            best = Math.max(best, dp[i]);
        }
        return best;
    }
}
```

#### Approach 2: Hash map — delete each character *(not in video)*
Process words by increasing length. `best[w] = 1 + max(best[w with one char removed])`, looking each candidate up in a hash map.

**Complexity:** O(n·L²) time, O(n·L) space. Faster when n is large and words are short.

**C++**
```cpp
int longestStrChainMap(vector<string>& words) {
    sort(words.begin(), words.end(), [](const string& x, const string& y) { return x.size() < y.size(); });
    unordered_map<string, int> best;
    int ans = 1;
    for (const string& w : words) {
        int cur = 1;
        for (size_t k = 0; k < w.size(); k++) {
            string pred = w.substr(0, k) + w.substr(k + 1);
            auto it = best.find(pred);
            if (it != best.end()) cur = max(cur, it->second + 1);
        }
        best[w] = max(best[w], cur);
        ans = max(ans, cur);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int longestStrChainMap(String[] words) {
        Arrays.sort(words, (x, y) -> x.length() - y.length());
        Map<String, Integer> best = new HashMap<>();
        int ans = 1;
        for (String w : words) {
            int cur = 1;
            for (int k = 0; k < w.length(); k++) {
                String pred = w.substring(0, k) + w.substring(k + 1);
                cur = Math.max(cur, best.getOrDefault(pred, 0) + 1);
            }
            best.put(w, Math.max(best.getOrDefault(w, 0), cur));
            ans = Math.max(ans, cur);
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- Insertion can happen **anywhere**, so it's not just a prefix or suffix check. The two-pointer allows exactly one skip.
- The length difference must be exactly 1. Equal-length words are never predecessors.

#### Key Takeaways
- LIS is a template: "sort by a key, then dp over the previous elements that satisfy a relation".

[↑ Contents](#contents) · [← Previous](#p416) · [Next →](#p418)

---

<a id="p418"></a>

### 34. Longest Bitonic Subsequence

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › LIS | Core | No | — | [Watch](https://youtu.be/y4vN0WNdrlg) |

#### Problem Statement
**Longest Bitonic Subsequence:** a subsequence that strictly **increases, then strictly decreases**. In the video's Code Studio version, a purely increasing or purely decreasing sequence also counts. Return the maximum length.

```text
arr = [1, 11, 2, 10, 4, 5, 2, 1]   ->  6   (1 2 10 4 2 1)
arr = [12, 11, 40, 5, 3, 1]        ->  5   (12 40 5 3 1)
arr = [80, 60, 30, 40, 20, 10]     ->  5   (80 60 30 20 10)
```

#### Intuition — LIS from the left plus LIS from the right
- **`dp1[i]`** is the LIS **ending** at `i`, scanning left to right.
- **`dp2[i]`** is the longest decreasing subsequence **starting** at `i`. That's the same as the LIS ending at `i` when scanning right to left.
- **Each peak `i`** gives a bitonic length of `dp1[i] + dp2[i] − 1`, since the peak is counted twice.
- **The answer** is the maximum over all `i`.

#### Approach 1: Two 1-D LIS passes (as in the video)
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
int longestBitonicSequence(vector<int>& a) {
    int n = a.size();
    vector<int> dp1(n, 1), dp2(n, 1);
    for (int i = 0; i < n; i++)
        for (int prev = 0; prev < i; prev++)
            if (a[prev] < a[i]) dp1[i] = max(dp1[i], 1 + dp1[prev]);
    for (int i = n - 1; i >= 0; i--)
        for (int nxt = n - 1; nxt > i; nxt--)
            if (a[nxt] < a[i]) dp2[i] = max(dp2[i], 1 + dp2[nxt]);
    int best = 0;
    for (int i = 0; i < n; i++) best = max(best, dp1[i] + dp2[i] - 1);
    return best;
}
```

**Java**
```java
class Solution {
    static int longestBitonicSequence(int[] a) {
        int n = a.length;
        int[] dp1 = new int[n], dp2 = new int[n];
        Arrays.fill(dp1, 1);
        Arrays.fill(dp2, 1);
        for (int i = 0; i < n; i++)
            for (int prev = 0; prev < i; prev++)
                if (a[prev] < a[i]) dp1[i] = Math.max(dp1[i], 1 + dp1[prev]);
        for (int i = n - 1; i >= 0; i--)
            for (int nxt = n - 1; nxt > i; nxt--)
                if (a[nxt] < a[i]) dp2[i] = Math.max(dp2[i], 1 + dp2[nxt]);
        int best = 0;
        for (int i = 0; i < n; i++) best = Math.max(best, dp1[i] + dp2[i] - 1);
        return best;
    }
}
```

#### Edge Cases & Pitfalls
- **Variant:** GfG's current version requires **both** an increasing and a decreasing part. Only consider peaks with `dp1[i] > 1 && dp2[i] > 1`, and return 0 if there are none.
- Both sides must be **strict**, so equal neighbours can't straddle the peak.

#### Key Takeaways
- "Up then down" splits into a prefix DP and a suffix DP joined at a pivot. The same idea appears in Trapping Rain Water and Candy.

[↑ Contents](#contents) · [← Previous](#p417) · [Next →](#p419)

---

<a id="p419"></a>

### 35. Number of Longest Increasing Subsequences

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › LIS | Core | No | [LeetCode](https://leetcode.com/problems/number-of-longest-increasing-subsequence/) | [Watch](https://youtu.be/cKVl1TFdNXg) |

#### Problem Statement
**Number of Longest Increasing Subsequences:** count how many strictly increasing subsequences have the maximum length.

```text
nums = [1, 3, 5, 4, 7]   ->  2   ([1,3,4,7], [1,3,5,7])
nums = [2, 2, 2, 2, 2]   ->  5   (five LIS of length 1)
nums = [1, 5, 4, 3, 2, 6, 7, 10, 8, 9]  ->  4   (1, {5|4|3|2}, 6, 7, 8, 9)
```

#### Intuition — carry a count next to every length
Next to `dp[i]` (the LIS length ending at `i`), keep `cnt[i]`, the number of LIS of that length ending at `i`. For each `prev < i` with `a[prev] < a[i]`:
- if `dp[prev] + 1 > dp[i]`, a **longer** length has been found: set `dp[i] = dp[prev] + 1` and `cnt[i] = cnt[prev]`, inheriting the count;
- else if `dp[prev] + 1 == dp[i]`, it's **another way** to reach the same length: `cnt[i] += cnt[prev]`.

The answer is the sum of `cnt[i]` over all `i` with `dp[i] == max`.

#### Approach 1: 1-D dp plus a count array (as in the video)
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
int findNumberOfLIS(vector<int>& a) {
    int n = a.size(), maxi = 1;
    vector<int> dp(n, 1), cnt(n, 1);
    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (a[prev] < a[i] && dp[prev] + 1 > dp[i]) {
                dp[i] = dp[prev] + 1;
                cnt[i] = cnt[prev];
            } else if (a[prev] < a[i] && dp[prev] + 1 == dp[i]) {
                cnt[i] += cnt[prev];
            }
        }
        maxi = max(maxi, dp[i]);
    }
    int total = 0;
    for (int i = 0; i < n; i++) if (dp[i] == maxi) total += cnt[i];
    return total;
}
```

**Java**
```java
class Solution {
    static int findNumberOfLIS(int[] a) {
        int n = a.length, maxi = 1;
        int[] dp = new int[n], cnt = new int[n];
        Arrays.fill(dp, 1);
        Arrays.fill(cnt, 1);
        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++) {
                if (a[prev] < a[i] && dp[prev] + 1 > dp[i]) {
                    dp[i] = dp[prev] + 1;
                    cnt[i] = cnt[prev];
                } else if (a[prev] < a[i] && dp[prev] + 1 == dp[i]) {
                    cnt[i] += cnt[prev];
                }
            }
            maxi = Math.max(maxi, dp[i]);
        }
        int total = 0;
        for (int i = 0; i < n; i++) if (dp[i] == maxi) total += cnt[i];
        return total;
    }
}
```

#### Edge Cases & Pitfalls
- On a new maximum, **inherit** the count (`cnt[i] = cnt[prev]`); don't reset it to 1.
- When all elements are equal, every single element is an LIS of length 1, so the answer is n.

#### Key Takeaways
- To count optimal solutions, store (best value, number of ways) per state, and merge with ">" (replace) and "==" (add).

[↑ Contents](#contents) · [← Previous](#p418) · [Next →](#p420)

---

## DP on strings

<a id="p420"></a>

### 36. Longest common subsequence

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Core | No | [LeetCode](https://leetcode.com/problems/longest-common-subsequence/) | [Watch](https://youtu.be/-zI4mrF2Pb4) |

#### Problem Statement
**Longest Common Subsequence:** return the length of the longest subsequence common to `s1` and `s2`.

```text
s1 = "abcde", s2 = "ace"   ->  3   ("ace")
s1 = "adebc", s2 = "dcadb" ->  3   ("adb")
s1 = "abc",   s2 = "def"   ->  0
```

#### Intuition — compare characters from the ends
`f(i, j)` is the LCS of `s1[0 … i]` and `s2[0 … j]`.
- **Match** (`s1[i] == s2[j]`): `1 + f(i−1, j−1)`, so both characters join the LCS.
- **No match:** `max(f(i−1, j), f(i, j−1))`, which drops one character from either string.
- **Base case:** `i < 0 || j < 0` returns 0.

For tabulation, the video **shifts indices by 1**: `f(i, j)` covers the first `i` and `j` characters, and row/column 0 is the empty-string base case. That avoids negative indices.

#### Approach 1: Recursion
**Complexity:** O(2^(n+m)) time, O(n+m) stack.

**C++**
```cpp
int lcsRec(int i, int j, string& a, string& b) {
    if (i < 0 || j < 0) return 0;
    if (a[i] == b[j]) return 1 + lcsRec(i - 1, j - 1, a, b);
    return max(lcsRec(i - 1, j, a, b), lcsRec(i, j - 1, a, b));
}
int longestCommonSubsequenceRec(string a, string b) { return lcsRec(a.size() - 1, b.size() - 1, a, b); }
```

**Java**
```java
class Solution {
    static int lcsRec(int i, int j, String a, String b) {
        if (i < 0 || j < 0) return 0;
        if (a.charAt(i) == b.charAt(j)) return 1 + lcsRec(i - 1, j - 1, a, b);
        return Math.max(lcsRec(i - 1, j, a, b), lcsRec(i, j - 1, a, b));
    }
    static int longestCommonSubsequenceRec(String a, String b) { return lcsRec(a.length() - 1, b.length() - 1, a, b); }
}
```

#### Approach 2: Memoization (shifted: f(i, j) uses the first i and j characters)
**Complexity:** O(n·m) time, O(n·m) + O(n+m) stack.

**C++**
```cpp
int lcsMemo(int i, int j, string& a, string& b, vector<vector<int>>& dp) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (a[i - 1] == b[j - 1]) return dp[i][j] = 1 + lcsMemo(i - 1, j - 1, a, b, dp);
    return dp[i][j] = max(lcsMemo(i - 1, j, a, b, dp), lcsMemo(i, j - 1, a, b, dp));
}
int longestCommonSubsequenceMemo(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return lcsMemo(n, m, a, b, dp);
}
```

**Java**
```java
class Solution {
    static int lcsMemo(int i, int j, String a, String b, int[][] dp) {
        if (i == 0 || j == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        if (a.charAt(i - 1) == b.charAt(j - 1)) return dp[i][j] = 1 + lcsMemo(i - 1, j - 1, a, b, dp);
        return dp[i][j] = Math.max(lcsMemo(i - 1, j, a, b, dp), lcsMemo(i, j - 1, a, b, dp));
    }
    static int longestCommonSubsequenceMemo(String a, String b) {
        int n = a.length(), m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return lcsMemo(n, m, a, b, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
int longestCommonSubsequenceTab(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));       // row 0 / col 0 = empty string
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (a[i - 1] == b[j - 1]) ? 1 + dp[i - 1][j - 1] : max(dp[i - 1][j], dp[i][j - 1]);
    return dp[n][m];
}
```

**Java**
```java
class Solution {
    static int longestCommonSubsequenceTab(String a, String b) {
        int n = a.length(), m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                dp[i][j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? 1 + dp[i - 1][j - 1] : Math.max(dp[i - 1][j], dp[i][j - 1]);
        return dp[n][m];
    }
}
```

#### Approach 4: Space optimisation — `prev` and `cur` rows
**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
int longestCommonSubsequence(string a, string b) {
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cur[j] = (a[i - 1] == b[j - 1]) ? 1 + prev[j - 1] : max(prev[j], cur[j - 1]);
        prev = cur;
    }
    return prev[m];
}
```

**Java**
```java
class Solution {
    static int longestCommonSubsequence(String a, String b) {
        int n = a.length(), m = b.length();
        int[] prev = new int[m + 1];
        for (int i = 1; i <= n; i++) {
            int[] cur = new int[m + 1];
            for (int j = 1; j <= m; j++)
                cur[j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? 1 + prev[j - 1] : Math.max(prev[j], cur[j - 1]);
            prev = cur;
        }
        return prev[m];
    }
}
```

#### Printing the LCS (DP 26 — the follow-up lecture)
Fill the shifted table, then walk back from `(n, m)`:
- on a **match**, take the character and move diagonally;
- otherwise, move towards the larger of `dp[i−1][j]` and `dp[i][j−1]`.

The characters come out in reverse, so build the string from the end.

**Complexity:** O(n·m) time and space.

**C++**
```cpp
string printLCS(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (a[i - 1] == b[j - 1]) ? 1 + dp[i - 1][j - 1] : max(dp[i - 1][j], dp[i][j - 1]);
    int len = dp[n][m], idx = len - 1, i = n, j = m;
    string s(len, '$');
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) { s[idx--] = a[i - 1]; i--; j--; }
        else if (dp[i - 1][j] > dp[i][j - 1]) i--;
        else j--;
    }
    return s;
}
```

**Java**
```java
class Solution {
    static String printLCS(String a, String b) {
        int n = a.length(), m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                dp[i][j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? 1 + dp[i - 1][j - 1] : Math.max(dp[i - 1][j], dp[i][j - 1]);
        StringBuilder sb = new StringBuilder();
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (a.charAt(i - 1) == b.charAt(j - 1)) { sb.append(a.charAt(i - 1)); i--; j--; }
            else if (dp[i - 1][j] > dp[i][j - 1]) i--;
            else j--;
        }
        return sb.reverse().toString();
    }
}
```

#### Edge Cases & Pitfalls
- In the shifted table, `dp[i][j]` compares `a[i−1]` with `b[j−1]`. Off-by-one errors here are the most common LCS bug.
- In the 1-D version, `cur[j−1]` (left, current row) and `prev[j−1]` (diagonal) must come from different rows.

#### Key Takeaways
- LCS is the parent of the string-DP family: LPS, minimum insertions, delete operations, SCS, edit distance.

[↑ Contents](#contents) · [← Previous](#p419) · [Next →](#p421)

---

<a id="p421"></a>

### 37. Longest common substring

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Core | No | — | [Watch](https://youtu.be/_wP9mWNPL5w) |

#### Problem Statement
**Longest Common Substring:** return the length of the longest **contiguous** string that appears in both `s1` and `s2`.

```text
s1 = "abcjklp", s2 = "acjkp"   ->  3   ("cjk")
s1 = "wasdijkl", s2 = "wsdjkl" ->  3   ("jkl")
```

#### Intuition — consecutive matches only
- **`dp[i][j]`** is the length of the common substring **ending** at `s1[i−1]` and `s2[j−1]`.
- **On a match:** `dp[i][j] = 1 + dp[i−1][j−1]`.
- **On a mismatch:** `dp[i][j] = 0`, because the run is broken. Unlike LCS, you can't carry the best value from a neighbour.
- **The answer** is the **maximum over all cells**, not `dp[n][m]`.

The video notes that a recursive formulation exists but needs an extra "current run" parameter, so it goes straight to tabulation.

#### Approach 1: Brute force — every pair of starting positions *(not in video)*
**Complexity:** O(n·m·min(n,m)) time, O(1) space.

**C++**
```cpp
int longestCommonSubstrBrute(string a, string b) {
    int n = a.size(), m = b.size(), best = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int k = 0;
            while (i + k < n && j + k < m && a[i + k] == b[j + k]) k++;
            best = max(best, k);
        }
    return best;
}
```

**Java**
```java
class Solution {
    static int longestCommonSubstrBrute(String a, String b) {
        int n = a.length(), m = b.length(), best = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                int k = 0;
                while (i + k < n && j + k < m && a.charAt(i + k) == b.charAt(j + k)) k++;
                best = Math.max(best, k);
            }
        return best;
    }
}
```

#### Approach 2: Tabulation (as in the video)
**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
int longestCommonSubstrTab(string a, string b) {
    int n = a.size(), m = b.size(), best = 0;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            dp[i][j] = (a[i - 1] == b[j - 1]) ? 1 + dp[i - 1][j - 1] : 0;
            best = max(best, dp[i][j]);
        }
    return best;
}
```

**Java**
```java
class Solution {
    static int longestCommonSubstrTab(String a, String b) {
        int n = a.length(), m = b.length(), best = 0;
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                dp[i][j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? 1 + dp[i - 1][j - 1] : 0;
                best = Math.max(best, dp[i][j]);
            }
        return best;
    }
}
```

#### Approach 3: Space optimisation
**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
int longestCommonSubstr(string a, string b) {
    int n = a.size(), m = b.size(), best = 0;
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cur[j] = (a[i - 1] == b[j - 1]) ? 1 + prev[j - 1] : 0;
            best = max(best, cur[j]);
        }
        prev = cur;
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int longestCommonSubstr(String a, String b) {
        int n = a.length(), m = b.length(), best = 0;
        int[] prev = new int[m + 1];
        for (int i = 1; i <= n; i++) {
            int[] cur = new int[m + 1];
            for (int j = 1; j <= m; j++) {
                cur[j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? 1 + prev[j - 1] : 0;
                best = Math.max(best, cur[j]);
            }
            prev = cur;
        }
        return best;
    }
}
```

#### Edge Cases & Pitfalls
- In C++, if you reuse `cur` without resetting it, a mismatch must **write 0**. The `: 0` branch does that, so a stale value can't leak in.

#### Key Takeaways
- Substring means a **reset to 0** on mismatch and the **maximum over the table**. Subsequence means carrying the best neighbour forward and reading `dp[n][m]`.

[↑ Contents](#contents) · [← Previous](#p420) · [Next →](#p422)

---

<a id="p422"></a>

### 38. Longest palindromic subsequence

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Core | No | [LeetCode](https://leetcode.com/problems/longest-palindromic-subsequence/) | [Watch](https://youtu.be/6i_T5kkfv4A) |

#### Problem Statement
**Longest Palindromic Subsequence:** return the length of the longest subsequence of `s` that is a palindrome.

```text
s = "bbbab"            ->  4   ("bbbb")
s = "cbbd"             ->  2   ("bb")
s = "bbabcbcab"        ->  7   ("babcbab")
```

#### Intuition — LPS(s) = LCS(s, reverse(s))
A palindromic subsequence reads the same forwards and backwards, so it is a common subsequence of `s` and `reverse(s)`. The longest common one is the longest palindrome. All four LCS approaches therefore apply directly.

#### Approach 1: Recursion
**Complexity:** O(2^(2n)) time, O(n) stack.

**C++**
```cpp
int lpsRec(int i, int j, string& a, string& b) {
    if (i < 0 || j < 0) return 0;
    if (a[i] == b[j]) return 1 + lpsRec(i - 1, j - 1, a, b);
    return max(lpsRec(i - 1, j, a, b), lpsRec(i, j - 1, a, b));
}
int longestPalindromeSubseqRec(string s) {
    string t(s.rbegin(), s.rend());
    return lpsRec(s.size() - 1, t.size() - 1, s, t);
}
```

**Java**
```java
class Solution {
    static int lpsRec(int i, int j, String a, String b) {
        if (i < 0 || j < 0) return 0;
        if (a.charAt(i) == b.charAt(j)) return 1 + lpsRec(i - 1, j - 1, a, b);
        return Math.max(lpsRec(i - 1, j, a, b), lpsRec(i, j - 1, a, b));
    }
    static int longestPalindromeSubseqRec(String s) {
        String t = new StringBuilder(s).reverse().toString();
        return lpsRec(s.length() - 1, t.length() - 1, s, t);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n²) time, O(n²) + O(n) stack.

**C++**
```cpp
int lpsMemo(int i, int j, string& a, string& b, vector<vector<int>>& dp) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (a[i - 1] == b[j - 1]) return dp[i][j] = 1 + lpsMemo(i - 1, j - 1, a, b, dp);
    return dp[i][j] = max(lpsMemo(i - 1, j, a, b, dp), lpsMemo(i, j - 1, a, b, dp));
}
int longestPalindromeSubseqMemo(string s) {
    string t(s.rbegin(), s.rend());
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    return lpsMemo(n, n, s, t, dp);
}
```

**Java**
```java
class Solution {
    static int lpsMemo(int i, int j, String a, String b, int[][] dp) {
        if (i == 0 || j == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        if (a.charAt(i - 1) == b.charAt(j - 1)) return dp[i][j] = 1 + lpsMemo(i - 1, j - 1, a, b, dp);
        return dp[i][j] = Math.max(lpsMemo(i - 1, j, a, b, dp), lpsMemo(i, j - 1, a, b, dp));
    }
    static int longestPalindromeSubseqMemo(String s) {
        String t = new StringBuilder(s).reverse().toString();
        int n = s.length();
        int[][] dp = new int[n + 1][n + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return lpsMemo(n, n, s, t, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n²) time, O(n²) space.

**C++**
```cpp
int longestPalindromeSubseqTab(string s) {
    string t(s.rbegin(), s.rend());
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (s[i - 1] == t[j - 1]) ? 1 + dp[i - 1][j - 1] : max(dp[i - 1][j], dp[i][j - 1]);
    return dp[n][n];
}
```

**Java**
```java
class Solution {
    static int longestPalindromeSubseqTab(String s) {
        String t = new StringBuilder(s).reverse().toString();
        int n = s.length();
        int[][] dp = new int[n + 1][n + 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (s.charAt(i - 1) == t.charAt(j - 1)) ? 1 + dp[i - 1][j - 1] : Math.max(dp[i - 1][j], dp[i][j - 1]);
        return dp[n][n];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
int longestPalindromeSubseq(string s) {
    string t(s.rbegin(), s.rend());
    int n = s.size();
    vector<int> prev(n + 1, 0), cur(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cur[j] = (s[i - 1] == t[j - 1]) ? 1 + prev[j - 1] : max(prev[j], cur[j - 1]);
        prev = cur;
    }
    return prev[n];
}
```

**Java**
```java
class Solution {
    static int longestPalindromeSubseq(String s) {
        String t = new StringBuilder(s).reverse().toString();
        int n = s.length();
        int[] prev = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            int[] cur = new int[n + 1];
            for (int j = 1; j <= n; j++)
                cur[j] = (s.charAt(i - 1) == t.charAt(j - 1)) ? 1 + prev[j - 1] : Math.max(prev[j], cur[j - 1]);
            prev = cur;
        }
        return prev[n];
    }
}
```

#### Key Takeaways
- Reverse-and-LCS is the trick. The interval DP `f(i, j)` on `s[i … j]` works too, and is the starting point for MCM-style problems.

[↑ Contents](#contents) · [← Previous](#p421) · [Next →](#p423)

---

<a id="p423"></a>

### 39. Minimum insertions to make string palindrome

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Pro | No | [LeetCode](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/) | [Watch](https://youtu.be/xPBLEj41rFU) |

#### Problem Statement
**Minimum insertions to make a string a palindrome:** return the minimum number of characters to insert anywhere in `s` to make it a palindrome.

```text
s = "zzazz"     ->  0
s = "mbadm"     ->  2   ("mbdadbm")
s = "leetcode"  ->  5
```

#### Intuition
- **Keep the LPS untouched.** It is already a palindrome.
- **Insert a mirror for everything else.** Each character outside the LPS needs one inserted copy on the other side.
- **So the answer is `n − LPS(s)`**, i.e. `n − LCS(s, reverse(s))`.

The video argues that inserting n characters (the full reverse) always works, and that keeping the longest palindromic core minimises the insertions.

#### Approach 1: Recursion (LCS on s and its reverse)
**Complexity:** exponential time, O(n) stack.

**C++**
```cpp
int miRec(int i, int j, string& a, string& b) {
    if (i < 0 || j < 0) return 0;
    if (a[i] == b[j]) return 1 + miRec(i - 1, j - 1, a, b);
    return max(miRec(i - 1, j, a, b), miRec(i, j - 1, a, b));
}
int minInsertionsRec(string s) {
    string t(s.rbegin(), s.rend());
    int n = s.size();
    return n - miRec(n - 1, n - 1, s, t);
}
```

**Java**
```java
class Solution {
    static int miRec(int i, int j, String a, String b) {
        if (i < 0 || j < 0) return 0;
        if (a.charAt(i) == b.charAt(j)) return 1 + miRec(i - 1, j - 1, a, b);
        return Math.max(miRec(i - 1, j, a, b), miRec(i, j - 1, a, b));
    }
    static int minInsertionsRec(String s) {
        String t = new StringBuilder(s).reverse().toString();
        int n = s.length();
        return n - miRec(n - 1, n - 1, s, t);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n²) time, O(n²) + O(n) stack.

**C++**
```cpp
int miMemo(int i, int j, string& a, string& b, vector<vector<int>>& dp) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (a[i - 1] == b[j - 1]) return dp[i][j] = 1 + miMemo(i - 1, j - 1, a, b, dp);
    return dp[i][j] = max(miMemo(i - 1, j, a, b, dp), miMemo(i, j - 1, a, b, dp));
}
int minInsertionsMemo(string s) {
    string t(s.rbegin(), s.rend());
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    return n - miMemo(n, n, s, t, dp);
}
```

**Java**
```java
class Solution {
    static int miMemo(int i, int j, String a, String b, int[][] dp) {
        if (i == 0 || j == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        if (a.charAt(i - 1) == b.charAt(j - 1)) return dp[i][j] = 1 + miMemo(i - 1, j - 1, a, b, dp);
        return dp[i][j] = Math.max(miMemo(i - 1, j, a, b, dp), miMemo(i, j - 1, a, b, dp));
    }
    static int minInsertionsMemo(String s) {
        String t = new StringBuilder(s).reverse().toString();
        int n = s.length();
        int[][] dp = new int[n + 1][n + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return n - miMemo(n, n, s, t, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n²) time, O(n²) space.

**C++**
```cpp
int minInsertionsTab(string s) {
    string t(s.rbegin(), s.rend());
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (s[i - 1] == t[j - 1]) ? 1 + dp[i - 1][j - 1] : max(dp[i - 1][j], dp[i][j - 1]);
    return n - dp[n][n];
}
```

**Java**
```java
class Solution {
    static int minInsertionsTab(String s) {
        String t = new StringBuilder(s).reverse().toString();
        int n = s.length();
        int[][] dp = new int[n + 1][n + 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (s.charAt(i - 1) == t.charAt(j - 1)) ? 1 + dp[i - 1][j - 1] : Math.max(dp[i - 1][j], dp[i][j - 1]);
        return n - dp[n][n];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
int minInsertions(string s) {
    string t(s.rbegin(), s.rend());
    int n = s.size();
    vector<int> prev(n + 1, 0), cur(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cur[j] = (s[i - 1] == t[j - 1]) ? 1 + prev[j - 1] : max(prev[j], cur[j - 1]);
        prev = cur;
    }
    return n - prev[n];
}
```

**Java**
```java
class Solution {
    static int minInsertions(String s) {
        String t = new StringBuilder(s).reverse().toString();
        int n = s.length();
        int[] prev = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            int[] cur = new int[n + 1];
            for (int j = 1; j <= n; j++)
                cur[j] = (s.charAt(i - 1) == t.charAt(j - 1)) ? 1 + prev[j - 1] : Math.max(prev[j], cur[j - 1]);
            prev = cur;
        }
        return n - prev[n];
    }
}
```

#### Key Takeaways
- Minimum insertions to make a palindrome equals minimum **deletions** to make a palindrome, and both are `n − LPS`.

[↑ Contents](#contents) · [← Previous](#p422) · [Next →](#p424)

---

<a id="p424"></a>

### 40. Minimum insertions or deletions to convert string A to B

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Core | No | [LeetCode](https://leetcode.com/problems/delete-operation-for-two-strings/) | [Watch](https://youtu.be/yMnH0jrir0Q) |

#### Problem Statement
**Delete Operation for Two Strings / minimum insertions and deletions to convert A into B:** return the minimum number of single-character deletions (and insertions) needed to make the strings equal.

```text
word1 = "sea", word2 = "eat"          ->  2   (delete s, insert t)
word1 = "leetcode", word2 = "etco"    ->  4
word1 = "abcd", word2 = "anc"         ->  3   (delete b, d; insert n)
```

#### Intuition
Keep the LCS, since it doesn't need to change:
- delete the other `n − LCS` characters of A;
- insert the other `m − LCS` characters of B.

So the total is **`n + m − 2·LCS`**.

#### Approach 1: Recursion
**Complexity:** exponential time, O(n+m) stack.

**C++**
```cpp
int doRec(int i, int j, string& a, string& b) {
    if (i < 0 || j < 0) return 0;
    if (a[i] == b[j]) return 1 + doRec(i - 1, j - 1, a, b);
    return max(doRec(i - 1, j, a, b), doRec(i, j - 1, a, b));
}
int minDistanceRec(string a, string b) {
    int n = a.size(), m = b.size();
    return n + m - 2 * doRec(n - 1, m - 1, a, b);
}
```

**Java**
```java
class Solution {
    static int doRec(int i, int j, String a, String b) {
        if (i < 0 || j < 0) return 0;
        if (a.charAt(i) == b.charAt(j)) return 1 + doRec(i - 1, j - 1, a, b);
        return Math.max(doRec(i - 1, j, a, b), doRec(i, j - 1, a, b));
    }
    static int minDistanceRec(String a, String b) {
        int n = a.length(), m = b.length();
        return n + m - 2 * doRec(n - 1, m - 1, a, b);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·m) time, O(n·m) + stack.

**C++**
```cpp
int doMemo(int i, int j, string& a, string& b, vector<vector<int>>& dp) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (a[i - 1] == b[j - 1]) return dp[i][j] = 1 + doMemo(i - 1, j - 1, a, b, dp);
    return dp[i][j] = max(doMemo(i - 1, j, a, b, dp), doMemo(i, j - 1, a, b, dp));
}
int minDistanceMemo(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return n + m - 2 * doMemo(n, m, a, b, dp);
}
```

**Java**
```java
class Solution {
    static int doMemo(int i, int j, String a, String b, int[][] dp) {
        if (i == 0 || j == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        if (a.charAt(i - 1) == b.charAt(j - 1)) return dp[i][j] = 1 + doMemo(i - 1, j - 1, a, b, dp);
        return dp[i][j] = Math.max(doMemo(i - 1, j, a, b, dp), doMemo(i, j - 1, a, b, dp));
    }
    static int minDistanceMemo(String a, String b) {
        int n = a.length(), m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return n + m - 2 * doMemo(n, m, a, b, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
int minDistanceTab(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (a[i - 1] == b[j - 1]) ? 1 + dp[i - 1][j - 1] : max(dp[i - 1][j], dp[i][j - 1]);
    return n + m - 2 * dp[n][m];
}
```

**Java**
```java
class Solution {
    static int minDistanceTab(String a, String b) {
        int n = a.length(), m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                dp[i][j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? 1 + dp[i - 1][j - 1] : Math.max(dp[i - 1][j], dp[i][j - 1]);
        return n + m - 2 * dp[n][m];
    }
}
```

#### Approach 4: Space optimisation
**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
int minDistance(string a, string b) {
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cur[j] = (a[i - 1] == b[j - 1]) ? 1 + prev[j - 1] : max(prev[j], cur[j - 1]);
        prev = cur;
    }
    return n + m - 2 * prev[m];
}
```

**Java**
```java
class Solution {
    static int minDistance(String a, String b) {
        int n = a.length(), m = b.length();
        int[] prev = new int[m + 1];
        for (int i = 1; i <= n; i++) {
            int[] cur = new int[m + 1];
            for (int j = 1; j <= m; j++)
                cur[j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? 1 + prev[j - 1] : Math.max(prev[j], cur[j - 1]);
            prev = cur;
        }
        return n + m - 2 * prev[m];
    }
}
```

#### Key Takeaways
- Whatever is common (the LCS) stays; everything else is deleted from A or inserted from B.

[↑ Contents](#contents) · [← Previous](#p423) · [Next →](#p425)

---

<a id="p425"></a>

### 41. Shortest common supersequence

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Pro | No | [LeetCode](https://leetcode.com/problems/shortest-common-supersequence/) | [Watch](https://youtu.be/xElxAuBcvsU) |

#### Problem Statement
**Shortest Common Supersequence:** return the shortest string that has both `s1` and `s2` as subsequences. Any one valid answer is accepted.

```text
s1 = "abac", s2 = "cab"        ->  "cabac"   (length 5)
s1 = "brute", s2 = "groot"     ->  "bgruoote" (length 8; any valid order)
```

#### Intuition
- **Length.** The common characters (the LCS) appear once, and everything else appears once from its own string. So the length is `n + m − LCS`.
- **Building the string.** Fill the shifted LCS table, then walk back from `(n, m)`:
  - on a **match**, emit the character once and move diagonally;
  - otherwise, move towards the larger neighbour and **emit the character you're skipping**: `s1[i−1]` when moving up, `s2[j−1]` when moving left;
  - when one string runs out, emit the rest of the other;
  - finally, reverse the result.

#### Approach 1: LCS table + backtracking (as in the video)
**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
string shortestCommonSupersequence(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (a[i - 1] == b[j - 1]) ? 1 + dp[i - 1][j - 1] : max(dp[i - 1][j], dp[i][j - 1]);
    string ans;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) { ans += a[i - 1]; i--; j--; }
        else if (dp[i - 1][j] > dp[i][j - 1]) { ans += a[i - 1]; i--; }
        else { ans += b[j - 1]; j--; }
    }
    while (i > 0) ans += a[--i];
    while (j > 0) ans += b[--j];
    reverse(ans.begin(), ans.end());
    return ans;
}
```

**Java**
```java
class Solution {
    static String shortestCommonSupersequence(String a, String b) {
        int n = a.length(), m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                dp[i][j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? 1 + dp[i - 1][j - 1] : Math.max(dp[i - 1][j], dp[i][j - 1]);
        StringBuilder ans = new StringBuilder();
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (a.charAt(i - 1) == b.charAt(j - 1)) { ans.append(a.charAt(i - 1)); i--; j--; }
            else if (dp[i - 1][j] > dp[i][j - 1]) { ans.append(a.charAt(i - 1)); i--; }
            else { ans.append(b.charAt(j - 1)); j--; }
        }
        while (i > 0) ans.append(a.charAt(--i));
        while (j > 0) ans.append(b.charAt(--j));
        return ans.reverse().toString();
    }
}
```

#### Edge Cases & Pitfalls
- Don't forget the leftover characters once one string is exhausted.
- If only the **length** is needed, return `n + m − LCS` without backtracking.

#### Key Takeaways
- Backtracking an LCS table can print the LCS (keep the matches only) or the SCS (keep everything, matches once).

[↑ Contents](#contents) · [← Previous](#p424) · [Next →](#p426)

---

<a id="p426"></a>

### 42. Distinct subsequences

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Pro | No | [LeetCode](https://leetcode.com/problems/distinct-subsequences/) | [Watch](https://youtu.be/nVG7eTiD2bY) |

#### Problem Statement
**Distinct Subsequences:** count the number of distinct ways (by position) in which `t` occurs as a **subsequence** of `s`.

```text
s = "rabbbit", t = "rabbit"   ->  3
s = "babgbag", t = "bag"      ->  5
s = "brootgroot", t = "brt"   ->  3
```

#### Intuition — f(i, j) counts the ways to form t[0 … j] from s[0 … i]
- **If `s[i] == t[j]`:** either **use** this match, giving `f(i−1, j−1)`, or **skip** it and look for `t[j]` earlier, giving `f(i−1, j)`. Add the two.
- **Otherwise:** `f(i−1, j)`.
- **Base cases:**
  - `j < 0` returns 1, because all of `t` has been matched;
  - `i < 0` returns 0, because `s` has run out first.

  Check `j < 0` first.

In the shifted form, `dp[i][0] = 1` for every `i`. The video uses Code Studio's modulo 1e9+7. On LeetCode 115, intermediate values overflow 64-bit even though the answer fits in 32-bit. The video switches to `double` there. Unsigned 64-bit arithmetic, or Java `long` (which wraps), also gives the exact final answer.

#### Approach 1: Recursion
**Complexity:** exponential time, O(n+m) stack.

**C++**
```cpp
const int MOD = 1e9 + 7;
int dsRec(int i, int j, string& s, string& t) {
    if (j < 0) return 1;
    if (i < 0) return 0;
    if (s[i] == t[j]) return (dsRec(i - 1, j - 1, s, t) + dsRec(i - 1, j, s, t)) % MOD;
    return dsRec(i - 1, j, s, t);
}
int numDistinctRec(string s, string t) { return dsRec(s.size() - 1, t.size() - 1, s, t); }
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int dsRec(int i, int j, String s, String t) {
        if (j < 0) return 1;
        if (i < 0) return 0;
        if (s.charAt(i) == t.charAt(j)) return (dsRec(i - 1, j - 1, s, t) + dsRec(i - 1, j, s, t)) % MOD;
        return dsRec(i - 1, j, s, t);
    }
    static int numDistinctRec(String s, String t) { return dsRec(s.length() - 1, t.length() - 1, s, t); }
}
```

#### Approach 2: Memoization (shifted indices)
**Complexity:** O(n·m) time, O(n·m) + stack.

**C++**
```cpp
const int MOD = 1e9 + 7;
int dsMemo(int i, int j, string& s, string& t, vector<vector<int>>& dp) {
    if (j == 0) return 1;
    if (i == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (s[i - 1] == t[j - 1]) return dp[i][j] = (dsMemo(i - 1, j - 1, s, t, dp) + dsMemo(i - 1, j, s, t, dp)) % MOD;
    return dp[i][j] = dsMemo(i - 1, j, s, t, dp);
}
int numDistinctMemo(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return dsMemo(n, m, s, t, dp);
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int dsMemo(int i, int j, String s, String t, int[][] dp) {
        if (j == 0) return 1;
        if (i == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        if (s.charAt(i - 1) == t.charAt(j - 1)) return dp[i][j] = (dsMemo(i - 1, j - 1, s, t, dp) + dsMemo(i - 1, j, s, t, dp)) % MOD;
        return dp[i][j] = dsMemo(i - 1, j, s, t, dp);
    }
    static int numDistinctMemo(String s, String t) {
        int n = s.length(), m = t.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return dsMemo(n, m, s, t, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
int numDistinctTab(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = 1;            // empty t: one way
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (s[i - 1] == t[j - 1]) ? (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD : dp[i - 1][j];
    return dp[n][m];
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int numDistinctTab(String s, String t) {
        int n = s.length(), m = t.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 0; i <= n; i++) dp[i][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                dp[i][j] = (s.charAt(i - 1) == t.charAt(j - 1)) ? (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD : dp[i - 1][j];
        return dp[n][m];
    }
}
```

#### Approach 4: Space optimisation — two rows, then a single array (right to left)
`dp[i][j]` reads only the previous row, at `j` and `j−1`. So a single array updated with `j` going **from m down to 1** works, the same trick as the 0/1 knapsack. If `s[i−1] != t[j−1]` the value stays as it is, so only matches need updating.

**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
int numDistinctTwoRows(string s, string t) {
    int n = s.size(), m = t.size();
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    prev[0] = cur[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cur[j] = (s[i - 1] == t[j - 1]) ? (prev[j - 1] + prev[j]) % MOD : prev[j];
        prev = cur;
    }
    return prev[m];
}
int numDistinct(string s, string t) {
    int n = s.size(), m = t.size();
    vector<int> dp(m + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            if (s[i - 1] == t[j - 1]) dp[j] = (dp[j] + dp[j - 1]) % MOD;
    return dp[m];
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static int numDistinctTwoRows(String s, String t) {
        int n = s.length(), m = t.length();
        int[] prev = new int[m + 1];
        prev[0] = 1;
        for (int i = 1; i <= n; i++) {
            int[] cur = new int[m + 1];
            cur[0] = 1;
            for (int j = 1; j <= m; j++)
                cur[j] = (s.charAt(i - 1) == t.charAt(j - 1)) ? (prev[j - 1] + prev[j]) % MOD : prev[j];
            prev = cur;
        }
        return prev[m];
    }
    static int numDistinct(String s, String t) {
        int n = s.length(), m = t.length();
        int[] dp = new int[m + 1];
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= 1; j--)
                if (s.charAt(i - 1) == t.charAt(j - 1)) dp[j] = (dp[j] + dp[j - 1]) % MOD;
        return dp[m];
    }
}
```

#### Edge Cases & Pitfalls
- Check `j < 0` (all of `t` matched) **before** `i < 0`. An empty `t` is matched by any `s`, including an empty one.
- **LeetCode 115 (no modulo):** use `double` as the video does, `unsigned long long` in C++, or Java `long`. Wrap-around arithmetic still yields the exact final value because it fits in 32 bits.

#### Key Takeaways
- Counting matches means "use it plus skip it" on a match and "skip it" otherwise. The 1-D right-to-left trick applies whenever row `i` reads only row `i−1` at columns ≤ `j`.

[↑ Contents](#contents) · [← Previous](#p425) · [Next →](#p427)

---

<a id="p427"></a>

### 43. Edit distance

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Pro | No | [LeetCode](https://leetcode.com/problems/edit-distance/) | [Watch](https://youtu.be/fJaKO8FbDdo) |

#### Problem Statement
**Edit Distance:** the minimum number of operations (insert, delete or replace a character) to convert `word1` into `word2`.

```text
word1 = "horse", word2 = "ros"            ->  3   (horse -> rorse -> rose -> ros)
word1 = "intention", word2 = "execution"  ->  5
word1 = "", word2 = "abc"                 ->  3
```

#### Intuition
`f(i, j)` is the minimum number of operations to turn `s1[0 … i]` into `s2[0 … j]`.
- **Match:** `f(i−1, j−1)`, with no operation needed.
- **Otherwise, 1 + min of:**
  - **insert** `s2[j]` (s2 advances, s1 stays): `f(i, j−1)`;
  - **delete** `s1[i]`: `f(i−1, j)`;
  - **replace** `s1[i]` with `s2[j]`: `f(i−1, j−1)`.
- **Base cases:**
  - `i < 0` returns `j + 1`, inserting the rest of `s2`;
  - `j < 0` returns `i + 1`, deleting the rest of `s1`.
- **Shifted form:** `dp[i][0] = i` and `dp[0][j] = j`.

#### Approach 1: Recursion
**Complexity:** O(3^(n+m)) time, O(n+m) stack.

**C++**
```cpp
int edRec(int i, int j, string& a, string& b) {
    if (i < 0) return j + 1;
    if (j < 0) return i + 1;
    if (a[i] == b[j]) return edRec(i - 1, j - 1, a, b);
    return 1 + min({edRec(i, j - 1, a, b), edRec(i - 1, j, a, b), edRec(i - 1, j - 1, a, b)});
}
int editDistanceRec(string a, string b) { return edRec(a.size() - 1, b.size() - 1, a, b); }
```

**Java**
```java
class Solution {
    static int edRec(int i, int j, String a, String b) {
        if (i < 0) return j + 1;
        if (j < 0) return i + 1;
        if (a.charAt(i) == b.charAt(j)) return edRec(i - 1, j - 1, a, b);
        return 1 + Math.min(edRec(i, j - 1, a, b), Math.min(edRec(i - 1, j, a, b), edRec(i - 1, j - 1, a, b)));
    }
    static int editDistanceRec(String a, String b) { return edRec(a.length() - 1, b.length() - 1, a, b); }
}
```

#### Approach 2: Memoization (shifted indices)
**Complexity:** O(n·m) time, O(n·m) + stack.

**C++**
```cpp
int edMemo(int i, int j, string& a, string& b, vector<vector<int>>& dp) {
    if (i == 0) return j;
    if (j == 0) return i;
    if (dp[i][j] != -1) return dp[i][j];
    if (a[i - 1] == b[j - 1]) return dp[i][j] = edMemo(i - 1, j - 1, a, b, dp);
    return dp[i][j] = 1 + min({edMemo(i, j - 1, a, b, dp), edMemo(i - 1, j, a, b, dp), edMemo(i - 1, j - 1, a, b, dp)});
}
int editDistanceMemo(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return edMemo(n, m, a, b, dp);
}
```

**Java**
```java
class Solution {
    static int edMemo(int i, int j, String a, String b, int[][] dp) {
        if (i == 0) return j;
        if (j == 0) return i;
        if (dp[i][j] != -1) return dp[i][j];
        if (a.charAt(i - 1) == b.charAt(j - 1)) return dp[i][j] = edMemo(i - 1, j - 1, a, b, dp);
        return dp[i][j] = 1 + Math.min(edMemo(i, j - 1, a, b, dp), Math.min(edMemo(i - 1, j, a, b, dp), edMemo(i - 1, j - 1, a, b, dp)));
    }
    static int editDistanceMemo(String a, String b) {
        int n = a.length(), m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return edMemo(n, m, a, b, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
int editDistanceTab(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (a[i - 1] == b[j - 1]) ? dp[i - 1][j - 1]
                                              : 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
    return dp[n][m];
}
```

**Java**
```java
class Solution {
    static int editDistanceTab(String a, String b) {
        int n = a.length(), m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                dp[i][j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? dp[i - 1][j - 1]
                        : 1 + Math.min(dp[i][j - 1], Math.min(dp[i - 1][j], dp[i - 1][j - 1]));
        return dp[n][m];
    }
}
```

#### Approach 4: Space optimisation — `prev` and `cur`, with `cur[0] = i` on every row
**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
int editDistance(string a, string b) {
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1), cur(m + 1);
    for (int j = 0; j <= m; j++) prev[j] = j;
    for (int i = 1; i <= n; i++) {
        cur[0] = i;                                         // the column-0 base case for this row
        for (int j = 1; j <= m; j++)
            cur[j] = (a[i - 1] == b[j - 1]) ? prev[j - 1] : 1 + min({cur[j - 1], prev[j], prev[j - 1]});
        prev = cur;
    }
    return prev[m];
}
```

**Java**
```java
class Solution {
    static int editDistance(String a, String b) {
        int n = a.length(), m = b.length();
        int[] prev = new int[m + 1];
        for (int j = 0; j <= m; j++) prev[j] = j;
        for (int i = 1; i <= n; i++) {
            int[] cur = new int[m + 1];
            cur[0] = i;
            for (int j = 1; j <= m; j++)
                cur[j] = (a.charAt(i - 1) == b.charAt(j - 1)) ? prev[j - 1] : 1 + Math.min(cur[j - 1], Math.min(prev[j], prev[j - 1]));
            prev = cur;
        }
        return prev[m];
    }
}
```

#### Edge Cases & Pitfalls
- Forgetting `cur[0] = i` in the 1-D version is a classic bug: the base column changes with every row.
- On a match, take `f(i−1, j−1)` **without adding 1**. Taking the minimum with the other options is unnecessary, because matching is never worse.

#### Key Takeaways
- Each operation corresponds to one move in the grid: insert is left, delete is up, replace is diagonal plus one, and a match is a free diagonal step.

[↑ Contents](#contents) · [← Previous](#p426) · [Next →](#p428)

---

<a id="p428"></a>

### 44. Wildcard matching

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Pro | No | [LeetCode](https://leetcode.com/problems/wildcard-matching/) | [Watch](https://youtu.be/ZmlQ3vgAOMo) |

#### Problem Statement
**Wildcard Matching:** pattern `p` contains `?` (matches any single character) and `*` (matches any sequence, including an empty one). Does `p` match **all** of `s`?

```text
s = "aa",    p = "a"      ->  false
s = "aa",    p = "*"      ->  true
s = "cb",    p = "?a"     ->  false
s = "adceb", p = "*a*b"   ->  true
```

#### Intuition
`f(i, j)` says whether `p[0 … i]` matches `s[0 … j]`.
- **Exact match or `?`:** `f(i−1, j−1)`.
- **`*`:** either it matches **nothing**, so drop the star: `f(i−1, j)`; or it matches **one more character** of `s` and stays available: `f(i, j−1)`. OR the two.
- **Different characters:** false.
- **Base cases:**
  - both exhausted: true;
  - pattern exhausted but `s` isn't: false;
  - `s` exhausted but pattern isn't: true **only if the remaining pattern is all `*`**.

#### Approach 1: Recursion
**Complexity:** exponential time, O(n+m) stack.

**C++**
```cpp
bool allStars(string& p, int i) {                 // p[0..i] are all '*'
    for (int k = 0; k <= i; k++) if (p[k] != '*') return false;
    return true;
}
bool wmRec(int i, int j, string& p, string& s) {
    if (i < 0 && j < 0) return true;
    if (i < 0) return false;
    if (j < 0) return allStars(p, i);
    if (p[i] == s[j] || p[i] == '?') return wmRec(i - 1, j - 1, p, s);
    if (p[i] == '*') return wmRec(i - 1, j, p, s) || wmRec(i, j - 1, p, s);
    return false;
}
bool isMatchRec(string s, string p) { return wmRec(p.size() - 1, s.size() - 1, p, s); }
```

**Java**
```java
class Solution {
    static boolean allStars(String p, int i) {
        for (int k = 0; k <= i; k++) if (p.charAt(k) != '*') return false;
        return true;
    }
    static boolean wmRec(int i, int j, String p, String s) {
        if (i < 0 && j < 0) return true;
        if (i < 0) return false;
        if (j < 0) return allStars(p, i);
        if (p.charAt(i) == s.charAt(j) || p.charAt(i) == '?') return wmRec(i - 1, j - 1, p, s);
        if (p.charAt(i) == '*') return wmRec(i - 1, j, p, s) || wmRec(i, j - 1, p, s);
        return false;
    }
    static boolean isMatchRec(String s, String p) { return wmRec(p.length() - 1, s.length() - 1, p, s); }
}
```

#### Approach 2: Memoization (shifted indices)
**Complexity:** O(n·m) time, O(n·m) + stack.

**C++**
```cpp
bool wmMemo(int i, int j, string& p, string& s, vector<vector<int>>& dp) {
    if (i == 0 && j == 0) return true;
    if (i == 0) return false;
    if (j == 0) {
        for (int k = 0; k < i; k++) if (p[k] != '*') return false;
        return true;
    }
    if (dp[i][j] != -1) return dp[i][j];
    bool res;
    if (p[i - 1] == s[j - 1] || p[i - 1] == '?') res = wmMemo(i - 1, j - 1, p, s, dp);
    else if (p[i - 1] == '*') res = wmMemo(i - 1, j, p, s, dp) || wmMemo(i, j - 1, p, s, dp);
    else res = false;
    return dp[i][j] = res;
}
bool isMatchMemo(string s, string p) {
    int n = p.size(), m = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return wmMemo(n, m, p, s, dp);
}
```

**Java**
```java
class Solution {
    static boolean wmMemo(int i, int j, String p, String s, int[][] dp) {
        if (i == 0 && j == 0) return true;
        if (i == 0) return false;
        if (j == 0) {
            for (int k = 0; k < i; k++) if (p.charAt(k) != '*') return false;
            return true;
        }
        if (dp[i][j] != -1) return dp[i][j] == 1;
        boolean res;
        if (p.charAt(i - 1) == s.charAt(j - 1) || p.charAt(i - 1) == '?') res = wmMemo(i - 1, j - 1, p, s, dp);
        else if (p.charAt(i - 1) == '*') res = wmMemo(i - 1, j, p, s, dp) || wmMemo(i, j - 1, p, s, dp);
        else res = false;
        dp[i][j] = res ? 1 : 0;
        return res;
    }
    static boolean isMatchMemo(String s, String p) {
        int n = p.length(), m = s.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int[] r : dp) Arrays.fill(r, -1);
        return wmMemo(n, m, p, s, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·m) time, O(n·m) space.

**C++**
```cpp
bool isMatchTab(string s, string p) {
    int n = p.size(), m = s.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;                                         // dp[0][j > 0] = false
    for (int i = 1; i <= n; i++) dp[i][0] = dp[i - 1][0] && p[i - 1] == '*';
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (p[i - 1] == s[j - 1] || p[i - 1] == '?') dp[i][j] = dp[i - 1][j - 1];
            else if (p[i - 1] == '*') dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            else dp[i][j] = false;
        }
    return dp[n][m];
}
```

**Java**
```java
class Solution {
    static boolean isMatchTab(String s, String p) {
        int n = p.length(), m = s.length();
        boolean[][] dp = new boolean[n + 1][m + 1];
        dp[0][0] = true;
        for (int i = 1; i <= n; i++) dp[i][0] = dp[i - 1][0] && p.charAt(i - 1) == '*';
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                char c = p.charAt(i - 1);
                if (c == s.charAt(j - 1) || c == '?') dp[i][j] = dp[i - 1][j - 1];
                else if (c == '*') dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else dp[i][j] = false;
            }
        return dp[n][m];
    }
}
```

#### Approach 4: Space optimisation — `prev` and `cur`, with `cur[0]` meaning "the pattern so far is all stars"
**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
bool isMatch(string s, string p) {
    int n = p.size(), m = s.size();
    vector<bool> prev(m + 1, false), cur(m + 1, false);
    prev[0] = true;
    bool stars = true;
    for (int i = 1; i <= n; i++) {
        stars = stars && p[i - 1] == '*';
        cur[0] = stars;
        for (int j = 1; j <= m; j++) {
            if (p[i - 1] == s[j - 1] || p[i - 1] == '?') cur[j] = prev[j - 1];
            else if (p[i - 1] == '*') cur[j] = prev[j] || cur[j - 1];
            else cur[j] = false;
        }
        prev = cur;
    }
    return prev[m];
}
```

**Java**
```java
class Solution {
    static boolean isMatch(String s, String p) {
        int n = p.length(), m = s.length();
        boolean[] prev = new boolean[m + 1];
        prev[0] = true;
        boolean stars = true;
        for (int i = 1; i <= n; i++) {
            boolean[] cur = new boolean[m + 1];
            char c = p.charAt(i - 1);
            stars = stars && c == '*';
            cur[0] = stars;
            for (int j = 1; j <= m; j++) {
                if (c == s.charAt(j - 1) || c == '?') cur[j] = prev[j - 1];
                else if (c == '*') cur[j] = prev[j] || cur[j - 1];
                else cur[j] = false;
            }
            prev = cur;
        }
        return prev[m];
    }
}
```

#### Edge Cases & Pitfalls
- Each row's `j = 0` base case depends on `i`, as in Edit Distance, so set `cur[0]` on every row.
- `s` exhausted with pattern `"**a"` remaining is **false**, because a letter is left over.

#### Key Takeaways
- A `*` either drops out (`i−1`) or absorbs one more character (`j−1`). This "stay or move on" choice also appears in unbounded knapsack.

[↑ Contents](#contents) · [← Previous](#p427) · [Next →](#p429)

---

<a id="p429"></a>

### 45. Word Break

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Core | No | [LeetCode](https://leetcode.com/problems/word-break/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
**Word Break:** given a string `s` and a dictionary `wordDict`, can `s` be segmented into a sequence of one or more dictionary words? Words may be reused.

```text
s = "leetcode", wordDict = ["leet","code"]              ->  true
s = "applepenapple", wordDict = ["apple","pen"]         ->  true
s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]  ->  false
```

#### Intuition
`f(i)` says whether the suffix `s[i … n−1]` can be segmented.
- **Recurrence:** try every dictionary word `w` that matches `s` starting at `i`. If `f(i + |w|)` is true, so is `f(i)`.
- **Base case:** `f(n) = true`, since an empty suffix is segmented.

There are only `n + 1` states, so memoizing turns the exponential recursion polynomial. The same problem can be posed as "can the prefix end at `i`", scanning cut positions `j < i` with a hash set.

#### Approach 1: Recursion
**Complexity:** O(2ⁿ) worst-case time, O(n) stack.

**C++**
```cpp
bool wbRec(int i, string& s, vector<string>& dict) {
    if (i == (int)s.size()) return true;
    for (const string& w : dict)
        if (s.compare(i, w.size(), w) == 0 && wbRec(i + w.size(), s, dict)) return true;
    return false;
}
bool wordBreakRec(string s, vector<string>& dict) { return wbRec(0, s, dict); }
```

**Java**
```java
class Solution {
    static boolean wbRec(int i, String s, List<String> dict) {
        if (i == s.length()) return true;
        for (String w : dict)
            if (s.startsWith(w, i) && wbRec(i + w.length(), s, dict)) return true;
        return false;
    }
    static boolean wordBreakRec(String s, List<String> dict) { return wbRec(0, s, dict); }
}
```

#### Approach 2: Memoization
**Complexity:** O(n · W · L) time, where W is the number of words and L the word length; O(n) space.

**C++**
```cpp
bool wbMemo(int i, string& s, vector<string>& dict, vector<int>& dp) {
    if (i == (int)s.size()) return true;
    if (dp[i] != -1) return dp[i];
    for (const string& w : dict)
        if (s.compare(i, w.size(), w) == 0 && wbMemo(i + w.size(), s, dict, dp)) return dp[i] = 1;
    return dp[i] = 0;
}
bool wordBreakMemo(string s, vector<string>& dict) {
    vector<int> dp(s.size(), -1);
    return wbMemo(0, s, dict, dp);
}
```

**Java**
```java
class Solution {
    static boolean wbMemo(int i, String s, List<String> dict, int[] dp) {
        if (i == s.length()) return true;
        if (dp[i] != -1) return dp[i] == 1;
        for (String w : dict)
            if (s.startsWith(w, i) && wbMemo(i + w.length(), s, dict, dp)) { dp[i] = 1; return true; }
        dp[i] = 0;
        return false;
    }
    static boolean wordBreakMemo(String s, List<String> dict) {
        int[] dp = new int[s.length()];
        Arrays.fill(dp, -1);
        return wbMemo(0, s, dict, dp);
    }
}
```

#### Approach 3: Tabulation — from the back
**Complexity:** O(n · W · L) time, O(n) space.

**C++**
```cpp
bool wordBreakTab(string s, vector<string>& dict) {
    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[n] = true;
    for (int i = n - 1; i >= 0; i--)
        for (const string& w : dict)
            if (i + w.size() <= (size_t)n && dp[i + w.size()] && s.compare(i, w.size(), w) == 0) { dp[i] = true; break; }
    return dp[0];
}
```

**Java**
```java
class Solution {
    static boolean wordBreakTab(String s, List<String> dict) {
        int n = s.length();
        boolean[] dp = new boolean[n + 1];
        dp[n] = true;
        for (int i = n - 1; i >= 0; i--)
            for (String w : dict)
                if (i + w.length() <= n && dp[i + w.length()] && s.startsWith(w, i)) { dp[i] = true; break; }
        return dp[0];
    }
}
```

#### Approach 4: Prefix DP with a hash set
`dp[i]` means the prefix `s[0 … i−1]` can be segmented. Try every last cut `j`, checking substring lengths only up to the longest word.

**Complexity:** O(n · maxLen²) time (the hash of each substring costs O(len)), O(n + dictionary) space.

**C++**
```cpp
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    size_t maxLen = 0;
    for (const string& w : wordDict) maxLen = max(maxLen, w.size());
    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = i - 1; j >= 0 && (size_t)(i - j) <= maxLen; j--)
            if (dp[j] && dict.count(s.substr(j, i - j))) { dp[i] = true; break; }
    return dp[n];
}
```

**Java**
```java
class Solution {
    static boolean wordBreak(String s, List<String> wordDict) {
        Set<String> dict = new HashSet<>(wordDict);
        int maxLen = 0;
        for (String w : wordDict) maxLen = Math.max(maxLen, w.length());
        int n = s.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;
        for (int i = 1; i <= n; i++)
            for (int j = i - 1; j >= 0 && i - j <= maxLen; j--)
                if (dp[j] && dict.contains(s.substring(j, i))) { dp[i] = true; break; }
        return dp[n];
    }
}
```

#### Edge Cases & Pitfalls
- A 1-D DP over positions has no "previous row" to drop, so there is no further space optimisation.
- Strings like `"aaaa…ab"` with dictionary `["a", "aa", "aaa"]` make the plain recursion exponential. Memoize.

#### Key Takeaways
- "Can the string be split into valid pieces?" is a DP over cut positions. Word Break II (listing all splits) is backtracking on top of this DP.

[↑ Contents](#contents) · [← Previous](#p428) · [Next →](#p430)

---

<a id="p430"></a>

### 46. Count Palindromic Subsequences

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › DP on strings | Pro | No | [LeetCode](https://leetcode.com/problems/count-palindromic-subsequences/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

> **Problem choice:** the sheet's title matches GfG's *Count Palindromic Subsequences*: all palindromic subsequences counted by position, modulo 1e9+7. That is covered first. Its LeetCode link (LC 2484) asks only for palindromes of **length 5**; that version is covered under "Related problem" at the end.

#### Problem Statement
Count all **palindromic subsequences** of `s`, counting subsequences at different positions as distinct, modulo 1e9+7.

```text
s = "abcd"  ->  4      ("a","b","c","d")
s = "aab"   ->  4      ("a","a","b","aa")
s = "aaaa"  ->  15     (every non-empty subsequence)
```

#### Intuition — interval DP with inclusion–exclusion
`f(i, j)` is the count of palindromic subsequences inside `s[i … j]`.
- **Combine the two sides.** Palindromes in `[i+1, j]` and in `[i, j−1]` together cover everything, but those inside `[i+1, j−1]` are counted twice. So start from `f(i+1, j) + f(i, j−1) − f(i+1, j−1)`.
- **If `s[i] == s[j]`:** every palindrome inside `[i+1, j−1]` can be wrapped with `s[i] … s[j]`, plus the pair `s[i]s[j]` itself. That adds `f(i+1, j−1) + 1`, so the total simplifies to **`f(i+1, j) + f(i, j−1) + 1`**.
- **Base cases:** `f(i, i) = 1`, and `f(i, j) = 0` when `i > j`.

#### Approach 1: Recursion
**Complexity:** exponential time, O(n) stack.

**C++**
```cpp
const int MOD = 1e9 + 7;
long long cpsRec(int i, int j, string& s) {
    if (i > j) return 0;
    if (i == j) return 1;
    if (s[i] == s[j]) return (cpsRec(i + 1, j, s) + cpsRec(i, j - 1, s) + 1) % MOD;
    return ((cpsRec(i + 1, j, s) + cpsRec(i, j - 1, s) - cpsRec(i + 1, j - 1, s)) % MOD + MOD) % MOD;
}
long long countPSRec(string s) { return cpsRec(0, s.size() - 1, s); }
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static long cpsRec(int i, int j, String s) {
        if (i > j) return 0;
        if (i == j) return 1;
        if (s.charAt(i) == s.charAt(j)) return (cpsRec(i + 1, j, s) + cpsRec(i, j - 1, s) + 1) % MOD;
        return ((cpsRec(i + 1, j, s) + cpsRec(i, j - 1, s) - cpsRec(i + 1, j - 1, s)) % MOD + MOD) % MOD;
    }
    static long countPSRec(String s) { return cpsRec(0, s.length() - 1, s); }
}
```

#### Approach 2: Memoization
**Complexity:** O(n²) time, O(n²) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
long long cpsMemo(int i, int j, string& s, vector<vector<long long>>& dp) {
    if (i > j) return 0;
    if (i == j) return 1;
    if (dp[i][j] != -1) return dp[i][j];
    long long r;
    if (s[i] == s[j]) r = (cpsMemo(i + 1, j, s, dp) + cpsMemo(i, j - 1, s, dp) + 1) % MOD;
    else r = ((cpsMemo(i + 1, j, s, dp) + cpsMemo(i, j - 1, s, dp) - cpsMemo(i + 1, j - 1, s, dp)) % MOD + MOD) % MOD;
    return dp[i][j] = r;
}
long long countPSMemo(string s) {
    int n = s.size();
    vector<vector<long long>> dp(n, vector<long long>(n, -1));
    return cpsMemo(0, n - 1, s, dp);
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static long cpsMemo(int i, int j, String s, long[][] dp) {
        if (i > j) return 0;
        if (i == j) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        long r;
        if (s.charAt(i) == s.charAt(j)) r = (cpsMemo(i + 1, j, s, dp) + cpsMemo(i, j - 1, s, dp) + 1) % MOD;
        else r = ((cpsMemo(i + 1, j, s, dp) + cpsMemo(i, j - 1, s, dp) - cpsMemo(i + 1, j - 1, s, dp)) % MOD + MOD) % MOD;
        return dp[i][j] = r;
    }
    static long countPSMemo(String s) {
        int n = s.length();
        long[][] dp = new long[n][n];
        for (long[] r : dp) Arrays.fill(r, -1);
        return cpsMemo(0, n - 1, s, dp);
    }
}
```

#### Approach 3: Tabulation — i from n−1 down, j from i up
**Complexity:** O(n²) time, O(n²) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
long long countPSTab(string s) {
    int n = s.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            long long inner = (i + 1 <= j - 1) ? dp[i + 1][j - 1] : 0;
            if (s[i] == s[j]) dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % MOD;
            else dp[i][j] = ((dp[i + 1][j] + dp[i][j - 1] - inner) % MOD + MOD) % MOD;
        }
    }
    return dp[0][n - 1];
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static long countPSTab(String s) {
        int n = s.length();
        long[][] dp = new long[n + 1][n + 1];
        for (int i = n - 1; i >= 0; i--) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; j++) {
                long inner = (i + 1 <= j - 1) ? dp[i + 1][j - 1] : 0;
                if (s.charAt(i) == s.charAt(j)) dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % MOD;
                else dp[i][j] = ((dp[i + 1][j] + dp[i][j - 1] - inner) % MOD + MOD) % MOD;
            }
        }
        return dp[0][n - 1];
    }
}
```

#### Approach 4: Space optimisation — rows i+1 (`next`) and i (`cur`)
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
const int MOD = 1e9 + 7;
long long countPS(string s) {
    int n = s.size();
    vector<long long> next(n, 0), cur(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        fill(cur.begin(), cur.end(), 0);
        cur[i] = 1;
        for (int j = i + 1; j < n; j++) {
            long long inner = (i + 1 <= j - 1) ? next[j - 1] : 0;
            if (s[i] == s[j]) cur[j] = (next[j] + cur[j - 1] + 1) % MOD;
            else cur[j] = ((next[j] + cur[j - 1] - inner) % MOD + MOD) % MOD;
        }
        swap(next, cur);
    }
    return n ? next[n - 1] : 0;
}
```

**Java**
```java
class Solution {
    static final int MOD = 1_000_000_007;
    static long countPS(String s) {
        int n = s.length();
        long[] next = new long[n];
        for (int i = n - 1; i >= 0; i--) {
            long[] cur = new long[n];
            cur[i] = 1;
            for (int j = i + 1; j < n; j++) {
                long inner = (i + 1 <= j - 1) ? next[j - 1] : 0;
                if (s.charAt(i) == s.charAt(j)) cur[j] = (next[j] + cur[j - 1] + 1) % MOD;
                else cur[j] = ((next[j] + cur[j - 1] - inner) % MOD + MOD) % MOD;
            }
            next = cur;
        }
        return n > 0 ? next[n - 1] : 0;
    }
}
```

#### Related problem: LC 2484 — palindromic subsequences of length 5
For a digit string, count the palindromes of length 5 (pattern `a b x b a`), modulo 1e9+7.
- **For each middle index `k`:**
  - multiply the number of `(a, b)` digit pairs strictly to the **left** of `k`, in that order,
  - by the number of `(b, a)` pairs strictly to the **right**.
- **Pair counts.** These are maintained incrementally with per-digit counters.

**Complexity:** O(n·100) time, O(n·100) space (the right-side counts per position).

**C++**
```cpp
int countPalindromes(string s) {
    const long long MOD = 1e9 + 7;
    int n = s.size();
    vector<array<long long, 100>> rightPairs(n + 1);         // rightPairs[k][b*10+a]: pairs (b, a) within s[k..]
    array<long long, 10> cnt{};
    rightPairs[n].fill(0);
    for (int k = n - 1; k >= 0; k--) {
        rightPairs[k] = rightPairs[k + 1];
        int d = s[k] - '0';
        for (int a = 0; a < 10; a++) rightPairs[k][d * 10 + a] += cnt[a];
        cnt[d]++;
    }
    array<long long, 100> leftPairs{};
    cnt.fill(0);
    long long ans = 0;
    for (int k = 0; k < n; k++) {
        for (int a = 0; a < 10; a++)
            for (int b = 0; b < 10; b++)
                ans = (ans + leftPairs[a * 10 + b] % MOD * (rightPairs[k + 1][b * 10 + a] % MOD)) % MOD;
        int d = s[k] - '0';
        for (int a = 0; a < 10; a++) leftPairs[a * 10 + d] += cnt[a];
        cnt[d]++;
    }
    return (int)ans;
}
```

**Java**
```java
class Solution {
    static int countPalindromes(String s) {
        final long MOD = 1_000_000_007L;
        int n = s.length();
        long[][] rightPairs = new long[n + 1][100];
        long[] cnt = new long[10];
        for (int k = n - 1; k >= 0; k--) {
            rightPairs[k] = rightPairs[k + 1].clone();
            int d = s.charAt(k) - '0';
            for (int a = 0; a < 10; a++) rightPairs[k][d * 10 + a] += cnt[a];
            cnt[d]++;
        }
        long[] leftPairs = new long[100];
        cnt = new long[10];
        long ans = 0;
        for (int k = 0; k < n; k++) {
            for (int a = 0; a < 10; a++)
                for (int b = 0; b < 10; b++)
                    ans = (ans + leftPairs[a * 10 + b] % MOD * (rightPairs[k + 1][b * 10 + a] % MOD)) % MOD;
            int d = s.charAt(k) - '0';
            for (int a = 0; a < 10; a++) leftPairs[a * 10 + d] += cnt[a];
            cnt[d]++;
        }
        return (int) ans;
    }
}
```

#### Edge Cases & Pitfalls
- With modulo arithmetic, the subtraction can go negative, so add `MOD` before taking `%` again.
- This counts by **position**: `"aa"` gives 3 (`a`, `a`, `aa`). Counting **distinct** palindromic strings is a different, harder problem (LC 730).

#### Key Takeaways
- Interval DP over `[i, j]` plus inclusion–exclusion is the standard way to count substructures inside a range. MCM (next) is also interval DP.

[↑ Contents](#contents) · [← Previous](#p429) · [Next →](#p431)

---

## MCM DP

<a id="p431"></a>

### 47. Matrix chain multiplication

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › MCM DP | Pro | No | — | [Watch](https://youtu.be/vRVfmbCFW7Y) |

#### Problem Statement
**Matrix Chain Multiplication:** `arr` of size `N` describes `N−1` matrices, where matrix `i` has dimensions `arr[i−1] × arr[i]`. Find the minimum number of scalar multiplications needed to multiply the whole chain, by choosing where the brackets go.

```text
arr = [10, 20, 30, 40, 50]  ->  38000   (((A1 A2) A3) A4)
arr = [10, 15, 20, 25]      ->  8000
arr = [4, 5, 3, 2]          ->  70      (A1 (A2 A3))
```

#### Intuition — partition DP
The video gives these rules for partition DP:
1. Start with the entire block or array, `f(i, j)`.
2. Try every partition point `k` inside it.
3. Return the best of all the partitions.

- **The state.** `f(i, j)` is the minimum cost to multiply matrices `i … j`, which form an `arr[i−1] × arr[j]` result.
- **The split.** Splitting at `k` (`i ≤ k < j`) costs `f(i, k) + f(k+1, j) + arr[i−1]·arr[k]·arr[j]`, the last term being the final product of the two halves.
- **Base case and answer.** `i == j` costs 0, since it's a single matrix. The answer is `f(1, N−1)`.
- **Tabulation (DP 49).** `f(i, j)` needs **shorter** intervals, so fill `i` from `N−1` down to 1 and `j` from `i+1` up to `N−1`.

#### Approach 1: Recursion
**Complexity:** exponential time, O(N) stack.

**C++**
```cpp
int mcmRec(int i, int j, vector<int>& arr) {
    if (i == j) return 0;
    int best = INT_MAX;
    for (int k = i; k < j; k++)
        best = min(best, arr[i - 1] * arr[k] * arr[j] + mcmRec(i, k, arr) + mcmRec(k + 1, j, arr));
    return best;
}
int matrixMultiplicationRec(vector<int>& arr) { return mcmRec(1, arr.size() - 1, arr); }
```

**Java**
```java
class Solution {
    static int mcmRec(int i, int j, int[] arr) {
        if (i == j) return 0;
        int best = Integer.MAX_VALUE;
        for (int k = i; k < j; k++)
            best = Math.min(best, arr[i - 1] * arr[k] * arr[j] + mcmRec(i, k, arr) + mcmRec(k + 1, j, arr));
        return best;
    }
    static int matrixMultiplicationRec(int[] arr) { return mcmRec(1, arr.length - 1, arr); }
}
```

#### Approach 2: Memoization — dp[N][N]
**Complexity:** O(N³) time, O(N²) + O(N) stack.

**C++**
```cpp
int mcmMemo(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
    if (i == j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int best = INT_MAX;
    for (int k = i; k < j; k++)
        best = min(best, arr[i - 1] * arr[k] * arr[j] + mcmMemo(i, k, arr, dp) + mcmMemo(k + 1, j, arr, dp));
    return dp[i][j] = best;
}
int matrixMultiplicationMemo(vector<int>& arr) {
    int N = arr.size();
    vector<vector<int>> dp(N, vector<int>(N, -1));
    return mcmMemo(1, N - 1, arr, dp);
}
```

**Java**
```java
class Solution {
    static int mcmMemo(int i, int j, int[] arr, int[][] dp) {
        if (i == j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        int best = Integer.MAX_VALUE;
        for (int k = i; k < j; k++)
            best = Math.min(best, arr[i - 1] * arr[k] * arr[j] + mcmMemo(i, k, arr, dp) + mcmMemo(k + 1, j, arr, dp));
        return dp[i][j] = best;
    }
    static int matrixMultiplicationMemo(int[] arr) {
        int N = arr.length;
        int[][] dp = new int[N][N];
        for (int[] r : dp) Arrays.fill(r, -1);
        return mcmMemo(1, N - 1, arr, dp);
    }
}
```

#### Approach 3: Tabulation (DP 49)
**Complexity:** O(N³) time, O(N²) space.

**C++**
```cpp
int matrixMultiplication(vector<int>& arr) {
    int N = arr.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));             // dp[i][i] = 0
    for (int i = N - 1; i >= 1; i--)
        for (int j = i + 1; j < N; j++) {
            int best = INT_MAX;
            for (int k = i; k < j; k++)
                best = min(best, arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j]);
            dp[i][j] = best;
        }
    return dp[1][N - 1];
}
```

**Java**
```java
class Solution {
    static int matrixMultiplication(int[] arr) {
        int N = arr.length;
        int[][] dp = new int[N][N];
        for (int i = N - 1; i >= 1; i--)
            for (int j = i + 1; j < N; j++) {
                int best = Integer.MAX_VALUE;
                for (int k = i; k < j; k++)
                    best = Math.min(best, arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j]);
                dp[i][j] = best;
            }
        return dp[1][N - 1];
    }
}
```

#### Edge Cases & Pitfalls
- `arr` of size 2 is a single matrix and costs 0.
- Interval DP has no simple row-by-row space optimisation, because `dp[i][j]` reads both `dp[i][k]` and `dp[k+1][j]`.
- Use `long long` if the products can exceed 2³¹.

#### Key Takeaways
- Partition DP template: `f(i, j)` = best over `k` of `cost(i, k, j) + f(i, k) + f(k+1, j)`. Tabulate by **increasing interval length**, or equivalently `i` descending and `j` ascending.

[↑ Contents](#contents) · [← Previous](#p430) · [Next →](#p432)

---

<a id="p432"></a>

### 48. Burst balloons

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › MCM DP | Pro | No | [LeetCode](https://leetcode.com/problems/burst-balloons/) | [Watch](https://youtu.be/Yz4LlDSlkns) |

#### Problem Statement
**Burst Balloons:** bursting balloon `i` earns `nums[left] · nums[i] · nums[right]`, where `left` and `right` are its **current** neighbours, and out-of-range neighbours count as 1. Maximise the total coins.

```text
nums = [3, 1, 5, 8]  ->  167   (3·1·5 + 3·5·8 + 1·3·8 + 1·8·1)
nums = [1, 5]        ->  10
```

#### Intuition — choose the balloon burst **last**
- **Why bursting first doesn't work.** If you pick which balloon to burst **first**, the two halves become dependent, because the neighbours change.
- **Bottom-up thinking.** Pick the balloon `ind` that is burst **last** in the range `[i, j]`. When it bursts, everything else in `[i, j]` is already gone, so its neighbours are fixed at `nums[i−1]` and `nums[j+1]`. Its left part `[i, ind−1]` and right part `[ind+1, j]` are then independent.
- **Padding.** Put a 1 at each end of the array.
- **Recurrence.** **f(i, j) = max over ind ∈ [i, j] of nums[i−1]·nums[ind]·nums[j+1] + f(i, ind−1) + f(ind+1, j)**, with f = 0 when `i > j`.

#### Approach 1: Recursion
**Complexity:** exponential time, O(n) stack.

**C++**
```cpp
int bbRec(int i, int j, vector<int>& a) {
    if (i > j) return 0;
    int best = INT_MIN;
    for (int ind = i; ind <= j; ind++)
        best = max(best, a[i - 1] * a[ind] * a[j + 1] + bbRec(i, ind - 1, a) + bbRec(ind + 1, j, a));
    return best;
}
int maxCoinsRec(vector<int> nums) {
    int n = nums.size();
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    return bbRec(1, n, nums);
}
```

**Java**
```java
class Solution {
    static int bbRec(int i, int j, int[] a) {
        if (i > j) return 0;
        int best = Integer.MIN_VALUE;
        for (int ind = i; ind <= j; ind++)
            best = Math.max(best, a[i - 1] * a[ind] * a[j + 1] + bbRec(i, ind - 1, a) + bbRec(ind + 1, j, a));
        return best;
    }
    static int maxCoinsRec(int[] nums) {
        int n = nums.length;
        int[] a = new int[n + 2];
        a[0] = a[n + 1] = 1;
        for (int i = 0; i < n; i++) a[i + 1] = nums[i];
        return bbRec(1, n, a);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(n³) time, O(n²) + O(n) stack.

**C++**
```cpp
int bbMemo(int i, int j, vector<int>& a, vector<vector<int>>& dp) {
    if (i > j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int best = INT_MIN;
    for (int ind = i; ind <= j; ind++)
        best = max(best, a[i - 1] * a[ind] * a[j + 1] + bbMemo(i, ind - 1, a, dp) + bbMemo(ind + 1, j, a, dp));
    return dp[i][j] = best;
}
int maxCoinsMemo(vector<int> nums) {
    int n = nums.size();
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
    return bbMemo(1, n, nums, dp);
}
```

**Java**
```java
class Solution {
    static int bbMemo(int i, int j, int[] a, int[][] dp) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        int best = Integer.MIN_VALUE;
        for (int ind = i; ind <= j; ind++)
            best = Math.max(best, a[i - 1] * a[ind] * a[j + 1] + bbMemo(i, ind - 1, a, dp) + bbMemo(ind + 1, j, a, dp));
        return dp[i][j] = best;
    }
    static int maxCoinsMemo(int[] nums) {
        int n = nums.length;
        int[] a = new int[n + 2];
        a[0] = a[n + 1] = 1;
        for (int i = 0; i < n; i++) a[i + 1] = nums[i];
        int[][] dp = new int[n + 2][n + 2];
        for (int[] r : dp) Arrays.fill(r, -1);
        return bbMemo(1, n, a, dp);
    }
}
```

#### Approach 3: Tabulation — i from n down to 1, j from i up to n
**Complexity:** O(n³) time, O(n²) space.

**C++**
```cpp
int maxCoins(vector<int> nums) {
    int n = nums.size();
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for (int i = n; i >= 1; i--)
        for (int j = i; j <= n; j++) {
            int best = INT_MIN;
            for (int ind = i; ind <= j; ind++)
                best = max(best, nums[i - 1] * nums[ind] * nums[j + 1] + dp[i][ind - 1] + dp[ind + 1][j]);
            dp[i][j] = best;
        }
    return dp[1][n];
}
```

**Java**
```java
class Solution {
    static int maxCoins(int[] nums) {
        int n = nums.length;
        int[] a = new int[n + 2];
        a[0] = a[n + 1] = 1;
        for (int i = 0; i < n; i++) a[i + 1] = nums[i];
        int[][] dp = new int[n + 2][n + 2];
        for (int i = n; i >= 1; i--)
            for (int j = i; j <= n; j++) {
                int best = Integer.MIN_VALUE;
                for (int ind = i; ind <= j; ind++)
                    best = Math.max(best, a[i - 1] * a[ind] * a[j + 1] + dp[i][ind - 1] + dp[ind + 1][j]);
                dp[i][j] = best;
            }
        return dp[1][n];
    }
}
```

#### Edge Cases & Pitfalls
- `dp[i][ind−1]` with `ind = i` reads `dp[i][i−1]`, which is the 0 base case, so the table must be `(n+2) × (n+2)`.
- Thinking "first balloon to burst" gives dependent subproblems. "Last balloon" is the key insight.

#### Key Takeaways
- When a choice changes its neighbours' context, reverse time: fix the **last** event so the subproblems become independent.

[↑ Contents](#contents) · [← Previous](#p431) · [Next →](#p433)

---

<a id="p433"></a>

### 49. Palindrome partitioning II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › MCM DP | Pro | No | [LeetCode](https://leetcode.com/problems/palindrome-partitioning-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/palindrome-partitioning-ii-minimum-cuts) | [Watch](https://youtu.be/_H8V5hJUGd0) |

#### Problem Statement
**Palindrome Partitioning II:** return the minimum number of cuts needed to partition `s` so that every piece is a palindrome.

```text
s = "aab"                ->  1   ("aa" | "b")
s = "a"                  ->  0
s = "bababcbadcede"      ->  4   ("bab | abcba | d | c | ede")
```

#### Intuition — front partition
The video calls this the **front-partition** pattern, which differs from MCM:
- **The state.** `f(i)` is the minimum number of **pieces** for the suffix `s[i … n−1]`.
- **The choice.** Try every end `j ≥ i` such that `s[i … j]` is a palindrome, cut there, and recurse: `1 + f(j+1)`.
- **Base case.** `f(n) = 0`.
- **The answer.** `f(0)` counts pieces, so the number of cuts is **`f(0) − 1`**. The video points out that this subtraction is needed because a cut is also counted at the very end.

#### Approach 1: Recursion
**Complexity:** exponential time, O(n) stack.

**C++**
```cpp
bool isPal(int i, int j, string& s) {
    while (i < j) if (s[i++] != s[j--]) return false;
    return true;
}
int ppRec(int i, string& s) {
    if (i == (int)s.size()) return 0;
    int best = INT_MAX;
    for (int j = i; j < (int)s.size(); j++)
        if (isPal(i, j, s)) best = min(best, 1 + ppRec(j + 1, s));
    return best;
}
int minCutRec(string s) { return ppRec(0, s) - 1; }
```

**Java**
```java
class Solution {
    static boolean isPal(int i, int j, String s) {
        while (i < j) if (s.charAt(i++) != s.charAt(j--)) return false;
        return true;
    }
    static int ppRec(int i, String s) {
        if (i == s.length()) return 0;
        int best = Integer.MAX_VALUE;
        for (int j = i; j < s.length(); j++)
            if (isPal(i, j, s)) best = Math.min(best, 1 + ppRec(j + 1, s));
        return best;
    }
    static int minCutRec(String s) { return ppRec(0, s) - 1; }
}
```

#### Approach 2: Memoization
**Complexity:** O(n³) time (O(n²) states and transitions × an O(n) palindrome check), O(n) space.

**C++**
```cpp
bool isPal(int i, int j, string& s) {
    while (i < j) if (s[i++] != s[j--]) return false;
    return true;
}
int ppMemo(int i, string& s, vector<int>& dp) {
    if (i == (int)s.size()) return 0;
    if (dp[i] != -1) return dp[i];
    int best = INT_MAX;
    for (int j = i; j < (int)s.size(); j++)
        if (isPal(i, j, s)) best = min(best, 1 + ppMemo(j + 1, s, dp));
    return dp[i] = best;
}
int minCutMemo(string s) {
    vector<int> dp(s.size(), -1);
    return ppMemo(0, s, dp) - 1;
}
```

**Java**
```java
class Solution {
    static boolean isPal(int i, int j, String s) {
        while (i < j) if (s.charAt(i++) != s.charAt(j--)) return false;
        return true;
    }
    static int ppMemo(int i, String s, int[] dp) {
        if (i == s.length()) return 0;
        if (dp[i] != -1) return dp[i];
        int best = Integer.MAX_VALUE;
        for (int j = i; j < s.length(); j++)
            if (isPal(i, j, s)) best = Math.min(best, 1 + ppMemo(j + 1, s, dp));
        return dp[i] = best;
    }
    static int minCutMemo(String s) {
        int[] dp = new int[s.length()];
        Arrays.fill(dp, -1);
        return ppMemo(0, s, dp) - 1;
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n³) time, O(n) space.

**C++**
```cpp
bool isPal(int i, int j, string& s) {
    while (i < j) if (s[i++] != s[j--]) return false;
    return true;
}
int minCutTab(string s) {
    int n = s.size();
    vector<int> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int best = INT_MAX;
        for (int j = i; j < n; j++)
            if (isPal(i, j, s)) best = min(best, 1 + dp[j + 1]);
        dp[i] = best;
    }
    return dp[0] - 1;
}
```

**Java**
```java
class Solution {
    static boolean isPal(int i, int j, String s) {
        while (i < j) if (s.charAt(i++) != s.charAt(j--)) return false;
        return true;
    }
    static int minCutTab(String s) {
        int n = s.length();
        int[] dp = new int[n + 1];
        for (int i = n - 1; i >= 0; i--) {
            int best = Integer.MAX_VALUE;
            for (int j = i; j < n; j++)
                if (isPal(i, j, s)) best = Math.min(best, 1 + dp[j + 1]);
            dp[i] = best;
        }
        return dp[0] - 1;
    }
}
```

#### Approach 4: Precomputed palindrome table — O(n²) *(not in video)*
`pal[i][j] = s[i] == s[j] && (j − i < 2 || pal[i+1][j−1])` removes the O(n) check.

**Complexity:** O(n²) time, O(n²) space.

**C++**
```cpp
int minCut(string s) {
    int n = s.size();
    vector<vector<bool>> pal(n, vector<bool>(n, false));
    for (int i = n - 1; i >= 0; i--)
        for (int j = i; j < n; j++)
            pal[i][j] = s[i] == s[j] && (j - i < 2 || pal[i + 1][j - 1]);
    vector<int> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int best = INT_MAX;
        for (int j = i; j < n; j++)
            if (pal[i][j]) best = min(best, 1 + dp[j + 1]);
        dp[i] = best;
    }
    return dp[0] - 1;
}
```

**Java**
```java
class Solution {
    static int minCut(String s) {
        int n = s.length();
        boolean[][] pal = new boolean[n][n];
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                pal[i][j] = s.charAt(i) == s.charAt(j) && (j - i < 2 || pal[i + 1][j - 1]);
        int[] dp = new int[n + 1];
        for (int i = n - 1; i >= 0; i--) {
            int best = Integer.MAX_VALUE;
            for (int j = i; j < n; j++)
                if (pal[i][j]) best = Math.min(best, 1 + dp[j + 1]);
            dp[i] = best;
        }
        return dp[0] - 1;
    }
}
```

#### Edge Cases & Pitfalls
- Remember the final `− 1`, which converts the number of pieces into the number of cuts.
- A string that's already a palindrome needs 0 cuts.

#### Key Takeaways
- **Front partition:** `f(i)` means "best for the suffix from `i`". Try every first piece `[i, j]` and recurse on `j+1`.

[↑ Contents](#contents) · [← Previous](#p432) · [Next →](#p434)

---

<a id="p434"></a>

### 50. Partition Array for Maximum Sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › MCM DP | Pro | No | [LeetCode](https://leetcode.com/problems/partition-array-for-maximum-sum/) | [Watch](https://youtu.be/PhWWJmaKfMc) |

#### Problem Statement
**Partition Array for Maximum Sum:** partition `arr` into contiguous subarrays of length **at most k**. Every element of a subarray is then replaced by that subarray's maximum. Return the largest possible sum.

```text
arr = [1,15,7,9,2,5,10], k = 3   ->  84    ([15,15,15],[9],[10,10,10])
arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4  ->  83
arr = [1], k = 1                  ->  1
```

#### Intuition — front partition again
- **The state.** `f(i)` is the best sum for the suffix starting at `i`.
- **The choice.** Try a first piece `[i, j]` with `j < min(n, i + k)`, keeping a running `maxi`. The piece contributes `(j − i + 1) · maxi + f(j+1)`.
- **Base case.** `f(n) = 0`.

#### Approach 1: Recursion
**Complexity:** exponential time, O(n) stack.

**C++**
```cpp
int pamsRec(int i, vector<int>& a, int k) {
    int n = a.size();
    if (i == n) return 0;
    int maxi = INT_MIN, best = INT_MIN;
    for (int j = i; j < min(n, i + k); j++) {
        maxi = max(maxi, a[j]);
        best = max(best, (j - i + 1) * maxi + pamsRec(j + 1, a, k));
    }
    return best;
}
int maxSumAfterPartitioningRec(vector<int>& a, int k) { return pamsRec(0, a, k); }
```

**Java**
```java
class Solution {
    static int pamsRec(int i, int[] a, int k) {
        int n = a.length;
        if (i == n) return 0;
        int maxi = Integer.MIN_VALUE, best = Integer.MIN_VALUE;
        for (int j = i; j < Math.min(n, i + k); j++) {
            maxi = Math.max(maxi, a[j]);
            best = Math.max(best, (j - i + 1) * maxi + pamsRec(j + 1, a, k));
        }
        return best;
    }
    static int maxSumAfterPartitioningRec(int[] a, int k) { return pamsRec(0, a, k); }
}
```

#### Approach 2: Memoization
**Complexity:** O(n·k) time, O(n) + O(n) stack.

**C++**
```cpp
int pamsMemo(int i, vector<int>& a, int k, vector<int>& dp) {
    int n = a.size();
    if (i == n) return 0;
    if (dp[i] != -1) return dp[i];
    int maxi = INT_MIN, best = INT_MIN;
    for (int j = i; j < min(n, i + k); j++) {
        maxi = max(maxi, a[j]);
        best = max(best, (j - i + 1) * maxi + pamsMemo(j + 1, a, k, dp));
    }
    return dp[i] = best;
}
int maxSumAfterPartitioningMemo(vector<int>& a, int k) {
    vector<int> dp(a.size(), -1);
    return pamsMemo(0, a, k, dp);
}
```

**Java**
```java
class Solution {
    static int pamsMemo(int i, int[] a, int k, int[] dp) {
        int n = a.length;
        if (i == n) return 0;
        if (dp[i] != -1) return dp[i];
        int maxi = Integer.MIN_VALUE, best = Integer.MIN_VALUE;
        for (int j = i; j < Math.min(n, i + k); j++) {
            maxi = Math.max(maxi, a[j]);
            best = Math.max(best, (j - i + 1) * maxi + pamsMemo(j + 1, a, k, dp));
        }
        return dp[i] = best;
    }
    static int maxSumAfterPartitioningMemo(int[] a, int k) {
        int[] dp = new int[a.length];
        Arrays.fill(dp, -1);
        return pamsMemo(0, a, k, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(n·k) time, O(n) space.

**C++**
```cpp
int maxSumAfterPartitioning(vector<int>& a, int k) {
    int n = a.size();
    vector<int> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int maxi = INT_MIN, best = INT_MIN;
        for (int j = i; j < min(n, i + k); j++) {
            maxi = max(maxi, a[j]);
            best = max(best, (j - i + 1) * maxi + dp[j + 1]);
        }
        dp[i] = best;
    }
    return dp[0];
}
```

**Java**
```java
class Solution {
    static int maxSumAfterPartitioning(int[] a, int k) {
        int n = a.length;
        int[] dp = new int[n + 1];
        for (int i = n - 1; i >= 0; i--) {
            int maxi = Integer.MIN_VALUE, best = Integer.MIN_VALUE;
            for (int j = i; j < Math.min(n, i + k); j++) {
                maxi = Math.max(maxi, a[j]);
                best = Math.max(best, (j - i + 1) * maxi + dp[j + 1]);
            }
            dp[i] = best;
        }
        return dp[0];
    }
}
```

#### Edge Cases & Pitfalls
- Keep `maxi` as a running maximum **within** the `j` loop; don't recompute it each time.
- `dp[i]` reads up to `dp[i + k]`, so space could be cut to a window of `k + 1` values. That's rarely worth doing.

#### Key Takeaways
- Front partition with a length limit: the inner loop is bounded by `k`, giving O(n·k).

[↑ Contents](#contents) · [← Previous](#p433) · [Next →](#p435)

---

<a id="p435"></a>

### 51. Minimum cost to cut the stick

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › MCM DP | Pro | No | [LeetCode](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/) | [Watch](https://youtu.be/xwomavsC86c) |

#### Problem Statement
**Minimum Cost to Cut a Stick:** a stick of length `n` must be cut at every position in `cuts`, in any order. Each cut costs the **current length** of the piece being cut. Minimise the total cost.

```text
n = 7, cuts = [1, 3, 4, 5]       ->  16
n = 9, cuts = [5, 6, 1, 4, 2]    ->  22
```

#### Intuition — MCM-style partition on the sorted cut list
- **Prepare the cuts.** **Sort** them so each subproblem is a contiguous range of cuts on a contiguous piece, then pad with `0` and `n`: `c = [0, sorted cuts…, n]`.
- **The state.** `f(i, j)` is the minimum cost to make cuts `c[i … j]` on the piece from `c[i−1]` to `c[j+1]`.
- **The choice.** Choose which cut `ind ∈ [i, j]` to make first. It costs the piece length `c[j+1] − c[i−1]`, and leaves two independent pieces: `f(i, ind−1)` and `f(ind+1, j)`.
- **Base case and answer.** `i > j` costs 0. The answer is `f(1, m)`, where `m` is the number of cuts.

#### Approach 1: Recursion
**Complexity:** exponential time, O(m) stack.

**C++**
```cpp
int csRec(int i, int j, vector<int>& c) {
    if (i > j) return 0;
    int best = INT_MAX;
    for (int ind = i; ind <= j; ind++)
        best = min(best, c[j + 1] - c[i - 1] + csRec(i, ind - 1, c) + csRec(ind + 1, j, c));
    return best;
}
int minCostRec(int n, vector<int> cuts) {
    int m = cuts.size();
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    return csRec(1, m, cuts);
}
```

**Java**
```java
class Solution {
    static int csRec(int i, int j, int[] c) {
        if (i > j) return 0;
        int best = Integer.MAX_VALUE;
        for (int ind = i; ind <= j; ind++)
            best = Math.min(best, c[j + 1] - c[i - 1] + csRec(i, ind - 1, c) + csRec(ind + 1, j, c));
        return best;
    }
    static int minCostRec(int n, int[] cuts) {
        int m = cuts.length;
        int[] c = new int[m + 2];
        c[0] = 0; c[m + 1] = n;
        for (int i = 0; i < m; i++) c[i + 1] = cuts[i];
        Arrays.sort(c);
        return csRec(1, m, c);
    }
}
```

#### Approach 2: Memoization
**Complexity:** O(m³) time, O(m²) + O(m) stack.

**C++**
```cpp
int csMemo(int i, int j, vector<int>& c, vector<vector<int>>& dp) {
    if (i > j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int best = INT_MAX;
    for (int ind = i; ind <= j; ind++)
        best = min(best, c[j + 1] - c[i - 1] + csMemo(i, ind - 1, c, dp) + csMemo(ind + 1, j, c, dp));
    return dp[i][j] = best;
}
int minCostMemo(int n, vector<int> cuts) {
    int m = cuts.size();
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(m + 2, vector<int>(m + 2, -1));
    return csMemo(1, m, cuts, dp);
}
```

**Java**
```java
class Solution {
    static int csMemo(int i, int j, int[] c, int[][] dp) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        int best = Integer.MAX_VALUE;
        for (int ind = i; ind <= j; ind++)
            best = Math.min(best, c[j + 1] - c[i - 1] + csMemo(i, ind - 1, c, dp) + csMemo(ind + 1, j, c, dp));
        return dp[i][j] = best;
    }
    static int minCostMemo(int n, int[] cuts) {
        int m = cuts.length;
        int[] c = new int[m + 2];
        c[m + 1] = n;
        for (int i = 0; i < m; i++) c[i + 1] = cuts[i];
        Arrays.sort(c);
        int[][] dp = new int[m + 2][m + 2];
        for (int[] r : dp) Arrays.fill(r, -1);
        return csMemo(1, m, c, dp);
    }
}
```

#### Approach 3: Tabulation
**Complexity:** O(m³) time, O(m²) space.

**C++**
```cpp
int minCost(int n, vector<int> cuts) {
    int m = cuts.size();
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(m + 2, vector<int>(m + 2, 0));
    for (int i = m; i >= 1; i--)
        for (int j = i; j <= m; j++) {
            int best = INT_MAX;
            for (int ind = i; ind <= j; ind++)
                best = min(best, cuts[j + 1] - cuts[i - 1] + dp[i][ind - 1] + dp[ind + 1][j]);
            dp[i][j] = best;
        }
    return dp[1][m];
}
```

**Java**
```java
class Solution {
    static int minCost(int n, int[] cuts) {
        int m = cuts.length;
        int[] c = new int[m + 2];
        c[m + 1] = n;
        for (int i = 0; i < m; i++) c[i + 1] = cuts[i];
        Arrays.sort(c);
        int[][] dp = new int[m + 2][m + 2];
        for (int i = m; i >= 1; i--)
            for (int j = i; j <= m; j++) {
                int best = Integer.MAX_VALUE;
                for (int ind = i; ind <= j; ind++)
                    best = Math.min(best, c[j + 1] - c[i - 1] + dp[i][ind - 1] + dp[ind + 1][j]);
                dp[i][j] = best;
            }
        return dp[1][m];
    }
}
```

#### Edge Cases & Pitfalls
- **Sorting is essential.** Without it, cuts `i … j` don't describe one contiguous piece.
- The state is over cut indices (`m ≤ 100`), not stick length (`n` up to 10⁶).

#### Key Takeaways
- This is the same "pick the operation inside the interval" structure as Burst Balloons, but here the first cut is chosen, because its cost (the full piece) is known up front.

[↑ Contents](#contents) · [← Previous](#p434) · [Next →](#p436)

---

<a id="p436"></a>

### 52. Different Ways to Evaluate a Boolean Expression

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Dynamic Programming › MCM DP | Pro | No | [LeetCode](https://leetcode.com/problems/parsing-a-boolean-expression/) | [Watch](https://youtu.be/MM7fXopgyjw) |

> **Problem choice:** this note follows the linked video, *DP 52 — Evaluate Boolean Expression to True*: count the parenthesisations that evaluate to true, modulo 1e9+7. The sheet's LeetCode link (LC 1106 *Parsing a Boolean Expression*) is a different, non-DP problem, covered briefly at the end. The video was available with Hindi captions only.

#### Problem Statement
An expression string alternates operands (`T` or `F`) with operators (`&`, `|`, `^`). Count the ways to parenthesise it so that it evaluates to **true**, modulo 1e9+7.

```text
exp = "T|T&F"     ->  1   ((T|T)&F = F,  T|(T&F) = T)
exp = "F|T^F"     ->  2
exp = "T^F|F"     ->  2
```

#### Intuition — partition on each operator, tracking both true and false counts
- **Why false counts are needed.** To get *true* from `L op R`, some operators need **false** results from a side: `F | T` is true, and `T ^ F` is true. So the state also carries **`isTrue`**: `f(i, j, isTrue)` counts the ways `exp[i … j]` evaluates to `isTrue`. That gives a 3-D DP of size `n × n × 2`.
- **Splitting.** For each operator position `ind` (`i+1, i+3, …, j−1`), compute `LT`, `LF` (left side true/false counts) and `RT`, `RF` (right side), then combine:

| op | ways to be **true** | ways to be **false** |
|---|---|---|
| `&` | LT·RT | LT·RF + LF·RT + LF·RF |
| `\|` | LT·RT + LT·RF + LF·RT | LF·RF |
| `^` | LT·RF + LF·RT | LT·RT + LF·RF |

- **Base case.** `i == j` returns 1 if the operand equals `isTrue`, else 0. The video also covers `i > j`, returning 0.
- **Modulo.** The video repeatedly stresses applying the modulo after **every** multiplication and addition.

#### Approach 1: Recursion
**Complexity:** exponential time, O(n) stack.

**C++**
```cpp
const long long MOD = 1e9 + 7;
long long beRec(int i, int j, int isTrue, string& e) {
    if (i > j) return 0;
    if (i == j) return isTrue ? e[i] == 'T' : e[i] == 'F';
    long long ways = 0;
    for (int ind = i + 1; ind <= j - 1; ind += 2) {
        long long LT = beRec(i, ind - 1, 1, e), LF = beRec(i, ind - 1, 0, e);
        long long RT = beRec(ind + 1, j, 1, e), RF = beRec(ind + 1, j, 0, e);
        if (e[ind] == '&') ways += isTrue ? LT * RT % MOD : (LT * RF + LF * RT + LF * RF) % MOD;
        else if (e[ind] == '|') ways += isTrue ? (LT * RT + LT * RF + LF * RT) % MOD : LF * RF % MOD;
        else ways += isTrue ? (LT * RF + LF * RT) % MOD : (LT * RT + LF * RF) % MOD;
        ways %= MOD;
    }
    return ways;
}
int evaluateExpRec(string e) { return beRec(0, e.size() - 1, 1, e); }
```

**Java**
```java
class Solution {
    static final long MOD = 1_000_000_007L;
    static long beRec(int i, int j, int isTrue, String e) {
        if (i > j) return 0;
        if (i == j) return (isTrue == 1) == (e.charAt(i) == 'T') ? 1 : 0;
        long ways = 0;
        for (int ind = i + 1; ind <= j - 1; ind += 2) {
            long LT = beRec(i, ind - 1, 1, e), LF = beRec(i, ind - 1, 0, e);
            long RT = beRec(ind + 1, j, 1, e), RF = beRec(ind + 1, j, 0, e);
            char op = e.charAt(ind);
            if (op == '&') ways += isTrue == 1 ? LT * RT % MOD : (LT * RF + LF * RT + LF * RF) % MOD;
            else if (op == '|') ways += isTrue == 1 ? (LT * RT + LT * RF + LF * RT) % MOD : LF * RF % MOD;
            else ways += isTrue == 1 ? (LT * RF + LF * RT) % MOD : (LT * RT + LF * RF) % MOD;
            ways %= MOD;
        }
        return ways;
    }
    static int evaluateExpRec(String e) { return (int) beRec(0, e.length() - 1, 1, e); }
}
```

#### Approach 2: Memoization — dp[n][n][2]
**Complexity:** O(n³) time, O(n²·2) + O(n) stack.

**C++**
```cpp
const long long MOD = 1e9 + 7;
long long beMemo(int i, int j, int isTrue, string& e, vector<vector<vector<long long>>>& dp) {
    if (i > j) return 0;
    if (i == j) return isTrue ? e[i] == 'T' : e[i] == 'F';
    if (dp[i][j][isTrue] != -1) return dp[i][j][isTrue];
    long long ways = 0;
    for (int ind = i + 1; ind <= j - 1; ind += 2) {
        long long LT = beMemo(i, ind - 1, 1, e, dp), LF = beMemo(i, ind - 1, 0, e, dp);
        long long RT = beMemo(ind + 1, j, 1, e, dp), RF = beMemo(ind + 1, j, 0, e, dp);
        if (e[ind] == '&') ways += isTrue ? LT * RT % MOD : (LT * RF + LF * RT + LF * RF) % MOD;
        else if (e[ind] == '|') ways += isTrue ? (LT * RT + LT * RF + LF * RT) % MOD : LF * RF % MOD;
        else ways += isTrue ? (LT * RF + LF * RT) % MOD : (LT * RT + LF * RF) % MOD;
        ways %= MOD;
    }
    return dp[i][j][isTrue] = ways;
}
int evaluateExpMemo(string e) {
    int n = e.size();
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, -1)));
    return beMemo(0, n - 1, 1, e, dp);
}
```

**Java**
```java
class Solution {
    static final long MOD = 1_000_000_007L;
    static long beMemo(int i, int j, int isTrue, String e, long[][][] dp) {
        if (i > j) return 0;
        if (i == j) return (isTrue == 1) == (e.charAt(i) == 'T') ? 1 : 0;
        if (dp[i][j][isTrue] != -1) return dp[i][j][isTrue];
        long ways = 0;
        for (int ind = i + 1; ind <= j - 1; ind += 2) {
            long LT = beMemo(i, ind - 1, 1, e, dp), LF = beMemo(i, ind - 1, 0, e, dp);
            long RT = beMemo(ind + 1, j, 1, e, dp), RF = beMemo(ind + 1, j, 0, e, dp);
            char op = e.charAt(ind);
            if (op == '&') ways += isTrue == 1 ? LT * RT % MOD : (LT * RF + LF * RT + LF * RF) % MOD;
            else if (op == '|') ways += isTrue == 1 ? (LT * RT + LT * RF + LF * RT) % MOD : LF * RF % MOD;
            else ways += isTrue == 1 ? (LT * RF + LF * RT) % MOD : (LT * RT + LF * RF) % MOD;
            ways %= MOD;
        }
        return dp[i][j][isTrue] = ways;
    }
    static int evaluateExpMemo(String e) {
        int n = e.length();
        long[][][] dp = new long[n][n][2];
        for (long[][] a : dp) for (long[] b : a) Arrays.fill(b, -1);
        return (int) beMemo(0, n - 1, 1, e, dp);
    }
}
```

#### Approach 3: Tabulation — i from n−1 down, j from i up
**Complexity:** O(n³) time, O(n²·2) space.

**C++**
```cpp
const long long MOD = 1e9 + 7;
int evaluateExp(string e) {
    int n = e.size();
    vector<vector<array<long long, 2>>> dp(n, vector<array<long long, 2>>(n, {0, 0}));
    for (int i = n - 1; i >= 0; i--)
        for (int j = i; j < n; j++) {
            if (i == j) { dp[i][j][1] = e[i] == 'T'; dp[i][j][0] = e[i] == 'F'; continue; }
            for (int isTrue = 0; isTrue <= 1; isTrue++) {
                long long ways = 0;
                for (int ind = i + 1; ind <= j - 1; ind += 2) {
                    long long LT = dp[i][ind - 1][1], LF = dp[i][ind - 1][0];
                    long long RT = dp[ind + 1][j][1], RF = dp[ind + 1][j][0];
                    if (e[ind] == '&') ways += isTrue ? LT * RT % MOD : (LT * RF + LF * RT + LF * RF) % MOD;
                    else if (e[ind] == '|') ways += isTrue ? (LT * RT + LT * RF + LF * RT) % MOD : LF * RF % MOD;
                    else ways += isTrue ? (LT * RF + LF * RT) % MOD : (LT * RT + LF * RF) % MOD;
                    ways %= MOD;
                }
                dp[i][j][isTrue] = ways;
            }
        }
    return dp[0][n - 1][1];
}
```

**Java**
```java
class Solution {
    static final long MOD = 1_000_000_007L;
    static int evaluateExp(String e) {
        int n = e.length();
        long[][][] dp = new long[n][n][2];
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++) {
                if (i == j) { dp[i][j][1] = e.charAt(i) == 'T' ? 1 : 0; dp[i][j][0] = e.charAt(i) == 'F' ? 1 : 0; continue; }
                for (int isTrue = 0; isTrue <= 1; isTrue++) {
                    long ways = 0;
                    for (int ind = i + 1; ind <= j - 1; ind += 2) {
                        long LT = dp[i][ind - 1][1], LF = dp[i][ind - 1][0];
                        long RT = dp[ind + 1][j][1], RF = dp[ind + 1][j][0];
                        char op = e.charAt(ind);
                        if (op == '&') ways += isTrue == 1 ? LT * RT % MOD : (LT * RF + LF * RT + LF * RF) % MOD;
                        else if (op == '|') ways += isTrue == 1 ? (LT * RT + LT * RF + LF * RT) % MOD : LF * RF % MOD;
                        else ways += isTrue == 1 ? (LT * RF + LF * RT) % MOD : (LT * RT + LF * RF) % MOD;
                        ways %= MOD;
                    }
                    dp[i][j][isTrue] = ways;
                }
            }
        return (int) dp[0][n - 1][1];
    }
}
```

#### Related problem: LC 1106 — Parsing a Boolean Expression (the sheet's link)
**Problem.** Evaluate a nested expression such as `"|(&(t,f,t),!(f))"` and return its value. There are no choices to make, so this is **parsing, not DP**.

**Approach.** Use a stack:
- push every character except `,`;
- on `)`, pop operands until `(`, then pop the operator and push the result.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
bool parseBoolExpr(string expr) {
    stack<char> st;
    for (char c : expr) {
        if (c == ',') continue;
        if (c != ')') { st.push(c); continue; }
        int t = 0, f = 0;
        while (st.top() != '(') { (st.top() == 't' ? t : f)++; st.pop(); }
        st.pop();                                              // '('
        char op = st.top(); st.pop();
        char res;
        if (op == '&') res = f == 0 ? 't' : 'f';
        else if (op == '|') res = t > 0 ? 't' : 'f';
        else res = f == 1 ? 't' : 'f';                         // '!': one operand
        st.push(res);
    }
    return st.top() == 't';
}
```

**Java**
```java
class Solution {
    static boolean parseBoolExpr(String expr) {
        Deque<Character> st = new ArrayDeque<>();
        for (char c : expr.toCharArray()) {
            if (c == ',') continue;
            if (c != ')') { st.push(c); continue; }
            int t = 0, f = 0;
            while (st.peek() != '(') { if (st.pop() == 't') t++; else f++; }
            st.pop();
            char op = st.pop();
            char res;
            if (op == '&') res = f == 0 ? 't' : 'f';
            else if (op == '|') res = t > 0 ? 't' : 'f';
            else res = f == 1 ? 't' : 'f';
            st.push(res);
        }
        return st.peek() == 't';
    }
}
```

#### Edge Cases & Pitfalls
- Operators sit at **odd** indices only, so step `ind` by 2.
- Multiplying two values below 1e9+7 fits in 64 bits. Take the modulo after each product and each sum.

#### Key Takeaways
- If combining sub-results needs more than the target outcome, add the outcome (true/false) to the state. Partition DP on operators gives the classic n × n × 2 table.

[↑ Contents](#contents) · [← Previous](#p435)

---
