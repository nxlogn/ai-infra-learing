#include <bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

using namespace std;

class Solution {
    /*
    1. 递归完成中序遍历
    */
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }

    void inorder(TreeNode *node, vector<int> &res) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left, res);
        res.push_back(node->val);
        inorder(node->right, res);
    }
};
