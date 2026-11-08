# Bit Manipulation — Striver's A2Z DSA Sheet Notes

Section 9 of 20 · 13 problems · 12 with video, 1 without · [All sections](00-index.md)

[← Linked-List](08-linked-list.md) | [Greedy Algorithms →](10-greedy-algorithms.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Bit Fundamentals**

1. [Check if the i-th bit is Set or Not](#p208) — Basic
2. [Check if a Number is Odd or Not](#p209) — Basic
3. [Check if a Number is Power of 2 or Not](#p210) — Basic
4. [Count the Number of Set Bits](#p211) — Basic
5. [Set the Rightmost Unset Bit](#p212) — — · *no video*
6. [Swap Two Numbers](#p213) — Basic

**Problems**

7. [Minimum Bit Flips to Convert Number](#p214) — Basic
8. [Single Number - I](#p215) — Basic
9. [Single Number - II](#p216) — Core
10. [Single Number - III](#p217) — Pro
11. [Divide two numbers without multiplication and division](#p218) — Core
12. [Power Set Bit Manipulation](#p219) — Core
13. [XOR of numbers in a given range](#p220) — Core

---

## Bit Fundamentals

<a id="p208"></a>

### 1. Check if the i-th bit is Set or Not

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Bit Fundamentals | Basic | Yes | — | [Watch from 3:09](https://youtu.be/nttpF8kwgd4?t=189) |

#### Problem Statement
Given an integer `n` and a bit index `i` (0-based, counted **from the right**), report whether bit `i` of `n` is set (1).

```text
n = 13 (1101), i = 2  ->  true   (bits from the right: 1, 0, 1, 1; bit 2 is 1)
n = 13 (1101), i = 1  ->  false
n = 13,        i = 10 ->  false  (missing high bits count as 0)
```

#### Intuition
The video opens the bit-manipulation problem set with this idea: build a **mask** with a single `1` exactly where you want to look, then `&` it with the number. Every other position ANDs with 0 and becomes 0. Only the bit you care about survives.

#### Approach 1: Brute Force — convert to binary
Convert `n` to binary by repeated division by 2, collecting remainders. The `i`-th remainder is bit `i`. This works, but it spends O(log n) time and builds a string you don't need.

**Complexity:** O(log n) time, O(log n) space for the binary string.

**C++**
```cpp
bool isIthBitSetBrute(int n, int i) {
    string bin = "";                       // stored least-significant bit first
    while (n > 0) { bin += char('0' + n % 2); n /= 2; }
    if (i >= (int)bin.size()) return false;
    return bin[i] == '1';
}
```

**Java**
```java
class Solution {
    static boolean isIthBitSetBrute(int n, int i) {
        StringBuilder bin = new StringBuilder();   // stored least-significant bit first
        while (n > 0) { bin.append(n % 2); n /= 2; }
        if (i >= bin.length()) return false;
        return bin.charAt(i) == '1';
    }
}
```

#### Approach 2: Left shift — move a 1 under the bit
`1 << i` is a number with only bit `i` set. For example, `1 << 2 = 100₂`. Then:
- if `n & (1 << i)` is **non-zero**, the bit is set;
- if it is 0, the bit is unset.

For 13 and i = 2: `1101 & 0100 = 0100`, which is non-zero, so the bit is set. For i = 1: `1101 & 0010 = 0000`, so the bit is unset.

**C++**
```cpp
bool isIthBitSetLeft(int n, int i) {
    return (n & (1 << i)) != 0;
}
```

**Java**
```java
class Solution {
    static boolean isIthBitSetLeft(int n, int i) {
        return (n & (1 << i)) != 0;
    }
}
```

#### Approach 3: Right shift — move the bit to position 0
`n >> i` drops the lowest `i` bits ("they fall off the cliff"), which brings bit `i` to the far right. Then `& 1` isolates it.

For 13 and i = 2: `1101 >> 2 = 11`, and `11 & 1 = 1`, so the bit is set.

**Complexity (both shift versions):** O(1) time and space. Bitwise operations are among the fastest operations a CPU performs.

**C++**
```cpp
bool isIthBitSetRight(int n, int i) {
    return ((n >> i) & 1) == 1;
}
```

**Java**
```java
class Solution {
    static boolean isIthBitSetRight(int n, int i) {
        return ((n >> i) & 1) == 1;
    }
}
```

#### Related operations from the same video: set, clear, toggle bit `i`
The video uses the same mask `1 << i` for three more one-liners.

| Operation | Expression | Why it works | Example (n = 13 = 1101, i = 2 / i = 1) |
|---|---|---|---|
| **Set** bit i | `n \| (1 << i)` | ORing with 1 always gives 1; ORing with 0 keeps the bit | `9 (1001) \| 0100 = 1101 = 13` |
| **Clear** bit i | `n & ~(1 << i)` | `~mask` is all 1s except a 0 at i. AND keeps every other bit and forces bit i to 0 | `1101 & 1011 = 1001 = 9` |
| **Toggle** bit i | `n ^ (1 << i)` | XOR with 1 flips a bit; XOR with 0 keeps it | i = 2: `1101 → 1001 (9)`; i = 1: `1101 → 1111 (15)` |

**C++**
```cpp
int setIthBit(int n, int i)    { return n | (1 << i); }
int clearIthBit(int n, int i)  { return n & ~(1 << i); }
int toggleIthBit(int n, int i) { return n ^ (1 << i); }
```

**Java**
```java
class Solution {
    static int setIthBit(int n, int i)    { return n | (1 << i); }
    static int clearIthBit(int n, int i)  { return n & ~(1 << i); }
    static int toggleIthBit(int n, int i) { return n ^ (1 << i); }
}
```

#### Edge Cases & Pitfalls
- Write the brackets: `n & (1 << i) != 0` parses as `n & ((1 << i) != 0)` in C++, Java and C, because `!=` binds tighter than `&`. In Java this doesn't even compile with ints.
- For `i ≥ 31` on a 32-bit int, `1 << i` overflows or is undefined *(not in video)*. Use `1LL << i` (C++) or `1L << i` (Java) with a 64-bit value.

#### Key Takeaways
- Mask with `1 << i`. Then **AND to test or clear**, **OR to set**, **XOR to toggle**.
- `(n >> i) & 1` is the other standard way to read bit `i`.

[↑ Contents](#contents) · [Next →](#p209)

---

<a id="p209"></a>

### 2. Check if a Number is Odd or Not

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Bit Fundamentals | Basic | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-even-or-odd) | [Watch from 34:00](https://youtu.be/nttpF8kwgd4?t=2040) |

#### Problem Statement
Check whether an integer `n` is odd.

```text
n = 13  ->  odd     (1101: last bit 1)
n = 6   ->  even    (110:  last bit 0)
```

#### Intuition
The video makes this point while counting set bits. In binary every bit position except the last is worth a power of two that is **even** (2, 4, 8, …). So the only bit that can make a number odd is the **last bit** (worth 1):
- 13 = 8 + 4 + **1**, so it is odd;
- 6 = 4 + 2, so it is even.

So `n & 1` is 1 exactly when `n` is odd.

#### Approach 1: Brute Force — modulo
`n % 2 == 1` (or better, `n % 2 != 0`).

**C++**
```cpp
bool isOddMod(int n) {
    return n % 2 != 0;
}
```

**Java**
```java
class Solution {
    static boolean isOddMod(int n) {
        return n % 2 != 0;
    }
}
```

#### Approach 2: Optimal — check the last bit
`(n & 1) == 1`. This is the odd check you'll find in most competitive programmers' code. In the same spirit, `n >> 1` replaces `n / 2`, as in `(low + high) >> 1` in binary search.

**Complexity:** O(1) time and space for both.

**C++**
```cpp
bool isOdd(int n) {
    return (n & 1) == 1;
}
```

**Java**
```java
class Solution {
    static boolean isOdd(int n) {
        return (n & 1) == 1;
    }
}
```

#### Edge Cases & Pitfalls
- **Negative numbers** *(not in video)*: `-3 % 2` is `-1` in C++ and Java, so `n % 2 == 1` wrongly says −3 is even. Use `n % 2 != 0`, or the bit test. In two's complement every odd number, negative ones included, has its last bit set.
- For `n >> 1` vs `n / 2` on negatives: `>>` rounds toward −∞, while `/` truncates toward 0. The two are equivalent only for non-negative `n`.

#### Key Takeaways
- Odd ⇔ last bit set ⇔ `n & 1`.

[↑ Contents](#contents) · [← Previous](#p208) · [Next →](#p210)

---

<a id="p210"></a>

### 3. Check if a Number is Power of 2 or Not

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Bit Fundamentals | Basic | No | [LeetCode](https://leetcode.com/problems/power-of-two/) | [Watch from 28:19](https://youtu.be/nttpF8kwgd4?t=1699) |

#### Problem Statement
Return `true` if `n` is a power of two (n = 2ˣ for some x ≥ 0).

```text
n = 16  ->  true   (10000)
n = 13  ->  false  (1101)
n = 32  ->  true   (100000)
```

#### Intuition
A power of two has **exactly one** set bit. The video builds the one-liner from a related trick: **removing the last set bit**.

**Observation (as in the video):** subtracting 1 turns the **rightmost set bit into 0** and every 0 to its right into 1. Everything to its left is unchanged.
```text
 16 = 10000      40 = 101000      84 = 1010100
 15 = 01111      39 = 100111      83 = 1010011
```
The reason: 40 = 32 + **8**. Subtracting 1 leaves 32 alone and turns 8 into 7 = 4 + 2 + 1, which is the run of ones.

So `n & (n − 1)` **removes the last set bit**:
- 40 & 39 = `101000 & 100111 = 100000` (32);
- 84 & 83 = `1010000` (80);
- 16 & 15 = 0.

Applying this to powers of two: there is only one set bit, so removing it leaves **0**. Any other number keeps some bits on the left, so the result is non-zero.

#### Approach 1: Brute Force — count the set bits
Convert to binary (repeated division) and check that there is exactly one `1`.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
bool isPowerOfTwoBrute(int n) {
    if (n <= 0) return false;
    int ones = 0;
    while (n > 0) { ones += n % 2; n /= 2; }
    return ones == 1;
}
```

**Java**
```java
class Solution {
    static boolean isPowerOfTwoBrute(int n) {
        if (n <= 0) return false;
        int ones = 0;
        while (n > 0) { ones += n % 2; n /= 2; }
        return ones == 1;
    }
}
```

#### Approach 2: Optimal — `n & (n − 1) == 0`
**Complexity:** O(1) time and space.

**C++**
```cpp
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}
```

**Java**
```java
class Solution {
    static boolean isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
}
```

#### Related operation from the same video: remove the last set bit
**C++**
```cpp
int removeLastSetBit(int n) {
    return n & (n - 1);   // 12 (1100) -> 8 (1000); 16 -> 0
}
```

**Java**
```java
class Solution {
    static int removeLastSetBit(int n) {
        return n & (n - 1);   // 12 (1100) -> 8 (1000); 16 -> 0
    }
}
```

#### Edge Cases & Pitfalls
- **`n > 0` is required** *(the video doesn't stress this)*:
  - `0 & (−1) = 0`, so 0 would wrongly pass;
  - `INT_MIN = 100…0` has one set bit and `INT_MIN & INT_MAX = 0`. It would also pass, but it is negative, not a power of two. Also, `INT_MIN − 1` overflows in C++.

  The `n > 0 &&` guard short-circuits both cases.

#### Key Takeaways
- `n & (n − 1)` clears the lowest set bit. It is the most reusable trick in this section (power of two, Kernighan's set-bit counting, Single Number III).
- Power of two ⇔ positive with exactly one set bit.

[↑ Contents](#contents) · [← Previous](#p209) · [Next →](#p211)

---

<a id="p211"></a>

### 4. Count the Number of Set Bits

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Bit Fundamentals | Basic | No | [LeetCode](https://leetcode.com/problems/number-of-1-bits/) | [Watch from 31:13](https://youtu.be/nttpF8kwgd4?t=1873) |

#### Problem Statement
Count the number of set bits (1s) in the binary representation of a non-negative integer `n` (LeetCode: *Number of 1 Bits* / Hamming weight).

```text
n = 16 (10000)  ->  1
n = 13 (1101)   ->  3
```

#### Approach 1: Brute Force — divide by 2 and count remainders
Converting decimal to binary is repeated division by 2. Every remainder of 1 is a set bit.
- 13: remainder 1 → 6: remainder 0 → 3: remainder 1 → 1: remainder 1. Count = 3.

The video loops `while (n > 1)` and adds the final 1 after the loop. `while (n > 0)` is the same thing and needs no special case.

**C++**
```cpp
int countSetBitsBrute(int n) {
    int cnt = 0;
    while (n > 0) {
        if (n % 2 == 1) cnt++;
        n = n / 2;
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countSetBitsBrute(int n) {
        int cnt = 0;
        while (n > 0) {
            if (n % 2 == 1) cnt++;
            n = n / 2;
        }
        return cnt;
    }
}
```

#### Approach 2: Same loop with bit operators
Replace the two arithmetic steps with bit operations:
- `n % 2 == 1` becomes `n & 1` (the odd check);
- `n / 2` becomes `n >> 1`.

Because `n & 1` is already 0 or 1, you can write `cnt += n & 1`. Bitwise operations are slightly faster.

**Complexity:** O(log₂ n) time, which is at most 31 iterations for an int. O(1) space.

**C++**
```cpp
int countSetBitsShift(int n) {
    int cnt = 0;
    while (n > 0) {
        cnt += n & 1;
        n = n >> 1;
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countSetBitsShift(int n) {
        int cnt = 0;
        while (n > 0) {
            cnt += n & 1;
            n = n >> 1;
        }
        return cnt;
    }
}
```

#### Approach 3: Optimal — repeatedly remove the last set bit (`n & (n − 1)`)
Each `n = n & (n − 1)` switches off exactly one set bit, the rightmost one.
- 84 = `1010100` → `1010000` → `1000000` → `0`: three steps, so 3 set bits.
- Keep going until `n == 0`. The number of steps is the answer.

**Complexity:** O(number of set bits) time. The worst case is still 31, but most numbers finish far sooner than the shift loop, which always runs about log₂ n times. O(1) space.

**C++**
```cpp
int countSetBits(int n) {
    int cnt = 0;
    while (n != 0) {
        n = n & (n - 1);
        cnt++;
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countSetBits(int n) {
        int cnt = 0;
        while (n != 0) {
            n = n & (n - 1);
            cnt++;
        }
        return cnt;
    }
}
```

#### Library functions
- C++: `__builtin_popcount(n)` (int), `__builtin_popcountll(x)` (long long), `bitset<32>(n).count()`.
- Java *(not in video)*: `Integer.bitCount(n)`, `Long.bitCount(x)`.

#### Edge Cases & Pitfalls
- **Negative input / unsigned tasks** *(not in video)*: for a negative `n`, `while (n > 0)` never runs, and `n >> 1` keeps the sign bit, so the loop would not terminate on `!= 0`.
  - The Kernighan loop (`n & (n − 1)`) counts all 32 bits of a negative int correctly in Java.
  - In C++, cast to `unsigned` first (or use `__builtin_popcount`), because `INT_MIN − 1` overflows.
  - For the shift loop in Java, use `>>>`.

#### Key Takeaways
- Three levels: divide/modulo → shift/AND → Kernighan's `n & (n − 1)`. The last runs in time proportional to the number of ones.

[↑ Contents](#contents) · [← Previous](#p210) · [Next →](#p212)

---

<a id="p212"></a>

### 5. Set the Rightmost Unset Bit

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Bit Fundamentals | — | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a non-negative integer `n`, set the **rightmost unset (0) bit** in its binary representation. If the number has no unset bit (all of its bits are 1, like 1, 3, 7, 15, …), return it unchanged.

```text
n = 6  (110)    ->  7  (111)
n = 10 (1010)   ->  11 (1011)
n = 13 (1101)   ->  15 (1111)
n = 15 (1111)   ->  15 (no unset bit)
```

#### Intuition
This is the mirror image of "remove the last set bit" (`n & (n − 1)`). Adding 1 to `n` turns the **rightmost 0 into 1** and every 1 to its right into 0:
```text
 n   = 1 0 1 1      (11)
 n+1 = 1 1 0 0      (12)
 OR  = 1 1 1 1      (15)  -> bit 2, the rightmost 0, is now set
```
ORing `n` with `n + 1` keeps all of `n`'s ones, so the trailing ones come back. The one new bit is that rightmost 0, now set.

The "all ones" case: `n` has the form `2ᵏ − 1` exactly when `n & (n + 1) == 0`. Example: `0111 & 1000 = 0`.

#### Approach 1: Brute Force — scan bits from the right
Check bits 0, 1, 2, … until you find one that's 0, but only within the number's length (up to its highest set bit). Set it with `n | (1 << i)`.

**Complexity:** O(log n) time, O(1) space.

**C++**
```cpp
int setRightmostUnsetBitBrute(int n) {
    if (n == 0) return 1;                        // "0" -> its only bit becomes 1
    for (int i = 0; (1LL << i) <= n; i++)
        if ((n & (1 << i)) == 0) return n | (1 << i);
    return n;                                    // every bit within length is 1
}
```

**Java**
```java
class Solution {
    static int setRightmostUnsetBitBrute(int n) {
        if (n == 0) return 1;                    // "0" -> its only bit becomes 1
        for (int i = 0; (1L << i) <= n; i++)
            if ((n & (1 << i)) == 0) return n | (1 << i);
        return n;                                // every bit within length is 1
    }
}
```

#### Approach 2: Optimal — `n | (n + 1)`
**Complexity:** O(1) time and space.

**C++**
```cpp
int setRightmostUnsetBit(int n) {
    if (n != 0 && (n & (n + 1)) == 0) return n;  // n = 2^k - 1: all ones already
    return n | (n + 1);
}
```

**Java**
```java
class Solution {
    static int setRightmostUnsetBit(int n) {
        if (n != 0 && (n & (n + 1)) == 0) return n;  // n = 2^k - 1: all ones already
        return n | (n + 1);
    }
}
```

#### Edge Cases & Pitfalls
- **Problem variants:** some versions (GfG-style) say to leave the number unchanged when all of its bits are set. Others treat the number as 32 bits, so 15 → 31. For the second version, simply return `n | (n + 1)`.
- `n = 0`: its binary is "0", and setting that bit gives 1. `n | (n + 1)` already gives 1. The `n != 0` guard stops 0 from being treated as "all ones".
- For `n = INT_MAX`, `n + 1` overflows. That value is all ones, so return early *(guard it if your inputs can reach that range)*.

#### Key Takeaways
- `n + 1` flips the trailing ones and the rightmost 0. `n | (n + 1)` sets that 0 without disturbing anything else.
- Companion tricks: `n & (n − 1)` (clear lowest set bit) and `n & (n + 1)` (clear trailing ones).

[↑ Contents](#contents) · [← Previous](#p211) · [Next →](#p213)

---

<a id="p213"></a>

### 6. Swap Two Numbers

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Bit Fundamentals | Basic | No | — | [Watch from 0:00](https://youtu.be/nttpF8kwgd4?t=0) |

#### Problem Statement
Swap two integers `a` and `b`. Follow-up: do it **without a third variable**.

```text
a = 5, b = 6   ->   a = 6, b = 5
```

#### Intuition — XOR recap from the video
XOR gives 1 when the number of ones is **odd** and 0 when it is even. Two facts follow:
- `x ^ x = 0`: every bit position has two equal bits;
- `x ^ 0 = x`.

XOR is also commutative and associative, so equal values cancel out wherever they appear.

#### Approach 1: Temporary variable
`temp = a; a = b; b = temp;`. You can't simply write `b = a`, because `a` has already been overwritten by then.

**C++**
```cpp
void swapTemp(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
```

**Java**
```java
class Solution {
    // Java passes ints by value, so swap inside an array (or return the pair).
    static void swapTemp(int[] v) {
        int temp = v[0];
        v[0] = v[1];
        v[1] = temp;
    }
}
```

#### Approach 2: Arithmetic, no extra variable *(not in video)*
`a = a + b; b = a − b; a = a − b;` This works, but `a + b` can overflow. In Java, wrap-around arithmetic happens to undo itself; in C++, signed overflow is undefined behaviour.

**C++**
```cpp
void swapArith(int &a, int &b) {
    a = a + b;       // risky: may overflow (UB for signed int in C++)
    b = a - b;
    a = a - b;
}
```

**Java**
```java
class Solution {
    static void swapArith(int[] v) {
        v[0] = v[0] + v[1];
        v[1] = v[0] - v[1];
        v[0] = v[0] - v[1];
    }
}
```

#### Approach 3: Optimal — XOR swap (three lines)
1. `a = a ^ b`. Now `a` holds `a ^ b`.
2. `b = a ^ b`. That is `(a ^ b) ^ b = a`, so **b becomes the original a**.
3. `a = a ^ b`. That is `(a ^ b) ^ a = b`, so **a becomes the original b**.

Dry run with a = 5 (101), b = 6 (110):
- a = 101 ^ 110 = 011 (3);
- b = 011 ^ 110 = 101 (5);
- a = 011 ^ 101 = 110 (6).

**Complexity:** O(1) time and space for every approach.

**C++**
```cpp
void swapXor(int &a, int &b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}
```

**Java**
```java
class Solution {
    static void swapXor(int[] v) {
        v[0] = v[0] ^ v[1];
        v[1] = v[0] ^ v[1];
        v[0] = v[0] ^ v[1];
    }
}
```

#### Edge Cases & Pitfalls
- **Aliasing** *(not in video)*: if `a` and `b` are the **same variable**, e.g. `swapXor(x, x)` or swapping `arr[i]` with `arr[j]` when `i == j`, the first line makes it 0 and the value is lost. Guard with `if (&a != &b)` or `if (i != j)`.
- XOR swap never overflows, unlike the arithmetic version.
- In practice, `std::swap` or a temp variable is clearer and just as fast. The XOR version is an interview-trick answer.

#### Key Takeaways
- `x ^ x = 0` and `x ^ 0 = x` are the two facts behind every "cancel out the pairs" XOR trick that follows in this section.

[↑ Contents](#contents) · [← Previous](#p212) · [Next →](#p214)

---

## Problems

<a id="p214"></a>

### 7. Minimum Bit Flips to Convert Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Problems | Basic | No | [LeetCode](https://leetcode.com/problems/minimum-bit-flips-to-convert-number/) | [Watch](https://youtu.be/OOdrmcfZXd8) |

#### Problem Statement
Given two non-negative integers `start` and `goal`, return the **minimum number of bit flips** needed to turn `start` into `goal`.

```text
start = 10 (1010), goal = 7 (0111)  ->  3   (bits 0, 1 and 3 differ)
start = 3  (011),  goal = 4 (100)   ->  3
```

#### Intuition
Each bit that **differs** between the two numbers must be flipped once. Bits that already match need nothing. Which operator marks the differing positions?
- AND and OR can't: both give the same answer for `1,1` as for one of the mixed cases.
- **XOR** gives 1 exactly when the bits differ: `0^1 = 1^0 = 1`, `0^0 = 1^1 = 0`.

So `start ^ goal` has a 1 at every position that needs flipping. **The answer is the number of set bits in `start ^ goal`.**

For 10 and 7: `1010 ^ 0111 = 1101 = 13`, which has 3 set bits.

#### Approach 1: XOR, then check all 32 bits
Loop `i = 0..31` and count the bits where `x & (1 << i)` is non-zero.

**Complexity:** O(31) time, O(1) space.

**C++**
```cpp
int minBitFlipsAll(int start, int goal) {
    int x = start ^ goal, cnt = 0;
    for (int i = 0; i < 31; i++)
        if (x & (1 << i)) cnt++;
    return cnt;
}
```

**Java**
```java
class Solution {
    static int minBitFlipsAll(int start, int goal) {
        int x = start ^ goal, cnt = 0;
        for (int i = 0; i < 31; i++)
            if ((x & (1 << i)) != 0) cnt++;
        return cnt;
    }
}
```

#### Approach 2: XOR, then divide by 2 until it reaches 0
There's no need to visit all 31 bits. Every bit above the highest set bit is 0, so keep taking `x % 2` (or `x & 1`) and halving `x` until it reaches 0. For 13: 1, 0, 1, 1, which gives 3.

**Complexity:** O(log₂(start ^ goal)) time, O(1) space.

**C++**
```cpp
int minBitFlips(int start, int goal) {
    int x = start ^ goal, cnt = 0;
    while (x > 0) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int minBitFlips(int start, int goal) {
        int x = start ^ goal, cnt = 0;
        while (x > 0) {
            cnt += x & 1;
            x >>= 1;
        }
        return cnt;
    }
}
```

#### Shortcut *(not in video)*
`__builtin_popcount(start ^ goal)` (C++) or `Integer.bitCount(start ^ goal)` (Java). Kernighan's `x &= x − 1` loop from the set-bit counting problem also works.

#### Key Takeaways
- "Positions where two numbers differ" means `a ^ b`. Hamming distance is `popcount(a ^ b)`.

[↑ Contents](#contents) · [← Previous](#p213) · [Next →](#p215)

---

<a id="p215"></a>

### 8. Single Number - I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Problems | Basic | No | [LeetCode](https://leetcode.com/problems/single-number/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/single-number-i) | [Watch from 22:49](https://youtu.be/bYWLJb3vCWY?t=1369) |

#### Problem Statement
In a non-empty array, every element appears **twice** except one, which appears **once**. Find that element. The intended solution runs in linear time with constant extra space.

```text
nums = [1, 1, 2, 3, 3, 4, 4]   ->   2
```

#### Approach 1: Brute Force — count each element by linear search
For each `nums[i]`, count how many times it appears in the whole array. The one with count 1 is the answer.

**Complexity:** O(n²) time, O(1) space.

**C++**
```cpp
int singleNumberBrute(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        int num = nums[i], cnt = 0;
        for (int j = 0; j < n; j++)
            if (nums[j] == num) cnt++;
        if (cnt == 1) return num;
    }
    return -1;
}
```

**Java**
```java
class Solution {
    static int singleNumberBrute(int[] nums) {
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            int num = nums[i], cnt = 0;
            for (int j = 0; j < n; j++)
                if (nums[j] == num) cnt++;
            if (cnt == 1) return num;
        }
        return -1;
    }
}
```

#### Approach 2: Better — hashing
**(a) Hash array.** Find `maxi`, make `hash[maxi + 1]`, count each value, then scan the array for the value whose count is 1.
- Time: O(3n), counting the max pass, the counting pass and the scan.
- Space: O(maxi).
- This only works for small **non-negative** values. It can't handle negatives or values like 10⁹ or 10¹².

**(b) Map.** Store `value → frequency`, then iterate the **map** and return the key whose frequency is 1. The map holds only `m = n/2 + 1` keys, since every value but one appears twice.
- Time: O(n log m) with an ordered map, or about O(n) on average with `unordered_map`/`HashMap`. The worst case for an unordered map is O(n²) if collisions pile up, so mention that in an interview.
- Space: O(n/2 + 1).

**C++**
```cpp
int singleNumberHashArray(vector<int>& nums) {      // only for small non-negative values
    int maxi = *max_element(nums.begin(), nums.end());
    vector<int> hash(maxi + 1, 0);
    for (int x : nums) hash[x]++;
    for (int x : nums) if (hash[x] == 1) return x;
    return -1;
}
int singleNumberMap(vector<int>& nums) {
    map<long long, int> mpp;
    for (int x : nums) mpp[x]++;
    for (auto& it : mpp)
        if (it.second == 1) return (int)it.first;
    return -1;
}
```

**Java**
```java
class Solution {
    static int singleNumberHashArray(int[] nums) {      // only for small non-negative values
        int maxi = nums[0];
        for (int x : nums) maxi = Math.max(maxi, x);
        int[] hash = new int[maxi + 1];
        for (int x : nums) hash[x]++;
        for (int x : nums) if (hash[x] == 1) return x;
        return -1;
    }
    static int singleNumberMap(int[] nums) {
        Map<Integer, Integer> mpp = new HashMap<>();
        for (int x : nums) mpp.put(x, mpp.getOrDefault(x, 0) + 1);
        for (Map.Entry<Integer, Integer> it : mpp.entrySet())
            if (it.getValue() == 1) return it.getKey();
        return -1;
    }
}
```

#### Approach 3: Optimal — XOR everything
- `x ^ x = 0`: pairs cancel.
- `0 ^ x = x`: what remains is the single number.
- XOR is commutative and associative, so the pairs don't need to be adjacent.

For the example: `1^1^2^3^3^4^4 = 0^2^0^0 = 2`.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int singleNumber(vector<int>& nums) {
    int xorr = 0;
    for (int x : nums) xorr ^= x;
    return xorr;
}
```

**Java**
```java
class Solution {
    static int singleNumber(int[] nums) {
        int xorr = 0;
        for (int x : nums) xorr ^= x;
        return xorr;
    }
}
```

#### Edge Cases & Pitfalls
- XOR handles negatives and any order. Only the hash-array version breaks on negative or huge values.
- The XOR trick needs **every other value to appear an even number of times**. For "thrice", see Single Number II.

#### Key Takeaways
- The video uses this problem to walk through brute → better → optimal, including the full complexity discussion for the hash array and the map.
- Pairs cancel under XOR. This is the same trick as finding the missing number with XOR.

[↑ Contents](#contents) · [← Previous](#p214) · [Next →](#p216)

---

<a id="p216"></a>

### 9. Single Number - II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Problems | Core | No | [LeetCode](https://leetcode.com/problems/single-number-ii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/single-number-ii) | [Watch](https://youtu.be/5Bb2nqA40JY) |

#### Problem Statement
Every element of `nums` appears **three times** except one, which appears **exactly once**. Find it in linear time and constant extra space. The repeated values need not be adjacent.

```text
nums = [5, 5, 5, 2, 4, 4, 4]   ->   2
nums = [0, 1, 0, 1, 0, 1, 99]  ->   99
```

#### Approach 1: Brute Force — frequency map
Count with a map, then return the key whose frequency is 1.

**Complexity:**
- Time: O(n log m + m) with an ordered map.
- Space: O(m), where `m = n/3 + 1` distinct values.

**C++**
```cpp
int singleNumberMap(vector<int>& nums) {
    map<int, int> mpp;
    for (int x : nums) mpp[x]++;
    for (auto& it : mpp)
        if (it.second == 1) return it.first;
    return -1;
}
```

**Java**
```java
class Solution {
    static int singleNumberMap(int[] nums) {
        Map<Integer, Integer> mpp = new HashMap<>();
        for (int x : nums) mpp.put(x, mpp.getOrDefault(x, 0) + 1);
        for (Map.Entry<Integer, Integer> it : mpp.entrySet())
            if (it.getValue() == 1) return it.getKey();
        return -1;
    }
}
```

#### Approach 2: Better — count each bit position
Look at one bit position across all numbers. Every value that appears thrice contributes 0 or 3 ones there. So:
- if the count of ones at that position is a **multiple of 3**, the single number has a 0 there;
- if the count is `3k + 1`, the single number has a 1 there.

Example with [5, 5, 5, 2, 4, 4, 4]:
- bit 0: 3 ones (from the 5s), so 0;
- bit 1: 1 one (from the 2), so 1;
- bit 2: 6 ones (from the 5s and 4s), so 0.

Rebuilding gives `010 = 2`. Do this for all 32 positions and set bit `b` of the answer when `cnt % 3 == 1`.

**Complexity:** O(32·n) in every case, O(1) space.

**C++**
```cpp
int singleNumberBits(vector<int>& nums) {
    unsigned ans = 0;
    for (int bit = 0; bit < 32; bit++) {
        int cnt = 0;
        for (int x : nums)
            if ((unsigned)x & (1u << bit)) cnt++;
        if (cnt % 3 == 1) ans |= (1u << bit);
    }
    return (int)ans;            // works for negatives (bit 31 = sign bit)
}
```

**Java**
```java
class Solution {
    static int singleNumberBits(int[] nums) {
        int ans = 0;
        for (int bit = 0; bit < 32; bit++) {
            int cnt = 0;
            for (int x : nums)
                if ((x & (1 << bit)) != 0) cnt++;
            if (cnt % 3 == 1) ans |= (1 << bit);
        }
        return ans;
    }
}
```

#### Approach 3: Better — sort and check each triple
After sorting, values sit in groups of three except where the single element breaks the pattern. Stand on the **middle** of each would-be triple, i.e. indices 1, 4, 7, …, stepping by 3.
- If `nums[i] != nums[i−1]`, the single element entered here, and `nums[i−1]` is the answer.
- If no mismatch is found, the single element is the **last** one.

Corner cases:
- `[2,3,3,3]` mismatches at i = 1, so 2 is returned.
- `[3,3,3,4]` finishes the loop, so `nums[n−1] = 4` is returned.
- `[1,1,1,3,4,4,4]`: i = 1 matches; i = 4 compares 4 with 3, a mismatch, so 3 is returned.

**Complexity:** O(n log n + n/3) time, O(1) extra space. The input is modified.

Why is this listed above the bit-count method? The bit count always costs 32·n. Sorting costs n·log n, and log n would only reach 32 for arrays of about 2³² elements. So in practice the sort is faster.

**C++**
```cpp
int singleNumberSort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 1; i < n; i += 3)
        if (nums[i] != nums[i - 1]) return nums[i - 1];
    return nums[n - 1];
}
```

**Java**
```java
class Solution {
    static int singleNumberSort(int[] nums) {
        Arrays.sort(nums);
        int n = nums.length;
        for (int i = 1; i < n; i += 3)
            if (nums[i] != nums[i - 1]) return nums[i - 1];
        return nums[n - 1];
    }
}
```

#### Approach 4: Optimal — `ones` / `twos` buckets
The video's disclaimer: this one has to be known beforehand. Nobody derives it on the spot. Keep two bitmask "buckets":
- `ones`: bits of numbers seen once so far, mod 3;
- `twos`: bits of numbers seen twice so far, mod 3.

The rules for `nums[i]`:
1. It goes into **ones** if it is **not in twos**: `ones = (ones ^ x) & ~twos`.
2. It goes into **twos** if it is **in ones** (already seen once). Using the *updated* `ones`, this is `twos = (twos ^ x) & ~ones`.
3. It would go into threes if it was in twos. A third bucket isn't needed: on the third occurrence it is simply removed from both, and that is all we care about.

Why XOR and not OR? XOR both **adds** (`0 ^ x = x`) and **removes** (`x ^ x = 0`). OR can only add.

Trace for a value 2 seen three times (ones, twos start at 0):

| occurrence | `ones = (ones^2) & ~twos` | `twos = (twos^2) & ~ones` |
|---|---|---|
| 1st | (0^2) & ~0 = **2** | (0^2) & ~2 = **0** |
| 2nd | (2^2) & ~0 = **0** | (0^2) & ~0 = **2** |
| 3rd | (0^2) & ~2 = **0** | (2^2) & ~0 = **0** |

After three occurrences the value has vanished from both buckets. The value that appears once stays in `ones`. All of this happens independently **per bit**, so it works for any mix of numbers in any order.

**Complexity:** O(n) time, O(1) space.

**C++**
```cpp
int singleNumber(vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int x : nums) {
        ones = (ones ^ x) & ~twos;
        twos = (twos ^ x) & ~ones;
    }
    return ones;
}
```

**Java**
```java
class Solution {
    static int singleNumber(int[] nums) {
        int ones = 0, twos = 0;
        for (int x : nums) {
            ones = (ones ^ x) & ~twos;
            twos = (twos ^ x) & ~ones;
        }
        return ones;
    }
}
```

#### Edge Cases & Pitfalls
- Negative numbers: the bit-count method must include bit 31. In C++, use `unsigned` to avoid the undefined `1 << 31`. The bucket method handles negatives naturally.
- The order of the two bucket updates matters: `twos` must use the **new** `ones`.

#### Key Takeaways
- "Appears k times except one" can always be solved by counting each bit mod k.
- The `ones`/`twos` state machine is that mod-3 counter for all bits at once.

[↑ Contents](#contents) · [← Previous](#p215) · [Next →](#p217)

---

<a id="p217"></a>

### 10. Single Number - III

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Problems | Pro | No | [LeetCode](https://leetcode.com/problems/single-number-iii/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/single-number-iii) | [Watch](https://youtu.be/UA5JnV1J2sI) |

#### Problem Statement
Every element of `nums` appears **twice** except **two distinct** elements, which appear once each. Return those two in any order, using linear time and constant extra space.

```text
nums = [2, 4, 2, 14, 3, 7, 7, 3]   ->   [14, 4]
nums = [1, 2, 1, 3, 2, 5]          ->   [3, 5]
```

#### Approach 1: Brute Force — frequency map
Count with a map, then collect the keys whose frequency is 1.

**Complexity:**
- Time: O(n log m + m) with an ordered map.
- Space: O(m), where `m = n/2 + 1`.

**C++**
```cpp
vector<int> singleNumberMap(vector<int>& nums) {
    map<int, int> mpp;
    for (int x : nums) mpp[x]++;
    vector<int> ans;
    for (auto& it : mpp)
        if (it.second == 1) ans.push_back(it.first);
    return ans;
}
```

**Java**
```java
class Solution {
    static int[] singleNumberMap(int[] nums) {
        Map<Integer, Integer> mpp = new HashMap<>();
        for (int x : nums) mpp.put(x, mpp.getOrDefault(x, 0) + 1);
        int[] ans = new int[2];
        int k = 0;
        for (Map.Entry<Integer, Integer> it : mpp.entrySet())
            if (it.getValue() == 1) ans[k++] = it.getKey();
        return ans;
    }
}
```

#### Approach 2: Optimal — XOR plus two "buckets"
1. **XOR everything.** The pairs cancel, leaving `xorr = a ^ b`, where a and b are the two answers. In the example, `14 ^ 4 = 1110 ^ 0100 = 1010 = 10`.
2. Since `a ≠ b`, `xorr` has **at least one set bit**. At every set bit of `xorr`, a and b differ. Pick the **rightmost** set bit:
   - `rightmost = (xorr & (xorr − 1)) ^ xorr`.
   - `xorr & (xorr − 1)` removes the lowest set bit. XORing with `xorr` keeps only that bit.
   - For 10 = `1010`: `1010 & 1001 = 1000`, then `1000 ^ 1010 = 0010 = 2`.
3. **Split into two buckets** by that bit:
   - bucket 1 holds numbers with the bit set: 2, 2, 14, 3, 3, 7, 7;
   - bucket 2 holds numbers without it: 4.

   a and b land in **different** buckets. Both copies of every paired number land in the **same** bucket.
4. XOR each bucket on the fly with two variables `b1` and `b2`; no actual lists are needed. The pairs cancel inside each bucket, leaving `b1 = 14` and `b2 = 4`.

**Complexity:** O(2n) time, O(1) space.

**C++**
```cpp
vector<int> singleNumber(vector<int>& nums) {
    long long xorr = 0;                       // long: see pitfall below
    for (int x : nums) xorr ^= x;
    long long rightmost = (xorr & (xorr - 1)) ^ xorr;
    int b1 = 0, b2 = 0;
    for (int x : nums) {
        if (x & rightmost) b1 ^= x;           // bucket 1: bit set
        else b2 ^= x;                         // bucket 2: bit unset
    }
    return {b1, b2};
}
```

**Java**
```java
class Solution {
    static int[] singleNumber(int[] nums) {
        long xorr = 0;
        for (int x : nums) xorr ^= x;
        long rightmost = (xorr & (xorr - 1)) ^ xorr;
        int b1 = 0, b2 = 0;
        for (int x : nums) {
            if ((x & rightmost) != 0) b1 ^= x;
            else b2 ^= x;
        }
        return new int[]{b1, b2};
    }
}
```

#### Edge Cases & Pitfalls
- **Overflow (stressed in the video):** if `xorr == INT_MIN = −2³¹`, then `xorr − 1` doesn't fit in an int. Example: `[1, 1, 0, −2³¹]`. In C++ that is undefined behaviour, so keep `xorr` in a 64-bit `long`.
  - Equivalent *(not in video)*: `xorr & -xorr` computed on `unsigned` (C++) or `long`.
- The two answers may come back in either order. LeetCode accepts both.

#### Key Takeaways
- Two unknowns hidden in one XOR: use any bit where they differ to **partition** the array, then each half reduces to Single Number I.

[↑ Contents](#contents) · [← Previous](#p216) · [Next →](#p218)

---

<a id="p218"></a>

### 11. Divide two numbers without multiplication and division

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Problems | Core | No | [LeetCode](https://leetcode.com/problems/divide-two-integers/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/divide-two-integers-without-multiplication-division-modulo) | [Watch](https://youtu.be/pBD4B1tzgVc) |

#### Problem Statement
Divide `dividend` by `divisor` **without** using multiplication, division or mod. Truncate toward zero.
- Both are 32-bit signed ints, and `divisor ≠ 0`.
- If the true quotient falls outside `[−2³¹, 2³¹ − 1]`, return the nearest bound. The only case is `−2³¹ / −1`, which returns `INT_MAX`.

```text
22 / 3      ->  7
7 / -3      ->  -2
-2^31 / -1  ->  2^31 - 1   (clamped)
```

#### Intuition
How many times can we take `divisor` out of `dividend`?
- Doing it one copy at a time is too slow when the divisor is 1.
- Instead, write the quotient in **powers of two**: `22 = 3·7 = 3·(2² + 2¹ + 2⁰)`.
- So remove the **largest** `divisor · 2ᵏ` that fits, add `2ᵏ` to the answer, and repeat on what remains.

**Signs:** the answer is negative only when exactly one of the two numbers is negative. Work with absolute values and apply the sign at the end.

#### Approach 1: Brute Force — repeated addition
Keep adding the divisor to a running `sum` while `sum + d ≤ n`, counting how many times.

**Complexity:** O(dividend / divisor) time, which can be about 2³¹ for divisor 1. That gets TLE. O(1) space.

**C++**
```cpp
int divideBrute(int dividend, int divisor) {
    if (dividend == divisor) return 1;
    bool positive = !((dividend >= 0) ^ (divisor > 0));   // same signs -> positive
    long long n = llabs((long long)dividend), d = llabs((long long)divisor);
    long long sum = 0, cnt = 0;
    while (sum + d <= n) { cnt++; sum += d; }
    if (cnt >= (1LL << 31)) return positive ? INT_MAX : INT_MIN;
    return positive ? (int)cnt : (int)-cnt;
}
```

**Java**
```java
class Solution {
    static int divideBrute(int dividend, int divisor) {
        if (dividend == divisor) return 1;
        boolean positive = !((dividend >= 0) ^ (divisor > 0));
        long n = Math.abs((long) dividend), d = Math.abs((long) divisor);
        long sum = 0, cnt = 0;
        while (sum + d <= n) { cnt++; sum += d; }
        if (cnt >= (1L << 31)) return positive ? Integer.MAX_VALUE : Integer.MIN_VALUE;
        return positive ? (int) cnt : (int) -cnt;
    }
}
```

#### Approach 2: Optimal — subtract the largest `d · 2ᵏ` each round
- While `n ≥ d`:
  1. Find the largest `cnt` with `d << cnt ≤ n`: start at 0 and grow while `n ≥ d << (cnt + 1)`.
  2. Add `1 << cnt` to the answer.
  3. Subtract `d << cnt` from `n`.
- Finally clamp:
  - `ans ≥ 2³¹` with a positive sign gives `INT_MAX`;
  - `ans ≥ 2³¹` with a negative sign gives `INT_MIN`, since −2³¹ is exactly INT_MIN.
- Otherwise apply the sign.

Dry run, 22 / 3:

| n | largest 3·2ᵏ ≤ n | ans += | n after |
|---|---|---|---|
| 22 | 12 (k = 2) | 4 | 10 |
| 10 | 6 (k = 1) | 2 | 4 |
| 4 | 3 (k = 0) | 1 | 1 |

Now 1 < 3, so stop. The answer is 7.

**Complexity:** the outer loop runs O(log n) times and the inner loop up to about 31 steps, so O((log₂ n)²) time. O(1) space.

**C++**
```cpp
int divide(int dividend, int divisor) {
    if (dividend == divisor) return 1;
    bool positive = true;
    if (dividend >= 0 && divisor < 0) positive = false;
    else if (dividend < 0 && divisor > 0) positive = false;
    long long n = llabs((long long)dividend);
    long long d = llabs((long long)divisor);
    long long ans = 0;
    while (n >= d) {
        int cnt = 0;
        while (n >= (d << (cnt + 1))) cnt++;
        ans += 1LL << cnt;
        n -= d << cnt;
    }
    if (ans >= (1LL << 31) && positive) return INT_MAX;
    if (ans >= (1LL << 31) && !positive) return INT_MIN;
    return positive ? (int)ans : (int)-ans;
}
```

**Java**
```java
class Solution {
    static int divide(int dividend, int divisor) {
        if (dividend == divisor) return 1;
        boolean positive = true;
        if (dividend >= 0 && divisor < 0) positive = false;
        else if (dividend < 0 && divisor > 0) positive = false;
        long n = Math.abs((long) dividend);
        long d = Math.abs((long) divisor);
        long ans = 0;
        while (n >= d) {
            int cnt = 0;
            while (n >= (d << (cnt + 1))) cnt++;
            ans += 1L << cnt;
            n -= d << cnt;
        }
        if (ans >= (1L << 31) && positive) return Integer.MAX_VALUE;
        if (ans >= (1L << 31) && !positive) return Integer.MIN_VALUE;
        return positive ? (int) ans : (int) -ans;
    }
}
```

#### Edge Cases & Pitfalls
- **Why use `long` when the problem says "only 32-bit integers"?** The video's answer: `abs(−2³¹) = 2³¹` doesn't fit in an int. Staying in 32 bits means a pile of special-case `if`s. Interviewers care about the powers-of-two decomposition, so state the assumption and use `long`.
  - In C++, use `long long`: `long` is 32 bits on Windows. Use `llabs` on a value already cast to `long long`, because `abs(INT_MIN)` is itself undefined.
- `d << (cnt + 1)` stays below 2³³ because `d·2ᶜⁿᵗ ≤ n ≤ 2³¹`, so a 64-bit value never overflows.
- `−2³¹ / 1` gives `ans = 2³¹` with a negative sign, which correctly returns `INT_MIN`.

#### Key Takeaways
- Any quotient is a sum of powers of two. Peel off the biggest `divisor·2ᵏ` each round, which is the binary form of long division.

[↑ Contents](#contents) · [← Previous](#p217) · [Next →](#p219)

---

<a id="p219"></a>

### 12. Power Set Bit Manipulation

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Problems | Core | No | [LeetCode](https://leetcode.com/problems/subsets/) | [Watch](https://youtu.be/LqKaUv1G3_I) |

#### Problem Statement
Given an array `nums` of **distinct** integers, return **all subsets** (the power set) in any order.

```text
nums = [1, 2, 3]  ->  [[], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]]
```

#### Intuition
- There are `2ⁿ` subsets: n = 1 gives 2, n = 2 gives 4, n = 3 gives 8, n = 4 gives 16. In bitwise terms, that is `1 << n`.
- Every number `num` from `0` to `2ⁿ − 1` is an **n-bit pattern**. Read bit `i` as "take `nums[i]`" (1) or "don't take it" (0).

| num | bits (b2 b1 b0) | subset |
|---|---|---|
| 0 | 000 | [] |
| 1 | 001 | [1] |
| 2 | 010 | [2] |
| 3 | 011 | [1, 2] |
| 4 | 100 | [3] |
| 5 | 101 | [1, 3] |
| 6 | 110 | [2, 3] |
| 7 | 111 | [1, 2, 3] |

The binary column for n = 3 is the pattern of four 0s and four 1s, then 2-2-2-2, then 1-1-1-1, which enumerates every combination exactly once.

#### Approach 1: Recursion — take / not take
This is covered in the Recursion section ("Power Set", "Subsets I"). It's included here for comparison: same output, plus O(n) recursion stack.

**C++**
```cpp
void genSubsets(int i, vector<int>& nums, vector<int>& cur, vector<vector<int>>& ans) {
    if (i == (int)nums.size()) { ans.push_back(cur); return; }
    cur.push_back(nums[i]);          // take
    genSubsets(i + 1, nums, cur, ans);
    cur.pop_back();                  // not take
    genSubsets(i + 1, nums, cur, ans);
}
vector<vector<int>> subsetsRec(vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> cur;
    genSubsets(0, nums, cur, ans);
    return ans;
}
```

**Java**
```java
class Solution {
    static void genSubsets(int i, int[] nums, List<Integer> cur, List<List<Integer>> ans) {
        if (i == nums.length) { ans.add(new ArrayList<>(cur)); return; }
        cur.add(nums[i]);                        // take
        genSubsets(i + 1, nums, cur, ans);
        cur.remove(cur.size() - 1);              // not take
        genSubsets(i + 1, nums, cur, ans);
    }
    static List<List<Integer>> subsetsRec(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        genSubsets(0, nums, new ArrayList<>(), ans);
        return ans;
    }
}
```

#### Approach 2: Optimal — bitmask enumeration (power set)
```text
subsets = 1 << n
for num in 0 .. subsets-1:
    list = []
    for i in 0 .. n-1:
        if num & (1 << i): list.add(nums[i])     // is the i-th bit set?
    ans.add(list)
```

**Complexity:**
- Time: O(2ⁿ · n).
- Space: about O(2ⁿ · n) for the output. Subsets have different sizes, so this is an upper bound; the true total is n·2ⁿ⁻¹ elements. There is no recursion stack.

**C++**
```cpp
vector<vector<int>> subsets(vector<int>& nums) {
    int n = nums.size();
    int total = 1 << n;
    vector<vector<int>> ans;
    for (int num = 0; num < total; num++) {
        vector<int> list;
        for (int i = 0; i < n; i++)
            if (num & (1 << i)) list.push_back(nums[i]);
        ans.push_back(list);
    }
    return ans;
}
```

**Java**
```java
class Solution {
    static List<List<Integer>> subsets(int[] nums) {
        int n = nums.length;
        int total = 1 << n;
        List<List<Integer>> ans = new ArrayList<>();
        for (int num = 0; num < total; num++) {
            List<Integer> list = new ArrayList<>();
            for (int i = 0; i < n; i++)
                if ((num & (1 << i)) != 0) list.add(nums[i]);
            ans.add(list);
        }
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- `1 << n` needs `n ≤ 30` for an int. That's never a problem, because the output alone would be astronomically large for any n near that.
- With duplicates in `nums`, masks produce repeated subsets. Use the sort-and-skip recursion from **Subsets II** instead.

#### Key Takeaways
- The integers `0 … 2ⁿ − 1` are exactly the subsets of an n-element set. Bit i = "include element i".

[↑ Contents](#contents) · [← Previous](#p218) · [Next →](#p220)

---

<a id="p220"></a>

### 13. XOR of numbers in a given range

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Bit Manipulation › Problems | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/xor-of-numbers-in-a-range-l-to-r) | [Watch](https://youtu.be/WqGb7159h7Q) |

#### Problem Statement
Return the XOR of all integers from `L` to `R` inclusive. The video first solves the special case `1 … n`, then extends it to a range.

```text
n = 4         ->  1^2^3^4 = 4
L = 4, R = 7  ->  4^5^6^7 = 0
L = 3, R = 5  ->  3^4^5   = 2
```

#### Approach 1: Brute Force — loop
`ans = 0`, then for every `i` in the range, `ans ^= i`.

**Complexity:** O(R − L + 1) time (O(n) for `1…n`), O(1) space.

**C++**
```cpp
int xorRangeBrute(int L, int R) {
    int ans = 0;
    for (int i = L; i <= R; i++) ans ^= i;
    return ans;
}
```

**Java**
```java
class Solution {
    static int xorRangeBrute(int L, int R) {
        int ans = 0;
        for (int i = L; i <= R; i++) ans ^= i;
        return ans;
    }
}
```

#### Approach 2: Optimal — the period-4 pattern, then prefix XOR
Write out the prefix XOR `f(n) = 1 ^ 2 ^ … ^ n`:

| n | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| f(n) | 1 | 3 | 0 | 4 | 1 | 7 | 0 | 8 | 1 | 11 | 0 | 12 |

The values repeat in blocks of four:
- `n % 4 == 1` gives **1**;
- `n % 4 == 2` gives **n + 1**;
- `n % 4 == 3` gives **0**;
- `n % 4 == 0` gives **n**.

The video's advice: know this pattern in advance. It's hard to discover live in an interview.

**For a range:** `f(R) = (1^…^(L−1)) ^ (L^…^R)`, and XORing with `f(L − 1)` cancels the common prefix, because each number XORs with itself. So

  **XOR(L…R) = f(L − 1) ^ f(R)**

Example: `f(3) ^ f(7) = 0 ^ 0 = 0`, matching `4^5^6^7`.

**Complexity:** O(1) time and space.

**C++**
```cpp
int xorTill(int n) {                 // 1 ^ 2 ^ ... ^ n  (f(0) = 0)
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    if (n % 4 == 3) return 0;
    return n;
}
int xorRange(int L, int R) {
    return xorTill(L - 1) ^ xorTill(R);
}
```

**Java**
```java
class Solution {
    static int xorTill(int n) {          // 1 ^ 2 ^ ... ^ n  (f(0) = 0)
        if (n % 4 == 1) return 1;
        if (n % 4 == 2) return n + 1;
        if (n % 4 == 3) return 0;
        return n;
    }
    static int xorRange(int L, int R) {
        return xorTill(L - 1) ^ xorTill(R);
    }
}
```

#### Edge Cases & Pitfalls
- `L = 1` calls `xorTill(0)`. The `n % 4 == 0` branch returns `n = 0`, which is the correct empty XOR.
- This is the XOR version of the prefix-sum idea `sum(L..R) = pre[R] − pre[L−1]`, because XOR is its own inverse.

#### Key Takeaways
- `f(n)` cycles with period 4: (1, n+1, 0, n) for n mod 4 = (1, 2, 3, 0).
- A range XOR is two prefix XORs combined with `^`.

[↑ Contents](#contents) · [← Previous](#p219)

---
