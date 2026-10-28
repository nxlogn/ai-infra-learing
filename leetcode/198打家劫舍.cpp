#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    // 本质：怎么在不碰到邻居的情况下收益最大化？
    // dp思路：当前房子被偷和不被偷情况
    // 只依赖两种情况，滚动dp
    int rob(vector<int> &nums) {
        int prev2 = 0;
        int prev1 = 0;

        for (int num : nums) {
            // i被偷：dp[i - 2] + nums[i]；
            // i不被偷：dp[i - 1];
            int cur = max(prev2 + num, prev1);
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};