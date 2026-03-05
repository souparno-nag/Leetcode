/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */

class Solution {
    TreeNode LCA (TreeNode root, int p, int q) {
        if (root == null) return null;
        if (root.val > p && root.val > q) return LCA(root.left, p, q);
        if (root.val < p && root.val < q) return LCA(root.right, p, q);
        return root;
    }
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        return LCA(root, p.val, q.val);
    }
}