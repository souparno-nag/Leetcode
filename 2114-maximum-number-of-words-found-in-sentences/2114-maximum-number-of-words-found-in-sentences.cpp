class Solution {
public:
    int mostWordsFound(vector<string>& sentences) {
        int max_count = 0;
        for (int i = 0; i < sentences.size(); i++) {
            int count = 0;
            for (char ch : sentences[i]) {
                if (ch == ' ') count++;
            }
            max_count = max(max_count, count);
        }
        return max_count + 1;
    }
};