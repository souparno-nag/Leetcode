# Sliding Window / 2 Pointer — Striver's A2Z DSA Sheet Notes

Section 11 of 20 · 12 problems · 11 with video, 1 without · [All sections](00-index.md)

[← Greedy Algorithms](10-greedy-algorithms.md) | [Stack / Queues →](12-stack-queues.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Constant Window**

1. [Maximum Points You Can Obtain from Cards](#p235) — Core

**Longest and Smallest Window Problems**

2. [Longest Substring Without Repeating Characters](#p236) — Core
3. [Max Consecutive Ones III](#p237) — Core
4. [Fruit Into Baskets](#p238) — Core
5. [Longest Substring With At Most K Distinct Characters](#p239) — Pro
6. [Longest Repeating Character Replacement](#p240) — Pro
7. [Minimum Window Substring](#p241) — Pro
8. [Minimum Window Subsequence](#p242) — Pro · *no video*

**Counting Subarrays / Substrings Problems**

9. [Number of Substrings Containing All Three Characters](#p243) — Core
10. [Binary Subarrays With Sum](#p244) — Core
11. [Count number of Nice subarrays](#p245) — Pro
12. [Subarrays with K Different Integers](#p246) — Pro

---

## Constant Window

<a id="p235"></a>

### 1. Maximum Points You Can Obtain from Cards

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Constant Window | Core | No | [LeetCode](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/maximum-points-you-can-obtain-from-cards) | [Watch](https://youtu.be/pBWCOCS636U) |

#### Problem Statement
`cardPoints` holds the points of `n` cards in a row. In each of `k` steps you take one card from either the **front** or the **back**. Cards are taken consecutively: you can never pick from the middle. Maximise the total points.

```text
cardPoints = [6, 2, 3, 4, 7, 2, 1, 7, 1], k = 4   ->   16   (6 + 2 from the front, 1 + 7 from the back)
cardPoints = [1, 2, 3, 4, 5, 6, 1],       k = 3   ->   12
```

#### Intuition
Any valid pick is "`i` cards from the front + `k − i` cards from the back" for some `i` in 0…k. There are only `k + 1` configurations. The video lists them in this order:
- all `k` from the front;
- `k−1` from the front and 1 from the back;
- …;
- all `k` from the back.

#### Approach 1: Brute Force — recompute each configuration
For each `i`, sum the first `i` cards plus the last `k − i` cards from scratch.

**Complexity:** O(k²) time, O(1) space.

**C++**
```cpp
int maxScoreBrute(vector<int>& cardPoints, int k) {
    int n = cardPoints.size(), best = 0;
    for (int i = 0; i <= k; i++) {                 // i from front, k - i from back
        int sum = 0;
        for (int j = 0; j < i; j++) sum += cardPoints[j];
        for (int j = 0; j < k - i; j++) sum += cardPoints[n - 1 - j];
        best = max(best, sum);
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int maxScoreBrute(int[] cardPoints, int k) {
        int n = cardPoints.length, best = 0;
        for (int i = 0; i <= k; i++) {
            int sum = 0;
            for (int j = 0; j < i; j++) sum += cardPoints[j];
            for (int j = 0; j < k - i; j++) sum += cardPoints[n - 1 - j];
            best = Math.max(best, sum);
        }
        return best;
    }
}
```

#### Approach 2: Optimal — slide the window from front to back (as in the video)
Adjacent configurations differ by just **one card leaving the front and one card joining from the back**:
- `leftSum` starts as the sum of the first `k` cards. `rightSum = 0`, and `maxSum = leftSum`.
- For `i = k−1` down to `0`:
  - `leftSum −= nums[i]`;
  - `rightSum += nums[rightIndex]`, with `rightIndex` starting at `n − 1` and moving left;
  - `maxSum = max(maxSum, leftSum + rightSum)`.

Dry run, `k = 4`:

| front cards | back cards | left + right |
|---|---|---|
| 6 2 3 4 | — | 15 + 0 = 15 |
| 6 2 3 | 1 | 11 + 1 = 12 |
| 6 2 | 7 1 | 8 + 8 = **16** |
| 6 | 1 7 1 | 6 + 9 = 15 |
| — | 2 1 7 1 | 0 + 11 = 11 |

**Complexity:** O(2k) time, O(1) space. The video recommends this over prefix-sum solutions because it's clean and easy to explain.

**C++**
```cpp
int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int leftSum = 0, rightSum = 0;
    for (int i = 0; i < k; i++) leftSum += cardPoints[i];
    int maxSum = leftSum;
    int rightIndex = n - 1;
    for (int i = k - 1; i >= 0; i--) {
        leftSum -= cardPoints[i];                   // drop one card from the front
        rightSum += cardPoints[rightIndex];         // take one more from the back
        rightIndex--;
        maxSum = max(maxSum, leftSum + rightSum);
    }
    return maxSum;
}
```

**Java**
```java
class Solution {
    static int maxScore(int[] cardPoints, int k) {
        int n = cardPoints.length;
        int leftSum = 0, rightSum = 0;
        for (int i = 0; i < k; i++) leftSum += cardPoints[i];
        int maxSum = leftSum;
        int rightIndex = n - 1;
        for (int i = k - 1; i >= 0; i--) {
            leftSum -= cardPoints[i];
            rightSum += cardPoints[rightIndex];
            rightIndex--;
            maxSum = Math.max(maxSum, leftSum + rightSum);
        }
        return maxSum;
    }
}
```

#### Edge Cases & Pitfalls
- `k == n`: take everything. The loop still works; every configuration has the same sum.
- An equivalent view *(not in video)*: you leave behind a **contiguous middle window of size n − k**, so the answer is the total minus the minimum-sum window of size `n − k`.

#### Key Takeaways
- This is a constant-size window that wraps around the ends.
- Update the sums incrementally (remove one, add one) instead of recomputing them.

[↑ Contents](#contents) · [Next →](#p236)

---

## Longest and Smallest Window Problems

<a id="p236"></a>

### 2. Longest Substring Without Repeating Characters

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Longest and Smallest Window Problems | Core | No | [LeetCode](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/longest-substring-without-repeating-characters) | [Watch](https://youtu.be/-zSxTJkcdAo) |

#### Problem Statement
Given a string `s`, which may contain any of the 256 ASCII characters, return the length of the **longest substring without repeating characters**. A substring is a contiguous block of the string.

```text
s = "cadbzabcd"  ->  5   ("cadbz" or "zabcd")
s = "bbbbb"      ->  1
s = "pwwkew"     ->  3   ("wke")
```

#### Approach 1: Brute Force — all substrings with an early break
- Fix the start `i`, then extend the end `j` to the right, marking each character in a 256-sized `hash`.
- The moment `s[j]` was already seen, **break**. Any longer substring from `i` contains the repeat too.
- Otherwise update `maxLen = max(maxLen, j − i + 1)`.

**Complexity:** O(n²) time, O(256) space. The hash is reset for every `i`.

**C++**
```cpp
int lengthOfLongestSubstringBrute(string s) {
    int n = s.size(), maxLen = 0;
    for (int i = 0; i < n; i++) {
        int hash[256] = {0};
        for (int j = i; j < n; j++) {
            if (hash[(unsigned char)s[j]] == 1) break;   // repeat found
            maxLen = max(maxLen, j - i + 1);
            hash[(unsigned char)s[j]] = 1;
        }
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int lengthOfLongestSubstringBrute(String s) {
        int n = s.length(), maxLen = 0;
        for (int i = 0; i < n; i++) {
            int[] hash = new int[256];
            for (int j = i; j < n; j++) {
                if (hash[s.charAt(j)] == 1) break;
                maxLen = Math.max(maxLen, j - i + 1);
                hash[s.charAt(j)] = 1;
            }
        }
        return maxLen;
    }
}
```

#### Approach 2: Optimal — sliding window with "last seen index"
"Longest substring with a property" is the signal for a **two-pointer / sliding window** technique. That isn't one fixed algorithm: the window changes with each problem's rule. The window `[l, r]` is the current candidate.
- `hash[c]` = the index where character `c` was **last seen**, initially −1.
- Expand `r` one step at a time. If `s[r]` was seen **inside the window** (`hash[s[r]] ≥ l`), jump `l = hash[s[r]] + 1`, just past the previous occurrence.
- Then `maxLen = max(maxLen, r − l + 1)`, and set `hash[s[r]] = r`.

Why check `≥ l`? The map remembers characters that have already **left** the window. In `"cadbzabcd"`, when `r` reaches the second `c` (index 7) the window is `[4..6]` = `"zab"`. The old `c` at index 0 is outside the window, so it must not move `l` backwards or count as a repeat.

Dry run on `"cadbzabcd"`:
- r = 0…4 (`cadbz`): no repeats, so the length grows to **5**.
- r = 5 (`a`, last seen at 1 ≥ l = 0): l = 2, window `dbza`, length 4.
- r = 6 (`b`, last seen at 3 ≥ 2): l = 4, window `zab`, length 3.
- r = 7 (`c`, last seen at 0 < 4): ignore it, window `zabc`, length 4.
- r = 8 (`d`, last seen at 2 < 4): window `zabcd`, length 5.
- Answer: **5**.

**Complexity:** O(n) time, because `r` moves exactly n times and each step is O(1) with an array instead of a map. O(256) space.

**C++**
```cpp
int lengthOfLongestSubstring(string s) {
    vector<int> hash(256, -1);                    // last index of each character
    int n = s.size(), l = 0, r = 0, maxLen = 0;
    while (r < n) {
        unsigned char c = s[r];
        if (hash[c] != -1 && hash[c] >= l)        // repeat inside the window
            l = hash[c] + 1;
        maxLen = max(maxLen, r - l + 1);
        hash[c] = r;
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int lengthOfLongestSubstring(String s) {
        int[] hash = new int[256];
        Arrays.fill(hash, -1);
        int n = s.length(), l = 0, r = 0, maxLen = 0;
        while (r < n) {
            char c = s.charAt(r);
            if (hash[c] != -1 && hash[c] >= l)
                l = hash[c] + 1;
            maxLen = Math.max(maxLen, r - l + 1);
            hash[c] = r;
            r++;
        }
        return maxLen;
    }
}
```

#### Edge Cases & Pitfalls
- Forgetting `hash[c] ≥ l` moves `l` **backwards** on stale entries and gives wrong, too-long answers. Example: `"abba"`.
- In C++, index the array with `unsigned char`. A plain `char` can be negative for bytes above 127.
- An empty string gives 0.

#### Key Takeaways
- The sliding-window template: expand `r`, shrink or jump `l` until the window is valid, then record the answer.
- Storing **last indices** lets `l` jump straight to the right place instead of crawling.

[↑ Contents](#contents) · [← Previous](#p235) · [Next →](#p237)

---

<a id="p237"></a>

### 3. Max Consecutive Ones III

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Longest and Smallest Window Problems | Core | Yes | [LeetCode](https://leetcode.com/problems/max-consecutive-ones-iii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/max-consecutive-ones-iii) | [Watch](https://youtu.be/3E4JBHSLpYk) |

#### Problem Statement
Given a binary array `nums` and an integer `k`, return the maximum number of consecutive 1s if you may flip **at most** `k` zeros.

```text
nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2                   ->  6
nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3   ->  10
```

#### Intuition — reframe the question
Flipping at most `k` zeros and maximising consecutive ones is the same as finding the **longest subarray containing at most `k` zeros**. Flip exactly those zeros and the whole subarray becomes ones. No actual flipping is needed.

#### Approach 1: Brute Force — all subarrays with an early break
- Fix `i` and extend `j`, counting the zeros as you go.
- Once `zeros > k`, **break**. Every longer subarray from `i` has even more zeros.
- Otherwise update `maxLen = max(maxLen, j − i + 1)`.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int longestOnesBrute(vector<int>& nums, int k) {
    int n = nums.size(), maxLen = 0;
    for (int i = 0; i < n; i++) {
        int zeros = 0;
        for (int j = i; j < n; j++) {
            if (nums[j] == 0) zeros++;
            if (zeros <= k) maxLen = max(maxLen, j - i + 1);
            else break;
        }
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int longestOnesBrute(int[] nums, int k) {
        int n = nums.length, maxLen = 0;
        for (int i = 0; i < n; i++) {
            int zeros = 0;
            for (int j = i; j < n; j++) {
                if (nums[j] == 0) zeros++;
                if (zeros <= k) maxLen = Math.max(maxLen, j - i + 1);
                else break;
            }
        }
        return maxLen;
    }
}
```

#### Approach 2: Better — sliding window that shrinks fully
Window `[l, r]`, counting `zeros` inside it:
- Expand `r`. If `nums[r] == 0`, `zeros++`.
- **While** `zeros > k`: if `nums[l] == 0`, `zeros−−`; then `l++`. This shrinks the window until it's valid again.
- Update `maxLen = max(maxLen, r − l + 1)`.

**Complexity:** O(2n) time. `r` and `l` each move at most n times in total, so the inner loop isn't n per step. O(1) space.

**C++**
```cpp
int longestOnesBetter(vector<int>& nums, int k) {
    int n = nums.size(), l = 0, r = 0, zeros = 0, maxLen = 0;
    while (r < n) {
        if (nums[r] == 0) zeros++;
        while (zeros > k) {                      // shrink until valid
            if (nums[l] == 0) zeros--;
            l++;
        }
        maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int longestOnesBetter(int[] nums, int k) {
        int n = nums.length, l = 0, r = 0, zeros = 0, maxLen = 0;
        while (r < n) {
            if (nums[r] == 0) zeros++;
            while (zeros > k) {
                if (nums[l] == 0) zeros--;
                l++;
            }
            maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Approach 3: Optimal — the window never shrinks (`while` becomes `if`)
- **Only growth matters.** Once a window of length `maxLen` has been found, shorter windows are useless. So when the window becomes invalid, **don't shrink it fully**: move `l` by **one** step, together with `r`.
- **The window slides at constant size.** It keeps its best-so-far length while invalid, and only **grows** again when it slides into a position with `≤ k` zeros.
- **Record only valid windows.** `maxLen` is updated only when `zeros ≤ k`.

Why it's correct: the window length never decreases, and every time it is valid it's an achievable answer. Shrinking further could only give windows shorter than `maxLen`, which can't improve the answer.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int longestOnes(vector<int>& nums, int k) {
    int n = nums.size(), l = 0, r = 0, zeros = 0, maxLen = 0;
    while (r < n) {
        if (nums[r] == 0) zeros++;
        if (zeros > k) {                         // slide instead of shrinking
            if (nums[l] == 0) zeros--;
            l++;
        }
        if (zeros <= k) maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int longestOnes(int[] nums, int k) {
        int n = nums.length, l = 0, r = 0, zeros = 0, maxLen = 0;
        while (r < n) {
            if (nums[r] == 0) zeros++;
            if (zeros > k) {
                if (nums[l] == 0) zeros--;
                l++;
            }
            if (zeros <= k) maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Edge Cases & Pitfalls
- `k = 0` reduces to the plain longest run of ones.
- `k ≥` the number of zeros makes the answer `n`.
- Write `zeros += (nums[r] == 0)`, not tricks like `zeros += !nums[r]`. Interviewers prefer readable code, as the video says.

#### Key Takeaways
- "Longest subarray where a count stays ≤ k" is a sliding window.
- The `while → if` trick turns O(2n) into O(n) whenever only the **maximum length** is needed. The same template powers the next several problems.

[↑ Contents](#contents) · [← Previous](#p236) · [Next →](#p238)

---

<a id="p238"></a>

### 4. Fruit Into Baskets

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Longest and Smallest Window Problems | Core | No | [LeetCode](https://leetcode.com/problems/fruit-into-baskets/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/fruit-into-baskets) | [Watch](https://youtu.be/e3bs0uA1NhQ) |

#### Problem Statement
Trees stand in a row, and `fruits[i]` is the **type** of fruit tree `i` produces. You have **two baskets**, and each basket holds only **one type**, in any quantity. You start at any tree and pick exactly one fruit from every tree moving right. You **can't skip** a tree, and you stop when a fruit fits neither basket. Return the maximum number of fruits you can pick.

```text
fruits = [3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4]   ->   5   ([1, 2, 1, 1, 2])
fruits = [1, 2, 1]                            ->   3
fruits = [0, 1, 2, 2]                         ->   3
```

#### Intuition — reframe the question
This is the **longest subarray with at most 2 distinct numbers**. "At most" because a run of a single type, like all 3s, fits in one basket with the other left empty. It's the same template as Max Consecutive Ones III, with "zeros ≤ k" replaced by "distinct ≤ 2".

#### Approach 1: Brute Force — all subarrays with a set
- For each start `i`, extend `j` and insert `fruits[j]` into a set.
- If `set.size() > 2`, **break**.
- Otherwise update `maxLen = max(maxLen, j − i + 1)`.

**Complexity:** O(n²) time. The set never holds more than 3 elements, so its log factor is constant. O(3) space.

**C++**
```cpp
int totalFruitBrute(vector<int>& fruits) {
    int n = fruits.size(), maxLen = 0;
    for (int i = 0; i < n; i++) {
        set<int> st;
        for (int j = i; j < n; j++) {
            st.insert(fruits[j]);
            if (st.size() <= 2) maxLen = max(maxLen, j - i + 1);
            else break;
        }
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int totalFruitBrute(int[] fruits) {
        int n = fruits.length, maxLen = 0;
        for (int i = 0; i < n; i++) {
            Set<Integer> st = new HashSet<>();
            for (int j = i; j < n; j++) {
                st.add(fruits[j]);
                if (st.size() <= 2) maxLen = Math.max(maxLen, j - i + 1);
                else break;
            }
        }
        return maxLen;
    }
}
```

#### Approach 2: Better — sliding window with a frequency map, shrinking fully
- Expand `r` and add `fruits[r]` to the map: `map[x]++`.
- **While** `map.size() > 2`: decrement `map[fruits[l]]`. If it hits 0, **erase** the key, because the size must count only types still in the window. Then `l++`.
- Update `maxLen`.

**Complexity:** O(2n) time, O(3) space.

**C++**
```cpp
int totalFruitBetter(vector<int>& fruits) {
    int n = fruits.size(), l = 0, r = 0, maxLen = 0;
    unordered_map<int, int> mpp;
    while (r < n) {
        mpp[fruits[r]]++;
        while (mpp.size() > 2) {
            mpp[fruits[l]]--;
            if (mpp[fruits[l]] == 0) mpp.erase(fruits[l]);
            l++;
        }
        maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int totalFruitBetter(int[] fruits) {
        int n = fruits.length, l = 0, r = 0, maxLen = 0;
        Map<Integer, Integer> mpp = new HashMap<>();
        while (r < n) {
            mpp.put(fruits[r], mpp.getOrDefault(fruits[r], 0) + 1);
            while (mpp.size() > 2) {
                mpp.put(fruits[l], mpp.get(fruits[l]) - 1);
                if (mpp.get(fruits[l]) == 0) mpp.remove(fruits[l]);
                l++;
            }
            maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Approach 3: Optimal — don't let the window shrink (`while` → `if`)
When the window becomes invalid, move `l` **one** step with `r`. The window keeps its best length while invalid, and grows only from valid positions. Update `maxLen` only when `map.size() ≤ 2`. The video points back to Max Consecutive Ones III for the full reasoning.

**Complexity:** O(n) time, O(3) space.

**C++**
```cpp
int totalFruit(vector<int>& fruits) {
    int n = fruits.size(), l = 0, r = 0, maxLen = 0;
    unordered_map<int, int> mpp;
    while (r < n) {
        mpp[fruits[r]]++;
        if (mpp.size() > 2) {                      // slide by one, don't shrink
            mpp[fruits[l]]--;
            if (mpp[fruits[l]] == 0) mpp.erase(fruits[l]);
            l++;
        }
        if (mpp.size() <= 2) maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int totalFruit(int[] fruits) {
        int n = fruits.length, l = 0, r = 0, maxLen = 0;
        Map<Integer, Integer> mpp = new HashMap<>();
        while (r < n) {
            mpp.put(fruits[r], mpp.getOrDefault(fruits[r], 0) + 1);
            if (mpp.size() > 2) {
                mpp.put(fruits[l], mpp.get(fruits[l]) - 1);
                if (mpp.get(fruits[l]) == 0) mpp.remove(fruits[l]);
                l++;
            }
            if (mpp.size() <= 2) maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Edge Cases & Pitfalls
- **Erase** zero-count keys. Otherwise `map.size()` keeps counting fruit types that have left the window.
- With only one or two types in the whole array, the answer is `n`.

#### Key Takeaways
- Problem-statement noise ("baskets", "trees") hides the standard "longest subarray with ≤ k distinct" pattern, here with k = 2.

[↑ Contents](#contents) · [← Previous](#p237) · [Next →](#p239)

---

<a id="p239"></a>

### 5. Longest Substring With At Most K Distinct Characters

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Longest and Smallest Window Problems | Pro | Yes | [LeetCode](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/longest-substring-with-at-most-k-distinct-characters) | [Watch](https://youtu.be/teM9ZsVRQyc) |

#### Problem Statement
Given a string `s` and an integer `k`, return the length of the longest substring containing **at most `k` distinct characters**.

```text
s = "aaabbccd", k = 2   ->  5   ("aaabb")
s = "eceba",    k = 2   ->  3   ("ece")
s = "aa",       k = 1   ->  2
```

#### Approach 1: Brute Force — all substrings with a frequency map
- For each start `i`, clear the map and extend `j`, counting characters.
- Once `map.size() > k`, **break**.
- Otherwise update `maxLen`.

**Complexity:** O(n²) time. Map operations are O(log 256) at most, which is constant, or O(1) with a hash map. O(256) space.

**C++**
```cpp
int kDistinctCharBrute(string s, int k) {
    int n = s.size(), maxLen = 0;
    for (int i = 0; i < n; i++) {
        unordered_map<char, int> mpp;
        for (int j = i; j < n; j++) {
            mpp[s[j]]++;
            if ((int)mpp.size() <= k) maxLen = max(maxLen, j - i + 1);
            else break;
        }
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int kDistinctCharBrute(String s, int k) {
        int n = s.length(), maxLen = 0;
        for (int i = 0; i < n; i++) {
            Map<Character, Integer> mpp = new HashMap<>();
            for (int j = i; j < n; j++) {
                mpp.put(s.charAt(j), mpp.getOrDefault(s.charAt(j), 0) + 1);
                if (mpp.size() <= k) maxLen = Math.max(maxLen, j - i + 1);
                else break;
            }
        }
        return maxLen;
    }
}
```

#### Approach 2: Better — sliding window, shrink while invalid
- Add `s[r]` to the map.
- **While** `map.size() > k`: decrement `s[l]`, erase it at zero, and `l++`.
- Update `maxLen`.

**Complexity:** O(2n) time, O(256) space.

**C++**
```cpp
int kDistinctCharBetter(string s, int k) {
    int n = s.size(), l = 0, r = 0, maxLen = 0;
    unordered_map<char, int> mpp;
    while (r < n) {
        mpp[s[r]]++;
        while ((int)mpp.size() > k) {
            mpp[s[l]]--;
            if (mpp[s[l]] == 0) mpp.erase(s[l]);
            l++;
        }
        maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int kDistinctCharBetter(String s, int k) {
        int n = s.length(), l = 0, r = 0, maxLen = 0;
        Map<Character, Integer> mpp = new HashMap<>();
        while (r < n) {
            mpp.put(s.charAt(r), mpp.getOrDefault(s.charAt(r), 0) + 1);
            while (mpp.size() > k) {
                char c = s.charAt(l);
                mpp.put(c, mpp.get(c) - 1);
                if (mpp.get(c) == 0) mpp.remove(c);
                l++;
            }
            maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Approach 3: Optimal — non-shrinking window
Replace the inner `while` with an `if`: slide `l` one step when invalid. Update `maxLen` only when `map.size() ≤ k`.

**Complexity:** O(n) time, O(256) space.

**C++**
```cpp
int kDistinctChar(string s, int k) {
    int n = s.size(), l = 0, r = 0, maxLen = 0;
    unordered_map<char, int> mpp;
    while (r < n) {
        mpp[s[r]]++;
        if ((int)mpp.size() > k) {
            mpp[s[l]]--;
            if (mpp[s[l]] == 0) mpp.erase(s[l]);
            l++;
        }
        if ((int)mpp.size() <= k) maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int kDistinctChar(String s, int k) {
        int n = s.length(), l = 0, r = 0, maxLen = 0;
        Map<Character, Integer> mpp = new HashMap<>();
        while (r < n) {
            mpp.put(s.charAt(r), mpp.getOrDefault(s.charAt(r), 0) + 1);
            if (mpp.size() > k) {
                char c = s.charAt(l);
                mpp.put(c, mpp.get(c) - 1);
                if (mpp.get(c) == 0) mpp.remove(c);
                l++;
            }
            if (mpp.size() <= k) maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Edge Cases & Pitfalls
- `k = 0` gives 0. Every non-empty substring has at least one distinct character, and the code naturally never records one.
- Some variants (GfG "Longest K unique characters substring") want **exactly** k distinct and return −1 if impossible. In that case, record only when `size == k`.

#### Key Takeaways
- This generalises Fruit Into Baskets (k = 2). One template covers both: expand, fix validity with `while` (or `if` for max-length-only), then record.

[↑ Contents](#contents) · [← Previous](#p238) · [Next →](#p240)

---

<a id="p240"></a>

### 6. Longest Repeating Character Replacement

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Longest and Smallest Window Problems | Pro | No | [LeetCode](https://leetcode.com/problems/longest-repeating-character-replacement/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/longest-repeating-character-replacement) | [Watch](https://youtu.be/_eNhaDCr6P0) |

#### Problem Statement
`s` consists of uppercase English letters. You may change **at most `k`** characters to any other uppercase letter. Return the length of the longest substring in which **all characters are equal** after the changes.

```text
s = "AABABBA", k = 1   ->  4   ("AABA" with the B changed to A, or "ABBB")
s = "AAABBCCD", k = 2  ->  5   ("AAABB": change both B's)
s = "ABAB", k = 2      ->  4
```

#### Intuition — how many changes does a window need?
To make a window uniform, keep its **most frequent** character and change everything else. That is the cheapest choice.

  **changes needed = window length − maxFreq**

For example, `AAABBC` (length 6, A × 3) needs 3 changes. A window is valid iff `len − maxFreq ≤ k`.

#### Approach 1: Brute Force — all substrings
- For each `i`, extend `j` while counting letters in `hash[26]` and tracking `maxFreq`.
- If `(j−i+1) − maxFreq ≤ k`, update the answer.
- Otherwise **break**. Adding characters never lowers the number of changes needed.

**Complexity:** O(n²) time, O(26) space.

**C++**
```cpp
int characterReplacementBrute(string s, int k) {
    int n = s.size(), maxLen = 0;
    for (int i = 0; i < n; i++) {
        int hash[26] = {0}, maxf = 0;
        for (int j = i; j < n; j++) {
            hash[s[j] - 'A']++;
            maxf = max(maxf, hash[s[j] - 'A']);
            int changes = (j - i + 1) - maxf;
            if (changes <= k) maxLen = max(maxLen, j - i + 1);
            else break;
        }
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int characterReplacementBrute(String s, int k) {
        int n = s.length(), maxLen = 0;
        for (int i = 0; i < n; i++) {
            int[] hash = new int[26];
            int maxf = 0;
            for (int j = i; j < n; j++) {
                hash[s.charAt(j) - 'A']++;
                maxf = Math.max(maxf, hash[s.charAt(j) - 'A']);
                int changes = (j - i + 1) - maxf;
                if (changes <= k) maxLen = Math.max(maxLen, j - i + 1);
                else break;
            }
        }
        return maxLen;
    }
}
```

#### Approach 2: Better — sliding window, shrink and rescan maxFreq
- Expand `r` and update `hash` and `maxf`.
- **While** `(r−l+1) − maxf > k`: remove `s[l]`, **rescan all 26 counts** to recompute `maxf`, then `l++`.
- Record the length of the valid window.

**Complexity:** O((n + n) · 26) time in the worst case. The rescan runs inside the shrink loop, whose iterations total at most n. O(26) space.

**C++**
```cpp
int characterReplacementBetter(string s, int k) {
    int n = s.size(), l = 0, r = 0, maxLen = 0, maxf = 0;
    int hash[26] = {0};
    while (r < n) {
        hash[s[r] - 'A']++;
        maxf = max(maxf, hash[s[r] - 'A']);
        while ((r - l + 1) - maxf > k) {
            hash[s[l] - 'A']--;
            maxf = 0;
            for (int i = 0; i < 26; i++) maxf = max(maxf, hash[i]);   // rescan
            l++;
        }
        maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int characterReplacementBetter(String s, int k) {
        int n = s.length(), l = 0, r = 0, maxLen = 0, maxf = 0;
        int[] hash = new int[26];
        while (r < n) {
            hash[s.charAt(r) - 'A']++;
            maxf = Math.max(maxf, hash[s.charAt(r) - 'A']);
            while ((r - l + 1) - maxf > k) {
                hash[s.charAt(l) - 'A']--;
                maxf = 0;
                for (int i = 0; i < 26; i++) maxf = Math.max(maxf, hash[i]);
                l++;
            }
            maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Approach 3: Better still — never decrease `maxf`
**Observation:** suppose the best answer so far is `len = 5`, with `maxf = 3`. To beat it, you need a window of length 6 that is valid: `6 − maxf ≤ k`. Since `5 − 3 = k` was the limit, that needs `maxf ≥ 4`.
- A **smaller** `maxf` can never produce a longer valid window.
- So when shrinking, there's no need to lower `maxf` or rescan for it. A stale, too-high `maxf` can only make a window *look* valid while it is no longer than one already recorded.
- That removes the ×26 factor.

**Complexity:** O(2n) time, O(26) space.

**C++**
```cpp
int characterReplacementBetter2(string s, int k) {
    int n = s.size(), l = 0, r = 0, maxLen = 0, maxf = 0;
    int hash[26] = {0};
    while (r < n) {
        hash[s[r] - 'A']++;
        maxf = max(maxf, hash[s[r] - 'A']);
        while ((r - l + 1) - maxf > k) {         // maxf is never decreased
            hash[s[l] - 'A']--;
            l++;
        }
        maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int characterReplacementBetter2(String s, int k) {
        int n = s.length(), l = 0, r = 0, maxLen = 0, maxf = 0;
        int[] hash = new int[26];
        while (r < n) {
            hash[s.charAt(r) - 'A']++;
            maxf = Math.max(maxf, hash[s.charAt(r) - 'A']);
            while ((r - l + 1) - maxf > k) {
                hash[s.charAt(l) - 'A']--;
                l++;
            }
            maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Approach 4: Optimal — non-shrinking window (`while` → `if`)
The answer only grows one step at a time: a 5 can become a 6, never jump to a 7. So when the window becomes invalid, drop just **one** character from the left. The window keeps its size while sliding, and grows only when a higher `maxf` makes the bigger size valid.

**Complexity:** O(n) time, O(26) space.

**C++**
```cpp
int characterReplacement(string s, int k) {
    int n = s.size(), l = 0, r = 0, maxLen = 0, maxf = 0;
    int hash[26] = {0};
    while (r < n) {
        hash[s[r] - 'A']++;
        maxf = max(maxf, hash[s[r] - 'A']);
        if ((r - l + 1) - maxf > k) {            // slide by one
            hash[s[l] - 'A']--;
            l++;
        }
        if ((r - l + 1) - maxf <= k) maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}
```

**Java**
```java
class Solution {
    static int characterReplacement(String s, int k) {
        int n = s.length(), l = 0, r = 0, maxLen = 0, maxf = 0;
        int[] hash = new int[26];
        while (r < n) {
            hash[s.charAt(r) - 'A']++;
            maxf = Math.max(maxf, hash[s.charAt(r) - 'A']);
            if ((r - l + 1) - maxf > k) {
                hash[s.charAt(l) - 'A']--;
                l++;
            }
            if ((r - l + 1) - maxf <= k) maxLen = Math.max(maxLen, r - l + 1);
            r++;
        }
        return maxLen;
    }
}
```

#### Edge Cases & Pitfalls
- With the stale `maxf`, the window `[l, r]` may not actually be valid at every moment. The **recorded maximum** is still correct: the window only grows when `maxf` truly increases, at which point the current window really is valid.
- `k ≥ n − 1`: the whole string works.

#### Key Takeaways
- Valid ⇔ `len − maxFreq ≤ k`.
- When the goal is the longest window, a quantity that only needs to *increase* to help (here `maxFreq`) never has to be decreased. Combined with `while → if`, this gives one O(n) pass.

[↑ Contents](#contents) · [← Previous](#p239) · [Next →](#p241)

---

<a id="p241"></a>

### 7. Minimum Window Substring

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Longest and Smallest Window Problems | Pro | No | [LeetCode](https://leetcode.com/problems/minimum-window-substring/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/minimum-window-substring) | [Watch](https://youtu.be/WJaij9ffOIY) |

#### Problem Statement
Given strings `s` and `t`, return the **shortest substring of `s`** that contains **every character of `t`, including duplicates**. Return `""` if there is none.

```text
s = "ddaaabbca", t = "abc"     ->  "bca"
s = "ADOBECODEBANC", t = "ABC" ->  "BANC"
s = "a", t = "aa"              ->  ""     (t needs two a's)
```

The count matters. For `t = "abbc"`, a window must contain at least two `b`s.

#### Intuition — the pre-insert / count trick (used by both approaches)
**Setup.** Put every character of `t` into `hash` with its frequency: `hash[c]++`. Keep `count` = how many characters of `t` the window has matched so far.

**Adding a character `c` to the window:**
- if `hash[c] > 0` **before** the decrement, it was "pre-inserted" (still needed), so `count++`;
- then `hash[c]−−` regardless.

Characters not in `t`, and surplus copies, simply go negative.

**Validity.** The window contains all of `t` exactly when `count == t.length()`. No scan over `t` is needed.

**Removing `c` from the window:** `hash[c]++`. If it becomes `> 0`, a needed character just left, so `count−−`.

#### Approach 1: Brute Force — every start, extend until valid
- For each `i`, re-initialise `hash` from `t` and set `count = 0`.
- Extend `j`, applying the add rule.
- The first time `count == m`, compare `j − i + 1` with the best length, store the start, and **break**. A longer window from the same start can't be smaller.

**Complexity:** O(n² + n·m) time, because `hash` is re-filled for each start. O(256) space.

**C++**
```cpp
string minWindowBrute(string s, string t) {
    int n = s.size(), m = t.size();
    int minLen = INT_MAX, sIndex = -1;
    for (int i = 0; i < n; i++) {
        int hash[256] = {0};
        for (char c : t) hash[(unsigned char)c]++;
        int count = 0;
        for (int j = i; j < n; j++) {
            unsigned char c = s[j];
            if (hash[c] > 0) count++;
            hash[c]--;
            if (count == m) {
                if (j - i + 1 < minLen) { minLen = j - i + 1; sIndex = i; }
                break;
            }
        }
    }
    return sIndex == -1 ? "" : s.substr(sIndex, minLen);
}
```

**Java**
```java
class Solution {
    static String minWindowBrute(String s, String t) {
        int n = s.length(), m = t.length();
        int minLen = Integer.MAX_VALUE, sIndex = -1;
        for (int i = 0; i < n; i++) {
            int[] hash = new int[256];
            for (char c : t.toCharArray()) hash[c]++;
            int count = 0;
            for (int j = i; j < n; j++) {
                char c = s.charAt(j);
                if (hash[c] > 0) count++;
                hash[c]--;
                if (count == m) {
                    if (j - i + 1 < minLen) { minLen = j - i + 1; sIndex = i; }
                    break;
                }
            }
        }
        return sIndex == -1 ? "" : s.substring(sIndex, sIndex + minLen);
    }
}
```

#### Approach 2: Optimal — sliding window: expand until valid, then shrink while valid
The words "minimum" and "**window**" in the title point straight to a sliding window.
- Expand `r`, applying the add rule.
- **While** `count == m`, the window is valid:
  1. record `r − l + 1` and `l` if smaller;
  2. remove `s[l]` (`hash[s[l]]++`, and if it becomes `> 0`, `count−−`);
  3. `l++`.
- Continue expanding.

Dry run on `"ddaaabbca"`, `t = "abc"`:
- `r` expands to the `c` at index 7, where count = 3. The window `ddaaabbc` has length 8.
- Shrink while valid: drop d, d, a, a, giving lengths 7, 6, 5 and then 4 (`abbc`).
- Dropping that last `a` makes `hash[a] = 1`, so count = 2 and the window is invalid.
- Expand to the `a` at index 8, and count = 3 again. Shrink: drop a `b` to get `bca`, length **3**. Dropping the next `b` invalidates the window.
- `r` runs out. Answer: **"bca"**.

**Complexity:**
- Time: O(2n + m). `l` and `r` each move at most n times, and pre-inserting `t` costs m.
- Space: O(256).

**C++**
```cpp
string minWindow(string s, string t) {
    int n = s.size(), m = t.size();
    int hash[256] = {0};
    for (char c : t) hash[(unsigned char)c]++;          // pre-insert t
    int l = 0, r = 0, count = 0, minLen = INT_MAX, sIndex = -1;
    while (r < n) {
        unsigned char c = s[r];
        if (hash[c] > 0) count++;                       // a needed char arrived
        hash[c]--;
        while (count == m) {                            // valid: try to shrink
            if (r - l + 1 < minLen) { minLen = r - l + 1; sIndex = l; }
            unsigned char d = s[l];
            hash[d]++;
            if (hash[d] > 0) count--;                   // a needed char left
            l++;
        }
        r++;
    }
    return sIndex == -1 ? "" : s.substr(sIndex, minLen);
}
```

**Java**
```java
class Solution {
    static String minWindow(String s, String t) {
        int n = s.length(), m = t.length();
        int[] hash = new int[256];
        for (char c : t.toCharArray()) hash[c]++;
        int l = 0, r = 0, count = 0, minLen = Integer.MAX_VALUE, sIndex = -1;
        while (r < n) {
            char c = s.charAt(r);
            if (hash[c] > 0) count++;
            hash[c]--;
            while (count == m) {
                if (r - l + 1 < minLen) { minLen = r - l + 1; sIndex = l; }
                char d = s.charAt(l);
                hash[d]++;
                if (hash[d] > 0) count--;
                l++;
            }
            r++;
        }
        return sIndex == -1 ? "" : s.substring(sIndex, sIndex + minLen);
    }
}
```

#### Edge Cases & Pitfalls
- **Record before you shrink.** The window is valid at the top of the shrink loop, and removing `s[l]` may break it.
- Increment `count` only when `hash[c] > 0` before the decrement. Surplus copies of a needed character must not count twice.
- C++ `substr(pos, len)` takes a **length**. Java `substring(begin, end)` takes an **end index**.
- If `t` is longer than `s`, the answer is `""` automatically.

#### Key Takeaways
- For "minimum window" problems: expand until valid, then **shrink while still valid**, recording at each step. This is the mirror image of the "longest window" template.
- The pre-insert-and-count trick turns "does the window contain all of t?" into an O(1) check.

[↑ Contents](#contents) · [← Previous](#p240) · [Next →](#p242)

---

<a id="p242"></a>

### 8. Minimum Window Subsequence

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Longest and Smallest Window Problems | Pro | Yes | [LeetCode](https://leetcode.com/problems/minimum-window-subsequence/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given strings `s1` and `s2`, return the **shortest contiguous substring of `s1`** in which `s2` appears as a **subsequence**: in order, but not necessarily contiguous. If several are equally short, return the **left-most**. Return `""` if there is none.

```text
s1 = "abcdebdde", s2 = "bde"   ->  "bcde"   ("bdde" is also length 4, but "bcde" starts earlier)
s1 = "jmeqksfrsdcmsiwvaovztaqenprpvnbstl", s2 = "u"  ->  ""
s1 = "fgrqsqsnodwmxzkzxwqegkndaa", s2 = "kzed"       ->  "kzxwqegknd"
```

How this differs from Minimum Window *Substring*: there, **order doesn't matter** but counts do. Here **order matters**.

#### Approach 1: Brute Force — start at every match of `s2[0]` and scan forward
- For each `i` with `s1[i] == s2[0]`, walk forward from `i`, advancing a pointer into `s2` on each match.
- When all of `s2` has been matched at index `j`, the window `[i, j]` is a candidate.
- Keep the shortest one. Iterate `i` left to right and use a strict `<` so the left-most wins ties.

**Complexity:** O(n²) time in the worst case, O(1) space.

**C++**
```cpp
string minWindowSubseqBrute(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    int bestLen = INT_MAX, bestStart = -1;
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[0]) continue;
        int k = 0, j = i;
        while (j < n && k < m) {
            if (s1[j] == s2[k]) k++;
            j++;
        }
        if (k == m && j - i < bestLen) { bestLen = j - i; bestStart = i; }   // window [i, j-1]
    }
    return bestStart == -1 ? "" : s1.substr(bestStart, bestLen);
}
```

**Java**
```java
class Solution {
    static String minWindowSubseqBrute(String s1, String s2) {
        int n = s1.length(), m = s2.length();
        int bestLen = Integer.MAX_VALUE, bestStart = -1;
        for (int i = 0; i < n; i++) {
            if (s1.charAt(i) != s2.charAt(0)) continue;
            int k = 0, j = i;
            while (j < n && k < m) {
                if (s1.charAt(j) == s2.charAt(k)) k++;
                j++;
            }
            if (k == m && j - i < bestLen) { bestLen = j - i; bestStart = i; }
        }
        return bestStart == -1 ? "" : s1.substring(bestStart, bestStart + bestLen);
    }
}
```

#### Approach 2: Better — forward scan, then backward tightening (two pointers)
A forward match from `i` that ends at `j` isn't necessarily tight: a later start may also work with the same end. So:
1. **Forward:** from `i`, match `s2` left to right until its last character matches at index `end`.
2. **Backward:** from `end`, match `s2` **right to left** going backwards in `s1`. The point where `s2[0]` matches is the **latest possible start** for this end. That window `[start, end]` is the tightest one ending at `end`.
3. Record it, then resume the forward scan from `start + 1`.

Dry run on `"abcdebdde"`, `"bde"`:
- Forward from index 0 matches b (1), d (3), e (4), so end = 4.
- Backward from 4 matches e (4), d (3), b (1), so start = 1. Window `"bcde"`.
- Resume at 2. Forward matches b (5), d (6), e (8). Backward gives e (8), d (7), b (5), so window `"bdde"`, length 4, not shorter.
- Resume at 6: no more `b`. Answer: **"bcde"**.

**Complexity:** O(n·m) time in the worst case, but usually much faster. O(1) space.

**C++**
```cpp
string minWindowSubseqTwoPtr(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    int bestLen = INT_MAX, bestStart = -1;
    int i = 0;
    while (i < n) {
        int k = 0;
        while (i < n) {                                   // forward: find an end
            if (s1[i] == s2[k]) { k++; if (k == m) break; }
            i++;
        }
        if (i == n) break;                                // s2 not completed
        int end = i;
        k = m - 1;
        while (k >= 0) {                                  // backward: tightest start
            if (s1[i] == s2[k]) k--;
            i--;
        }
        int start = i + 1;
        if (end - start + 1 < bestLen) { bestLen = end - start + 1; bestStart = start; }
        i = start + 1;                                    // resume after this start
    }
    return bestStart == -1 ? "" : s1.substr(bestStart, bestLen);
}
```

**Java**
```java
class Solution {
    static String minWindowSubseqTwoPtr(String s1, String s2) {
        int n = s1.length(), m = s2.length();
        int bestLen = Integer.MAX_VALUE, bestStart = -1;
        int i = 0;
        while (i < n) {
            int k = 0;
            while (i < n) {
                if (s1.charAt(i) == s2.charAt(k)) { k++; if (k == m) break; }
                i++;
            }
            if (i == n) break;
            int end = i;
            k = m - 1;
            while (k >= 0) {
                if (s1.charAt(i) == s2.charAt(k)) k--;
                i--;
            }
            int start = i + 1;
            if (end - start + 1 < bestLen) { bestLen = end - start + 1; bestStart = start; }
            i = start + 1;
        }
        return bestStart == -1 ? "" : s1.substring(bestStart, bestStart + bestLen);
    }
}
```

#### Approach 3: Optimal (guaranteed bound) — DP on "latest start"
Let `dp[i][j]` = the **largest start index** `k` such that `s2[0..j]` is a subsequence of `s1[k..i]`, or −1 if there is none.
- If `s1[i] == s2[j]`: `dp[i][j] = (j == 0) ? i : dp[i−1][j−1]`. Use this character for `s2[j]` and inherit the start.
- Otherwise: `dp[i][j] = dp[i−1][j]`. Skip `s1[i]`.

For every `i` with `dp[i][m−1] ≠ −1`, the window `[dp[i][m−1], i]` is the tightest one ending at `i`. Scanning `i` left to right with a strict `<` gives the left-most minimum. Only the previous row is needed, so keep a 1-D array and update `j` from high to low.

**Complexity:** O(n·m) time, O(m) space.

**C++**
```cpp
string minWindowSubseq(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<int> dp(m, -1);                            // dp[j] for the previous i
    int bestLen = INT_MAX, bestStart = -1;
    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {            // high -> low: dp[j-1] is still "i-1"
            if (s1[i] == s2[j]) dp[j] = (j == 0) ? i : dp[j - 1];
        }
        if (dp[m - 1] != -1 && i - dp[m - 1] + 1 < bestLen) {
            bestLen = i - dp[m - 1] + 1;
            bestStart = dp[m - 1];
        }
    }
    return bestStart == -1 ? "" : s1.substr(bestStart, bestLen);
}
```

**Java**
```java
class Solution {
    static String minWindowSubseq(String s1, String s2) {
        int n = s1.length(), m = s2.length();
        int[] dp = new int[m];
        Arrays.fill(dp, -1);
        int bestLen = Integer.MAX_VALUE, bestStart = -1;
        for (int i = 0; i < n; i++) {
            for (int j = m - 1; j >= 0; j--) {
                if (s1.charAt(i) == s2.charAt(j)) dp[j] = (j == 0) ? i : dp[j - 1];
            }
            if (dp[m - 1] != -1 && i - dp[m - 1] + 1 < bestLen) {
                bestLen = i - dp[m - 1] + 1;
                bestStart = dp[m - 1];
            }
        }
        return bestStart == -1 ? "" : s1.substring(bestStart, bestStart + bestLen);
    }
}
```

#### Edge Cases & Pitfalls
- **Ties go to the left-most window.** Compare with `<`, never `≤`, while scanning left to right.
- In the 1-D DP, iterate `j` **downwards**. Otherwise `dp[j−1]` has already been overwritten with the current row.
- A plain "expand then shrink" window (as in Minimum Window Substring) does **not** work here: order matters, and removing a character from the left can break the subsequence in non-obvious ways.

#### Key Takeaways
- "Subsequence inside a window" calls for forward/backward two pointers in practice, or a DP storing the latest start for a guaranteed O(n·m).
- The backward pass is what makes a forward-found window tight.

[↑ Contents](#contents) · [← Previous](#p241) · [Next →](#p243)

---

## Counting Subarrays / Substrings Problems

<a id="p243"></a>

### 9. Number of Substrings Containing All Three Characters

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Counting Subarrays / Substrings Problems | Core | No | [LeetCode](https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-substrings-containing-all-three-characters-a-b-and-c) | [Watch](https://youtu.be/xtqN4qlgr8s) |

#### Problem Statement
`s` contains only the characters `a`, `b` and `c`. Return the number of substrings that contain **at least one of each** of the three characters.

```text
s = "bbacba"   ->  9
s = "abcabc"   ->  10
s = "aaacb"    ->  3
```

#### Approach 1: Brute Force — all substrings
For each start `i`, extend `j` and mark `hash[s[j] − 'a'] = 1`. Whenever `hash[0] + hash[1] + hash[2] == 3`, increment `count`.

**Complexity:** O(n²) time, O(3) space.

**C++**
```cpp
int numberOfSubstringsBrute(string s) {
    int n = s.size(), count = 0;
    for (int i = 0; i < n; i++) {
        int hash[3] = {0};
        for (int j = i; j < n; j++) {
            hash[s[j] - 'a'] = 1;
            if (hash[0] + hash[1] + hash[2] == 3) count++;
        }
    }
    return count;
}
```

**Java**
```java
class Solution {
    static int numberOfSubstringsBrute(String s) {
        int n = s.length(), count = 0;
        for (int i = 0; i < n; i++) {
            int[] hash = new int[3];
            for (int j = i; j < n; j++) {
                hash[s.charAt(j) - 'a'] = 1;
                if (hash[0] + hash[1] + hash[2] == 3) count++;
            }
        }
        return count;
    }
}
```

#### Approach 2: Better — break at the first valid end
- **Every extension of a valid window is valid.** If `s[i..j]` already contains a, b and c, then so do `s[i..j+1]`, `s[i..j+2]` and so on.
- **So count them all at once.** At the first `j` that makes the window valid, add **`n − j`** and **break**.

For example, in `"bbacba"` starting at 0, the first valid `j` is 3, which adds 6 − 3 = 3.

This is faster on many inputs, but it's still O(n²) in the worst case, e.g. `"aaaa…"` never breaks. The video presents it as the stepping stone to the optimal idea.

**C++**
```cpp
int numberOfSubstringsBetter(string s) {
    int n = s.size(), count = 0;
    for (int i = 0; i < n; i++) {
        int hash[3] = {0};
        for (int j = i; j < n; j++) {
            hash[s[j] - 'a'] = 1;
            if (hash[0] + hash[1] + hash[2] == 3) {
                count += n - j;                  // this window and every extension
                break;
            }
        }
    }
    return count;
}
```

**Java**
```java
class Solution {
    static int numberOfSubstringsBetter(String s) {
        int n = s.length(), count = 0;
        for (int i = 0; i < n; i++) {
            int[] hash = new int[3];
            for (int j = i; j < n; j++) {
                hash[s.charAt(j) - 'a'] = 1;
                if (hash[0] + hash[1] + hash[2] == 3) {
                    count += n - j;
                    break;
                }
            }
        }
        return count;
    }
}
```

#### Approach 3: Optimal — count by end index using "last seen" positions
Flip the viewpoint. For each **end** index `i`, count the valid substrings that **end at `i`**.
- Track `lastSeen[a]`, `lastSeen[b]` and `lastSeen[c]`, the latest index of each character, initially −1.
- The **minimal** valid window ending at `i` starts at `minLast = min(lastSeen[a], lastSeen[b], lastSeen[c])`. That is the character seen least recently.
- Any start in `0 … minLast` also works, because extending to the left keeps all three. So `minLast + 1` substrings end at `i`.

Dry run on `"bbacba"`:

| i | char | lastSeen (a, b, c) | min | adds |
|---|---|---|---|---|
| 0 | b | (−1, 0, −1) | −1 | 0 |
| 1 | b | (−1, 1, −1) | −1 | 0 |
| 2 | a | (2, 1, −1) | −1 | 0 |
| 3 | c | (2, 1, 3) | 1 | 2 |
| 4 | b | (2, 4, 3) | 2 | 3 |
| 5 | a | (5, 4, 3) | 3 | 4 |

Total = **9**.

If one of the characters hasn't appeared yet, `min = −1` and `1 + (−1) = 0` is added. So the "all three seen" check is optional.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int numberOfSubstrings(string s) {
    int lastSeen[3] = {-1, -1, -1};
    int n = s.size(), count = 0;
    for (int i = 0; i < n; i++) {
        lastSeen[s[i] - 'a'] = i;
        if (lastSeen[0] != -1 && lastSeen[1] != -1 && lastSeen[2] != -1)
            count += 1 + min({lastSeen[0], lastSeen[1], lastSeen[2]});
    }
    return count;
}
```

**Java**
```java
class Solution {
    static int numberOfSubstrings(String s) {
        int[] lastSeen = {-1, -1, -1};
        int n = s.length(), count = 0;
        for (int i = 0; i < n; i++) {
            lastSeen[s.charAt(i) - 'a'] = i;
            if (lastSeen[0] != -1 && lastSeen[1] != -1 && lastSeen[2] != -1)
                count += 1 + Math.min(lastSeen[0], Math.min(lastSeen[1], lastSeen[2]));
        }
        return count;
    }
}
```

#### Edge Cases & Pitfalls
- Use a 64-bit counter for very long strings. The number of substrings is about n²/2, which overflows an int beyond n ≈ 65 000. LeetCode's limit is 5·10⁴, so `int` is fine there.
- The `n − j` trick counts substrings by **start**, while the optimal solution counts them by **end**. Both partitions cover every substring exactly once.

#### Key Takeaways
- To **count** substrings with an "at least" property, use the fact that every extension of a valid window is valid. Count all extensions in one step instead of enumerating them.
- Tracking the "last seen" index per character gives the minimal valid window ending at each position in O(1).

[↑ Contents](#contents) · [← Previous](#p242) · [Next →](#p244)

---

<a id="p244"></a>

### 10. Binary Subarrays With Sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Counting Subarrays / Substrings Problems | Core | No | [LeetCode](https://leetcode.com/problems/binary-subarrays-with-sum/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/binary-subarrays-with-sum) | [Watch](https://youtu.be/XnMdNUkX6VM) |

#### Problem Statement
Given a **binary** array `nums` and an integer `goal`, return the number of non-empty subarrays whose sum equals `goal`.

```text
nums = [1, 0, 0, 1, 1, 0], goal = 2   ->  7
nums = [1, 0, 1, 0, 1],    goal = 2   ->  4
nums = [0, 0, 0, 0, 0],    goal = 0   ->  15
```

The video's prerequisite is **Count Subarray Sum Equals K** from the Arrays/Hashing section, which handles arbitrary integers with prefix sums and a hash map. Here the array is binary, which allows dropping the extra space.

#### Approach 1: Brute Force — all subarrays
Fix `i`, extend `j` while keeping a running sum, and count `sum == goal`.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int numSubarraysWithSumBrute(vector<int>& nums, int goal) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum == goal) count++;
        }
    }
    return count;
}
```

**Java**
```java
class Solution {
    static int numSubarraysWithSumBrute(int[] nums, int goal) {
        int n = nums.length, count = 0;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = i; j < n; j++) {
                sum += nums[j];
                if (sum == goal) count++;
            }
        }
        return count;
    }
}
```

#### Approach 2: Better — prefix sum + hash map (from "Subarray Sum Equals K")
A subarray ending at `i` sums to `goal` exactly when an earlier prefix sum equals `prefix − goal`. Count the prefix sums seen so far in a map, seeded with `{0: 1}`.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int numSubarraysWithSumHash(vector<int>& nums, int goal) {
    unordered_map<int, int> mpp;
    mpp[0] = 1;
    int prefix = 0, count = 0;
    for (int x : nums) {
        prefix += x;
        if (mpp.count(prefix - goal)) count += mpp[prefix - goal];
        mpp[prefix]++;
    }
    return count;
}
```

**Java**
```java
class Solution {
    static int numSubarraysWithSumHash(int[] nums, int goal) {
        Map<Integer, Integer> mpp = new HashMap<>();
        mpp.put(0, 1);
        int prefix = 0, count = 0;
        for (int x : nums) {
            prefix += x;
            count += mpp.getOrDefault(prefix - goal, 0);
            mpp.put(prefix, mpp.getOrDefault(prefix, 0) + 1);
        }
        return count;
    }
}
```

#### Approach 3: Optimal — `atMost(goal) − atMost(goal − 1)`, O(1) space
**Why a direct window fails for "sum == goal":** zeros don't change the sum. When the window's sum equals `goal`, you can't tell whether to move `r` or `l`. In `[1,0,1,1,0]`, both `[1,0,1]` and `[0,1,1]` are valid, and a single window misses one of them.

**Count "sum ≤ goal" instead.** This *is* monotone:
- Expand `r` and add `nums[r]`.
- While `sum > goal`, subtract `nums[l]` and `l++`.
- Now **every** subarray ending at `r` and starting in `[l, r]` has sum ≤ goal. There are `r − l + 1` of them. If the longest one is valid, all of its suffixes are too.

**Then subtract:**

  **#(sum == goal) = #(sum ≤ goal) − #(sum ≤ goal − 1)**

When `goal = 0`, the second call gets −1. No subarray of a binary array has a negative sum, so `atMost(−1)` returns 0. That's why the guard `if (goal < 0) return 0` exists.

Dry run of `atMost(2)` on `[1,0,1,1,0]`:
- r = 0 adds 1, r = 1 adds 2, r = 2 adds 3.
- r = 3: sum = 3 > 2, so drop `nums[0]` and l = 1. Adds 3.
- r = 4 adds 4.
- Total: 13.

**Complexity:** O(2 · 2n) time (two calls, each two-pointer), O(1) space. The time grows a little; the extra space disappears.

**C++**
```cpp
int countAtMost(vector<int>& nums, int goal) {
    if (goal < 0) return 0;                    // sums are never negative
    int l = 0, r = 0, sum = 0, count = 0, n = nums.size();
    while (r < n) {
        sum += nums[r];
        while (sum > goal) {
            sum -= nums[l];
            l++;
        }
        count += r - l + 1;                    // subarrays ending at r
        r++;
    }
    return count;
}
int numSubarraysWithSum(vector<int>& nums, int goal) {
    return countAtMost(nums, goal) - countAtMost(nums, goal - 1);
}
```

**Java**
```java
class Solution {
    static int countAtMost(int[] nums, int goal) {
        if (goal < 0) return 0;
        int l = 0, r = 0, sum = 0, count = 0, n = nums.length;
        while (r < n) {
            sum += nums[r];
            while (sum > goal) {
                sum -= nums[l];
                l++;
            }
            count += r - l + 1;
            r++;
        }
        return count;
    }
    static int numSubarraysWithSum(int[] nums, int goal) {
        return countAtMost(nums, goal) - countAtMost(nums, goal - 1);
    }
}
```

#### Edge Cases & Pitfalls
- The `sum > goal` shrink loop can push `l` to `r + 1`, giving an empty window that adds 0. That's fine.
- The loop condition is `r < n`. The video's on-screen pseudocode writes `r ≤ size`, which would read past the end.
- This trick needs **non-negative** elements so that the window sum is monotone. With negatives, use the hash-map approach.

#### Key Takeaways
- "Exactly K" = "at most K" − "at most K−1". This converts a non-monotone counting problem into two monotone sliding windows.
- For counting problems, each step adds `r − l + 1`: the number of valid subarrays ending at `r`.

[↑ Contents](#contents) · [← Previous](#p243) · [Next →](#p245)

---

<a id="p245"></a>

### 11. Count number of Nice subarrays

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Counting Subarrays / Substrings Problems | Pro | No | [LeetCode](https://leetcode.com/problems/count-number-of-nice-subarrays/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-nice-subarrays) | [Watch](https://youtu.be/j_QOv9OT9Og) |

#### Problem Statement
Given an integer array `nums` and an integer `k`, a subarray is **nice** if it contains exactly `k` **odd** numbers. Return the number of nice subarrays.

```text
nums = [1, 1, 2, 1, 1], k = 3          ->  2
nums = [2, 4, 6], k = 1                ->  0
nums = [2, 2, 2, 1, 2, 2, 1, 2, 2, 2], k = 2  ->  16
```

#### Intuition — it's the previous problem in disguise
Map each number to `nums[i] % 2`: odd becomes 1, even becomes 0. A subarray has exactly `k` odd numbers iff its **mapped sum equals k**. That is exactly **Binary Subarrays With Sum**. The video's lesson is to recognise such twisted restatements of a known problem.

#### Approach 1: Brute Force — all subarrays
**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int numberOfSubarraysBrute(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        int odd = 0;
        for (int j = i; j < n; j++) {
            odd += nums[j] % 2 != 0;
            if (odd == k) count++;
            else if (odd > k) break;
        }
    }
    return count;
}
```

**Java**
```java
class Solution {
    static int numberOfSubarraysBrute(int[] nums, int k) {
        int n = nums.length, count = 0;
        for (int i = 0; i < n; i++) {
            int odd = 0;
            for (int j = i; j < n; j++) {
                if (nums[j] % 2 != 0) odd++;
                if (odd == k) count++;
                else if (odd > k) break;
            }
        }
        return count;
    }
}
```

#### Approach 2: Optimal — `atMost(k) − atMost(k − 1)` on the odd count
This is the same code as Binary Subarrays With Sum, with `nums[r] % 2` in place of `nums[r]` when adding and removing.

**Complexity:** O(2 · 2n) time, O(1) space.

**C++**
```cpp
int countAtMostOdd(vector<int>& nums, int k) {
    if (k < 0) return 0;
    int l = 0, r = 0, odd = 0, count = 0, n = nums.size();
    while (r < n) {
        odd += nums[r] % 2 != 0;                // 1 for odd, 0 for even
        while (odd > k) {
            odd -= nums[l] % 2 != 0;
            l++;
        }
        count += r - l + 1;
        r++;
    }
    return count;
}
int numberOfSubarrays(vector<int>& nums, int k) {
    return countAtMostOdd(nums, k) - countAtMostOdd(nums, k - 1);
}
```

**Java**
```java
class Solution {
    static int countAtMostOdd(int[] nums, int k) {
        if (k < 0) return 0;
        int l = 0, r = 0, odd = 0, count = 0, n = nums.length;
        while (r < n) {
            if (nums[r] % 2 != 0) odd++;
            while (odd > k) {
                if (nums[l] % 2 != 0) odd--;
                l++;
            }
            count += r - l + 1;
            r++;
        }
        return count;
    }
    static int numberOfSubarrays(int[] nums, int k) {
        return countAtMostOdd(nums, k) - countAtMostOdd(nums, k - 1);
    }
}
```

#### Edge Cases & Pitfalls
- **Negative numbers:** `−3 % 2 == −1` in C++ and Java. Test oddness with `!= 0` (or `& 1`), not `== 1`. The video's `sum += nums[r] % 2` would subtract for negative odd numbers. LeetCode's inputs are positive, but be careful elsewhere.

#### Key Takeaways
- Map elements to 0/1 indicators, and "count elements with property P" becomes "subarray sum".
- Learn the original problem well, and its disguised variants become copy-paste.

[↑ Contents](#contents) · [← Previous](#p244) · [Next →](#p246)

---

<a id="p246"></a>

### 12. Subarrays with K Different Integers

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sliding Window / 2 Pointer › Counting Subarrays / Substrings Problems | Pro | No | [LeetCode](https://leetcode.com/problems/subarrays-with-k-different-integers/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/subarrays-with-k-different-integers) | [Watch](https://youtu.be/7wYGbV_LsX4) |

#### Problem Statement
Given an integer array `nums` and an integer `k`, return the number of subarrays with **exactly `k` distinct** integers.

```text
nums = [2, 1, 1, 1, 3, 4, 3, 2], k = 3   ->  9
nums = [1, 2, 1, 2, 3], k = 2            ->  7
nums = [1, 2, 1, 3, 4], k = 3            ->  3
```

#### Approach 1: Brute Force — all subarrays with a map
- For each `i`, extend `j` and add `nums[j]` to a frequency map.
- If `map.size() == k`, `count++`.
- If `map.size() > k`, **break**, because the distinct count can't decrease by extending.

**Complexity:** O(n²) time (with log factors for an ordered map), O(n) space.

**C++**
```cpp
int subarraysWithKDistinctBrute(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        unordered_map<int, int> mpp;
        for (int j = i; j < n; j++) {
            mpp[nums[j]]++;
            if ((int)mpp.size() == k) count++;
            else if ((int)mpp.size() > k) break;
        }
    }
    return count;
}
```

**Java**
```java
class Solution {
    static int subarraysWithKDistinctBrute(int[] nums, int k) {
        int n = nums.length, count = 0;
        for (int i = 0; i < n; i++) {
            Map<Integer, Integer> mpp = new HashMap<>();
            for (int j = i; j < n; j++) {
                mpp.put(nums[j], mpp.getOrDefault(nums[j], 0) + 1);
                if (mpp.size() == k) count++;
                else if (mpp.size() > k) break;
            }
        }
        return count;
    }
}
```

#### Approach 2: Optimal — `atMost(k) − atMost(k − 1)`
**Why a direct window fails for "exactly k":** in `[2,1,1,1,3,4,3,2]` the window `[1,1,1,3,4]` is valid. Moving `r` forward keeps it valid, but you'd miss the shorter valid windows `[1,1,3,4]`, `[1,3,4]`, … ending there. It isn't clear whether to shrink or expand.

**Count "≤ k distinct" instead.** This is monotone:
- Expand `r` and add `nums[r]` to the map.
- While `map.size() > k`, remove `nums[l]` (erase the key at zero) and `l++`.
- Every subarray ending at `r` and starting in `[l, r]` has ≤ k distinct values: if the longest one does, all of its suffixes do. So `count += r − l + 1`.

Then **exactly(k) = atMost(k) − atMost(k − 1)**.

**Complexity:** O(2 · 2n) time with an O(1) hash map, O(n) space.

**C++**
```cpp
int atMostKDistinct(vector<int>& nums, int k) {
    if (k < 0) return 0;
    unordered_map<int, int> mpp;
    int l = 0, r = 0, count = 0, n = nums.size();
    while (r < n) {
        mpp[nums[r]]++;
        while ((int)mpp.size() > k) {
            mpp[nums[l]]--;
            if (mpp[nums[l]] == 0) mpp.erase(nums[l]);
            l++;
        }
        count += r - l + 1;
        r++;
    }
    return count;
}
int subarraysWithKDistinct(vector<int>& nums, int k) {
    return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
}
```

**Java**
```java
class Solution {
    static int atMostKDistinct(int[] nums, int k) {
        if (k < 0) return 0;
        Map<Integer, Integer> mpp = new HashMap<>();
        int l = 0, r = 0, count = 0, n = nums.length;
        while (r < n) {
            mpp.put(nums[r], mpp.getOrDefault(nums[r], 0) + 1);
            while (mpp.size() > k) {
                mpp.put(nums[l], mpp.get(nums[l]) - 1);
                if (mpp.get(nums[l]) == 0) mpp.remove(nums[l]);
                l++;
            }
            count += r - l + 1;
            r++;
        }
        return count;
    }
    static int subarraysWithKDistinct(int[] nums, int k) {
        return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
    }
}
```

#### Edge Cases & Pitfalls
- In the shrink loop, `l` moves **forward** (`l++`). The video's pseudocode briefly shows `L = L − 1`, which is a typo.
- Erase keys whose count hits 0, or `map.size()` over-counts.
- `atMost(0)` returns 0, because every non-empty subarray has at least one distinct value.

#### Key Takeaways
- The "exactly = atMost(k) − atMost(k−1)" trick solves the three counting problems in this section with one template. Only the validity measure changes: sum, odd count or distinct count.

[↑ Contents](#contents) · [← Previous](#p245)

---
