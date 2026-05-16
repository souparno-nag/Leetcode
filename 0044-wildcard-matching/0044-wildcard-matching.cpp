class Solution {
public:
    bool isMatch(string s, string p) {
        int n = p.length(), m = s.length();
        vector<bool> prev(m+1, false), curr(m+1, false);
        // define base case
        prev[0] = true;
        for (int j = 1; j <= m; j++) prev[j] = false;
        // build the table
        for (int i = 1; i <= n; i++) {
            curr[0] = false;
            if (p[i-1] == '*') curr[0] = prev[0];
            for (int j = 1; j <= m; j++) {
                if (p[i-1] == s[j-1] || p[i-1] == '?') curr[j] = prev[j-1];
                else if (p[i-1] == '*') {
                    curr[j] = prev[j] || curr[j-1];
                } else {
                    curr[j] = false;
                }
            }
            prev = curr;
        }
        return prev[m];
    }
};