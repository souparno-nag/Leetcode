class Solution {
    public String longestPalindrome(String s) {
        StringBuilder sb = new StringBuilder();
        sb.append("^");
        for (int i = 0; i < s.length(); i++) sb.append("#").append(s.charAt(i));
        sb.append("#$");
        String str = sb.toString();

        int n = str.length();
        int[] lps = new int[n];
        int mid = 0, r = 0;

        int index = 0, max = 0;
        for (int i = 1; i < n-1; i++) {
            if (i < r) {
                int mirror = mid - (i - mid);
                lps[i] = Math.min(lps[mirror], r - i);
            }
            while (str.charAt(i + lps[i] + 1) == str.charAt(i - (lps[i] + 1))) lps[i]++;
            if (i + lps[i] > r) {
                mid = i;
                r = i + lps[i];
            }
            if (lps[i] > max) {
                max = lps[i];
                index = i;
            }
        }
        
        int start = (index - max) / 2;
        return s.substring(start, start + max);
    }
}