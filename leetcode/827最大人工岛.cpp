#include <bits/stdc++.h>

using namespace std;

class Solution {

  public:
    /**
     * dfs算出每个岛屿的面积
     * 遍历0，加上岛屿的面积，记得去重，防止多次加
     */
    int n;
    // 四个方向
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    // dfs(i, j, label) ij位置处岛屿标志为label的岛的面积
    int dfs(vector<vector<int>> &grid, int i, int j, int label) {
        grid[i][j] = label;
        int area = 1;
        for (int d = 0; d < 4; d++) {
            int x = i + dx[d], y = j + dy[d];
            if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] == 1) {
                area += dfs(grid, x, y, label);
            }
        }
        return area;
    }

    int largestIsland(vector<vector<int>> &grid) {
        n = grid.size();

        // 遍历所有岛屿，计算面积
        vector<int> areas = {0, 0};
        int label = 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    areas.push_back(dfs(grid, i, j, label));
                    ++label;
                }
            }
        }

        int ans = *max_element(areas.begin(), areas.end());
        // 遍历所有0，加入岛屿计算最大值
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    int sum = 1;
                    // 存邻居的label
                    unordered_set<int> neighbors;
                    for (int d = 0; d < 4; d++) {
                        int x = i + dx[d], y = j + dy[d];
                        if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] > 1) {
                            neighbors.insert(grid[x][y]);
                        }
                    }
                    for (int id: neighbors) {
                        sum += areas[id];
                    }
                    ans = max(ans, sum);
                }
            }
        }
        return ans;
    }
};