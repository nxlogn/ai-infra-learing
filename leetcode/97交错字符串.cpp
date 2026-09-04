#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  /**
   * 可以分解为小问题-存在状态转移-动态规划
   */
  bool isInterleave(string s1, string s2, string s3) {
    int m = s1.size();
    int n = s2.size();

    if (m + n != s3.size())
      return false; // 长度不符合

    // dp[i][j]:s1的前i个字符和s2的前j个字符是否可以组成s3的前i+j个字符
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= m; i++) {
      dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
    }

    for (int j = 1; j <= n; j++) {
      dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];
    }

    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        // 只需要考虑第i+j-1位置的字符加入后的状态,要么从s1取，要么从s2取
        dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1] ||
                    dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
      }
    }

    return dp[m][n];
  }
};