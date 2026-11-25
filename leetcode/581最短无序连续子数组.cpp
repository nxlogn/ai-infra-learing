//
// Created by 55340 on 2026/11/25.
//

#include <vector>
using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int right = -1, left = -1; // 初始化区间的边界
        int maxSeen = nums[0], minSeen = nums[n - 1]; // 初始化前缀最大和最小，用于判断是否需要加入排序区间

        for (int i = 0; i < n; i++) {
            maxSeen = max(maxSeen, nums[i]);
            if (nums[i] < maxSeen) {
                right = i;
            }
            int j = n - 1 - i;
            minSeen = min(minSeen, nums[j]);
            if (nums[j] > minSeen) {
                left = j;
            }
        }
        return left == -1 ? 0 : right - left + 1;
    }
};