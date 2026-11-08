# Sorting — Striver's A2Z DSA Sheet Notes

Section 2 of 20 · 7 problems · 5 with video, 2 without · [All sections](00-index.md)

[← Beginner Problems](01-beginner-problems.md) | [Arrays →](03-arrays.md)

> **How these notes were made:** for problems with a video, the notes follow the video's auto-generated transcript (approaches, intuition, dry runs, complexity). Code is written in C++ and Java for every approach discussed. Anything not covered in the video is marked *(not in video)*. Problems without a video are marked as such and the notes are prepared independently.

<a id="contents"></a>

## Contents

**Algorithms**

1. [Selection Sort](#p61) — Core
2. [Bubble Sort](#p62) — Core
3. [Insertion Sorting](#p63) — Core
4. [Merge Sorting](#p64) — Core
5. [Quick Sorting](#p65) — Core
6. [Recursive Bubble Sort](#p66) — Core · *no video*
7. [Recursive Insertion Sort](#p67) — Core · *no video*

---

## Algorithms

<a id="p61"></a>

### 1. Selection Sort

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sorting › Algorithms | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/selection-sort-algorithm) | [Watch from 2:47](https://youtu.be/HGk_ypEuS24?t=167) |

#### Problem Statement
Sort an array in ascending order using **selection sort**.

```text
[13, 46, 24, 52, 20, 9] -> [9, 13, 20, 24, 46, 52]
```

#### Intuition (from the video)
As the name says, you **select the minimum**: find the smallest element of the unsorted part and swap it to the front of that part. Repeat on the remaining unsorted part.

**Walkthrough ([13, 46, 24, 52, 20, 9]):**

| Step | Range searched | Minimum | Swap with | Array after step |
|---|---|---|---|---|
| 1 | 0..5 | 9 | index 0 (13) | 9, 46, 24, 52, 20, 13 |
| 2 | 1..5 | 13 | index 1 (46) | 9, 13, 24, 52, 20, 46 |
| 3 | 2..5 | 20 | index 2 (24) | 9, 13, 20, 52, 24, 46 |
| 4 | 3..5 | 24 | index 3 (52) | 9, 13, 20, 24, 52, 46 |
| 5 | 4..5 | 46 | index 4 (52) | 9, 13, 20, 24, 46, 52 |

After `n − 1` steps the last element is automatically in place (a single element is always sorted).

#### Algorithm
- Outer loop `i = 0 .. n−2`: the position being filled.
- Inner loop `j = i .. n−1`: find `mini`, the index of the minimum (start with `mini = i`; update when `arr[j] < arr[mini]`).
- Swap `arr[i]` with `arr[mini]`.

**Swap with a temporary variable:** `temp = a[mini]; a[mini] = a[i]; a[i] = temp;`

**Complexity:** the inner loop runs n, n−1, n−2, … times → ≈ n(n+1)/2 → **O(n²)** in the best, average and worst case (it scans even if the array is already sorted). Space O(1). Not stable.

**C++**
```cpp
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= n - 2; i++) {
        int mini = i;
        for (int j = i; j <= n - 1; j++)
            if (arr[j] < arr[mini]) mini = j;
        int temp = arr[mini];
        arr[mini] = arr[i];
        arr[i] = temp;
    }
}
```

**Java**
```java
class Solution {
    static void selectionSort(int[] arr) {
        int n = arr.length;
        for (int i = 0; i <= n - 2; i++) {
            int mini = i;
            for (int j = i; j <= n - 1; j++)
                if (arr[j] < arr[mini]) mini = j;
            int temp = arr[mini];
            arr[mini] = arr[i];
            arr[i] = temp;
        }
    }
}
```

#### Key Takeaways
- Selection sort = "select minimum, swap to front". Exactly `n − 1` swaps at most, which is useful when writes are expensive.

[↑ Contents](#contents) · [Next →](#p62)

---

<a id="p62"></a>

### 2. Bubble Sort

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sorting › Algorithms | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/bubble-sort-algorithm) | [Watch from 17:41](https://youtu.be/HGk_ypEuS24?t=1061) |

#### Problem Statement
Sort an array in ascending order using **bubble sort**.

```text
[13, 46, 24, 52, 20, 9] -> [9, 13, 20, 24, 46, 52]
```

#### Intuition (from the video)
Bubble sort **pushes the maximum to the end** (the opposite of selection sort) using **adjacent swaps**: compare each neighbouring pair and swap if they are out of order. After one full pass, the largest element has "bubbled" to the last position.

**Pass 1 ([13, 46, 24, 52, 20, 9]):** 13/46 ok → 46/24 swap → 46/52 ok → 52/20 swap → 52/9 swap → `[13, 24, 46, 20, 9, 52]` — 52 is in place.
**Pass 2:** works on indices 0..4 only → `[13, 24, 20, 9, 46, 52]` — 46 in place. And so on; after `n − 1` passes the array is sorted.

#### Algorithm
- Outer loop `i` from `n − 1` down to 1: the last index of the unsorted part.
- Inner loop `j` from 0 to `i − 1`: compare `arr[j]` and `arr[j + 1]`, swap if `arr[j] > arr[j + 1]`.
- The inner loop must stop at `i − 1` because it reads `j + 1`; going to `i` would read past the unsorted range (and at `i = n − 1`, past the array → runtime error).

#### Optimisation: stop when a pass makes no swaps
If a whole pass performs no swap, every adjacent pair is in order, so the array is already sorted — break out. On a sorted input the algorithm then does a single pass.

**Complexity:**
- Worst/average: n + (n−1) + … ≈ n²/2 → **O(n²)**.
- Best (already sorted, with the `didSwap` optimisation): **O(n)** — a common interview follow-up.
- Space O(1). Stable.

**C++**
```cpp
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i >= 1; i--) {
        bool didSwap = false;
        for (int j = 0; j <= i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                didSwap = true;
            }
        }
        if (!didSwap) break;     // no swaps -> already sorted
    }
}
```

**Java**
```java
class Solution {
    static void bubbleSort(int[] arr) {
        int n = arr.length;
        for (int i = n - 1; i >= 1; i--) {
            boolean didSwap = false;
            for (int j = 0; j <= i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j + 1];
                    arr[j + 1] = arr[j];
                    arr[j] = temp;
                    didSwap = true;
                }
            }
            if (!didSwap) break;
        }
    }
}
```

#### Key Takeaways
- Bubble sort: adjacent swaps push the max to the end each pass.
- Mention the early-exit optimisation and its O(n) best case in interviews.

[↑ Contents](#contents) · [← Previous](#p61) · [Next →](#p63)

---

<a id="p63"></a>

### 3. Insertion Sorting

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sorting › Algorithms | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/insertion-sort-algorithm) | [Watch from 31:40](https://youtu.be/HGk_ypEuS24?t=1900) |

#### Problem Statement
Sort an array in ascending order using **insertion sort**.

```text
[14, 9, 15, 12, 6, 8, 13] -> [6, 8, 9, 12, 13, 14, 15]
```

#### Intuition (from the video)
Insertion sort **takes an element and places it in its correct position** within the already-sorted prefix to its left — like arranging playing cards in your hand.

**Walkthrough:**
- [14] — one element is sorted.
- 9: smaller than 14 → swap → [9, 14].
- 15: already larger than 14 → stays → [9, 14, 15].
- 12: swap with 15, swap with 14, stop at 9 → [9, 12, 14, 15].
- 6: keeps swapping left past 15, 14, 12, 9 → [6, 9, 12, 14, 15].
- 8: swaps past 15, 14, 12, 9; stops at 6 → [6, 8, 9, 12, 14, 15].
- 13: swaps past 15, 14; stops at 12 → [6, 8, 9, 12, 13, 14, 15].

#### Algorithm
For `i = 0..n−1`: let `j = i`; while `j > 0` and `arr[j − 1] > arr[j]`, swap them and `j--`.
- The condition is `j > 0` (not `j >= 0`) because the loop reads `arr[j − 1]`; at `j = 0` that would be index −1.

**Complexity:**
- Worst (reverse-sorted, e.g. 5 4 3 2 1): each element moves all the way left: 0 + 1 + 2 + … + (n−1) → **O(n²)**; average also O(n²).
- Best (already sorted): the inner `while` never runs → **O(n)**.
- Space O(1). Stable.

**C++**
```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= n - 1; i++) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            int temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
        }
    }
}
```

**Java**
```java
class Solution {
    static void insertionSort(int[] arr) {
        int n = arr.length;
        for (int i = 0; i <= n - 1; i++) {
            int j = i;
            while (j > 0 && arr[j - 1] > arr[j]) {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
                j--;
            }
        }
    }
}
```

#### Key Takeaways
- Insertion sort is fast on nearly-sorted data (O(n) best case) and is used inside hybrid sorts (e.g. Timsort, introsort) for small ranges.

[↑ Contents](#contents) · [← Previous](#p62) · [Next →](#p64)

---

<a id="p64"></a>

### 4. Merge Sorting

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sorting › Algorithms | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/merge-sort-algorithm) | [Watch](https://youtu.be/ogjf7ORKfd8) |

#### Problem Statement
Sort an array in ascending order using **merge sort**.

```text
[3, 1, 2, 4, 1, 5, 2, 6, 4] -> [1, 1, 2, 2, 3, 4, 4, 5, 6]
```

#### Why another sort? (from the video)
Selection, bubble and insertion sort are O(n²). Merge sort runs in **O(n log n)** in every case.

#### Intuition — "divide and merge"
1. **Divide** the array into two halves (for an odd length, e.g. 9 → 5 + 4; just be consistent), and keep dividing until each part has a single element. A single element is always sorted.
2. **Merge** sorted halves back together into a sorted whole, all the way up.

The division is **hypothetical**: no new arrays are created; we only pass the index range `[low, high]` of the part being sorted.

#### Algorithm
```
mergeSort(arr, low, high):
    if low >= high: return              // 0 or 1 element
    mid = (low + high) / 2
    mergeSort(arr, low, mid)            // sort left half
    mergeSort(arr, mid + 1, high)       // sort right half
    merge(arr, low, mid, high)          // merge the two sorted halves
```

**merge(arr, low, mid, high)** — two sorted runs `[low..mid]` and `[mid+1..high]`:
1. `left = low`, `right = mid + 1`, `temp = []`.
2. While both runs have elements: append the smaller of `arr[left]`, `arr[right]` to `temp` and advance that pointer (`<=` keeps it stable).
3. Copy whatever remains of the left run, then of the right run.
4. Copy `temp` back: `arr[i] = temp[i − low]` for `i = low..high`.

**Merge dry run** (`[1, 1, 2, 3, 4]` + `[2, 4, 5, 6]`): 1, 1, 2 (left), 2 (right), 3, 4 (left) → left exhausted → copy 4, 5, 6 → `[1, 1, 2, 2, 3, 4, 4, 5, 6]`.

**Recursion dry run ([3, 2, 4, 1, 3], low = 0, high = 4):** mid = 2 → sort [0..2]: mid = 1 → sort [0..1]: mid = 0 → [0..0] and [1..1] are single elements → merge → [2, 3]; then [2..2] → merge [2, 3] + [4] → [2, 3, 4]. Then sort [3..4] → [1, 3]. Finally merge [2, 3, 4] + [1, 3] → [1, 2, 3, 3, 4]. The left call always finishes completely before the right call starts.

**Complexity:**
- The array is halved repeatedly → about log₂ n levels; each level's merges touch all n elements → **O(n log n)** in best, average and worst case.
- Space **O(n)** for the temporary array (plus O(log n) recursion stack).
- Stable.

**C++**
```cpp
void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low, right = mid + 1;
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) temp.push_back(arr[left++]);
        else temp.push_back(arr[right++]);
    }
    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);
    for (int i = low; i <= high; i++) arr[i] = temp[i - low];
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}
// call: mergeSort(arr, 0, arr.size() - 1);
```

**Java**
```java
class Solution {
    static void merge(int[] arr, int low, int mid, int high) {
        List<Integer> temp = new ArrayList<>();
        int left = low, right = mid + 1;
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) temp.add(arr[left++]);
            else temp.add(arr[right++]);
        }
        while (left <= mid) temp.add(arr[left++]);
        while (right <= high) temp.add(arr[right++]);
        for (int i = low; i <= high; i++) arr[i] = temp.get(i - low);
    }

    static void mergeSort(int[] arr, int low, int high) {
        if (low >= high) return;
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
```

#### Edge Cases & Pitfalls
- Pass the array by reference in C++ (`vector<int>&`), otherwise the sorted result is lost.
- `mid = low + (high − low) / 2` avoids overflow for huge indices *(not in video)*.

#### Key Takeaways
- Merge sort's **merge** step is a reusable tool: counting inversions and reverse pairs (Arrays section) are solved by modifying it.

[↑ Contents](#contents) · [← Previous](#p63) · [Next →](#p65)

---

<a id="p65"></a>

### 5. Quick Sorting

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sorting › Algorithms | Core | No | [Editorial](https://takeuforward.org/blogs/data-structure-and-algorithm/quick-sort-algorithm) | [Watch](https://youtu.be/WIrA4YexLRQ) |

#### Problem Statement
Sort an array in ascending order using **quick sort**.

```text
[4, 6, 2, 5, 7, 9, 1, 3] -> [1, 2, 3, 4, 5, 6, 7, 9]
```

#### Why quick sort? (from the video)
Like merge sort it averages **O(n log n)**, but it sorts **in place** — no temporary array (only the recursion stack). Both are worth knowing: many problems are solved by tweaking merge sort.

#### Intuition — a divide-and-conquer algorithm
1. **Pick a pivot** — any element works (first, last, median, random). We use the **first** element.
2. **Place the pivot at its correct position** in the sorted order, with all **smaller (or equal) elements on its left** and all **larger elements on its right**.
3. Recursively apply the same steps to the left part and the right part.

Why it works: if every element eventually gets placed at its correct sorted position, the array is sorted — regardless of which pivot you pick each time. And once the pivot is placed, everything that belongs before it is on its left and everything after it on its right.

#### Partition (placing the pivot)
Work on `[low, high]` with `pivot = arr[low]`, `i = low`, `j = high`:
- Move `i` right to the **first element greater than the pivot** (`while arr[i] <= pivot && i <= high − 1`).
- Move `j` left to the **first element ≤ pivot** (`while arr[j] > pivot && j >= low + 1`).
- If `i < j`, swap `arr[i]` and `arr[j]`; repeat while `i < j`.
- When they cross, `j` sits on the last element of the "≤ pivot" zone: swap `arr[low]` (the pivot) with `arr[j]`. `j` is the **partition index**.

Equal elements go to the left side (hence `<=` for `i` and `>` for `j`). The bounds `high − 1` and `low + 1` stop `i`/`j` running past the range.

**Dry run ([4, 6, 2, 5, 7, 9, 1, 3], pivot 4):** i stops at 6, j stops at 3 → swap → [4, 3, 2, 5, 7, 9, 1, 6]; i stops at 5, j stops at 1 → swap → [4, 3, 2, 1, 7, 9, 5, 6]; i stops at 7, j moves to 1 → crossed → swap pivot with arr[j] → **[1, 3, 2, 4, 7, 9, 5, 6]**, partition index 3. Recurse on [1, 3, 2] and [7, 9, 5, 6].

```
quickSort(arr, low, high):
    if low < high:
        p = partition(arr, low, high)
        quickSort(arr, low, p − 1)
        quickSort(arr, p + 1, high)
```

**Complexity:**
- Average/best: the range is split into two parts each time → about log n levels × O(n) partition work per level → **O(n log n)**.
- Worst case *(not in video)*: if the pivot is always the smallest/largest (e.g. an already-sorted array with first-element pivot), the split is n−1 / 0 → **O(n²)**. A random pivot makes this unlikely.
- Space: no extra array — O(1) auxiliary apart from the recursion stack (O(log n) average, O(n) worst).
- Not stable.

**C++**
```cpp
int partitionArr(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low, j = high;
    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1) i++;
        while (arr[j] > pivot && j >= low + 1) j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partitionArr(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}
// call: quickSort(arr, 0, arr.size() - 1);
```

**Java**
```java
class Solution {
    static int partition(int[] arr, int low, int high) {
        int pivot = arr[low];
        int i = low, j = high;
        while (i < j) {
            while (arr[i] <= pivot && i <= high - 1) i++;
            while (arr[j] > pivot && j >= low + 1) j--;
            if (i < j) { int t = arr[i]; arr[i] = arr[j]; arr[j] = t; }
        }
        int t = arr[low]; arr[low] = arr[j]; arr[j] = t;
        return j;
    }

    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int p = partition(arr, low, high);
            quickSort(arr, low, p - 1);
            quickSort(arr, p + 1, high);
        }
    }
}
```

#### Descending order (the video's assignment)
Flip the two comparisons in `partition`: move `i` while `arr[i] >= pivot`, move `j` while `arr[j] < pivot`. Larger elements then end up on the left.

#### Key Takeaways
- Partition is the heart of quick sort and also powers Quickselect (k-th smallest/largest in average O(n)).
- In the video a `<=` typed instead of `>=` caused a time-limit error — loop conditions in partition must be exact.

[↑ Contents](#contents) · [← Previous](#p64) · [Next →](#p66)

---

<a id="p66"></a>

### 6. Recursive Bubble Sort

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sorting › Algorithms | Core | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Implement bubble sort **recursively**.

```text
[5, 1, 4, 2, 8] -> [1, 2, 4, 5, 8]
```

#### Intuition
One pass of bubble sort over the first `n` elements pushes the largest of them to index `n − 1`. After that, the problem is "bubble-sort the first `n − 1` elements" — a smaller instance of the same problem → recursion.

#### Approach
```
bubble(arr, n):
    if n == 1: return
    didSwap = false
    for j in 0..n−2:
        if arr[j] > arr[j+1]: swap, didSwap = true
    if not didSwap: return          // already sorted
    bubble(arr, n − 1)
```

**Complexity:** Time O(n²) worst/average, O(n) best (sorted input, thanks to `didSwap`). Space O(n) recursion stack.

**C++**
```cpp
void bubbleRec(vector<int>& arr, int n) {
    if (n <= 1) return;
    bool didSwap = false;
    for (int j = 0; j <= n - 2; j++) {
        if (arr[j] > arr[j + 1]) {
            swap(arr[j], arr[j + 1]);
            didSwap = true;
        }
    }
    if (!didSwap) return;
    bubbleRec(arr, n - 1);
}
// call: bubbleRec(arr, arr.size());
```

**Java**
```java
class Solution {
    static void bubbleRec(int[] arr, int n) {
        if (n <= 1) return;
        boolean didSwap = false;
        for (int j = 0; j <= n - 2; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
                didSwap = true;
            }
        }
        if (!didSwap) return;
        bubbleRec(arr, n - 1);
    }
}
```

#### Key Takeaways
- An iterative outer loop can usually be replaced by a recursive call on a smaller size; the inner loop stays.

[↑ Contents](#contents) · [← Previous](#p65) · [Next →](#p67)

---

<a id="p67"></a>

### 7. Recursive Insertion Sort

| Topic | Difficulty | Plus | Links | Video |
|---|---|---|---|---|
| Sorting › Algorithms | Core | No | — | Not available |

> **No video available for this problem.** These notes were prepared independently, following the same format as the rest of the sheet.

#### Problem Statement
Implement insertion sort **recursively**.

```text
[5, 1, 4, 2, 8] -> [1, 2, 4, 5, 8]
```

#### Intuition
Insertion sort processes indices left to right, inserting `arr[i]` into the sorted prefix `[0..i−1]`. Make the outer loop a recursive call: `insertion(arr, i, n)` inserts `arr[i]` and then calls `insertion(arr, i + 1, n)`; stop when `i == n`.

#### Approach
```
insertion(arr, i, n):
    if i == n: return
    j = i
    while j > 0 and arr[j−1] > arr[j]: swap(arr[j−1], arr[j]); j--
    insertion(arr, i + 1, n)
```

**Complexity:** Time O(n²) worst/average, O(n) best. Space O(n) recursion stack.

**C++**
```cpp
void insertionRec(vector<int>& arr, int i, int n) {
    if (i == n) return;
    int j = i;
    while (j > 0 && arr[j - 1] > arr[j]) {
        swap(arr[j - 1], arr[j]);
        j--;
    }
    insertionRec(arr, i + 1, n);
}
// call: insertionRec(arr, 0, arr.size());
```

**Java**
```java
class Solution {
    static void insertionRec(int[] arr, int i, int n) {
        if (i == n) return;
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            int t = arr[j - 1]; arr[j - 1] = arr[j]; arr[j] = t;
            j--;
        }
        insertionRec(arr, i + 1, n);
    }
}
```

#### Key Takeaways
- Both recursive sorts are mainly recursion practice; the iterative versions are preferred in real code (no stack growth).

[↑ Contents](#contents) · [← Previous](#p66)

---
