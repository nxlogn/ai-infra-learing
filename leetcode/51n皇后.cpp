#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
  vector<vector<string>> ans;

  // 判断在row行，col列放皇后是否合法
  bool isValid(vector<string>& board, int row, int col, int n)
  {
    // 检查同一列
    for (int i = 0; i < row; i++)
    {
      if (board[i][col] == 'Q')
      {
        return false;
      }
    }

    // 检查左上角
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
      if (board[i][j] == 'Q')
      {
        return false;
      }
    }

    // 检查右上角
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
    {
      if (board[i][j] == 'Q')
      {
        return false;
      }
    }
    return true;
  }

  // 回溯
  void backtrack(vector<string>& board, int row, int n)
  {
    // n 行全部放完
    if (row == n)
    {
      ans.push_back(board);
      return;
    }

    // 当前这一行尝试每一列
    for (int col = 0; col < n; col++)
    {
      if (!isValid(board, row, col, n))
      {
        continue;
      }
      // 做选择
      board[row][col] = 'Q';

      // 放下一行
      backtrack(board, row + 1, n);

      // 撤销
      board[row][col] = '.';
    }
  }

  vector<vector<string>> solveNQueens(int n)
  {
    vector<string> board(n, string(n, '.'));

    backtrack(board, 0, n);

    return ans;
  }
};

int main()
{
}
