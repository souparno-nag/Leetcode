# Minimum Path Sum

## Understanding the Problem

A MxN grid is provided where each cell represents the cost of going through the cell.
Objective: Calculating minimum cost for moving from (0, 0) to (M-1, N-1)

## Recursion Approach

Breaking the recursion approach down to the 3 main steps

1. Define the indexes and the base case
   Here, the indexes are i (indicates row) and j (indicates column)
   Base Case:
   - When i = 0 and j = 0, cost is grid[i][j]
   - When i < 0 or j < 0, cost is +infinity (invalid steps)
2. Perform operations on the values represented by the indexes
   From a point (i, j), the path can come from left or above
   - up = f(i - 1, j) + grid[i][j]
   - left = f(i, j - 1) + grid[i][j]
3. Calculate final output
   f(i, j) = min(up, left)

### Pseudocode

```markdown
f(i, j, grid) {
  if (i = 0 and j = 0) return grid[i][j]
  if (i < 0 or j < 0) return +infinity
  up = f(i - 1, j) + grid[i][j]
  left = f(i, j - 1) + grid[i][j]
  return min(up, left)
}
```

Time Complexity: O(2^(M+N)-1)
Space Complexity: O((M-1)+(N-1)) {recursive stack from path length}

## Top Down Approach (Memoization)

Initialize array: dp[i: 0 ... M-1][j: 0 ... N-1] to -1

### Pseudocode

```markdown
f(i, j, grid, dp) {
  if (i = 0 and j = 0) return dp[i][j] = grid[i][j]
  if (i < 0 or j < 0) return +infinity
  if (dp[i][j] != -1) return dp[i][j]
  up = f(i - 1, j) + grid[i][j]
  left = f(i, j - 1) + grid[i][j]
  return dp[i][j] = min(up, left)
}
```

Time Complexity: O(MxN)
Space Complexity: O((M-1)+(N-1)) {recursive stack from path length} + O(MxN) {dp}

## Bottom Up Approach (Tabulation)

Initialize array: dp[i: 0 ... M-1][j: 0 ... N-1] to -1

### Pseudocode

```markdown
f(grid) {
  Initialize array: dp[i: 0 ... M-1][j: 0 ... N-1] to -1
  for (i -> 0 to M-1) {
    for (j -> 0 to N-1) {
      if (i = 0 and j = 0) dp[i][j] = grid[i][j]
      else {
        up = dp[i-1][j] + grid[i][j]
        left = dp[i][j-1] + grid[i][j]
        dp[i][j] = min(up, left)
      }
    }
  }
  return dp[M-1][N-1]
}
```

Time Complexity: O(MxN)
Space Complexity: O(MxN) {dp}

## Space Optimization

Initialize array: dp[j: 0 ... N-1] in order to track last row and temp[j: 0 ... N-1] in order to track last column

### Pseudocode

```markdown
f(grid) {
  Initialize array: dp[j: 0 ... N-1] to -1
  for (i -> 0 to M-1) {
    Initialize temp[j: 0 ... N-1]
    for (j -> 0 to N-1) {
      if (i = 0 and j = 0) temp[j] = grid[i][j]
      else {
        up = dp[j] + grid[i][j]
        left = temp[j-1] + grid[i][j]
        temp[i][j] = min(up, left)
      }
    }
    dp = temp
  }
  return dp[N-1]
}
```

Time Complexity: O(MxN)
Space Complexity: O(N) {dp}
