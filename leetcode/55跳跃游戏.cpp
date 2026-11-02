#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = (int)nums.size();
        int reach = 0;

        for (int i = 0; i < n; i++) {
            if (i > reach) return false;
            // 更新最远可抵达点
            reach = max(reach, i + nums[i]);
            if (reach >= n - 1) return true;
        }
        
        return true;
    }
};