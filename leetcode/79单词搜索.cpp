#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    // 寻找一条路径，路径上的字符拼成word
    // 网格dfs，每个格子作为起点，向四方递归匹配下一个字符，匹配失败就回退
    bool exist(vector<vector<char>>& board, string word) {
        // board不能为空
        if (word.empty()) return false;
        if (board.empty() || board[0].empty()) return false;

        rows = board.size();
        cols = board[0].size();

        // 从每一个可以开始的格子开始执行回溯
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == word[0] && backtrack(board, i, j, word, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
private:
    int rows = 0;
    int cols = 0;
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool backtrack(vector<vector<char>>& board, int r, int c, string word, int idx) {
        // 越界或不相等
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[idx]) {
            return false;
        }
        // 终止条件
        if (idx == static_cast<int>(word.size()) - 1) {
            return true;
        }

        // 修改当前位置标记为已访问
        char saved = board[r][c];
        board[r][c] = '#';

        // 向四边搜索
        for (int d = 0; d < 4; d++) {
            int nextRow = r + directions[d][0];
            int nextCol = c + directions[d][1];
            if (backtrack(board, nextRow, nextCol, word, idx + 1)) {
                return true;
            }
        }
        // 4个方向都不行，撤回
        board[r][c] = saved;
        return false;
    }
};