#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int longest = 0;
        for (int num: numSet) {
            if (numSet.count(num - 1)) {
                continue;
            }
            // 只考虑起点
            int cur = num;
            int length = 1;
            while (numSet.count(cur + 1)) {
                cur = cur + 1;
                length++; 
            }
            longest = max(longest, length);
        }
        return longest;
    }
};