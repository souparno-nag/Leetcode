class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (string word: strs) {
            string sort_word = word;
            sort(sort_word.begin(), sort_word.end());
            map[sort_word].push_back(word);
        }
        vector<vector<string>> result;
        for (auto it = map.begin(); it != map.end(); it++) {
            result.push_back(it->second);
        }
        return result;
    }
};