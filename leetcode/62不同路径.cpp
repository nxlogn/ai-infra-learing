#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    // 典型的计数型dp，状态来源于上面和左边的格子
    int uniquePaths(int m, int n) {
        // 初始化
        vector<vector<int>> dp(m, vector<int>(n, 1));

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }
};