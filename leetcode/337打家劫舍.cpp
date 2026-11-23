//
// Created by 55340 on 2026/11/18.
//
// LeetCode 337. 打家劫舍 III
// 二叉树版打家劫舍：父子节点不能同时被偷，求能偷到的最大金额。
//
// 思路：树形 DP（后序遍历），每个节点向上返回两个状态：
//   rob  : 偷当前节点时，以它为根的子树最大金额
//          = node->val + 左孩子不偷 + 右孩子不偷（孩子必须不偷）
//   skip : 不偷当前节点时，子树最大金额
//          = max(左偷, 左不偷) + max(右偷, 右不偷)（孩子随意）
// 答案 = max(根的 rob, 根的 skip)。
// 时间 O(n)，空间 O(h)（递归栈，h 为树高）。

#include <algorithm>
#include <utility>

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
    int rob(TreeNode *root) {
        auto [robRoot, skipRoot] = dfs(root);
        return std::max(robRoot, skipRoot);
    }
private:
    // 返回 偷该节点的最大金额，不偷该节点的最大金额
    std::pair<int, int> dfs(TreeNode *node) {
        if (node == nullptr) return {0, 0};

        auto [robL, skipL] = dfs(node->left);
        auto[robR, skipR] = dfs(node->right);

        int rob = node->val + skipL + skipR;
        int skip = std::max(robL, skipL) + std::max(robR, skipR);
        return {rob, skip};
    }
};
