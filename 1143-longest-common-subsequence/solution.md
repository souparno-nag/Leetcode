## Memoization

```cpp
class Solution {
public:
    int lcs(string t1, string t2, int i1, int i2, vector<vector<int>>& dp) {
        // base case
        if (i1 < 0 || i2 < 0) return 0;
        // check dp
        if (dp[i1][i2] != -1) return dp[i1][i2];
        // define all possibilities
        if (t1[i1] == t2[i2]) {
            return dp[i1][i2] = 1 + lcs(t1, t2, i1-1, i2-1, dp);
        } else {
            return dp[i1][i2] = max(lcs(t1, t2, i1-1, i2, dp), lcs(t1, t2, i1, i2-1, dp));
        }
    }
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.length(), n2 = text2.length();
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, -1));
        return lcs(text1, text2, n1-1, n2-1, dp);
    }
};
```

## Tabulation

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.length(), n2 = text2.length();
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, 0));
        // build the dp
        for (int i = 1; i<= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (text1[i-1] == text2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[n1][n2];
    }
};
```

## Space Optimization

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.length(), n2 = text2.length();
        vector<int> dp(n2+1, 0), temp(n2+1, 0);
        // base case
        for (int i = 0; i <= n1; i++) dp[0] = 0;
        // build the dp
        for (int i = 1; i<= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (text1[i-1] == text2[j-1]) temp[j] = 1 + dp[j-1];
                else temp[j] = max(dp[j], temp[j-1]);
            }
            dp = temp;
        }
        return dp[n2];
    }
};
```

## Print LCS

```cpp
class Solution {
  public:
    string printLCS(string &s1, string &s2) {
        int n1 = s1.length(), n2 = s2.length();
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, -1));
        for (int i = 0; i <= n1; i++) dp[i][0] = 0;
        for (int j = 0; j <= n2; j++) dp[0][j] = 0;
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        int i = n1, j = n2;
        string res = "";
        while (i > 0 && j > 0) {
            if (s1[i] == s2[j]) {
                res = s1[i] + res;
            } else if (dp[i-1][j] > dp[i][j-1]) i--;
            else j--;
        }
        return res;
    }
};
```
