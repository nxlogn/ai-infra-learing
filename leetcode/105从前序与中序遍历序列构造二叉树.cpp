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
private:
    unordered_map<int, int> inIndexs;

    /*
    1. 给定前序遍历和中序遍历的区间，根据root节点来递归并返回root节点
    */
    TreeNode *build(vector<int> &preorder, int preL, int preR, int inL,
                    int inR) {
        if (preL > preR)
            return nullptr;

        int rootVal = preorder[preL];

        TreeNode *root = new TreeNode(rootVal);
        // 中心节点中序遍历位置，区分左右区间
        int idx = inIndexs[rootVal];
        // 左区间长度
        int leftSize = idx - inL;
        // 根节点左右子节点
        root->left = build(preorder, preL + 1, preL + leftSize, inL, idx - 1);
        root->right = build(preorder, preL + 1 + leftSize, preR, idx + 1, inR);

        return root;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        for (int i = 0; i < (int)preorder.size(); i++) {
            inIndexs[inorder[i]] = i;
        }

        return build(preorder, 0, (int)preorder.size() - 1, 0,
                     (int)inorder.size() - 1);
    }
};