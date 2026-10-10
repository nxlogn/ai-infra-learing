#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    // 寻找左边第一个target
    int lowbound(vector<int> &nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
    // 寻找最后一个target
    int upperbound(vector<int> &nums, int target) {
        int left = 0, right = (int)nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
    vector<int> searchRange(vector<int> &nums, int target) {
        int left = lowbound(nums, target);
        if (left == (int)nums.size() || nums[left] != target) {
            return {-1, -1};
        }
        int right = upperbound(nums, target);
        return {left, right - 1};
    }
};