//
// Created by 55340 on 2026/11/24.
//
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int> const &nums) {
        int n = nums.size();

        // nums两边加上1
        vector val(n + 2, 1);

        // 初始化val
        for (int i = 0; i < n; i++) {
            val[i + 1] = nums[i];
        }

        // dp[i][j]:开区间(i, j)内搓气球的最大硬币数量
        vector dp(n + 2, vector(n + 2, 0));

        for (int len = 2; len <= n + 1; len++) {
            // len = j - i 为2时开区间内有至少一个气球
            for (int i = 0; i + len <= n + 1; i++) {
                // 左边界向右走，枚举所有长度为len的区间
                int j = i + len;
                for (int k = i + 1; k < j; k++) {
                    // 区间内枚举每一个最后戳的气球的硬币数量
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] +
                                                 val[i] * val[k] * val[j]);
                }
            }
        }
        return dp[0][n + 1];
    }
};