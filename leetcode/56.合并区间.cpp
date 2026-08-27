#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    if (intervals.empty())
      return {};

    // 按左端点排序
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> mergerd;

    // 初始化第一个区间
    mergerd.push_back(intervals[0]);

    for (int i = 1; i < intervals.size(); i++) {
      // 当前区间
      int left = intervals[i][0];
      int right = intervals[i][1];
      // 上一个合并区间的右端点
      int lastRight = mergerd.back()[1];

      if (left <= lastRight) {
        // 重叠,更新右端点为较大值
        mergerd.back()[1] = max(lastRight, right);
      } else {
        // 不重叠,加入新区间
        mergerd.push_back(intervals[i]);
      }
    }
    return mergerd;
  }
};