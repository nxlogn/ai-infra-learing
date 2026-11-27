//
// Created by 55340 on 2026/11/26.
//

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
    int sum = 0;
public:
    TreeNode *convertBST(TreeNode *root) {
        // 反向中序遍历维护一个sum值赋值即可
        if (root == nullptr) return nullptr;

        // 右子树先进入
        convertBST(root->right);

        // 加上sum，更新自己
        sum += root->val;
        root->val = sum;

        // 进入左子树
        convertBST(root->left);

        return root;
    }
};
