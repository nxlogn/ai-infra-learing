#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
  int findDuplicate(vector<int> &nums)
  {
    int slow = 0;
    int fast = 0;

    // 第一阶段 寻找相遇点
    do
    {
      slow = nums[slow];
      fast = nums[nums[fast]];
    } while (slow != fast);

    // 第二阶段 寻找环入口
    fast = 0;

    while (slow != fast)
    {
      slow = nums[slow];
      fast = nums[fast];
    }

    return slow;
  }
};