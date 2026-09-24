#include <algorithm>
#include <climits>
#include <cstdint>
#include <vector>
using namespace std;

class Solution {
public:
    /*
    1. nums1拿前i个，nums2拿前j个，i + j = （m + n + 1） / 2
    2. [...nums[i -1]][nums[i]....], [...nums[j - 1]][nums[j]...]
    3. 只需要考虑这四个边界元素的大小情况即可确定是否满足切分，无需重新组合
    */
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        if (m > n) {
          return findMedianSortedArrays(nums2, nums1);
        }

        int left = 0;
        int right = m;
        int half = (m + n + 1) / 2;
        while (left <= right) {
          int i = left + (right - left) / 2;
          int j = half - i;

          int left1 = (i == 0) ? INT_MIN : nums1[i - 1];
          int right1 = (i == m) ? INT_MAX : nums1[i];

          int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
          int right2 = (j == n) ? INT_MAX : nums2[j];

          if (left1 <= right2 && left2 <= right1) {
            if ((m + n) % 2 != 0) {
              return max(left1, left2);
            } else {
              return static_cast<double>((max(left1, left2) + min(right1, right2) )) / 2.0;
            }
          }

          if (left1 > right2) {
            right = i - 1;
          } else {
            left = i + 1;
          }
        }
        return 0.0;
    }
};