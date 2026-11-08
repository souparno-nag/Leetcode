# Recursion — Striver's A2Z DSA Sheet Notes

Section 7 of 20 · 21 problems · 11 with video, 10 without · [All sections](00-index.md)

[← Strings (Basic and Medium)](06-strings-basic-and-medium.md) | [Linked-List →](08-linked-list.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Implementation Problems**

1. [Pow(x,n)](#p144) — Core
2. [Generate Parentheses](#p145) — Core · *no video*
3. [Power Set](#p146) — Core
4. [Count Good Numbers](#p147) — Core · *no video*
5. [Reverse a Stack](#p148) — Core · *no video*

**Subsequence Pattern Problems**

6. [Check if there exists a subsequence with sum K](#p149) — Core · *no video*
7. [Count all subsequences with sum K](#p150) — Core · *no video*
8. [Generate Binary Strings Without Consecutive 1s](#p151) — Core · *no video*

**FAQs (Medium)**

9. [Combination Sum](#p152) — Core · *video not transcribed*
10. [Combination Sum II](#p153) — Core · *video not transcribed*
11. [Subsets I](#p154) — Core
12. [Subsets II](#p155) — Core
13. [Combination Sum III](#p156) — Pro · *no video*

**Hard**

14. [Letter Combinations of a Phone Number](#p157) — Pro · *no video*

**FAQs (Hard)**

15. [Palindrome partitioning](#p158) — Pro
16. [Word Search](#p159) — Pro · *no video*
17. [N Queen](#p160) — Pro · *video not transcribed*
18. [Rat in a Maze](#p161) — Pro · *video not transcribed*
19. [M Coloring Problem](#p162) — Pro
20. [Sudoku Solver](#p163) — Pro
21. [Expression Add Operators](#p164) — Pro · *no video*

---

## Implementation Problems

<a id="p144"></a>

### 1. Pow(x,n)

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Implementation Problems | Core | No | [LeetCode](https://leetcode.com/problems/powx-n/) | [Watch](https://youtu.be/l0YC3876qxg) |

#### Problem Statement
Implement `pow(x, n)`, which returns xⁿ (LeetCode 50). Here `x` is a double and `n` is any 32-bit integer, including negative values and `INT_MIN`.

```text
x = 2.0,  n = 10  ->  1024.0
x = 2.1,  n = 3   ->  9.261
x = 2.0,  n = -2  ->  0.25      (2^-2 = 1 / 2^2)
```

> **Ask the interviewer:** can `n` be negative? If it can, use x⁻ⁿ = 1 / xⁿ, and watch for the overflow edge case below.

#### Approach 1: Brute Force — multiply `|n|` times
Multiply `ans` by `x` `|n|` times. If `n < 0`, return `1 / ans`.

**The edge case:** `n = −2147483648` has no positive `int` counterpart, so negating it overflows. Copy `n` into a **`long long` / `long`** before taking its absolute value.

**Complexity:** O(|n|) time, O(1) space.

**C++**
```cpp
double myPowBrute(double x, int n) {
    long long nn = n;
    if (nn < 0) nn = -nn;              // safe: nn is 64-bit
    double ans = 1.0;
    for (long long i = 0; i < nn; i++) ans *= x;
    return n < 0 ? 1.0 / ans : ans;
}
```

**Java**
```java
class Solution {
    static double myPowBrute(double x, int n) {
        long nn = n;
        if (nn < 0) nn = -nn;              // safe: nn is 64-bit
        double ans = 1.0;
        for (long i = 0; i < nn; i++) ans *= x;
        return n < 0 ? 1.0 / ans : ans;
    }
}
```

#### Approach 2: Optimal — binary exponentiation (iterative)
- **Even power:** xⁿ = (x·x)^(n/2). Square `x` and halve `n`.
- **Odd power:** xⁿ = x · xⁿ⁻¹. Multiply `x` into `ans` and decrement `n`, which makes it even.
- Stop when `n` reaches 0.

**Dry run** 2¹⁰:
- `x = 2`, `n = 10` (even): square to `x = 4`, `n = 5`.
- `n = 5` (odd): `ans = 4`, `n = 4`.
- `n = 4` (even): `x = 16`, `n = 2`.
- `n = 2` (even): `x = 256`, `n = 1`.
- `n = 1` (odd): `ans = 4 · 256 = 1024`, `n = 0`. Stop.

**Complexity:** O(log |n|) time, since an odd step always leads to an even step that halves `n`. O(1) space.

**C++**
```cpp
double myPow(double x, int n) {
    double ans = 1.0;
    long long nn = n;
    if (nn < 0) nn = -nn;
    while (nn > 0) {
        if (nn % 2 == 1) { ans *= x; nn -= 1; }   // odd: take one x out
        else { x *= x; nn /= 2; }                 // even: square the base, halve the power
    }
    return n < 0 ? 1.0 / ans : ans;
}
```

**Java**
```java
class Solution {
    public double myPow(double x, int n) {
        double ans = 1.0;
        long nn = n;
        if (nn < 0) nn = -nn;
        while (nn > 0) {
            if (nn % 2 == 1) { ans *= x; nn -= 1; }   // odd: take one x out
            else { x *= x; nn /= 2; }                 // even: square the base, halve the power
        }
        return n < 0 ? 1.0 / ans : ans;
    }
}
```

#### Approach 3: Recursive binary exponentiation *(not in video; fits the Recursion section)*
`pow(x, n)` = `pow(x·x, n/2)` when `n` is even, and `x · pow(x, n − 1)` when `n` is odd. The base case is `n = 0`, which returns 1.

**Complexity:** O(log n) time, O(log n) stack.

**C++**
```cpp
double powRec(double x, long long n) {
    if (n == 0) return 1.0;
    if (n % 2 == 0) return powRec(x * x, n / 2);
    return x * powRec(x, n - 1);
}
double myPowRecursive(double x, int n) {
    long long nn = n;
    return nn < 0 ? 1.0 / powRec(x, -nn) : powRec(x, nn);
}
```

**Java**
```java
class Solution {
    static double powRec(double x, long n) {
        if (n == 0) return 1.0;
        if (n % 2 == 0) return powRec(x * x, n / 2);
        return x * powRec(x, n - 1);
    }
    static double myPowRecursive(double x, int n) {
        long nn = n;
        return nn < 0 ? 1.0 / powRec(x, -nn) : powRec(x, nn);
    }
}
```

#### Key Takeaways
- Binary exponentiation: square the base on even powers and peel off one factor on odd powers, for O(log n) total.
- Always widen `n` to 64 bits before negating it.

[↑ Contents](#contents) · [Next →](#p145)

---

<a id="p145"></a>

### 2. Generate Parentheses

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Implementation Problems | Core | No | [LeetCode](https://leetcode.com/problems/generate-parentheses/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given `n` pairs of parentheses, generate **all well-formed** combinations (LeetCode 22).

```text
n = 3  ->  ["((()))", "(()())", "(())()", "()(())", "()()()"]
n = 1  ->  ["()"]
```

#### Approach 1: Brute Force — generate all 2²ⁿ strings, keep the valid ones
Recursively build every string of length `2n` from `(` and `)`. Keep a string only if its running balance never goes negative and ends at 0.

**Complexity:** O(2²ⁿ · n) time, O(n) recursion depth.

**C++**
```cpp
bool validParens(const string& s) {
    int bal = 0;
    for (char c : s) { bal += c == '(' ? 1 : -1; if (bal < 0) return false; }
    return bal == 0;
}
void genAll(string& cur, int n, vector<string>& res) {
    if ((int)cur.size() == 2 * n) { if (validParens(cur)) res.push_back(cur); return; }
    for (char c : {'(', ')'}) { cur.push_back(c); genAll(cur, n, res); cur.pop_back(); }
}
vector<string> generateParenthesisBrute(int n) {
    vector<string> res; string cur;
    genAll(cur, n, res);
    return res;
}
```

**Java**
```java
class Solution {
    static boolean validParens(String s) {
        int bal = 0;
        for (char c : s.toCharArray()) { bal += c == '(' ? 1 : -1; if (bal < 0) return false; }
        return bal == 0;
    }
    static void genAll(StringBuilder cur, int n, List<String> res) {
        if (cur.length() == 2 * n) { if (validParens(cur.toString())) res.add(cur.toString()); return; }
        for (char c : new char[]{'(', ')'}) { cur.append(c); genAll(cur, n, res); cur.deleteCharAt(cur.length() - 1); }
    }
    static List<String> generateParenthesisBrute(int n) {
        List<String> res = new ArrayList<>();
        genAll(new StringBuilder(), n, res);
        return res;
    }
}
```

#### Approach 2: Optimal — backtracking that only builds valid prefixes
Track `open` (the number of `(` used) and `close` (the number of `)` used):
- You can add `(` while `open < n`.
- You can add `)` only while `close < open`, so the prefix never becomes invalid.
- When the length reaches `2n`, record the string.

**Recursion tree for n = 2:** `""` → `"("` → (`"(("` → `"(()"` → `"(())"`) and (`"()"` → `"()("` → `"()()"`).

**Complexity:** O(4ⁿ / √n), the n-th Catalan number of results times the length of each. O(n) recursion depth.

**C++**
```cpp
void build(string& cur, int open, int close, int n, vector<string>& res) {
    if ((int)cur.size() == 2 * n) { res.push_back(cur); return; }
    if (open < n) { cur.push_back('('); build(cur, open + 1, close, n, res); cur.pop_back(); }
    if (close < open) { cur.push_back(')'); build(cur, open, close + 1, n, res); cur.pop_back(); }
}
vector<string> generateParenthesis(int n) {
    vector<string> res; string cur;
    build(cur, 0, 0, n, res);
    return res;
}
```

**Java**
```java
class Solution {
    private void build(StringBuilder cur, int open, int close, int n, List<String> res) {
        if (cur.length() == 2 * n) { res.add(cur.toString()); return; }
        if (open < n) { cur.append('('); build(cur, open + 1, close, n, res); cur.deleteCharAt(cur.length() - 1); }
        if (close < open) { cur.append(')'); build(cur, open, close + 1, n, res); cur.deleteCharAt(cur.length() - 1); }
    }
    public List<String> generateParenthesis(int n) {
        List<String> res = new ArrayList<>();
        build(new StringBuilder(), 0, 0, n, res);
        return res;
    }
}
```

#### Key Takeaways
- Prune while you generate. Constraints like `close < open` stop invalid branches early, so you don't filter at the end.
- The number of valid strings is the Catalan number Cₙ.

[↑ Contents](#contents) · [← Previous](#p144) · [Next →](#p146)

---

<a id="p146"></a>

### 3. Power Set

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Implementation Problems | Core | No | [LeetCode](https://leetcode.com/problems/subsets/) | [Watch](https://youtu.be/b7AYbpM5YrE) |

#### Problem Statement
Return the **power set** of a string or array: every subsequence (subset), including the empty one. A set of size `n` has **2ⁿ** subsets.

```text
"abc" -> "", "a", "b", "ab", "c", "ac", "bc", "abc"
```

#### Prerequisite — checking whether bit `i` of `num` is set
`num & (1 << i)` is non-zero exactly when bit `i` is 1. For example, 5 = `101`: `5 & (1 << 2) = 4`, so bit 2 is set. `5 & (1 << 1) = 0`, so bit 1 is not. Bits are indexed from the right, starting at 0.

#### Approach 1: Bit-mask enumeration (as in the video)
Write every number from `0` to `2ⁿ − 1` in binary. Read bit `i` as "pick element `i`" (1) or "skip it" (0). Each number then corresponds to exactly one subset:

| num | bits (2 1 0) | subset |
|---|---|---|
| 0 | 000 | "" |
| 1 | 001 | a |
| 2 | 010 | b |
| 3 | 011 | ab |
| 4 | 100 | c |
| 5 | 101 | ac |
| 6 | 110 | bc |
| 7 | 111 | abc |

**Complexity:** O(2ⁿ · n) time, and O(1) extra space besides the output.

**C++**
```cpp
vector<string> powerSet(string s) {
    int n = s.size();
    vector<string> res;
    for (int num = 0; num < (1 << n); num++) {
        string sub;
        for (int i = 0; i < n; i++)
            if (num & (1 << i)) sub += s[i];     // bit i set -> pick s[i]
        res.push_back(sub);
    }
    return res;
}
```

**Java**
```java
class Solution {
    static List<String> powerSet(String s) {
        int n = s.length();
        List<String> res = new ArrayList<>();
        for (int num = 0; num < (1 << n); num++) {
            StringBuilder sub = new StringBuilder();
            for (int i = 0; i < n; i++)
                if ((num & (1 << i)) != 0) sub.append(s.charAt(i));   // bit i set -> pick s[i]
            res.add(sub.toString());
        }
        return res;
    }
}
```

#### Approach 2: Recursion — pick / not pick *(not in video; it's the "previous video" referred to)*
At index `i`, either include `s[i]` or skip it, then recurse on `i + 1`. Every leaf of the recursion tree is one subset.

**Complexity:** O(2ⁿ · n) time, O(n) recursion depth.

**C++**
```cpp
void subseq(const string& s, int i, string& cur, vector<string>& res) {
    if (i == (int)s.size()) { res.push_back(cur); return; }
    cur.push_back(s[i]); subseq(s, i + 1, cur, res); cur.pop_back();   // pick
    subseq(s, i + 1, cur, res);                                         // not pick
}
vector<string> powerSetRecursive(string s) {
    vector<string> res; string cur;
    subseq(s, 0, cur, res);
    return res;
}
```

**Java**
```java
class Solution {
    static void subseq(String s, int i, StringBuilder cur, List<String> res) {
        if (i == s.length()) { res.add(cur.toString()); return; }
        cur.append(s.charAt(i)); subseq(s, i + 1, cur, res); cur.deleteCharAt(cur.length() - 1);   // pick
        subseq(s, i + 1, cur, res);                                                                 // not pick
    }
    static List<String> powerSetRecursive(String s) {
        List<String> res = new ArrayList<>();
        subseq(s, 0, new StringBuilder(), res);
        return res;
    }
}
```

#### Key Takeaways
- 2ⁿ subsets correspond one-to-one with the n-bit masks `0 … 2ⁿ − 1`.
- `1 << n` equals 2ⁿ, and `num & (1 << i)` tests bit `i`.

[↑ Contents](#contents) · [← Previous](#p145) · [Next →](#p147)

---

<a id="p147"></a>

### 4. Count Good Numbers

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Implementation Problems | Core | No | [LeetCode](https://leetcode.com/problems/count-good-numbers/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-good-numbers) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
A digit string is **good** if the digits at **even indices are even** (0, 2, 4, 6, 8, so 5 choices) and the digits at **odd indices are prime** (2, 3, 5, 7, so 4 choices). Count the good digit strings of length `n`, modulo 10⁹ + 7. `n` can be as large as 10¹⁵ (LeetCode 1922).

```text
n = 1  ->  5         ("0", "2", "4", "6", "8")
n = 4  ->  400       (5 · 4 · 5 · 4)
n = 50 ->  564908303
```

#### Intuition
Each position is independent. Out of `n` positions, `⌈n/2⌉` are even indices (5 choices each) and `⌊n/2⌋` are odd indices (4 choices each). So the answer is **5^⌈n/2⌉ · 4^⌊n/2⌋ mod (10⁹ + 7)**.

#### Approach 1: Brute Force — multiply position by position
Loop over all `n` positions, multiplying by 5 or 4. This is correct, but O(n) is far too slow when n = 10¹⁵.

**C++**
```cpp
int countGoodNumbersBrute(long long n) {
    const long long MOD = 1e9 + 7;
    long long ans = 1;
    for (long long i = 0; i < n; i++) ans = ans * (i % 2 == 0 ? 5 : 4) % MOD;
    return (int)ans;
}
```

**Java**
```java
class Solution {
    static int countGoodNumbersBrute(long n) {
        final long MOD = 1_000_000_007L;
        long ans = 1;
        for (long i = 0; i < n; i++) ans = ans * (i % 2 == 0 ? 5 : 4) % MOD;
        return (int) ans;
    }
}
```

#### Approach 2: Optimal — modular fast exponentiation (recursive)
Use binary exponentiation (Pow(x, n) from this section) with `% MOD` after every multiplication, written recursively:
- `power(b, e)` = `power(b·b mod M, e/2)` when `e` is even.
- `power(b, e)` = `b · power(b, e−1) mod M` when `e` is odd.

**Complexity:** O(log n) time, O(log n) stack.

**C++**
```cpp
const long long MODG = 1e9 + 7;
long long modPow(long long b, long long e) {
    if (e == 0) return 1;
    if (e % 2 == 0) return modPow(b * b % MODG, e / 2);
    return b * modPow(b, e - 1) % MODG;
}
int countGoodNumbers(long long n) {
    long long evenPos = (n + 1) / 2, oddPos = n / 2;
    return (int)(modPow(5, evenPos) * modPow(4, oddPos) % MODG);
}
```

**Java**
```java
class Solution {
    static final long MOD = 1_000_000_007L;
    static long modPow(long b, long e) {
        if (e == 0) return 1;
        if (e % 2 == 0) return modPow(b * b % MOD, e / 2);
        return b * modPow(b, e - 1) % MOD;
    }
    public int countGoodNumbers(long n) {
        long evenPos = (n + 1) / 2, oddPos = n / 2;
        return (int) (modPow(5, evenPos) * modPow(4, oddPos) % MOD);
    }
}
```

#### Edge Cases & Pitfalls
- Take `% MOD` after **every** product. `b * b` stays below 10¹⁸·4, which fits in a 64-bit integer only because `b < MOD` beforehand.
- With 0-indexing, position 0 is even, so the even positions number `⌈n/2⌉ = (n + 1) / 2`.

#### Key Takeaways
- For counting with independent choices, multiply the number of choices per position. A huge `n` calls for fast modular exponentiation.

[↑ Contents](#contents) · [← Previous](#p146) · [Next →](#p148)

---

<a id="p148"></a>

### 5. Reverse a Stack

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Implementation Problems | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Reverse a stack **using recursion only**: no loops over a second container, just the stack's own `push`/`pop`/`top` and the call stack.

```text
stack (top -> bottom): 4 3 2 1   ->   1 2 3 4
```

#### Approach 1: Brute Force — use an auxiliary container *(not allowed by the problem, but a useful baseline)*
Pop everything into a queue (FIFO), then push it all back. The first element popped is the first one pushed back, so it ends up at the bottom and the order is reversed.

**Complexity:** O(n) time, O(n) extra space.

**C++**
```cpp
void reverseStackQueue(stack<int>& st) {
    queue<int> q;
    while (!st.empty()) { q.push(st.top()); st.pop(); }
    while (!q.empty()) { st.push(q.front()); q.pop(); }
}
```

**Java**
```java
class Solution {
    static void reverseStackQueue(Deque<Integer> st) {
        Queue<Integer> q = new ArrayDeque<>();
        while (!st.isEmpty()) q.add(st.pop());
        while (!q.isEmpty()) st.push(q.poll());
    }
}
```

#### Approach 2: Pure recursion — reverse plus insertAtBottom
1. `reverse(st)`: pop the top `x`, reverse the remaining stack recursively, then **insert `x` at the bottom**.
2. `insertAtBottom(st, x)`: if the stack is empty, push `x`. Otherwise pop the top `y`, call `insertAtBottom(st, x)`, then push `y` back.

**Trace** for `[4 3 2 1]` (top first). `reverse` pops 4, 3, 2 and 1, recursing each time. On the way back, the elements are inserted at the bottom in the order 1, 2, 3, 4. Each insertion lands beneath the ones already there, so 4 ends up at the bottom and 1 on top.

**Complexity:** O(n²) time, because each of the `n` insertions walks the whole stack. O(n) recursion depth.

**C++**
```cpp
void insertAtBottom(stack<int>& st, int x) {
    if (st.empty()) { st.push(x); return; }
    int y = st.top(); st.pop();
    insertAtBottom(st, x);
    st.push(y);
}
void reverseStack(stack<int>& st) {
    if (st.empty()) return;
    int x = st.top(); st.pop();
    reverseStack(st);
    insertAtBottom(st, x);
}
```

**Java**
```java
class Solution {
    static void insertAtBottom(Stack<Integer> st, int x) {
        if (st.isEmpty()) { st.push(x); return; }
        int y = st.pop();
        insertAtBottom(st, x);
        st.push(y);
    }
    static void reverseStack(Stack<Integer> st) {
        if (st.isEmpty()) return;
        int x = st.pop();
        reverseStack(st);
        insertAtBottom(st, x);
    }
}
```

#### Key Takeaways
- The call stack works as hidden storage. "Hold one element in a frame, solve the rest, then put it back" is the pattern behind recursive stack reversal and recursive stack sorting.

[↑ Contents](#contents) · [← Previous](#p147) · [Next →](#p149)

---

## Subsequence Pattern Problems

<a id="p149"></a>

### 6. Check if there exists a subsequence with sum K

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Subsequence Pattern Problems | Core | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an array `arr` of **positive** integers and a target `k`, return **true** if some subsequence (not necessarily contiguous) sums to `k`.

```text
arr = [1, 2, 3, 4, 5], k = 8   ->  true   (3 + 5, or 1 + 3 + 4, ...)
arr = [4, 3, 9, 2],    k = 10  ->  false
```

#### Approach 1: Recursion — pick / not pick, with early exit
`f(i, sum)` asks whether some subsequence of `arr[i..]` reaches the remaining `sum`.
- **Base cases:** if `sum == 0`, return true. If `i == n` or `sum < 0`, return false. The `sum < 0` prune works because all values are positive.
- **Recurrence:** `f(i, sum)` = `f(i+1, sum − arr[i])` (pick) **or** `f(i+1, sum)` (not pick).
- Short-circuit: as soon as one branch returns true, stop searching.

**Complexity:** O(2ⁿ) time worst case, O(n) recursion depth.

**C++**
```cpp
bool existsRec(vector<int>& arr, int i, int sum) {
    if (sum == 0) return true;
    if (i == (int)arr.size() || sum < 0) return false;
    if (existsRec(arr, i + 1, sum - arr[i])) return true;   // pick
    return existsRec(arr, i + 1, sum);                      // not pick
}
bool checkSubsequenceSum(vector<int>& arr, int k) {
    return existsRec(arr, 0, k);
}
```

**Java**
```java
class Solution {
    static boolean existsRec(int[] arr, int i, int sum) {
        if (sum == 0) return true;
        if (i == arr.length || sum < 0) return false;
        if (existsRec(arr, i + 1, sum - arr[i])) return true;   // pick
        return existsRec(arr, i + 1, sum);                      // not pick
    }
    static boolean checkSubsequenceSum(int[] arr, int k) {
        return existsRec(arr, 0, k);
    }
}
```

#### Approach 2: DP (memoised / tabulated) — Subset Sum *(previews the DP section)*
The state `(i, sum)` repeats across branches. A table `dp[s]` ("can we make sum s?") filled with each element in turn gives O(n · k).

**Complexity:** O(n · k) time, O(k) space.

**C++**
```cpp
bool checkSubsequenceSumDP(vector<int>& arr, int k) {
    vector<bool> dp(k + 1, false);
    dp[0] = true;
    for (int x : arr)
        for (int s = k; s >= x; s--)          // backwards: each element is used at most once
            if (dp[s - x]) dp[s] = true;
    return dp[k];
}
```

**Java**
```java
class Solution {
    static boolean checkSubsequenceSumDP(int[] arr, int k) {
        boolean[] dp = new boolean[k + 1];
        dp[0] = true;
        for (int x : arr)
            for (int s = k; s >= x; s--)          // backwards: each element is used at most once
                if (dp[s - x]) dp[s] = true;
        return dp[k];
    }
}
```

#### Key Takeaways
- For "does any subsequence satisfy …", return a boolean and stop at the first true. This is the "print only one answer" recursion pattern.
- Overlapping `(i, sum)` states are the signal that DP applies.

[↑ Contents](#contents) · [← Previous](#p148) · [Next →](#p150)

---

<a id="p150"></a>

### 7. Count all subsequences with sum K

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Subsequence Pattern Problems | Core | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an array of **positive** integers and `k`, **count** the subsequences whose sum is exactly `k`.

```text
arr = [4, 9, 2, 5, 1], k = 10  ->  2     ([4, 5, 1], [9, 1])
arr = [4, 2, 10, 5, 1, 3], k = 5 -> 3    ([4, 1], [2, 3], [5])
```

#### Approach 1: Recursion — return counts from both branches
- `f(i, sum)` = `f(i+1, sum − arr[i]) + f(i+1, sum)`.
- **Base cases:**
  - `sum == 0` means one valid subsequence was found, so return 1. Because elements are positive, no extension can stay at 0.
  - `sum < 0` or `i == n` (with `sum ≠ 0`) returns 0.

**Complexity:** O(2ⁿ) time, O(n) recursion depth.

**C++**
```cpp
int countRec(vector<int>& arr, int i, int sum) {
    if (sum == 0) return 1;                       // positives only: stop here
    if (sum < 0 || i == (int)arr.size()) return 0;
    return countRec(arr, i + 1, sum - arr[i])     // pick
         + countRec(arr, i + 1, sum);             // not pick
}
int countSubsequenceWithSumK(vector<int>& arr, int k) {
    return countRec(arr, 0, k);
}
```

**Java**
```java
class Solution {
    static int countRec(int[] arr, int i, int sum) {
        if (sum == 0) return 1;                       // positives only: stop here
        if (sum < 0 || i == arr.length) return 0;
        return countRec(arr, i + 1, sum - arr[i])     // pick
             + countRec(arr, i + 1, sum);             // not pick
    }
    static int countSubsequenceWithSumK(int[] arr, int k) {
        return countRec(arr, 0, k);
    }
}
```

#### Approach 2: DP — count subsets with sum k *(previews DP)*
`dp[s]` is the number of ways to make sum `s` using the elements processed so far. Iterate `s` from high to low so each element is used at most once.

**Complexity:** O(n · k) time, O(k) space.

**C++**
```cpp
int countSubsequenceWithSumKDP(vector<int>& arr, int k) {
    vector<long long> dp(k + 1, 0);
    dp[0] = 1;
    for (int x : arr)
        for (int s = k; s >= x; s--) dp[s] += dp[s - x];
    return (int)dp[k];
}
```

**Java**
```java
class Solution {
    static int countSubsequenceWithSumKDP(int[] arr, int k) {
        long[] dp = new long[k + 1];
        dp[0] = 1;
        for (int x : arr)
            for (int s = k; s >= x; s--) dp[s] += dp[s - x];
        return (int) dp[k];
    }
}
```

#### Edge Cases & Pitfalls
- If **zeros** are allowed, returning 1 as soon as `sum == 0` misses the subsequences that also include later zeros. In that case, only count at `i == n`.

#### Key Takeaways
- To count, the base case returns 1 or 0 and you add `left + right`. This is the "count all answers" recursion pattern.

[↑ Contents](#contents) · [← Previous](#p149) · [Next →](#p151)

---

<a id="p151"></a>

### 8. Generate Binary Strings Without Consecutive 1s

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Subsequence Pattern Problems | Core | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Generate all binary strings of length `n` that contain **no two consecutive 1s**.

```text
n = 3  ->  ["000", "001", "010", "100", "101"]
n = 2  ->  ["00", "01", "10"]
```

#### Approach 1: Brute Force — all 2ⁿ strings, then filter
Generate every mask from 0 to 2ⁿ − 1. Keep it if `mask & (mask >> 1)` is 0, which means no two adjacent bits are both 1. Write each kept mask out as `n` characters, most significant bit first.

**Complexity:** O(2ⁿ · n) time.

**C++**
```cpp
vector<string> noConsecutiveOnesBrute(int n) {
    vector<string> res;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (mask & (mask >> 1)) continue;            // two adjacent 1-bits
        string s(n, '0');
        for (int i = 0; i < n; i++) if (mask & (1 << (n - 1 - i))) s[i] = '1';
        res.push_back(s);
    }
    return res;
}
```

**Java**
```java
class Solution {
    static List<String> noConsecutiveOnesBrute(int n) {
        List<String> res = new ArrayList<>();
        for (int mask = 0; mask < (1 << n); mask++) {
            if ((mask & (mask >> 1)) != 0) continue;    // two adjacent 1-bits
            char[] s = new char[n];
            for (int i = 0; i < n; i++) s[i] = (mask & (1 << (n - 1 - i))) != 0 ? '1' : '0';
            res.add(new String(s));
        }
        return res;
    }
}
```

#### Approach 2: Optimal — backtracking that never places "11"
At each position, `0` can always be placed. `1` can be placed only if the previous character isn't `1`. Every leaf is a valid string, so no work is wasted.

**Complexity:** O(F(n+2) · n), where F is the Fibonacci sequence: the number of valid strings follows a(n) = a(n−1) + a(n−2). O(n) recursion depth.

**C++**
```cpp
void genNo11(int n, string& cur, vector<string>& res) {
    if ((int)cur.size() == n) { res.push_back(cur); return; }
    cur.push_back('0'); genNo11(n, cur, res); cur.pop_back();
    if (cur.empty() || cur.back() != '1') { cur.push_back('1'); genNo11(n, cur, res); cur.pop_back(); }
}
vector<string> noConsecutiveOnes(int n) {
    vector<string> res; string cur;
    genNo11(n, cur, res);
    return res;
}
```

**Java**
```java
class Solution {
    static void genNo11(int n, StringBuilder cur, List<String> res) {
        if (cur.length() == n) { res.add(cur.toString()); return; }
        cur.append('0'); genNo11(n, cur, res); cur.deleteCharAt(cur.length() - 1);
        if (cur.length() == 0 || cur.charAt(cur.length() - 1) != '1') {
            cur.append('1'); genNo11(n, cur, res); cur.deleteCharAt(cur.length() - 1);
        }
    }
    static List<String> noConsecutiveOnes(int n) {
        List<String> res = new ArrayList<>();
        genNo11(n, new StringBuilder(), res);
        return res;
    }
}
```

#### Key Takeaways
- Put the constraint into the branching rule ("place 1 only after 0") instead of filtering at the end.
- The count of valid strings grows like the Fibonacci numbers.

[↑ Contents](#contents) · [← Previous](#p150) · [Next →](#p152)

---

## FAQs (Medium)

<a id="p152"></a>

### 9. Combination Sum

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/combination-sum/) | [Watch](https://youtu.be/OyZFFqQtu98) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Given an array of **distinct** positive integers `candidates` and a `target`, return all **unique combinations** that sum to `target`. The same number may be used **any number of times** (LeetCode 39). Two combinations are the same if they use the same numbers with the same frequencies.

```text
candidates = [2, 3, 6, 7], target = 7  ->  [[2, 2, 3], [7]]
candidates = [2, 3, 5],    target = 8  ->  [[2, 2, 2, 2], [2, 3, 3], [3, 5]]
candidates = [2],          target = 1  ->  []
```

#### Intuition — pick / not pick, where "pick" stays on the same index
At index `i` you have two choices:
- **Pick** `candidates[i]`, if it fits. Subtract it from the target and **stay at `i`**, because it may be picked again.
- **Don't pick** it. Move to `i + 1` and never consider it again.

Never moving backwards means each multiset is generated exactly once, in non-decreasing index order.

#### Approach 1: Brute Force — generate sequences, deduplicate with a set
Try every candidate at every step (index order not enforced). This produces permutations such as `[2,2,3]`, `[2,3,2]`, `[3,2,2]`. Sort each result and insert it into a `set` to remove duplicates.

**Complexity:** exponential with many duplicate branches, so slower than needed.

**C++**
```cpp
void permuteSums(vector<int>& c, int target, vector<int>& cur, set<vector<int>>& out) {
    if (target == 0) { vector<int> t = cur; sort(t.begin(), t.end()); out.insert(t); return; }
    for (int x : c)
        if (x <= target) { cur.push_back(x); permuteSums(c, target - x, cur, out); cur.pop_back(); }
}
vector<vector<int>> combinationSumBrute(vector<int>& candidates, int target) {
    set<vector<int>> out; vector<int> cur;
    permuteSums(candidates, target, cur, out);
    return vector<vector<int>>(out.begin(), out.end());
}
```

**Java**
```java
class Solution {
    static void permuteSums(int[] c, int target, List<Integer> cur, Set<List<Integer>> out) {
        if (target == 0) { List<Integer> t = new ArrayList<>(cur); Collections.sort(t); out.add(t); return; }
        for (int x : c)
            if (x <= target) { cur.add(x); permuteSums(c, target - x, cur, out); cur.remove(cur.size() - 1); }
    }
    static List<List<Integer>> combinationSumBrute(int[] candidates, int target) {
        Set<List<Integer>> out = new HashSet<>();
        permuteSums(candidates, target, new ArrayList<>(), out);
        return new ArrayList<>(out);
    }
}
```

#### Approach 2: Optimal — pick (stay) / not pick (move on)
Write `f(i, target, ds)` for the search at index `i`, with `ds` holding the numbers chosen so far.
- **Base case:** `i == n`. If `target == 0`, record `ds`. Return either way.
- **Pick:** if `candidates[i] <= target`, push it onto `ds`, call `f(i, target − candidates[i])`, then pop.
- **Not pick:** call `f(i + 1, target)`.

**Recursion sketch** `[2, 3, 6, 7]`, target 7:
- From index 0, keep picking 2: 7 → 5 → 3 → 1. Then 2 > 1, so stop picking 2.
- Back at remainder 3 with `[2, 2]`, move to index 1 and pick 3. The remainder is 0, giving **[2, 2, 3]**.
- …
- Skip 2, 3 and 6, then pick 7. The remainder is 0, giving **[7]**.

**Complexity:** O(2ᵗ · k) in the worst case, where t = target / min(candidates) bounds the depth and k is the average combination length. Recursion depth is O(t).

**C++**
```cpp
void findComb(int i, int target, vector<int>& c, vector<int>& ds, vector<vector<int>>& ans) {
    if (i == (int)c.size()) {
        if (target == 0) ans.push_back(ds);
        return;
    }
    if (c[i] <= target) {                       // pick, and stay on i (unlimited reuse)
        ds.push_back(c[i]);
        findComb(i, target - c[i], c, ds, ans);
        ds.pop_back();
    }
    findComb(i + 1, target, c, ds, ans);        // not pick -> move on
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans; vector<int> ds;
    findComb(0, target, candidates, ds, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    private void findComb(int i, int target, int[] c, List<Integer> ds, List<List<Integer>> ans) {
        if (i == c.length) {
            if (target == 0) ans.add(new ArrayList<>(ds));
            return;
        }
        if (c[i] <= target) {                       // pick, and stay on i (unlimited reuse)
            ds.add(c[i]);
            findComb(i, target - c[i], c, ds, ans);
            ds.remove(ds.size() - 1);
        }
        findComb(i + 1, target, c, ds, ans);        // not pick -> move on
    }
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> ans = new ArrayList<>();
        findComb(0, target, candidates, new ArrayList<>(), ans);
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Stay on `i` after a pick.** Moving to `i + 1` turns this into "use each element at most once", which is a different problem.
- **Copy `ds`** when recording an answer. Otherwise you store a reference that later backtracking will change.
- Base case: you could stop as soon as `target == 0`, but checking at `i == n` keeps the recursion simple and correct. The `c[i] <= target` check prevents negative targets.

#### Key Takeaways
- For unlimited reuse, the pick branch stays on the same index. To deduplicate combinations, only ever move forward.

[↑ Contents](#contents) · [← Previous](#p151) · [Next →](#p153)

---

<a id="p153"></a>

### 10. Combination Sum II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/combination-sum-ii/) | [Watch](https://youtu.be/G1fRTGRxXU8) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Given `candidates`, which **may contain duplicates**, and a `target`, return all **unique** combinations that sum to `target`. **Each element may be used at most once** (LeetCode 40).

```text
candidates = [10, 1, 2, 7, 6, 1, 5], target = 8  ->  [[1, 1, 6], [1, 2, 5], [1, 7], [2, 6]]
candidates = [2, 5, 2, 1, 2],        target = 5  ->  [[1, 2, 2], [5]]
```

#### Approach 1: Brute Force — pick / not pick plus a set
Use the plain subset recursion, where each element is used at most once. Collect every subset that sums to `target` into a `set` (after sorting the input) to drop duplicates such as the two different `[1, 7]` formed from the two 1s.

**Complexity:** O(2ⁿ · k · log(#answers)), where the log comes from the set.

**C++**
```cpp
void subsetSumsSet(int i, int target, vector<int>& c, vector<int>& ds, set<vector<int>>& out) {
    if (target == 0) { out.insert(ds); return; }
    if (i == (int)c.size() || target < 0) return;
    ds.push_back(c[i]); subsetSumsSet(i + 1, target - c[i], c, ds, out); ds.pop_back();
    subsetSumsSet(i + 1, target, c, ds, out);
}
vector<vector<int>> combinationSum2Brute(vector<int> candidates, int target) {
    sort(candidates.begin(), candidates.end());
    set<vector<int>> out; vector<int> ds;
    subsetSumsSet(0, target, candidates, ds, out);
    return vector<vector<int>>(out.begin(), out.end());
}
```

**Java**
```java
class Solution {
    static void subsetSumsSet(int i, int target, int[] c, List<Integer> ds, Set<List<Integer>> out) {
        if (target == 0) { out.add(new ArrayList<>(ds)); return; }
        if (i == c.length || target < 0) return;
        ds.add(c[i]); subsetSumsSet(i + 1, target - c[i], c, ds, out); ds.remove(ds.size() - 1);
        subsetSumsSet(i + 1, target, c, ds, out);
    }
    static List<List<Integer>> combinationSum2Brute(int[] arr, int target) {
        int[] c = arr.clone();
        Arrays.sort(c);
        Set<List<Integer>> out = new LinkedHashSet<>();
        subsetSumsSet(0, target, c, new ArrayList<>(), out);
        return new ArrayList<>(out);
    }
}
```

#### Approach 2: Optimal — sort, then "choose the next element" with a skip-duplicates rule
After sorting, each call chooses which element goes **next** in the combination, by looping `j` from `i` to `n − 1`:
- **Skip duplicates at the same level:** if `j > i` and `c[j] == c[j − 1]`, continue. Putting the same value in the same position twice would create the same combination.
- **Prune:** if `c[j] > target`, break. The array is sorted, so every later value is too large as well.
- Otherwise push `c[j]` and recurse with `f(j + 1, target − c[j])`, because each element can be used once.

Every call whose target reaches 0 records `ds`.

**Example** with sorted `[1, 1, 2, 5, 6, 7, 10]`, target 8:
- First element 1 (index 0): the next element can be 1, giving `[1,1,6]`. Or it can be 2, giving `[1,2,5]`. Or it can be 7, giving `[1,7]`.
- First element 1 again (index 1): it equals the previous 1 at the same level, so it's skipped. That avoids a second `[1,2,5]` and a second `[1,7]`.
- First element 2: gives `[2,6]`.

**Complexity:** O(2ⁿ · k) in the worst case, but the skipping and pruning cut it down a lot in practice. Recursion depth is O(n).

**C++**
```cpp
void comb2(int i, int target, vector<int>& c, vector<int>& ds, vector<vector<int>>& ans) {
    if (target == 0) { ans.push_back(ds); return; }
    for (int j = i; j < (int)c.size(); j++) {
        if (j > i && c[j] == c[j - 1]) continue;   // same value already tried at this level
        if (c[j] > target) break;                  // sorted: nothing further fits
        ds.push_back(c[j]);
        comb2(j + 1, target - c[j], c, ds, ans);   // each element at most once
        ds.pop_back();
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ans; vector<int> ds;
    comb2(0, target, candidates, ds, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    private void comb2(int i, int target, int[] c, List<Integer> ds, List<List<Integer>> ans) {
        if (target == 0) { ans.add(new ArrayList<>(ds)); return; }
        for (int j = i; j < c.length; j++) {
            if (j > i && c[j] == c[j - 1]) continue;   // same value already tried at this level
            if (c[j] > target) break;                  // sorted: nothing further fits
            ds.add(c[j]);
            comb2(j + 1, target - c[j], c, ds, ans);   // each element at most once
            ds.remove(ds.size() - 1);
        }
    }
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        Arrays.sort(candidates);
        List<List<Integer>> ans = new ArrayList<>();
        comb2(0, target, candidates, new ArrayList<>(), ans);
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- The duplicate check is `j > i`, **not** `j > 0`. The first element at each level may equal the previous value in the array. That is how `[1, 1, 6]` is allowed to use both 1s.
- **Sort first.** Both the skip and the `break` rely on sorted order.

#### Key Takeaways
- "Choose the next element from `i..n−1`, skipping equal values at the same level" is the standard way to deduplicate. It's reused in Subsets II.

[↑ Contents](#contents) · [← Previous](#p152) · [Next →](#p154)

---

<a id="p154"></a>

### 11. Subsets I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/subsets/) | [Watch](https://youtu.be/rYkfBRtMJr8) |

#### Problem Statement
Given a list of `n` integers, return the **sums of all 2ⁿ subsets** in **increasing order**. This is "Subset Sums" on GfG. The empty subset contributes sum 0.

```text
arr = [3, 1, 2]  ->  [0, 1, 2, 3, 3, 4, 5, 6]
   {} =0, {3}=3, {1}=1, {2}=2, {3,1}=4, {3,2}=5, {1,2}=3, {3,1,2}=6
```

**Note from the video:** GfG claims an expected space of O(n). That isn't achievable, because the output alone holds 2ⁿ sums.

#### Approach 1: Brute Force — power set (bit masks), sum each subset
Enumerate every mask from 0 to 2ⁿ − 1, as in the Power Set problem, and add up the chosen elements for each mask. Then sort the sums.

**Complexity:** O(2ⁿ · n + 2ⁿ log 2ⁿ) time, O(2ⁿ) space for the output.

**C++**
```cpp
vector<int> subsetSumsBits(vector<int>& arr) {
    int n = arr.size();
    vector<int> sums;
    for (int mask = 0; mask < (1 << n); mask++) {
        int s = 0;
        for (int i = 0; i < n; i++) if (mask & (1 << i)) s += arr[i];
        sums.push_back(s);
    }
    sort(sums.begin(), sums.end());
    return sums;
}
```

**Java**
```java
class Solution {
    static List<Integer> subsetSumsBits(int[] arr) {
        int n = arr.length;
        List<Integer> sums = new ArrayList<>();
        for (int mask = 0; mask < (1 << n); mask++) {
            int s = 0;
            for (int i = 0; i < n; i++) if ((mask & (1 << i)) != 0) s += arr[i];
            sums.add(s);
        }
        Collections.sort(sums);
        return sums;
    }
}
```

#### Approach 2: Optimal — pick / not pick recursion carrying the running sum
`f(index, sum)`:
- **Base case:** if `index == n`, every element has been decided, so record `sum`.
- **Pick:** call `f(index + 1, sum + arr[index])`.
- **Not pick:** call `f(index + 1, sum)`.

Sort the results at the end.

**Recursion tree** for `[3, 1, 2]`, starting at `f(0, 0)`:
- Pick 3: `f(1, 3)`.
  - Pick 1: `f(2, 4)`, which records 6 (pick 2) and 4 (skip 2).
  - Skip 1: `f(2, 3)`, which records 5 and 3.
- Skip 3: `f(1, 0)`.
  - Pick 1: `f(2, 1)`, which records 3 and 1.
  - Skip 1: `f(2, 0)`, which records 2 and 0.

There are 8 leaves in total, one per subset.

**Complexity:** O(2ⁿ) for the recursion, since there's no inner loop to sum each subset. Add O(2ⁿ log 2ⁿ) to sort. Space is O(2ⁿ) for the output, plus O(n) recursion depth.

**C++**
```cpp
void subsetSumsRec(int index, int sum, vector<int>& arr, vector<int>& res) {
    if (index == (int)arr.size()) { res.push_back(sum); return; }
    subsetSumsRec(index + 1, sum + arr[index], arr, res);   // pick
    subsetSumsRec(index + 1, sum, arr, res);                // not pick
}
vector<int> subsetSums(vector<int>& arr) {
    vector<int> res;
    subsetSumsRec(0, 0, arr, res);
    sort(res.begin(), res.end());
    return res;
}
```

**Java**
```java
class Solution {
    static void subsetSumsRec(int index, int sum, int[] arr, List<Integer> res) {
        if (index == arr.length) { res.add(sum); return; }
        subsetSumsRec(index + 1, sum + arr[index], arr, res);   // pick
        subsetSumsRec(index + 1, sum, arr, res);                // not pick
    }
    static List<Integer> subsetSums(int[] arr) {
        List<Integer> res = new ArrayList<>();
        subsetSumsRec(0, 0, arr, res);
        Collections.sort(res);
        return res;
    }
}
```

#### Key Takeaways
- Pick / not pick produces all 2ⁿ subsets. Carry the running sum so no extra pass over each subset is needed.
- In an interview, start with the power set (O(2ⁿ · n)), then remove the factor n with recursion.

[↑ Contents](#contents) · [← Previous](#p153) · [Next →](#p155)

---

<a id="p155"></a>

### 12. Subsets II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Medium) | Core | No | [LeetCode](https://leetcode.com/problems/subsets-ii/) | [Watch](https://youtu.be/RIn3gOkbhQE) |

#### Problem Statement
Given `nums`, which **may contain duplicates**, return all **subsets without duplicate subsets**, in any order (LeetCode 90).

```text
nums = [1, 2, 2]  ->  [[], [1], [1, 2], [1, 2, 2], [2], [2, 2]]
nums = [0]        ->  [[], [0]]
```

#### Approach 1: Brute Force — all 2ⁿ subsets into a set
Generate every subset with pick / not pick and insert each one, sorted, into a `set`. Duplicates disappear. Convert the set back into a list.

**Complexity:** O(2ⁿ · n) to generate, plus O(2ⁿ · n · log 2ⁿ) for the set operations. O(2ⁿ · n) space.

**C++**
```cpp
void allSubsets(int i, vector<int>& nums, vector<int>& ds, set<vector<int>>& st) {
    if (i == (int)nums.size()) { st.insert(ds); return; }
    ds.push_back(nums[i]); allSubsets(i + 1, nums, ds, st); ds.pop_back();
    allSubsets(i + 1, nums, ds, st);
}
vector<vector<int>> subsetsWithDupBrute(vector<int> nums) {
    sort(nums.begin(), nums.end());              // so equal subsets compare equal
    set<vector<int>> st; vector<int> ds;
    allSubsets(0, nums, ds, st);
    return vector<vector<int>>(st.begin(), st.end());
}
```

**Java**
```java
class Solution {
    static void allSubsets(int i, int[] nums, List<Integer> ds, Set<List<Integer>> st) {
        if (i == nums.length) { st.add(new ArrayList<>(ds)); return; }
        ds.add(nums[i]); allSubsets(i + 1, nums, ds, st); ds.remove(ds.size() - 1);
        allSubsets(i + 1, nums, ds, st);
    }
    static List<List<Integer>> subsetsWithDupBrute(int[] arr) {
        int[] nums = arr.clone();
        Arrays.sort(nums);                           // so equal subsets compare equal
        Set<List<Integer>> st = new HashSet<>();
        allSubsets(0, nums, new ArrayList<>(), st);
        return new ArrayList<>(st);
    }
}
```

#### Approach 2: Optimal — every call is a subset; skip duplicates at the same level
Think of the recursion by **subset size**:
- The first call records the empty subset, of size 0.
- At each level, a loop over `i = index … n−1` chooses **which element goes next**. That extends the current subset by one element and records it as a size `s + 1` subset.
- **Skip rule:** if `i != index` and `nums[i] == nums[i−1]`, skip it. That value was already used for this position at this level. The first index of the loop (`i == index`) is always allowed, even if it equals the previous element. That's how `[2, 2]` gets built.
- Recurse with `f(i + 1, ds + nums[i])`.
- **Sort first** so duplicates sit next to each other.

**Trace** `[1, 2, 2]`:
- `f(0, [])` records `[]`.
  - Choose 1: `f(1, [1])` records `[1]`.
    - Choose 2: `f(2, [1,2])` records `[1,2]`.
      - Choose 2: `[1,2,2]`.
    - Choose the second 2: skipped.
  - Choose 2: `f(2, [2])` records `[2]`.
    - Choose 2: `[2,2]`.
  - Choose the second 2: skipped.

There's no explicit base case. When `index == n`, the loop simply doesn't run.

**Complexity:** O(2ⁿ · n) time, because each subset costs up to n to copy into the answer. O(2ⁿ · k) space for the output, plus O(n) recursion depth.

**C++**
```cpp
void findSubsets(int index, vector<int>& nums, vector<int>& ds, vector<vector<int>>& ans) {
    ans.push_back(ds);                                     // every call is a valid subset
    for (int i = index; i < (int)nums.size(); i++) {
        if (i != index && nums[i] == nums[i - 1]) continue;    // duplicate at this level
        ds.push_back(nums[i]);
        findSubsets(i + 1, nums, ds, ans);
        ds.pop_back();
    }
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans; vector<int> ds;
    findSubsets(0, nums, ds, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    private void findSubsets(int index, int[] nums, List<Integer> ds, List<List<Integer>> ans) {
        ans.add(new ArrayList<>(ds));                              // every call is a valid subset
        for (int i = index; i < nums.length; i++) {
            if (i != index && nums[i] == nums[i - 1]) continue;    // duplicate at this level
            ds.add(nums[i]);
            findSubsets(i + 1, nums, ds, ans);
            ds.remove(ds.size() - 1);
        }
    }
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> ans = new ArrayList<>();
        findSubsets(0, nums, new ArrayList<>(), ans);
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Sorting is essential.** Without it, duplicates aren't adjacent and the skip rule misses them.
- **Remove after recursing** (`pop_back`) so the next iteration starts from the right state.

#### Key Takeaways
- The same skip rule as Combination Sum II, `i > start && a[i] == a[i−1]`, deduplicates any "choose the next element" recursion.
- Recording at every call, not only at leaves, lists the subsets level by level, by size.

[↑ Contents](#contents) · [← Previous](#p154) · [Next →](#p156)

---

<a id="p156"></a>

### 13. Combination Sum III

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Medium) | Pro | No | [LeetCode](https://leetcode.com/problems/combination-sum-iii/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Find all combinations of **`k` distinct numbers from 1–9** that sum to `n`. Each number is used at most once (LeetCode 216).

```text
k = 3, n = 7  ->  [[1, 2, 4]]
k = 3, n = 9  ->  [[1, 2, 6], [1, 3, 5], [2, 3, 4]]
k = 4, n = 1  ->  []
```

#### Approach 1: Brute Force — all 2⁹ subsets of 1..9 via bit masks
Enumerate the 512 masks. Keep a mask if it has exactly `k` bits set and the chosen numbers sum to `n`.

**Complexity:** O(2⁹ · 9), which is constant.

**C++**
```cpp
vector<vector<int>> combinationSum3Brute(int k, int n) {
    vector<vector<int>> ans;
    for (int mask = 0; mask < (1 << 9); mask++) {
        if (__builtin_popcount(mask) != k) continue;
        vector<int> v; int s = 0;
        for (int d = 1; d <= 9; d++) if (mask & (1 << (d - 1))) { v.push_back(d); s += d; }
        if (s == n) ans.push_back(v);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> combinationSum3Brute(int k, int n) {
        List<List<Integer>> ans = new ArrayList<>();
        for (int mask = 0; mask < (1 << 9); mask++) {
            if (Integer.bitCount(mask) != k) continue;
            List<Integer> v = new ArrayList<>(); int s = 0;
            for (int d = 1; d <= 9; d++) if ((mask & (1 << (d - 1))) != 0) { v.add(d); s += d; }
            if (s == n) ans.add(v);
        }
        return ans;
    }
}
```

#### Approach 2: Backtracking with pruning
Choose the next number from `start … 9`, increasing so no combination repeats. Two prunes apply:
- Stop if the current number exceeds the remaining sum. Every later number is larger.
- Stop when `ds` already has `k` numbers.

Record `ds` when it has exactly `k` numbers and the remainder is 0.

**Complexity:** at most C(9, k) leaves, so effectively constant. Recursion depth ≤ k.

**C++**
```cpp
void comb3(int start, int k, int remain, vector<int>& ds, vector<vector<int>>& ans) {
    if ((int)ds.size() == k) { if (remain == 0) ans.push_back(ds); return; }
    for (int d = start; d <= 9 && d <= remain; d++) {
        ds.push_back(d);
        comb3(d + 1, k, remain - d, ds, ans);
        ds.pop_back();
    }
}
vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> ans; vector<int> ds;
    comb3(1, k, n, ds, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    private void comb3(int start, int k, int remain, List<Integer> ds, List<List<Integer>> ans) {
        if (ds.size() == k) { if (remain == 0) ans.add(new ArrayList<>(ds)); return; }
        for (int d = start; d <= 9 && d <= remain; d++) {
            ds.add(d);
            comb3(d + 1, k, remain - d, ds, ans);
            ds.remove(ds.size() - 1);
        }
    }
    public List<List<Integer>> combinationSum3(int k, int n) {
        List<List<Integer>> ans = new ArrayList<>();
        comb3(1, k, n, new ArrayList<>(), ans);
        return ans;
    }
}
```

#### Key Takeaways
- This is Combination Sum II over the fixed, sorted, duplicate-free set 1..9, with an added size constraint `k`.

[↑ Contents](#contents) · [← Previous](#p155) · [Next →](#p157)

---

## Hard

<a id="p157"></a>

### 14. Letter Combinations of a Phone Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › Hard | Pro | No | [LeetCode](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a string of digits `2–9`, return all letter combinations it could represent on a phone keypad (LeetCode 17): 2 → abc, 3 → def, 4 → ghi, 5 → jkl, 6 → mno, 7 → pqrs, 8 → tuv, 9 → wxyz.

```text
"23" -> ["ad","ae","af","bd","be","bf","cd","ce","cf"]
""   -> []
"2"  -> ["a","b","c"]
```

#### Approach 1: Iterative BFS — extend the partial results one digit at a time
Start with `[""]`. For each digit, replace the list with every existing string extended by each of that digit's letters.

**Complexity:** O(4ⁿ · n) time and space, since a digit maps to at most 4 letters.

**C++**
```cpp
vector<string> letterCombinationsIter(string digits) {
    if (digits.empty()) return {};
    vector<string> mp = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res = {""};
    for (char d : digits) {
        vector<string> next;
        for (auto& s : res) for (char c : mp[d - '0']) next.push_back(s + c);
        res = next;
    }
    return res;
}
```

**Java**
```java
class Solution {
    static List<String> letterCombinationsIter(String digits) {
        if (digits.isEmpty()) return new ArrayList<>();
        String[] mp = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        List<String> res = new ArrayList<>(List.of(""));
        for (char d : digits.toCharArray()) {
            List<String> next = new ArrayList<>();
            for (String s : res) for (char c : mp[d - '0'].toCharArray()) next.add(s + c);
            res = next;
        }
        return res;
    }
}
```

#### Approach 2: Recursion / backtracking
`f(i, cur)`: if `i == n`, record `cur`. Otherwise, for each letter of `digits[i]`, append it, recurse with `f(i + 1)`, and remove it again.

**Complexity:** O(4ⁿ · n) time, O(n) recursion depth plus the output.

**C++**
```cpp
void letters(const string& digits, int i, string& cur, vector<string>& mp, vector<string>& res) {
    if (i == (int)digits.size()) { res.push_back(cur); return; }
    for (char c : mp[digits[i] - '0']) {
        cur.push_back(c);
        letters(digits, i + 1, cur, mp, res);
        cur.pop_back();
    }
}
vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    vector<string> mp = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res; string cur;
    letters(digits, 0, cur, mp, res);
    return res;
}
```

**Java**
```java
class Solution {
    private static final String[] MP = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    private void letters(String digits, int i, StringBuilder cur, List<String> res) {
        if (i == digits.length()) { res.add(cur.toString()); return; }
        for (char c : MP[digits.charAt(i) - '0'].toCharArray()) {
            cur.append(c);
            letters(digits, i + 1, cur, res);
            cur.deleteCharAt(cur.length() - 1);
        }
    }
    public List<String> letterCombinations(String digits) {
        List<String> res = new ArrayList<>();
        if (digits.isEmpty()) return res;
        letters(digits, 0, new StringBuilder(), res);
        return res;
    }
}
```

#### Key Takeaways
- This is a Cartesian product over the choices for each digit. Recursion depth equals the number of digits, and the branching factor is 3 or 4.
- An empty input returns `[]`, not `[""]`.

[↑ Contents](#contents) · [← Previous](#p156) · [Next →](#p158)

---

## FAQs (Hard)

<a id="p158"></a>

### 15. Palindrome partitioning

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/palindrome-partitioning/) | [Watch](https://youtu.be/_H8V5hJUGd0) |

> **About the linked video:** the sheet links Striver's *DP-53 Palindrome Partitioning II* lecture, which finds the **minimum number of cuts**. The sheet problem itself is LeetCode 131, which asks for **all** partitions. Approaches 1–2 below cover LeetCode 131 *(not in video; the video only mentions that Part I is in the recursion series)*. Approach 3 is the video's content.

#### Problem Statement
Partition a string `s` so that **every substring of the partition is a palindrome**. Return **all** such partitions (LeetCode 131).

```text
s = "aab"  ->  [["a","a","b"], ["aa","b"]]
s = "a"    ->  [["a"]]
```

#### Approach 1: Brute Force — try every cut pattern (bit mask), keep the all-palindrome ones *(not in video)*
A string of length `n` has `n − 1` gaps, and each gap is either cut or not. That gives 2ⁿ⁻¹ cut patterns. For each pattern, split the string and check that every piece is a palindrome.

**Complexity:** O(2ⁿ · n) time.

**C++**
```cpp
bool isPalin(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}
vector<vector<string>> partitionBrute(string s) {
    int n = s.size();
    vector<vector<string>> res;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {     // bit i set -> cut after s[i]
        vector<string> parts; int start = 0; bool ok = true;
        for (int i = 0; i < n && ok; i++)
            if (i == n - 1 || (mask & (1 << i))) {
                if (!isPalin(s, start, i)) ok = false;
                else parts.push_back(s.substr(start, i - start + 1));
                start = i + 1;
            }
        if (ok) res.push_back(parts);
    }
    return res;
}
```

**Java**
```java
class Solution {
    static boolean isPalin(String s, int l, int r) {
        while (l < r) if (s.charAt(l++) != s.charAt(r--)) return false;
        return true;
    }
    static List<List<String>> partitionBrute(String s) {
        int n = s.length();
        List<List<String>> res = new ArrayList<>();
        for (int mask = 0; mask < (1 << (n - 1)); mask++) {     // bit i set -> cut after s[i]
            List<String> parts = new ArrayList<>(); int start = 0; boolean ok = true;
            for (int i = 0; i < n && ok; i++)
                if (i == n - 1 || (mask & (1 << i)) != 0) {
                    if (!isPalin(s, start, i)) ok = false;
                    else parts.add(s.substring(start, i + 1));
                    start = i + 1;
                }
            if (ok) res.add(parts);
        }
        return res;
    }
}
```

#### Approach 2: Backtracking — front partition *(not in video)*
`f(index)`: try every end position `i` from `index` to `n−1`. If `s[index..i]` is a palindrome, add it to the current path and recurse on `f(i + 1)`. When `index == n`, the path is a complete partition, so record it.

**Complexity:** O(2ⁿ · n) in the worst case, for example "aaaa…", where every split works. O(n) recursion depth.

**C++**
```cpp
bool isPalin(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}
void partHelper(int index, const string& s, vector<string>& path, vector<vector<string>>& res) {
    if (index == (int)s.size()) { res.push_back(path); return; }
    for (int i = index; i < (int)s.size(); i++)
        if (isPalin(s, index, i)) {
            path.push_back(s.substr(index, i - index + 1));
            partHelper(i + 1, s, path, res);
            path.pop_back();
        }
}
vector<vector<string>> partition(string s) {
    vector<vector<string>> res; vector<string> path;
    partHelper(0, s, path, res);
    return res;
}
```

**Java**
```java
class Solution {
    static boolean isPalin(String s, int l, int r) {
        while (l < r) if (s.charAt(l++) != s.charAt(r--)) return false;
        return true;
    }
    private void partHelper(int index, String s, List<String> path, List<List<String>> res) {
        if (index == s.length()) { res.add(new ArrayList<>(path)); return; }
        for (int i = index; i < s.length(); i++)
            if (isPalin(s, index, i)) {
                path.add(s.substring(index, i + 1));
                partHelper(i + 1, s, path, res);
                path.remove(path.size() - 1);
            }
    }
    public List<List<String>> partition(String s) {
        List<List<String>> res = new ArrayList<>();
        partHelper(0, s, new ArrayList<>(), res);
        return res;
    }
}
```

#### Approach 3: The video's problem — **minimum cuts** (Palindrome Partitioning II, LeetCode 132)
The goal here is the **fewest cuts** such that every piece is a palindrome. An answer always exists, because `n − 1` cuts leave single characters, which are all palindromes.

```text
"aab"           ->  1     ("aa" | "b")
"bababcbadcede" ->  4     ("bab" | "abcba" | "d" | "c" | "ede")
```

**Front partition (as taught):**
- `f(i)` is the minimum number of palindromic pieces for the suffix `s[i..]`.
- At each start `i`, try every `j` from `i` to `n−1`. If `s[i..j]` is a palindrome, that's 1 piece plus the best for the rest: `cost = 1 + f(j + 1)`. Take the minimum over all `j`.
- **Base case:** `f(n) = 0`.
- **Answer:** `f(0) − 1`. The recursion also "cuts" after the last piece, so the number of cuts is one less than the number of pieces.

**Memoisation:** only `i` changes, so a 1-D `dp[n]` is enough. That gives O(n²) states × transitions (times the palindrome check), plus O(n) for the dp array and O(n) stack.

**Tabulation:**
1. Set `dp[n] = 0`.
2. For `i = n−1` down to 0, compute the same minimum.
3. Return `dp[0] − 1`.

Note that `dp` needs `n + 1` entries: the video hit a runtime error until it was resized.

**C++**
```cpp
bool isPalin(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}
// Memoization
int minCutsRec(int i, const string& s, vector<int>& dp) {
    int n = s.size();
    if (i == n) return 0;
    if (dp[i] != -1) return dp[i];
    int best = INT_MAX;
    for (int j = i; j < n; j++)
        if (isPalin(s, i, j)) best = min(best, 1 + minCutsRec(j + 1, s, dp));
    return dp[i] = best;
}
int minCutMemo(string s) {
    vector<int> dp(s.size(), -1);
    return minCutsRec(0, s, dp) - 1;
}

// Tabulation
int minCut(string s) {
    int n = s.size();
    vector<int> dp(n + 1, 0);                       // dp[n] = 0 is the base case
    for (int i = n - 1; i >= 0; i--) {
        int best = INT_MAX;
        for (int j = i; j < n; j++)
            if (isPalin(s, i, j)) best = min(best, 1 + dp[j + 1]);
        dp[i] = best;
    }
    return dp[0] - 1;
}
```

**Java**
```java
class Solution {
    static boolean isPalin(String s, int l, int r) {
        while (l < r) if (s.charAt(l++) != s.charAt(r--)) return false;
        return true;
    }
    // Memoization
    static int minCutsRec(int i, String s, int[] dp) {
        int n = s.length();
        if (i == n) return 0;
        if (dp[i] != -1) return dp[i];
        int best = Integer.MAX_VALUE;
        for (int j = i; j < n; j++)
            if (isPalin(s, i, j)) best = Math.min(best, 1 + minCutsRec(j + 1, s, dp));
        return dp[i] = best;
    }
    static int minCutMemo(String s) {
        int[] dp = new int[s.length()];
        Arrays.fill(dp, -1);
        return minCutsRec(0, s, dp) - 1;
    }
    // Tabulation
    public int minCut(String s) {
        int n = s.length();
        int[] dp = new int[n + 1];                      // dp[n] = 0 is the base case
        for (int i = n - 1; i >= 0; i--) {
            int best = Integer.MAX_VALUE;
            for (int j = i; j < n; j++)
                if (isPalin(s, i, j)) best = Math.min(best, 1 + dp[j + 1]);
            dp[i] = best;
        }
        return dp[0] - 1;
    }
}
```

#### Edge Cases & Pitfalls
- In Approach 3, subtract 1 at the end, because the last piece needs no cut after it.
- **Palindrome checks:** precomputing an `isPal[i][j]` table makes each check O(1), bringing the min-cut DP down to O(n²) overall. *(not in video)*

#### Key Takeaways
- For "partition into valid pieces", use a **front partition**: choose where the first piece ends, then recurse on the rest.
- Listing all partitions calls for backtracking. A minimum or count over the partitions calls for a 1-D DP on the start index.

[↑ Contents](#contents) · [← Previous](#p157) · [Next →](#p159)

---

<a id="p159"></a>

### 16. Word Search

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/word-search/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an `m × n` grid of letters and a `word`, return true if the word can be formed from **sequentially adjacent** cells (up, down, left or right), using each cell **at most once** (LeetCode 79).

```text
board = [["A","B","C","E"],
         ["S","F","C","S"],
         ["A","D","E","E"]]
word = "ABCCED" -> true,  "SEE" -> true,  "ABCB" -> false
```

#### Approach 1: Brute Force — DFS from every cell with a separate visited matrix
For each cell that matches `word[0]`, run a DFS that keeps a `visited` matrix. At step `k`, try the 4 neighbours that are unvisited and match `word[k]`.

**Complexity:** O(m · n · 4ᴸ) time, where L is the word length. O(m · n) space for `visited`, plus O(L) stack.

**C++**
```cpp
bool dfsVis(vector<vector<char>>& b, const string& w, int k, int r, int c, vector<vector<bool>>& vis) {
    if (k == (int)w.size()) return true;
    if (r < 0 || c < 0 || r >= (int)b.size() || c >= (int)b[0].size() || vis[r][c] || b[r][c] != w[k]) return false;
    vis[r][c] = true;
    bool found = dfsVis(b, w, k + 1, r + 1, c, vis) || dfsVis(b, w, k + 1, r - 1, c, vis) ||
                 dfsVis(b, w, k + 1, r, c + 1, vis) || dfsVis(b, w, k + 1, r, c - 1, vis);
    vis[r][c] = false;
    return found;
}
bool existVisited(vector<vector<char>>& board, string word) {
    int m = board.size(), n = board[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (dfsVis(board, word, 0, i, j, vis)) return true;
    return false;
}
```

**Java**
```java
class Solution {
    static boolean dfsVis(char[][] b, String w, int k, int r, int c, boolean[][] vis) {
        if (k == w.length()) return true;
        if (r < 0 || c < 0 || r >= b.length || c >= b[0].length || vis[r][c] || b[r][c] != w.charAt(k)) return false;
        vis[r][c] = true;
        boolean found = dfsVis(b, w, k + 1, r + 1, c, vis) || dfsVis(b, w, k + 1, r - 1, c, vis) ||
                        dfsVis(b, w, k + 1, r, c + 1, vis) || dfsVis(b, w, k + 1, r, c - 1, vis);
        vis[r][c] = false;
        return found;
    }
    static boolean existVisited(char[][] board, String word) {
        boolean[][] vis = new boolean[board.length][board[0].length];
        for (int i = 0; i < board.length; i++)
            for (int j = 0; j < board[0].length; j++)
                if (dfsVis(board, word, 0, i, j, vis)) return true;
        return false;
    }
}
```

#### Approach 2: Optimal — in-place marking (O(1) extra space)
Mark a cell as used by temporarily overwriting it with `'#'`, and restore it when backtracking. This avoids the `visited` matrix. Two cheap prunes help: check `word[0]` before starting a DFS, and return false straight away if the word is longer than `m·n`.

**Complexity:** O(m · n · 3ᴸ) time, because after the first step you never go back to the cell you came from. O(L) stack.

**C++**
```cpp
bool dfs(vector<vector<char>>& b, const string& w, int k, int r, int c) {
    if (k == (int)w.size()) return true;
    if (r < 0 || c < 0 || r >= (int)b.size() || c >= (int)b[0].size() || b[r][c] != w[k]) return false;
    char saved = b[r][c];
    b[r][c] = '#';                                   // mark as used
    bool found = dfs(b, w, k + 1, r + 1, c) || dfs(b, w, k + 1, r - 1, c) ||
                 dfs(b, w, k + 1, r, c + 1) || dfs(b, w, k + 1, r, c - 1);
    b[r][c] = saved;                                 // backtrack
    return found;
}
bool exist(vector<vector<char>>& board, string word) {
    int m = board.size(), n = board[0].size();
    if ((int)word.size() > m * n) return false;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == word[0] && dfs(board, word, 0, i, j)) return true;
    return false;
}
```

**Java**
```java
class Solution {
    private boolean dfs(char[][] b, String w, int k, int r, int c) {
        if (k == w.length()) return true;
        if (r < 0 || c < 0 || r >= b.length || c >= b[0].length || b[r][c] != w.charAt(k)) return false;
        char saved = b[r][c];
        b[r][c] = '#';                                   // mark as used
        boolean found = dfs(b, w, k + 1, r + 1, c) || dfs(b, w, k + 1, r - 1, c) ||
                        dfs(b, w, k + 1, r, c + 1) || dfs(b, w, k + 1, r, c - 1);
        b[r][c] = saved;                                 // backtrack
        return found;
    }
    public boolean exist(char[][] board, String word) {
        int m = board.length, n = board[0].length;
        if (word.length() > m * n) return false;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == word.charAt(0) && dfs(board, word, 0, i, j)) return true;
        return false;
    }
}
```

#### Key Takeaways
- Grid backtracking follows one pattern: mark the cell, explore the 4 directions, then unmark it. Short-circuit with `||` so the search stops at the first success.

[↑ Contents](#contents) · [← Previous](#p158) · [Next →](#p160)

---

<a id="p160"></a>

### 17. N Queen

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/n-queens/) | [Watch](https://youtu.be/i05Ju7AftcM) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Place `n` queens on an `n × n` chessboard so that **no two attack each other**: no two share a row, a column or a diagonal. Return all distinct boards (LeetCode 51).

```text
n = 4 -> [".Q..","...Q","Q...","..Q."], ["..Q.","Q...","...Q",".Q.."]
n = 1 -> ["Q"]
```

#### Intuition
Place the queens **column by column**, with exactly one queen per column. For column `col`, try each row. Keep a placement if it's safe, recurse to `col + 1`, then remove it and backtrack. Reaching `col == n` means all queens are placed, so record the board.

The queens to the right of `col` haven't been placed yet. So a safety check only needs to look **left**: along the same row, the upper-left diagonal and the lower-left diagonal.

#### Approach 1: Backtracking with an O(n) safety check
`isSafe(row, col)` walks left along the row, up-left along one diagonal and down-left along the other, looking for a `Q`.

**Complexity:** O(n! · n) time, since there are about n! placements and each check is O(n). O(n²) space for the board.

**C++**
```cpp
bool isSafe(int row, int col, vector<string>& board, int n) {
    for (int r = row, c = col; r >= 0 && c >= 0; r--, c--) if (board[r][c] == 'Q') return false;  // upper-left
    for (int c = col; c >= 0; c--) if (board[row][c] == 'Q') return false;                         // left
    for (int r = row, c = col; r < n && c >= 0; r++, c--) if (board[r][c] == 'Q') return false;    // lower-left
    return true;
}
void solveQ(int col, vector<string>& board, vector<vector<string>>& ans, int n) {
    if (col == n) { ans.push_back(board); return; }
    for (int row = 0; row < n; row++)
        if (isSafe(row, col, board, n)) {
            board[row][col] = 'Q';
            solveQ(col + 1, board, ans, n);
            board[row][col] = '.';
        }
}
vector<vector<string>> solveNQueensBasic(int n) {
    vector<vector<string>> ans;
    vector<string> board(n, string(n, '.'));
    solveQ(0, board, ans, n);
    return ans;
}
```

**Java**
```java
class Solution {
    static boolean isSafe(int row, int col, char[][] board, int n) {
        for (int r = row, c = col; r >= 0 && c >= 0; r--, c--) if (board[r][c] == 'Q') return false;  // upper-left
        for (int c = col; c >= 0; c--) if (board[row][c] == 'Q') return false;                         // left
        for (int r = row, c = col; r < n && c >= 0; r++, c--) if (board[r][c] == 'Q') return false;    // lower-left
        return true;
    }
    static List<String> toList(char[][] board) {
        List<String> res = new ArrayList<>();
        for (char[] r : board) res.add(new String(r));
        return res;
    }
    static void solveQ(int col, char[][] board, List<List<String>> ans, int n) {
        if (col == n) { ans.add(toList(board)); return; }
        for (int row = 0; row < n; row++)
            if (isSafe(row, col, board, n)) {
                board[row][col] = 'Q';
                solveQ(col + 1, board, ans, n);
                board[row][col] = '.';
            }
    }
    static List<List<String>> solveNQueensBasic(int n) {
        char[][] board = new char[n][n];
        for (char[] r : board) Arrays.fill(r, '.');
        List<List<String>> ans = new ArrayList<>();
        solveQ(0, board, ans, n);
        return ans;
    }
}
```

#### Approach 2: Optimal — O(1) safety check with hashing arrays
Three boolean arrays record which lines are already occupied:
- `leftRow[row]`: some queen is in this row.
- `lowerDiag[row + col]` (size 2n−1): the "/" anti-diagonals. Every cell on one has the same `row + col`.
- `upperDiag[n − 1 + col − row]` (size 2n−1): the "\" diagonals. Every cell on one has the same `col − row`, shifted by `n − 1` so the index is never negative.

A cell is safe if all three flags are false. Set the flags when placing a queen and clear them when backtracking.

**Complexity:** O(n!) time, O(n) for the arrays plus the board.

**C++**
```cpp
void solveFast(int col, vector<string>& board, vector<vector<string>>& ans,
               vector<int>& leftRow, vector<int>& lowerDiag, vector<int>& upperDiag, int n) {
    if (col == n) { ans.push_back(board); return; }
    for (int row = 0; row < n; row++) {
        if (!leftRow[row] && !lowerDiag[row + col] && !upperDiag[n - 1 + col - row]) {
            board[row][col] = 'Q';
            leftRow[row] = lowerDiag[row + col] = upperDiag[n - 1 + col - row] = 1;
            solveFast(col + 1, board, ans, leftRow, lowerDiag, upperDiag, n);
            board[row][col] = '.';
            leftRow[row] = lowerDiag[row + col] = upperDiag[n - 1 + col - row] = 0;
        }
    }
}
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<string> board(n, string(n, '.'));
    vector<int> leftRow(n, 0), lowerDiag(2 * n - 1, 0), upperDiag(2 * n - 1, 0);
    solveFast(0, board, ans, leftRow, lowerDiag, upperDiag, n);
    return ans;
}
```

**Java**
```java
class Solution {
    private void solveFast(int col, char[][] board, List<List<String>> ans,
                           boolean[] leftRow, boolean[] lowerDiag, boolean[] upperDiag, int n) {
        if (col == n) {
            List<String> b = new ArrayList<>();
            for (char[] r : board) b.add(new String(r));
            ans.add(b);
            return;
        }
        for (int row = 0; row < n; row++) {
            if (!leftRow[row] && !lowerDiag[row + col] && !upperDiag[n - 1 + col - row]) {
                board[row][col] = 'Q';
                leftRow[row] = lowerDiag[row + col] = upperDiag[n - 1 + col - row] = true;
                solveFast(col + 1, board, ans, leftRow, lowerDiag, upperDiag, n);
                board[row][col] = '.';
                leftRow[row] = lowerDiag[row + col] = upperDiag[n - 1 + col - row] = false;
            }
        }
    }
    public List<List<String>> solveNQueens(int n) {
        char[][] board = new char[n][n];
        for (char[] r : board) Arrays.fill(r, '.');
        List<List<String>> ans = new ArrayList<>();
        solveFast(0, board, ans, new boolean[n], new boolean[2 * n - 1], new boolean[2 * n - 1], n);
        return ans;
    }
}
```

#### Key Takeaways
- Placing one queen per column removes column checks. Diagonals are identified by `row + col` and `row − col`.
- Hash arrays turn an O(n) safety check into O(1). The same trick is used in Sudoku.

[↑ Contents](#contents) · [← Previous](#p159) · [Next →](#p161)

---

<a id="p161"></a>

### 18. Rat in a Maze

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Hard) | Pro | Yes | — | [Watch](https://youtu.be/bLGZhJlt4y0) |

> **Video available, but its auto-captions could not be used** (YouTube produced only a garbled, wrongly-detected-language track). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
A rat starts at `(0, 0)` in an `n × n` binary maze, where 1 means open and 0 means blocked. It wants to reach `(n−1, n−1)`, moving **U, D, L or R** and visiting no cell twice. Return **all paths** as direction strings, in **lexicographic order**. Return an empty list if there are none.

```text
maze = [[1,0,0,0],
        [1,1,0,1],
        [1,1,0,0],
        [0,1,1,1]]   ->  ["DDRDRR", "DRDDRR"]
```

#### Approach 1: Backtracking with explicit direction branches
Explore in **alphabetical order, D → L → R → U**. That way the paths are generated already sorted. Mark a cell as visited before going deeper and unmark it on return. When `(n−1, n−1)` is reached, record the path.

**Complexity:** O(4^(n²)) in the worst case. O(n²) for `visited`, plus O(n²) recursion depth.

**C++**
```cpp
void ratSolve(int r, int c, vector<vector<int>>& m, int n, string& path, vector<string>& ans, vector<vector<int>>& vis) {
    if (r == n - 1 && c == n - 1) { ans.push_back(path); return; }
    vis[r][c] = 1;
    if (r + 1 < n && !vis[r + 1][c] && m[r + 1][c] == 1) { path += 'D'; ratSolve(r + 1, c, m, n, path, ans, vis); path.pop_back(); }
    if (c - 1 >= 0 && !vis[r][c - 1] && m[r][c - 1] == 1) { path += 'L'; ratSolve(r, c - 1, m, n, path, ans, vis); path.pop_back(); }
    if (c + 1 < n && !vis[r][c + 1] && m[r][c + 1] == 1) { path += 'R'; ratSolve(r, c + 1, m, n, path, ans, vis); path.pop_back(); }
    if (r - 1 >= 0 && !vis[r - 1][c] && m[r - 1][c] == 1) { path += 'U'; ratSolve(r - 1, c, m, n, path, ans, vis); path.pop_back(); }
    vis[r][c] = 0;
}
vector<string> findPathExplicit(vector<vector<int>>& m) {
    int n = m.size();
    vector<string> ans;
    if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return ans;
    vector<vector<int>> vis(n, vector<int>(n, 0));
    string path;
    ratSolve(0, 0, m, n, path, ans, vis);
    return ans;
}
```

**Java**
```java
class Solution {
    static void ratSolve(int r, int c, int[][] m, int n, StringBuilder path, List<String> ans, boolean[][] vis) {
        if (r == n - 1 && c == n - 1) { ans.add(path.toString()); return; }
        vis[r][c] = true;
        if (r + 1 < n && !vis[r + 1][c] && m[r + 1][c] == 1) { path.append('D'); ratSolve(r + 1, c, m, n, path, ans, vis); path.deleteCharAt(path.length() - 1); }
        if (c - 1 >= 0 && !vis[r][c - 1] && m[r][c - 1] == 1) { path.append('L'); ratSolve(r, c - 1, m, n, path, ans, vis); path.deleteCharAt(path.length() - 1); }
        if (c + 1 < n && !vis[r][c + 1] && m[r][c + 1] == 1) { path.append('R'); ratSolve(r, c + 1, m, n, path, ans, vis); path.deleteCharAt(path.length() - 1); }
        if (r - 1 >= 0 && !vis[r - 1][c] && m[r - 1][c] == 1) { path.append('U'); ratSolve(r - 1, c, m, n, path, ans, vis); path.deleteCharAt(path.length() - 1); }
        vis[r][c] = false;
    }
    static List<String> findPathExplicit(int[][] m) {
        int n = m.length;
        List<String> ans = new ArrayList<>();
        if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return ans;
        ratSolve(0, 0, m, n, new StringBuilder(), ans, new boolean[n][n]);
        return ans;
    }
}
```

#### Approach 2: Same backtracking, compact with direction arrays
Store the four moves in arrays ordered D, L, R, U, as `di = {+1, 0, 0, −1}`, `dj = {0, −1, +1, 0}` and `dir = "DLRU"`. A single loop replaces the four `if` blocks. The complexity is the same.

**C++**
```cpp
void ratLoop(int r, int c, vector<vector<int>>& m, int n, string& path, vector<string>& ans, vector<vector<int>>& vis) {
    static const int di[4] = {1, 0, 0, -1}, dj[4] = {0, -1, 1, 0};
    static const char dir[4] = {'D', 'L', 'R', 'U'};
    if (r == n - 1 && c == n - 1) { ans.push_back(path); return; }
    vis[r][c] = 1;
    for (int k = 0; k < 4; k++) {
        int nr = r + di[k], nc = c + dj[k];
        if (nr >= 0 && nc >= 0 && nr < n && nc < n && !vis[nr][nc] && m[nr][nc] == 1) {
            path.push_back(dir[k]);
            ratLoop(nr, nc, m, n, path, ans, vis);
            path.pop_back();
        }
    }
    vis[r][c] = 0;
}
vector<string> findPath(vector<vector<int>>& m) {
    int n = m.size();
    vector<string> ans;
    if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return ans;
    vector<vector<int>> vis(n, vector<int>(n, 0));
    string path;
    ratLoop(0, 0, m, n, path, ans, vis);
    return ans;
}
```

**Java**
```java
class Solution {
    private static final int[] DI = {1, 0, 0, -1}, DJ = {0, -1, 1, 0};
    private static final char[] DIR = {'D', 'L', 'R', 'U'};
    static void ratLoop(int r, int c, int[][] m, int n, StringBuilder path, List<String> ans, boolean[][] vis) {
        if (r == n - 1 && c == n - 1) { ans.add(path.toString()); return; }
        vis[r][c] = true;
        for (int k = 0; k < 4; k++) {
            int nr = r + DI[k], nc = c + DJ[k];
            if (nr >= 0 && nc >= 0 && nr < n && nc < n && !vis[nr][nc] && m[nr][nc] == 1) {
                path.append(DIR[k]);
                ratLoop(nr, nc, m, n, path, ans, vis);
                path.deleteCharAt(path.length() - 1);
            }
        }
        vis[r][c] = false;
    }
    public static List<String> findPath(int[][] m) {
        int n = m.length;
        List<String> ans = new ArrayList<>();
        if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return ans;
        ratLoop(0, 0, m, n, new StringBuilder(), ans, new boolean[n][n]);
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- If the start or end cell is blocked, return an empty list immediately.
- Unmark `vis` after exploring. Otherwise other paths through that cell get blocked.

#### Key Takeaways
- Exploring directions in alphabetical order produces lexicographically sorted paths for free.

[↑ Contents](#contents) · [← Previous](#p160) · [Next →](#p162)

---

<a id="p162"></a>

### 19. M Coloring Problem

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Hard) | Pro | Yes | — | [Watch](https://youtu.be/wuVwUK25Rfc) |

#### Problem Statement
Given an undirected graph with `n` vertices and an integer `m`, decide whether the vertices can be coloured with **at most `m` colours** so that **no two adjacent vertices share a colour**. Return true/false (1/0 on GfG). With `m = 2` this is the bipartite check.

```text
4 vertices, edges (0-1), (1-2), (2-3), (3-0), (0-2):
  m = 3 -> true   (0:1, 1:2, 2:3, 3:2)
  m = 2 -> false  (0, 1, 2 form a triangle)
```

#### Approach 1: Brute Force — try every assignment of colours
Enumerate all `mⁿ` colour assignments with nested recursion and no pruning. For each complete assignment, check every edge.

**Complexity:** O(mⁿ · E) time, O(n) space.

**C++**
```cpp
bool allAssign(int node, int n, int m, vector<int>& color, vector<vector<int>>& adj) {
    if (node == n) {                                     // full assignment: verify all edges
        for (int u = 0; u < n; u++) for (int v : adj[u]) if (color[u] == color[v]) return false;
        return true;
    }
    for (int c = 1; c <= m; c++) {
        color[node] = c;
        if (allAssign(node + 1, n, m, color, adj)) return true;
    }
    color[node] = 0;
    return false;
}
bool graphColoringBrute(vector<vector<int>>& adj, int m, int n) {
    vector<int> color(n, 0);
    return allAssign(0, n, m, color, adj);
}
```

**Java**
```java
class Solution {
    static boolean allAssign(int node, int n, int m, int[] color, List<List<Integer>> adj) {
        if (node == n) {                                     // full assignment: verify all edges
            for (int u = 0; u < n; u++) for (int v : adj.get(u)) if (color[u] == color[v]) return false;
            return true;
        }
        for (int c = 1; c <= m; c++) {
            color[node] = c;
            if (allAssign(node + 1, n, m, color, adj)) return true;
        }
        color[node] = 0;
        return false;
    }
    static boolean graphColoringBrute(List<List<Integer>> adj, int m, int n) {
        return allAssign(0, n, m, new int[n], adj);
    }
}
```

#### Approach 2: Backtracking with an `isSafe` check (as in the video)
Colour the vertices **in serial order** 0, 1, 2, … rather than by traversing the graph.
- `solve(node)`: if `node == n`, every vertex is coloured, so return true.
- Otherwise try colours `c = 1 … m`. If no neighbour of `node` already has colour `c` (`isSafe`), set `color[node] = c` and recurse on `node + 1`.
  - If the recursion returns true, **return true immediately**. The question only asks whether a colouring exists, so there's no need to try other colours.
  - If it returns false, **backtrack**: `color[node] = 0`.
- If no colour works, return false.

**Dry run** with `m = 2` on the example:
- 0 gets colour 1, and 1 gets colour 2.
- 2 can't take colour 1 (neighbour 0 has it) or colour 2 (neighbour 1 has it), so return false. Vertex 1 has no other colour to try.
- Vertex 0 tries colour 2, and the same contradiction appears. Result: **false**.

**Complexity:** O(mⁿ) in the worst case, which is much less in practice thanks to pruning. O(n) for `color` and O(n) recursion depth.

**C++**
```cpp
bool isSafeColor(int node, int c, vector<int>& color, vector<vector<int>>& adj) {
    for (int nb : adj[node]) if (color[nb] == c) return false;
    return true;
}
bool solveColor(int node, int n, int m, vector<int>& color, vector<vector<int>>& adj) {
    if (node == n) return true;
    for (int c = 1; c <= m; c++) {
        if (isSafeColor(node, c, color, adj)) {
            color[node] = c;
            if (solveColor(node + 1, n, m, color, adj)) return true;
            color[node] = 0;                         // backtrack
        }
    }
    return false;
}
bool graphColoring(vector<vector<int>>& adj, int m, int n) {
    vector<int> color(n, 0);
    return solveColor(0, n, m, color, adj);
}
```

**Java**
```java
class Solution {
    static boolean isSafeColor(int node, int c, int[] color, List<List<Integer>> adj) {
        for (int nb : adj.get(node)) if (color[nb] == c) return false;
        return true;
    }
    static boolean solveColor(int node, int n, int m, int[] color, List<List<Integer>> adj) {
        if (node == n) return true;
        for (int c = 1; c <= m; c++) {
            if (isSafeColor(node, c, color, adj)) {
                color[node] = c;
                if (solveColor(node + 1, n, m, color, adj)) return true;
                color[node] = 0;                         // backtrack
            }
        }
        return false;
    }
    public static boolean graphColoring(List<List<Integer>> adj, int m, int n) {
        return solveColor(0, n, m, new int[n], adj);
    }
}
```

> With an **adjacency matrix** `graph[i][j]` (as in the video's C++ version), `isSafe` loops `k = 0..n−1` and checks `k != node && graph[node][k] == 1 && color[k] == c`.

#### Key Takeaways
- "Can it be done?" backtracking: return true as soon as one full solution is found, and undo the choice otherwise.
- Colouring in vertex-index order means the safety check only has to look at neighbours coloured earlier.

[↑ Contents](#contents) · [← Previous](#p161) · [Next →](#p163)

---

<a id="p163"></a>

### 20. Sudoku Solver

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/sudoku-solver/) | [Watch](https://youtu.be/FWAIf_EVUKE) |

#### Problem Statement
Fill a partially completed 9×9 Sudoku (empty cells are `'.'`) so that every **row**, every **column** and every **3×3 box** contains the digits 1–9 exactly once. Modify the board in place; a solution is guaranteed (LeetCode 37).

> The video's captions were a Hindi-script transliteration of the English audio. The notes below follow that transcript.

#### Approach 1: Backtracking with three separate checks
1. Scan the board for the **first empty cell**.
2. Try the characters `'1'…'9'` in that cell. For each one that's valid, place it and recurse.
   - If the recursion returns true, return true **without undoing anything**. The board is solved, and only one solution is needed.
   - Otherwise undo the cell (`'.'`) and try the next digit.
3. If no digit fits, return false. A wrong choice was made earlier.
4. If the scan finds **no empty cell**, the board is complete, so return true.

The video's walk-through: putting 1 in the first empty cell later leaves another cell with no valid digit. The search backtracks and tries 4 in the first cell instead, and from there it succeeds.

Here the validity check uses three loops: one for the row, one for the column, and one for the box.

**Complexity:** O(9^(empty cells)) in the worst case, though pruning makes it fast in practice. The board is a fixed size, so O(1) extra space besides the recursion.

**C++**
```cpp
bool validThree(vector<vector<char>>& b, int row, int col, char ch) {
    for (int i = 0; i < 9; i++) if (b[row][i] == ch) return false;      // row
    for (int i = 0; i < 9; i++) if (b[i][col] == ch) return false;      // column
    int br = 3 * (row / 3), bc = 3 * (col / 3);
    for (int r = br; r < br + 3; r++)                                    // 3x3 box
        for (int c = bc; c < bc + 3; c++) if (b[r][c] == ch) return false;
    return true;
}
bool solveThree(vector<vector<char>>& b) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (b[i][j] == '.') {
                for (char ch = '1'; ch <= '9'; ch++)
                    if (validThree(b, i, j, ch)) {
                        b[i][j] = ch;
                        if (solveThree(b)) return true;
                        b[i][j] = '.';
                    }
                return false;                      // nothing fits here
            }
    return true;                                   // no empty cell left
}
```

**Java**
```java
class Solution {
    static boolean validThree(char[][] b, int row, int col, char ch) {
        for (int i = 0; i < 9; i++) if (b[row][i] == ch) return false;      // row
        for (int i = 0; i < 9; i++) if (b[i][col] == ch) return false;      // column
        int br = 3 * (row / 3), bc = 3 * (col / 3);
        for (int r = br; r < br + 3; r++)                                    // 3x3 box
            for (int c = bc; c < bc + 3; c++) if (b[r][c] == ch) return false;
        return true;
    }
    static boolean solveThree(char[][] b) {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (b[i][j] == '.') {
                    for (char ch = '1'; ch <= '9'; ch++)
                        if (validThree(b, i, j, ch)) {
                            b[i][j] = ch;
                            if (solveThree(b)) return true;
                            b[i][j] = '.';
                        }
                    return false;                      // nothing fits here
                }
        return true;                                   // no empty cell left
    }
}
```

#### Approach 2: The video's single-loop `isValid`
One loop `i = 0…8` checks all three constraints at once:
- **Row:** `board[row][i]`, where only the column changes.
- **Column:** `board[i][col]`, where only the row changes.
- **Box:** `board[3*(row/3) + i/3][3*(col/3) + i%3]`.
  - `3*(row/3)` and `3*(col/3)` give the box's top-left corner. For cell (5, 7), that's row 3, column 6.
  - As `i` runs 0…8, `i/3` steps through the box's rows 0, 0, 0, 1, 1, 1, 2, 2, 2. At the same time `i%3` steps through its columns 0, 1, 2, 0, 1, 2, 0, 1, 2.
  - So the loop visits (3,6), (3,7), (3,8), (4,6), …, (5,8): all 9 cells of the box.

The complexity is the same as Approach 1, but each check is a single loop of 9 instead of three loops.

**C++**
```cpp
bool isValid(vector<vector<char>>& board, int row, int col, char c) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == c) return false;
        if (board[i][col] == c) return false;
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
    }
    return true;
}
bool solve(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j] == '.') {
                for (char c = '1'; c <= '9'; c++)
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;
                        if (solve(board)) return true;
                        board[i][j] = '.';             // backtrack
                    }
                return false;
            }
    return true;
}
void solveSudoku(vector<vector<char>>& board) { solve(board); }
```

**Java**
```java
class Solution {
    private boolean isValid(char[][] board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == c) return false;
            if (board[i][col] == c) return false;
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
        }
        return true;
    }
    private boolean solve(char[][] board) {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++)
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            if (solve(board)) return true;
                            board[i][j] = '.';             // backtrack
                        }
                    return false;
                }
        return true;
    }
    public void solveSudoku(char[][] board) { solve(board); }
}
```

#### Edge Cases & Pitfalls
- After trying every digit in an empty cell, return false. Without this, the loops would move past an empty cell and leave it unfilled.
- Once `solve` returns true, don't undo the board. That's the answer.

#### Key Takeaways
- To fill a grid under constraints: find the next empty cell, try each option, recurse, and undo on failure.
- The cells of a box are `(3·(r/3) + i/3, 3·(c/3) + i%3)` for `i = 0…8`.

[↑ Contents](#contents) · [← Previous](#p162) · [Next →](#p164)

---

<a id="p164"></a>

### 21. Expression Add Operators

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Recursion › FAQs (Hard) | Pro | No | [LeetCode](https://leetcode.com/problems/expression-add-operators/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a digit string `num` and a `target`, insert the operators `+`, `-` or `*` between digits (or nothing, which joins digits into a longer number) so that the expression evaluates to `target`. Return **all** such expressions. Operands may not have leading zeros (LeetCode 282).

```text
num = "123",  target = 6   ->  ["1*2*3", "1+2+3"]
num = "232",  target = 8   ->  ["2*3+2", "2+3*2"]
num = "105",  target = 5   ->  ["1*0+5", "10-5"]
num = "3456237490", target = 9191 -> []
```

#### Approach 1: Brute Force — build every expression, then evaluate it
Between each pair of digits, place one of 4 options: nothing, `+`, `-`, `*`. That gives 4ⁿ⁻¹ strings. Evaluate each one with a small parser that respects `*` precedence, and keep those that equal `target` and contain no operands with leading zeros.

**Complexity:** O(4ⁿ · n) time.

**C++**
```cpp
long long evalExpr(const string& e) {                 // +,-,* with precedence, no spaces
    long long total = 0, term = 0, num = 0; char op = '+';
    for (size_t i = 0; i <= e.size(); i++) {
        if (i < e.size() && isdigit(e[i])) { num = num * 10 + (e[i] - '0'); continue; }
        if (op == '+') { total += term; term = num; }
        else if (op == '-') { total += term; term = -num; }
        else term *= num;                              // '*'
        num = 0;
        if (i < e.size()) op = e[i];
    }
    return total + term;
}
bool noLeadingZeros(const string& e) {
    for (size_t i = 0; i < e.size(); i++)
        if (e[i] == '0' && (i == 0 || !isdigit(e[i - 1])) && i + 1 < e.size() && isdigit(e[i + 1])) return false;
    return true;
}
void buildAll(const string& num, int i, string cur, long long target, vector<string>& res) {
    if (i == (int)num.size()) {
        if (noLeadingZeros(cur) && evalExpr(cur) == target) res.push_back(cur);
        return;
    }
    for (string op : {"", "+", "-", "*"}) buildAll(num, i + 1, cur + op + num[i], target, res);
}
vector<string> addOperatorsBrute(string num, int target) {
    vector<string> res;
    if (num.empty()) return res;
    buildAll(num, 1, string(1, num[0]), target, res);
    return res;
}
```

**Java**
```java
class Solution {
    static long evalExpr(String e) {                       // +,-,* with precedence, no spaces
        long total = 0, term = 0, num = 0; char op = '+';
        for (int i = 0; i <= e.length(); i++) {
            if (i < e.length() && Character.isDigit(e.charAt(i))) { num = num * 10 + (e.charAt(i) - '0'); continue; }
            if (op == '+') { total += term; term = num; }
            else if (op == '-') { total += term; term = -num; }
            else term *= num;                              // '*'
            num = 0;
            if (i < e.length()) op = e.charAt(i);
        }
        return total + term;
    }
    static boolean noLeadingZeros(String e) {
        for (int i = 0; i < e.length(); i++)
            if (e.charAt(i) == '0' && (i == 0 || !Character.isDigit(e.charAt(i - 1)))
                    && i + 1 < e.length() && Character.isDigit(e.charAt(i + 1))) return false;
        return true;
    }
    static void buildAll(String num, int i, String cur, long target, List<String> res) {
        if (i == num.length()) {
            if (noLeadingZeros(cur) && evalExpr(cur) == target) res.add(cur);
            return;
        }
        for (String op : new String[]{"", "+", "-", "*"}) buildAll(num, i + 1, cur + op + num.charAt(i), target, res);
    }
    static List<String> addOperatorsBrute(String num, int target) {
        List<String> res = new ArrayList<>();
        if (num.isEmpty()) return res;
        buildAll(num, 1, String.valueOf(num.charAt(0)), target, res);
        return res;
    }
}
```

#### Approach 2: Optimal — backtracking that evaluates as it goes
Carry two values along with the expression string:
- `value`: the result of the expression built so far.
- `last`: the last operand, with its sign.

At each step, choose the next operand `s[index..i]`. Stop extending once it would have a leading zero. Then branch on the operator:
- `+` : `value + cur`, with `last = cur`.
- `-` : `value − cur`, with `last = −cur`.
- `*` : **`value − last + last·cur`**, with `last = last·cur`. This undoes the last term and replaces it with its product, which gives `*` its higher precedence.

At position 0 there's no operator: the first operand starts the expression. Record the expression when `index == n` and `value == target`.

**Complexity:** O(4ⁿ · n) worst case, but each branch costs O(1) besides building strings, with no re-parsing. O(n) recursion depth. Use 64-bit values: a 10-digit operand alone can exceed `int`.

**C++**
```cpp
void addOps(const string& num, long long target, int index, long long value, long long last,
            string& expr, vector<string>& res) {
    if (index == (int)num.size()) {
        if (value == target) res.push_back(expr);
        return;
    }
    long long cur = 0;
    int len = expr.size();
    for (int i = index; i < (int)num.size(); i++) {
        if (i > index && num[index] == '0') break;       // no leading zeros
        cur = cur * 10 + (num[i] - '0');
        string part = num.substr(index, i - index + 1);
        if (index == 0) {
            expr += part;
            addOps(num, target, i + 1, cur, cur, expr, res);
            expr.resize(len);
        } else {
            expr += "+" + part; addOps(num, target, i + 1, value + cur, cur, expr, res); expr.resize(len);
            expr += "-" + part; addOps(num, target, i + 1, value - cur, -cur, expr, res); expr.resize(len);
            expr += "*" + part; addOps(num, target, i + 1, value - last + last * cur, last * cur, expr, res); expr.resize(len);
        }
    }
}
vector<string> addOperators(string num, int target) {
    vector<string> res; string expr;
    addOps(num, target, 0, 0, 0, expr, res);
    return res;
}
```

**Java**
```java
class Solution {
    private void addOps(String num, long target, int index, long value, long last,
                        StringBuilder expr, List<String> res) {
        if (index == num.length()) {
            if (value == target) res.add(expr.toString());
            return;
        }
        long cur = 0;
        int len = expr.length();
        for (int i = index; i < num.length(); i++) {
            if (i > index && num.charAt(index) == '0') break;    // no leading zeros
            cur = cur * 10 + (num.charAt(i) - '0');
            String part = num.substring(index, i + 1);
            if (index == 0) {
                expr.append(part);
                addOps(num, target, i + 1, cur, cur, expr, res);
                expr.setLength(len);
            } else {
                expr.append('+').append(part); addOps(num, target, i + 1, value + cur, cur, expr, res); expr.setLength(len);
                expr.append('-').append(part); addOps(num, target, i + 1, value - cur, -cur, expr, res); expr.setLength(len);
                expr.append('*').append(part); addOps(num, target, i + 1, value - last + last * cur, last * cur, expr, res); expr.setLength(len);
            }
        }
    }
    public List<String> addOperators(String num, int target) {
        List<String> res = new ArrayList<>();
        addOps(num, target, 0, 0, 0, new StringBuilder(), res);
        return res;
    }
}
```

#### Edge Cases & Pitfalls
- **Leading zeros:** "05" isn't a valid operand, but a single "0" is. That's why the loop breaks only when `i > index`.
- **Multiplication precedence:** the `value − last + last·cur` trick is the key. Without it, `2+3*2` would be evaluated as `(2+3)*2`.

#### Key Takeaways
- To evaluate operator-precedence expressions incrementally, track the last term so that `*` can retroactively rebind it.

[↑ Contents](#contents) · [← Previous](#p163)

---
