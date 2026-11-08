# Strings (Advanced Algo) — Striver's A2Z DSA Sheet Notes

Section 19 of 20 · 8 problems · 0 with video, 8 without · [All sections](00-index.md)

[← Tries](18-tries.md) | [Maths →](20-maths.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Medium Problems**

1. [Reverse every word in a string](#p443) — Core · *no video*
2. [Minimum number of bracket reversals to make an expression balanced](#p444) — Core · *no video*
3. [Count and say](#p445) — Core · *no video*

**Advanced Problems (Less asked)**

4. [Rabin Karp Algorithm](#p446) — Pro · *no video*
5. [Z function](#p447) — Pro · *no video*
6. [KMP Algorithm or LPS array](#p448) — Pro · *no video*
7. [Shortest Palindrome](#p449) — Pro · *no video*
8. [Longest happy prefix](#p450) — Pro · *no video*

---

## Medium Problems

<a id="p443"></a>

### 1. Reverse every word in a string

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Advanced Algo) › Medium Problems | Core | No | [LeetCode](https://leetcode.com/problems/reverse-words-in-a-string/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/reverse-every-word-in-a-string) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
**Reverse Words in a String:** reverse the order of the words in `s`. Words are separated by one or more spaces. The result must have single spaces between words and no leading or trailing spaces.

```text
s = "the sky is blue"      ->  "blue is sky the"
s = "  hello world  "      ->  "world hello"
s = "a good   example"     ->  "example good a"
```

#### Intuition
- **Brute force.** Split the string into words, skipping empty tokens, then join them in reverse order. This takes O(n) extra space for the word list.
- **In place (optimal).**
  1. Reverse the **whole** string.
  2. Reverse each **word** back.
  3. Compact the spaces with a write pointer.

  Reversing the whole string puts the words in the right order but spells them backwards; the second reverse fixes each word. In C++ this needs only O(1) extra space. Java strings are immutable, so a `char[]` copy is unavoidable.

#### Approach 1: Brute force — split and join
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
string reverseWordsBrute(string s) {
    stringstream ss(s);
    vector<string> words;
    string w;
    while (ss >> w) words.push_back(w);            // >> skips any run of spaces
    string res;
    for (int i = (int)words.size() - 1; i >= 0; i--) {
        res += words[i];
        if (i) res += ' ';
    }
    return res;
}
```

**Java**
```java
class Solution {
    static String reverseWordsBrute(String s) {
        String[] parts = s.trim().split("\\s+");
        StringBuilder res = new StringBuilder();
        for (int i = parts.length - 1; i >= 0; i--) {
            res.append(parts[i]);
            if (i > 0) res.append(' ');
        }
        return res.toString();
    }
}
```

#### Approach 2: Optimal — reverse all, reverse each word, compact
**Complexity:** O(n) time, O(1) extra space in C++ (in place).

**C++**
```cpp
string reverseWords(string s) {
    reverse(s.begin(), s.end());
    int n = s.size(), write = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == ' ') continue;
        if (write > 0) s[write++] = ' ';           // one space before every word except the first
        int start = write;
        while (i < n && s[i] != ' ') s[write++] = s[i++];
        reverse(s.begin() + start, s.begin() + write);
    }
    s.resize(write);
    return s;
}
```

**Java**
```java
class Solution {
    static String reverseWords(String str) {
        char[] s = str.toCharArray();
        int n = s.length, write = 0;
        reverse(s, 0, n - 1);
        for (int i = 0; i < n; i++) {
            if (s[i] == ' ') continue;
            if (write > 0) s[write++] = ' ';
            int start = write;
            while (i < n && s[i] != ' ') s[write++] = s[i++];
            reverse(s, start, write - 1);
        }
        return new String(s, 0, write);
    }
    static void reverse(char[] a, int l, int r) {
        while (l < r) { char t = a[l]; a[l++] = a[r]; a[r--] = t; }
    }
}
```

#### Edge Cases & Pitfalls
- Leading, trailing and repeated spaces must all disappear. In Java, `split(" ")` would create empty tokens, so use `trim().split("\\s+")`.
- A string with a single word comes back unchanged, apart from trimmed spaces.

#### Key Takeaways
- "Reverse the whole thing, then reverse each part" is a general rotation and reordering trick. Array rotation uses it too.

[↑ Contents](#contents) · [Next →](#p444)

---

<a id="p444"></a>

### 2. Minimum number of bracket reversals to make an expression balanced

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Advanced Algo) › Medium Problems | Core | Yes | [LeetCode](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

> **Problem choice:** the sheet's title is GfG's *Count the Reversals* (the minimum number of bracket **reversals** to balance a string of `{` and `}`), covered first. Its LeetCode link (LC 921 *Minimum Add to Make Parentheses Valid*, which counts **insertions**) is covered under "Related problem".

#### Problem Statement
Given a string of only `{` and `}`, return the minimum number of reversals (`{` ↔ `}`) needed to make it balanced, or `−1` if that's impossible.

```text
s = "}{{}}{{{"   ->  3
s = "{{}{{{}{{}}{{"  ->  -1   (odd length)
s = "}}}}"       ->  2
s = "{{{{"       ->  2
```

#### Intuition
- **Odd length** can never balance, so return −1.
- **Cancel matched pairs.** Remove every matched `{}` pair; they need nothing. What remains has the form `}}}…{{{…`, with `close` unmatched closers followed by `open` unmatched openers. Both counts are even or both are odd, because the length is even.
- **Fix the leftovers.**
  - Each pair `}}` needs **1** reversal (`{}`), and so does each pair `{{`.
  - If both counts are odd, the last `}{` needs **2** reversals.
  - Overall: **`ceil(close/2) + ceil(open/2)`**.

#### Approach 1: Stack — cancel pairs explicitly
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
int countRevStack(string s) {
    if (s.size() % 2) return -1;
    stack<char> st;
    for (char c : s) {
        if (c == '}' && !st.empty() && st.top() == '{') st.pop();
        else st.push(c);
    }
    int open = 0, close = 0;
    while (!st.empty()) { (st.top() == '{' ? open : close)++; st.pop(); }
    return (close + 1) / 2 + (open + 1) / 2;
}
```

**Java**
```java
class Solution {
    static int countRevStack(String s) {
        if (s.length() % 2 != 0) return -1;
        Deque<Character> st = new ArrayDeque<>();
        for (char c : s.toCharArray()) {
            if (c == '}' && !st.isEmpty() && st.peek() == '{') st.pop();
            else st.push(c);
        }
        int open = 0, close = 0;
        while (!st.isEmpty()) { if (st.pop() == '{') open++; else close++; }
        return (close + 1) / 2 + (open + 1) / 2;
    }
}
```

#### Approach 2: Counters — O(1) space
**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int countRev(string s) {
    if (s.size() % 2) return -1;
    int open = 0, close = 0;               // unmatched '{' so far, unmatched '}' so far
    for (char c : s) {
        if (c == '{') open++;
        else if (open > 0) open--;          // this '}' matches an earlier '{'
        else close++;
    }
    return (close + 1) / 2 + (open + 1) / 2;
}
```

**Java**
```java
class Solution {
    static int countRev(String s) {
        if (s.length() % 2 != 0) return -1;
        int open = 0, close = 0;
        for (char c : s.toCharArray()) {
            if (c == '{') open++;
            else if (open > 0) open--;
            else close++;
        }
        return (close + 1) / 2 + (open + 1) / 2;
    }
}
```

#### Related problem: LC 921 — Minimum Add to Make Parentheses Valid
Insertions instead of reversals: every unmatched `(` needs one `)` and every unmatched `)` needs one `(`, so the answer is **`open + close`**.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int minAddToMakeValid(string s) {
    int open = 0, close = 0;
    for (char c : s) {
        if (c == '(') open++;
        else if (open > 0) open--;
        else close++;
    }
    return open + close;
}
```

**Java**
```java
class Solution {
    static int minAddToMakeValid(String s) {
        int open = 0, close = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') open++;
            else if (open > 0) open--;
            else close++;
        }
        return open + close;
    }
}
```

#### Edge Cases & Pitfalls
- `"}{"` needs **2** reversals: `ceil(1/2) + ceil(1/2)`.
- An empty string is already balanced, so the answer is 0.

#### Key Takeaways
- Cancel matched pairs greedily. Whatever is left (`}}…{{`) is fixed by a simple formula.

[↑ Contents](#contents) · [← Previous](#p443) · [Next →](#p445)

---

<a id="p445"></a>

### 3. Count and say

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Advanced Algo) › Medium Problems | Core | No | [LeetCode](https://leetcode.com/problems/count-and-say/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-and-say) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
**Count and Say:** `countAndSay(1) = "1"`, and each next term **describes** the previous one as runs of "count, then digit".

```text
n = 1  ->  "1"
n = 4  ->  "1211"     (1 -> "one 1" = 11 -> "two 1s" = 21 -> "one 2, one 1" = 1211)
n = 5  ->  "111221"
```

#### Intuition
Build each term from the previous one with **run-length encoding**: scan the string, count each run of equal digits, and append `count` followed by `digit`. Repeat `n − 1` times.

Term lengths grow by roughly 30% per step (Conway's constant, about 1.3036), so the total work is dominated by the last term.

#### Approach 1: Recursion
**Complexity:** O(total length of all terms) time, O(n) stack plus the strings.

**C++**
```cpp
string countAndSayRec(int n) {
    if (n == 1) return "1";
    string prev = countAndSayRec(n - 1), res;
    for (size_t i = 0; i < prev.size();) {
        size_t j = i;
        while (j < prev.size() && prev[j] == prev[i]) j++;
        res += to_string(j - i);
        res += prev[i];
        i = j;
    }
    return res;
}
```

**Java**
```java
class Solution {
    static String countAndSayRec(int n) {
        if (n == 1) return "1";
        String prev = countAndSayRec(n - 1);
        StringBuilder res = new StringBuilder();
        for (int i = 0; i < prev.length();) {
            int j = i;
            while (j < prev.length() && prev.charAt(j) == prev.charAt(i)) j++;
            res.append(j - i).append(prev.charAt(i));
            i = j;
        }
        return res.toString();
    }
}
```

#### Approach 2: Iteration
**Complexity:** O(total length) time, O(length of the last term) space.

**C++**
```cpp
string countAndSay(int n) {
    string cur = "1";
    for (int step = 2; step <= n; step++) {
        string nxt;
        for (size_t i = 0; i < cur.size();) {
            size_t j = i;
            while (j < cur.size() && cur[j] == cur[i]) j++;
            nxt += to_string(j - i);
            nxt += cur[i];
            i = j;
        }
        cur = nxt;
    }
    return cur;
}
```

**Java**
```java
class Solution {
    static String countAndSay(int n) {
        String cur = "1";
        for (int step = 2; step <= n; step++) {
            StringBuilder nxt = new StringBuilder();
            for (int i = 0; i < cur.length();) {
                int j = i;
                while (j < cur.length() && cur.charAt(j) == cur.charAt(i)) j++;
                nxt.append(j - i).append(cur.charAt(i));
                i = j;
            }
            cur = nxt.toString();
        }
        return cur;
    }
}
```

#### Edge Cases & Pitfalls
- In Java, use a `StringBuilder`. Repeated `+=` on a `String` is quadratic.
- No run is ever longer than 3, so a count is always a single digit, but `to_string` / `append(int)` is safer anyway.

#### Key Takeaways
- This is a pure simulation, built on the two-pointer run scan used for run-length encoding.

[↑ Contents](#contents) · [← Previous](#p444) · [Next →](#p446)

---

## Advanced Problems (Less asked)

<a id="p446"></a>

### 4. Rabin Karp Algorithm

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Advanced Algo) › Advanced Problems (Less asked) | Pro | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
**Rabin–Karp:** find every occurrence (starting index) of `pattern` in `text`.

```text
text = "geeksforgeeks", pattern = "geek"   ->  [0, 8]
text = "aaaaa", pattern = "aa"             ->  [0, 1, 2, 3]
text = "abc", pattern = "d"                ->  []
```

#### Intuition — compare hashes, not strings
- **Brute force.** Compare the pattern at every shift, which is O(n·m) in the worst case.
- **Rabin–Karp.**
  - Give each length-`m` window a **polynomial hash**: `h = (c₀·B^(m−1) + c₁·B^(m−2) + … + c_(m−1)) mod P`.
  - Sliding the window by one is O(1): remove the leading character's contribution, multiply by `B`, and add the new character.
  - Only when the window hash equals the pattern hash do you compare characters, which guards against collisions.
- **Cost.** O(n + m) on average, and O(n·m) in the worst case, when many hashes collide.

#### Approach 1: Brute force — check every shift
**Complexity:** O(n·m) time, O(1) space.

**C++**
```cpp
vector<int> searchBrute(string text, string pat) {
    vector<int> res;
    int n = text.size(), m = pat.size();
    for (int i = 0; i + m <= n; i++) {
        int j = 0;
        while (j < m && text[i + j] == pat[j]) j++;
        if (j == m) res.push_back(i);
    }
    return res;
}
```

**Java**
```java
class Solution {
    static List<Integer> searchBrute(String text, String pat) {
        List<Integer> res = new ArrayList<>();
        int n = text.length(), m = pat.length();
        for (int i = 0; i + m <= n; i++) {
            int j = 0;
            while (j < m && text.charAt(i + j) == pat.charAt(j)) j++;
            if (j == m) res.add(i);
        }
        return res;
    }
}
```

#### Approach 2: Rabin–Karp rolling hash
**Complexity:** O(n + m) expected time, O(1) extra space besides the output.

**C++**
```cpp
vector<int> rabinKarp(string text, string pat) {
    const long long B = 256, P = 1000000007LL;
    int n = text.size(), m = pat.size();
    vector<int> res;
    if (m == 0 || m > n) return res;
    long long hp = 0, ht = 0, power = 1;           // power = B^(m-1) mod P
    for (int i = 0; i < m - 1; i++) power = power * B % P;
    for (int i = 0; i < m; i++) {
        hp = (hp * B + (unsigned char)pat[i]) % P;
        ht = (ht * B + (unsigned char)text[i]) % P;
    }
    for (int i = 0; i + m <= n; i++) {
        if (hp == ht && text.compare(i, m, pat) == 0) res.push_back(i);   // verify on a hash hit
        if (i + m < n) {
            ht = (ht - (unsigned char)text[i] * power % P + P) % P;       // drop the leading char
            ht = (ht * B + (unsigned char)text[i + m]) % P;               // add the next char
        }
    }
    return res;
}
```

**Java**
```java
class Solution {
    static List<Integer> rabinKarp(String text, String pat) {
        final long B = 256, P = 1_000_000_007L;
        int n = text.length(), m = pat.length();
        List<Integer> res = new ArrayList<>();
        if (m == 0 || m > n) return res;
        long hp = 0, ht = 0, power = 1;
        for (int i = 0; i < m - 1; i++) power = power * B % P;
        for (int i = 0; i < m; i++) {
            hp = (hp * B + pat.charAt(i)) % P;
            ht = (ht * B + text.charAt(i)) % P;
        }
        for (int i = 0; i + m <= n; i++) {
            if (hp == ht && text.regionMatches(i, pat, 0, m)) res.add(i);
            if (i + m < n) {
                ht = (ht - text.charAt(i) * power % P + P) % P;
                ht = (ht * B + text.charAt(i + m)) % P;
            }
        }
        return res;
    }
}
```

#### Edge Cases & Pitfalls
- **Always verify** on a hash match. Different strings can share a hash, and only the character check makes the result correct.
- Keep the subtraction non-negative (`+ P`) before taking `%`.
- An adversary can force collisions against a fixed `B`/`P`. A random base, or double hashing with two moduli, makes that impractical.

#### Key Takeaways
- Rolling hashes make every window comparison O(1). The same idea powers duplicate-substring searches (binary search plus hashing) and the hashing route to 450.

[↑ Contents](#contents) · [← Previous](#p445) · [Next →](#p447)

---

<a id="p447"></a>

### 5. Z function

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Advanced Algo) › Advanced Problems (Less asked) | Pro | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/z-function) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
**Z-function:** for a string `s` of length `n`, `Z[i]` is the length of the longest substring starting at `i` that is also a **prefix** of `s` (with `Z[0]` defined as 0, or as n by some conventions). Use it to find every occurrence of a pattern in a text.

```text
s = "aabxaab"   ->  Z = [0, 1, 0, 0, 3, 1, 0]
pattern search: text = "xabcabzabc", pattern = "abc"  ->  [1, 7]
```

#### Intuition — reuse the rightmost Z-box
- **Naive.** Compare from each `i` against the prefix, which is O(n²).
- **Z-algorithm.** Maintain the window `[l, r)` that reaches furthest right such that `s[l … r)` matches a prefix of `s` (the "Z-box").
  - For `i < r`, position `i` mirrors position `i − l` inside the prefix, so `Z[i] ≥ min(r − i, Z[i − l])`.
  - Then extend by direct comparison past that point, and update `[l, r)` whenever the match reaches beyond `r`.
  - Every successful comparison pushes `r` to the right, so the total work is O(n).
- **Pattern matching.** Compute Z on `pattern + '$' + text`. Every `i` with `Z[i] == |pattern|` is a match at text index `i − |pattern| − 1`. The separator `$` must not appear in either string.

#### Approach 1: Naive Z-array
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
vector<int> zNaive(string s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1; i < n; i++)
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    return z;
}
```

**Java**
```java
class Solution {
    static int[] zNaive(String s) {
        int n = s.length();
        int[] z = new int[n];
        for (int i = 1; i < n; i++)
            while (i + z[i] < n && s.charAt(z[i]) == s.charAt(i + z[i])) z[i]++;
        return z;
    }
}
```

#### Approach 2: Linear Z-algorithm, plus pattern search
**Complexity:** O(n + m) time, O(n + m) space.

**C++**
```cpp
vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);              // reuse the mirrored value
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }          // new rightmost Z-box
    }
    return z;
}
vector<int> zSearch(string text, string pat) {
    vector<int> res;
    int m = pat.size();
    if (m == 0) return res;
    vector<int> z = zFunction(pat + '$' + text);
    for (size_t i = m + 1; i < z.size(); i++)
        if (z[i] == m) res.push_back(i - m - 1);
    return res;
}
```

**Java**
```java
class Solution {
    static int[] zFunction(String s) {
        int n = s.length();
        int[] z = new int[n];
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i < r) z[i] = Math.min(r - i, z[i - l]);
            while (i + z[i] < n && s.charAt(z[i]) == s.charAt(i + z[i])) z[i]++;
            if (i + z[i] > r) { l = i; r = i + z[i]; }
        }
        return z;
    }
    static List<Integer> zSearch(String text, String pat) {
        List<Integer> res = new ArrayList<>();
        int m = pat.length();
        if (m == 0) return res;
        int[] z = zFunction(pat + '$' + text);
        for (int i = m + 1; i < z.length; i++)
            if (z[i] == m) res.add(i - m - 1);
        return res;
    }
}
```

#### Edge Cases & Pitfalls
- Choose a separator that occurs in neither string. Without one, `Z` values could run past the pattern into the text.
- `[l, r)` is half-open here, so `r` is one past the end of the matched window.

#### Key Takeaways
- The Z-array and the KMP prefix function carry the same information in different shapes. Either one gives linear-time matching, the period of a string, and border problems such as 449 and 450.

[↑ Contents](#contents) · [← Previous](#p446) · [Next →](#p448)

---

<a id="p448"></a>

### 6. KMP Algorithm or LPS array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Advanced Algo) › Advanced Problems (Less asked) | Pro | No | [LeetCode](https://leetcode.com/problems/implement-strstr/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
**KMP / LPS array:** build the **LPS** (longest proper prefix that is also a suffix) array of a pattern, and use it to find the first occurrence of `needle` in `haystack` (LeetCode 28), or −1.

```text
pattern = "aabaaab"  ->  lps = [0, 1, 0, 1, 2, 2, 3]
haystack = "sadbutsad", needle = "sad"    ->  0
haystack = "leetcode",  needle = "leeto"  ->  -1
```

#### Intuition
- **What LPS means.** `lps[i]` is the length of the longest **proper** prefix of `pat[0 … i]` that is also a suffix of it.
- **Building it.** Keep `len`, the current border length:
  - if `pat[i] == pat[len]`, extend it: `lps[i] = ++len`;
  - otherwise **fall back** to `len = lps[len − 1]` and retry. The next-shorter border is exactly the border of the current border.
- **Matching.** Scan the text with `j`, the number of pattern characters matched so far:
  - on a mismatch, set `j = lps[j − 1]` instead of restarting at 0, so text characters are never re-read;
  - when `j == m`, a match ends at `i`.

#### Approach 1: Brute force
**Complexity:** O(n·m) time, O(1) space.

**C++**
```cpp
int strStrBrute(string hay, string needle) {
    int n = hay.size(), m = needle.size();
    for (int i = 0; i + m <= n; i++) {
        int j = 0;
        while (j < m && hay[i + j] == needle[j]) j++;
        if (j == m) return i;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int strStrBrute(String hay, String needle) {
        int n = hay.length(), m = needle.length();
        for (int i = 0; i + m <= n; i++) {
            int j = 0;
            while (j < m && hay.charAt(i + j) == needle.charAt(j)) j++;
            if (j == m) return i;
        }
        return -1;
    }
}
```

#### Approach 2: KMP — LPS array plus a linear scan
**Complexity:** O(n + m) time, O(m) space.

**C++**
```cpp
vector<int> buildLPS(const string& p) {
    int m = p.size();
    vector<int> lps(m, 0);
    for (int i = 1, len = 0; i < m;) {
        if (p[i] == p[len]) lps[i++] = ++len;
        else if (len > 0) len = lps[len - 1];            // fall back to the next-shorter border
        else lps[i++] = 0;
    }
    return lps;
}
int strStr(string hay, string needle) {
    int n = hay.size(), m = needle.size();
    if (m == 0) return 0;
    vector<int> lps = buildLPS(needle);
    for (int i = 0, j = 0; i < n;) {
        if (hay[i] == needle[j]) {
            i++; j++;
            if (j == m) return i - m;
        } else if (j > 0) j = lps[j - 1];                // keep i; reuse the matched border
        else i++;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int[] buildLPS(String p) {
        int m = p.length();
        int[] lps = new int[m];
        for (int i = 1, len = 0; i < m;) {
            if (p.charAt(i) == p.charAt(len)) lps[i++] = ++len;
            else if (len > 0) len = lps[len - 1];
            else lps[i++] = 0;
        }
        return lps;
    }
    static int strStr(String hay, String needle) {
        int n = hay.length(), m = needle.length();
        if (m == 0) return 0;
        int[] lps = buildLPS(needle);
        for (int i = 0, j = 0; i < n;) {
            if (hay.charAt(i) == needle.charAt(j)) {
                i++; j++;
                if (j == m) return i - m;
            } else if (j > 0) j = lps[j - 1];
            else i++;
        }
        return -1;
    }
}
```

#### Edge Cases & Pitfalls
- "Proper" means the prefix can't be the whole string, so `lps[0] = 0`.
- On a mismatch with `len > 0`, **don't** advance `i`; retry the same character with the shorter border.
- To find all occurrences, after `j == m` record `i − m` and set `j = lps[m − 1]` to continue.

#### Key Takeaways
- KMP never moves backwards in the text. The LPS array is the "how much is still matched" table, and it also solves 449 and 450 directly.

[↑ Contents](#contents) · [← Previous](#p447) · [Next →](#p449)

---

<a id="p449"></a>

### 7. Shortest Palindrome

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Advanced Algo) › Advanced Problems (Less asked) | Pro | No | [LeetCode](https://leetcode.com/problems/shortest-palindrome/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/shortest-palindrome) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
**Shortest Palindrome:** you may only add characters to the **front** of `s`. Return the shortest palindrome you can make.

```text
s = "aacecaaa"  ->  "aaacecaaa"
s = "abcd"      ->  "dcbabcd"
s = ""          ->  ""
```

#### Intuition
- **The key fact.** If the longest **palindromic prefix** of `s` has length `L`, the answer is `reverse(s[L …]) + s`. Mirror the unmatched tail onto the front, and nothing shorter works.
- **Brute force.** Test the prefixes from longest to shortest, checking each for being a palindrome. That's O(n²).
- **KMP.**
  - Build `t = s + '#' + reverse(s)`.
  - The longest palindromic prefix of `s` is the longest prefix of `s` that also appears as a suffix of `reverse(s)`.
  - That is exactly `lps[last]` of `t`. The `#` stops a border from spanning both halves.

#### Approach 1: Brute force — longest palindromic prefix by checking
**Complexity:** O(n²) time, O(n) space.

**C++**
```cpp
string shortestPalindromeBrute(string s) {
    int n = s.size(), L = 0;
    for (int len = n; len >= 1; len--) {
        int i = 0, j = len - 1;
        while (i < j && s[i] == s[j]) { i++; j--; }
        if (i >= j) { L = len; break; }
    }
    string tail = s.substr(L);
    reverse(tail.begin(), tail.end());
    return tail + s;
}
```

**Java**
```java
class Solution {
    static String shortestPalindromeBrute(String s) {
        int n = s.length(), L = 0;
        for (int len = n; len >= 1; len--) {
            int i = 0, j = len - 1;
            while (i < j && s.charAt(i) == s.charAt(j)) { i++; j--; }
            if (i >= j) { L = len; break; }
        }
        return new StringBuilder(s.substring(L)).reverse() + s;
    }
}
```

#### Approach 2: KMP on s + '#' + reverse(s)
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
string shortestPalindrome(string s) {
    string rev(s.rbegin(), s.rend());
    string t = s + '#' + rev;
    int m = t.size();
    vector<int> lps(m, 0);
    for (int i = 1, len = 0; i < m;) {
        if (t[i] == t[len]) lps[i++] = ++len;
        else if (len > 0) len = lps[len - 1];
        else lps[i++] = 0;
    }
    int L = lps[m - 1];                                // longest palindromic prefix of s
    return rev.substr(0, s.size() - L) + s;            // rev's first n-L chars = reverse of s[L..]
}
```

**Java**
```java
class Solution {
    static String shortestPalindrome(String s) {
        String rev = new StringBuilder(s).reverse().toString();
        String t = s + "#" + rev;
        int m = t.length();
        int[] lps = new int[m];
        for (int i = 1, len = 0; i < m;) {
            if (t.charAt(i) == t.charAt(len)) lps[i++] = ++len;
            else if (len > 0) len = lps[len - 1];
            else lps[i++] = 0;
        }
        int L = lps[m - 1];
        return rev.substring(0, s.length() - L) + s;
    }
}
```

#### Edge Cases & Pitfalls
- The separator is required. Without it, for `s = "aaa"` the border could run past the original string's length.
- An empty `s` returns `""`, which works naturally since `lps` of `"#"` is `[0]`.

#### Key Takeaways
- "Longest prefix of A that is a suffix of B" is one prefix-function pass over `A + # + B`.

[↑ Contents](#contents) · [← Previous](#p448) · [Next →](#p450)

---

<a id="p450"></a>

### 8. Longest happy prefix

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Strings (Advanced Algo) › Advanced Problems (Less asked) | Pro | No | [LeetCode](https://leetcode.com/problems/longest-happy-prefix/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/longest-happy-prefix) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
**Longest Happy Prefix:** return the longest **proper** prefix of `s` that is also a suffix of `s`, or `""` if none exists.

```text
s = "level"        ->  "l"
s = "ababab"       ->  "abab"
s = "leetcodeleet" ->  "leet"
s = "a"            ->  ""
```

#### Intuition
- **This is `lps[n−1]`** from KMP: the longest proper border of the whole string. Return `s.substr(0, lps[n−1])`.
- **Brute force.** Compare prefix and suffix for every length from `n−1` down to 1. That's O(n²).
- **Rolling hash.** Hash the prefix and suffix incrementally for each length, verifying on equality. That's O(n) expected.

#### Approach 1: Brute force
**Complexity:** O(n²) time, O(1) extra space.

**C++**
```cpp
string longestPrefixBrute(string s) {
    int n = s.size();
    for (int len = n - 1; len >= 1; len--)
        if (s.compare(0, len, s, n - len, len) == 0) return s.substr(0, len);
    return "";
}
```

**Java**
```java
class Solution {
    static String longestPrefixBrute(String s) {
        int n = s.length();
        for (int len = n - 1; len >= 1; len--)
            if (s.regionMatches(0, s, n - len, len)) return s.substring(0, len);
        return "";
    }
}
```

#### Approach 2: Rolling hash
The prefix hash grows on the right (`h = h·B + c`) and the suffix hash grows on the left (`h = c·B^k + h`). Matching lengths are verified, so collisions can't produce a wrong answer.

**Complexity:** O(n) expected time, O(1) extra space.

**C++**
```cpp
string longestPrefixHash(string s) {
    const long long B = 131, P = 1000000007LL;
    int n = s.size(), best = 0;
    long long pre = 0, suf = 0, pw = 1;
    for (int len = 1; len < n; len++) {
        pre = (pre * B + s[len - 1]) % P;              // hash of s[0 .. len-1]
        suf = (s[n - len] * pw + suf) % P;             // hash of s[n-len .. n-1]
        pw = pw * B % P;
        if (pre == suf && s.compare(0, len, s, n - len, len) == 0) best = len;
    }
    return s.substr(0, best);
}
```

**Java**
```java
class Solution {
    static String longestPrefixHash(String s) {
        final long B = 131, P = 1_000_000_007L;
        int n = s.length(), best = 0;
        long pre = 0, suf = 0, pw = 1;
        for (int len = 1; len < n; len++) {
            pre = (pre * B + s.charAt(len - 1)) % P;
            suf = (s.charAt(n - len) * pw + suf) % P;
            pw = pw * B % P;
            if (pre == suf && s.regionMatches(0, s, n - len, len)) best = len;
        }
        return s.substring(0, best);
    }
}
```

#### Approach 3: KMP prefix function — `lps[n − 1]`
**Complexity:** O(n) time, O(n) space.

**C++**
```cpp
string longestPrefix(string s) {
    int n = s.size();
    vector<int> lps(n, 0);
    for (int i = 1, len = 0; i < n;) {
        if (s[i] == s[len]) lps[i++] = ++len;
        else if (len > 0) len = lps[len - 1];
        else lps[i++] = 0;
    }
    return s.substr(0, n ? lps[n - 1] : 0);
}
```

**Java**
```java
class Solution {
    static String longestPrefix(String s) {
        int n = s.length();
        int[] lps = new int[n];
        for (int i = 1, len = 0; i < n;) {
            if (s.charAt(i) == s.charAt(len)) lps[i++] = ++len;
            else if (len > 0) len = lps[len - 1];
            else lps[i++] = 0;
        }
        return s.substring(0, n > 0 ? lps[n - 1] : 0);
    }
}
```

#### Edge Cases & Pitfalls
- The border must be **proper**, so it can never be the whole string. A string like `"aaaa"` gives `"aaa"`.
- Prefix and suffix may overlap, as in `"ababab"` → `"abab"`. That's allowed.

#### Key Takeaways
- The last LPS value is the "happy prefix", and `n − lps[n−1]` is the string's smallest period.

[↑ Contents](#contents) · [← Previous](#p449)

---
