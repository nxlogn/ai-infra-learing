#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  /**
   * f = s1arr1[i] + s2arr2[i] + s3k
   * fmax - fmin即可，系数组合有8种情况
   * 其中固定其中一个，算出来的结果只会让max-min交换位置
   */
  int maxAbsValExpr(vector<int> &arr1, vector<int> &arr2) {
    int n = arr1.size();

    int ans = 0;

    for (int s1 : {-1, 1}) {
      for (int s2 : {-1, 1}) {
        int mx = INT_MAX;
        int mn = INT_MIN;
        for (int k = 0; k < n; k++) {
          int f = s1 * arr1[k] + s2 * arr2[k] + k;
          mx = max(mx, f);
          mn = min(mn, f);
        }
        ans = max(ans, mx - mn);
      }
    }
    return ans;
  }
};