#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    /**
     * slow站在应该被交换的位置
     * fast站在非0元素的位置，逐个交换
     */
    void moveZeroes(vector<int>& nums) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != 0) {
                swap(nums[slow], nums[fast]);
                slow++;
            }
        }
    }
};