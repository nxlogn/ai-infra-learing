#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
  int longestOnes(vector<int> &nums, int k)
  {
    int left = 0;
    int zeroCount = 0;
    int ans = 0;

    for (int right = 0; right < nums.size(); right++)
    {
      // 进入窗口
      if (nums[right] == 0)
      {
        zeroCount++;
      }

      // 0的数量超过k，窗口不合法
      while (zeroCount > k)
      {
        if (nums[left] == 0)
        {
          zeroCount--;
        }
        left++;
      }

      // 当前窗口中最多只有k个0
      ans = max(ans, right - left + 1);
    }

    return ans;
  }
};