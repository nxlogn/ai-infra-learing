#include <string>;
#include <vector>;
using namespace std;
class Solution {
public:
    /*
    1. 记录当前右括号结尾的最长局部最长长度，注意当前右括号是最后一个结尾
    2. 动态规划找到之间的关系进行转移方程
    */
    int longestValidParentheses(string s) {
        int n = s.size();
        int ans = 0;
        vector<int> dp(n, 0);

        for (int i = 1; i < n; i++) {
            // s[i]为右括号
            if (s[i] == ')') {
                // ...()
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } 
                // ...j(...i-1)
                else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + 2;
                    if (i - dp[i - 1] - 2 >= 0) {
                        // 如果第j-1个位置有元素，接上前面的长度
                        dp[i] += dp[i - dp[i - 1] - 2];
                    } 
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};