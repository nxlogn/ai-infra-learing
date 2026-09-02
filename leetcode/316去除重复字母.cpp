#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
  string removeDuplicateLetters(string s)
  {
    int cnt[26] = {0}; // 后面还剩多少个字符
    bool used[26] = {false}; // 字符是否已经在答案中

    for (char c : s)
    {
      cnt[c - 'a']++;
    }

    string ans;

    for (char c : s)
    {
      int index = c - 'a';
      cnt[index]--;

      // 已经选过了，跳过
      if (used[index])
      {
        continue;
      }

      // 当前字符更小，并且栈顶字符后面还能再出现
      // 把栈顶弹掉，让字典序更小
      while (!ans.empty() && ans.back() > c && cnt[ans.back() - 'a'] > 0)
      {
        used[ans.back() - 'a'] = false;
        ans.pop_back();
      }

      ans.push_back(c);
      used[index] = true;
    }

    return ans;
  }
};