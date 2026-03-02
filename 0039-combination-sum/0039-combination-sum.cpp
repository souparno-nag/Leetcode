class Solution {
public:
    void findAllUniqueCombinations (vector<int> current, int currentSum, int start, int targetSum, vector<vector<int>>& result, vector<int>& candidates, int n) {
        if (currentSum == targetSum) {
            result.push_back(current);
            return;
        }
        for (int i = start; i < n; i++) {
            if (candidates[i] <= targetSum - currentSum) {
                current.push_back(candidates[i]);
                currentSum += candidates[i];
                findAllUniqueCombinations(current, currentSum, i, targetSum, result, candidates, n);
                current.pop_back();
                currentSum -= candidates[i];
                }
        }
        return;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int n = candidates.size();
        vector<vector<int>> result;
        vector<int> current;
        findAllUniqueCombinations(current, 0, 0, target, result, candidates, n);
        return result;
    }
};