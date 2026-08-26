class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (string word: strs) {
            int chars[26] = {0};
            for (char c: word) {
                chars[c-'a']++;
            }
            string key = "";
            for (int i = 0; i < 26; i++) {
                key += "#";
                key += to_string(chars[i]+'a');
            }
            map[key].push_back(word);
        }
        vector<vector<string>> result;
        for (auto it = map.begin(); it != map.end(); it++) {
            result.push_back(it->second);
        }
        return result;
    }
};