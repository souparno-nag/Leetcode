class Solution {
    String flipBinaryString(String binaryString) {
        return binaryString.replace('0', 'x').replace('1', '0').replace('x', '1');
    }
    String reverseBinaryString(String binaryString) {
        StringBuilder sb = new StringBuilder(binaryString);
        return sb.reverse().toString();
    }
    public char findKthBit(int n, int k) {
        String S = "0";
        for (int i = 1; i < n; i++) {
            S = S + "1" + reverseBinaryString(flipBinaryString(S));
        }
        return S.charAt(k-1);
    }
}