class Solution {
    bool possible(vector<int>& bloomDay, int day, int m, int k) {
        int count = 0, bouquets = 0;
        for (int b : bloomDay) {
            if (b <= day) count++;
            else {
                bouquets += count/k;
                count = 0;
            }
        }
        bouquets += count/k;
        return bouquets >= m;
    }
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if ((long long)m*k > bloomDay.size()) return -1;
        int low = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());
        while (low <= high) {
            int mid = (low+high)/2;
            if (possible(bloomDay, mid, m, k)) high = mid-1;
            else low = mid+1;
        }
        return low;
    }
};