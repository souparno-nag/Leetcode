# Unique Paths

## Understanding the problem

There is a MxN matrix. A robot is located at the top left corner (0,0) and has to reach the bottom right corner (M-1, N-1).
Given: M, N
To find: Number of possible paths from (0,0) to (M-1, N-1)

## Recursive approach

Since the problem asks for all possible paths, we are approaching it using recursion.
The 3 steps in every recursive solution are:

1. Define the problems in terms of indexes (here i, j or row, column).
2. Explore and perform operations using the values represented by those indexes.
3. Sum up all the ways / Find max/min (depending on the problem).

Let us consider the path as going from (M-1, N-1) to (0,0).
Here, since the task is to determine and count valid paths, a valid path should return 1 and aninvalid path should return 0.
Base case:

- if i = 0 and j = 0 return 1 (since path is valid)
- if i < 0 or j < 0 return 0 (since path is not valid)

After that, consider operations on i, j.
From any grid (i, j) one can go up or left. The left grid consists of all possible paths in that direction. The up grid consists of all possible paths in that direction.
The value of point (i, j) is the sum of left and up.

### Pseudocode

```recursion
f(i, j) {
  if (i == 0 and j == 0) return 1
  if (i < 0 or j < 0) return 0
  up = f(i - 1, j)
  left = f(i, j - 1)
  return up + left
}
```

Time Complexity: O(2^(M+N) - 1)
Space Complexity: O((M-1)x(N-1)) { recursion stack }

## Top Down Approach (Memoization)

Initialize an array: dp[i: 0 ... M][j: 0 ... N] with -1

### Pseudocode

```recursion
f(i, j, dp) {
  if (i == 0 and j == 0) return dp[i][j] = 1
  if (i < 0 or j < 0) return 0
  if (dp[i][j] != -1) return dp[i][j]
  up = f(i - 1, j)
  left = f(i, j - 1)
  return dp[i][j] = up + left
}
```

Time Complexity: O(MxN)
Space Complexity: O((M-1)x(N-1)) { recursion stack } + O(MxN) { dp }

## Bottom Up Approach (Tabulation)

Initialize an array: dp[i: 0 ... M][j: 0 ... N]

### Pseudocode

```recursion
f (m, n) {
  Initialize dp[i: 0 ... M][j: 0 ... N]
  for (i -> 0 ... M) {
    for (j -> 0 ... N) {
      if (i = 0 and j = 0) dp[i][j] = 1
      else {
        up = dp[i - 1][j]
        left = dp[i][j - 1]
        dp[i, j] = up + left
      }
    }
  }
  return dp[m-1][n-1]
} 
```

Time Complexity: O(MxN)
Space Complexity: O(MxN) { dp }

## Space Optimization

Here, the fundamental dp operation is: dp[i, j] = dp[i - 1, j] + dp[i, j - 1]
Thus, the value of (i, j) depends on the previous row (i-1) and the previous column (j-1).
**Whenever the value of dp relies on last row and/or last column, there can always be space optimization.**

So, instead of maintaining a MxN array, create an array dp[0 ... N] in order to store previous row. Also, within the loop, create a temp array to obtain the value from previous column.

### Pseudocode

```markdown
f (m, n) {
  Initialize dp[j: 0 ... N]
  for (i -> 0 ... M) {
    Initialize array temp[j: 0 ... N]
    for (j -> 0 ... N) {
      if (i = 0 and j = 0) temp[j] = 1
      else {
        up = dp[j]
        left = temp[j - 1]
        temp[j] = up + left
      }
    }
    dp = temp
  }
  return dp[n-1]
} 
```

Time Complexity: O(MxN)
Space Complexity: O(N) { dp }
