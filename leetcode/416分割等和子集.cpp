//
// Created by 55340 on 2026/11/12.
//

#include <numeric>
#include <vector>
class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        // 总和为奇数，无法平分
        if (sum % 2 != 0) return false;

        int target = sum / 2;

        // dp[j] 能否凑出和j
        std::vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int num : nums) {
            if (num > target) return false;
            // 倒序遍历，保证每个数只用1次（01背包）
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
            if (dp[target]) return true;
        }
        return dp[target];
    }
};