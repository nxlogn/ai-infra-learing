//
// Created by 55340 on 2026/11/16.
//

#include <vector>
#include <stack>
#include <algorithm>
class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        // 首尾加上哨兵0，首部保证栈不空，尾部包转增清算完所有柱子
        std::vector<int> h;
        h.reserve(heights.size() + 2);
        h.push_back(0);
        h.insert(h.end(), heights.begin(), heights.end());
        h.push_back(0);

        std::stack<int> st;  // 存下标，对应高度单调递增
        int ans = 0;

        for (int i = 0; i < (int)h.size(); i++) {
            // 当前柱子比栈顶矮，栈顶的右边界确定，弹出结算
            while (!st.empty() && h[st.top()] > h[i]) {
                int top = st.top();
                st.pop();
                int width = i - st.top() - 1; // 左边界是新的栈顶
                ans = std::max(ans, h[top] * width);
            }
            st.push(i);
        }
        return ans;
    }
};