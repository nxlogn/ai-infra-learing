#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
  bool wordBreak(string s, vector<string> &wordDict)
  {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());

    int n = s.size();
    //  dp[i]前i个字符可以被拆分
    vector<bool> dp(n + 1, false);

    //  空字符串可以被拆分
    dp[0] = true;

    for (int i = 1; i <= n; i++)
    {
      for (int j = 0; j < i; j++)
      {
        // 前j个字符可以拆分并且s[j, i - 1]在字典中
        if (dp[j] && dict.count(s.substr(j, i - j)))
        {
          dp[i] = true;
          break;
        }
      }
    }
    return dp[n];
  }
};