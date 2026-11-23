//
// Created by 55340 on 2026/11/19.
//
// LeetCode 301. 删除无效的括号
// 删除最少数量的括号使 s 有效，返回所有可能的结果（不能重复）。
//
// 思路：预先计数 + 回溯
// 1) 先扫一遍求出最少要删的左/右括号数 ldel/rdel：
//    遇 '(' 则 ldel++；遇 ')' 能消掉一个 '(' 就 ldel--，否则 rdel++。
// 2) DFS 枚举每段连续相同括号「删几个」，恰好删掉 ldel 个 '('、rdel 个 ')'。
//    字母永远保留；一段相同括号删哪几个结果都一样，只枚举个数 d，天然去重。
// 3) 剪枝：前缀中未匹配的 '(' 数 balance < 0 时立即返回。
//
// 时间：最坏指数级（答案个数本身可达指数级），n <= 25 轻松通过。
// 空间：O(n) 递归栈 + path。

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        // 第一步，统计最少需要删除的左右括号数量
        int ldel = 0, rdel = 0;
        for (char c : s) {
            if (c == '(') {
                ++ldel;
            } else if (c == ')') {
                if (ldel > 0) --ldel; // 与前面1哥（配对
                else ++rdel; // 多余的） 需要删掉
            }
        }

        vector<string> ans;
        string path;
        path.reserve(s.size());
        dfs(s, 0, ldel, rdel, 0, path, ans);

        return ans;
    }
private:
    // i 待处理位置
    // ldel/rdel：还需要删除的左右括号数量
    // balance：path中尚未匹配的左括号数量
    void dfs(const string& s, int i, int ldel, int rdel, int balance, string& path, vector<string>& ans) {
        if (balance < 0) return; // 前缀非法，剪枝
        if (i == static_cast<int>(s.size())) {
            if (ldel == 0 && rdel == 0 && balance == 0) ans.push_back(path);
            return;
        }

        char c = s[i];
        if (c != '(' && c != ')') { // 字母必须保留
            path.push_back(c);
            dfs(s, i + 1, ldel, rdel, balance, path, ans);
            path.pop_back();
            return;
        }

        // 找到从i开始的连续相同括号段长度len
        int len = 1;
        while (i + len < static_cast<int>(s.size()) && s[i + len] == c) ++len;

        // 枚举删除d个，保留 len - d 个
        int maxDel = min(len, c == '(' ? ldel : rdel);
        for (int d = 0; d <= maxDel; d++) {
            int keep = len - d;
            path.append(keep, c);
            dfs(s, i + len,
                ldel - (c == '(' ? d : 0),
                rdel - (c == ')' ? d : 0),
                    balance + (c == '(' ? keep : -keep),
                    path, ans);
            );
            path.erase(path.size() - keep);
        }
    }
};














