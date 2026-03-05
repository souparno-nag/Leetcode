class Solution {
public:
    bool checkPalindrome(string word) {
        int n = word.length();
        for (int i = 0; i < n/2; i++) {
            if (word[i] != word[n-i-1]) return false;
        }
        return true;
    }
    string firstPalindrome(vector<string>& words) {
        int n = words.size();
        for (int i = 0; i < n; i++) {
            if (checkPalindrome(words[i])) return words[i];
        }
        return "";
    }
};