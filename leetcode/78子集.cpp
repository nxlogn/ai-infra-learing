#include <bits/stdc++.h>

using namespace std;


class Solution {
public:

    // 答案数组
    vector<vector<int>> res;
    // 路径数组
    vector<int> path;
    // 回溯收集
    void backtrack(vector<int>& nums, int start) {
        res.push_back(path);

        for (int i = start; i < (int)nums.size(); i++) {
            path.push_back(nums[i]);
            backtrack(nums, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(nums, 0);
        return res;
    }
};