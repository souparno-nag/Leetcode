class Solution {
public:
    int lcs(string s1, string s2) {
        int n1 = s1.length(), n2 = s2.length();
        vector<int> prev(n2+1, 0), curr(n2+1, 0);
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (s1[i-1] == s2[j-1]) curr[j] = 1 + prev[j-1];
                else curr[j] = max(curr[j-1], prev[j]);
            }
            prev = curr;
        }
        return prev[n2];
    }
    int minDistance(string word1, string word2) {
        return word1.length() + word2.length() - 2*lcs(word1, word2);
    }
};