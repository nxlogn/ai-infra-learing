#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
  /**
   * 先排序，再固定一个位置，再双指针找答案
   */
  vector<vector<int>> threeSum(vector<int> &nums)
  {
    // 排序
    sort(nums.begin(), nums.end());

    int n = nums.size();

    vector<vector<int>> ans;

    for (int i = 0; i < n - 2; i++)
    {
      if (nums[i] > 0)
        break;

      int left = i + 1, right = n - 1;

      if (i > 0 && nums[i] == nums[i - 1])
        continue;

      while (left < right)
      {
        int sum = nums[i] + nums[left] + nums[right];

        if (sum == 0)
        {
          ans.push_back({nums[i], nums[left], nums[right]});

          // 去重，继续找
          while (left < right && nums[left] == nums[left+1])
            left++;
          while (left < right && nums[right] == nums[right-1])
            right--;

          left++;
          right--;
        }
        else if (sum < 0)
        {
          left++;
        }
        else
        {
          right--;
        }
      }
    }

    return ans;
  }
};