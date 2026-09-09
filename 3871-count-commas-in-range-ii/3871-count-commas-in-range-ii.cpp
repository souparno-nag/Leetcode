class Solution {
public:
    long long countCommas(long long n) {
        if (n == 1e15) {
            return 1*5 + 4*(1e15 - 1e12) + 3*(1e12 - 1e9) + 2*(1e9 - 1e6) + 1*(1e6 - 1e3);
        } else if (n >= 1e12) {
            return 4*(n - 1e12 + 1) + 3*(1e12 - 1e9) + 2*(1e9 - 1e6) + 1*(1e6 - 1e3);
        } else if (n >= 1e9) {
            return 3*(n - 1e9 + 1) + 2*(1e9 - 1e6) + 1*(1e6 - 1e3);
        } else if (n >= 1e6) {
            return 2*(n - 1e6 + 1) + 1*(1e6 - 1e3);
        } else if (n >= 1e3) {
            return 1*(n - 1e3 + 1);
        }
        return 0;
    }
};