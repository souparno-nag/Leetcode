class Solution {
public:
    int findMinDistance(string w1, string w2, int i, int j, vector<vector<int>>& dp) {
        // base case
        if (j < 0) return i+1;
        if (i < 0) return j+1;
        // check dp table
        if (dp[i][j] != -1) return dp[i][j];
        // define all possibilities
        // if characters match
        if (w1[i] == w2[j]) return dp[i][j] = findMinDistance(w1, w2, i-1, j-1, dp);
        // if characters do not match
        int insertion = 1 + findMinDistance(w1, w2, i, j-1, dp);
        int deletion = 1 + findMinDistance(w1, w2, i-1, j, dp);
        int replacement = 1 + findMinDistance(w1, w2, i-1, j-1, dp);
        return dp[i][j] = min(replacement, min(insertion, deletion));
    }
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return findMinDistance(word1, word2, n-1, m-1, dp);
    }
};