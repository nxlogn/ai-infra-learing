//
// Created by 55340 on 2026/11/25.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int cnt[26] = {};

        // 统计出现次数
        for (char c : tasks) {
            cnt[c - 'A']++;
        }

        // 统计出现的最大次数
        int maxCount = *max_element(cnt, cnt + 26);
        // 统计出现的最大次数的元素个数
        int maxKind = 0;
        for (int c : cnt) {
            if (c == maxCount) maxKind++;
        }

        // 用出现次数最大的元素搭建骨架 A ? ? A ? ? A..
        // 塞满了，取长度；塞不满，(maxCount - 1) * (n - 1) + maxKind;
        return max((int)tasks.size(), (maxCount - 1) * (n - 1) + maxKind);
    }
};