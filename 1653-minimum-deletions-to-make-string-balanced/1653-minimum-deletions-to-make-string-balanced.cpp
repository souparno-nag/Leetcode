class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.length();
        vector<int> count_a_right(n+1, 0);
        for (int i = n-1; i >= 0; i--) {
            count_a_right[i] = count_a_right[i+1] + (s[i] == 'a' ? 1 : 0);
        }
        int count_b_left = 0, min_deletions = n;
        for (int i = -1; i < n; i++) {
            if (i >= 0) count_b_left += (s[i] == 'b' ? 1 : 0);
            min_deletions = min(min_deletions, count_b_left + count_a_right[i+1]);
        }
        return min_deletions;
    }
};