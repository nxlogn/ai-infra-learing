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
    bool isSymmetric(TreeNode *root) {
        if (root == nullptr) return true;

        return check(root->left, root->right);

    }

    // 检查p和q是否镜像对称
    bool check(TreeNode* p, TreeNode* q) {
        if (q == nullptr && p == nullptr) return true;
        if (q == nullptr || p == nullptr) return false;

        return q->val == p->val && check(p->left, q->right) && check(p->right, q->left);
    }
};