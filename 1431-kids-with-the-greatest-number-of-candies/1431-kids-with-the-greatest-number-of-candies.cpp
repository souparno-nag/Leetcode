class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int n = candies.size();
        vector<bool> result(n);
        int highest_candies = -1;
        for (int i = 0; i < n; i++) highest_candies = max(highest_candies, candies[i]);
        for (int i = 0; i < n; i++) {
            result[i] = (candies[i] + extraCandies >= highest_candies) ? true : false;
        }
        return result;
    }
};