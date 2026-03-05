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
    void preorder(TreeNode* root, vector<int>& arr) {
        if (root == NULL) return;
        arr.push_back(root -> val);
        preorder(root -> left, arr);
        preorder(root -> right, arr);
    }
    void flatten(TreeNode* root) {
        vector<int> arr;
        preorder(root, arr);
        int n = arr.size();
        if (n == 0) {
            return;
        }
        TreeNode* temp = root;
        temp -> val = arr[0];
        temp -> left = nullptr;
        for (int i = 1; i < n; i++) {
            temp -> right = new TreeNode(arr[i]);
            temp = temp -> right;
        }
    }
};