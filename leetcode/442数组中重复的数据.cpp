#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
  vector<int> findDuplicates(vector<int> &nums)
  {
    vector<int> ans;

    // 数值范围是 [1, n]
    // 数字 x 映射到下标 x - 1
    // 用正负号记录“是否出现过”
    for (int num : nums)
    {
      int x = abs(num);
      int index = x - 1;
      if (nums[x - 1] < 0)
      {
        ans.push_back(x);
      }
      else
      {
        nums[index] = - nums[index];
      }
    }
    return ans;
  }
};