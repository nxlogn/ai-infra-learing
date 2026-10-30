#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    // 递归反转每一颗子树
    TreeNode *invertTree(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }

        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        // 交换左右
        root->left = right;
        root->right = left;

        return root;
    }
};