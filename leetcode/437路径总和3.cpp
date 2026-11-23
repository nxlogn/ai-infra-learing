//
// Created by 55340 on 2026/11/23.
//

#include <unordered_map>
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
    std::unordered_map<long long, int> prefixCount;// 前缀和 -》在当前路径上出现的次数
    int target = 0;
    int ans = 0;

    void dfs(TreeNode* node, long long cur) {
        if (!node) return;

        cur += node->val;                           // 根到当前节点的前缀和
        auto it = prefixCount.find(cur - target);
        if (it != prefixCount.end())                // 每个匹配的祖先 = 一条合法路径
            ans += it->second;

        prefixCount[cur]++;                         // 记账，当前前缀和供子孙查询
        dfs(node->left, cur);
        dfs(node->right, cur);
        prefixCount[cur]--;                         // 回溯，离开时撤销，不污染兄弟分支
    }
public:
    int pathSum(TreeNode *root, int targetSum) {
        target = targetSum;
        prefixCount[0] = 1;                         // 空前缀，处理从根开始的路径
        dfs(root, 0);
        return ans;
    }
};