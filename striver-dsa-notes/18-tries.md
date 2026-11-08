# Tries — Striver's A2Z DSA Sheet Notes

Section 18 of 20 · 6 problems · 6 with video, 0 without · [All sections](00-index.md)

[← Dynamic Programming](17-dynamic-programming.md) | [Strings (Advanced Algo) →](19-strings-advanced-algo.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Theory**

1. [Trie Implementation and Operations](#p437) — Core
2. [Trie Implementation and Advanced Operations](#p438) — Core

**Problems**

3. [Longest Word with All Prefixes](#p439) — Core
4. [Number of distinct substrings in a string](#p440) — Pro · *video not transcribed*
5. [Maximum XOR of two numbers in an array](#p441) — Core
6. [Maximum Xor with an element from an array](#p442) — Pro · *video not transcribed*

---

## Theory

<a id="p437"></a>

### 1. Trie Implementation and Operations

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Tries › Theory | Core | No | [LeetCode](https://leetcode.com/problems/implement-trie-prefix-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/trie-implementation) | [Watch](https://youtu.be/dBGUmUQhjaM) |

#### Problem Statement
**Implement Trie (Prefix Tree):** support the following on lowercase words:
- `insert(word)`;
- `search(word)`, which checks whether the exact word was inserted;
- `startsWith(prefix)`, which checks whether any inserted word starts with the prefix.

```text
insert("apple"); search("apple") -> true; search("app") -> false;
startsWith("app") -> true; insert("app"); search("app") -> true
```

#### Intuition — a 26-way tree of characters
- **What a node holds.** Each node has `links[26]` (one child per letter) and a boolean `flag` that is true if **a word ends here**. The root represents the empty prefix.
- **`insert`.** Walk down the word, creating any missing child (`put`), then set `flag` on the last node.
- **`search`.** Walk down; if a link is missing, return false. At the end, return the node's `flag`.
- **`startsWith`.** The same walk, but return true as long as all the links exist. The flag doesn't matter.

The video wraps these steps in small helper methods on the node:
- `containsKey(ch)`;
- `get(ch)`;
- `put(ch, node)`;
- `setEnd()` and `isEnd()`.

#### Approach 1: Trie with node helper methods (as in the video)
**Complexity:** O(L) time per operation, where L is the word length. Space is O(total characters × 26) in the worst case.

**C++**
```cpp
struct Node {
    Node* links[26] = {nullptr};
    bool flag = false;
    bool containsKey(char ch) { return links[ch - 'a'] != nullptr; }
    void put(char ch, Node* node) { links[ch - 'a'] = node; }
    Node* get(char ch) { return links[ch - 'a']; }
    void setEnd() { flag = true; }
    bool isEnd() { return flag; }
};
class Trie {
    Node* root;
public:
    Trie() { root = new Node(); }
    void insert(string word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) node->put(ch, new Node());
            node = node->get(ch);                 // move to the reference trie
        }
        node->setEnd();
    }
    bool search(string word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) return false;
            node = node->get(ch);
        }
        return node->isEnd();
    }
    bool startsWith(string prefix) {
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containsKey(ch)) return false;
            node = node->get(ch);
        }
        return true;
    }
};
```

**Java**
```java
class Node {
    Node[] links = new Node[26];
    boolean flag = false;
    boolean containsKey(char ch) { return links[ch - 'a'] != null; }
    void put(char ch, Node node) { links[ch - 'a'] = node; }
    Node get(char ch) { return links[ch - 'a']; }
    void setEnd() { flag = true; }
    boolean isEnd() { return flag; }
}
class Trie {
    private final Node root = new Node();
    public void insert(String word) {
        Node node = root;
        for (char ch : word.toCharArray()) {
            if (!node.containsKey(ch)) node.put(ch, new Node());
            node = node.get(ch);
        }
        node.setEnd();
    }
    public boolean search(String word) {
        Node node = root;
        for (char ch : word.toCharArray()) {
            if (!node.containsKey(ch)) return false;
            node = node.get(ch);
        }
        return node.isEnd();
    }
    public boolean startsWith(String prefix) {
        Node node = root;
        for (char ch : prefix.toCharArray()) {
            if (!node.containsKey(ch)) return false;
            node = node.get(ch);
        }
        return true;
    }
}
```

#### Edge Cases & Pitfalls
- `search("app")` after inserting only `"apple"` must be **false**. The path exists but `flag` isn't set.
- Inserting the same word twice is harmless; the flag just stays true.

#### Key Takeaways
- A trie trades memory for prefix queries in O(L), independent of how many words are stored. Every later trie problem reuses this node layout.

[↑ Contents](#contents) · [Next →](#p438)

---

<a id="p438"></a>

### 2. Trie Implementation and Advanced Operations

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Tries › Theory | Core | Yes | [LeetCode](https://leetcode.com/problems/implement-trie-ii-prefix-tree/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/trie-ii-count-words-erase) | [Watch](https://youtu.be/K5pcpkEMCN0) |

#### Problem Statement
**Implement Trie II:** support the following, where the same word may be inserted many times:
- `insert(word)`;
- `countWordsEqualTo(word)`, the number of inserted copies of `word`;
- `countWordsStartingWith(prefix)`, the number of inserted words that start with `prefix`;
- `erase(word)`, which removes one copy of `word`. It's guaranteed to exist.

```text
insert("apple"); insert("apple"); countWordsEqualTo("apple") -> 2
countWordsStartingWith("app") -> 2; erase("apple"); countWordsStartingWith("app") -> 1
```

#### Intuition — two counters per node instead of a flag
Each node stores:
- **`cntPrefix`:** how many inserted words pass **through** this node, i.e. have this prefix;
- **`cntEndWith`:** how many inserted words **end** exactly here.

The operations then become:
- **insert:** walk down, `cntPrefix++` on every node passed, then `cntEndWith++` at the end;
- **countWordsEqualTo:** walk down and return `cntEndWith` at the end, or 0 if a link is missing;
- **countWordsStartingWith:** walk down and return `cntPrefix` at the end, or 0;
- **erase:** walk down with `cntPrefix--` on each node, then `cntEndWith--` at the end. Nodes are not deleted; their counters just drop to 0. The video only erases words known to exist, and checks existence first in its general form.

#### Approach 1: Counting trie (as in the video)
**Complexity:** O(L) time per operation. Space is O(total characters × 26).

**C++**
```cpp
struct Node2 {
    Node2* links[26] = {nullptr};
    int cntEndWith = 0, cntPrefix = 0;
    bool containsKey(char ch) { return links[ch - 'a'] != nullptr; }
    Node2* get(char ch) { return links[ch - 'a']; }
    void put(char ch, Node2* node) { links[ch - 'a'] = node; }
};
class Trie2 {
    Node2* root;
public:
    Trie2() { root = new Node2(); }
    void insert(const string& word) {
        Node2* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) node->put(ch, new Node2());
            node = node->get(ch);
            node->cntPrefix++;
        }
        node->cntEndWith++;
    }
    int countWordsEqualTo(const string& word) {
        Node2* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) return 0;
            node = node->get(ch);
        }
        return node->cntEndWith;
    }
    int countWordsStartingWith(const string& prefix) {
        Node2* node = root;
        for (char ch : prefix) {
            if (!node->containsKey(ch)) return 0;
            node = node->get(ch);
        }
        return node->cntPrefix;
    }
    void erase(const string& word) {
        if (countWordsEqualTo(word) == 0) return;   // guard: only erase words that exist
        Node2* node = root;
        for (char ch : word) {
            node = node->get(ch);
            node->cntPrefix--;
        }
        node->cntEndWith--;
    }
};
```

**Java**
```java
class Node2 {
    Node2[] links = new Node2[26];
    int cntEndWith = 0, cntPrefix = 0;
    boolean containsKey(char ch) { return links[ch - 'a'] != null; }
    Node2 get(char ch) { return links[ch - 'a']; }
    void put(char ch, Node2 node) { links[ch - 'a'] = node; }
}
class Trie2 {
    private final Node2 root = new Node2();
    public void insert(String word) {
        Node2 node = root;
        for (char ch : word.toCharArray()) {
            if (!node.containsKey(ch)) node.put(ch, new Node2());
            node = node.get(ch);
            node.cntPrefix++;
        }
        node.cntEndWith++;
    }
    public int countWordsEqualTo(String word) {
        Node2 node = root;
        for (char ch : word.toCharArray()) {
            if (!node.containsKey(ch)) return 0;
            node = node.get(ch);
        }
        return node.cntEndWith;
    }
    public int countWordsStartingWith(String prefix) {
        Node2 node = root;
        for (char ch : prefix.toCharArray()) {
            if (!node.containsKey(ch)) return 0;
            node = node.get(ch);
        }
        return node.cntPrefix;
    }
    public void erase(String word) {
        if (countWordsEqualTo(word) == 0) return;
        Node2 node = root;
        for (char ch : word.toCharArray()) {
            node = node.get(ch);
            node.cntPrefix--;
        }
        node.cntEndWith--;
    }
}
```

#### Edge Cases & Pitfalls
- Increment `cntPrefix` **after** moving to the child, so the root (the empty prefix) isn't counted. Prefix counts then live on the node of the prefix's last character.
- Erasing a word that doesn't exist would push counters negative. That's why the guard is there.

#### Key Takeaways
- Swapping the boolean `flag` for counters turns a set into a multiset with prefix counting.

[↑ Contents](#contents) · [← Previous](#p437) · [Next →](#p439)

---

## Problems

<a id="p439"></a>

### 3. Longest Word with All Prefixes

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Tries › Problems | Core | Yes | [LeetCode](https://leetcode.com/problems/longest-word-with-all-prefixes/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/longest-word-with-all-prefixes) | [Watch](https://youtu.be/AWnBa91lThI) |

#### Problem Statement
**Longest Word with All Prefixes / Complete String:** given a list of words, find the longest word such that **every prefix** of it is also in the list. If several have the same length, return the **lexicographically smallest**. If none exists, return `"None"` (Code Studio, as in the video) or `""` (LeetCode 1858).

```text
words = ["n","ni","nin","ninj","ninja","ninga"]  ->  "ninja"
words = ["ab","bc"]                              ->  "None"
words = ["k","ki","kir","kira","kiran"]          ->  "kiran"
```

#### Intuition
- **Insert every word** into a trie.
- **Check each word.** Walk down it; at **every** node on the path, `isEnd()` must be true, meaning that prefix is a word in the list. The video calls this check `checkIfAllPrefixExists`.
- **Keep the best word.** Among the words that pass, keep the longest, breaking ties by the smaller string.

A brute force would check each prefix against a hash set, at O(L) per prefix and O(L²) per word. The trie walk does the whole check in O(L).

#### Approach 1: Trie + prefix-flag check (as in the video)
**Complexity:** O(N·L) time for the inserts and checks, where N is the number of words and L their length; O(N·L·26) space.

**C++**
```cpp
struct TNode {
    TNode* links[26] = {nullptr};
    bool flag = false;
};
class PrefixTrie {
    TNode* root = new TNode();
public:
    void insert(const string& w) {
        TNode* node = root;
        for (char ch : w) {
            if (!node->links[ch - 'a']) node->links[ch - 'a'] = new TNode();
            node = node->links[ch - 'a'];
        }
        node->flag = true;
    }
    bool checkIfAllPrefixExists(const string& w) {
        TNode* node = root;
        for (char ch : w) {
            node = node->links[ch - 'a'];
            if (!node || !node->flag) return false;     // this prefix is not a word
        }
        return true;
    }
};
string completeString(vector<string>& words) {
    PrefixTrie t;
    for (auto& w : words) t.insert(w);
    string best = "";
    for (auto& w : words)
        if (t.checkIfAllPrefixExists(w))
            if (w.size() > best.size() || (w.size() == best.size() && w < best)) best = w;
    return best.empty() ? "None" : best;              // LeetCode 1858 expects "" instead
}
```

**Java**
```java
class TNode {
    TNode[] links = new TNode[26];
    boolean flag = false;
}
class PrefixTrie {
    private final TNode root = new TNode();
    void insert(String w) {
        TNode node = root;
        for (char ch : w.toCharArray()) {
            if (node.links[ch - 'a'] == null) node.links[ch - 'a'] = new TNode();
            node = node.links[ch - 'a'];
        }
        node.flag = true;
    }
    boolean checkIfAllPrefixExists(String w) {
        TNode node = root;
        for (char ch : w.toCharArray()) {
            node = node.links[ch - 'a'];
            if (node == null || !node.flag) return false;
        }
        return true;
    }
}
class Solution {
    static String completeString(String[] words) {
        PrefixTrie t = new PrefixTrie();
        for (String w : words) t.insert(w);
        String best = "";
        for (String w : words)
            if (t.checkIfAllPrefixExists(w))
                if (w.length() > best.length() || (w.length() == best.length() && w.compareTo(best) < 0)) best = w;
        return best.isEmpty() ? "None" : best;
    }
}
```

#### Edge Cases & Pitfalls
- A one-letter word only needs itself to be present.
- Ties are broken lexicographically: `"ninja"` vs `"ninga"` both pass in some inputs, and `"ninga"` is smaller.

#### Key Takeaways
- The trie's end-of-word flags along a path answer "are all prefixes present?" in one walk.

[↑ Contents](#contents) · [← Previous](#p438) · [Next →](#p440)

---

<a id="p440"></a>

### 4. Number of distinct substrings in a string

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Tries › Problems | Pro | Yes | [LeetCode](https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/number-of-distinct-substrings-in-a-string) | [Watch](https://youtu.be/RV0QeTyHZxo) |

> **Video available, but its auto-captions could not be used** (YouTube served no caption track, or only a garbled, wrongly-detected-language one). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
Count the number of **distinct substrings** of a string `s`. LeetCode 1698 counts non-empty substrings only. The Code Studio version used in the playlist also counts the empty string, which adds 1.

```text
s = "abab"     ->  7    (a, b, ab, ba, aba, bab, abab)      [Code Studio: 8]
s = "aaaaa"    ->  5    (a, aa, aaa, aaaa, aaaaa)           [Code Studio: 6]
s = "abcdefg"  ->  28                                       [Code Studio: 29]
```

#### Intuition
- **Brute force.** Generate all `O(n²)` substrings and insert them into a hash set. Building and hashing each string costs O(n), so this is O(n³) overall.
- **Trie.**
  - Every substring is a prefix of some suffix.
  - For each start `i`, walk `s[i … ]` character by character down **one shared trie**.
  - Each time you have to **create a new node**, you've found a substring never seen before, so count it.
  - Total: O(n²) time, with no string copies.

#### Approach 1: Brute force — hash set of substrings
**Complexity:** O(n³) time, O(n³) space in the worst case.

**C++**
```cpp
int countDistinctSubstringsBrute(string s) {
    unordered_set<string> st;
    for (size_t i = 0; i < s.size(); i++) {
        string cur;
        for (size_t j = i; j < s.size(); j++) { cur += s[j]; st.insert(cur); }
    }
    return st.size();                                  // add 1 for the Code Studio version
}
```

**Java**
```java
class Solution {
    static int countDistinctSubstringsBrute(String s) {
        Set<String> st = new HashSet<>();
        for (int i = 0; i < s.length(); i++) {
            StringBuilder cur = new StringBuilder();
            for (int j = i; j < s.length(); j++) { cur.append(s.charAt(j)); st.add(cur.toString()); }
        }
        return st.size();
    }
}
```

#### Approach 2: Trie — count newly created nodes
**Complexity:** O(n²) time, O(n²·26) space in the worst case.

**C++**
```cpp
struct SNode { SNode* links[26] = {nullptr}; };
int countDistinctSubstrings(string s) {
    SNode* root = new SNode();
    int cnt = 0;
    for (size_t i = 0; i < s.size(); i++) {
        SNode* node = root;
        for (size_t j = i; j < s.size(); j++) {
            int c = s[j] - 'a';
            if (!node->links[c]) { node->links[c] = new SNode(); cnt++; }   // new substring s[i..j]
            node = node->links[c];
        }
    }
    return cnt;                                        // Code Studio: return cnt + 1 (empty string)
}
```

**Java**
```java
class SNode { SNode[] links = new SNode[26]; }
class Solution {
    static int countDistinctSubstrings(String s) {
        SNode root = new SNode();
        int cnt = 0;
        for (int i = 0; i < s.length(); i++) {
            SNode node = root;
            for (int j = i; j < s.length(); j++) {
                int c = s.charAt(j) - 'a';
                if (node.links[c] == null) { node.links[c] = new SNode(); cnt++; }
                node = node.links[c];
            }
        }
        return cnt;
    }
}
```

#### Edge Cases & Pitfalls
- Check which convention the judge uses for the empty string, since that's an off-by-one.
- For n up to about 10⁵ you need a suffix automaton or a suffix array with LCP (`n(n+1)/2 − Σ LCP`). The trie is O(n²) in memory.

#### Key Takeaways
- Every substring is a prefix of some suffix, so the number of nodes in the trie of all suffixes equals the number of distinct substrings.

[↑ Contents](#contents) · [← Previous](#p439) · [Next →](#p441)

---

<a id="p441"></a>

### 5. Maximum XOR of two numbers in an array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Tries › Problems | Core | No | [LeetCode](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/maximum-xor-of-two-numbers-in-an-array) | [Watch](https://youtu.be/EIhAwfHubE8) |

#### Problem Statement
**Maximum XOR of Two Numbers in an Array:** return the maximum value of `nums[i] XOR nums[j]`.

```text
nums = [3, 10, 5, 25, 2, 8]   ->  28   (5 ^ 25)
nums = [14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70]  ->  127
```

#### Intuition — a binary trie, greedy from the most significant bit
- **Why greedy works.** The XOR is maximised by making the **highest** bit 1 whenever possible, since one high bit outweighs all lower bits together.
- **Build.** Insert every number into a trie over its bits, from bit 31 (or 30) down to bit 0.
- **Query, for each `x`.** Walk from the top bit down. At each bit `b`, prefer the child with the **opposite** bit `1 − b`, which makes this XOR bit 1. If that child doesn't exist, take the same bit.
- **Answer.** The maximum of those queries.

The video builds up to this in the "bit prerequisites" lecture first: checking a bit is `(x >> i) & 1`, and setting a bit is `ans | (1 << i)`.

#### Approach 1: Brute force — every pair *(not in video)*
**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int findMaximumXORBrute(vector<int>& a) {
    int best = 0;
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = i + 1; j < a.size(); j++) best = max(best, a[i] ^ a[j]);
    return best;
}
```

**Java**
```java
class Solution {
    static int findMaximumXORBrute(int[] a) {
        int best = 0;
        for (int i = 0; i < a.length; i++)
            for (int j = i + 1; j < a.length; j++) best = Math.max(best, a[i] ^ a[j]);
        return best;
    }
}
```

#### Approach 2: Binary trie (as in the video)
**Complexity:** O(n·32) time, O(n·32) space.

**C++**
```cpp
struct BNode {
    BNode* links[2] = {nullptr, nullptr};
    bool containsKey(int bit) { return links[bit] != nullptr; }
    BNode* get(int bit) { return links[bit]; }
    void put(int bit, BNode* node) { links[bit] = node; }
};
class BitTrie {
    BNode* root = new BNode();
public:
    void insert(int num) {
        BNode* node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->containsKey(bit)) node->put(bit, new BNode());
            node = node->get(bit);
        }
    }
    int getMax(int num) {                      // the trie must be non-empty
        BNode* node = root;
        int maxNum = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node->containsKey(1 - bit)) {   // opposite bit makes this XOR bit 1
                maxNum |= (1 << i);
                node = node->get(1 - bit);
            } else node = node->get(bit);
        }
        return maxNum;
    }
};
int findMaximumXOR(vector<int>& nums) {
    BitTrie t;
    for (int x : nums) t.insert(x);
    int best = 0;
    for (int x : nums) best = max(best, t.getMax(x));
    return best;
}
```

**Java**
```java
class BNode {
    BNode[] links = new BNode[2];
    boolean containsKey(int bit) { return links[bit] != null; }
    BNode get(int bit) { return links[bit]; }
    void put(int bit, BNode node) { links[bit] = node; }
}
class BitTrie {
    private final BNode root = new BNode();
    void insert(int num) {
        BNode node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node.containsKey(bit)) node.put(bit, new BNode());
            node = node.get(bit);
        }
    }
    int getMax(int num) {
        BNode node = root;
        int maxNum = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node.containsKey(1 - bit)) {
                maxNum |= (1 << i);
                node = node.get(1 - bit);
            } else node = node.get(bit);
        }
        return maxNum;
    }
}
class Solution {
    static int findMaximumXOR(int[] nums) {
        BitTrie t = new BitTrie();
        for (int x : nums) t.insert(x);
        int best = 0;
        for (int x : nums) best = Math.max(best, t.getMax(x));
        return best;
    }
}
```

#### Edge Cases & Pitfalls
- Every number must use the **same bit width** (32), so that equal bit positions line up.
- A single element gives 0 (`x ^ x`).
- Inserting first and then querying is fine, because `x` XOR itself is 0, which never beats a real pair.

#### Key Takeaways
- To maximise XOR, walk a binary trie preferring the opposite bit. The same `getMax` is the core of 442 and of max-XOR-subarray problems (using prefix XORs).

[↑ Contents](#contents) · [← Previous](#p440) · [Next →](#p442)

---

<a id="p442"></a>

### 6. Maximum Xor with an element from an array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Tries › Problems | Pro | No | [LeetCode](https://leetcode.com/problems/maximum-xor-with-an-element-from-array/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/maximum-xor-queries-trie) | [Watch](https://youtu.be/Q8LhG9Pi5KM) |

> **Video available, but its auto-captions could not be used** (YouTube served no caption track, or only a garbled, wrongly-detected-language one). These notes were therefore prepared independently, in the same format and covering the standard approaches; watch the video for the original explanation.

#### Problem Statement
**Maximum XOR with an Element from Array:** for each query `[x, m]`, return the maximum of `x XOR nums[j]` over all `nums[j] ≤ m`, or `−1` if no such `nums[j]` exists.

```text
nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]   ->  [3, 3, 7]
nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]] ->  [15, -1, 5]
```

#### Intuition — offline queries plus an incrementally built trie
- **Why answer offline.** Each query only allows numbers `≤ m`, so the queries can't share one trie built over all of `nums`.
- **Sort.** Sort `nums` ascending, and sort the queries by `m`, keeping their original indices.
- **Sweep.** Move a pointer through `nums`, inserting every `nums[j] ≤ m` before answering the query.
- **Answer.** Each query's answer is `getMax(x)`, as in 441. If nothing has been inserted yet, the answer is `−1`.

#### Approach 1: Brute force *(not in video)*
**Complexity:** O(n·q) time, O(1) extra space.

**C++**
```cpp
vector<int> maximizeXorBrute(vector<int>& nums, vector<vector<int>>& queries) {
    vector<int> ans;
    for (auto& q : queries) {
        int best = -1;
        for (int v : nums) if (v <= q[1]) best = max(best, v ^ q[0]);
        ans.push_back(best);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] maximizeXorBrute(int[] nums, int[][] queries) {
        int[] ans = new int[queries.length];
        for (int k = 0; k < queries.length; k++) {
            int best = -1;
            for (int v : nums) if (v <= queries[k][1]) best = Math.max(best, v ^ queries[k][0]);
            ans[k] = best;
        }
        return ans;
    }
}
```

#### Approach 2: Offline sort plus binary trie
**Complexity:** O(n log n + q log q + (n + q)·32) time, O(n·32 + q) space.

**C++**
```cpp
struct XNode { XNode* links[2] = {nullptr, nullptr}; };
class XorTrie {
    XNode* root = new XNode();
public:
    void insert(int num) {
        XNode* node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->links[bit]) node->links[bit] = new XNode();
            node = node->links[bit];
        }
    }
    int getMax(int num) {
        XNode* node = root;
        int maxNum = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node->links[1 - bit]) { maxNum |= (1 << i); node = node->links[1 - bit]; }
            else node = node->links[bit];
        }
        return maxNum;
    }
};
vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
    sort(nums.begin(), nums.end());
    int q = queries.size();
    vector<array<int, 3>> offline;                        // {m, x, original index}
    for (int i = 0; i < q; i++) offline.push_back({queries[i][1], queries[i][0], i});
    sort(offline.begin(), offline.end());
    vector<int> ans(q, -1);
    XorTrie t;
    size_t ind = 0;
    for (auto& [m, x, idx] : offline) {
        while (ind < nums.size() && nums[ind] <= m) t.insert(nums[ind++]);
        ans[idx] = (ind == 0) ? -1 : t.getMax(x);
    }
    return ans;
}
```

**Java**
```java
class XNode { XNode[] links = new XNode[2]; }
class XorTrie {
    private final XNode root = new XNode();
    void insert(int num) {
        XNode node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node.links[bit] == null) node.links[bit] = new XNode();
            node = node.links[bit];
        }
    }
    int getMax(int num) {
        XNode node = root;
        int maxNum = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node.links[1 - bit] != null) { maxNum |= (1 << i); node = node.links[1 - bit]; }
            else node = node.links[bit];
        }
        return maxNum;
    }
}
class Solution {
    static int[] maximizeXor(int[] nums, int[][] queries) {
        Arrays.sort(nums);
        int q = queries.length;
        Integer[] order = new Integer[q];
        for (int i = 0; i < q; i++) order[i] = i;
        Arrays.sort(order, (a, b) -> Integer.compare(queries[a][1], queries[b][1]));
        int[] ans = new int[q];
        XorTrie t = new XorTrie();
        int ind = 0;
        for (int idx : order) {
            int x = queries[idx][0], m = queries[idx][1];
            while (ind < nums.length && nums[ind] <= m) t.insert(nums[ind++]);
            ans[idx] = (ind == 0) ? -1 : t.getMax(x);
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- Return the answers in the **original** query order. Store the indices before sorting.
- If no number is `≤ m`, answer −1. Don't query an empty trie, because its walk would dereference null.

#### Key Takeaways
- **Offline processing:** when queries carry a threshold, sort them by it and grow the data structure monotonically.

[↑ Contents](#contents) · [← Previous](#p441)

---
