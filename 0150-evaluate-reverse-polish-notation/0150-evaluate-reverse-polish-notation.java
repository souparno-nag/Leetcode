class Solution {
    public int evalRPN(String[] tokens) {
        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < tokens.length; i++) {
            if (tokens[i].equals("+")) {
                int n1 = st.peek(); st.pop();
                int n2 =st.peek(); st.pop();
                st.push((n1+n2));
            } else if (tokens[i].equals("-")) {
                int n1 = st.peek(); st.pop();
                int n2 = st.peek(); st.pop();
                st.push((n2-n1));
            } else if (tokens[i].equals("*")) {
                int n1 = st.peek(); st.pop();
                int n2 = st.peek(); st.pop();
                st.push((n1*n2));
            } else if (tokens[i].equals("/")) {
                int n1 = st.peek(); st.pop();
                int n2 = st.peek(); st.pop();
                st.push((n2/n1));
            } else {
                st.push(Integer.parseInt(tokens[i]));
            }
        }
        return st.peek();
    }
}