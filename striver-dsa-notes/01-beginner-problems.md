# Beginner Problems — Striver's A2Z DSA Sheet Notes

Section 1 of 20 · 60 problems · 35 with video, 25 without · [All sections](00-index.md)

[Sorting →](02-sorting.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Patterns**

1. [Pattern 1](#p1) — Basic
2. [Pattern 2](#p2) — Basic
3. [Pattern 3](#p3) — Basic
4. [Pattern 4](#p4) — Basic
5. [Pattern 5](#p5) — Basic
6. [Pattern 6](#p6) — Basic
7. [Pattern 7](#p7) — Basic
8. [Pattern 8](#p8) — Basic
9. [Pattern 9](#p9) — Basic
10. [Pattern 10](#p10) — Basic
11. [Pattern 11](#p11) — Basic
12. [Pattern 12](#p12) — Basic
13. [Pattern 13](#p13) — Basic
14. [Pattern 14](#p14) — Basic
15. [Pattern 15](#p15) — Basic
16. [Pattern 16](#p16) — Basic
17. [Pattern 17](#p17) — Basic
18. [Pattern 18](#p18) — Basic
19. [Pattern 19](#p19) — Basic
20. [Pattern 20](#p20) — Core
21. [Pattern 21](#p21) — Core
22. [Pattern 22](#p22) — Core

**Basic Maths**

23. [Count all Digits of a Number](#p23) — Basic
24. [Count number of odd digits in a number](#p24) — Basic · *no video*
25. [Reverse a number](#p25) — Core
26. [Palindrome Number](#p26) — Basic
27. [Return the Largest Digit in a Number](#p27) — Basic · *no video*
28. [Factorial of a given number](#p28) — Basic
29. [Check if the Number is Armstrong](#p29) — Basic
30. [Check for Perfect Number](#p30) — Basic · *no video*
31. [Check for Prime Number](#p31) — Core
32. [Count of Prime Numbers till N](#p32) — Basic · *no video*
33. [GCD of Two Numbers](#p33) — Core
34. [LCM of two numbers](#p34) — Core · *no video*
35. [Divisors of a Number](#p35) — Core

**Basic Arrays**

36. [Sum of Array Elements](#p36) — Basic · *no video*
37. [Count of odd numbers in Array](#p37) — Basic · *no video*
38. [Check if the Array is Sorted I](#p38) — Basic · *no video*
39. [Reverse an array](#p39) — Basic

**Basic Hashing**

40. [Highest Occurring Element in an Array](#p40) — Core · *no video*
41. [Second Highest Occurring Element](#p41) — Core · *no video*
42. [Sum of Highest and Lowest Frequency](#p42) — Core · *no video*

**Basic Strings**

43. [Reverse a String II](#p43) — Basic · *no video*
44. [Palindrome Check](#p44) — Core · *no video*
45. [Largest Odd Number in a String](#p45) — Core · *no video*
46. [Longest Common Prefix](#p46) — Core · *no video*
47. [Isomorphic Strings](#p47) — Basic · *no video*
48. [Rotate String](#p48) — Core · *no video*
49. [Valid Anagram](#p49) — Basic · *no video*
50. [Sort Characters by Frequency](#p50) — Core · *no video*

**Basic Recursion**

51. [Sum of First N Numbers](#p51) — Basic
52. [Factorial of a Given Number](#p52) — Basic · *no video*
53. [Sum of Array Elements II](#p53) — Basic · *no video*
54. [Reverse a String I](#p54) — Basic · *no video*
55. [Check if String is Palindrome or Not](#p55) — Basic
56. [Check if a Number is Prime or Not](#p56) — Core · *no video*
57. [Reverse an array 2](#p57) — Core · *no video*
58. [Check if the Array is Sorted II](#p58) — Basic
59. [Sum of Digits in a Given Number](#p59) — Basic · *no video*
60. [Fibonacci Number](#p60) — Core

---

## Patterns

<a id="p1"></a>

### 1. Pattern 1

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Given an integer `n`, print an `n × n` square of stars.

```text
n = 5
* * * * *
* * * * *
* * * * *
* * * * *
* * * * *
```

#### The 4 rules for printing any pattern (from the video)
Every pattern in this series uses **nested loops**: an outer loop for the rows (lines) and an inner loop for the columns.

1. **Outer loop = number of lines.** Count the rows; that decides how many times the outer loop runs.
2. **Inner loop = columns, connected to the row number.** For each row, work out how many columns are printed and express that count in terms of the row index `i`.
3. **Print inside the inner loop.** Whatever is printed (star, number, letter) goes inside the inner loop. After the inner loop, print a newline so the next row starts on a new line.
4. **Observe symmetry (optional).** Some patterns are mirror images around a middle row/column; split them into halves and handle each half with its own formula.

#### Approach
- Rows: `n` → `for i in 0..n-1`.
- Every row prints `n` stars, independent of `i` → `for j in 0..n-1`.
- Print `"* "` inside the inner loop, newline after it.

**Dry run (n = 4):** `i = 0` → `j = 0,1,2,3` prints 4 stars, then newline; the same repeats for `i = 1, 2, 3`; when `i` becomes 4 the outer condition fails and the square is complete.

**About online judges (from the video):** on coding platforms you only write the function; the hidden `main` reads `T` test cases and calls your function once per test case with a different `n`. So never hard-code the size — always take `n` as a parameter. The expected output on that judge also had a space after each star.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern1(int n) {
    for (int i = 0; i < n; i++) {          // rows
        for (int j = 0; j < n; j++) {      // columns
            cout << "* ";
        }
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern1(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print("* ");
            }
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Patterns are not interview questions at top companies, but they build loop fluency, which every DSA topic depends on.
- Outer loop → rows; inner loop → columns tied to the row; print inside; newline after each row.

[↑ Contents](#contents) · [Next →](#p2)

---

<a id="p2"></a>

### 2. Pattern 2

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a right-angled triangle of stars with `n` rows: row `i` (1-based) has `i` stars.

```text
n = 5
*
* *
* * *
* * * *
* * * * *
```

#### Approach (4-rule method)
- Outer loop: `n` rows, `i = 0..n-1`.
- Inner loop: row 0 prints 1 star, row 1 prints 2, …, row `i` prints `i + 1` stars → `for (j = 0; j <= i; j++)`.
- Print `"* "` inside, newline after.

**Dry run:** `i = 0` → `j` runs 0..0 (1 star); `i = 1` → `j` runs 0..1 (2 stars); `i = 2` → 0..2 (3 stars), and so on.

**Complexity:** Time O(n²) (about n²/2 prints), Space O(1).

**C++**
```cpp
void pattern2(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) cout << "* ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern2(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) System.out.print("* ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- The inner loop bound depends on the outer variable (`j <= i`) — this is the "connect columns to rows" rule.

[↑ Contents](#contents) · [← Previous](#p1) · [Next →](#p3)

---

<a id="p3"></a>

### 3. Pattern 3

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a right-angled number triangle: row `i` prints `1 2 … i`.

```text
n = 5
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
```

#### Approach (4-rule method)
- The video switches to **1-based** rows here for simplicity: `i = 1..n`.
- Row `i` prints the numbers from 1 to `i` → inner loop `j = 1..i`.
- What is printed is exactly the inner-loop counter `j`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern3(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) cout << j << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern3(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print(j + " ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- 0-based or 1-based indexing is your choice; only the loop bounds change. Pick whichever makes the formula simplest.

[↑ Contents](#contents) · [← Previous](#p2) · [Next →](#p4)

---

<a id="p4"></a>

### 4. Pattern 4

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a triangle where row `i` contains the number `i` repeated `i` times.

```text
n = 5
1
2 2
3 3 3
4 4 4 4
5 5 5 5 5
```

#### Approach (4-rule method)
Same loops as Pattern 3 (`i = 1..n`, `j = 1..i`), but on every column we print the **row number `i`** instead of `j`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern4(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) cout << i << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern4(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print(i + " ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Changing only *what* you print (row number vs column counter) turns one pattern into another.

[↑ Contents](#contents) · [← Previous](#p3) · [Next →](#p5)

---

<a id="p5"></a>

### 5. Pattern 5

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print an inverted right-angled triangle of stars: the first row has `n` stars, the last has 1.

```text
n = 5
* * * * *
* * * *
* * *
* *
*
```

#### Approach (4-rule method)
- Outer loop: `n` rows.
- With 1-based rows, row 1 prints 5, row 2 prints 4, … → row `i` prints `n - i + 1` stars.
- With 0-based rows (as in the code below) row `i` prints `n - i` stars → `for (j = 0; j < n - i; j++)`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern5(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) cout << "* ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern5(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i; j++) System.out.print("* ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- For a decreasing count, express it as "total minus row number" and adjust by ±1 depending on your indexing.

[↑ Contents](#contents) · [← Previous](#p4) · [Next →](#p6)

---

<a id="p6"></a>

### 6. Pattern 6

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print an inverted number triangle: row `i` prints `1 2 … (n - i + 1)`.

```text
n = 5
1 2 3 4 5
1 2 3 4
1 2 3
1 2
1
```

#### Approach (4-rule method)
Exactly the loops of Pattern 5, but print the column counter (`j`, starting from 1) instead of a star.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern6(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n - i; j++) cout << j << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern6(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= n - i; j++) System.out.print(j + " ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Reuse: once Pattern 5 works, Pattern 6 is a one-line change.

[↑ Contents](#contents) · [← Previous](#p5) · [Next →](#p7)

---

<a id="p7"></a>

### 7. Pattern 7

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a star pyramid with `n` rows.

```text
n = 5
    *
   ***
  *****
 *******
*********
```

#### Intuition
Each row is **spaces → stars → spaces**. The total width is `2n − 1` columns (9 for n = 5). Break the row into these three parts and find a formula for each.

| Row `i` (0-based) | spaces | stars | spaces |
|---|---|---|---|
| 0 | 4 | 1 | 4 |
| 1 | 3 | 3 | 3 |
| 2 | 2 | 5 | 2 |
| 3 | 1 | 7 | 1 |
| 4 | 0 | 9 | 0 |

- Spaces go 4, 3, 2, 1, 0 → `n − i − 1`.
- Stars go 1, 3, 5, 7, 9 → "one more than twice the row" → `2i + 1`.

#### Approach
Outer loop `i = 0..n-1`; inside it **three** inner loops: spaces (`n − i − 1`), stars (`2i + 1`), spaces (`n − i − 1`); then newline. The trailing spaces are optional visually but the video prints them to keep every row the same width.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern7(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) cout << " ";
        for (int j = 0; j < 2 * i + 1; j++) cout << "*";
        for (int j = 0; j < n - i - 1; j++) cout << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern7(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            for (int j = 0; j < 2 * i + 1; j++) System.out.print("*");
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Break a complicated row into simple segments (space / star / space) and find one formula per segment.

[↑ Contents](#contents) · [← Previous](#p6) · [Next →](#p8)

---

<a id="p8"></a>

### 8. Pattern 8

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print an inverted star pyramid with `n` rows.

```text
n = 5
*********
 *******
  *****
   ***
    *
```

#### Intuition
The reverse of Pattern 7:

| Row `i` | spaces | stars |
|---|---|---|
| 0 | 0 | 9 |
| 1 | 1 | 7 |
| 2 | 2 | 5 |
| 3 | 3 | 3 |
| 4 | 4 | 1 |

- Spaces = `i`.
- Stars decrease from `2n − 1` by 2 each row → `2n − (2i + 1)` = `2n − 2i − 1`. (The video derives it as "the Pattern 7 count `2i + 1` subtracted from `2n`.")

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern8(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) cout << " ";
        for (int j = 0; j < 2 * n - (2 * i + 1); j++) cout << "*";
        for (int j = 0; j < i; j++) cout << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern8(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) System.out.print(" ");
            for (int j = 0; j < 2 * n - (2 * i + 1); j++) System.out.print("*");
            for (int j = 0; j < i; j++) System.out.print(" ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- An inverted pattern usually means "replace `i` by its distance from the end" in each formula.

[↑ Contents](#contents) · [← Previous](#p7) · [Next →](#p9)

---

<a id="p9"></a>

### 9. Pattern 9

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a diamond of stars (an upright pyramid followed by an inverted pyramid).

```text
n = 5
    *
   ***
  *****
 *******
*********
*********
 *******
  *****
   ***
    *
```

#### Approach
The diamond is exactly **Pattern 7 followed by Pattern 8** for the same `n`. Instead of writing new loops, call both functions. The video's point: you can combine already-solved patterns to build new ones.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern7(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) cout << " ";
        for (int j = 0; j < 2 * i + 1; j++) cout << "*";
        cout << "\n";
    }
}
void pattern8(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) cout << " ";
        for (int j = 0; j < 2 * n - (2 * i + 1); j++) cout << "*";
        cout << "\n";
    }
}
void pattern9(int n) {
    pattern7(n);
    pattern8(n);
}
```

**Java**
```java
class Solution {
    static void pattern7(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            for (int j = 0; j < 2 * i + 1; j++) System.out.print("*");
            System.out.println();
        }
    }
    static void pattern8(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) System.out.print(" ");
            for (int j = 0; j < 2 * n - (2 * i + 1); j++) System.out.print("*");
            System.out.println();
        }
    }
    static void pattern9(int n) {
        pattern7(n);
        pattern8(n);
    }
}
```

#### Key Takeaways
- The middle row appears twice here because the two halves are both full pyramids — that is the expected output for this problem.

[↑ Contents](#contents) · [← Previous](#p8) · [Next →](#p10)

---

<a id="p10"></a>

### 10. Pattern 10

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a half-diamond (a sideways triangle) of stars with `2n − 1` rows.

```text
n = 5
*
**
***
****
*****
****
***
**
*
```

#### Intuition — observe symmetry (rule 4)
The pattern is symmetric about the n-th row. Unlike Pattern 9, the middle row is **not** repeated, so we cannot simply glue two triangles together; instead one loop handles both halves with a formula that flips after the middle.

- Rows: `2n − 1` (9 for n = 5) → `i = 1..2n-1`.
- Up to the middle (`i <= n`): stars = `i`.
- After the middle (`i > n`): rows 6, 7, 8, 9 need 4, 3, 2, 1 stars → stars = `2n − i`.

#### Approach
```
for i in 1..2n-1:
    stars = (i > n) ? 2n - i : i
    print stars '*'
    newline
```

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern10(int n) {
    for (int i = 1; i <= 2 * n - 1; i++) {
        int stars = (i > n) ? 2 * n - i : i;
        for (int j = 1; j <= stars; j++) cout << "*";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern10(int n) {
        for (int i = 1; i <= 2 * n - 1; i++) {
            int stars = (i > n) ? 2 * n - i : i;
            for (int j = 1; j <= stars; j++) System.out.print("*");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- When a pattern mirrors around a row, compute the count with a condition on which half you are in.

[↑ Contents](#contents) · [← Previous](#p9) · [Next →](#p11)

---

<a id="p11"></a>

### 11. Pattern 11

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a right-angled triangle of alternating 1s and 0s (binary number triangle).

```text
n = 5
1
0 1
1 0 1
0 1 0 1
1 0 1 0 1
```

#### Intuition
- It is a right-angled triangle (row `i` has `i + 1` entries).
- Rows 0, 2, 4 (even, 0-based) start with **1**; rows 1, 3 (odd) start with **0**.
- Within a row the value flips at every column: 1 → 0 → 1 …

#### Approach
For each row set `start = (i % 2 == 0) ? 1 : 0`. In the inner loop print `start`, then flip it with `start = 1 − start` (this maps 1→0 and 0→1).

**Dry run (row 3):** start = 0 → print 0, flip→1, print 1, flip→0, print 0, flip→1, print 1 → `0 1 0 1`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern11(int n) {
    for (int i = 0; i < n; i++) {
        int start = (i % 2 == 0) ? 1 : 0;
        for (int j = 0; j <= i; j++) {
            cout << start << " ";
            start = 1 - start;          // flip 1 <-> 0
        }
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern11(int n) {
        for (int i = 0; i < n; i++) {
            int start = (i % 2 == 0) ? 1 : 0;
            for (int j = 0; j <= i; j++) {
                System.out.print(start + " ");
                start = 1 - start;
            }
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- `x = 1 − x` is a handy toggle between 0 and 1.
- In the video the first attempt used `j < i` and missed a column — always check the inner-loop bound against row 0.

[↑ Contents](#contents) · [← Previous](#p10) · [Next →](#p12)

---

<a id="p12"></a>

### 12. Pattern 12

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print the "number crown" pattern.

```text
n = 4
1      1
12    21
123  321
12344321
```

#### Intuition
Each row is **numbers → spaces → numbers**.

| Row `i` (1-based) | left numbers | spaces | right numbers |
|---|---|---|---|
| 1 | 1 | 6 | 1 |
| 2 | 1 2 | 4 | 2 1 |
| 3 | 1 2 3 | 2 | 3 2 1 |
| 4 | 1 2 3 4 | 0 | 4 3 2 1 |

- Left part: `1..i`. Right part: `i..1` (same numbers in reverse).
- Spaces start at `2(n − 1)` (6 for n = 4) and **decrease by 2** every row.

#### Approach
Keep a variable `space = 2 * (n - 1)`. For each row print `1..i`, then `space` spaces, then `i..1`, newline, and finally `space -= 2`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern12(int n) {
    int space = 2 * (n - 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) cout << j;
        for (int j = 1; j <= space; j++) cout << " ";
        for (int j = i; j >= 1; j--) cout << j;
        cout << "\n";
        space -= 2;
    }
}
```

**Java**
```java
class Solution {
    static void pattern12(int n) {
        int space = 2 * (n - 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print(j);
            for (int j = 1; j <= space; j++) System.out.print(" ");
            for (int j = i; j >= 1; j--) System.out.print(j);
            System.out.println();
            space -= 2;
        }
    }
}
```

#### Key Takeaways
- When a count changes by a constant every row, you don't need a closed formula: keep a running variable and update it after each row.

[↑ Contents](#contents) · [← Previous](#p11) · [Next →](#p13)

---

<a id="p13"></a>

### 13. Pattern 13

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print an increasing number triangle (Floyd's triangle).

```text
n = 5
1
2 3
4 5 6
7 8 9 10
11 12 13 14 15
```

#### Approach
- Shape: right-angled triangle (row `i` has `i` entries, `i = 1..n`).
- Content: a single counter `num` that starts at 1 and is incremented **after every print**, and is never reset between rows.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern13(int n) {
    int num = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout << num << " ";
            num++;
        }
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern13(int n) {
        int num = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                System.out.print(num + " ");
                num++;
            }
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Declare the counter *outside* the outer loop when the numbering continues across rows.

[↑ Contents](#contents) · [← Previous](#p12) · [Next →](#p14)

---

<a id="p14"></a>

### 14. Pattern 14

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print an increasing letter triangle.

```text
n = 5
A
A B
A B C
A B C D
A B C D E
```

#### Approach
- Right-angled triangle shape (`i = 0..n-1`, row `i` has `i + 1` letters).
- Loop directly over characters: `for (ch = 'A'; ch <= 'A' + i; ch++)`.
- Characters are stored as numbers (ASCII), so `'A' + 2` is `'C'` — that is why character arithmetic works.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern14(int n) {
    for (int i = 0; i < n; i++) {
        for (char ch = 'A'; ch <= 'A' + i; ch++) cout << ch << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern14(int n) {
        for (int i = 0; i < n; i++) {
            for (char ch = 'A'; ch <= 'A' + i; ch++) System.out.print(ch + " ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- A loop variable can be a `char`; incrementing it moves to the next letter.

[↑ Contents](#contents) · [← Previous](#p13) · [Next →](#p15)

---

<a id="p15"></a>

### 15. Pattern 15

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a reverse letter triangle.

```text
n = 5
A B C D E
A B C D
A B C
A B
A
```

#### Approach
- Inverted triangle: row `i` (0-based) has `n − i` letters.
- Letters go from `'A'` to `'A' + (n − i − 1)`. Careful: the first row ends at `'A' + 4` (E), **not** `'A' + 5`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern15(int n) {
    for (int i = 0; i < n; i++) {
        for (char ch = 'A'; ch <= 'A' + (n - i - 1); ch++) cout << ch << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern15(int n) {
        for (int i = 0; i < n; i++) {
            for (char ch = 'A'; ch <= 'A' + (n - i - 1); ch++) System.out.print(ch + " ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Off-by-one errors are the main risk; check the formula on row 0 and on the last row.

[↑ Contents](#contents) · [← Previous](#p14) · [Next →](#p16)

---

<a id="p16"></a>

### 16. Pattern 16

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print the "alpha-ramp" pattern: row `i` repeats the `i`-th letter `i` times.

```text
n = 5
A
B B
C C C
D D D D
E E E E E
```

#### Approach
- Right-angled triangle shape.
- Row `i` (0-based) uses the character `'A' + i`; print it `i + 1` times.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern16(int n) {
    for (int i = 0; i < n; i++) {
        char ch = 'A' + i;
        for (int j = 0; j <= i; j++) cout << ch << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern16(int n) {
        for (int i = 0; i < n; i++) {
            char ch = (char) ('A' + i);
            for (int j = 0; j <= i; j++) System.out.print(ch + " ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- In Java, `'A' + i` is an `int`; cast it back with `(char)`.

[↑ Contents](#contents) · [← Previous](#p15) · [Next →](#p17)

---

<a id="p17"></a>

### 17. Pattern 17

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print the "alpha-hill" pattern.

```text
n = 4
   A
  ABA
 ABCBA
ABCDCBA
```

#### Intuition
- Same skeleton as the star pyramid (Pattern 7): spaces `n − i − 1`, then `2i + 1` characters, then spaces.
- The characters are symmetric: they **increase up to the middle** and then **decrease**.
- For a row with `2i + 1` characters, the break point is `(2i + 1) / 2`. While the column index `j` (1-based) is `≤` the break point we do `ch++` after printing, otherwise `ch--`.

**Dry run (row with 5 chars, breakpoint = 2):** print A (j=1 ≤ 2 → B), print B (j=2 ≤ 2 → C), print C (j=3 > 2 → B), print B (→ A), print A → `ABCBA`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern17(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) cout << " ";
        char ch = 'A';
        int breakpoint = (2 * i + 1) / 2;
        for (int j = 1; j <= 2 * i + 1; j++) {
            cout << ch;
            if (j <= breakpoint) ch++;
            else ch--;
        }
        for (int j = 0; j < n - i - 1; j++) cout << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern17(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            char ch = 'A';
            int breakpoint = (2 * i + 1) / 2;
            for (int j = 1; j <= 2 * i + 1; j++) {
                System.out.print(ch);
                if (j <= breakpoint) ch++;
                else ch--;
            }
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Symmetry inside a row: find the midpoint and switch from incrementing to decrementing.

[↑ Contents](#contents) · [← Previous](#p16) · [Next →](#p18)

---

<a id="p18"></a>

### 18. Pattern 18

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print the "alpha-triangle" pattern: each row ends at the `n`-th letter and starts one letter earlier than the previous row.

```text
n = 5
E
D E
C D E
B C D E
A B C D E
```

#### Approach
- Right-angled triangle shape.
- The last letter is always `'A' + n − 1` (E for n = 5). Row `i` (0-based) starts at `last − i` and goes up to `last`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern18(int n) {
    char last = 'A' + n - 1;
    for (int i = 0; i < n; i++) {
        for (char ch = last - i; ch <= last; ch++) cout << ch << " ";
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern18(int n) {
        char last = (char) ('A' + n - 1);
        for (int i = 0; i < n; i++) {
            for (char ch = (char) (last - i); ch <= last; ch++) System.out.print(ch + " ");
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- The video hard-codes `'E'` for n = 5; using `'A' + n − 1` makes it work for any `n` *(generalisation, not in video)*.

[↑ Contents](#contents) · [← Previous](#p17) · [Next →](#p19)

---

<a id="p19"></a>

### 19. Pattern 19

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Basic | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print the "symmetric void" pattern.

```text
n = 5
**********
****  ****
***    ***
**      **
*        *
*        *
**      **
***    ***
****  ****
**********
```

#### Intuition — observe symmetry
Split it at the middle into an **upper half** and a **lower half** (n rows each). Each row is stars → spaces → stars.

Upper half (`i = 0..n-1`):

| i | stars | spaces | stars |
|---|---|---|---|
| 0 | 5 | 0 | 5 |
| 1 | 4 | 2 | 4 |
| 2 | 3 | 4 | 3 |
| 3 | 2 | 6 | 2 |
| 4 | 1 | 8 | 1 |

stars = `n − i`; spaces start at 0 and increase by 2.

Lower half (`i = 1..n`): stars = `i`; spaces start at `2n − 2` (8) and decrease by 2.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern19(int n) {
    int spaces = 0;
    for (int i = 0; i < n; i++) {                    // upper half
        for (int j = 1; j <= n - i; j++) cout << "*";
        for (int j = 0; j < spaces; j++) cout << " ";
        for (int j = 1; j <= n - i; j++) cout << "*";
        spaces += 2;
        cout << "\n";
    }
    spaces = 2 * n - 2;
    for (int i = 1; i <= n; i++) {                   // lower half
        for (int j = 1; j <= i; j++) cout << "*";
        for (int j = 0; j < spaces; j++) cout << " ";
        for (int j = 1; j <= i; j++) cout << "*";
        spaces -= 2;
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern19(int n) {
        int spaces = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= n - i; j++) System.out.print("*");
            for (int j = 0; j < spaces; j++) System.out.print(" ");
            for (int j = 1; j <= n - i; j++) System.out.print("*");
            spaces += 2;
            System.out.println();
        }
        spaces = 2 * n - 2;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print("*");
            for (int j = 0; j < spaces; j++) System.out.print(" ");
            for (int j = 1; j <= i; j++) System.out.print("*");
            spaces -= 2;
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- For a perfectly symmetric pattern, solve the upper half, then copy the code for the lower half with the formulas reversed.

[↑ Contents](#contents) · [← Previous](#p18) · [Next →](#p20)

---

<a id="p20"></a>

### 20. Pattern 20

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Core | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print the "symmetric butterfly" pattern.

```text
n = 5
*        *
**      **
***    ***
****  ****
**********
****  ****
***    ***
**      **
*        *
```

#### Intuition
Unlike Pattern 19, the middle row appears only **once**, so there are `2n − 1` rows and the two halves can't simply be copied. Handle everything in one loop (like Pattern 10):

- Rows `i = 1..2n-1`.
- Stars on each side = `i` while `i ≤ n`, otherwise `2n − i`.
- Spaces start at `2n − 2` (8 for n = 5), **decrease by 2** while `i < n`, and **increase by 2** after the middle row.

**Dry run (n = 5):** i=1 → 1 star, 8 spaces, 1 star; … i=5 → 5 stars, 0 spaces, 5 stars; then spaces become 2: i=6 → 4 stars, 2 spaces, 4 stars; …

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern20(int n) {
    int spaces = 2 * n - 2;
    for (int i = 1; i <= 2 * n - 1; i++) {
        int stars = (i > n) ? 2 * n - i : i;
        for (int j = 1; j <= stars; j++) cout << "*";
        for (int j = 1; j <= spaces; j++) cout << " ";
        for (int j = 1; j <= stars; j++) cout << "*";
        cout << "\n";
        if (i < n) spaces -= 2;
        else spaces += 2;
    }
}
```

**Java**
```java
class Solution {
    static void pattern20(int n) {
        int spaces = 2 * n - 2;
        for (int i = 1; i <= 2 * n - 1; i++) {
            int stars = (i > n) ? 2 * n - i : i;
            for (int j = 1; j <= stars; j++) System.out.print("*");
            for (int j = 1; j <= spaces; j++) System.out.print(" ");
            for (int j = 1; j <= stars; j++) System.out.print("*");
            System.out.println();
            if (i < n) spaces -= 2;
            else spaces += 2;
        }
    }
}
```

#### Key Takeaways
- In the video the initial space count was first written wrongly (as 0); recomputing it from the first row (`2n − 2`) fixed it. Always derive starting values from row 1.

[↑ Contents](#contents) · [← Previous](#p19) · [Next →](#p21)

---

<a id="p21"></a>

### 21. Pattern 21

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Core | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print a hollow square of size `n × n` (stars on the border only).

```text
n = 4
****
*  *
*  *
****
```

#### Intuition
Run the full `n × n` grid. A cell `(i, j)` (0-based) is on the boundary if it is in the first row, last row, first column or last column:
`i == 0 || i == n − 1 || j == 0 || j == n − 1` → print `*`, otherwise print a space.

(The video notes the image on the sheet was wrong at recording time; the intended output is this hollow square.)

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern21(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0 || i == n - 1 || j == n - 1) cout << "*";
            else cout << " ";
        }
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern21(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 || j == 0 || i == n - 1 || j == n - 1) System.out.print("*");
                else System.out.print(" ");
            }
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Hollow shapes: loop over every cell and decide with a condition whether to print the character or a space.

[↑ Contents](#contents) · [← Previous](#p20) · [Next →](#p22)

---

<a id="p22"></a>

### 22. Pattern 22

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Patterns | Core | Yes | — | [Watch](https://youtu.be/tNm_NNSB3_w) |

#### Problem Statement
Print the concentric-squares number pattern.

```text
n = 4
4444444
4333334
4322234
4321234
4322234
4333334
4444444
```

#### Intuition
- The grid is `(2n − 1) × (2n − 1)` (7 × 7 for n = 4).
- Subtract every value from `n` and you get a simpler grid: the outer ring is 0, the next ring 1, …, the centre `n − 1`. Each cell's value in this new grid is its **minimum distance to any edge**.
- For cell `(i, j)`: top = `i`, left = `j`, right = `(2n − 2) − j`, bottom = `(2n − 2) − i`.
- Original value = `n − min(top, bottom, left, right)`.

**Dry run (n = 4, cell (3,3) = centre):** top=3, left=3, right=3, bottom=3 → min 3 → 4 − 3 = 1 ✔.
Cell (1,4): top=1, left=4, right=2, bottom=5 → min 1 → 4 − 1 = 3 ✔.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
void pattern22(int n) {
    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            int top = i, left = j;
            int right = (2 * n - 2) - j, bottom = (2 * n - 2) - i;
            cout << n - min(min(top, bottom), min(left, right));
        }
        cout << "\n";
    }
}
```

**Java**
```java
class Solution {
    static void pattern22(int n) {
        for (int i = 0; i < 2 * n - 1; i++) {
            for (int j = 0; j < 2 * n - 1; j++) {
                int top = i, left = j;
                int right = (2 * n - 2) - j, bottom = (2 * n - 2) - i;
                System.out.print(n - Math.min(Math.min(top, bottom), Math.min(left, right)));
            }
            System.out.println();
        }
    }
}
```

#### Key Takeaways
- Transform the problem (subtract from `n`) to reveal a simpler structure — here, "distance to the nearest edge".
- `min` takes two arguments, so nest the calls.

[↑ Contents](#contents) · [← Previous](#p21) · [Next →](#p23)

---

## Basic Maths

<a id="p23"></a>

### 23. Count all Digits of a Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Basic | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-digits-in-a-number) | [Watch](https://youtu.be/1xNbjMdbjug) |

#### Problem Statement
Given a non-negative integer `n`, return the number of digits in it.

```text
n = 156   -> 3
n = 7     -> 1
n = 7789  -> 4
```

#### Core concept from the video: extraction of digits
- `n % 10` gives the **last digit** (the remainder after dividing by 10, because every multiple of 10 ends in 0).
- `n / 10` (integer division) **removes** the last digit.
- Repeating "take `n % 10`, then `n = n / 10`" until `n` becomes 0 extracts every digit, in **reverse order**.

**Dry run (7789):** 7789 % 10 = 9, n = 778 → 778 % 10 = 8, n = 77 → 7, n = 7 → 7, n = 0 → stop. Digits extracted: 9, 8, 7, 7.

This single idea solves count digits, reverse a number, palindrome, Armstrong and more.

#### Approach 1: Count while extracting
Keep a counter and increment it once per loop iteration. (The `n % 10` itself isn't needed for counting — we only need how many times `n` can be divided by 10 before it becomes 0.)

**Complexity:** Time O(log₁₀ n) — the loop runs once per division by 10. Space O(1).
> Rule from the video: whenever the number of iterations depends on repeatedly dividing by `k`, the time complexity is O(log_k n).

**C++**
```cpp
int countDigits(int n) {
    if (n == 0) return 1;            // edge case (not in video)
    int cnt = 0;
    while (n > 0) {
        cnt++;
        n = n / 10;
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countDigits(int n) {
        if (n == 0) return 1;        // edge case (not in video)
        int cnt = 0;
        while (n > 0) {
            cnt++;
            n = n / 10;
        }
        return cnt;
    }
}
```

#### Approach 2: Using log₁₀
The number of times `n` can be divided by 10 is captured by `log₁₀(n)`. For 7789, `log₁₀(7789) ≈ 3.89`; adding 1 and taking the integer part gives 4.
`digits = (int)(log10(n)) + 1` (for `n > 0`).
If the judge says `log10` is not declared, include `<cmath>` (or `bits/stdc++.h`).

**Complexity:** O(1) per call (the log is computed by the math library). Space O(1).

**C++**
```cpp
int countDigits(int n) {
    if (n == 0) return 1;
    return (int)(log10(n)) + 1;
}
```

**Java**
```java
class Solution {
    static int countDigits(int n) {
        if (n == 0) return 1;
        return (int) Math.log10(n) + 1;
    }
}
```

#### Edge Cases & Pitfalls
- `n = 0` has 1 digit but the loop returns 0 and `log10(0)` is −∞ — handle it separately *(not in video)*.
- Negative input: take the absolute value first *(not in video)*.

#### Key Takeaways
- Master **extraction of digits** (`% 10` and `/ 10`) — it is the foundation of the whole basic-maths section.

[↑ Contents](#contents) · [← Previous](#p22) · [Next →](#p24)

---

<a id="p24"></a>

### 24. Count number of odd digits in a number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Basic | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-odd-digits-in-a-number) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a non-negative integer `n`, return how many of its digits are **odd**.

```text
n = 5    -> 1
n = 25   -> 1   (5 is odd, 2 is even)
n = 15   -> 2
n = 2048 -> 0
```

#### Approach: Extraction of digits
Extract each digit with `n % 10`, check whether it is odd (`digit % 2 == 1`), count it, then drop it with `n /= 10`.

**Dry run (n = 1534):** digits 4 (even), 3 (odd → 1), 5 (odd → 2), 1 (odd → 3) → answer 3.

**Complexity:** Time O(log₁₀ n), Space O(1).

**C++**
```cpp
int countOddDigits(int n) {
    int cnt = 0;
    while (n > 0) {
        int d = n % 10;
        if (d % 2 == 1) cnt++;
        n /= 10;
    }
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countOddDigits(int n) {
        int cnt = 0;
        while (n > 0) {
            int d = n % 10;
            if (d % 2 == 1) cnt++;
            n /= 10;
        }
        return cnt;
    }
}
```

#### Edge Cases & Pitfalls
- `n = 0` → its only digit 0 is even → 0 (the loop doesn't run, which happens to give the right answer).
- For negative numbers `%` returns a negative remainder in C++/Java; use `abs(n)` first.

#### Key Takeaways
- Any "count digits with property X" question = digit extraction + a condition.

[↑ Contents](#contents) · [← Previous](#p23) · [Next →](#p25)

---

<a id="p25"></a>

### 25. Reverse a number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Core | No | [LeetCode](https://leetcode.com/problems/reverse-integer/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/reverse-digits-of-a-number) | [Watch from 15:30](https://youtu.be/1xNbjMdbjug?t=930) |

#### Problem Statement
Given an integer `n`, return the number with its digits reversed. Trailing zeros of `n` disappear in the reverse (e.g. 10400 → 401).

```text
n = 7789  -> 9877
n = 10400 -> 401
```
(LeetCode 7 adds: the input is a signed 32-bit integer; return 0 if the reversed value overflows.)

#### Intuition (from the video)
Digit extraction already produces the digits in reverse order (9, 8, 7, 7). We just need to **glue** them into a number. To append a digit `d` to the end of a number `r`, shift `r` left by one decimal place and add `d`: `r = r * 10 + d`.

**Dry run (7789):**

| n | last digit | rev = rev·10 + last |
|---|---|---|
| 7789 | 9 | 0·10 + 9 = 9 |
| 778 | 8 | 9·10 + 8 = 98 |
| 77 | 7 | 98·10 + 7 = 987 |
| 7 | 7 | 987·10 + 7 = 9877 |

#### Approach
```
rev = 0
while n > 0:
    last = n % 10
    rev = rev * 10 + last
    n = n / 10
```

**Complexity:** Time O(log₁₀ n), Space O(1).

**C++**
```cpp
int reverseNumber(int n) {
    int rev = 0;
    while (n > 0) {
        int last = n % 10;
        rev = rev * 10 + last;
        n /= 10;
    }
    return rev;
}
```

**Java**
```java
class Solution {
    static int reverseNumber(int n) {
        int rev = 0;
        while (n > 0) {
            int last = n % 10;
            rev = rev * 10 + last;
            n /= 10;
        }
        return rev;
    }
}
```

#### LeetCode 7 version (negatives + overflow) *(not in video)*
Before doing `rev * 10 + last`, check that it cannot overflow: `rev > INT_MAX/10 || rev < INT_MIN/10` → return 0. With truncating division, the loop condition `x != 0` handles negative numbers naturally (the last digit is negative too).

**C++**
```cpp
class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int last = x % 10;
            if (rev > INT_MAX / 10 || rev < INT_MIN / 10) return 0;
            rev = rev * 10 + last;
            x /= 10;
        }
        return rev;
    }
};
```

**Java**
```java
class Solution {
    public int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int last = x % 10;
            if (rev > Integer.MAX_VALUE / 10 || rev < Integer.MIN_VALUE / 10) return 0;
            rev = rev * 10 + last;
            x /= 10;
        }
        return rev;
    }
}
```
(For a 32-bit input the last digit added is at most 2, so checking `rev` against `MAX/10` before the multiply is sufficient.)

#### Key Takeaways
- `rev = rev * 10 + digit` is the standard way to build a number digit by digit.

[↑ Contents](#contents) · [← Previous](#p24) · [Next →](#p26)

---

<a id="p26"></a>

### 26. Palindrome Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Basic | No | [LeetCode](https://leetcode.com/problems/palindrome-number/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-whether-a-number-is-a-palindrome) | [Watch from 20:30](https://youtu.be/1xNbjMdbjug?t=1230) |

#### Problem Statement
Return `true` if the integer `n` is a palindrome (it reads the same forwards and backwards), else `false`.

```text
121  -> true
1331 -> true
7    -> true
123  -> false (reverse is 321)
```

#### Intuition (from the video)
By definition, a palindrome number equals its own reverse. So: compute the reverse (previous problem) and compare it with the original.

**Pitfall highlighted in the video:** the reversing loop destroys `n` (it ends at 0). Save a **copy** (`dup = n`) before the loop and compare the reverse with the copy.

#### Approach
1. `dup = n`, `rev = 0`.
2. While `n > 0`: `rev = rev * 10 + n % 10`, `n /= 10`.
3. Return `dup == rev`.

**Complexity:** Time O(log₁₀ n), Space O(1).

**C++**
```cpp
bool isPalindrome(int n) {
    if (n < 0) return false;          // LeetCode: negatives are never palindromes (not in video)
    int dup = n;
    long long rev = 0;                // long long avoids overflow while reversing
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return dup == rev;
}
```

**Java**
```java
class Solution {
    static boolean isPalindrome(int n) {
        if (n < 0) return false;      // (not in video)
        int dup = n;
        long rev = 0;
        while (n > 0) {
            rev = rev * 10 + n % 10;
            n /= 10;
        }
        return dup == rev;
    }
}
```

#### Edge Cases & Pitfalls
- Negative numbers (e.g. −121 reads "121−") are not palindromes on LeetCode *(not in video)*.
- The reverse of a large `int` can overflow — store it in a 64-bit variable.

#### Key Takeaways
- Whenever a loop consumes the input, keep a duplicate if you still need the original value later.

[↑ Contents](#contents) · [← Previous](#p25) · [Next →](#p27)

---

<a id="p27"></a>

### 27. Return the Largest Digit in a Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Basic | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/find-the-largest-digit-in-a-number) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a non-negative integer `n`, return its largest digit.

```text
n = 25    -> 5
n = 99    -> 9
n = 0     -> 0
n = 41870 -> 8
```

#### Approach: Extraction of digits
Initialise `mx = 0`; extract each digit with `n % 10`, update `mx = max(mx, digit)`, then `n /= 10`.

**Dry run (41870):** 0 → mx 0; 7 → 7; 8 → 8; 1 → 8; 4 → 8 → answer 8.

**Complexity:** Time O(log₁₀ n), Space O(1).

**C++**
```cpp
int largestDigit(int n) {
    int mx = 0;
    while (n > 0) {
        mx = max(mx, n % 10);
        n /= 10;
    }
    return mx;
}
```

**Java**
```java
class Solution {
    static int largestDigit(int n) {
        int mx = 0;
        while (n > 0) {
            mx = Math.max(mx, n % 10);
            n /= 10;
        }
        return mx;
    }
}
```

#### Edge Cases & Pitfalls
- `n = 0` → the loop doesn't run and the answer 0 is correct because `mx` starts at 0.
- Early exit: if a digit 9 is found you can stop immediately (small optimisation).

#### Key Takeaways
- Max/min over digits uses the same extraction loop with a running best.

[↑ Contents](#contents) · [← Previous](#p26) · [Next →](#p28)

---

<a id="p28"></a>

### 28. Factorial of a given number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Basic | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/factorial-of-a-number) | [Watch](https://youtu.be/69ZCDFy-OUo) |

#### Problem Statement
Given `n ≥ 0`, return `n! = 1 × 2 × … × n` (with `0! = 1`).

```text
n = 3 -> 6
n = 4 -> 24
n = 0 -> 1
```

#### Approach 1: Iterative loop *(not in video)*
Multiply a running product by every number from 1 to `n`.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
long long factorial(int n) {
    long long ans = 1;
    for (int i = 1; i <= n; i++) ans *= i;
    return ans;
}
```

**Java**
```java
class Solution {
    static long factorial(int n) {
        long ans = 1;
        for (int i = 1; i <= n; i++) ans *= i;
        return ans;
    }
}
```

#### Approach 2: Functional recursion (from the video)
The video solves "sum of first N numbers" with recursion and then asks you to adapt it for factorial: replace `+` with `×`.
- Recurrence: `fact(n) = n × fact(n − 1)`.
- **Base case:** `fact(0) = 1` (or `fact(1) = 1`).

**Pitfall shown in the video:** copying the sum's base case `if (n == 0) return 0;` makes every product 0 — `1 × 0 = 0` propagates all the way up. For multiplication the base case must return **1**.

**Recursion tree (n = 3):** `fact(3) = 3 × fact(2)` → `2 × fact(1)` → `1 × fact(0)` → `fact(0) = 1`; returning: 1 → 1 → 2 → 6.

**Complexity:** Time O(n) (n calls, each O(1)); Space O(n) recursion stack (each call waits for the next).

**C++**
```cpp
long long factorial(int n) {
    if (n == 0) return 1;            // base case must be 1 for products
    return n * factorial(n - 1);
}
```

**Java**
```java
class Solution {
    static long factorial(int n) {
        if (n == 0) return 1;
        return n * factorial(n - 1);
    }
}
```

#### Edge Cases & Pitfalls
- Factorials grow very fast: 13! overflows a 32-bit int and 21! overflows 64 bits. Use `long long`/`long`, or `BigInteger`/modulo arithmetic for bigger `n` *(not in video)*.

#### Key Takeaways
- In functional recursion, the base case must be the identity element of the operation: 0 for sums, 1 for products.

[↑ Contents](#contents) · [← Previous](#p27) · [Next →](#p29)

---

<a id="p29"></a>

### 29. Check if the Number is Armstrong

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Basic | Yes | [LeetCode](https://leetcode.com/problems/armstrong-number/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/armstrong-number) | [Watch from 23:38](https://youtu.be/1xNbjMdbjug?t=1418) |

#### Problem Statement
An **Armstrong number** equals the sum of its digits each raised to the power of the number of digits. Return whether `n` is an Armstrong number.

```text
153  = 1³ + 5³ + 3³ = 153            -> true
371  = 3³ + 7³ + 1³ = 371            -> true
1634 = 1⁴ + 6⁴ + 3⁴ + 4⁴ = 1634      -> true
35   : 3² + 5² = 34 ≠ 35             -> false
```

#### Intuition (from the video)
Extract every digit, raise it to the required power, and add it to a running `sum`. At the end compare `sum` with the **original** number (keep a duplicate, because the loop reduces `n` to 0).

> The video explains it with **cubes** (`digit × digit × digit`), which is correct for 3-digit numbers like 153 and 371. For the general definition (and for 1634) the power must be the **number of digits** `k` *(clarification, not in video)*.

#### Approach
1. `k` = number of digits of `n`; `dup = n`; `sum = 0`.
2. While `n > 0`: `d = n % 10`; `sum += d^k`; `n /= 10`.
3. Return `sum == dup`.

**Dry run (371, k = 3):** 1³ = 1 → sum 1; 7³ = 343 → 344; 3³ = 27 → 371 → equals 371 → true.

**Complexity:** Time O(log₁₀ n · k) (or O(log n) with a fast power), Space O(1).

**C++**
```cpp
bool isArmstrong(int n) {
    int k = to_string(n).length();
    int dup = n;
    long long sum = 0;
    while (n > 0) {
        int d = n % 10;
        long long p = 1;
        for (int i = 0; i < k; i++) p *= d;   // d^k
        sum += p;
        n /= 10;
    }
    return sum == dup;
}
```

**Java**
```java
class Solution {
    static boolean isArmstrong(int n) {
        int k = String.valueOf(n).length();
        int dup = n;
        long sum = 0;
        while (n > 0) {
            int d = n % 10;
            long p = 1;
            for (int i = 0; i < k; i++) p *= d;
            sum += p;
            n /= 10;
        }
        return sum == dup;
    }
}
```

#### Edge Cases & Pitfalls
- Use integer multiplication for the power; `pow()` returns a floating-point value and can round incorrectly.
- Forgetting the duplicate makes you compare with 0.

#### Key Takeaways
- Armstrong = digit extraction + per-digit transformation + compare with a saved copy.

[↑ Contents](#contents) · [← Previous](#p28) · [Next →](#p30)

---

<a id="p30"></a>

### 30. Check for Perfect Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Basic | No | [LeetCode](https://leetcode.com/problems/perfect-number/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/perfect-number) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
A **perfect number** is a positive integer equal to the sum of its proper divisors (all positive divisors except itself). Return whether `n` is perfect.

```text
6  = 1 + 2 + 3           -> true
28 = 1 + 2 + 4 + 7 + 14  -> true
12 : 1+2+3+4+6 = 16       -> false
1  : no proper divisors   -> false
```

#### Approach 1: Brute force
Try every `i` from 1 to `n − 1`; if `n % i == 0` add `i` to `sum`. Compare `sum` with `n`.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
bool isPerfect(int n) {
    if (n <= 1) return false;
    long long sum = 0;
    for (int i = 1; i < n; i++)
        if (n % i == 0) sum += i;
    return sum == n;
}
```

**Java**
```java
class Solution {
    static boolean isPerfect(int n) {
        if (n <= 1) return false;
        long sum = 0;
        for (int i = 1; i < n; i++)
            if (n % i == 0) sum += i;
        return sum == n;
    }
}
```

#### Approach 2: Divisors in pairs up to √n
Divisors come in pairs `(i, n / i)` with `i ≤ √n` (same idea as "Divisors of a Number"). Start with `sum = 1` (1 is always a proper divisor for `n > 1`), loop `i = 2` while `i * i <= n`; when `i` divides `n`, add `i` and, if different, `n / i`. The pair partner `n / 1 = n` itself is excluded because we started from `i = 2`.

**Complexity:** Time O(√n), Space O(1).

**C++**
```cpp
bool isPerfect(int n) {
    if (n <= 1) return false;
    long long sum = 1;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (n / i != i) sum += n / i;
        }
    }
    return sum == n;
}
```

**Java**
```java
class Solution {
    static boolean isPerfect(int n) {
        if (n <= 1) return false;
        long sum = 1;
        for (long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                sum += i;
                if (n / i != i) sum += n / i;
            }
        }
        return sum == n;
    }
}
```

#### Edge Cases & Pitfalls
- `n = 1` is **not** perfect.
- For a perfect square, don't add `√n` twice.

#### Key Takeaways
- Any "sum/count of divisors" task can be done in O(√n) using divisor pairs.

[↑ Contents](#contents) · [← Previous](#p29) · [Next →](#p31)

---

<a id="p31"></a>

### 31. Check for Prime Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-whether-a-number-is-prime) | [Watch from 39:41](https://youtu.be/1xNbjMdbjug?t=2381) |

#### Problem Statement
Return whether `n` is a prime number.

#### Definition (from the video)
"Divisible by 1 and itself" is a **wrong** definition — it would make 1 prime. The correct one: **a prime has exactly two distinct factors, 1 and itself.**

```text
11, 13, 5, 17 -> prime
4  (1, 2, 4)      -> not prime
8  (1, 2, 4, 8)   -> not prime
1  (only 1)       -> not prime
```

#### Approach 1: Brute force — count all factors
Loop `i = 1..n`, count how many divide `n`; prime iff the count is exactly 2.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
bool isPrime(int n) {
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (n % i == 0) cnt++;
    return cnt == 2;
}
```

**Java**
```java
class Solution {
    static boolean isPrime(int n) {
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (n % i == 0) cnt++;
        return cnt == 2;
    }
}
```

#### Approach 2: Optimal — loop till √n
Factors come in pairs `(i, n / i)`; every pair has one member `≤ √n` (shown with 36 = 1·36, 2·18, 3·12, 4·9, 6·6). So looping `i` while `i * i <= n` finds every factor:
- if `n % i == 0`, count `i`; and if `n / i != i`, count the partner `n / i` too.
- Prime iff the count is 2.

Write the condition as `i * i <= n` instead of `i <= sqrt(n)` to avoid calling `sqrt` on every iteration.

**Complexity:** Time O(√n), Space O(1).

**C++**
```cpp
bool isPrime(int n) {
    int cnt = 0;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (n / i != i) cnt++;
        }
    }
    return cnt == 2;
}
```

**Java**
```java
class Solution {
    static boolean isPrime(int n) {
        int cnt = 0;
        for (long i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                cnt++;
                if (n / i != i) cnt++;
            }
        }
        return cnt == 2;
    }
}
```

#### Edge Cases & Pitfalls
- 1 has a single factor → not prime; 2 is the only even prime.
- You can return `false` early as soon as the count exceeds 2 *(not in video)*.

#### Key Takeaways
- Divisor pairs reduce O(n) factor searches to O(√n).

[↑ Contents](#contents) · [← Previous](#p30) · [Next →](#p32)

---

<a id="p32"></a>

### 32. Count of Prime Numbers till N

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Basic | No | [LeetCode](https://leetcode.com/problems/count-primes/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given `n`, count the prime numbers **strictly less than** `n` (LeetCode 204).

```text
n = 10 -> 4   (2, 3, 5, 7)
n = 0  -> 0
n = 1  -> 0
```

#### Approach 1: Check every number with the √n primality test
For each `i` in `[2, n)`, test primality in O(√i) and count.

**Complexity:** Time O(n√n), Space O(1). Too slow for `n` up to 5·10⁶.

**C++**
```cpp
bool isPrime(int x) {
    if (x < 2) return false;
    for (long long i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}
int countPrimes(int n) {
    int cnt = 0;
    for (int i = 2; i < n; i++)
        if (isPrime(i)) cnt++;
    return cnt;
}
```

**Java**
```java
class Solution {
    static boolean isPrime(int x) {
        if (x < 2) return false;
        for (long i = 2; i * i <= x; i++)
            if (x % i == 0) return false;
        return true;
    }
    static int countPrimes(int n) {
        int cnt = 0;
        for (int i = 2; i < n; i++)
            if (isPrime(i)) cnt++;
        return cnt;
    }
}
```

#### Approach 2: Sieve of Eratosthenes
Assume every number ≥ 2 is prime. For each `i` from 2 while `i * i < n`, if `i` is still marked prime, mark all its multiples starting at `i * i` (smaller multiples were already marked by smaller primes) as not prime. Count what remains.

**Dry run (n = 20):** i = 2 marks 4, 6, 8, …, 18; i = 3 marks 9, 12, 15, 18; i = 4 is already crossed out; 5·5 = 25 ≥ 20 → stop. Remaining: 2, 3, 5, 7, 11, 13, 17, 19 → 8.

**Complexity:** Time O(n log log n), Space O(n).

**C++**
```cpp
int countPrimes(int n) {
    if (n < 3) return 0;
    vector<bool> prime(n, true);
    prime[0] = prime[1] = false;
    for (long long i = 2; i * i < n; i++) {
        if (!prime[i]) continue;
        for (long long j = i * i; j < n; j += i) prime[j] = false;
    }
    return count(prime.begin(), prime.end(), true);
}
```

**Java**
```java
class Solution {
    static int countPrimes(int n) {
        if (n < 3) return 0;
        boolean[] composite = new boolean[n];
        int cnt = 0;
        for (int i = 2; i < n; i++) {
            if (composite[i]) continue;
            cnt++;
            for (long j = (long) i * i; j < n; j += i) composite[(int) j] = true;
        }
        return cnt;
    }
}
```

#### Edge Cases & Pitfalls
- "Less than n" vs "till n": LeetCode excludes `n` itself; some judges include it — adjust the bound.
- Use `long` for `i * i` to avoid overflow.

#### Key Takeaways
- For many primality queries up to a limit, precompute with the sieve instead of testing each number.

[↑ Contents](#contents) · [← Previous](#p31) · [Next →](#p33)

---

<a id="p33"></a>

### 33. GCD of Two Numbers

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/gcd-euclidean-algorithm) | [Watch from 44:44](https://youtu.be/1xNbjMdbjug?t=2684) |

#### Problem Statement
Return the GCD (greatest common divisor), also called HCF (highest common factor), of two positive integers `n1` and `n2` — the largest number that divides both.

```text
gcd(9, 12)  = 3   (factors of 9: 1,3,9; of 12: 1,2,3,4,6,12; common: 1,3)
gcd(11, 13) = 1
gcd(20, 40) = 20  (one of the numbers can itself be the GCD)
```
1 divides every number, so a GCD always exists.

#### Approach 1: Brute force (increasing)
Try every `i` from 1 to `min(n1, n2)` (no divisor can exceed the smaller number); whenever `i` divides both, store it. The last stored value is the largest.

**Complexity:** Time O(min(n1, n2)), Space O(1).

**C++**
```cpp
int gcdBrute(int n1, int n2) {
    int g = 1;
    for (int i = 1; i <= min(n1, n2); i++)
        if (n1 % i == 0 && n2 % i == 0) g = i;
    return g;
}
```

**Java**
```java
class Solution {
    static int gcdBrute(int n1, int n2) {
        int g = 1;
        for (int i = 1; i <= Math.min(n1, n2); i++)
            if (n1 % i == 0 && n2 % i == 0) g = i;
        return g;
    }
}
```

#### Approach 2: Brute force (decreasing, with break)
Loop from `min(n1, n2)` down to 1 and stop at the first common divisor. This is faster on many inputs (e.g. 20, 40 finishes immediately), but the **worst case is still O(min(n1, n2))** — e.g. 11 and 13 run all the way down to 1.

**C++**
```cpp
int gcdBrute2(int n1, int n2) {
    for (int i = min(n1, n2); i >= 1; i--)
        if (n1 % i == 0 && n2 % i == 0) return i;
    return 1;
}
```

**Java**
```java
class Solution {
    static int gcdBrute2(int n1, int n2) {
        for (int i = Math.min(n1, n2); i >= 1; i--)
            if (n1 % i == 0 && n2 % i == 0) return i;
        return 1;
    }
}
```

#### Approach 3: Euclidean algorithm (subtraction form)
`gcd(a, b) = gcd(a − b, b)` for `a > b`. Keep replacing the larger number by the difference until one becomes 0; the other number is the GCD.
Example: gcd(20, 15) → gcd(5, 15) → gcd(10, 5) → gcd(5, 5) → gcd(0, 5) → **5**.
Problem: with gcd(52, 10) you subtract 10 five times (52 → 42 → 32 → 22 → 12 → 2) — many steps.

#### Approach 4: Euclidean algorithm (modulo form) — optimal
Repeated subtraction of `b` from `a` until it's smaller than `b` is exactly `a % b`. So:
`gcd(a, b) = gcd(a % b, b)` (greater % smaller), repeated until one of them is 0; the other is the answer.

**Dry run (52, 10):** 52 % 10 = 2 → (2, 10); 10 % 2 = 0 → (2, 0) → answer 2.

The video's code avoids swapping: in each step, whichever of `a`, `b` is larger gets reduced modulo the other.

**Complexity:** Time O(log_φ(min(a, b))) — every step is a division-like reduction, hence logarithmic; φ is the golden ratio (the worst case is consecutive Fibonacci numbers). Space O(1).

**C++**
```cpp
int gcd(int a, int b) {
    while (a > 0 && b > 0) {
        if (a > b) a = a % b;
        else b = b % a;
    }
    if (a == 0) return b;
    return a;
}
```

**Java**
```java
class Solution {
    static int gcd(int a, int b) {
        while (a > 0 && b > 0) {
            if (a > b) a = a % b;
            else b = b % a;
        }
        if (a == 0) return b;
        return a;
    }
}
```

**Recursive one-liner** *(common form, not in video)*: `gcd(a, b) = b == 0 ? a : gcd(b, a % b)`.

#### Key Takeaways
- Remember: `gcd(a, b) = gcd(a % b, b)`; stop when one number is 0.
- GCD is the building block for LCM, fraction reduction, and many number-theory problems.

[↑ Contents](#contents) · [← Previous](#p32) · [Next →](#p34)

---

<a id="p34"></a>

### 34. LCM of two numbers

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the LCM (least common multiple) of two positive integers `n1` and `n2` — the smallest positive number divisible by both.

```text
lcm(4, 6)  = 12
lcm(3, 5)  = 15
lcm(4, 12) = 12
```

#### Approach 1: Brute force
The LCM lies between `max(n1, n2)` and `n1 × n2`. Start at the larger number and step by the larger number (only its multiples can work) until you find one divisible by the smaller.

**Complexity:** Time O(min(n1, n2)) iterations in the worst case, Space O(1).

**C++**
```cpp
long long lcmBrute(int n1, int n2) {
    long long mx = max(n1, n2), mn = min(n1, n2);
    long long m = mx;
    while (m % mn != 0) m += mx;
    return m;
}
```

**Java**
```java
class Solution {
    static long lcmBrute(int n1, int n2) {
        long mx = Math.max(n1, n2), mn = Math.min(n1, n2);
        long m = mx;
        while (m % mn != 0) m += mx;
        return m;
    }
}
```

#### Approach 2: Using the GCD (optimal)
For any two positive integers: `gcd(a, b) × lcm(a, b) = a × b`. So `lcm = a / gcd(a, b) × b` — divide first to reduce the risk of overflow. Use the Euclidean GCD from the previous problem.

**Dry run (4, 6):** gcd = 2 → 4 / 2 × 6 = 12.

**Complexity:** Time O(log(min(a, b))), Space O(1).

**C++**
```cpp
long long gcdLL(long long a, long long b) {
    while (b != 0) { long long t = a % b; a = b; b = t; }
    return a;
}
long long lcm(long long a, long long b) {
    return a / gcdLL(a, b) * b;
}
```

**Java**
```java
class Solution {
    static long gcd(long a, long b) {
        while (b != 0) { long t = a % b; a = b; b = t; }
        return a;
    }
    static long lcm(long a, long b) {
        return a / gcd(a, b) * b;
    }
}
```

#### Edge Cases & Pitfalls
- `a * b` can overflow 32 bits; compute `a / gcd * b` with 64-bit integers.

#### Key Takeaways
- LCM is almost always computed through the GCD.

[↑ Contents](#contents) · [← Previous](#p33) · [Next →](#p35)

---

<a id="p35"></a>

### 35. Divisors of a Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Maths | Core | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/count-divisors) | [Watch from 26:20](https://youtu.be/1xNbjMdbjug?t=1580) |

#### Problem Statement
Print (or return) all divisors of `n` in increasing order.

```text
n = 36 -> 1 2 3 4 6 9 12 18 36
```

#### Approach 1: Brute force
Every divisor lies in `[1, n]`. Loop `i = 1..n` and print `i` whenever `n % i == 0` (remainder 0 means `i` divides `n` completely).

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
vector<int> divisors(int n) {
    vector<int> res;
    for (int i = 1; i <= n; i++)
        if (n % i == 0) res.push_back(i);
    return res;
}
```

**Java**
```java
class Solution {
    static List<Integer> divisors(int n) {
        List<Integer> res = new ArrayList<>();
        for (int i = 1; i <= n; i++)
            if (n % i == 0) res.add(i);
        return res;
    }
}
```

#### Approach 2: Optimal — divisor pairs up to √n
Write 36 as products: 1·36, 2·18, 3·12, 4·9, **6·6**, 9·4, 12·3, 18·2, 36·1. After the line at 6·6 (= √36) the pairs simply repeat in reverse. So looping `i` while `i * i <= n` is enough:
- if `n % i == 0`, `i` is a divisor, and so is its partner `n / i`;
- add the partner only if `n / i != i` (otherwise 6 would be added twice).

The pairs come out unordered (1, 36, 2, 18, …), so store them in a dynamic list (`vector` / `ArrayList`) and **sort** before returning. Prefer `i * i <= n` over `i <= sqrt(n)` so `sqrt` isn't evaluated every iteration.

**Complexity:** Time O(√n) to find the divisors + O(d log d) to sort them (d = number of divisors) + O(d) to print. Space O(d).

**C++**
```cpp
vector<int> divisors(int n) {
    vector<int> res;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (n / i != i) res.push_back(n / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}
```

**Java**
```java
class Solution {
    static List<Integer> divisors(int n) {
        List<Integer> res = new ArrayList<>();
        for (long i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                res.add((int) i);
                if (n / i != i) res.add((int) (n / i));
            }
        }
        Collections.sort(res);
        return res;
    }
}
```

#### Edge Cases & Pitfalls
- Perfect squares: guard against adding `√n` twice.
- An alternative without sorting *(not in video)*: push small divisors into one list and large partners into another, then append the second list reversed.

#### Key Takeaways
- Divisors pair up around √n — this observation powers prime checks, perfect numbers and divisor counts.

[↑ Contents](#contents) · [← Previous](#p34) · [Next →](#p36)

---

## Basic Arrays

<a id="p36"></a>

### 36. Sum of Array Elements

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Arrays | Basic | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/sum-of-array) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an array `arr` of `n` integers, return the sum of all its elements.

```text
arr = [1, 2, 3]        -> 6
arr = [1, 3, 5, 7, 9]  -> 25
```

#### Approach: Single pass
Keep a running `sum` initialised to 0 and add every element.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
long long sumOfArray(vector<int>& arr) {
    long long sum = 0;
    for (int x : arr) sum += x;
    return sum;
}
```

**Java**
```java
class Solution {
    static long sumOfArray(int[] arr) {
        long sum = 0;
        for (int x : arr) sum += x;
        return sum;
    }
}
```

#### Edge Cases & Pitfalls
- Use a 64-bit accumulator when `n` and the values are large (e.g. 10⁵ elements of 10⁹ overflow `int`).
- Empty array → 0.

#### Key Takeaways
- The accumulator pattern (`init` + `update per element`) underlies sums, products, counts and max/min.

[↑ Contents](#contents) · [← Previous](#p35) · [Next →](#p37)

---

<a id="p37"></a>

### 37. Count of odd numbers in Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Arrays | Basic | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/odd-elements-in-an-array) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an array of `n` integers, count how many are odd.

```text
arr = [1, 2, 3, 4, 5] -> 3
arr = [2, 4, 6]       -> 0
```

#### Approach: Single pass with a parity check
A number is odd when `x % 2 != 0`. Use `!= 0` rather than `== 1` so negative odd numbers (where `-3 % 2 == -1`) are counted correctly.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
int countOdd(vector<int>& arr) {
    int cnt = 0;
    for (int x : arr)
        if (x % 2 != 0) cnt++;
    return cnt;
}
```

**Java**
```java
class Solution {
    static int countOdd(int[] arr) {
        int cnt = 0;
        for (int x : arr)
            if (x % 2 != 0) cnt++;
        return cnt;
    }
}
```

#### Key Takeaways
- Bitwise alternative: `(x & 1) == 1` also works for negatives in two's complement.

[↑ Contents](#contents) · [← Previous](#p36) · [Next →](#p38)

---

<a id="p38"></a>

### 38. Check if the Array is Sorted I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Arrays | Basic | Yes | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-if-an-array-is-sorted-in-ascending-order) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an array of `n` integers, return `true` if it is sorted in non-decreasing order, else `false`.

```text
[1, 2, 2, 5]  -> true
[1, 3, 2]     -> false
[7]           -> true
```

#### Approach 1: Brute force — compare every pair
For every `i < j` check `arr[i] <= arr[j]`.

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
bool isSortedBrute(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[i]) return false;
    return true;
}
```

**Java**
```java
class Solution {
    static boolean isSortedBrute(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (arr[j] < arr[i]) return false;
        return true;
    }
}
```

#### Approach 2: Optimal — compare adjacent elements
If every element is ≥ the one before it, the whole array is sorted (sortedness is transitive). One pass suffices.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
bool isSorted(vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); i++)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}
```

**Java**
```java
class Solution {
    static boolean isSorted(int[] arr) {
        for (int i = 1; i < arr.length; i++)
            if (arr[i] < arr[i - 1]) return false;
        return true;
    }
}
```

#### Key Takeaways
- Global properties of sorted arrays can usually be checked locally (adjacent pairs).

[↑ Contents](#contents) · [← Previous](#p37) · [Next →](#p39)

---

<a id="p39"></a>

### 39. Reverse an array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Arrays | Basic | No | — | [Watch](https://youtu.be/twuC1F6gLI8) |

#### Problem Statement
Reverse an array of `n` integers in place.

```text
[1, 2, 3, 4, 5] -> [5, 4, 3, 2, 1]
[1, 3, 2, 5, 4] -> [4, 5, 2, 3, 1]
```

#### Approach 1: Extra array *(not in video)*
Copy `arr[n − 1 − i]` into `res[i]`, then copy back.

**Complexity:** Time O(n), Space O(n).

**C++**
```cpp
void reverseExtra(vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n);
    for (int i = 0; i < n; i++) res[i] = arr[n - 1 - i];
    arr = res;
}
```

**Java**
```java
class Solution {
    static void reverseExtra(int[] arr) {
        int n = arr.length;
        int[] res = new int[n];
        for (int i = 0; i < n; i++) res[i] = arr[n - 1 - i];
        System.arraycopy(res, 0, arr, 0, n);
    }
}
```

#### Approach 2: Two pointers (iterative)
The video starts from the loop version: put `l` at index 0 and `r` at index `n − 1`, swap, move `l` right and `r` left, and stop when they meet or cross.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
void reverseIter(vector<int>& arr) {
    int l = 0, r = arr.size() - 1;
    while (l < r) swap(arr[l++], arr[r--]);
}
```

**Java**
```java
class Solution {
    static void reverseIter(int[] arr) {
        int l = 0, r = arr.length - 1;
        while (l < r) {
            int t = arr[l]; arr[l] = arr[r]; arr[r] = t;
            l++; r--;
        }
    }
}
```

#### Approach 3: Recursion with two pointers (video)
The recursion's job: **swap `arr[l]` and `arr[r]`, then ask recursion to handle `(l + 1, r − 1)`**. Base case: `l >= r` → nothing left to swap.

**Dry run ([1, 3, 2, 5, 4]):** f(0,4) swaps 1↔4 → f(1,3) swaps 3↔5 → f(2,2) hits the base case → array is [4, 5, 2, 3, 1].

**C++**
```cpp
void reverseRec(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    swap(arr[l], arr[r]);
    reverseRec(arr, l + 1, r - 1);
}
// call: reverseRec(arr, 0, arr.size() - 1);
```

**Java**
```java
class Solution {
    static void reverseRec(int[] arr, int l, int r) {
        if (l >= r) return;
        int t = arr[l]; arr[l] = arr[r]; arr[r] = t;
        reverseRec(arr, l + 1, r - 1);
    }
}
```

#### Approach 4: Recursion with a single pointer (video)
The partner of index `i` is `n − i − 1` (for n = 5: 0↔4, 1↔3). Swap `arr[i]` with `arr[n − i − 1]` and recurse on `i + 1`. Stop once `i` reaches the middle: `i >= n / 2`.

**Complexity (both recursive versions):** Time O(n/2) = O(n) calls; Space O(n/2) = O(n) recursion stack.

**C++**
```cpp
void reverseRec1(int i, vector<int>& arr) {
    int n = arr.size();
    if (i >= n / 2) return;
    swap(arr[i], arr[n - i - 1]);
    reverseRec1(i + 1, arr);
}
// call: reverseRec1(0, arr);
```

**Java**
```java
class Solution {
    static void reverseRec1(int i, int[] arr) {
        int n = arr.length;
        if (i >= n / 2) return;
        int t = arr[i]; arr[i] = arr[n - i - 1]; arr[n - i - 1] = t;
        reverseRec1(i + 1, arr);
    }
}
```

#### Key Takeaways
- To write recursion, first identify the **one task** each call performs (here: one swap) and the **next call** it delegates to.
- Arrays/vectors must be passed by reference (C++ `&`) so the swaps are visible to the caller; Java arrays are references already.

[↑ Contents](#contents) · [← Previous](#p38) · [Next →](#p40)

---

## Basic Hashing

<a id="p40"></a>

### 40. Highest Occurring Element in an Array

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Hashing | Core | No | [LeetCode](https://leetcode.com/problems/frequency-of-the-most-frequent-element/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/highest-freq-element) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given an array of `n` integers, return the element that occurs the most times. If several elements share the highest frequency, return the **smallest** of them.

```text
[1, 2, 2, 3, 3, 3] -> 3
[4, 4, 5, 5, 6]    -> 4   (4 and 5 both occur twice; 4 is smaller)
```

#### Approach 1: Brute force — count each element with a nested loop
For each `i`, count how many times `arr[i]` occurs; keep the best (highest count, ties → smaller value).

**Complexity:** Time O(n²), Space O(1).

**C++**
```cpp
int mostFrequentBrute(vector<int>& arr) {
    int n = arr.size(), best = arr[0], bestCnt = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) if (arr[j] == arr[i]) cnt++;
        if (cnt > bestCnt || (cnt == bestCnt && arr[i] < best)) { bestCnt = cnt; best = arr[i]; }
    }
    return best;
}
```

**Java**
```java
class Solution {
    static int mostFrequentBrute(int[] arr) {
        int n = arr.length, best = arr[0], bestCnt = 0;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) if (arr[j] == arr[i]) cnt++;
            if (cnt > bestCnt || (cnt == bestCnt && arr[i] < best)) { bestCnt = cnt; best = arr[i]; }
        }
        return best;
    }
}
```

#### Approach 2: Optimal — hash map of frequencies
Count every element in one pass with a hash map (pre-computation), then scan the map for the highest frequency, breaking ties by the smaller key.

**Complexity:** Time O(n) average (hash map), Space O(n). With a `map`/`TreeMap` it is O(n log n).

**C++**
```cpp
int mostFrequent(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;
    int best = INT_MAX, bestCnt = 0;
    for (auto& [val, cnt] : freq)
        if (cnt > bestCnt || (cnt == bestCnt && val < best)) { bestCnt = cnt; best = val; }
    return best;
}
```

**Java**
```java
class Solution {
    static int mostFrequent(int[] arr) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int x : arr) freq.merge(x, 1, Integer::sum);
        int best = Integer.MAX_VALUE, bestCnt = 0;
        for (Map.Entry<Integer, Integer> e : freq.entrySet()) {
            int val = e.getKey(), cnt = e.getValue();
            if (cnt > bestCnt || (cnt == bestCnt && val < best)) { bestCnt = cnt; best = val; }
        }
        return best;
    }
}
```

#### Edge Cases & Pitfalls
- Read the tie-breaking rule carefully (smallest value here).
- The LeetCode link attached on the sheet ("Frequency of the Most Frequent Element") is a different, harder problem (with up to `k` increments); this note covers the sheet's version.

#### Key Takeaways
- Frequency questions → hashing: pre-compute counts once, answer queries in O(1).

[↑ Contents](#contents) · [← Previous](#p39) · [Next →](#p41)

---

<a id="p41"></a>

### 41. Second Highest Occurring Element

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Hashing | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/second-highest-occurring-element) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the element with the **second highest** frequency in the array. If several elements share that frequency, return the smallest; if there is no second-highest frequency, return −1.

```text
[1, 2, 2, 3, 3, 3]  -> 2   (3 occurs 3 times, 2 occurs twice)
[4, 4, 5, 5, 6, 7]  -> 6   (highest freq 2; second highest freq 1 → 6 and 7 → smallest 6)
[10, 9, 7, 7]       -> 9
[5, 5, 5]           -> -1
```

#### Approach: Frequency map + track top two frequencies
1. Count frequencies with a hash map.
2. Find the highest frequency `f1` and the highest frequency strictly less than `f1`, call it `f2`.
3. Among elements whose frequency equals `f2`, return the smallest; if `f2` doesn't exist, return −1.

(This can be fused into one pass over the map by maintaining `(f1, e1)` and `(f2, e2)` and demoting the first pair when a larger frequency appears.)

**Complexity:** Time O(n) average, Space O(n).

**C++**
```cpp
int secondMostFrequent(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;
    int f1 = 0, f2 = 0;
    for (auto& [v, c] : freq) {
        if (c > f1) { f2 = f1; f1 = c; }
        else if (c < f1 && c > f2) f2 = c;
    }
    if (f2 == 0) return -1;
    int ans = INT_MAX;
    for (auto& [v, c] : freq)
        if (c == f2) ans = min(ans, v);
    return ans;
}
```

**Java**
```java
class Solution {
    static int secondMostFrequent(int[] arr) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int x : arr) freq.merge(x, 1, Integer::sum);
        int f1 = 0, f2 = 0;
        for (int c : freq.values()) {
            if (c > f1) { f2 = f1; f1 = c; }
            else if (c < f1 && c > f2) f2 = c;
        }
        if (f2 == 0) return -1;
        int ans = Integer.MAX_VALUE;
        for (Map.Entry<Integer, Integer> e : freq.entrySet())
            if (e.getValue() == f2) ans = Math.min(ans, e.getKey());
        return ans;
    }
}
```

#### Edge Cases & Pitfalls
- "Second highest" means second highest **distinct** frequency — elements tied for the top don't count as second.
- When a new maximum appears, the old maximum becomes the second (`f2 = f1` before updating `f1`).

#### Key Takeaways
- "Top-2" tracking (largest and second largest) is a reusable trick; it reappears in "second largest element".

[↑ Contents](#contents) · [← Previous](#p40) · [Next →](#p42)

---

<a id="p42"></a>

### 42. Sum of Highest and Lowest Frequency

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Hashing | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the sum of the **highest frequency** and the **lowest frequency** among the elements of the array.

```text
[1, 2, 2, 3, 3, 3] -> 4   (highest freq 3 for '3', lowest freq 1 for '1')
[4, 4, 5, 5, 6]    -> 3   (highest 2, lowest 1)
[7, 7, 7]          -> 6   (only one distinct element: 3 + 3)
```

#### Approach 1: Brute force with visited markers
For each unvisited element, count its occurrences with an inner loop (marking them visited), and update the max and min frequencies.

**Complexity:** Time O(n²), Space O(n) for the visited array.

**C++**
```cpp
int sumHighLowBrute(vector<int>& arr) {
    int n = arr.size(), mx = 0, mn = INT_MAX;
    vector<bool> seen(n, false);
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        int cnt = 0;
        for (int j = i; j < n; j++)
            if (arr[j] == arr[i]) { cnt++; seen[j] = true; }
        mx = max(mx, cnt); mn = min(mn, cnt);
    }
    return mx + mn;
}
```

**Java**
```java
class Solution {
    static int sumHighLowBrute(int[] arr) {
        int n = arr.length, mx = 0, mn = Integer.MAX_VALUE;
        boolean[] seen = new boolean[n];
        for (int i = 0; i < n; i++) {
            if (seen[i]) continue;
            int cnt = 0;
            for (int j = i; j < n; j++)
                if (arr[j] == arr[i]) { cnt++; seen[j] = true; }
            mx = Math.max(mx, cnt); mn = Math.min(mn, cnt);
        }
        return mx + mn;
    }
}
```

#### Approach 2: Optimal — hash map
Count with a hash map, then take the max and min over the map's values.

**Complexity:** Time O(n) average, Space O(n).

**C++**
```cpp
int sumHighLow(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;
    int mx = 0, mn = INT_MAX;
    for (auto& [v, c] : freq) { mx = max(mx, c); mn = min(mn, c); }
    return mx + mn;
}
```

**Java**
```java
class Solution {
    static int sumHighLow(int[] arr) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int x : arr) freq.merge(x, 1, Integer::sum);
        int mx = 0, mn = Integer.MAX_VALUE;
        for (int c : freq.values()) { mx = Math.max(mx, c); mn = Math.min(mn, c); }
        return mx + mn;
    }
}
```

#### Key Takeaways
- The answer is a sum of **frequencies**, not of elements — read what is being asked.

[↑ Contents](#contents) · [← Previous](#p41) · [Next →](#p43)

---

## Basic Strings

<a id="p43"></a>

### 43. Reverse a String II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Strings | Basic | No | [LeetCode](https://leetcode.com/problems/reverse-string/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Reverse a string given as an array of characters, **in place** with O(1) extra memory (LeetCode 344).

```text
['h','e','l','l','o'] -> ['o','l','l','e','h']
```

#### Approach 1: Extra array (not in-place)
Copy characters in reverse order into a new array, then copy back.

**Complexity:** Time O(n), Space O(n).

**C++**
```cpp
void reverseStringExtra(vector<char>& s) {
    vector<char> t(s.rbegin(), s.rend());
    s = t;
}
```

**Java**
```java
class Solution {
    static void reverseStringExtra(char[] s) {
        int n = s.length;
        char[] t = new char[n];
        for (int i = 0; i < n; i++) t[i] = s[n - 1 - i];
        System.arraycopy(t, 0, s, 0, n);
    }
}
```

#### Approach 2: Optimal — two pointers
Swap `s[l]` and `s[r]`, move `l` forward and `r` backward until they meet.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
void reverseString(vector<char>& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) swap(s[l++], s[r--]);
}
```

**Java**
```java
class Solution {
    public void reverseString(char[] s) {
        int l = 0, r = s.length - 1;
        while (l < r) {
            char t = s[l]; s[l] = s[r]; s[r] = t;
            l++; r--;
        }
    }
}
```

#### Key Takeaways
- Two pointers moving towards each other = the standard in-place reversal.

[↑ Contents](#contents) · [← Previous](#p42) · [Next →](#p44)

---

<a id="p44"></a>

### 44. Palindrome Check

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Strings | Core | No | [LeetCode](https://leetcode.com/problems/valid-palindrome/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/valid-palindrome) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a string `s`, return `true` if it is a palindrome. On LeetCode 125 (linked on the sheet), first convert uppercase to lowercase and ignore every non-alphanumeric character.

```text
"madam"                          -> true
"A man, a plan, a canal: Panama" -> true   ("amanaplanacanalpanama")
"race a car"                     -> false
```

#### Approach 1: Build a cleaned copy and compare with its reverse
Keep only alphanumeric characters (lower-cased) in a new string `t`; return `t == reverse(t)`.

**Complexity:** Time O(n), Space O(n).

**C++**
```cpp
bool isPalindromeCopy(string s) {
    string t;
    for (char c : s) if (isalnum((unsigned char)c)) t += tolower((unsigned char)c);
    string r(t.rbegin(), t.rend());
    return t == r;
}
```

**Java**
```java
class Solution {
    static boolean isPalindromeCopy(String s) {
        StringBuilder t = new StringBuilder();
        for (char c : s.toCharArray()) if (Character.isLetterOrDigit(c)) t.append(Character.toLowerCase(c));
        return t.toString().equals(t.reverse().toString());
    }
}
```

#### Approach 2: Optimal — two pointers, skipping invalid characters
`l` from the start, `r` from the end; skip non-alphanumeric characters on each side; compare lower-cased characters; move inward.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
bool isPalindrome(string s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        while (l < r && !isalnum((unsigned char)s[l])) l++;
        while (l < r && !isalnum((unsigned char)s[r])) r--;
        if (tolower((unsigned char)s[l]) != tolower((unsigned char)s[r])) return false;
        l++; r--;
    }
    return true;
}
```

**Java**
```java
class Solution {
    public boolean isPalindrome(String s) {
        int l = 0, r = s.length() - 1;
        while (l < r) {
            while (l < r && !Character.isLetterOrDigit(s.charAt(l))) l++;
            while (l < r && !Character.isLetterOrDigit(s.charAt(r))) r--;
            if (Character.toLowerCase(s.charAt(l)) != Character.toLowerCase(s.charAt(r))) return false;
            l++; r--;
        }
        return true;
    }
}
```

#### Key Takeaways
- For a plain palindrome check (no cleaning), the same two-pointer loop without the skipping works.

[↑ Contents](#contents) · [← Previous](#p43) · [Next →](#p45)

---

<a id="p45"></a>

### 45. Largest Odd Number in a String

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Strings | Core | No | [LeetCode](https://leetcode.com/problems/largest-odd-number-in-string/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Given a string `num` representing a large non-negative integer, return the **largest-valued odd integer** that is a non-empty substring of `num`, or `""` if none exists (LeetCode 1903). The takeUforward version also asks you to drop leading zeros from the answer.

```text
"52"      -> "5"
"4206"    -> ""
"35427"   -> "35427"
"0214638" -> "21463"  (sheet version: leading zero removed)
```

#### Intuition
A number is odd iff its **last digit** is odd. The largest odd substring must start at index 0 (a longer prefix is always a larger number) and end at the **rightmost odd digit**.

#### Approach 1: Brute force
Try every substring, keep the odd ones, compare by numeric value (length after stripping zeros, then lexicographically). O(n³) — only useful to understand the problem; skipped in code.

#### Approach 2: Optimal — scan from the right
1. Find the rightmost index `i` with an odd digit. If none, return `""`.
2. Skip leading zeros from the left: first index `j` with `num[j] != '0'`.
3. Return `num.substr(j, i − j + 1)`.

**Complexity:** Time O(n), Space O(1) besides the output.

**C++**
```cpp
string largestOddNumber(string num) {
    int i = (int)num.size() - 1;
    while (i >= 0 && (num[i] - '0') % 2 == 0) i--;
    if (i < 0) return "";
    int j = 0;
    while (j < i && num[j] == '0') j++;
    return num.substr(j, i - j + 1);
}
```

**Java**
```java
class Solution {
    public String largestOddNumber(String num) {
        int i = num.length() - 1;
        while (i >= 0 && (num.charAt(i) - '0') % 2 == 0) i--;
        if (i < 0) return "";
        int j = 0;
        while (j < i && num.charAt(j) == '0') j++;
        return num.substring(j, i + 1);
    }
}
```

#### Edge Cases & Pitfalls
- Don't convert the string to an integer — it can be up to 10⁵ digits long.
- LeetCode inputs never have leading zeros, so step 2 matters only for the sheet's version.

#### Key Takeaways
- Look for the property that decides the answer (here: last digit odd) and greedily maximise the rest.

[↑ Contents](#contents) · [← Previous](#p44) · [Next →](#p46)

---

<a id="p46"></a>

### 46. Longest Common Prefix

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Strings | Core | No | [LeetCode](https://leetcode.com/problems/longest-common-prefix/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the longest common prefix of an array of strings, or `""` if there is none (LeetCode 14).

```text
["flower","flow","flight"] -> "fl"
["dog","racecar","car"]    -> ""
```

#### Approach 1: Vertical scanning
Compare characters column by column: for position `i`, check that every string has the same character as the first string; stop at the first mismatch or when any string ends.

**Complexity:** Time O(N · m) where N = number of strings, m = length of the shortest one. Space O(1).

**C++**
```cpp
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    for (int i = 0; i < (int)strs[0].size(); i++) {
        char c = strs[0][i];
        for (int k = 1; k < (int)strs.size(); k++)
            if (i >= (int)strs[k].size() || strs[k][i] != c) return strs[0].substr(0, i);
    }
    return strs[0];
}
```

**Java**
```java
class Solution {
    public String longestCommonPrefix(String[] strs) {
        if (strs.length == 0) return "";
        for (int i = 0; i < strs[0].length(); i++) {
            char c = strs[0].charAt(i);
            for (int k = 1; k < strs.length; k++)
                if (i >= strs[k].length() || strs[k].charAt(i) != c) return strs[0].substring(0, i);
        }
        return strs[0];
    }
}
```

#### Approach 2: Sort, then compare first and last
After sorting lexicographically, the first and last strings are the most different; their common prefix is the common prefix of all.

**Complexity:** Time O(N · L · log N) for sorting (L = average length), Space O(1) extra (ignoring sort internals).

**C++**
```cpp
string longestCommonPrefixSort(vector<string>& strs) {
    if (strs.empty()) return "";
    sort(strs.begin(), strs.end());
    string& a = strs.front();
    string& b = strs.back();
    int i = 0;
    while (i < (int)min(a.size(), b.size()) && a[i] == b[i]) i++;
    return a.substr(0, i);
}
```

**Java**
```java
class Solution {
    static String longestCommonPrefixSort(String[] strs) {
        if (strs.length == 0) return "";
        Arrays.sort(strs);
        String a = strs[0], b = strs[strs.length - 1];
        int i = 0;
        while (i < Math.min(a.length(), b.length()) && a.charAt(i) == b.charAt(i)) i++;
        return a.substring(0, i);
    }
}
```

#### Key Takeaways
- Sorting puts "extreme" strings at the ends — a neat trick for prefix problems.

[↑ Contents](#contents) · [← Previous](#p45) · [Next →](#p47)

---

<a id="p47"></a>

### 47. Isomorphic Strings

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Strings | Basic | No | [LeetCode](https://leetcode.com/problems/isomorphic-strings/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Two strings `s` and `t` are **isomorphic** if the characters of `s` can be replaced to get `t`, with a one-to-one mapping (no two characters map to the same character; a character may map to itself). Return whether they are isomorphic (LeetCode 205).

```text
s = "egg",   t = "add"   -> true   (e→a, g→d)
s = "foo",   t = "bar"   -> false  (o would need to map to both a and r)
s = "badc",  t = "baba"  -> false  (b→b and d→b: two chars map to b)
```

#### Approach 1: Two hash maps (s→t and t→s)
Walk both strings together. If `s[i]` already maps to something other than `t[i]`, or `t[i]` is already mapped from something other than `s[i]`, return false; otherwise record both directions.

**Complexity:** Time O(n), Space O(k) (k = alphabet size).

**C++**
```cpp
bool isIsomorphic(string s, string t) {
    unordered_map<char, char> st, ts;
    for (int i = 0; i < (int)s.size(); i++) {
        char a = s[i], b = t[i];
        if ((st.count(a) && st[a] != b) || (ts.count(b) && ts[b] != a)) return false;
        st[a] = b; ts[b] = a;
    }
    return true;
}
```

**Java**
```java
class Solution {
    public boolean isIsomorphic(String s, String t) {
        Map<Character, Character> st = new HashMap<>(), ts = new HashMap<>();
        for (int i = 0; i < s.length(); i++) {
            char a = s.charAt(i), b = t.charAt(i);
            if ((st.containsKey(a) && st.get(a) != b) || (ts.containsKey(b) && ts.get(b) != a)) return false;
            st.put(a, b); ts.put(b, a);
        }
        return true;
    }
}
```

#### Approach 2: Last-seen positions (arrays of size 256)
Two characters correspond iff they were last seen at the same position. Store `i + 1` (so 0 means "never seen") for `s[i]` and `t[i]`; if the stored values differ at any step, the strings are not isomorphic.

**Complexity:** Time O(n), Space O(256) = O(1).

**C++**
```cpp
bool isIsomorphicArr(string s, string t) {
    int ms[256] = {0}, mt[256] = {0};
    for (int i = 0; i < (int)s.size(); i++) {
        unsigned char a = s[i], b = t[i];
        if (ms[a] != mt[b]) return false;
        ms[a] = mt[b] = i + 1;
    }
    return true;
}
```

**Java**
```java
class Solution {
    static boolean isIsomorphicArr(String s, String t) {
        int[] ms = new int[256], mt = new int[256];
        for (int i = 0; i < s.length(); i++) {
            char a = s.charAt(i), b = t.charAt(i);
            if (ms[a] != mt[b]) return false;
            ms[a] = mt[b] = i + 1;
        }
        return true;
    }
}
```

#### Key Takeaways
- One-to-one mappings need checks in **both** directions.

[↑ Contents](#contents) · [← Previous](#p46) · [Next →](#p48)

---

<a id="p48"></a>

### 48. Rotate String

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Strings | Core | No | [LeetCode](https://leetcode.com/problems/rotate-string/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return `true` if string `s` can become `goal` after some number of left shifts (moving the first character to the end) (LeetCode 796).

```text
s = "abcde", goal = "cdeab" -> true
s = "abcde", goal = "abced" -> false
```

#### Approach 1: Brute force — try every rotation
For each `k` in `0..n−1`, build `s.substr(k) + s.substr(0, k)` and compare with `goal`.

**Complexity:** Time O(n²), Space O(n).

**C++**
```cpp
bool rotateStringBrute(string s, string goal) {
    if (s.size() != goal.size()) return false;
    int n = s.size();
    for (int k = 0; k < n; k++)
        if (s.substr(k) + s.substr(0, k) == goal) return true;
    return n == 0;
}
```

**Java**
```java
class Solution {
    static boolean rotateStringBrute(String s, String goal) {
        if (s.length() != goal.length()) return false;
        int n = s.length();
        for (int k = 0; k < n; k++)
            if ((s.substring(k) + s.substring(0, k)).equals(goal)) return true;
        return n == 0;
    }
}
```

#### Approach 2: Optimal — `goal` must be a substring of `s + s`
Every rotation of `s` appears as a length-`n` window inside `s + s` ("abcdeabcde" contains "cdeab"). So check equal lengths and `(s + s).find(goal)`.

**Complexity:** Time O(n) with KMP; the library `find`/`contains` is O(n²) in the worst case but fast in practice. Space O(n).

**C++**
```cpp
bool rotateString(string s, string goal) {
    return s.size() == goal.size() && (s + s).find(goal) != string::npos;
}
```

**Java**
```java
class Solution {
    public boolean rotateString(String s, String goal) {
        return s.length() == goal.length() && (s + s).contains(goal);
    }
}
```

#### Key Takeaways
- Doubling a string (or array) is the standard trick for rotation and circular problems.

[↑ Contents](#contents) · [← Previous](#p47) · [Next →](#p49)

---

<a id="p49"></a>

### 49. Valid Anagram

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Strings | Basic | No | [LeetCode](https://leetcode.com/problems/valid-anagram/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-if-two-strings-are-anagrams) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return `true` if `t` is an anagram of `s` — the same characters with the same counts, possibly in a different order (LeetCode 242).

```text
s = "anagram", t = "nagaram" -> true
s = "rat",     t = "car"     -> false
```

#### Approach 1: Sort both strings
Two strings are anagrams iff their sorted forms are equal.

**Complexity:** Time O(n log n), Space O(1) extra (or O(n) for copies).

**C++**
```cpp
bool isAnagramSort(string s, string t) {
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}
```

**Java**
```java
class Solution {
    static boolean isAnagramSort(String s, String t) {
        char[] a = s.toCharArray(), b = t.toCharArray();
        Arrays.sort(a); Arrays.sort(b);
        return Arrays.equals(a, b);
    }
}
```

#### Approach 2: Optimal — frequency count
Increment counts for `s`, decrement for `t`; all counts must end at 0.

**Complexity:** Time O(n), Space O(26).

**C++**
```cpp
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    int cnt[26] = {0};
    for (int i = 0; i < (int)s.size(); i++) { cnt[s[i] - 'a']++; cnt[t[i] - 'a']--; }
    for (int c : cnt) if (c != 0) return false;
    return true;
}
```

**Java**
```java
class Solution {
    public boolean isAnagram(String s, String t) {
        if (s.length() != t.length()) return false;
        int[] cnt = new int[26];
        for (int i = 0; i < s.length(); i++) { cnt[s.charAt(i) - 'a']++; cnt[t.charAt(i) - 'a']--; }
        for (int c : cnt) if (c != 0) return false;
        return true;
    }
}
```

#### Edge Cases & Pitfalls
- For Unicode / mixed-case input use a hash map instead of a 26-slot array.

#### Key Takeaways
- Anagram problems are frequency-count problems.

[↑ Contents](#contents) · [← Previous](#p48) · [Next →](#p50)

---

<a id="p50"></a>

### 50. Sort Characters by Frequency

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Strings | Core | No | [LeetCode](https://leetcode.com/problems/sort-characters-by-frequency/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/sort-characters-by-frequency) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Sort a string in **decreasing order of character frequency** (LeetCode 451). Characters with equal frequency may appear in any order (the takeUforward version breaks ties alphabetically).

```text
"tree"   -> "eert"   ("eetr" is also valid on LeetCode)
"cccaaa" -> "aaaccc" or "cccaaa"
"Aabb"   -> "bbAa"
```

#### Approach 1: Count + sort by frequency
Count each character, put `(freq, char)` pairs into a list, sort by frequency descending (then by character), and build the result.

**Complexity:** Time O(n + k log k) with k distinct characters (≤ 128), Space O(n).

**C++**
```cpp
string frequencySort(string s) {
    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;
    vector<pair<int, char>> v;
    for (auto& [c, f] : freq) v.push_back({f, c});
    sort(v.begin(), v.end(), [](const pair<int,char>& a, const pair<int,char>& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });
    string res;
    for (auto& [f, c] : v) res.append(f, c);
    return res;
}
```

**Java**
```java
class Solution {
    public String frequencySort(String s) {
        Map<Character, Integer> freq = new HashMap<>();
        for (char c : s.toCharArray()) freq.merge(c, 1, Integer::sum);
        List<Character> chars = new ArrayList<>(freq.keySet());
        chars.sort((a, b) -> !freq.get(a).equals(freq.get(b)) ? freq.get(b) - freq.get(a) : a - b);
        StringBuilder sb = new StringBuilder();
        for (char c : chars) sb.append(String.valueOf(c).repeat(freq.get(c)));
        return sb.toString();
    }
}
```

#### Approach 2: Bucket sort by frequency
Frequencies are between 1 and n, so put each character into `bucket[freq]` and read buckets from high to low.

**Complexity:** Time O(n), Space O(n).

**C++**
```cpp
string frequencySortBucket(string s) {
    int n = s.size();
    vector<int> freq(128, 0);
    for (char c : s) freq[c]++;
    vector<string> bucket(n + 1);
    for (int c = 0; c < 128; c++)
        if (freq[c]) bucket[freq[c]].push_back((char)c);
    string res;
    for (int f = n; f >= 1; f--)
        for (char c : bucket[f]) res.append(f, c);
    return res;
}
```

**Java**
```java
class Solution {
    static String frequencySortBucket(String s) {
        int n = s.length();
        int[] freq = new int[128];
        for (char c : s.toCharArray()) freq[c]++;
        List<List<Character>> bucket = new ArrayList<>();
        for (int i = 0; i <= n; i++) bucket.add(new ArrayList<>());
        for (int c = 0; c < 128; c++) if (freq[c] > 0) bucket.get(freq[c]).add((char) c);
        StringBuilder sb = new StringBuilder();
        for (int f = n; f >= 1; f--)
            for (char c : bucket.get(f)) sb.append(String.valueOf(c).repeat(f));
        return sb.toString();
    }
}
```

#### Key Takeaways
- When the sort key is bounded by n (frequencies), bucket sort gives linear time.

[↑ Contents](#contents) · [← Previous](#p49) · [Next →](#p51)

---

## Basic Recursion

<a id="p51"></a>

### 51. Sum of First N Numbers

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Basic | No | — | [Watch](https://youtu.be/69ZCDFy-OUo) |

#### Problem Statement
Given `n`, return the sum of the first `n` natural numbers: `1 + 2 + … + n`.

```text
n = 3 -> 6
n = 5 -> 15
```

The video uses this problem to teach the two basic styles of recursion: **parameterised** and **functional**.

#### Approach 1: Formula / loop *(not in video)*
`n(n + 1) / 2` in O(1), or a simple loop in O(n).

**C++**
```cpp
long long sumFormula(long long n) { return n * (n + 1) / 2; }
```

**Java**
```java
class Solution {
    static long sumFormula(long n) { return n * (n + 1) / 2; }
}
```

#### Approach 2: Parameterised recursion (from the video)
Carry the running answer **as a parameter**. `f(i, sum)`: if `i < 1`, the work is finished — print/return `sum`; otherwise call `f(i − 1, sum + i)`. Start with `f(n, 0)`.

**Recursion tree (n = 3):** f(3, 0) → f(2, 3) → f(1, 5) → f(0, 6) → `i < 1`, print **6**, then every call returns.

**Complexity:** Time O(n), Space O(n) recursion stack.

**C++**
```cpp
void sumParam(int i, int sum) {
    if (i < 1) {
        cout << sum << "\n";
        return;
    }
    sumParam(i - 1, sum + i);
}
// call: sumParam(n, 0);
```

**Java**
```java
class Solution {
    static void sumParam(int i, int sum) {
        if (i < 1) {
            System.out.println(sum);
            return;
        }
        sumParam(i - 1, sum + i);
    }
}
```

#### Approach 3: Functional recursion (from the video)
Make the function **return** the answer, which is what you'll need later (e.g. in dynamic programming): `sum(n) = n + sum(n − 1)`, base case `sum(0) = 0`.

**How it unwinds (n = 3):** `3 + sum(2)` waits → `2 + sum(1)` waits → `1 + sum(0)` waits → `sum(0)` returns 0 → `1 + 0 = 1` → `2 + 1 = 3` → `3 + 3 = 6`.

**Complexity:** Time O(n), Space O(n) recursion stack.

**C++**
```cpp
int sumFunc(int n) {
    if (n == 0) return 0;
    return n + sumFunc(n - 1);
}
```

**Java**
```java
class Solution {
    static int sumFunc(int n) {
        if (n == 0) return 0;
        return n + sumFunc(n - 1);
    }
}
```

#### Key Takeaways
- **Parameterised:** the answer travels down in the arguments and is used at the base case.
- **Functional:** the answer travels back up through return values; each call combines its own part with the sub-answer.

[↑ Contents](#contents) · [← Previous](#p50) · [Next →](#p52)

---

<a id="p52"></a>

### 52. Factorial of a Given Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Basic | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/factorial-of-a-number-using-recursion) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Compute `n!` using recursion.

```text
n = 3 -> 6
n = 5 -> 120
n = 0 -> 1
```

#### Approach 1: Functional recursion
`fact(n) = n × fact(n − 1)` with base case `fact(0) = 1` (or `fact(1) = 1`). The base case must return 1, the identity for multiplication — returning 0 would make the whole product 0 (see "Factorial of a given number" in Basic Maths).

**Complexity:** Time O(n), Space O(n) recursion stack.

**C++**
```cpp
long long fact(int n) {
    if (n <= 1) return 1;
    return n * fact(n - 1);
}
```

**Java**
```java
class Solution {
    static long fact(int n) {
        if (n <= 1) return 1;
        return n * fact(n - 1);
    }
}
```

#### Approach 2: Parameterised recursion
Carry the product so far: `f(i, prod)` → if `i < 1` return `prod`, else `f(i − 1, prod × i)`. Start with `f(n, 1)`.

**C++**
```cpp
long long factParam(int i, long long prod) {
    if (i < 1) return prod;
    return factParam(i - 1, prod * i);
}
// call: factParam(n, 1);
```

**Java**
```java
class Solution {
    static long factParam(int i, long prod) {
        if (i < 1) return prod;
        return factParam(i - 1, prod * i);
    }
}
```

#### Edge Cases & Pitfalls
- 21! already exceeds 64-bit range; very large `n` also risks stack overflow with recursion.

#### Key Takeaways
- Same skeleton as sum-of-first-N; only the operator and the base value change.

[↑ Contents](#contents) · [← Previous](#p51) · [Next →](#p53)

---

<a id="p53"></a>

### 53. Sum of Array Elements II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Basic | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the sum of all elements of an array using recursion.

```text
[1, 2, 3]       -> 6
[5, 8, 10, -2]  -> 21
```

#### Approach 1: Functional recursion from the front
`sum(i) = arr[i] + sum(i + 1)`; base case `i == n` → 0. Call `sum(0)`.

**Complexity:** Time O(n), Space O(n) stack.

**C++**
```cpp
int arraySum(vector<int>& arr, int i) {
    if (i == (int)arr.size()) return 0;
    return arr[i] + arraySum(arr, i + 1);
}
// call: arraySum(arr, 0);
```

**Java**
```java
class Solution {
    static int arraySum(int[] arr, int i) {
        if (i == arr.length) return 0;
        return arr[i] + arraySum(arr, i + 1);
    }
}
```

#### Approach 2: Recursion on the size (from the back)
`sum(n) = arr[n − 1] + sum(n − 1)`; base case `n == 0` → 0.

**C++**
```cpp
int arraySumBack(vector<int>& arr, int n) {
    if (n == 0) return 0;
    return arr[n - 1] + arraySumBack(arr, n - 1);
}
```

**Java**
```java
class Solution {
    static int arraySumBack(int[] arr, int n) {
        if (n == 0) return 0;
        return arr[n - 1] + arraySumBack(arr, n - 1);
    }
}
```

#### Key Takeaways
- Array recursion = "handle one index, delegate the rest". The base case is the empty range.

[↑ Contents](#contents) · [← Previous](#p52) · [Next →](#p54)

---

<a id="p54"></a>

### 54. Reverse a String I

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Basic | No | [LeetCode](https://leetcode.com/problems/reverse-string/) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Reverse a string (array of characters) **using recursion**, in place.

```text
['h','e','l','l','o'] -> ['o','l','l','e','h']
```

#### Approach 1: Recursion with two pointers
Swap `s[l]` and `s[r]`, then recurse on `(l + 1, r − 1)`; stop when `l >= r`.

**Complexity:** Time O(n), Space O(n/2) recursion stack.

**C++**
```cpp
void revRec(vector<char>& s, int l, int r) {
    if (l >= r) return;
    swap(s[l], s[r]);
    revRec(s, l + 1, r - 1);
}
void reverseString(vector<char>& s) { revRec(s, 0, (int)s.size() - 1); }
```

**Java**
```java
class Solution {
    static void revRec(char[] s, int l, int r) {
        if (l >= r) return;
        char t = s[l]; s[l] = s[r]; s[r] = t;
        revRec(s, l + 1, r - 1);
    }
    public void reverseString(char[] s) { revRec(s, 0, s.length - 1); }
}
```

#### Approach 2: Recursion with one pointer
Index `i` pairs with `n − i − 1`; stop at `i >= n / 2`.

**C++**
```cpp
void revRec1(vector<char>& s, int i) {
    int n = s.size();
    if (i >= n / 2) return;
    swap(s[i], s[n - i - 1]);
    revRec1(s, i + 1);
}
```

**Java**
```java
class Solution {
    static void revRec1(char[] s, int i) {
        int n = s.length;
        if (i >= n / 2) return;
        char t = s[i]; s[i] = s[n - i - 1]; s[n - i - 1] = t;
        revRec1(s, i + 1);
    }
}
```

#### Key Takeaways
- Identical to reversing an integer array; the iterative two-pointer loop (O(1) space) is preferred in practice.

[↑ Contents](#contents) · [← Previous](#p53) · [Next →](#p55)

---

<a id="p55"></a>

### 55. Check if String is Palindrome or Not

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Basic | No | [LeetCode](https://leetcode.com/problems/valid-palindrome/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-whether-a-string-is-a-palindrome) | [Watch](https://youtu.be/twuC1F6gLI8) |

#### Problem Statement
Check whether a string is a palindrome **using recursion** — a palindrome reads the same after reversal ("madam", "11211").

```text
"madam" -> true
"madbm" -> false
```
(The LeetCode link on the sheet is "Valid Palindrome", which additionally ignores non-alphanumeric characters and case — see "Palindrome Check" in Basic Strings for that cleaning step.)

#### Intuition (from the video)
Reversing swaps `s[i]` with `s[n − i − 1]`. If the string must stay the same after reversing, then every such pair must already be **equal**. So instead of swapping, **compare**.

#### Approach: Functional recursion with one pointer
`f(i)`:
- if `i >= n / 2` → every pair matched → return `true`;
- if `s[i] != s[n − i − 1]` → return `false` (stop immediately);
- otherwise return `f(i + 1)`.

**Dry run "madam":** f(0): m == m → f(1): a == a → f(2): 2 ≥ 5/2 → true, propagated back up.
**"madbm":** f(0): m == m → f(1): a ≠ b → false, propagated back up — later pairs are never checked.

**Complexity:** Time O(n/2), Space O(n/2) recursion stack.

**C++**
```cpp
bool palRec(int i, const string& s) {
    int n = s.size();
    if (i >= n / 2) return true;
    if (s[i] != s[n - i - 1]) return false;
    return palRec(i + 1, s);
}
// call: palRec(0, s);
```

**Java**
```java
class Solution {
    static boolean palRec(int i, String s) {
        int n = s.length();
        if (i >= n / 2) return true;
        if (s.charAt(i) != s.charAt(n - i - 1)) return false;
        return palRec(i + 1, s);
    }
}
```

#### Edge Cases & Pitfalls
- Pass the string by (const) reference in C++ — passing by value copies it at every call (O(n²) total).

#### Key Takeaways
- A recursive boolean check: return `false` as soon as a violation appears, `true` at the base case, otherwise return whatever the next call returns.

[↑ Contents](#contents) · [← Previous](#p54) · [Next →](#p56)

---

<a id="p56"></a>

### 56. Check if a Number is Prime or Not

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Core | Yes | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Check whether a number `n` is prime **using recursion**.

```text
7  -> true
12 -> false
1  -> false
```

#### Approach 1: Recursion over candidate divisors up to √n
`check(n, d)`:
- if `d * d > n` → no divisor found → prime;
- if `n % d == 0` → divisible → not prime;
- else `check(n, d + 1)`.
Handle `n < 2` (not prime) before calling `check(n, 2)`.

**Complexity:** Time O(√n), Space O(√n) recursion stack.

**C++**
```cpp
bool check(int n, long long d) {
    if (d * d > n) return true;
    if (n % d == 0) return false;
    return check(n, d + 1);
}
bool isPrimeRec(int n) {
    if (n < 2) return false;
    return check(n, 2);
}
```

**Java**
```java
class Solution {
    static boolean check(int n, long d) {
        if (d * d > n) return true;
        if (n % d == 0) return false;
        return check(n, d + 1);
    }
    static boolean isPrimeRec(int n) {
        if (n < 2) return false;
        return check(n, 2);
    }
}
```

#### Approach 2: Iterative (for comparison)
The same idea with a loop avoids the recursion stack: O(√n) time, O(1) space.

**C++**
```cpp
bool isPrimeIter(int n) {
    if (n < 2) return false;
    for (long long d = 2; d * d <= n; d++)
        if (n % d == 0) return false;
    return true;
}
```

**Java**
```java
class Solution {
    static boolean isPrimeIter(int n) {
        if (n < 2) return false;
        for (long d = 2; d * d <= n; d++)
            if (n % d == 0) return false;
        return true;
    }
}
```

#### Key Takeaways
- A `for` loop with an early exit translates directly into tail recursion: the loop variable becomes a parameter.

[↑ Contents](#contents) · [← Previous](#p55) · [Next →](#p57)

---

<a id="p57"></a>

### 57. Reverse an array 2

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/reversing-an-array-using-recursion) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Reverse an array **using recursion** (in place).

```text
[1, 2, 3, 4, 5] -> [5, 4, 3, 2, 1]
```

#### Approach 1: Two-pointer recursion
`rev(l, r)`: if `l >= r` return; swap `arr[l]`, `arr[r]`; call `rev(l + 1, r − 1)`.

**Complexity:** Time O(n), Space O(n) recursion stack.

**C++**
```cpp
void rev(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    swap(arr[l], arr[r]);
    rev(arr, l + 1, r - 1);
}
```

**Java**
```java
class Solution {
    static void rev(int[] arr, int l, int r) {
        if (l >= r) return;
        int t = arr[l]; arr[l] = arr[r]; arr[r] = t;
        rev(arr, l + 1, r - 1);
    }
}
```

#### Approach 2: Single-pointer recursion
`rev(i)`: if `i >= n / 2` return; swap `arr[i]` with `arr[n − i − 1]`; call `rev(i + 1)`.

**C++**
```cpp
void rev1(vector<int>& arr, int i) {
    int n = arr.size();
    if (i >= n / 2) return;
    swap(arr[i], arr[n - i - 1]);
    rev1(arr, i + 1);
}
```

**Java**
```java
class Solution {
    static void rev1(int[] arr, int i) {
        int n = arr.length;
        if (i >= n / 2) return;
        int t = arr[i]; arr[i] = arr[n - i - 1]; arr[n - i - 1] = t;
        rev1(arr, i + 1);
    }
}
```

#### Key Takeaways
- See "Reverse an array" in Basic Arrays for the video walkthrough of both recursive versions.

[↑ Contents](#contents) · [← Previous](#p56) · [Next →](#p58)

---

<a id="p58"></a>

### 58. Check if the Array is Sorted II

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Basic | Yes | [LeetCode](https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/) · [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/check-if-an-array-is-sorted-in-ascending-order) | [Watch from 28:44](https://youtu.be/37E9ckMDdTk?t=1724) |

#### Problem Statement
Check whether an array is sorted in non-decreasing order (this section asks you to practise it with recursion). The LeetCode link on the sheet (1752) is a variant: return `true` if the array is sorted **and then rotated** some number of times (possibly zero).

```text
[1, 2, 2, 3, 3, 4] -> true
[1, 2, 1, 3, 4]    -> false
LC 1752: [3, 4, 5, 1, 2] -> true   (rotation of [1,2,3,4,5])
         [2, 1, 3, 4]    -> false
```
> The sheet's video link points to t = 17224 s, which is past the end of this 43-minute video; the relevant part actually starts at **28:44** (≈ 1724 s), which is the timestamp used here.

#### Approach 1: Iterative — compare with the previous element (from the video)
Start from index 1; if `arr[i] >= arr[i − 1]` keep going, otherwise return `false` immediately. If the loop finishes, return `true`. The video points out there is no separate brute/better/optimal here — a single pass is already optimal.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
bool isSorted(vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); i++)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}
```

**Java**
```java
class Solution {
    static boolean isSorted(int[] arr) {
        for (int i = 1; i < arr.length; i++)
            if (arr[i] < arr[i - 1]) return false;
        return true;
    }
}
```

#### Approach 2: Recursive version *(not in video)*
`sorted(i)`: if `i >= n` return true; if `arr[i] < arr[i − 1]` return false; return `sorted(i + 1)`. Call `sorted(1)`.

**Complexity:** Time O(n), Space O(n) recursion stack.

**C++**
```cpp
bool sortedRec(vector<int>& arr, int i) {
    if (i >= (int)arr.size()) return true;
    if (arr[i] < arr[i - 1]) return false;
    return sortedRec(arr, i + 1);
}
// call: sortedRec(arr, 1);
```

**Java**
```java
class Solution {
    static boolean sortedRec(int[] arr, int i) {
        if (i >= arr.length) return true;
        if (arr[i] < arr[i - 1]) return false;
        return sortedRec(arr, i + 1);
    }
}
```

#### Approach 3: LeetCode 1752 — sorted and rotated *(not in video)*
Count the "drops" where `nums[i] > nums[(i + 1) % n]` (comparing circularly). A sorted array rotated any number of times has **at most one** drop.

**Complexity:** Time O(n), Space O(1).

**C++**
```cpp
bool check(vector<int>& nums) {
    int n = nums.size(), drops = 0;
    for (int i = 0; i < n; i++)
        if (nums[i] > nums[(i + 1) % n]) drops++;
    return drops <= 1;
}
```

**Java**
```java
class Solution {
    public boolean check(int[] nums) {
        int n = nums.length, drops = 0;
        for (int i = 0; i < n; i++)
            if (nums[i] > nums[(i + 1) % n]) drops++;
        return drops <= 1;
    }
}
```

#### Key Takeaways
- "Non-decreasing" allows equal neighbours — compare with `<`, not `<=`, when looking for violations.

[↑ Contents](#contents) · [← Previous](#p57) · [Next →](#p59)

---

<a id="p59"></a>

### 59. Sum of Digits in a Given Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Basic | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/sum-of-digits-of-a-number-using-recursion) | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Return the sum of the digits of a non-negative integer `n` **using recursion**.

```text
n = 12345 -> 15
n = 7     -> 7
n = 0     -> 0
```

#### Approach 1: Functional recursion
`digitSum(n) = (n % 10) + digitSum(n / 10)`; base case `n == 0` → 0. Each call peels off the last digit (digit-extraction idea).

**Dry run (123):** 3 + ds(12) → 2 + ds(1) → 1 + ds(0) = 1 → 3 → 6.

**Complexity:** Time O(log₁₀ n), Space O(log₁₀ n) recursion stack.

**C++**
```cpp
int digitSum(int n) {
    if (n == 0) return 0;
    return n % 10 + digitSum(n / 10);
}
```

**Java**
```java
class Solution {
    static int digitSum(int n) {
        if (n == 0) return 0;
        return n % 10 + digitSum(n / 10);
    }
}
```

#### Approach 2: Iterative
Same loop as digit extraction with an accumulator — O(log n) time, O(1) space.

**C++**
```cpp
int digitSumIter(int n) {
    int s = 0;
    while (n > 0) { s += n % 10; n /= 10; }
    return s;
}
```

**Java**
```java
class Solution {
    static int digitSumIter(int n) {
        int s = 0;
        while (n > 0) { s += n % 10; n /= 10; }
        return s;
    }
}
```

#### Key Takeaways
- Number recursion usually shrinks the input by `/ 10` and works with `% 10`.

[↑ Contents](#contents) · [← Previous](#p58) · [Next →](#p60)

---

<a id="p60"></a>

### 60. Fibonacci Number

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Beginner Problems › Basic Recursion | Core | No | [LeetCode](https://leetcode.com/problems/fibonacci-number/) | [Watch](https://youtu.be/kvRjNm4rVBE) |

#### Problem Statement
Return the `n`-th Fibonacci number, where `F(0) = 0`, `F(1) = 1` and `F(n) = F(n − 1) + F(n − 2)` (LeetCode 509).

```text
Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
n = 3 -> 2,  n = 4 -> 3,  n = 5 -> 5
```

#### Approach 1: Iterative loop (mentioned in the video)
Fill `f[0] = 0`, `f[1] = 1`, then `f[i] = f[i − 1] + f[i − 2]` for `i = 2..n`. Only the last two values are ever needed, so two variables suffice.

**Complexity:** Time O(n), Space O(1) (with two variables).

**C++**
```cpp
int fibIter(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}
```

**Java**
```java
class Solution {
    static int fibIter(int n) {
        if (n <= 1) return n;
        int prev2 = 0, prev1 = 1;
        for (int i = 2; i <= n; i++) {
            int cur = prev1 + prev2;
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
}
```

#### Approach 2: Recursion with multiple calls (the focus of the video)
`fib(n) = fib(n − 1) + fib(n − 2)`, base case `n <= 1` → return `n`.

**How two recursive calls execute:** they do **not** run simultaneously. `last = fib(n − 1)` runs to completion first (its whole subtree), and only then does `secondLast = fib(n − 2)` start.

**Recursion tree for fib(4)** (left child is always evaluated first):
```text
                fib(4)=3
              /          \
        fib(3)=2        fib(2)=1
        /     \          /    \
   fib(2)=1  fib(1)=1  fib(1) fib(0)
    /    \
 fib(1) fib(0)
```
That is 9 calls for n = 4, not 4.

**Complexity:** Every call spawns two more, so the call count grows like 2ⁿ — **exponential** (not exactly 2ⁿ because the right branch is shallower; the tight bound is about 1.618ⁿ). Space O(n) for the deepest recursion path. The video notes this will be optimised later with dynamic programming.

**C++**
```cpp
int fib(int n) {
    if (n <= 1) return n;
    int last = fib(n - 1);
    int secondLast = fib(n - 2);
    return last + secondLast;
}
```

**Java**
```java
class Solution {
    static int fib(int n) {
        if (n <= 1) return n;
        int last = fib(n - 1);
        int secondLast = fib(n - 2);
        return last + secondLast;
    }
}
```

#### Approach 3: Memoisation (top-down DP) *(not in video — previews the DP section)*
Store each `fib(i)` the first time it's computed; repeated subtrees become O(1) look-ups.

**Complexity:** Time O(n), Space O(n) (memo + stack).

**C++**
```cpp
int fibMemo(int n, vector<int>& dp) {
    if (n <= 1) return n;
    if (dp[n] != -1) return dp[n];
    return dp[n] = fibMemo(n - 1, dp) + fibMemo(n - 2, dp);
}
// call: vector<int> dp(n + 1, -1); fibMemo(n, dp);
```

**Java**
```java
class Solution {
    static int fibMemo(int n, int[] dp) {
        if (n <= 1) return n;
        if (dp[n] != -1) return dp[n];
        return dp[n] = fibMemo(n - 1, dp) + fibMemo(n - 2, dp);
    }
    // call: int[] dp = new int[n + 1]; Arrays.fill(dp, -1); fibMemo(n, dp);
}
```

#### Key Takeaways
- With multiple recursive calls, the first call (and its entire subtree) finishes before the second begins — draw the recursion tree top-down, left to right.
- Overlapping subproblems (fib(2) computed twice above) are the signal for dynamic programming.

[↑ Contents](#contents) · [← Previous](#p59)

---
