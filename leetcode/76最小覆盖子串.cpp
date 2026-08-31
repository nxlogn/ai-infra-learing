#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
  string minWindow(string s, string t)
  {
    // need[c]:字符 c 还需要多少个
    vector<int> need(128, 0);

    for (char c: t)
    {
      need[c]++;
    }

    int left = 0;
    int right = 0;

    // 当前窗口已经匹配了 t 中多少个字符
    int matchted = 0;

    int start = 0;
    int minLen = INT_MAX;

    while (right < s.size())
    {
      char c = s[right];

      // 如果这个字符当前还是需要的,说明成功配一个
      if (need[c] > 0)
      {
        matchted++;
      }

      // 无论是不是多余字符,都要进入窗口
      need[c]--;

      right++;

      // 当前窗口已经覆盖t
      while (matchted == t.size())
      {
        // 更新答案
        if (right - left < minLen)
        {
          minLen = right - left;
          start = left;
        }

        char d = s[left];

        // 左侧字符准备已出窗口
        need[d]++;

        // need[d] > 0 表示这个数字移走以后不够了
        if (need[d] > 0)
        {
          matchted--;
        }

        left++;
      }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
  }
};