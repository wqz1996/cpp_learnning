/*
 * @lc app=leetcode.cn id=773 lang=cpp
 * @lcpr version=30404
 *
 * [773] 滑动谜题
 * https://leetcode.cn/problems/sliding-puzzle/description/
 */

// @lc code=start
class Solution {
public:
  int slidingPuzzle(vector<vector<int>> &board) {
    if (board.empty())
      return -1;
    row = board.size();
    col = board[0].size();
    string target = "123450";
    string start;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        start += to_string(board[i][j]);
      }
    }
    //记录
    unordered_set<string> visited;
    queue<string> q;
    q.push(start);
    visited.insert(start);
    int step = 0;
    while (!q.empty()) {
      int sz = q.size();
      for (int i = 0; i < sz; i++) {
        string cur = q.front();
        q.pop();
        if (cur == target) {
          return step;
        }
        for (string nextboard : getNextBoard(cur)) {
          if (!visited.count(nextboard)) {
            q.push(nextboard);
            visited.insert(nextboard);
          }
        }
      }
      step++;
    }
    return -1;
  }

private:
  int row, col;
  vector<string> getNextBoard(string board) {
    // 生成每个位置所有邻居索引
    vector<vector<int>> neiborIndexs = generateNeiborIdx(row, col);
    // 找到0的索引位置
    int idx = board.find('0');
    vector<string> nextboards;
    // 遍历所有可能的交换方式，分别与各邻居进行交换
    for (int neiborIndex : neiborIndexs[idx]) {
      string nextboard = swap(board, idx, neiborIndex);
      nextboards.push_back(nextboard);
    }
    return nextboards;
  }
  //生成m*n的二维数组各个位置的上下左右相邻元素的索引，对应在一维数组中的索引
  vector<vector<int>> generateNeiborIdx(int m, int n) {
    vector<vector<int>> neiborIndexs;

    for (int i = 0; i < m * n; i++) {
      vector<int> neiborIndex;
      // 不是第一列则有左邻居
      if (i % n != 0)
        neiborIndex.push_back(i - 1);
      // 不是最后一列则有右邻居
      if (i % n != n - 1)
        neiborIndex.push_back(i + 1);
      // 不是第一行则有上面邻居
      if (i - n >= 0)
        neiborIndex.push_back(i - n);
      // 不是最后一行则有下面邻居
      if (i + n < m * n)
        neiborIndex.push_back(i + n);
      neiborIndexs.push_back(neiborIndex);
    }
    return neiborIndexs;
  }
  string swap(string board, int i, int j) {
    char temp = board[i];
    board[i] = board[j];
    board[j] = temp;
    return board;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [[1,2,3],[4,0,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3],[5,4,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[4,1,2],[5,0,3]]\n
// @lcpr case=end

 */
