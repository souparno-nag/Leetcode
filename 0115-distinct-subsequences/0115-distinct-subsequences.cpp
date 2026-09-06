class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.length(), m = t.length();
        vector<uint32_t> curr(m+1, 0);
        // base cases
        curr[0] = 1;
        // build the dp table
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s[i-1] == t[j-1]) {
                    curr[j] = curr[j-1] + curr[j];
                }
            }
        }
        return (int) curr[m];
    }
};