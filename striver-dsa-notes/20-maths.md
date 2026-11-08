# Maths — Striver's A2Z DSA Sheet Notes

Section 20 of 20 · 3 problems · 3 with video, 0 without · [All sections](00-index.md)

[← Strings (Advanced Algo)](19-strings-advanced-algo.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Sieve of Eratosthenes**

1. [Print all primes till N](#p451) — Core
2. [Prime factorisation of a Number](#p452) — Core
3. [Count primes in range L to R](#p453) — Pro

---

## Sieve of Eratosthenes

<a id="p451"></a>

### 1. Print all primes till N

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Maths › Sieve of Eratosthenes | Core | No | — | [Watch](https://youtu.be/g5Fuxn_AvSk) |

> **Video note:** the sheet doesn't link a video for this row. This problem is the subject of Striver's *L6 — Sieve of Eratosthenes* (Maths playlist), which the sheet had attached to problem 453 instead. These notes follow L6.

#### Problem Statement
Given `n`, print every prime number from 2 to `n`.

```text
n = 10  ->  2 3 5 7
n = 30  ->  2 3 5 7 11 13 17 19 23 29
```

#### Intuition
- **Brute force.** Run a primality test on each number from 2 to n, checking divisors up to √i. That's O(n·√n), too slow for n around 10⁶ or larger.
- **Sieve of Eratosthenes.** Start by marking every number as prime. For each `i` that is still marked prime, **cross out all its multiples**.
- **Optimisations from the video:**
  - start crossing out at **`i·i`**, because smaller multiples `k·i` (with `k < i`) were already crossed out by `k`'s own prime factors;
  - so the outer loop only needs to run while **`i·i ≤ n`**.
- **Complexity.** The total work is `n·(1/2 + 1/3 + 1/5 + …)` over the primes, which is **O(n log log n)**. The video notes this derivation isn't expected in interviews.

#### Approach 1: Brute force — a √n primality test for each number
**Complexity:** O(n·√n) time, O(1) space.

**C++**
```cpp
bool isPrimeNum(int x) {
    if (x < 2) return false;
    for (int d = 2; (long long)d * d <= x; d++)
        if (x % d == 0) return false;
    return true;
}
vector<int> primesTillNBrute(int n) {
    vector<int> res;
    for (int i = 2; i <= n; i++) if (isPrimeNum(i)) res.push_back(i);
    return res;
}
```

**Java**
```java
class Solution {
    static boolean isPrimeNum(int x) {
        if (x < 2) return false;
        for (int d = 2; (long) d * d <= x; d++)
            if (x % d == 0) return false;
        return true;
    }
    static List<Integer> primesTillNBrute(int n) {
        List<Integer> res = new ArrayList<>();
        for (int i = 2; i <= n; i++) if (isPrimeNum(i)) res.add(i);
        return res;
    }
}
```

#### Approach 2: Sieve of Eratosthenes (as in the video)
**Complexity:** O(n log log n) time, O(n) space.

**C++**
```cpp
vector<int> primesTillN(int n) {
    vector<int> prime(n + 1, 1);                      // 1 = still assumed prime
    for (long long i = 2; i * i <= n; i++)
        if (prime[i])
            for (long long j = i * i; j <= n; j += i) prime[j] = 0;   // multiples below i*i are already done
    vector<int> res;
    for (int i = 2; i <= n; i++) if (prime[i]) res.push_back(i);
    return res;
}
```

**Java**
```java
class Solution {
    static List<Integer> primesTillN(int n) {
        boolean[] composite = new boolean[n + 1];
        for (long i = 2; i * i <= n; i++)
            if (!composite[(int) i])
                for (long j = i * i; j <= n; j += i) composite[(int) j] = true;
        List<Integer> res = new ArrayList<>();
        for (int i = 2; i <= n; i++) if (!composite[i]) res.add(i);
        return res;
    }
}
```

#### Edge Cases & Pitfalls
- `n < 2` gives an empty list. 0 and 1 aren't prime.
- Compute `i * i` in 64-bit, or it can overflow for n near 2³¹.

#### Key Takeaways
- Precomputing primality for a whole range beats testing numbers one by one. The sieve array is reused in 452 (smallest prime factors) and 453 (prefix counts).

[↑ Contents](#contents) · [Next →](#p452)

---

<a id="p452"></a>

### 2. Prime factorisation of a Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Maths › Sieve of Eratosthenes | Core | Yes | — | [Watch](https://youtu.be/LT7XhVdeRyg) |

> **Video note:** the linked video is *L4 — Print all prime factors of a Number*, which covers the brute, better and optimal single-number approaches. This row sits under "Sieve of Eratosthenes", so the query-based version from *L8 — Smallest Prime Factor (SPF)* is also covered (Approach 4).

#### Problem Statement
Return the **distinct prime factors** of `n` in increasing order. In the query version, do this for many numbers `n ≤ 10⁵` (or so) and return each one's prime factorisation, with repeats.

```text
n = 780  ->  2 3 5 13         (780 = 2² · 3 · 5 · 13)
n = 60   ->  2 3 5            (SPF factorisation: 2 2 3 5)
n = 37   ->  37
```

#### Intuition
- **Brute force.** For every `i` from 2 to n: if `i` divides n **and** `i` is prime, it's a prime factor. That's O(n·√n).
- **Better.** Divisors come in pairs `(i, n/i)` with `i ≤ √n`. Loop only to √n and test both members of each pair for primality. That's O(√n·√n) in the worst case.
- **Optimal (divide out the factors).**
  - Loop `i` from 2. Whenever `i` divides n, record it and **divide n by `i` repeatedly**.
  - Because the smaller primes have already been removed, every `i` that divides n at this point **must be prime**, so no primality test is needed.
  - Stop at `i·i ≤ n`. Whatever remains (if it's > 1) is one last prime factor larger than √n.
  - Complexity: O(√n · log n).
- **Many queries (SPF sieve).**
  - Precompute `spf[x]`, the smallest prime factor of each `x ≤ N`, with a sieve.
  - Factorise any `x` by repeatedly dividing it by `spf[x]`, at O(log x) per query.

#### Approach 1: Brute force
**Complexity:** O(n·√n) time, O(1) extra space.

**C++**
```cpp
bool isPrimeF(int x) {
    if (x < 2) return false;
    for (int d = 2; (long long)d * d <= x; d++) if (x % d == 0) return false;
    return true;
}
vector<int> primeFactorsBrute(int n) {
    vector<int> res;
    for (int i = 2; i <= n; i++)
        if (n % i == 0 && isPrimeF(i)) res.push_back(i);
    return res;
}
```

**Java**
```java
class Solution {
    static boolean isPrimeF(int x) {
        if (x < 2) return false;
        for (int d = 2; (long) d * d <= x; d++) if (x % d == 0) return false;
        return true;
    }
    static List<Integer> primeFactorsBrute(int n) {
        List<Integer> res = new ArrayList<>();
        for (int i = 2; i <= n; i++)
            if (n % i == 0 && isPrimeF(i)) res.add(i);
        return res;
    }
}
```

#### Approach 2: Better — divisor pairs up to √n
**Complexity:** O(√n · √n) time in the worst case, O(number of factors) space.

**C++**
```cpp
bool isPrimeF(int x) {
    if (x < 2) return false;
    for (int d = 2; (long long)d * d <= x; d++) if (x % d == 0) return false;
    return true;
}
vector<int> primeFactorsBetter(int n) {
    vector<int> res;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i) continue;
        if (isPrimeF(i)) res.push_back(i);
        if (n / i != i && isPrimeF(n / i)) res.push_back(n / i);
    }
    if (isPrimeF(n)) res.push_back(n);                 // n itself prime: no divisor pairs found
    sort(res.begin(), res.end());
    return res;
}
```

**Java**
```java
class Solution {
    static boolean isPrimeF(int x) {
        if (x < 2) return false;
        for (int d = 2; (long) d * d <= x; d++) if (x % d == 0) return false;
        return true;
    }
    static List<Integer> primeFactorsBetter(int n) {
        List<Integer> res = new ArrayList<>();
        for (long i = 2; i * i <= n; i++) {
            if (n % i != 0) continue;
            if (isPrimeF((int) i)) res.add((int) i);
            if (n / i != i && isPrimeF((int) (n / i))) res.add((int) (n / i));
        }
        if (isPrimeF(n)) res.add(n);
        Collections.sort(res);
        return res;
    }
}
```

#### Approach 3: Optimal — divide out each factor up to √n (as in the video)
**Complexity:** O(√n · log n) time, O(1) extra space.

**C++**
```cpp
vector<int> primeFactors(int n) {
    vector<int> res;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);                          // i must be prime: smaller primes are gone
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) res.push_back(n);                      // leftover prime > sqrt(original n)
    return res;
}
```

**Java**
```java
class Solution {
    static List<Integer> primeFactors(int n) {
        List<Integer> res = new ArrayList<>();
        for (long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                res.add((int) i);
                while (n % i == 0) n /= i;
            }
        }
        if (n != 1) res.add(n);
        return res;
    }
}
```

#### Approach 4: Many queries — SPF sieve (L8)
**Complexity:** O(N log log N) precomputation, O(log x) per query; O(N) space.

**C++**
```cpp
vector<int> buildSPF(int N) {
    vector<int> spf(N + 1);
    for (int i = 0; i <= N; i++) spf[i] = i;            // initially each number is its own spf
    for (long long i = 2; i * i <= N; i++)
        if (spf[i] == i)                               // i is prime
            for (long long j = i * i; j <= N; j += i)
                if (spf[j] == j) spf[j] = i;           // keep the smallest prime only
    return spf;
}
vector<vector<int>> factoriseQueries(vector<int>& queries) {
    int N = queries.empty() ? 1 : *max_element(queries.begin(), queries.end());
    vector<int> spf = buildSPF(max(N, 1));
    vector<vector<int>> ans;
    for (int x : queries) {
        vector<int> f;
        while (x > 1) { f.push_back(spf[x]); x /= spf[x]; }   // O(log x)
        ans.push_back(f);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] buildSPF(int N) {
        int[] spf = new int[N + 1];
        for (int i = 0; i <= N; i++) spf[i] = i;
        for (long i = 2; i * i <= N; i++)
            if (spf[(int) i] == i)
                for (long j = i * i; j <= N; j += i)
                    if (spf[(int) j] == j) spf[(int) j] = (int) i;
        return spf;
    }
    static List<List<Integer>> factoriseQueries(int[] queries) {
        int N = 1;
        for (int x : queries) N = Math.max(N, x);
        int[] spf = buildSPF(N);
        List<List<Integer>> ans = new ArrayList<>();
        for (int x : queries) {
            List<Integer> f = new ArrayList<>();
            while (x > 1) { f.add(spf[x]); x /= spf[x]; }
            ans.add(f);
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- `n = 1` has no prime factors.
- A prime `n` must still be reported: that's the `if (n != 1)` leftover in the optimal approach.
- In the SPF sieve, only overwrite `spf[j]` while it still equals `j`, so the **smallest** prime wins.

#### Key Takeaways
- Dividing out each factor as soon as it's found guarantees every divisor you meet is prime. With many queries, precompute the SPF table once and factorise each number in O(log n).

[↑ Contents](#contents) · [← Previous](#p451) · [Next →](#p453)

---

<a id="p453"></a>

### 3. Count primes in range L to R

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Maths › Sieve of Eratosthenes | Pro | No | [LeetCode](https://leetcode.com/problems/count-primes/) | [Watch](https://youtu.be/os82DjD2-MA) |

> **Video note:** the sheet linked the Sieve lecture (L6, used for problem 451). This problem is solved in *L7 — Count Prime in a range L–R*, which these notes follow. The sheet's LeetCode link, LC 204 *Count Primes* (primes strictly less than n), is the special case L = 2, R = n − 1, covered under "Related problem".

#### Problem Statement
You get `Q` queries `[L, R]`. For each, count the primes in `[L, R]`.

```text
queries = [[3,10],[8,20],[1,5]]   ->  [3, 4, 3]   ({3,5,7}, {11,13,17,19}, {2,3,5})
```

#### Intuition — sieve once, then prefix sums
- **Brute force.** For each query, test every number in `[L, R]` with an O(√n) primality check. That's O(Q · (R − L) · √R), which is far too slow for many queries.
- **Optimal.**
  1. Sieve up to `maxR` once.
  2. Build a prefix count `cnt[i]` = the number of primes `≤ i`.
  3. Answer each query in O(1) as `cnt[R] − cnt[L − 1]`.

  The video introduces this as its first "query-based problem": precompute once, then answer quickly.

#### Approach 1: Brute force — test each number per query
**Complexity:** O(Q · (R − L) · √R) time, O(1) extra space.

**C++**
```cpp
bool isPrimeQ(int x) {
    if (x < 2) return false;
    for (int d = 2; (long long)d * d <= x; d++) if (x % d == 0) return false;
    return true;
}
vector<int> countPrimesInRangeBrute(vector<pair<int, int>>& queries) {
    vector<int> ans;
    for (auto [L, R] : queries) {
        int c = 0;
        for (int x = L; x <= R; x++) c += isPrimeQ(x);
        ans.push_back(c);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static boolean isPrimeQ(int x) {
        if (x < 2) return false;
        for (int d = 2; (long) d * d <= x; d++) if (x % d == 0) return false;
        return true;
    }
    static int[] countPrimesInRangeBrute(int[][] queries) {
        int[] ans = new int[queries.length];
        for (int k = 0; k < queries.length; k++) {
            int c = 0;
            for (int x = queries[k][0]; x <= queries[k][1]; x++) if (isPrimeQ(x)) c++;
            ans[k] = c;
        }
        return ans;
    }
}
```

#### Approach 2: Sieve plus prefix count (as in the video)
**Complexity:** O(maxR log log maxR + Q) time, O(maxR) space.

**C++**
```cpp
vector<int> countPrimesInRange(vector<pair<int, int>>& queries) {
    int maxR = 1;
    for (auto& q : queries) maxR = max(maxR, q.second);
    vector<int> prime(maxR + 1, 1);
    prime[0] = 0;
    prime[1] = 0;
    for (long long i = 2; i * i <= maxR; i++)
        if (prime[i])
            for (long long j = i * i; j <= maxR; j += i) prime[j] = 0;
    vector<int> cnt(maxR + 1, 0);                     // cnt[i] = number of primes <= i
    for (int i = 1; i <= maxR; i++) cnt[i] = cnt[i - 1] + prime[i];
    vector<int> ans;
    for (auto [L, R] : queries) ans.push_back(cnt[R] - (L > 0 ? cnt[L - 1] : 0));
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] countPrimesInRange(int[][] queries) {
        int maxR = 1;
        for (int[] q : queries) maxR = Math.max(maxR, q[1]);
        boolean[] composite = new boolean[maxR + 1];
        composite[0] = true;
        composite[1] = true;
        for (long i = 2; i * i <= maxR; i++)
            if (!composite[(int) i])
                for (long j = i * i; j <= maxR; j += i) composite[(int) j] = true;
        int[] cnt = new int[maxR + 1];
        for (int i = 1; i <= maxR; i++) cnt[i] = cnt[i - 1] + (composite[i] ? 0 : 1);
        int[] ans = new int[queries.length];
        for (int k = 0; k < queries.length; k++) {
            int L = queries[k][0], R = queries[k][1];
            ans[k] = cnt[R] - (L > 0 ? cnt[L - 1] : 0);
        }
        return ans;
    }
}
```

#### Related problem: LC 204 — Count Primes (primes strictly less than n)
**Complexity:** O(n log log n) time, O(n) space.

**C++**
```cpp
int countPrimes(int n) {
    if (n < 3) return 0;
    vector<bool> composite(n, false);
    int count = 0;
    for (long long i = 2; i < n; i++) {
        if (composite[i]) continue;
        count++;
        for (long long j = i * i; j < n; j += i) composite[j] = true;
    }
    return count;
}
```

**Java**
```java
class Solution {
    static int countPrimes(int n) {
        if (n < 3) return 0;
        boolean[] composite = new boolean[n];
        int count = 0;
        for (long i = 2; i < n; i++) {
            if (composite[(int) i]) continue;
            count++;
            for (long j = i * i; j < n; j += i) composite[(int) j] = true;
        }
        return count;
    }
}
```

#### Edge Cases & Pitfalls
- `L` can be 0 or 1. Mark 0 and 1 as non-prime, and guard `cnt[L − 1]` when `L = 0`.
- LC 204 counts primes **strictly less than** n, so the sieve is of size n and doesn't include n.

#### Key Takeaways
- Query problems: precompute once (sieve plus prefix sums), then answer each query in O(1).

[↑ Contents](#contents) · [← Previous](#p452)

---
