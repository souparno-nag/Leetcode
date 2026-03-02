class Solution {
public:
    void findAllUniqueCombinations (vector<int> current, int currentSum, int targetSum, vector<vector<int>>& result, vector<int>& candidates, int n, int start) {
        if (currentSum == targetSum) {
            result.push_back(current);
            return;
        }
        for (int i = start; i < n; i++) {
            if (i > start && candidates[i] == candidates[i-1]) continue;
            if (candidates[i] <= targetSum - currentSum) {
                current.push_back(candidates[i]);
                findAllUniqueCombinations(current, currentSum + candidates[i], targetSum, result, candidates, n, i+1);
                current.pop_back();
            }
        }
        return;
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        int n = candidates.size();
        vector<vector<int>> result;
        sort(candidates.begin(), candidates.end());
        vector<int> curr;
        findAllUniqueCombinations(curr, 0, target, result, candidates, n, 0);
        return result;
    }
};