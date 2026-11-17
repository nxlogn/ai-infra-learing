#include <vector>
#include <algorithm>
#include <climits>
//
// Created by 55340 on 2026/11/17.
//
// LeetCode 279. 完全平方数
// 思路：动态规划（完全背包）。
// 物品：1, 4, 9, 16, ... 所有不超过 n 的完全平方数，每个可用无限次。
// 背包容量：n。求恰好装满背包所需的最少物品数。
// 状态：dp[i] = 和为 i 的完全平方数的最少数量。
// 转移：dp[i] = min(dp[i - j*j] + 1)，其中 1 <= j*j <= i。
//   含义：最后一个数是 j*j，剩下的 i - j*j 用最优方案凑出。
// 初始化：dp[0] = 0（和为 0 不需要任何数），其余为 INT_MAX。
//   由于 1 是完全平方数，任何 i 都能被凑出，dp[i - j*j] 不会是 INT_MAX，无溢出风险。
// 时间复杂度 O(n * sqrt(n))，空间复杂度 O(n)。
class Solution {
public:
    int numSquares(int n) {
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = std::min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};
