#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    // 异或满足交换律
    // a ^ a = 0
    // a ^ 0 = a
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int x : nums) {
            ans ^= x;
        }
        return ans;
    }
};