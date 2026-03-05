class Solution {
public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> result;
        for (int i = 0; i < words.size(); i++) {
            bool check = false;
            for (char ch : words[i]) {
                if (ch == x) {
                    check = true;
                    break;
                }
            }
            if (check) result.push_back(i);
        }
        return result;
    }
};