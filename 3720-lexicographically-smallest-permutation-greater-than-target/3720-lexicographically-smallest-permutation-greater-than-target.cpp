class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        int count[26] = {0};
        for (char ch: s) count[ch-'a']++;
        string res = "";
        int k = 0;
        while (k < n && count[target[k]-'a'] > 0) {
            count[target[k]-'a']--;
            res += target[k++];
        }
        if (k == n) {
            res.pop_back();
            count[target[--k]-'a']++;
        }
        while (k >= 0) {
            for (int c = target[k]-'a'+1; c < 26; c++) {
                if (!count[c]) continue;
                count[c]--;
                res += char(c+'a');
                for (int d = 0; d < 26; d++)
                    res.append(count[d], char('a'+d));
                return res;
            }
            k--;
            if (k >= 0) {
                count[target[k]-'a']++;
                res.pop_back();
            }
        }
        return "";
    }
};