#include <vector>
using namespace std;
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        // cnt[r] 表示之前前缀和模 k 余 r 的出现次数
        vector<int> cnt(k, 0);
        cnt[0] = 1;

        int ans = 0;
        int prefix = 0;

        for (int num: nums) {
            prefix += num;

            // 负数取模
            int r = (prefix % k + k) % k;

            // 所有余数相等的i和j位置都可以形成满足条件的子数组
            ans += cnt[r];
            cnt[r]++;
        }

        return ans;
    }
};