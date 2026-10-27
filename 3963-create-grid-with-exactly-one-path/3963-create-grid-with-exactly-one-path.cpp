class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> result(m, "");
        for (int i = 0; i < m; i++) {
            if (i == 0) {
                for (int j = 0; j < n; j++) result[i] += '.';
            } else {
                for (int j = 0; j < n-1; j++) result[i] += '#';
                result[i] += '.';
            }
        }
        return result;
    }
};