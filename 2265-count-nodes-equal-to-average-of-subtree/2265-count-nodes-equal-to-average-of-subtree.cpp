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
    pair<int, int> subTree(TreeNode* node, int& count) {
        if (node == nullptr) return {0, 0};
        auto [leftSum, leftCount] = subTree(node->left, count);
        auto [rightSum, rightCount] = subTree(node->right, count);
        int sum = leftSum + rightSum + node->val;
        int nodeCount = leftCount + rightCount + 1;
        if (sum/nodeCount == node->val) count++;
        return {sum, nodeCount};
    }
public:
    int averageOfSubtree(TreeNode* root) {
        int count = 0;
        subTree(root, count);
        return count;
    }
};