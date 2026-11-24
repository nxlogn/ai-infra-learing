//
// Created by 55340 on 2026/11/24.
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        int n = nums.size(); // 用于遍历

        vector<int> answer(n, 1); // answer作为前缀的同时也是答案

        for (int i = 1; i < n; i++) { // 从左到右记录不包含自己的前缀
            answer[i] = answer[i - 1] * nums[i - 1];
        }

        int suffix = 1;
        for (int j = n - 1; j >= 0; j--) { // 从右到左记录不包含自己的后缀
            answer[j] *= suffix;
            suffix *= nums[j];
        }

        return answer;
    }
};