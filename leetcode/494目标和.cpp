#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:
    /**
     * p = (sum + target) / 2
     * 找和为p的子集，01背包
     */
    int findTargetSumWays(vector<int> &nums, int target) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (abs(target) > sum || (sum + target) % 2 != 0) return 0;
        int p = (sum + target) / 2;

        // dp[i][j]:前i个元素和为j的方案个数
        vector<vector<int>> dp(n + 1, vector<int>(p + 1, 0));

        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= p; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1]) dp[i][j] += dp[i - 1][j - nums[i - 1]];
            }
        }

        return dp[n][p];
    }
};
