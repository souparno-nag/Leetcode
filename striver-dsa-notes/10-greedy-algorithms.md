# Greedy Algorithms — Striver's A2Z DSA Sheet Notes

Section 10 of 20 · 14 problems · 14 with video, 0 without · [All sections](00-index.md)

[← Bit Manipulation](09-bit-manipulation.md) | [Sliding Window / 2 Pointer →](11-sliding-window-2-pointer.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Easy**

1. [Assign Cookies](#p221) — Core
2. [Lemonade Change](#p222) — Core
3. [Fractional Knapsack](#p223) — Core
4. [Jump Game - I](#p224) — Core

**Scheduling and Interval Problems**

5. [Shortest Job First](#p225) — Core
6. [Job sequencing Problem](#p226) — Core
7. [N meetings in one room](#p227) — Core
8. [Non-overlapping Intervals](#p228) — Core
9. [Insert Interval](#p229) — Core
10. [Merge Intervals](#p230) — Core
11. [Minimum number of platforms required for a railway](#p231) — Core

**Hard**

12. [Valid Parenthesis Checker](#p232) — Pro
13. [Candy](#p233) — Pro
14. [Jump Game II](#p234) — Pro

---

## Easy

<a id="p221"></a>

### 1. Assign Cookies

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Easy | Core | No | [LeetCode](https://leetcode.com/problems/assign-cookies/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/assign-cookies) | [Watch](https://youtu.be/DIX2p7vb9co) |

#### Problem Statement
A parent has `n` children with greed factors `g[i]` and `m` cookies with sizes `s[j]`.
- Child `i` is satisfied only by a cookie with `s[j] ≥ g[i]`.
- Each cookie goes to at most one child, and each child gets at most one cookie.

Return the **maximum number of satisfied children**.

```text
g = [1, 5, 3, 3, 4],  s = [4, 2, 1, 2, 1, 3]   ->   3
(e.g. greed 1 gets cookie 1, greed 3 gets cookie 3, the other greed 3 gets cookie 4; greed 4 and 5 go unsatisfied)
```

#### Intuition — why greedy
Handing out cookies in array order can waste big cookies. Giving the 4 to the child with greed 1 satisfies only 2 children here. The greedy choice is to give each child the **smallest cookie that still satisfies them** and save bigger cookies for greedier children. To make that easy, **sort both arrays**.

#### Approach: Sort + two pointers (as in the video)
- `l` walks the cookies and `r` walks the children, both sorted ascending.
- For each cookie `s[l]`: if it satisfies child `g[r]`, that child is done, so `r++`.
- Either way the cookie has been used or proven useless, so `l++`. A cookie too small for child `r` is too small for every child after `r` as well, because the greeds are sorted.
- When the cookies run out, **`r` = number of satisfied children**.

Dry run:
- Sorted cookies: 1, 1, 2, 2, 3, 4. Sorted greeds: 1, 3, 3, 4, 5.
- Cookie 1 satisfies greed 1, so r = 1.
- Cookies 1, 2 and 2 can't satisfy greed 3.
- Cookie 3 satisfies greed 3, so r = 2.
- Cookie 4 satisfies the second greed 3, so r = 3.
- Answer: 3.

**Complexity:** O(n log n + m log m + m) time. O(1) extra space, though the inputs are reordered.

**C++**
```cpp
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int n = g.size(), m = s.size();
    int l = 0, r = 0;                 // l -> cookies, r -> children
    while (l < m && r < n) {
        if (g[r] <= s[l]) r++;        // cookie l satisfies child r
        l++;                          // cookie l is used up / useless
    }
    return r;
}
```

**Java**
```java
class Solution {
    static int findContentChildren(int[] g, int[] s) {
        Arrays.sort(g);
        Arrays.sort(s);
        int n = g.length, m = s.length;
        int l = 0, r = 0;
        while (l < m && r < n) {
            if (g[r] <= s[l]) r++;
            l++;
        }
        return r;
    }
}
```

#### Edge Cases & Pitfalls
- Stop when **either** array is exhausted. The video's loop only checks `l < m`; once every child is satisfied, `g[r]` would read out of bounds. Hence `r < n` in the condition.
- No cookies, or no children, gives 0.

#### Key Takeaways
- This is the classic greedy "use the smallest resource that works". Sorting turns it into a linear two-pointer sweep.

[↑ Contents](#contents) · [Next →](#p222)

---

<a id="p222"></a>

### 2. Lemonade Change

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Easy | Core | No | [LeetCode](https://leetcode.com/problems/lemonade-change/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/lemonade-change) | [Watch](https://youtu.be/n_tmibEhO6Q) |

#### Problem Statement
Lemonade costs $5. Customers arrive in order, each paying with a single $5, $10 or $20 bill (`bills[i]`). You start with **no change**. Return `true` if you can give every customer correct change.

```text
bills = [5, 5, 5, 10, 20]   ->   true
bills = [5, 5, 10, 10, 20]  ->   false  (the last customer needs 15 back: you hold two 10s but no 5)
```

#### Intuition
Track how many $5 and $10 bills you hold. $20 bills are never given as change, so they don't need tracking.
- **$5:** keep it.
- **$10:** you must return one $5.
- **$20:** you must return $15. Either give one $10 and one $5, or three $5s. **Prefer the $10 + $5**, which is the greedy choice: $5s are more flexible, since they're needed for both $10 and $20 customers, while a $10 is only useful for a $20.

#### Approach: Count bills, greedy change
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;
    for (int b : bills) {
        if (b == 5) five++;
        else if (b == 10) {
            if (five == 0) return false;
            five--; ten++;
        } else {                                  // b == 20
            if (ten > 0 && five > 0) { ten--; five--; }
            else if (five >= 3) five -= 3;
            else return false;
        }
    }
    return true;
}
```

**Java**
```java
class Solution {
    static boolean lemonadeChange(int[] bills) {
        int five = 0, ten = 0;
        for (int b : bills) {
            if (b == 5) five++;
            else if (b == 10) {
                if (five == 0) return false;
                five--; ten++;
            } else {
                if (ten > 0 && five > 0) { ten--; five--; }
                else if (five >= 3) five -= 3;
                else return false;
            }
        }
        return true;
    }
}
```

#### Edge Cases & Pitfalls
- Trying "three 5s" first can fail later. For example, `[5,5,5,10,20,10]`: paying the 20 with three 5s leaves no 5 for the final 10.
- Return `false` the moment change can't be made. Later customers don't matter.

#### Key Takeaways
- When making change, hand out the least flexible denomination first.

[↑ Contents](#contents) · [← Previous](#p221) · [Next →](#p223)

---

<a id="p223"></a>

### 3. Fractional Knapsack

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Easy | Core | No | — | [Watch](https://youtu.be/1ibsQrnuEEg) |

#### Problem Statement
There are `n` items with `value[i]` and `weight[i]`, and a bag of capacity `W`. You may take **fractions** of items. Maximise the total value in the bag.

```text
value = [100, 60, 100, 200], weight = [20, 10, 50, 50], W = 90   ->   380.0
(take 60/10, 100/20 and 200/50 whole, then 10/50 of the last item, worth 20)
```

#### Intuition
- **Taking the highest value first fails.** With items (100,20), (60,10), (100,50) and (200,90), W = 90, picking (200,90) fills the bag at value 200. Taking the three small items and part of the big one beats that.
- **The right measure is value per unit weight.** Here those ratios are 5, 6, 2 and 4. Greedily fill the bag with the best ratio first.
- **Fractions remove the risk.** You can always top up with part of the next-best item, so this greedy is optimal. This is unlike 0/1 knapsack, which needs DP.

#### Approach: Sort by value/weight descending, then fill (as in the video)
- Sort the items by `value / weight` in **descending** order, using a custom comparator.
- Walk the items:
  - if `weight ≤ W`, take the whole item: `total += value`, `W −= weight`;
  - otherwise take the fraction `value / weight × W` and **break**, because the bag is now full.

Dry run (W = 90):
- Sorted: (60,10), (100,20), (200,50), (100,50).
- Take 60 (W = 80), then 100 (W = 60), then 200 (W = 10).
- Take 100/50 × 10 = 20.
- Total: **380**.

**Complexity:** O(n log n + n) time. O(n) space for the item pairs here (O(1) if you sort the items in place).

**C++**
```cpp
double fractionalKnapsack(vector<int>& val, vector<int>& wt, int W) {
    int n = val.size();
    vector<pair<int, int>> items(n);             // {value, weight}
    for (int i = 0; i < n; i++) items[i] = {val[i], wt[i]};
    sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return (double)a.first / a.second > (double)b.first / b.second;   // value/weight desc
    });
    double total = 0.0;
    for (auto& it : items) {
        if (it.second <= W) {                    // take the whole item
            total += it.first;
            W -= it.second;
        } else {                                 // take only the part that fits
            total += (double)it.first / it.second * W;
            break;
        }
    }
    return total;
}
```

**Java**
```java
class Solution {
    static double fractionalKnapsack(int[] val, int[] wt, int W) {
        int n = val.length;
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; i++) idx[i] = i;
        Arrays.sort(idx, (a, b) -> Double.compare((double) val[b] / wt[b], (double) val[a] / wt[a]));
        double total = 0.0;
        for (int k = 0; k < n; k++) {
            int i = idx[k];
            if (wt[i] <= W) {
                total += val[i];
                W -= wt[i];
            } else {
                total += (double) val[i] / wt[i] * W;
                break;
            }
        }
        return total;
    }
}
```

#### Edge Cases & Pitfalls
- **Cast to double** before dividing. Integer division silently truncates the ratio and the fraction.
- A comparator must be a strict weak ordering. Return `a > b`, not `a >= b`, in C++. The video writes `>=`, which can crash `std::sort` on equal ratios. The C++ alternative *(not in video)* is to compare `a.first * b.second > b.first * a.second` in `long long`, which avoids floating point entirely.
- Ties in ratio don't matter. Either order gives the same total.

#### Key Takeaways
- Fractional knapsack is greedy by value density. 0/1 knapsack is not; it needs DP (see the Dynamic Programming section).

[↑ Contents](#contents) · [← Previous](#p222) · [Next →](#p224)

---

<a id="p224"></a>

### 4. Jump Game - I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Easy | Core | No | [LeetCode](https://leetcode.com/problems/jump-game/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/jump-game) | [Watch](https://youtu.be/tZAa_jJ3SwQ) |

#### Problem Statement
You start at index 0 of `nums`, where `nums[i]` is the **maximum** jump length from index `i`. Return `true` if you can reach the last index.

```text
nums = [2, 3, 1, 1, 4]        ->  true   (0 -> 1 -> 4)
nums = [3, 2, 1, 0, 4]        ->  false  (every path gets stuck on the 0 at index 3)
nums = [1, 2, 4, 1, 1, 0, 2, 5] -> true
```

#### Intuition
- Without zeros you can always move forward at least one step, so the end is always reachable. **Zeros are the only obstacle**, and the question is whether some earlier index can jump **over** them.
- Track `maxIndex`, the furthest index reachable so far. At each index `i`:
  - if `i > maxIndex`, nobody could reach `i`, so return `false`;
  - otherwise update `maxIndex = max(maxIndex, i + nums[i])`.

Dry run on `[1,2,3,1,1,0,2,5]`:
- maxIndex goes 1, 3, 5, 5, 5, 5.
- At i = 6, 6 > 5. No one reaches index 6, so return **false**.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
bool canJump(vector<int>& nums) {
    int n = nums.size();
    int maxIndex = 0;
    for (int i = 0; i < n; i++) {
        if (i > maxIndex) return false;           // index i is unreachable
        maxIndex = max(maxIndex, i + nums[i]);
        if (maxIndex >= n - 1) return true;       // early exit
    }
    return true;
}
```

**Java**
```java
class Solution {
    static boolean canJump(int[] nums) {
        int n = nums.length;
        int maxIndex = 0;
        for (int i = 0; i < n; i++) {
            if (i > maxIndex) return false;
            maxIndex = Math.max(maxIndex, i + nums[i]);
            if (maxIndex >= n - 1) return true;
        }
        return true;
    }
}
```

#### Edge Cases & Pitfalls
- A single element (`[0]`) is already at the end, so the answer is `true`.
- Jump values are maximums, not exact lengths. You may land anywhere in `[i+1, i+nums[i]]`, which is why tracking the furthest reach is enough.

#### Key Takeaways
- Maintain the furthest reachable index. Failing means hitting an index beyond it.
- "If there is no 0 you always reach the end" is a good edge case to mention in an interview.

[↑ Contents](#contents) · [← Previous](#p223) · [Next →](#p225)

---

## Scheduling and Interval Problems

<a id="p225"></a>

### 5. Shortest Job First

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Scheduling and Interval Problems | Core | Yes | — | [Watch](https://youtu.be/3-QbX1iDbXs) |

#### Problem Statement
`n` processes all arrive at time 0, with burst (execution) times `bt[i]`. Using **Shortest Job First** (always run the waiting process with the smallest execution time next), return the **average waiting time**, rounded down to an integer.

```text
bt = [4, 3, 7, 1, 2]   ->   4
order: 1 (wait 0), 2 (wait 1), 3 (wait 3), 4 (wait 6), 7 (wait 10)  ->  total 20, 20 / 5 = 4
```

#### Intuition
SJF *is* the greedy rule: run the shortest job first. Since all jobs arrive at time 0, **sort** the burst times. Each job's waiting time is the **sum of the burst times run before it**. Putting short jobs first keeps those prefix sums small, which minimises the total wait.

#### Approach: Sort, then accumulate start times
- Keep a clock `t = 0` and a running `waitTime = 0`.
- For each job in sorted order:
  - `waitTime += t`, the time it waited before starting;
  - then `t += bt[i]`.
- Return `waitTime / n` using integer division, which floors for non-negative values.

**Complexity:** O(n log n + n) time, O(1) extra space. The input is sorted in place.

**C++**
```cpp
long long shortestJobFirst(vector<int> bt) {
    sort(bt.begin(), bt.end());
    long long t = 0, waitTime = 0;
    int n = bt.size();
    for (int i = 0; i < n; i++) {
        waitTime += t;       // job i starts at time t
        t += bt[i];
    }
    return waitTime / n;
}
```

**Java**
```java
class Solution {
    static long shortestJobFirst(int[] bt) {
        int[] a = bt.clone();
        Arrays.sort(a);
        long t = 0, waitTime = 0;
        int n = a.length;
        for (int i = 0; i < n; i++) {
            waitTime += t;
            t += a[i];
        }
        return waitTime / n;
    }
}
```

#### Edge Cases & Pitfalls
- Use 64-bit totals. With large n and burst times, the sum of prefix sums grows quadratically.
- This assumes **all arrivals at time 0** (non-preemptive SJF). With different arrival times you'd need a min-heap of the arrived jobs.

#### Key Takeaways
- Shortest-first minimises the sum of completion and waiting times. It is the canonical "exchange argument" greedy.

[↑ Contents](#contents) · [← Previous](#p224) · [Next →](#p226)

---

<a id="p226"></a>

### 6. Job sequencing Problem

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Scheduling and Interval Problems | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/job-sequencing-problem) | [Watch](https://youtu.be/QbwltemZbRg) |

#### Problem Statement
There are `n` jobs, each with an id, a `deadline` and a `profit`.
- Every job takes exactly **one day**.
- Only one job can be done per day.
- A job with deadline `d` must be done on one of days `1 … d`.

Maximise the total profit. Return **{number of jobs done, maximum profit}**.

```text
deadline = [4, 1, 1, 1], profit = [20, 10, 40, 30]                    ->  {2, 60}
(id, deadline, profit) = (1,4,20) (2,5,60) (3,6,70) (4,6,65) (5,4,25) (6,2,80) (7,2,10) (8,2,22)
                                                                       ->  {6, 322}
```

#### Intuition — two greedy choices (from the video)
1. **Do the most profitable jobs first.** Sort by profit, descending.
2. **Do each job as late as possible.** Use the latest free day on or before its deadline. A job with deadline 4 done on day 1 would block day 1 for jobs whose deadline is 1. Scheduling it late keeps the early days free for urgent jobs.

#### Approach 1: Sort by profit + slot array (as in the video)
- `maxDeadline` = the largest deadline. Make `slot[1 … maxDeadline]`, filled with −1 (meaning free).
- For each job in descending profit order, scan `j = deadline, deadline−1, …, 1` for the first free day.
  - If you find one, book it: `count++`, `totalProfit += profit`, then **break**.
  - If no day is free, skip the job.

Dry run on the second example (sorted by profit):

| job (d, p) | slot taken | count | profit |
|---|---|---|---|
| 6 (2, 80) | 2 | 1 | 80 |
| 3 (6, 70) | 6 | 2 | 150 |
| 4 (6, 65) | 5 | 3 | 215 |
| 2 (5, 60) | 4 | 4 | 275 |
| 5 (4, 25) | 3 | 5 | 300 |
| 8 (2, 22) | 1 | 6 | 322 |
| 1 (4, 20) | days 4…1 all busy, skipped | 6 | 322 |
| 7 (2, 10) | skipped | 6 | 322 |

**Complexity:**
- Time: O(n log n + n · maxDeadline).
- Space: O(maxDeadline) for the slot array.

**C++**
```cpp
vector<int> jobSequencing(vector<int>& deadline, vector<int>& profit) {
    int n = deadline.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) { return profit[a] > profit[b]; });
    int maxDeadline = *max_element(deadline.begin(), deadline.end());
    vector<int> slot(maxDeadline + 1, -1);           // slot[day] = job index, -1 = free
    int count = 0, totalProfit = 0;
    for (int k = 0; k < n; k++) {
        int i = idx[k];
        for (int j = deadline[i]; j >= 1; j--) {     // latest free day <= deadline
            if (slot[j] == -1) {
                slot[j] = i;
                count++;
                totalProfit += profit[i];
                break;
            }
        }
    }
    return {count, totalProfit};
}
```

**Java**
```java
class Solution {
    static int[] jobSequencing(int[] deadline, int[] profit) {
        int n = deadline.length;
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; i++) idx[i] = i;
        Arrays.sort(idx, (a, b) -> profit[b] - profit[a]);
        int maxDeadline = 0;
        for (int d : deadline) maxDeadline = Math.max(maxDeadline, d);
        int[] slot = new int[maxDeadline + 1];
        Arrays.fill(slot, -1);
        int count = 0, totalProfit = 0;
        for (int k = 0; k < n; k++) {
            int i = idx[k];
            for (int j = deadline[i]; j >= 1; j--) {
                if (slot[j] == -1) {
                    slot[j] = i;
                    count++;
                    totalProfit += profit[i];
                    break;
                }
            }
        }
        return new int[]{count, totalProfit};
    }
}
```

#### Approach 2: Optimised slot search with DSU *(mentioned in the video, not taught; code not in video)*
The inner loop hunts for the latest free day ≤ deadline. A disjoint-set ("parent" pointers) answers that in almost O(1):
- `find(d)` returns the latest free day ≤ d, where 0 means none.
- After booking day `t`, link `t → t − 1`.

Path compression keeps the chains short. The DSU itself is taught in the Graphs section.

**Complexity:** O(n log n + n·α(n)) time, O(maxDeadline) space.

**C++**
```cpp
int findSlot(vector<int>& par, int d) {
    return par[d] == d ? d : par[d] = findSlot(par, par[d]);
}
vector<int> jobSequencingDSU(vector<int>& deadline, vector<int>& profit) {
    int n = deadline.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) { return profit[a] > profit[b]; });
    int maxDeadline = *max_element(deadline.begin(), deadline.end());
    vector<int> par(maxDeadline + 1);
    iota(par.begin(), par.end(), 0);                 // every day is its own free slot
    int count = 0, totalProfit = 0;
    for (int i : idx) {
        int t = findSlot(par, deadline[i]);
        if (t > 0) {
            count++;
            totalProfit += profit[i];
            par[t] = t - 1;                          // day t is now taken
        }
    }
    return {count, totalProfit};
}
```

**Java**
```java
class Solution {
    static int findSlot(int[] par, int d) {
        while (par[d] != d) { par[d] = par[par[d]]; d = par[d]; }   // path halving
        return d;
    }
    static int[] jobSequencingDSU(int[] deadline, int[] profit) {
        int n = deadline.length;
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; i++) idx[i] = i;
        Arrays.sort(idx, (a, b) -> profit[b] - profit[a]);
        int maxDeadline = 0;
        for (int d : deadline) maxDeadline = Math.max(maxDeadline, d);
        int[] par = new int[maxDeadline + 1];
        for (int i = 0; i <= maxDeadline; i++) par[i] = i;
        int count = 0, totalProfit = 0;
        for (int i : idx) {
            int t = findSlot(par, deadline[i]);
            if (t > 0) {
                count++;
                totalProfit += profit[i];
                par[t] = t - 1;
            }
        }
        return new int[]{count, totalProfit};
    }
}
```

#### Edge Cases & Pitfalls
- **Days are 1-indexed.** The video's dry run books a job on "day 0" and reports 7 jobs / 342. Day 0 doesn't exist, so that job (id 1) can't be scheduled. The correct result for that example is **6 jobs, 322**. Loop `j` down to **1**.
- Sort a list of indices (or job objects), not the profit array alone. Otherwise each profit loses its deadline.
- Use `long long` for the profit sum if values can be large.

#### Key Takeaways
- Greedy on profit, placed at the latest feasible slot.
- "Latest free slot ≤ d" can be sped up with DSU.

[↑ Contents](#contents) · [← Previous](#p225) · [Next →](#p227)

---

<a id="p227"></a>

### 7. N meetings in one room

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Scheduling and Interval Problems | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/n-meetings-in-one-room) | [Watch](https://youtu.be/mKfhTotEguk) |

#### Problem Statement
There is one meeting room and `n` meetings with `start[i]` and `end[i]`. A meeting can begin only **after** the previous one has ended: the next start must be **strictly greater** than the last end. Return the **maximum number of meetings** that can be held. Some versions also ask for their order.

```text
start = [0, 3, 1, 5, 5, 8], end = [5, 4, 2, 9, 7, 9]   ->   4   (meetings 3, 2, 5, 6)
```

#### Intuition
- Following the given order holds only 2 meetings here, because 0–5 blocks everything else.
- **Short and early-ending** meetings leave more room for the rest. Would you rather hold one meeting 0–5, or the two meetings 1–2 and 3–4?
- The greedy rule: **always pick the meeting that ends first** among those that can still be held.

#### Approach: Sort by end time, then sweep (as in the video)
- Store `{start, end, position}` for each meeting, where position is 1-based so the order can be reported.
- Sort by `end` ascending.
- Take the first meeting: `count = 1`, `freeTime = its end`.
- For each next meeting: if `start > freeTime`, take it. Increment `count`, set `freeTime = end`, and record its position.

Dry run:
- Sorted by end: (1,2,#3), (3,4,#2), (0,5,#1), (5,7,#5), (5,9,#4), (8,9,#6).
- Take #3 (free at 2).
- 3 > 2, take #2 (free at 4).
- 0 ≯ 4, skip #1.
- 5 > 4, take #5 (free at 7).
- 5 ≯ 7, skip #4.
- 8 > 7, take #6.
- **4 meetings: order 3, 2, 5, 6.**

**Complexity:**
- Time: O(n) to build the list, O(n log n) to sort and O(n) to sweep, so O(2n + n log n) in total.
- Space: O(3n) for the triples, plus O(n) for the order if it's requested.

**C++**
```cpp
struct Meeting { int start, end, pos; };
int maxMeetings(vector<int>& start, vector<int>& end) {
    int n = start.size();
    vector<Meeting> arr(n);
    for (int i = 0; i < n; i++) arr[i] = {start[i], end[i], i + 1};
    sort(arr.begin(), arr.end(), [](const Meeting& a, const Meeting& b) {
        if (a.end != b.end) return a.end < b.end;
        return a.pos < b.pos;                         // stable tie-break
    });
    int count = 1;
    int freeTime = arr[0].end;
    vector<int> order = {arr[0].pos};                 // order of meetings held
    for (int i = 1; i < n; i++) {
        if (arr[i].start > freeTime) {
            count++;
            freeTime = arr[i].end;
            order.push_back(arr[i].pos);
        }
    }
    return count;                                     // or return `order`
}
```

**Java**
```java
class Solution {
    static int maxMeetings(int[] start, int[] end) {
        int n = start.length;
        int[][] arr = new int[n][3];                  // {start, end, pos}
        for (int i = 0; i < n; i++) arr[i] = new int[]{start[i], end[i], i + 1};
        Arrays.sort(arr, (a, b) -> a[1] != b[1] ? Integer.compare(a[1], b[1]) : Integer.compare(a[2], b[2]));
        int count = 1;
        int freeTime = arr[0][1];
        List<Integer> order = new ArrayList<>();
        order.add(arr[0][2]);
        for (int i = 1; i < n; i++) {
            if (arr[i][0] > freeTime) {
                count++;
                freeTime = arr[i][1];
                order.add(arr[i][2]);
            }
        }
        return count;                                 // or return `order`
    }
}
```

#### Edge Cases & Pitfalls
- **Strict vs non-strict:** this problem (GfG) needs `start > freeTime`. Some variants allow back-to-back meetings (`>=`). Read the statement.
- The comparator must use `<`, not `<=`. `std::sort` needs a strict weak ordering.
- Tie on end time: either choice gives the same count. Breaking ties by position makes the reported order deterministic.

#### Key Takeaways
- Earliest-finish-time-first is optimal for activity selection. An exchange argument shows any optimal schedule can be rewritten to start with the earliest-ending meeting.
- The same idea drives "Non-overlapping Intervals" next.

[↑ Contents](#contents) · [← Previous](#p226) · [Next →](#p228)

---

<a id="p228"></a>

### 8. Non-overlapping Intervals

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Scheduling and Interval Problems | Core | No | [LeetCode](https://leetcode.com/problems/non-overlapping-intervals/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/non-overlapping-intervals) | [Watch](https://youtu.be/HDHQ8lAWakY) |

#### Problem Statement
Given an array of intervals `[start, end]`, return the **minimum number of intervals to remove** so the rest are non-overlapping. In this problem, intervals that only **touch** (`[1,2]` and `[2,3]`) do **not** overlap.

```text
[[1,2], [2,3], [3,4], [1,3]]   ->   1   (remove [1,3])
[[1,2], [1,2], [1,2]]          ->   2
```

#### Intuition — the inverse of "N meetings in one room"
Minimising removals is the same as **maximising how many intervals you can keep** without overlap. The answer is `n − maxKept`. Maximising kept intervals is exactly the meeting-room problem: **sort by end time** and greedily keep every interval that starts at or after the last kept end.

#### Approach: Sort by end, count the keepable intervals
- Sort by `end` ascending.
- Start with `count = 1` and `lastEnd = intervals[0][1]`.
- For each next interval: if `start ≥ lastEnd`, keep it (`count++`, `lastEnd = end`). Use `≥` because touching is allowed here, unlike the strict `>` in N-meetings.
- Return `n − count`.

Dry run on the meeting-style example `(1,2) (3,4) (0,5) (5,7) (7,9) (5,9)`:
- These are already sorted by end.
- Keep (1,2), keep (3,4), skip (0,5), keep (5,7), keep (7,9) because 7 ≥ 7, skip (5,9).
- Kept 4 of 6, so **2 removals**.

**Complexity:** O(n log n + n) time, O(1) extra space.

**C++**
```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n == 0) return 0;
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];                          // earliest end first
    });
    int count = 1;
    int lastEnd = intervals[0][1];
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] >= lastEnd) {            // touching is allowed
            count++;
            lastEnd = intervals[i][1];
        }
    }
    return n - count;
}
```

**Java**
```java
class Solution {
    static int eraseOverlapIntervals(int[][] intervals) {
        int n = intervals.length;
        if (n == 0) return 0;
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[1], b[1]));
        int count = 1;
        int lastEnd = intervals[0][1];
        for (int i = 1; i < n; i++) {
            if (intervals[i][0] >= lastEnd) {
                count++;
                lastEnd = intervals[i][1];
            }
        }
        return n - count;
    }
}
```

#### Edge Cases & Pitfalls
- Sort by **end**, not start. Sorting by start lets one long early interval block many short ones. (A start-sorted variant works only if you drop whichever interval ends later on each conflict.)
- Use `Integer.compare` in Java comparators. `a[1] - b[1]` can overflow when values are near ±2³¹.

#### Key Takeaways
- Min removals = n − max non-overlapping set. Activity selection again.

[↑ Contents](#contents) · [← Previous](#p227) · [Next →](#p229)

---

<a id="p229"></a>

### 9. Insert Interval

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Scheduling and Interval Problems | Core | No | [LeetCode](https://leetcode.com/problems/insert-interval/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/insert-interval) | [Watch](https://youtu.be/xxRE-46OCC8) |

#### Problem Statement
`intervals` is **sorted by start** and **non-overlapping**. Insert `newInterval` so the array stays sorted and non-overlapping, merging wherever needed. Return the result.

```text
intervals = [[1,3],[6,9]],                      new = [2,5]   ->  [[1,5],[6,9]]
intervals = [[1,2],[3,4],[5,7],[8,10],[12,16]], new = [6,8]   ->  [[1,2],[3,4],[5,10],[12,16]]
intervals = [[1,2],[3,4],[7,7]],                new = [5,6]   ->  [[1,2],[3,4],[5,6],[7,7]]
```

#### Intuition — three segments
Because the array is sorted and non-overlapping, it splits cleanly around `newInterval`:
1. **Left:** intervals that **end before** the new one starts (`end < new.start`). Copy them as-is.
2. **Middle:** intervals that **start before or when** the new one ends (`start ≤ new.end`). These overlap it. Absorb each one:
   - `new.start = min(new.start, start)`;
   - `new.end = max(new.end, end)`.

   Then add the merged interval. If nothing overlapped, it's just `newInterval` itself.
3. **Right:** everything else starts after the merged interval ends. Copy it as-is.

For `new = [6,8]`:
- Left: [1,2], [3,4].
- Middle: [5,7] and [8,10] merge into [5,10].
- Right: [12,16].

#### Approach: Single pass with three while-loops (as in the video)
**Complexity:**
- Time: O(n). Each interval is visited once.
- Space: O(n) for the result, which the problem requires anyway.

You can't beat O(n), since every interval has to be copied. Sometimes the straightforward solution is already optimal.

**C++**
```cpp
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    int n = intervals.size(), i = 0;
    // 1. left part: ends before newInterval starts
    while (i < n && intervals[i][1] < newInterval[0]) {
        res.push_back(intervals[i]);
        i++;
    }
    // 2. overlapping part: merge into newInterval
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    res.push_back(newInterval);
    // 3. right part: copy as-is
    while (i < n) {
        res.push_back(intervals[i]);
        i++;
    }
    return res;
}
```

**Java**
```java
class Solution {
    static int[][] insert(int[][] intervals, int[] newInterval) {
        List<int[]> res = new ArrayList<>();
        int n = intervals.length, i = 0;
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.add(intervals[i]);
            i++;
        }
        int s = newInterval[0], e = newInterval[1];
        while (i < n && intervals[i][0] <= e) {
            s = Math.min(s, intervals[i][0]);
            e = Math.max(e, intervals[i][1]);
            i++;
        }
        res.add(new int[]{s, e});
        while (i < n) {
            res.add(intervals[i]);
            i++;
        }
        return res.toArray(new int[0][]);
    }
}
```

#### Edge Cases & Pitfalls
- Empty `intervals`: the result is just `[newInterval]`.
- `newInterval` before all intervals or after all of them: the left part is empty or takes everything, and the code handles both.
- Touching endpoints such as `[1,5]` plus `[5,7]` **merge** here (`start ≤ new.end`). This is the usual LeetCode 57 definition, unlike Non-overlapping Intervals.

#### Key Takeaways
- Sorted, disjoint intervals partition into left, overlapping and right around any new interval. Merging is min of starts and max of ends.

[↑ Contents](#contents) · [← Previous](#p228) · [Next →](#p230)

---

<a id="p230"></a>

### 10. Merge Intervals

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Scheduling and Interval Problems | Core | No | [LeetCode](https://leetcode.com/problems/merge-intervals/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/merge-overlapping-intervals) | [Watch](https://youtu.be/IexN60k62jo) |

> *The sheet links an older video (2JzRBPFYbKE) whose auto-captions are garbled. These notes follow Striver's newer A2Z video for the same problem (IexN60k62jo).*

#### Problem Statement
Given an array of intervals `[start, end]`, merge all overlapping intervals and return the minimal list of non-overlapping intervals covering the same points.

```text
[[1,3],[2,6],[8,10],[15,18]]                          ->  [[1,6],[8,10],[15,18]]
[[1,3],[2,6],[8,9],[9,11],[8,10],[2,4],[15,18],[16,17]] -> [[1,6],[8,11],[15,18]]
```

You can't simply return one giant interval like `[1, 18]`: every point inside a merged interval must be covered by some input interval.

#### Intuition
Overlapping intervals are scattered across the array. **Sort them** by start (ties broken by end), and every interval that could merge with another sits right next to it:
```text
[1,3] [2,4] [2,6] [8,9] [8,10] [9,11] [15,18] [16,17]
```
Two intervals overlap when the next one's **start ≤ the current end**.

#### Approach 1: Brute Force — from each interval, scan forward
- Sort the intervals.
- For each `i`:
  - If `intervals[i]` already lies inside the last merged interval (`end ≤ ans.back().end`), **skip** it.
  - Otherwise start a new interval `[start, end]` and scan `j = i+1 …`:
    - while `intervals[j].start ≤ end`, extend `end = max(end, intervals[j].end)`;
    - break at the first `j` that doesn't overlap. The array is sorted, so nothing later can overlap either.
  - Push `[start, end]`.

**Complexity:**
- Time: O(n log n + 2n). It looks like O(n²), but thanks to the `break` and `continue` every interval is touched about twice.
- Space: O(n) for the answer, e.g. when nothing overlaps.

**C++**
```cpp
vector<vector<int>> mergeBrute(vector<vector<int>>& arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) {
        int start = arr[i][0], end = arr[i][1];
        if (!ans.empty() && end <= ans.back()[1]) continue;   // already merged
        for (int j = i + 1; j < n; j++) {
            if (arr[j][0] <= end) end = max(end, arr[j][1]);
            else break;
        }
        ans.push_back({start, end});
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<int[]> mergeBrute(int[][] arr) {
        int n = arr.length;
        Arrays.sort(arr, (a, b) -> a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]));
        List<int[]> ans = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int start = arr[i][0], end = arr[i][1];
            if (!ans.isEmpty() && end <= ans.get(ans.size() - 1)[1]) continue;
            for (int j = i + 1; j < n; j++) {
                if (arr[j][0] <= end) end = Math.max(end, arr[j][1]);
                else break;
            }
            ans.add(new int[]{start, end});
        }
        return ans;
    }
}
```

#### Approach 2: Optimal — one pass, compare with the last merged interval
After sorting, compare each interval only with the **last interval in `ans`**:
- if `ans` is empty, or `start > ans.back().end`, it starts a **new** interval, so push it;
- otherwise it overlaps, so extend `ans.back().end = max(ans.back().end, end)`.

The `max` matters: `[16,17]` inside `[15,18]` must not shrink the end to 17.

Dry run:
- [1,3]: push.
- [2,4]: 2 ≤ 3, so the last interval becomes [1,4].
- [2,6]: it becomes [1,6].
- [8,9]: 8 > 6, so push.
- [8,10]: it becomes [8,10].
- [9,11]: it becomes [8,11].
- [15,18]: push.
- [16,17]: max(18, 17) = 18, unchanged.
- Result: **[1,6], [8,11], [15,18]**.

**Complexity:** O(n log n + n) time. O(n) space for the output; that's the answer itself, not auxiliary space.

**C++**
```cpp
vector<vector<int>> merge(vector<vector<int>>& arr) {
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;
    for (auto& it : arr) {
        if (ans.empty() || it[0] > ans.back()[1]) ans.push_back(it);   // new interval
        else ans.back()[1] = max(ans.back()[1], it[1]);                 // merge
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[][] merge(int[][] arr) {
        Arrays.sort(arr, (a, b) -> Integer.compare(a[0], b[0]));
        List<int[]> ans = new ArrayList<>();
        for (int[] it : arr) {
            if (ans.isEmpty() || it[0] > ans.get(ans.size() - 1)[1]) ans.add(new int[]{it[0], it[1]});
            else ans.get(ans.size() - 1)[1] = Math.max(ans.get(ans.size() - 1)[1], it[1]);
        }
        return ans.toArray(new int[0][]);
    }
}
```

#### Edge Cases & Pitfalls
- **Touching intervals** (`[1,4]`, `[4,5]`) **merge** into `[1,5]` here, because `start ≤ end`. That's the opposite convention from Non-overlapping Intervals.
- Always take the `max` when extending. A contained interval must not shrink the merged end.
- In Java, copy intervals into `ans` (`new int[]{…}`) if you don't want to mutate the input arrays.

#### Key Takeaways
- Sort by start, then a single pass against the last merged interval.
- This "sort, then compare with `ans.back()`" pattern solves most interval-merge variants.

[↑ Contents](#contents) · [← Previous](#p229) · [Next →](#p231)

---

<a id="p231"></a>

### 11. Minimum number of platforms required for a railway

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Scheduling and Interval Problems | Core | Yes | [LeetCode](https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/minimum-platforms-required-for-a-railway-station) | [Watch](https://youtu.be/AsGzwR_FWok) |

#### Problem Statement
Given the arrival and departure times of `n` trains, find the **minimum number of platforms** so that no train waits.
- A platform can't serve two trains at the same instant.
- A train arriving at the exact time another departs needs a **separate** platform.

```text
arr = [0900, 0945, 0955, 1100, 1500, 1800]
dep = [0920, 1200, 1130, 1150, 1900, 2000]   ->   3
```

#### Intuition
The answer is the **maximum number of trains present at the same instant**. Here the trains of 9:45–12:00, 9:55–11:30 and 11:00–11:50 are all at the station around 11:00, so 3 platforms are needed.

#### Approach 1: Brute Force — count the trains present when each train arrives
The video's brute counts, for every train `i`, the trains whose time ranges **intersect** train i's range. It considers four cases: the other train arrives before or within i's range, and departs within or after it.

Counting pairwise intersections can **over-count**, though *(this note is not in the video)*. Take A = 1–10, B = 1–2 and C = 5–6. A intersects both B and C, giving 3, but B and C are never present together, so only 2 platforms are needed.

A correct O(n²) brute uses the fact that the maximum occupancy occurs **at some arrival instant**. So for every train `i`, count the trains `j` with `arr[j] ≤ arr[i] ≤ dep[j]`, which are exactly the trains standing on platforms when train i pulls in, itself included. Take the maximum.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int findPlatformBrute(vector<int>& arr, vector<int>& dep) {
    int n = arr.size(), maxCount = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;                                   // trains present when train i arrives
        for (int j = 0; j < n; j++)
            if (arr[j] <= arr[i] && arr[i] <= dep[j]) count++;
        maxCount = max(maxCount, count);
    }
    return maxCount;
}
```

**Java**
```java
class Solution {
    static int findPlatformBrute(int[] arr, int[] dep) {
        int n = arr.length, maxCount = 0;
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++)
                if (arr[j] <= arr[i] && arr[i] <= dep[j]) count++;
            maxCount = Math.max(maxCount, count);
        }
        return maxCount;
    }
}
```

#### Approach 2: Optimal — sort the arrivals and departures separately, then sweep
Picture standing outside the station watching the clock. Only the **sequence of events** matters, not which train is which:
- an arrival means `count++`;
- a departure means `count−−`.

So sort `arr` and `dep` **independently**, then merge them with two pointers:
- if `arr[i] ≤ dep[j]`, the next event is an arrival: `count++`, `i++`. The `≤` handles the "same instant needs another platform" rule;
- otherwise the next event is a departure: `count−−`, `j++`.
- Track `maxCount`.
- Stop once all arrivals are processed. After the last arrival, the count can only fall.

Dry run:
- Sorted dep: 920, 1130, 1150, 1200, 1900, 2000.
- Events in order:
  - 900 arr → 1
  - 920 dep → 0
  - 945 arr → 1
  - 955 arr → 2
  - 1100 arr → **3**
  - 1130 dep → 2
  - 1150 dep → 1
  - 1200 dep → 0
  - 1500 arr → 1
  - 1800 arr → 2
- Max = **3**.

**Complexity:** O(2·n log n + 2n) time. O(1) extra space, though the inputs are sorted in place.

**C++**
```cpp
int findPlatform(vector<int>& arr, vector<int>& dep) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());
    int i = 0, j = 0, count = 0, maxCount = 0;
    while (i < n) {
        if (arr[i] <= dep[j]) { count++; i++; }      // an arrival happens first
        else { count--; j++; }                        // a departure happens first
        maxCount = max(maxCount, count);
    }
    return maxCount;
}
```

**Java**
```java
class Solution {
    static int findPlatform(int[] arr, int[] dep) {
        int n = arr.length;
        Arrays.sort(arr);
        Arrays.sort(dep);
        int i = 0, j = 0, count = 0, maxCount = 0;
        while (i < n) {
            if (arr[i] <= dep[j]) { count++; i++; }
            else { count--; j++; }
            maxCount = Math.max(maxCount, count);
        }
        return maxCount;
    }
}
```

#### Edge Cases & Pitfalls
- `≤` vs `<`: with `≤`, a train arriving exactly when another departs takes an extra platform. That's the GfG and LeetCode 2406 convention, where intervals are inclusive. If the problem allows the reuse, change it to `<`.
- If you mustn't mutate the inputs, copy them first, or merge all events into one sorted array, which costs O(n) space.

#### Key Takeaways
- "Maximum simultaneous overlap" means sweeping a line over sorted start and end events.
- The pairing between a train's arrival and its departure doesn't matter for the count.

[↑ Contents](#contents) · [← Previous](#p230) · [Next →](#p232)

---

## Hard

<a id="p232"></a>

### 12. Valid Parenthesis Checker

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Hard | Pro | No | [LeetCode](https://leetcode.com/problems/valid-parenthesis-string/) | [Watch](https://youtu.be/cHT6sG_hUZI) |

#### Problem Statement
A string contains only `'('`, `')'` and `'*'`. Each `'*'` can be treated as `'('`, `')'` or an **empty** string. Return `true` if some choice makes the string a valid parenthesis string: every `'('` has a matching `')'` **after** it.

```text
"()"      ->  true
"(*)"     ->  true    ('*' = empty)
"(*))"    ->  true    ('*' = '(')
"(*()("   ->  false   (the last '(' can never be closed)
```

#### Intuition — the counter check without stars
For a string of only `'('` and `')'`, keep a counter: `+1` for `'('` and `−1` for `')'`.
- If it ever **drops below 0**, some `')'` has no partner, so the string is invalid. Stop at once: `"())("` would otherwise end at 0 and look valid.
- At the end the counter must be **0**.

Stars are the complication, because each one has three choices.

#### Approach 1: Brute Force — try all three choices recursively
`f(i, count)`:
- If `count < 0`, return `false`.
- If `i == n`, return `count == 0`.
- `'('` → `f(i+1, count+1)`.
- `')'` → `f(i+1, count−1)`.
- `'*'` → `f(i+1, count+1) || f(i+1, count−1) || f(i+1, count)`.

**Complexity:** O(3ⁿ) time in the worst case (all stars), O(n) recursion stack.

**C++**
```cpp
bool checkRec(const string& s, int idx, int count) {
    if (count < 0) return false;
    if (idx == (int)s.size()) return count == 0;
    if (s[idx] == '(') return checkRec(s, idx + 1, count + 1);
    if (s[idx] == ')') return checkRec(s, idx + 1, count - 1);
    return checkRec(s, idx + 1, count + 1)          // '*' as '('
        || checkRec(s, idx + 1, count - 1)          // '*' as ')'
        || checkRec(s, idx + 1, count);             // '*' as empty
}
bool checkValidStringBrute(string s) {
    return checkRec(s, 0, 0);
}
```

**Java**
```java
class Solution {
    static boolean checkRec(String s, int idx, int count) {
        if (count < 0) return false;
        if (idx == s.length()) return count == 0;
        char c = s.charAt(idx);
        if (c == '(') return checkRec(s, idx + 1, count + 1);
        if (c == ')') return checkRec(s, idx + 1, count - 1);
        return checkRec(s, idx + 1, count + 1)
            || checkRec(s, idx + 1, count - 1)
            || checkRec(s, idx + 1, count);
    }
    static boolean checkValidStringBrute(String s) {
        return checkRec(s, 0, 0);
    }
}
```

#### Approach 2: Better — memoize on (index, count)
The recursion has only two changing parameters: `index` in `0…n` and `count` in `0…n`. Cache the results in a `dp[n][n+1]` table. The video mentions this step but leaves the code to the Dynamic Programming section; the code below is added for completeness.

**Complexity:** O(n²) time, O(n²) space plus the O(n) stack.

**C++**
```cpp
bool checkMemo(const string& s, int idx, int count, vector<vector<int>>& dp) {
    if (count < 0) return false;
    if (idx == (int)s.size()) return count == 0;
    if (dp[idx][count] != -1) return dp[idx][count];
    bool ans;
    if (s[idx] == '(') ans = checkMemo(s, idx + 1, count + 1, dp);
    else if (s[idx] == ')') ans = checkMemo(s, idx + 1, count - 1, dp);
    else ans = checkMemo(s, idx + 1, count + 1, dp)
            || checkMemo(s, idx + 1, count - 1, dp)
            || checkMemo(s, idx + 1, count, dp);
    return dp[idx][count] = ans;
}
bool checkValidStringMemo(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return checkMemo(s, 0, 0, dp);
}
```

**Java**
```java
class Solution {
    static boolean checkMemo(String s, int idx, int count, int[][] dp) {
        if (count < 0) return false;
        if (idx == s.length()) return count == 0;
        if (dp[idx][count] != -1) return dp[idx][count] == 1;
        char c = s.charAt(idx);
        boolean ans;
        if (c == '(') ans = checkMemo(s, idx + 1, count + 1, dp);
        else if (c == ')') ans = checkMemo(s, idx + 1, count - 1, dp);
        else ans = checkMemo(s, idx + 1, count + 1, dp)
                || checkMemo(s, idx + 1, count - 1, dp)
                || checkMemo(s, idx + 1, count, dp);
        dp[idx][count] = ans ? 1 : 0;
        return ans;
    }
    static boolean checkValidStringMemo(String s) {
        int n = s.length();
        int[][] dp = new int[n][n + 1];
        for (int[] row : dp) Arrays.fill(row, -1);
        return checkMemo(s, 0, 0, dp);
    }
}
```

#### Approach 3: Optimal — track the range of possible counts `[mn, mx]`
- **The range idea.** Instead of a single count, keep the **range** of counts that some choice of stars can produce. Every value in between is also reachable.
- **Updates per character:**
  - `'('`: `mn++`, `mx++`.
  - `')'`: `mn--`, `mx--`.
  - `'*'`: `mn--` (star as `')'`) and `mx++` (star as `'('`). Treating the star as empty is covered by the values in between.
- **Pruning negative counts.**
  - If `mn < 0`, clamp it to `0`. Negative counts are invalid paths, so we just discard them.
  - If **`mx < 0`**, even the most optimistic path has too many `')'`, so return `false`. For example, a string starting with `')'`.
- **At the end:** valid iff `mn == 0`, i.e. a count of 0 is still reachable.

Dry run `"(*()("`:

| char | ( | * | ( | ) | ( |
|---|---|---|---|---|---|
| [mn, mx] | [1,1] | [0,2] | [1,3] | [0,2] | [1,3] |

The final `mn` is 1, not 0, so the answer is **false**.

Dry run `"()*)*()"`: [1,1] → [0,0] → [0,1] → [0,0] → [0,1] → [1,2] → [0,1]. The final `mn` is 0, so the answer is **true**.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
bool checkValidString(string s) {
    int mn = 0, mx = 0;
    for (char c : s) {
        if (c == '(') { mn++; mx++; }
        else if (c == ')') { mn--; mx--; }
        else { mn--; mx++; }                 // '*'
        if (mn < 0) mn = 0;                  // drop invalid (negative) counts
        if (mx < 0) return false;            // no valid count left at all
    }
    return mn == 0;
}
```

**Java**
```java
class Solution {
    static boolean checkValidString(String s) {
        int mn = 0, mx = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') { mn++; mx++; }
            else if (c == ')') { mn--; mx--; }
            else { mn--; mx++; }
            if (mn < 0) mn = 0;
            if (mx < 0) return false;
        }
        return mn == 0;
    }
}
```

#### Edge Cases & Pitfalls
- Check `mx < 0` **inside** the loop. Clamping `mn` alone would accept `")("`.
- For `')'` the update is `mx−−`. The video's on-screen pseudocode briefly shows `max + 1` there, which is a typo.
- The empty string is valid.

#### Key Takeaways
- When a choice multiplies the states (here, 3 per star) but the states are just a contiguous range of integers, track the range `[min, max]` instead of every state. That turns exponential into O(n).
- In an interview, present the recursion first (try all ways), then the DP, then the range compression.

[↑ Contents](#contents) · [← Previous](#p231) · [Next →](#p233)

---

<a id="p233"></a>

### 13. Candy

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Hard | Pro | No | [LeetCode](https://leetcode.com/problems/candy/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/candy-distribution-problem) | [Watch](https://youtu.be/IIqVFvKE6RY) |

#### Problem Statement
`n` children stand in a line, each with a rating. Hand out candies so that:
1. every child gets **at least one** candy;
2. a child with a **higher rating than a neighbour** gets **more candies than that neighbour**.

Return the **minimum total** number of candies.

```text
ratings = [1, 3, 2, 1]                                ->  7    (candies 1, 3, 2, 1)
ratings = [1, 2, 3]                                   ->  6    (1, 2, 3)
ratings = [0, 2, 4, 7, 6, 5, 4, 3, 2, 1, 1, 1, 2, 3, 4, 2, 1, 1, 1] -> 50
```

#### Intuition
- **Split the rule into two independent constraints.** Rule 2 is really "more than the left neighbour if rated higher" plus "more than the right neighbour if rated higher".
  - Left pass: `left[i] = left[i−1] + 1` if `r[i] > r[i−1]`, else `1`. That is the greedy minimum.
  - Right pass: `right[i] = right[i+1] + 1` if `r[i] > r[i+1]`, else `1`.
- **Combine them.** A child must satisfy both, so give `max(left[i], right[i])`. Taking the max can't break the other side, because it only ever raises a value.

For `[1, 3, 2, 1]`: left = [1,2,1,1], right = [1,3,2,1], max = [1,3,2,1], which sums to 7.

#### Approach 1: Brute Force — two arrays
**Complexity:** O(3n) time, O(2n) space.

**C++**
```cpp
int candyBrute(vector<int>& r) {
    int n = r.size();
    vector<int> left(n), right(n);
    left[0] = 1;
    for (int i = 1; i < n; i++)
        left[i] = (r[i] > r[i - 1]) ? left[i - 1] + 1 : 1;
    right[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
        right[i] = (r[i] > r[i + 1]) ? right[i + 1] + 1 : 1;
    int sum = 0;
    for (int i = 0; i < n; i++) sum += max(left[i], right[i]);
    return sum;
}
```

**Java**
```java
class Solution {
    static int candyBrute(int[] r) {
        int n = r.length;
        int[] left = new int[n], right = new int[n];
        left[0] = 1;
        for (int i = 1; i < n; i++)
            left[i] = (r[i] > r[i - 1]) ? left[i - 1] + 1 : 1;
        right[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--)
            right[i] = (r[i] > r[i + 1]) ? right[i + 1] + 1 : 1;
        int sum = 0;
        for (int i = 0; i < n; i++) sum += Math.max(left[i], right[i]);
        return sum;
    }
}
```

#### Approach 2: Better — drop the right array
Only the **sum** is needed, not the distribution. So compute the right-pass values on the fly while walking backwards:
- `cur` is the right-pass value at index i, and `right` is the value at i + 1.
- If `r[i] > r[i+1]`, set `cur = right + 1`; otherwise set `cur = 1`.
- Then `right = cur` and `sum += max(left[i], cur)`.

The last child gets `max(1, left[n−1])`, so start `sum` from that.

**Complexity:** O(2n) time, O(n) space.

**C++**
```cpp
int candyBetter(vector<int>& r) {
    int n = r.size();
    vector<int> left(n);
    left[0] = 1;
    for (int i = 1; i < n; i++)
        left[i] = (r[i] > r[i - 1]) ? left[i - 1] + 1 : 1;
    int cur = 1, right = 1;
    int sum = max(1, left[n - 1]);               // last child
    for (int i = n - 2; i >= 0; i--) {
        cur = (r[i] > r[i + 1]) ? right + 1 : 1;
        right = cur;
        sum += max(left[i], cur);
    }
    return sum;
}
```

**Java**
```java
class Solution {
    static int candyBetter(int[] r) {
        int n = r.length;
        int[] left = new int[n];
        left[0] = 1;
        for (int i = 1; i < n; i++)
            left[i] = (r[i] > r[i - 1]) ? left[i - 1] + 1 : 1;
        int cur = 1, right = 1;
        int sum = Math.max(1, left[n - 1]);
        for (int i = n - 2; i >= 0; i--) {
            cur = (r[i] > r[i + 1]) ? right + 1 : 1;
            right = cur;
            sum += Math.max(left[i], cur);
        }
        return sum;
    }
}
```

#### Approach 3: Optimal — slope counting, O(1) space
The video's disclaimer: this one has to be known beforehand. Picture the ratings as a mountain range of **increasing slopes**, **decreasing slopes** and **flats**:
- **Flat** (`r[i] == r[i−1]`): neither neighbour constrains the child, so give 1. `sum += 1`.
- **Increasing slope:** give 2, 3, 4, … in order. Track `peak`, the value given to the top.
- **Decreasing slope:** the true distribution would be …, 3, 2, 1. But only the **sum** matters, and 1 + 2 + … + k is the same added in either order. So add 1, 2, 3, … while walking down, with `down` counting up.
- **Fix the peak.** The top must exceed both sides. It already counted `peak`, but the descent needs it to be `down` (one more than the descent's largest value). If `down > peak`, add the difference `down − peak`.

Example `0 2 4 7 6 5 4 3 2 1 1 1 2 3 4 2 1 1 1`:

| segment | adds | running sum |
|---|---|---|
| first child (0) | 1 | 1 |
| ascent 2, 4, 7 | 2 + 3 + 4 (peak = 4) | 10 |
| descent 6 … 1 (six children) | 1 + … + 6 = 21, `down` ends at 7 | 31 |
| peak fix: 7 > 4 | + 3, so the 7-rated child counts as 7 | 34 |
| flats 1, 1 | + 1 + 1 | 36 |
| ascent 2, 3, 4 | 2 + 3 + 4 (peak = 4) | 45 |
| descent 2, 1 | 1 + 2, `down` ends at 3 < 4, so no fix | 48 |
| flats 1, 1 | + 1 + 1 | **50** |

**Complexity:** O(n) time. The inner loops only advance `i`. O(1) space.

**C++**
```cpp
int candy(vector<int>& r) {
    int n = r.size();
    int sum = 1, i = 1;                          // child 0 gets 1
    while (i < n) {
        if (r[i] == r[i - 1]) {                  // flat: gets 1
            sum += 1;
            i++;
            continue;
        }
        int peak = 1;
        while (i < n && r[i] > r[i - 1]) {       // increasing slope
            peak++;
            sum += peak;
            i++;
        }
        int down = 1;
        while (i < n && r[i] < r[i - 1]) {       // decreasing slope
            sum += down;
            i++;
            down++;
        }
        if (down > peak) sum += down - peak;     // peak must beat the descent
    }
    return sum;
}
```

**Java**
```java
class Solution {
    static int candy(int[] r) {
        int n = r.length;
        int sum = 1, i = 1;
        while (i < n) {
            if (r[i] == r[i - 1]) {
                sum += 1;
                i++;
                continue;
            }
            int peak = 1;
            while (i < n && r[i] > r[i - 1]) {
                peak++;
                sum += peak;
                i++;
            }
            int down = 1;
            while (i < n && r[i] < r[i - 1]) {
                sum += down;
                i++;
                down++;
            }
            if (down > peak) sum += down - peak;
        }
        return sum;
    }
}
```

#### Edge Cases & Pitfalls
- **Equal neighbours impose nothing.** `[1,2,2]` gives 1 + 2 + 1 = 4; the second 2 doesn't need more than the first.
- **Starting downhill works too.** For `[3,2,1]`, the ascent loop doesn't run (peak = 1). The descent adds 1 + 2 and `down` becomes 3. The fix adds 3 − 1 = 2, for a total of 1 + 1 + 2 + 2 = 6 = 3 + 2 + 1.
- A single child needs 1 candy.

#### Key Takeaways
- Two-directional constraints: satisfy each direction separately with a greedy pass, then take the max.
- The slope trick works because the problem asks for a **sum**: each descent can be counted bottom-up, with a correction at the peak.

[↑ Contents](#contents) · [← Previous](#p232) · [Next →](#p234)

---

<a id="p234"></a>

### 14. Jump Game II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Greedy Algorithms › Hard | Pro | No | [LeetCode](https://leetcode.com/problems/jump-game-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/jump-game-ii-minimum-jumps) | [Watch](https://youtu.be/7SBVnw7GSTk) |

#### Problem Statement
Start at index 0. `nums[i]` is the **maximum** jump length from index `i`. Return the **minimum number of jumps** to reach the last index. Reaching it is guaranteed.

```text
nums = [2, 3, 1, 4, 1, 1, 1, 2]   ->   3   (0 -> 1 -> 3 -> 7)
nums = [2, 3, 1, 1, 4]            ->   2   (0 -> 1 -> 4)
```

#### Approach 1: Brute Force — recursion over every jump length
`f(index, jumps)`:
- If `index ≥ n−1`, the end is reached, so return `jumps`.
- Otherwise return the minimum over `i = 1 … nums[index]` of `f(index + i, jumps + 1)`. Start `i` at 1, because a jump of 0 goes nowhere.

**Complexity:** exponential, roughly O(nⁿ) in the worst case. O(n) recursion stack.

**C++**
```cpp
int jumpRec(vector<int>& nums, int index, int jumps) {
    int n = nums.size();
    if (index >= n - 1) return jumps;
    int mini = INT_MAX;
    for (int i = 1; i <= nums[index]; i++)
        mini = min(mini, jumpRec(nums, index + i, jumps + 1));
    return mini;
}
int jumpBrute(vector<int>& nums) {
    return jumpRec(nums, 0, 0);
}
```

**Java**
```java
class Solution {
    static int jumpRec(int[] nums, int index, int jumps) {
        int n = nums.length;
        if (index >= n - 1) return jumps;
        int mini = Integer.MAX_VALUE;
        for (int i = 1; i <= nums[index]; i++)
            mini = Math.min(mini, jumpRec(nums, index + i, jumps + 1));
        return mini;
    }
    static int jumpBrute(int[] nums) {
        return jumpRec(nums, 0, 0);
    }
}
```

#### Approach 2: Better — memoization
- **The video's version.** It memoizes on `(index, jumps)` with a `dp[n][n]` table, which gives O(n²) time and O(n²) space.
- **A simpler state** *(not in video)*. The future doesn't depend on the jumps already taken, so memoize **`g(index)` = minimum jumps from `index` to the end**:

  `g(i) = 0` if `i ≥ n−1`, else `1 + min over 1 ≤ k ≤ nums[i] of g(i+k)`.

  This is still O(n²) time, but only O(n) space.

**C++**
```cpp
int jumpMemoRec(vector<int>& nums, int index, vector<int>& dp) {
    int n = nums.size();
    if (index >= n - 1) return 0;
    if (dp[index] != -1) return dp[index];
    int mini = INT_MAX;
    for (int k = 1; k <= nums[index]; k++) {
        int sub = jumpMemoRec(nums, index + k, dp);
        if (sub != INT_MAX) mini = min(mini, 1 + sub);
    }
    return dp[index] = mini;                      // INT_MAX = unreachable from here
}
int jumpMemo(vector<int>& nums) {
    vector<int> dp(nums.size(), -1);
    return jumpMemoRec(nums, 0, dp);
}
```

**Java**
```java
class Solution {
    static int jumpMemoRec(int[] nums, int index, int[] dp) {
        int n = nums.length;
        if (index >= n - 1) return 0;
        if (dp[index] != -1) return dp[index];
        int mini = Integer.MAX_VALUE;
        for (int k = 1; k <= nums[index]; k++) {
            int sub = jumpMemoRec(nums, index + k, dp);
            if (sub != Integer.MAX_VALUE) mini = Math.min(mini, 1 + sub);
        }
        return dp[index] = mini;
    }
    static int jumpMemo(int[] nums) {
        int[] dp = new int[nums.length];
        Arrays.fill(dp, -1);
        return jumpMemoRec(nums, 0, dp);
    }
}
```

#### Approach 3: Optimal — greedy BFS by ranges
Instead of branching recursively, track the **range of indices reachable with exactly `jumps` jumps**. The same trick, replacing branches with a range, was used in Valid Parenthesis String.
- Start with `jumps = 0` and range `[l, r] = [0, 0]`.
- While `r < n − 1`:
  - `farthest = max(i + nums[i])` over all `i` in `[l, r]`;
  - the next range is `[r + 1, farthest]`;
  - `jumps++`.
- When the range reaches or passes the last index, `jumps` is the answer.

It's greedy because each level reaches **as far as possible**. Every index in the new range is reachable in `jumps` steps, and none of them sooner.

Dry run on `[2,3,1,4,1,1,1,2]`:
- [0,0] → farthest 2, range [1,2], jumps 1.
- From index 1, 1 + 3 = 4; from index 2, 2 + 1 = 3. Range [3,4], jumps 2.
- From index 3, 3 + 4 = 7, which is ≥ 7. Range [5,7], jumps **3**.

**Complexity:** O(n) time. Each index is scanned in exactly one range, despite the nested loops. O(1) space.

**C++**
```cpp
int jump(vector<int>& nums) {
    int n = nums.size();
    int jumps = 0, l = 0, r = 0;
    while (r < n - 1) {
        int farthest = 0;
        for (int i = l; i <= r; i++)
            farthest = max(farthest, i + nums[i]);
        l = r + 1;
        r = farthest;
        jumps++;
    }
    return jumps;
}
```

**Java**
```java
class Solution {
    static int jump(int[] nums) {
        int n = nums.length;
        int jumps = 0, l = 0, r = 0;
        while (r < n - 1) {
            int farthest = 0;
            for (int i = l; i <= r; i++)
                farthest = Math.max(farthest, i + nums[i]);
            l = r + 1;
            r = farthest;
            jumps++;
        }
        return jumps;
    }
}
```

#### Edge Cases & Pitfalls
- `n == 1` gives 0 jumps, because the loop never runs.
- The greedy relies on the guarantee that the end is reachable. Otherwise `farthest` could stay ≤ `r` and the loop would never end. Add `if (farthest <= r) return -1;` for the general case.
- In the recursion, start the jump length at 1, never 0, or it recurses forever.

#### Key Takeaways
- Jump Game I asks "can I reach?" (track the max reach). Jump Game II asks "in how few jumps?" (a BFS over ranges of equal jump count).
- A recursion that explores contiguous choices can often be compressed into a range, an idea that recurs throughout this sheet.

[↑ Contents](#contents) · [← Previous](#p233)

---
