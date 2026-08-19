/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int countGoodNodes(TreeNode* node, int prev_max) {
        if (node == NULL) return 0;
        if (node->val >= prev_max) {
            prev_max = node->val;
            return 1 + countGoodNodes(node->left, prev_max) + countGoodNodes(node->right, prev_max);
        }
        return countGoodNodes(node->left, prev_max) + countGoodNodes(node->right, prev_max);
    }
public:
    int goodNodes(TreeNode* root) {
        return countGoodNodes(root, -1e9);
    }
};