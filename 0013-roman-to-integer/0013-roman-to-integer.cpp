class Solution {
public:
    int romanToInt(string s) {
        int n = s.length();
        unordered_map<char, int> map;
        // map individual characters to value
        map.insert({'I', 1});
        map.insert({'V', 5});
        map.insert({'X', 10});
        map.insert({'L', 50});
        map.insert({'C', 100});
        map.insert({'D', 500});
        map.insert({'M', 1000});
        // calculate the value
        int num = map[s[n-1]], prev = map[s[n-1]];
        for (int i = n-2; i >= 0; i--) {
            int curr = map[s[i]];
            if (curr < prev) {
                num -= curr;
            } else {
                num += curr;
            }
            prev = curr;
        }
        return num;
    }
};