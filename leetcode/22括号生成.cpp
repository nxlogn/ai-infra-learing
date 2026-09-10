#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:
    /**
     * 只有当前左括号个数小于n可以放左括号
     * 只有当前右括号个数小于左括号可以放右括号
     * 回溯生成
     */
    vector<string> generateParenthesis(int n) {
        string path;
        path.reserve(2 * n); // 预分配存储空间
        dfs(path, 0, 0, n);
        return res;
    }

  private:
    vector<string> res;

    /**
     * @param: path 回溯的暂存结果
     * @param: open 左括号个数
     * @param: close 右括号个数
     * @param: n 括号对数
     * @return: void
     */
    void dfs(string &path, int open, int close, int n) {
        if (path.size() == n * 2) {
            res.push_back(path);
            return;
        }
        if (open < n) {
            path.push_back('(');
            dfs(path, open + 1, close, n);
            path.pop_back();
        }
        if (close < open) {
            path.push_back(')');
            dfs(path, open, close + 1, n);
            path.pop_back();
        }
    }
};