#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;

        int m = matrix.size();
        int n = matrix[0].size();

        // 从右上角开始二分查找，保证左边更小，下边更大
        int row = 0;
        int col = n - 1;

        while (row < m && col >= 0) {
            int curNum = matrix[row][col];
            if (curNum == target) {
                return true;
            } else if (curNum > target) {
                // 大了，往左
                col--;
            } else {
                // 小了，往下
                row++;
            }
        }
        return false;
    }
};