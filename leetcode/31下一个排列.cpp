#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    /*
    1. 倒着找到第一个nums[i]<nums[i+1]的i
    2. 倒着找到第一个大于nums[i]的j
    3. 交换nums[i]和nums[j]
    4. 反转后面的非递增序列，完成最小变动
    */
public:
    void nextPermutation(vector<int> &nums) {
        int n = nums.size();
        int i = n - 2;

        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        if (i >= 0) {
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }

        reverse(nums.begin() + i + 1, nums.end());
    }
};