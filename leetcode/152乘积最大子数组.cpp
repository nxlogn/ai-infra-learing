#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int curMax = nums[0];
        int curMin = nums[0];
        int ans = nums[0];

        // 保存最大值和最小值，只能从3个状态中取值
        for (int i = 1; i < (int)nums.size(); i++) {
            int oldMax = curMax;
            int oldMin = curMin;
            curMax = max({nums[i], nums[i] * oldMax, nums[i] * oldMin});
            curMin = min({nums[i], nums[i] * oldMax, nums[i] * oldMin});
            
            ans = max(ans, curMax);
        }
        return ans;
    }
};

