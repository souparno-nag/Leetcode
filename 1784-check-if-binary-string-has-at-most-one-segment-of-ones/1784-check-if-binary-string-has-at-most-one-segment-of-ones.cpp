class Solution {
public:
    bool checkOnesSegment(string s) {
        int count_segment = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '1') {
                count_segment++;
                while (s[i] == '1') i++;
            }
            if (count_segment > 1) break;
        }
        return (count_segment <= 1);
    }
};