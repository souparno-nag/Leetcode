class Solution {
    public int calculate(String s) {
        Stack<Integer> st = new Stack<>();
        int ans = 0, sign = 1;
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            if (Character.isDigit(ch)) {
                int x = 0;
                while ((i < s.length()) && Character.isDigit(s.charAt(i))) {
                    x = x * 10 + (int)((s.charAt(i++)-'0'));
                }
                ans += sign * x;
                i -= 1;
            } else if (ch == '+') {
                sign = 1;
            } else if (ch == '-') {
                sign = -1;
            } else if (ch == '(') {
                st.push(ans);
                st.push(sign);
                ans = 0;
                sign = 1;
            } else if (ch == ')') {
                int prev_sign = st.peek(); st.pop();
                int prev_ans = st.peek(); st.pop();
                ans = prev_sign * ans + prev_ans;
            } else if (Character.isSpace(ch)) {
                continue;
            }
        }
        return ans;
    }
}