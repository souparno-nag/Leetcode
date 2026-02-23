# Partition a Set into Two Subsets of Equal Sum

## Understanding the problem

Given: an array of integers, num[]
The task is to check if the array can be partitioned into 2 subsequences with equal sum

## Solving the problem

Let us assume the sum of all the numbers in the array num[] is **totalSum**.
If totalSum is odd, the answer is false.
Thus the sum for each subsequence will be **targetSum = totalSum/2**.
The next step will be to check the existance of any subsequence whose sum is targetSum.
So, it is a modification of the **subset sum problem**.

## Space Optimized Tabulation Approach

### Pseudocode

```markdown
main(num[])
  totalSum = sum(num[])
  if (totalSum is odd) return false
  targetSum = totalSum/2
  return f(num[], targetSum)
}
f(num[], targetSum) {
  N = length(num[])
  Initialize an array: dp[target: 0 ... targetSum]
  // define base cases
  dp[0] = true
  if (num[arr[0]] < targetSum) dp[arr[0]] = true
  // build the nested loops
  for (ind -> 1 to N-1) {
      Initialize an array: temp[target: 0 ... targetSum]
      temp[0] = true
      for (target -> 0 to targetSum) {
        notTake = dp[target]
        take = dp[target-num[ind]] if (num[ind] < target) else false
        temp[target] = take || notTake
      }
      dp = temp
  }
  return dp[targetSum]
```

Time Complexity: O(NxtargetSum)
Space Complexity: O(targetSum)
