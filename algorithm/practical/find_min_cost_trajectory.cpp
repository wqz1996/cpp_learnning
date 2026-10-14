// 原理总结：网格路径问题可用动态规划，假设每步只能向右或向下。
// 路径数 = 上方路径数 + 左方路径数；最小费用 = 当前费用 + 两个前驱中的较小值。
// 一维 dp 可节省空间；需要输出路线时，用二维表记录每格的最优前驱再反向回溯。
// 障碍用 1（计数问题）或 INT_MAX（费用问题）表示，具体见各函数说明。
#include <utility>
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;
// 无障碍的 m×n 网格：dp[j] 更新前是上方路径数，dp[j-1] 是左方路径数。
int totalPathNum(int m, int n) {
  vector<int> dp(n, 1);
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      dp[j] = dp[j] + dp[j - 1];
    }
  }
  return dp[n - 1];
}
// grid 中 1 表示障碍；遇到障碍时，该格的路径数归零。
int totalPathNumWithObstacle(vector<vector<int>> &grid) {
  if (grid.empty())
    return 0;
  int m = grid.size();
  int n = grid[0].size();

  vector<int> dp(n + 1, 0); // 多留一个 0，简化第一列的边界处理。
  dp[1] = grid[0][0] == 1 ? 0 : 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (grid[i - 1][j - 1] == 1)
        dp[j] = 0;
      else
        dp[j] = dp[j] + dp[j - 1];
    }
  }
  return dp[n];
}
// 无障碍时的最小路径和：dp[j] 始终保存到当前格的最小费用。
int minCost(vector<vector<int>> &grid) {
  int m = grid.size();
  int n = grid[0].size();

  vector<int> dp(grid[0]);
  // 第一行只能从左侧到达，首格本身不需要累加。
  for (int j = 1; j < n; j++)
    dp[j] = dp[j] + dp[j - 1];
  for (int i = 1; i < m; i++) {
    dp[0] = dp[0] + grid[i][0];
    for (int j = 1; j < n; j++) {
      dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
    }
  }
  return dp[n - 1];
}

// INT_MAX 表示障碍或不可达；返回 -1 表示终点不可达。
int minCostWithObstacle(vector<vector<int>> &grid) {
  int m = grid.size();
  int n = grid[0].size();

  vector<int> dp(n, INT_MAX);
  dp[0] = grid[0][0];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0)
        continue;

      // 只有前驱可达且当前格不是障碍时，才能转移费用。
      int fromleft = INT_MAX, fromup = INT_MAX;
      if (i > 0 && grid[i][j] != INT_MAX && dp[j] != INT_MAX)
        fromup = dp[j] + grid[i][j];
      if (j > 0 && grid[i][j] != INT_MAX && dp[j - 1] != INT_MAX)
        fromleft = dp[j - 1] + grid[i][j];
      dp[j] = min(fromleft, fromup);
    }
  }
  return dp[n - 1] != INT_MAX ? dp[n - 1] : -1;
}

// 记录最优前驱坐标，再从终点回溯得到具体路径；不可达时返回空路径。
vector<pair<int, int>> minCostPathWithObstacle(vector<vector<int>> &grid) {
  if (grid.empty())
    return {};
  int m = grid.size();
  int n = grid[0].size();

  vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
  // came_from[i][j] 保存到达 (i,j) 的最优前驱。
  vector<vector<pair<int, int>>> came_from(m,
                                           vector<pair<int, int>>(n, {-1, -1}));

  dp[0][0] = grid[0][0];

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0 || grid[i][j] == INT_MAX)
        continue;
      int fromleft = INT_MAX, fromup = INT_MAX;
      if (i > 0 && dp[i - 1][j] != INT_MAX) {
        fromup = dp[i - 1][j] + grid[i][j];
      }
      if (j > 0 && dp[i][j - 1] != INT_MAX) {
        fromleft = dp[i][j - 1] + grid[i][j];
      }

      if (fromleft < fromup) {
        dp[i][j] = fromleft;
        came_from[i][j] = {i, j - 1};
      } else if (fromup < INT_MAX) {
        dp[i][j] = fromup;
        came_from[i][j] = {i - 1, j};
      }
    }
  }

  vector<pair<int, int>> path;
  if (dp[m - 1][n - 1] == INT_MAX)
    return path;

  // 回溯得到的是逆序路径，最后再翻转。
  for (int i = m - 1, j = n - 1; i >= 0 && j >= 0;) {
    path.push_back({i, j});
    pair<int, int> pre = came_from[i][j];
    i = pre.first;
    j = pre.second;
    if (i == -1 && j == -1)
      break;
  }
  reverse(path.begin(), path.end());
  return path;
}

// 将路径标记为 #；示例仅适合显示 0～9 的单数字格值。
vector<vector<char>> buildGrid(vector<vector<int>> &grid,
                               vector<pair<int, int>> &path) {
  int m = grid.size();
  int n = grid[0].size();
  vector<vector<char>> grid_with_path(m, vector<char>(n, '.'));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      grid_with_path[i][j] = grid[i][j] == INT_MAX ? 'X' : grid[i][j] + '0';
    }
  }
  for (pair<int, int> p : path) {
    grid_with_path[p.first][p.second] = '#';
  }
  return grid_with_path;
}
int main() {
  vector<vector<int>> grid_with_obstacle = {
      {1, 3, 1}, {1, 5, INT_MAX}, {4, 2, 1}};
  vector<pair<int, int>> res = minCostPathWithObstacle(grid_with_obstacle);
  cout << "res.size: " << res.size() << endl;
  cout << "path: " << endl;
  for (pair<int, int> &p : res) {
    cout << p.first << ',' << p.second << ' ';
  }
  cout << endl;

  vector<vector<char>> grid_with_path = buildGrid(grid_with_obstacle, res);

  cout << "Path in grid" << endl;

  for (vector<char> row : grid_with_path) {
    for (char col : row) {
      cout << col << ' ';
    }
    cout << endl;
  }
  return 0;
}
