//
// Created by 55340 on 2026/11/9.
//

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};

class Solution {
public:
    void flatten(TreeNode *root) {
        if (!root) return;
        // 递归遍历
        flatten(root->left);
        flatten(root->right);

        TreeNode* left = root->left;
        TreeNode* right = root->right;

        // 左子树为右子树，右子树为左子树的右子树
        root->right = left;
        root->left = nullptr;
        TreeNode* p = root;
        while (p->right) {
            p = p->right;
        }
        p->right = right;
    }
};
