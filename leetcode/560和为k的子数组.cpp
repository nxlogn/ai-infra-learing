#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    // 这种求子数组满足什么条件的一律想到前缀和
    // 如何一次遍历就找到所有的个数？哈希表空间换时间，保存每种sum出现的次数
    // 利用prefix[i] - prefix[j -1] = sum[j, i] = k; prefix[j - 1] = prefix[i] - k;
    // 和为preifix[j - 1]出现的次数统计进来即可； 
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefix;
        prefix[0] = 1;

        int ans = 0;
        int sum = 0;

        for (int num : nums) {
            sum += num;
            auto it = prefix.find(sum - k);
            if (it != prefix.end()) {
                ans += it->second;
            }
            prefix[sum]++;
        }

        return ans;
    }
};