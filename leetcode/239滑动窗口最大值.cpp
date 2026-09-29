#include <bits/stdc++.h>
#include <deque>
#include <vector>
using namespace std;

class Solution {
public:
    /**
    1. deque实现单调队列，保证队头元素是窗口内最大的
    2. 每次循环去掉索引在窗口前的元素
    3. 每次循环加入的元素必须满足单调性
    */
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;

        int n = static_cast<int>(nums.size());

        vector<int> result;
        result.reserve(n - k + 1);

        for (int i = 0; i < n; i++) {
          while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
          }

          while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
          }
          dq.push_back(i);

          // 窗口大小达到k后，记录最大值
          if (i - k + 1) {
            result.push_back(nums[dq.front()]);
          }
        }
        return result;
    }
};

int main() {
    Solution solution;
    
    return 0;
}
