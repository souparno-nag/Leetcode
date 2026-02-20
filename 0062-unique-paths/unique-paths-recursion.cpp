class Solution {
public:
    int countUniquePaths(int i, int j) {
        if (i == 0 && j == 0) return 1;
        if (i < 0 || j < 0) return 0;
        int up = countUniquePaths(i - 1, j);
        int left = countUniquePaths(i, j - 1);
        return up + left;
    }
    int uniquePaths(int m, int n) {
        return countUniquePaths(m - 1, n - 1);
    }
};
// Time Complexity = 2^(M+N)-1
// Space Complexity = O((M-1)*(N-1)) {due to recursion stack space}
