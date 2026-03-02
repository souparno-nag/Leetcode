class Solution {
    void generateAllWellFormedParenthesis (String current, int open, int close, int n, List<String> result) {
        if (current.length() == 2*n) {
            result.add(current);
            return;
        }
        if (open < n) {
            generateAllWellFormedParenthesis(current + "(", open + 1, close, n, result);
        }
        if (close < open) {
            generateAllWellFormedParenthesis(current + ")", open, close + 1, n, result);
        }
        return;
    }
    public List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();
        String current = "";
        generateAllWellFormedParenthesis(current, 0, 0, n, result);
        return result;
    }
}