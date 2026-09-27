#include <algorithm> // min：第 18 行首次使用
#include <climits>   // INT_MAX：第 15 行首次使用
#include <iostream>  // cout, endl：第 117 行首次使用
#include <vector>    // vector：第 13 行首次使用

using namespace std;
// 64. 最小路径和
//给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，
//使得路径上的数字总和为最小。
/************暴力递归*****************/
class Solution {
private:
  int findpath(vector<vector<int>> &grid, int x, int y) {
    if (x == grid.size() || y == grid[0].size())
      return INT_MAX;
    if (x == grid.size() - 1 && y == grid[0].size() - 1)
      return grid[x][y];
    return grid[x][y] + min(findpath(grid, x + 1, y), findpath(grid, x, y + 1));
  }

public:
  int minPathSum(vector<vector<int>> &grid) { return findpath(grid, 0, 0); }
};
/************记忆化搜索*****************/
class Solution1 {
private:
  vector<vector<int>> mem;
  int findpath(vector<vector<int>> &grid, int x, int y) {
    if (x == grid.size() || y == grid[0].size())
      return INT_MAX;
    if (x == grid.size() - 1 && y == grid[0].size() - 1)
      return grid[x][y];
    if (mem[x][y] == -1) { //未计算过则进入递归
      mem[x][y] =
          grid[x][y] + min(findpath(grid, x + 1, y), findpath(grid, x, y + 1));
    }
    return mem[x][y]; //计算过直接返回值
  }

public:
  int minPathSum(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    mem = vector<vector<int>>(m, vector<int>(n, -1));
    return findpath(grid, 0, 0);
  }
};
/****************经典动态规划*******************/
class Solution2 {
public:
  int minPathSum(vector<vector<int>> &grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<int>> dp(row, vector<int>(col, 0));
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (i == 0 && j == 0)
          dp[i][j] = grid[i][j];
        else if (i == 0)
          dp[i][j] = dp[i][j - 1] + grid[i][j];
        else if (j == 0)
          dp[i][j] = dp[i - 1][j] + grid[i][j];
        else {
          dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
      }
    }
    return dp[row - 1][col - 1];
  }
};
/****************一维动态规划，空间 O(列数)*******************/
class Solution3 {
public:
  int minPathSum(vector<vector<int>> &grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<int> dp(col, 0);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (i == 0 && j == 0)
          dp[j] = grid[i][j];
        else if (i == 0)
          dp[j] = dp[j - 1] + grid[i][j];
        else if (j == 0)
          dp[j] += grid[i][j];
        else
          dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
      }
    }
    return dp[col - 1];
  }
};
/****************直接在原数组上修改*******************/
class Solution4 {
public:
  int minPathSum(vector<vector<int>> &grid) {
    int row = grid.size();
    int col = grid[0].size();
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (i == 0 && j != 0)
          grid[i][j] += grid[i][j - 1];
        else if (j == 0 && i != 0)
          grid[i][j] += grid[i - 1][j];
        else if (i == 0 && j == 0) {
          continue;
        } else {
          grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
        }
      }
    }
    return grid[row - 1][col - 1];
  }
};
int main() {
  vector<vector<int>> grid{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
  cout << "暴力递归： " << Solution().minPathSum(grid) << endl;
  cout << "记忆化搜索： " << Solution1().minPathSum(grid) << endl;
  cout << "经典动态规划： " << Solution2().minPathSum(grid) << endl;
  cout << "一维数组记忆： " << Solution3().minPathSum(grid) << endl;
  cout << "原数组修改： " << Solution4().minPathSum(grid) << endl;
  return 0;
}
