#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> result;
        // 路径数组
        vector<int> path;
        // 排序
        sort(candidates.begin(), candidates.end());
        // 执行回溯
        backtrack(candidates, target, 0, path, result);
        return result;
    }

private:
    void backtrack(vector<int> &candidates, int target, int start,
                   vector<int> &path, vector<vector<int>> &result) {
        // target为0，满足条件
        if (target == 0) {
            result.push_back(path);
            return;
        }
        // 遍历每一个数字
        for (int i = start; i < (int)candidates.size(); i++) {
            // 该数字已经超过，不做后续处理
            if (candidates[i] > target) {
                break;
            }
            // 选择
            path.push_back(candidates[i]);
            // 回溯
            backtrack(candidates, target - candidates[i], i, path, result);
            // 撤销
            path.pop_back();
        }
    }
};