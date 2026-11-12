//
// Created by 55340 on 2026/11/12.
//

#include <stack>
#include <vector>
#include <iostream>
class Solution {
public:
    int maximalRectangle(std::vector<std::vector<char>> &matrix) {
        // 空matrix返回0
        if (matrix.empty() || matrix[0].empty())
            return 0;

        // 高m，宽n
        int m = matrix.size(), n = matrix[0].size();

        // 每列的连续1高度
        std::vector<int> heights(n, 0);

        int ans = 0;

        // 计算每一行的连续1的柱子高度
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
            }
            std::stack<int> stk;
            // j从0走到n
            for (int j = 0; j <= n; j++) {
                // 当前高度
                int cur = (j == n) ? 0 : heights[j];
                // 单调栈递增，处理每一个柱子
                while (!stk.empty() && cur < heights[stk.top()]) {
                    // 右边界就是j
                    // 栈顶高度
                    int h = heights[stk.top()];
                    stk.pop();
                    // 左边界
                    int left = stk.empty() ? -1 : stk.top();
                    ans = std::max(ans, h * (j - left - 1));
                }
                // 处理完单调栈里全部的高柱子
                stk.push(j);
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    std::vector<std::vector<char>> m = {{'1','0'},{'1','1'}};
    std::cout << s.maximalRectangle(m) << std::endl;
    return 0;
}