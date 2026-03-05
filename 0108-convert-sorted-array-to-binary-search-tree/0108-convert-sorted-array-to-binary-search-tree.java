/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    TreeNode sortedArrayToBSTRec(int left, int right, int[] nums) {
        if (left > right) return null;
        int mid = left + (right - left)/2;
        TreeNode root = new TreeNode(nums[mid]);
        root.left = sortedArrayToBSTRec(left, mid-1, nums);
        root.right = sortedArrayToBSTRec(mid+1, right, nums);
        return root;
    }
    public TreeNode sortedArrayToBST(int[] nums) {
        int n = nums.length;
        return sortedArrayToBSTRec(0, n-1, nums);
    }
}