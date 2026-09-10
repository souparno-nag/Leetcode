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
    vector<int> subTree(TreeNode* node, int& count) {
        if (node == NULL) return {0, 0};
        vector<int> leftSubTree = subTree(node->left, count);
        vector<int> rightSubTree = subTree(node->right, count);
        int sum = leftSubTree[0] + rightSubTree[0] + node->val;
        int nodeCount = leftSubTree[1] + rightSubTree[1] + 1;
        int avg = sum/nodeCount;
        if (avg == node->val) count++;
        return {sum, nodeCount};
    }
public:
    int averageOfSubtree(TreeNode* root) {
        int count = 0;
        subTree(root, count);
        return count;
    }
};