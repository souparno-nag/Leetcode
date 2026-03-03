class Solution {
    int max (int a, int b) {
        return (a >= b) ? a : b;
    }
    public int longestValidParentheses(String s) {
        Stack<Integer> st = new Stack<>();
        
        st.push(-1);
        int maxLen = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i);
                } else {
                    maxLen = max(maxLen, i - st.peek());
                }
            }
        }

        return maxLen;
    }
}