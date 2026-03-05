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
    int kthSmallestRecursive(TreeNode root, int[] count, int k) {
        if (root == null) return -1;
        int left = kthSmallestRecursive(root.left, count, k);
        if (left != -1) return left;
        count[0]++;
        if (count[0] == k) return root.val;
        int right = kthSmallestRecursive(root.right, count, k);
        return right;
    }
    public int kthSmallest(TreeNode root, int k) {
        int[] count = new int[1];
        return kthSmallestRecursive(root, count, k);
    }
}