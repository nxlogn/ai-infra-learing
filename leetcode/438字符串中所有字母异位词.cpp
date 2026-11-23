//
// Created by 55340 on 2026/11/23.
//

#include <string>
#include <vector>
#include <array>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        int n = s.size(), m = p.size();
        if (n < m) return ans; // s比p短，不可能

        array<int, 26> need{}, window{}; // {}初始化为全0

        for (char c : p)
            need[c - 'a']++; // 目标账本：p中各字母次数

        for (int i = 0; i < n; i++) {
            window[s[i] - 'a']++; // 右端字符进窗口

            if (i >= m) { // 窗口超出长度，左端字符出窗口
                window[s[i - m] - 'a']--;
            }

            if (i >= m - 1 && window == need) {
                // 窗口长度恰好为m时对比
                ans.push_back(i - m + 1);
            }
        }
        return ans;
    }
};