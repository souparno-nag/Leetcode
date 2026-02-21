# Minimum Falling Path Sum

## Understanding the Problem

A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
Given, an n x n array of integers matrix, the objective is to return the minimum sum of any falling path through matrix.

## Recursion Approach

1. Express the problem in terms of (i, j) and define base case
2. Explore all paths and their costs
3. Find the path with the lowest cost

### Pseudocode

```markdown
f(i, j, matrix) {
  if (j < 0 or j >= m) return +infinity
  if (i == 0) return matrix[i][j]
  straightUp = f(i-1, j) + matrix[i][j]
  leftDiagonal = f(i-1, j-1) + matrix[i][j]
  rightDiagonal = f(i-1, j+1) + matrix[i][j]
  return min(straightUp, leftDiagonal, rightDiagonal)
}
main {
  minPath = +infinity
  for (j -> 0 to n-1) {
    minPath = min(minPath, f(n-1, j, matrix)
  }
  return minPath
}
```

Time Complexity = O(Nx(3^N)) {exponential}
Space Complexity = O(M) {recursive stack}

## Top Down Approach (Memoization)

Use an MxN array dp

### Pseudocode

```markdown
f(i, j, matrix, dp) {
  if (j < 0 or j >= m) return +infinity
  if (i == 0) return dp[i][j] = matrix[i][j]
  straightUp = f(i-1, j) + matrix[i][j]
  leftDiagonal = f(i-1, j-1) + matrix[i][j]
  rightDiagonal = f(i-1, j+1) + matrix[i][j]
  return dp[i][j] = min(straightUp, leftDiagonal, rightDiagonal)
}
```

Time Complexity = O(Mx(N^2)) {exponential}
Space Complexity = O(MxN) {dp} + O(M) {recursive stack}
