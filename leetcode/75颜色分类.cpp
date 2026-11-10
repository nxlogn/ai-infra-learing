#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = (int)nums.size();
        // 一次遍历，分区0 1 2
        // p[0]指向下一个需要被填充0的位置
        // p[2]指向下一个需要被填充2的位置
        int p0 = 0, i = 0, p2 = n - 1;
        while (i <= p2) {
            if (nums[i] == 0) {
                swap(nums[p0], nums[i]);
                p0++;
                i++;
            } else if (nums[i] == 2) {
                swap(nums[p2], nums[i]);
                // 交换后需要检查
                p2--;
            } else {
                // nums[i] == 1
                i++;
            }
        }
    }
};