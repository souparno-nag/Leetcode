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
    void dfs_recursive(TreeNode* root, int curr, int* sum) {
        if (root == nullptr) return;
        curr = curr * 10 + root -> val;
        if (root -> left == nullptr && root -> right == nullptr) *sum += curr;
        if (root -> left != nullptr) dfs_recursive(root -> left, curr, sum);
        if (root -> right != nullptr) dfs_recursive(root -> right, curr, sum);
    }
    int sumNumbers(TreeNode* root) {
        vector<int> arr;
        int sum = 0;
        dfs_recursive(root , 0, &sum);
        return sum;
    }
};