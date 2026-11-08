# Strings (Basic and Medium) — Striver's A2Z DSA Sheet Notes

Section 6 of 20 · 7 problems · 0 with video, 7 without · [All sections](00-index.md)

[← Binary Search](05-binary-search.md) | [Recursion →](07-recursion.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Parentheses**

1. [Remove Outermost Parentheses](#p137) — Core · *no video*
2. [Maximum Nesting Depth of the Parentheses](#p138) — Core · *no video*

**String Conversions**

3. [Roman to Integer](#p139) — Basic · *no video*
4. [String to Integer (atoi)](#p140) — Core · *no video*

**Substring Problems**

5. [Count Number of Substrings](#p141) — — · *no video*
6. [Longest Palindromic Substring](#p142) — Core · *no video*
7. [Sum of Beauty of All Substrings](#p143) — Core · *no video*

---

## Parentheses

<a id="p137"></a>

### 1. Remove Outermost Parentheses

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Basic and Medium) › Parentheses | Core | No | [LeetCode](https://leetcode.com/problems/remove-outermost-parentheses/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
A **valid parentheses string (VPS)** can be split into **primitive** parts: non-empty VPS pieces that can't be split any further. Remove the **outermost** pair of parentheses from every primitive part and return the result (LeetCode 1021).

```text
"(()())(())"       ->  "()()()"        primitives: "(()())" + "(())" -> "()()" + "()"
"(()())(())(()(()))" -> "()()()()(())"
"()()"             ->  ""
```

#### Intuition
Scan the string while tracking the **depth**, i.e. the number of currently open brackets.
- A `(` seen at depth 0 opens a new primitive. It's an outermost bracket, so skip it.
- A `)` that brings the depth back to 0 closes that primitive, so skip it as well.
- Every other bracket is inside a primitive, so keep it.

#### Approach 1: Brute Force — split into primitives first, then strip
Find each primitive's boundaries with a balance counter (it closes when the balance hits 0). Then append the inside of each primitive, `s.substr(start + 1, len − 2)`.

**Complexity:** O(n) time, plus O(n) for the substrings.

**C++**
```cpp
string removeOuterParenthesesSplit(string s) {
    string res;
    int bal = 0, start = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        bal += (s[i] == '(') ? 1 : -1;
        if (bal == 0) {                                   // primitive s[start..i]
            res += s.substr(start + 1, i - start - 1);    // drop its outer pair
            start = i + 1;
        }
    }
    return res;
}
```

**Java**
```java
class Solution {
    static String removeOuterParenthesesSplit(String s) {
        StringBuilder res = new StringBuilder();
        int bal = 0, start = 0;
        for (int i = 0; i < s.length(); i++) {
            bal += (s.charAt(i) == '(') ? 1 : -1;
            if (bal == 0) {                                       // primitive s[start..i]
                res.append(s, start + 1, i);                      // drop its outer pair
                start = i + 1;
            }
        }
        return res.toString();
    }
}
```

#### Approach 2: Optimal — single pass with a depth counter
- For `(`: append it if `depth > 0`, then `depth++`.
- For `)`: `depth−−` first, then append it if `depth > 0`.

**Dry run** `"(()())(())"`:

| char | depth before | action | depth after |
|---|---|---|---|
| ( | 0 | skip (outer) | 1 |
| ( | 1 | keep | 2 |
| ) | 2 | keep | 1 |
| ( | 1 | keep | 2 |
| ) | 2 | keep | 1 |
| ) | 1 | skip (outer close) | 0 |
| ( | 0 | skip (outer) | 1 |
| ( | 1 | keep | 2 |
| ) | 2 | keep | 1 |
| ) | 1 | skip (outer close) | 0 |

The kept characters give `"()()()"`.

**Complexity:** O(n) time, O(1) extra space besides the output. This is the stack idea with only the stack's size kept.

**C++**
```cpp
string removeOuterParentheses(string s) {
    string res;
    int depth = 0;
    for (char c : s) {
        if (c == '(') {
            if (depth > 0) res += c;
            depth++;
        } else {
            depth--;
            if (depth > 0) res += c;
        }
    }
    return res;
}
```

**Java**
```java
class Solution {
    public String removeOuterParentheses(String s) {
        StringBuilder res = new StringBuilder();
        int depth = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') {
                if (depth > 0) res.append(c);
                depth++;
            } else {
                depth--;
                if (depth > 0) res.append(c);
            }
        }
        return res.toString();
    }
}
```

#### Edge Cases & Pitfalls
- Order matters: for `(` check the depth *before* incrementing, and for `)` check it *after* decrementing.
- The input is guaranteed to be valid. On invalid input the depth could go negative.
- In Java, use a `StringBuilder`. Repeated `+=` on strings is O(n²).

#### Key Takeaways
- For balanced-bracket questions, an integer depth counter usually replaces an explicit stack.
- Depth 0 marks the boundaries between primitive parts.

[↑ Contents](#contents) · [Next →](#p138)

---

<a id="p138"></a>

### 2. Maximum Nesting Depth of the Parentheses

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Basic and Medium) › Parentheses | Core | No | [LeetCode](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a valid parentheses expression `s` (which may contain digits and operators), return its **nesting depth**: the maximum number of parentheses open at the same time (LeetCode 1614).

```text
"(1+(2*3)+((8)/4))+1"  ->  3     (the "8" sits inside three open brackets)
"(1)+((2))+(((3)))"    ->  3
"1+(2*3)/(2-1)"        ->  1
"1"                    ->  0
```

#### Approach 1: Brute Force — explicit stack
Push on `(` and pop on `)`. The answer is the largest stack size ever reached.

**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int maxDepthStack(string s) {
    stack<char> st;
    int best = 0;
    for (char c : s) {
        if (c == '(') { st.push(c); best = max(best, (int)st.size()); }
        else if (c == ')') st.pop();
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int maxDepthStack(String s) {
        Deque<Character> st = new ArrayDeque<>();
        int best = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') { st.push(c); best = Math.max(best, st.size()); }
            else if (c == ')') st.pop();
        }
        return best;
    }
}
```

#### Approach 2: Optimal — counter instead of a stack
The stack only ever holds `(` characters, so its size is all we need. Use a counter: `cur++` on `(` (and update `best`), `cur−−` on `)`.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int maxDepth(string s) {
    int cur = 0, best = 0;
    for (char c : s) {
        if (c == '(') best = max(best, ++cur);
        else if (c == ')') cur--;
    }
    return best;
}
```

**Java**
```java
class Solution {
    public int maxDepth(String s) {
        int cur = 0, best = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') best = Math.max(best, ++cur);
            else if (c == ')') cur--;
        }
        return best;
    }
}
```

#### Edge Cases & Pitfalls
- Ignore every character that isn't a bracket.
- Update `best` right after an opening bracket. That's the moment the depth can increase.

#### Key Takeaways
- Nesting depth is the running count of open brackets, and the answer is its maximum.

[↑ Contents](#contents) · [← Previous](#p137) · [Next →](#p139)

---

## String Conversions

<a id="p139"></a>

### 3. Roman to Integer

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Basic and Medium) › String Conversions | Basic | No | [LeetCode](https://leetcode.com/problems/roman-to-integer/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Convert a Roman numeral to an integer (LeetCode 13). The symbols are `I=1, V=5, X=10, L=50, C=100, D=500, M=1000`. Normally symbols run from largest to smallest and are added. A smaller symbol placed **before** a larger one is subtracted instead: `IV=4, IX=9, XL=40, XC=90, CD=400, CM=900`.

```text
"III"     ->  3
"LVIII"   ->  58      (L + V + III)
"MCMXCIV" ->  1994    (M + CM + XC + IV = 1000 + 900 + 90 + 4)
```

#### Approach 1: Brute Force — handle the six subtractive pairs explicitly
Scan left to right. If the current and next characters form one of the six pairs, add the pair's value and skip both. Otherwise add the single symbol's value.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int romanToIntPairs(string s) {
    unordered_map<string, int> pairs = {{"IV",4},{"IX",9},{"XL",40},{"XC",90},{"CD",400},{"CM",900}};
    unordered_map<char, int> val = {{'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};
    int res = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (i + 1 < (int)s.size() && pairs.count(s.substr(i, 2))) { res += pairs[s.substr(i, 2)]; i++; }
        else res += val[s[i]];
    }
    return res;
}
```

**Java**
```java
class Solution {
    static int romanToIntPairs(String s) {
        Map<String, Integer> pairs = Map.of("IV",4,"IX",9,"XL",40,"XC",90,"CD",400,"CM",900);
        Map<Character, Integer> val = Map.of('I',1,'V',5,'X',10,'L',50,'C',100,'D',500,'M',1000);
        int res = 0;
        for (int i = 0; i < s.length(); i++) {
            if (i + 1 < s.length() && pairs.containsKey(s.substring(i, i + 2))) { res += pairs.get(s.substring(i, i + 2)); i++; }
            else res += val.get(s.charAt(i));
        }
        return res;
    }
}
```

#### Approach 2: Optimal — compare each symbol with the next one
There's a single rule: **if a symbol is smaller than the symbol after it, subtract it; otherwise add it.** This covers all six subtractive cases without listing them.

**Dry run** `"MCMXCIV"`:
- M (1000 ≥ C) → +1000.
- C (100 < M) → −100.
- M → +1000.
- X (10 < C) → −10.
- C → +100.
- I (1 < V) → −1.
- V → +5.

Total: **1994**.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int value(char c) {
    switch (c) {
        case 'I': return 1;   case 'V': return 5;   case 'X': return 10;  case 'L': return 50;
        case 'C': return 100; case 'D': return 500; case 'M': return 1000;
    }
    return 0;
}
int romanToInt(string s) {
    int res = 0, n = s.size();
    for (int i = 0; i < n; i++) {
        if (i + 1 < n && value(s[i]) < value(s[i + 1])) res -= value(s[i]);
        else res += value(s[i]);
    }
    return res;
}
```

**Java**
```java
class Solution {
    static int value(char c) {
        switch (c) {
            case 'I': return 1;   case 'V': return 5;   case 'X': return 10;  case 'L': return 50;
            case 'C': return 100; case 'D': return 500; case 'M': return 1000;
        }
        return 0;
    }
    public int romanToInt(String s) {
        int res = 0, n = s.length();
        for (int i = 0; i < n; i++) {
            if (i + 1 < n && value(s.charAt(i)) < value(s.charAt(i + 1))) res -= value(s.charAt(i));
            else res += value(s.charAt(i));
        }
        return res;
    }
}
```

#### Key Takeaways
- The "smaller before larger means subtract" rule turns Roman numeral parsing into one linear pass.
- A `switch` (or a 26-entry array) is faster than a hash map for a fixed small alphabet.

[↑ Contents](#contents) · [← Previous](#p138) · [Next →](#p140)

---

<a id="p140"></a>

### 4. String to Integer (atoi)

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Basic and Medium) › String Conversions | Core | No | [LeetCode](https://leetcode.com/problems/string-to-integer-atoi/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Implement `myAtoi(s)` (LeetCode 8). Parse the string into a 32-bit signed integer as follows:
1. Skip leading spaces.
2. Read an optional `+` or `−` sign.
3. Read digits until the first non-digit character.
4. **Clamp** the result to `[−2³¹, 2³¹ − 1]`.

If no digits are read, return 0.

```text
"42"              ->  42
"   -042"         ->  -42
"1337c0d3"        ->  1337
"0-1"             ->  0
"words and 987"   ->  0
"-91283472332"    ->  -2147483648   (clamped)
```

#### Approach 1: Iterative parse with 64-bit accumulation
Follow the four steps directly. Accumulate in a `long long` / `long`, and clamp as soon as the value passes the `int` range so the accumulator itself can't overflow.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int myAtoi(string s) {
    int i = 0, n = s.size(), sign = 1;
    while (i < n && s[i] == ' ') i++;
    if (i < n && (s[i] == '+' || s[i] == '-')) sign = (s[i++] == '-') ? -1 : 1;
    long long res = 0;
    while (i < n && isdigit(s[i])) {
        res = res * 10 + (s[i++] - '0');
        if (sign * res > INT_MAX) return INT_MAX;
        if (sign * res < INT_MIN) return INT_MIN;
    }
    return (int)(sign * res);
}
```

**Java**
```java
class Solution {
    public int myAtoi(String s) {
        int i = 0, n = s.length(), sign = 1;
        while (i < n && s.charAt(i) == ' ') i++;
        if (i < n && (s.charAt(i) == '+' || s.charAt(i) == '-')) sign = (s.charAt(i++) == '-') ? -1 : 1;
        long res = 0;
        while (i < n && Character.isDigit(s.charAt(i))) {
            res = res * 10 + (s.charAt(i++) - '0');
            if (sign * res > Integer.MAX_VALUE) return Integer.MAX_VALUE;
            if (sign * res < Integer.MIN_VALUE) return Integer.MIN_VALUE;
        }
        return (int) (sign * res);
    }
}
```

#### Approach 2: Recursive digit parsing (the A2Z recursion-practice version)
The sheet's recursion section asks for the same parse done recursively. A helper `parse(i, acc)` reads the digit at `i`, folds it into the accumulator, and recurses on `i + 1`. It stops at the first non-digit or when the value overflows.

**Complexity:** O(n) time, plus O(n) recursion stack.

**C++**
```cpp
long long parseRec(const string& s, int i, long long acc, int sign) {
    if (i >= (int)s.size() || !isdigit(s[i])) return acc;
    acc = acc * 10 + (s[i] - '0');
    if (sign * acc > INT_MAX) return (long long)INT_MAX + 1;      // signal overflow
    if (sign * acc < INT_MIN) return -(long long)INT_MIN;         // magnitude of INT_MIN
    return parseRec(s, i + 1, acc, sign);
}
int myAtoiRecursive(string s) {
    int i = 0, n = s.size(), sign = 1;
    while (i < n && s[i] == ' ') i++;
    if (i < n && (s[i] == '+' || s[i] == '-')) sign = (s[i++] == '-') ? -1 : 1;
    long long val = sign * parseRec(s, i, 0, sign);
    if (val > INT_MAX) return INT_MAX;
    if (val < INT_MIN) return INT_MIN;
    return (int)val;
}
```

**Java**
```java
class Solution {
    static long parseRec(String s, int i, long acc, int sign) {
        if (i >= s.length() || !Character.isDigit(s.charAt(i))) return acc;
        acc = acc * 10 + (s.charAt(i) - '0');
        if (sign * acc > Integer.MAX_VALUE) return (long) Integer.MAX_VALUE + 1;   // signal overflow
        if (sign * acc < Integer.MIN_VALUE) return -(long) Integer.MIN_VALUE;      // magnitude of MIN
        return parseRec(s, i + 1, acc, sign);
    }
    static int myAtoiRecursive(String s) {
        int i = 0, n = s.length(), sign = 1;
        while (i < n && s.charAt(i) == ' ') i++;
        if (i < n && (s.charAt(i) == '+' || s.charAt(i) == '-')) sign = (s.charAt(i++) == '-') ? -1 : 1;
        long val = sign * parseRec(s, i, 0, sign);
        if (val > Integer.MAX_VALUE) return Integer.MAX_VALUE;
        if (val < Integer.MIN_VALUE) return Integer.MIN_VALUE;
        return (int) val;
    }
}
```

#### Edge Cases & Pitfalls
- Only **spaces** count as leading whitespace in LeetCode's version. Tabs and other characters stop the parse.
- At most one sign is allowed, so `"+-12"` → 0.
- **Overflow:** check after each digit, before the accumulator itself overflows. Long digit strings like `"99999999999999999999"` would otherwise overflow even a 64-bit value.
- Leading zeros (`"0000123"`) are fine.

#### Key Takeaways
- Parsers are simplest as a fixed sequence of phases: whitespace, then sign, then digits, then clamp.
- Overflow-safe accumulation means checking the range on every step.

[↑ Contents](#contents) · [← Previous](#p139) · [Next →](#p141)

---

## Substring Problems

<a id="p141"></a>

### 5. Count Number of Substrings

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Basic and Medium) › Substring Problems | — | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a string `s` of lowercase letters and an integer `k`, count the **substrings with exactly `k` distinct characters**.

```text
s = "pqpqs", k = 2  ->  7     ("pq", "pqp", "pqpq", "qp", "qpq", "pq", "qs")
s = "aabab", k = 3  ->  0
s = "abc",   k = 2  ->  2     ("ab", "bc")
```

#### Approach 1: Brute Force — all substrings, with a running distinct count
Fix the start `i`. Extend the end `j`, keep a frequency array, and count the distinct letters as you go. Once the distinct count goes past `k`, stop extending, because it can only grow from there.

**Complexity:** O(n²) time, O(26) space.

**C++**
```cpp
long long countExactlyKBrute(string s, int k) {
    int n = s.size();
    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        int freq[26] = {0}, distinct = 0;
        for (int j = i; j < n; j++) {
            if (freq[s[j] - 'a']++ == 0) distinct++;
            if (distinct == k) cnt++;
            else if (distinct > k) break;
        }
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static long countExactlyKBrute(String s, int k) {
        int n = s.length();
        long cnt = 0;
        for (int i = 0; i < n; i++) {
            int[] freq = new int[26];
            int distinct = 0;
            for (int j = i; j < n; j++) {
                if (freq[s.charAt(j) - 'a']++ == 0) distinct++;
                if (distinct == k) cnt++;
                else if (distinct > k) break;
            }
        }
        return cnt;
    }
}
```

#### Approach 2: Optimal — exactly(k) = atMost(k) − atMost(k − 1), sliding window
Counting substrings with **at most** `k` distinct characters is easy with a sliding window:
- Expand `right`.
- While the window holds more than `k` distinct characters, shrink `left`.
- Each valid window `[left, right]` contributes `right − left + 1` substrings that end at `right`.

Substrings with **exactly** `k` distinct characters are the ones counted by `atMost(k)` but not by `atMost(k − 1)`.

**Dry run** `"pqpqs"`, `k = 2`:
- `atMost(2)`: the window adds 1 + 2 + 3 + 4 + 2 = 12. At `s`, the window shrinks to `"qs"`, contributing 2.
- `atMost(1)` = 5, since every single character counts.
- So exactly(2) = 12 − 5 = **7**.

**Complexity:** O(n) time (two linear passes), O(26) space.

**C++**
```cpp
long long atMostK(const string& s, int k) {
    if (k < 0) return 0;
    int freq[26] = {0}, distinct = 0, left = 0;
    long long cnt = 0;
    for (int right = 0; right < (int)s.size(); right++) {
        if (freq[s[right] - 'a']++ == 0) distinct++;
        while (distinct > k)
            if (--freq[s[left++] - 'a'] == 0) distinct--;
        cnt += right - left + 1;                 // substrings ending at `right`
    }
    return cnt;
}
long long countExactlyK(string s, int k) {
    return atMostK(s, k) - atMostK(s, k - 1);
}
```

**Java**
```java
class Solution {
    static long atMostK(String s, int k) {
        if (k < 0) return 0;
        int[] freq = new int[26];
        int distinct = 0, left = 0;
        long cnt = 0;
        for (int right = 0; right < s.length(); right++) {
            if (freq[s.charAt(right) - 'a']++ == 0) distinct++;
            while (distinct > k)
                if (--freq[s.charAt(left++) - 'a'] == 0) distinct--;
            cnt += right - left + 1;                 // substrings ending at `right`
        }
        return cnt;
    }
    static long countExactlyK(String s, int k) {
        return atMostK(s, k) - atMostK(s, k - 1);
    }
}
```

#### Edge Cases & Pitfalls
- "Exactly k" isn't monotonic, so a single sliding window doesn't work directly. "At most k" is monotonic, which is why the subtraction trick works.
- Use 64-bit counts. There are up to n(n+1)/2 substrings.
- If `k > 26` or `k > n`, the answer is 0.

#### Key Takeaways
- **exactly(k) = atMost(k) − atMost(k−1)** is a standard trick. It also solves "subarrays with K different integers" and "binary subarrays with sum".
- A valid window `[l, r]` contributes `r − l + 1` substrings that end at `r`.

[↑ Contents](#contents) · [← Previous](#p140) · [Next →](#p142)

---

<a id="p142"></a>

### 6. Longest Palindromic Substring

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Basic and Medium) › Substring Problems | Core | No | [LeetCode](https://leetcode.com/problems/longest-palindromic-substring/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the **longest palindromic substring** of `s` (LeetCode 5).

```text
"babad"  ->  "bab"   ("aba" is also valid)
"cbbd"   ->  "bb"
"a"      ->  "a"
```

#### Approach 1: Brute Force — check every substring
Try every `(i, j)` and check whether `s[i..j]` is a palindrome with two pointers. Keep the longest one.

**Complexity:** O(n³) time, O(1) space.

**C++**
```cpp
bool isPal(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}
string longestPalindromeBrute(string s) {
    int n = s.size(), bestL = 0, bestLen = n ? 1 : 0;
    for (int i = 0; i < n; i++)
        for (int j = i + bestLen; j < n; j++)            // only longer candidates
            if (isPal(s, i, j)) { bestL = i; bestLen = j - i + 1; }
    return s.substr(bestL, bestLen);
}
```

**Java**
```java
class Solution {
    static boolean isPal(String s, int l, int r) {
        while (l < r) if (s.charAt(l++) != s.charAt(r--)) return false;
        return true;
    }
    static String longestPalindromeBrute(String s) {
        int n = s.length(), bestL = 0, bestLen = n > 0 ? 1 : 0;
        for (int i = 0; i < n; i++)
            for (int j = i + bestLen; j < n; j++)            // only longer candidates
                if (isPal(s, i, j)) { bestL = i; bestLen = j - i + 1; }
        return s.substring(bestL, bestL + bestLen);
    }
}
```

#### Approach 2: Better — DP table
`dp[i][j]` is true when `s[i..j]` is a palindrome. That happens when `s[i] == s[j]` and either `j − i < 2` or `dp[i+1][j−1]` holds. Fill the table in increasing order of length.

**Complexity:** O(n²) time, O(n²) space.

**C++**
```cpp
string longestPalindromeDP(string s) {
    int n = s.size(), bestL = 0, bestLen = n ? 1 : 0;
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    for (int len = 1; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && (len <= 2 || dp[i + 1][j - 1])) {
                dp[i][j] = true;
                if (len > bestLen) { bestL = i; bestLen = len; }
            }
        }
    return s.substr(bestL, bestLen);
}
```

**Java**
```java
class Solution {
    static String longestPalindromeDP(String s) {
        int n = s.length(), bestL = 0, bestLen = n > 0 ? 1 : 0;
        boolean[][] dp = new boolean[n][n];
        for (int len = 1; len <= n; len++)
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s.charAt(i) == s.charAt(j) && (len <= 2 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    if (len > bestLen) { bestL = i; bestLen = len; }
                }
            }
        return s.substring(bestL, bestL + bestLen);
    }
}
```

#### Approach 3: Optimal (practical) — expand around each centre
Every palindrome has a centre: either a character (odd length) or the gap between two characters (even length). There are `2n − 1` centres. From each one, expand outward while the characters on both sides match.

**Dry run** `"babad"`: the centre at index 1 (`a`) expands to `"bab"`. The centre at index 2 expands to `"aba"`. Both have length 3, which is the best.

**Complexity:** O(n²) time in the worst case, but O(1) space and fast in practice. *(Manacher's algorithm solves this in O(n). It's covered under Strings Advanced.)*

**C++**
```cpp
string longestPalindrome(string s) {
    int n = s.size(), bestL = 0, bestLen = 0;
    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) { l--; r++; }
        if (r - l - 1 > bestLen) { bestLen = r - l - 1; bestL = l + 1; }
    };
    for (int c = 0; c < n; c++) {
        expand(c, c);          // odd length
        expand(c, c + 1);      // even length
    }
    return s.substr(bestL, bestLen);
}
```

**Java**
```java
class Solution {
    private int bestL = 0, bestLen = 0;
    private void expand(String s, int l, int r) {
        while (l >= 0 && r < s.length() && s.charAt(l) == s.charAt(r)) { l--; r++; }
        if (r - l - 1 > bestLen) { bestLen = r - l - 1; bestL = l + 1; }
    }
    public String longestPalindrome(String s) {
        bestL = 0; bestLen = 0;
        for (int c = 0; c < s.length(); c++) {
            expand(s, c, c);          // odd length
            expand(s, c, c + 1);      // even length
        }
        return s.substring(bestL, bestL + bestLen);
    }
}
```

#### Edge Cases & Pitfalls
- Don't forget the **even-length** centres. `"cbbd"` → `"bb"` needs one.
- When the expansion loop stops at `(l, r)`, the palindrome is `s[l+1 .. r−1]`, which has length `r − l − 1`.

#### Key Takeaways
- Expand around the centre: there are 2n−1 centres, it's O(n²) time with O(1) space, and it's the standard interview answer.
- The DP table is the stepping stone to palindromic-subsequence and partitioning DPs.

[↑ Contents](#contents) · [← Previous](#p141) · [Next →](#p143)

---

<a id="p143"></a>

### 7. Sum of Beauty of All Substrings

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Basic and Medium) › Substring Problems | Core | No | [LeetCode](https://leetcode.com/problems/sum-of-beauty-of-all-substrings/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
The **beauty** of a string is the frequency of its most frequent character minus the frequency of its least frequent character, counting only characters that appear. Return the **sum of the beauty of all substrings** of `s` (LeetCode 1781).

```text
"aabcb"   ->  5     (substrings with beauty 1: "aab", "aabc", "aabcb", "abcb", "bcb")
"aabcbaa" ->  17
```

#### Approach 1: Brute Force — recount each substring from scratch
For every `(i, j)`, build the frequency counts of `s[i..j]` and add `max − min` over the non-zero counts.

**Complexity:** O(n³) time (O(n² · (n + 26))), O(26) space.

**C++**
```cpp
int beautySumBrute(string s) {
    int n = s.size(), total = 0;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            int freq[26] = {0};
            for (int t = i; t <= j; t++) freq[s[t] - 'a']++;
            int mx = 0, mn = INT_MAX;
            for (int f : freq) if (f) { mx = max(mx, f); mn = min(mn, f); }
            total += mx - mn;
        }
    return total;
}
```

**Java**
```java
class Solution {
    static int beautySumBrute(String s) {
        int n = s.length(), total = 0;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++) {
                int[] freq = new int[26];
                for (int t = i; t <= j; t++) freq[s.charAt(t) - 'a']++;
                int mx = 0, mn = Integer.MAX_VALUE;
                for (int f : freq) if (f > 0) { mx = Math.max(mx, f); mn = Math.min(mn, f); }
                total += mx - mn;
            }
        return total;
    }
}
```

#### Approach 2: Optimal — fix the start, grow the end, update counts incrementally
For a fixed `i`, extending `j` by one changes a single count. Keep the frequency array across iterations of `j`, and after each extension scan the 26 counts for the max and min.

**Complexity:** O(26 · n²) time, O(26) space. With n ≤ 500 this is about 6.5 million operations.

**C++**
```cpp
int beautySum(string s) {
    int n = s.size(), total = 0;
    for (int i = 0; i < n; i++) {
        int freq[26] = {0};
        for (int j = i; j < n; j++) {
            freq[s[j] - 'a']++;
            int mx = 0, mn = INT_MAX;
            for (int f : freq) if (f) { mx = max(mx, f); mn = min(mn, f); }
            total += mx - mn;
        }
    }
    return total;
}
```

**Java**
```java
class Solution {
    public int beautySum(String s) {
        int n = s.length(), total = 0;
        for (int i = 0; i < n; i++) {
            int[] freq = new int[26];
            for (int j = i; j < n; j++) {
                freq[s.charAt(j) - 'a']++;
                int mx = 0, mn = Integer.MAX_VALUE;
                for (int f : freq) if (f > 0) { mx = Math.max(mx, f); mn = Math.min(mn, f); }
                total += mx - mn;
            }
        }
        return total;
    }
}
```

#### Edge Cases & Pitfalls
- Ignore zero counts when computing the minimum, since only characters that appear are considered.
- A substring with a single distinct character has beauty 0.

#### Key Takeaways
- "All substrings" plus a per-substring statistic usually means fixing the start and updating the statistic as the end grows. That saves a factor of n over the brute force.

[↑ Contents](#contents) · [← Previous](#p142)

---
