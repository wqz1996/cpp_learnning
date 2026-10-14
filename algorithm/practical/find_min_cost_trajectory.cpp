#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;
// 给定m*n 的grid，找到从左上角到右下角总的路径数
int totalPathNum(int m, int n) {
  vector<int> dp(n, 1);
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      dp[j] = dp[j] + dp[j - 1];
    }
  }
  return dp[n - 1];
}
// 基于上面的问题，带障碍物
int totalPathNumWithObstacle(vector<vector<int>> &grid) {
  if (grid.empty())
    return 0;
  int m = grid.size();
  int n = grid[0].size();

  vector<int> dp(n + 1, 0);
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
// 给定m*n 的grid，寻找从左上角到右下角的最小路径和
int minCost(vector<vector<int>> &grid) {
  int m = grid.size();
  int n = grid[0].size();

  vector<int> dp(grid[0]);
  for (int j = 0; j < n; j++)
    dp[j] = dp[j] + dp[j - 1];
  for (int i = 1; i < m; i++) {
    dp[0] = dp[0] + grid[i][0];
    for (int j = 1; j < n; j++) {
      dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
    }
  }
  return dp[n - 1];
}

// 对上一个问题的补充，如果带障碍物呢，带障碍物为inf
int minCostWithObstacle(vector<vector<int>> &grid) {
  int m = grid.size();
  int n = grid[0].size();

  vector<int> dp(n, INT_MAX);
  dp[0] = grid[0][0];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0)
        continue;

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

vector<pair<int, int>> minCostPathWithObstacle(vector<vector<int>> &grid) {
  if (grid.empty())
    return vector<pair<int, int>>{{-1, -1}};
  int m = grid.size();
  int n = grid[0].size();

  vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
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

vector<vector<char>> buildGrid(vector<vector<int>> &grid,
                               vector<pair<int, int>> &path) {
  int m = grid.size();
  int n = grid[0].size();
  vector<vector<char>> grid_with_path(m, vector<char>(n, '.'));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      grid_with_path[i][j] = grid[i][j] + '0';
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
