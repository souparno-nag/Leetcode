class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int len = s.length();
        int i = 0, j = 0, count = 0;
        string result = "";
        while (j < len) {
            count += (s[j++] == '1') ? 1 : 0;
            while (count >= k) {
                string candidate = s.substr(i, j-i);
                if (result.empty() ||
                    candidate.length() < result.length() ||
                    candidate.length() == result.length() && candidate < result) {
                        result = candidate;
                }
                count -= (s[i++] == '1') ? 1 : 0;
            }
        }
        return result;
    }
};