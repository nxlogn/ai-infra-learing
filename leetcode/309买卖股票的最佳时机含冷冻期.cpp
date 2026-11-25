//
// Created by 55340 on 2026/11/25.
//
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 今天结束时 3种状态 持有 冷冻 free
        int hold = -prices[0];
        int freezing = 0; // 今天卖了，明天冷冻
        int free = 0; // 包括了昨天卖的情况

        // 更新3个状态
        for (int i = 1; i < prices.size(); i++) {
            // 今天持有，今天买的
            int newHold = max(hold, free - prices[i]);
            // 今天卖了
            int newFreezing = hold + prices[i];
            // 今天什么都不做
            int newFree = max(free, freezing);
            hold = newHold;
            freezing = newFreezing;
            free = newFree;
        }

        return max(freezing, free);
    }
};