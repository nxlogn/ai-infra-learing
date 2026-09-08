#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    /**
     * 查找互补的数的下标-遍历的过程中用map存储
     */
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (seen.count(complement)) {
                return {seen[complement], i};
            }
            seen[nums[i]] = i;
        }
        return {};
    }
};