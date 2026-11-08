class Solution {
    long long totalHours(vector<int>& piles, int k) {
        long long hours = 0;
        for (int pile : piles) hours += (pile+k-1)/k;
        return hours;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1, high = *max_element(piles.begin(), piles.end());
        while (low <= high) {
            int mid = (low+high)/2;
            if (totalHours(piles, mid) <= h) high = mid-1;
            else low = mid+1;
        }
        return low;
    }
};