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
private:
    void preTraversal(TreeNode* curr, string path, vector<string>& paths) {
        if (curr == nullptr) return;
        path += ("->" + to_string(curr -> val));
        // leaf node
        if (curr -> left == nullptr && curr -> right == nullptr) {
            paths.push_back(path);
            return;
        }
        if (curr -> left) preTraversal(curr -> left, path, paths);
        if (curr -> right) preTraversal(curr -> right, path, paths);
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        string path = to_string(root -> val);
        preTraversal(root -> left, path, paths);
        preTraversal(root -> right, path, paths);
        if (root -> left == nullptr && root -> right == nullptr) paths.push_back(path);
        return paths;
    }
};