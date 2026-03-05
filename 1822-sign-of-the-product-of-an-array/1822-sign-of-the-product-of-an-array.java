class Solution {
    public int arraySign(int[] nums) {
        int count_neg = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == 0) return 0;
            if (nums[i] < 1) count_neg++;
        } 
        return (count_neg % 2 == 0) ? 1 : -1;
    }
}