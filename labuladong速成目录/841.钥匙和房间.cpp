/*
 * @lc app=leetcode.cn id=841 lang=cpp
 * @lcpr version=30404
 *
 * [841] 钥匙和房间
 * https://leetcode.cn/problems/keys-and-rooms/description/
 */

// @lc code=start
class Solution {
public:
  bool canVisitAllRooms(vector<vector<int>> &rooms) {
    int n = rooms.size();
    vector<bool> visited(n, false);
    visited[0] = true;
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
      int sz = q.size();
      for (int i = 0; i < sz; i++) {
        int cur = q.front();
        q.pop();
        for (int room : rooms[cur]) {
          if (!visited[room]) {
            visited[room] = true;
            q.push(room);
          }
        }
      }
    }
    for (bool v : visited) {
      if (!v) {
        return false;
      }
    }
    return true;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [[1],[2],[3],[]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,3],[3,0,1],[2],[0]]\n
// @lcpr case=end

 */
