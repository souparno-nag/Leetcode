class Solution {
    public String[] phone = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    public void FindLetterCombinations (String current, int i, int n, List<String> result, String digits) {
        if (i == n) {
            result.add(current);
            return;
        }
        char digit = digits.charAt(i);
        String alpha = phone[digit - '0' - 2];
        for (char ch : alpha.toCharArray()) {
            current += ch;
            FindLetterCombinations(current, i+1, n, result, digits);
            current = current.substring(0, current.length() - 1);
        }
    }
    public List<String> letterCombinations(String digits) {
        List<String> result = new ArrayList<>();;
        String current = "";
        int n = digits.length();
        FindLetterCombinations(current, 0, n, result, digits);
        return result;
    }
}