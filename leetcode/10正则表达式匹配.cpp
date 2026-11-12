//
// Created by 55340 on 2026/11/11.
//

#include <string>
#include <vector>

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        int size_s = s.size();
        int size_p = p.size();

        // dp[i][j] s前i个能否被p前j个字符匹配
        std::vector<std::vector<bool>> dp(size_s + 1, std::vector<bool>(size_p + 1));
        dp[0][0] = true;

        // 匹配s为空的情况的初始化
        for (int j = 2; j <= size_p; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= size_s; i++) {
            for (int j = 1; j <= size_p; j++) {
                if (p[j - 1] == '*') {
                    // 选择匹配0次 取决于dp[i][j - 2]
                    bool match_zero = dp[i][j - 2];
                    // 选择匹配一次或者多次，继续用p[j - 1]去匹配前面的
                    bool match_1_more = (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j];

                    dp[i][j] = match_1_more || match_zero;
                } else {
                    bool cur_match = s[i - 1] == p[j - 1] || p[j - 1] == '.';
                    // 当前字符匹配成功，取决于d[i - 1][j - 1]
                    dp[i][j] = cur_match && dp[i - 1][j - 1];
                }
            }
        }

        return dp[size_s][size_p];
    }
};
