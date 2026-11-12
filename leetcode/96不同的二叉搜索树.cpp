//
// Created by 55340 on 2026/11/12.
//

#include <vector>
class Solution {
public:
    int numTrees(int n) {
        // dp[i] i个节点能组成的不同二叉树个数
        std::vector<int> dp(n + 1, 0);

        // 初始化空树和单节点
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            // 根节点时第i小的值
            for (int j = 1; j <= i; j++) {
                // 左边能组成的不同个数
                int left = dp[j - 1];
                int right = dp[i - j];
                // 把所有可能的j根节点情况下的组合加起来
                dp[i] += left * right;
            }
        }

        return dp[n];
    }
};
