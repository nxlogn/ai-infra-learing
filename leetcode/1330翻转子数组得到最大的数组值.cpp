#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    /**
     * 把相邻元素的差值想象成坐标轴上的距离，一对相邻元素一个区间
     * 交换元素影响的是区间的边界值，而最大的情况下是新增了2倍的间隙
     */
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;

        long long base = 0;

        for (int i = 1; i < n; i++) {
            base += abs(nums[i] - nums[i - 1]);
        }

        int maxLow = INT_MIN;
        int minHigh = INT_MAX;
        int gain= 0;
        
        // 中间反转
        for (int i = 0; i < n - 1; i++) {
            maxLow = max(maxLow, min(nums[i], nums[i + 1]));
            minHigh = min(minHigh, max(nums[i], nums[i + 1]));
        }

        gain = max(gain, 2 * (maxLow - minHigh));

        // 前缀反转
        for (int i = 0; i < n - 1; i++) {
            gain = max(gain, abs(nums[0] - nums[i + 1]) - abs(nums[i] - nums[i + 1]));
        }

        // 后缀反转
        for (int i = 1; i < n; i++) {
            gain = max(gain, abs(nums[i - 1] - nums[n - 1]) - abs(nums[i - 1] - nums[i]));
        }

        return (int)(base + max(0, gain));
    }
};