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
public:
    int maxPathDown(TreeNode* node, int* maximum) {
        if (node == NULL) return 0;
        int leftSum = max(0, maxPathDown(node -> left, maximum));
        int rightSum = max(0, maxPathDown(node -> right, maximum));
        *maximum = max(*maximum, leftSum + rightSum + node -> val);
        return max(leftSum, rightSum) + node -> val;
    }
    int maxPathSum(TreeNode* root) {
        int maximum = INT_MIN;
        maxPathDown(root, &maximum);
        return maximum;
    }
};