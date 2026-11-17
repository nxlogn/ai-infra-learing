#include <string>
//
// Created by 55340 on 2026/11/17.
//
// LeetCode 647. 回文子串
// 思路：中心扩展法。每个回文串都有一个"中心"，
// 长度为 n 的字符串共有 2n-1 个中心：
//   - n 个单字符中心（奇数长度回文，如 "aba"）
//   - n-1 个字符间隙中心（偶数长度回文，如 "abba"）
// 从每个中心向两边扩展，只要 s[l] == s[r] 就找到一个回文子串，计数 +1。
// 时间复杂度 O(n^2)，空间复杂度 O(1)。
class Solution {
public:
    int countSubstrings(std::string s) {
        int n = static_cast<int>(s.size());
        int ans = 0;

        // center编码。偶数表示单字符中心，奇数表示间隙中心
        for (int center = 0; center < 2 * n - 1; ++center) {
            int l = center / 2;
            int r = l + center % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {
                ++ans; // [l ,r] 是一个回文子串
                --l;
                ++r;
            }
        }
        return ans;
    }
};
