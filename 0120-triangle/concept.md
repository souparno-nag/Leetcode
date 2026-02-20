# Triangle

## Understanding the problem

Given a triangle array, the objective is to obtain the minimum path sum from top to bottom.
Also, from a point (i, j), one can only move to (i+1, j) or (i+1, j+1).

## Greedy Approach

Rejected due to lack of uniformity.

## Recursion Approach

The problem is again divided into 3 parts:

1. Represent the problem in terms of indexes (i, j)
2. Explore all the paths
   In this case, we shall traverse from the (n-1)th row to the 0th row.
3. Find the minimum cost from all the paths.

### Pseudocode

```markdown
f(i, j, triangle) {
  if (i = n-1) return triangle[i][j]
  down = f(i+1, j, triangle)
  diagonal = f(i+1, j+1, triangle)
  return min(down, diagonal) + triangle[i][j]
}
```

Time Complexity = O(2^2n -1)
Space Complexity = O(2N-2)

## Top Down Dynamic Approach (Memoization)

Initialize an array to store the repeating subproblems: dp[i: 0 ... n-1][j: 0 ... n-1]
dp[i][j] represents the min cost of path from (i, j) to the bottom.

### Pseudocode

```markdown
f(i, j, triangle, dp) {
  if (i = n-1) return dp[i][j] = triangle[i][j]
  if (dp[i][j] != -1) return dp[i][j]
  down = f(i+1, j, triangle)
  diagonal = f(i+1, j+1, triangle)
  return dp[i][j] = min(down, diagonal) + triangle[i][j]
}
```

Time Complexity = O(N^2)
Space Complexity = O(N^2) {dp} + O(2N-2) {recursive stack space}

## Bottom Up Dynamic Approach (Tabulation)

Initialize an array to store the repeating subproblems: dp[i: 0 ... n-1][j: 0 ... n-1]
dp[i][j] represents the min cost of path from (i, j) to the bottom.
Base Case:
When i == n-1, dp[i][j] = triangle[i][j]
Now traverse from i = (n-2) to 0 and j = i to 0, filling in the points.
dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j]

### Pseudocode

```markdown
f(triangle) {
  n = length(triangle)
  Initialize dp[i: 0 ... n-1][j: 0 ... n-1]
  for (j -> 0 to n-1) dp[n-1][j] = triangle[n-1][j]
  for (i -> n-2 to 0) {
    for (j -> i to 0) {
      down = dp[i+1][j]
      diagonal = dp[i+1][j+1]
      dp[i][j] = min(down, diagonal) + triangle[i][j]
    }
  }
  return dp[0][0]
```

Time Complexity = O(N^2)
Space Complexity = O(N^2) {dp}

## Space Optimization

Instead of an NxN array, an array of size N is initialized

### Pseudocode

```markdown
f(triangle) {
  n = length(triangle)
  Initialize dp[j: 0 ... n-1]
  for (j -> 0 to n-1) dp[j] = triangle[n-1][j]
  for (i -> n-2 to 0) {
    Initialize temp[j: 0 ... n-1]
    for (j -> i to 0) {
      down = dp[j]
      diagonal = dp[j+1]
      temp[j] = min(down, diagonal) + triangle[i][j]
    }
    dp = temp
  }
  return dp[0]
```

Time Complexity = O(N^2)
Space Complexity = O(N) {dp}
