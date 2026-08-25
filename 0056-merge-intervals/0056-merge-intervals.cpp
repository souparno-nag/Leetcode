class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> result;
        for (int i = 0; i < n; i++) {
            int start = intervals[i][0], end = intervals[i][1];
            if (!result.empty() && end <= result.back()[1]) continue;
            for (int j = i+1; j < n; j++) {
                if (end >= intervals[j][0]) {
                    end = max(end, intervals[j][1]);
                } else {
                    break;
                }
            }
            result.push_back({start, end});
        }
        return result;
    }
};