#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
  /**
   * 从下往上更新动态数组
   */
  int minimumTotal(vector<vector<int>> &triangle)
  {
    int n = triangle.size();
    // dp[i]：从下往上的第i行的最小路径和
    vector<int> dp = {triangle[n - 1]};

    // 倒数第二行开始
    for (int i = n - 2; i >= 0; i--)
    {
      for (int j = 0; j <= i; j++)
      {
        dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
      }
    }

    return dp[0];
  }
};
