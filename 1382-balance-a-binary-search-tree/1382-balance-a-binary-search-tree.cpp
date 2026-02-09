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
    void storeInorder (TreeNode* root, vector<int>& nodes) {
        if (root == NULL) return;
        storeInorder(root -> left, nodes);
        nodes.push_back(root -> val);
        storeInorder(root -> right, nodes);
    }
    TreeNode* buildBalancedTree(vector<int>& nodes, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start+end)/2;
        TreeNode* root = new TreeNode(nodes[mid]);

        root -> left = buildBalancedTree(nodes, start, mid - 1);
        root -> right = buildBalancedTree(nodes, mid + 1, end);

        return root;
    }
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> nodes;
        storeInorder(root, nodes);
        return buildBalancedTree(nodes, 0, nodes.size()-1);
    }
};