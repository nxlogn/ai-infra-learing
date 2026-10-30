#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    // 下一个最大元素用单调栈的思想
    // 栈底-栈顶 大-小 一次遍历 每个当前元素和栈顶元素比较 保持栈元素的大小关系
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> stk;

        for (int i = 0; i < n; i++) {
            // 比栈顶元素大，就是栈顶元素的下一个最大
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int idx = stk.top();
                stk.pop();
                answer[idx] = i - idx;
            }
            stk.push(i);
        }

        return answer;
    }
};