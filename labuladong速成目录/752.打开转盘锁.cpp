/*
 * @lc app=leetcode.cn id=752 lang=cpp
 * @lcpr version=30404
 *
 * [752] 打开转盘锁
 * https://leetcode.cn/problems/open-the-lock/description/
 */

// @lc code=start
class Solution {
public:
  unordered_set<string> visited;
  int openLock(vector<string> &deadends, string target) {
    int step = 0;
    queue<string> q;
    q.push("0000");
    for (string d : deadends) {
      visited.insert(d);
    }
    // 如果起点已经在死亡密码里，必然无解
    if (visited.count("0000"))
      return -1;
    while (!q.empty()) {
      int sz = q.size();
      for (int i = 0; i < sz; i++) {
        string cur = q.front();
        q.pop();
        if (cur == target) {
          return step;
        }
        for (string neibor : getNeibors(cur)) {
          if (!visited.count(neibor)) {
            visited.insert(neibor);
            q.push(neibor);
          }
        }
      }
      step++;
    }
    return -1;
  }

private:
  // 向上转动第i位数字
  string plusOne(string s, int i) {
    if (s[i] == '9') {
      s[i] = '0';
    } else {
      s[i] += 1;
    }
    return s;
  }
  // 向下转动第i位数字
  string minusOne(string s, int i) {
    if (s[i] == '0') {
      s[i] = '9';
    } else {
      s[i] -= 1;
    }
    return s;
  }
  vector<string> getNeibors(string s) {
    vector<string> neibors;
    for (int i = 0; i < 4; i++) {
      neibors.push_back(plusOne(s, i));
      neibors.push_back(minusOne(s, i));
    }
    return neibors;
  }
};
// @lc code=end

/*
// @lcpr case=start
// ["0201","0101","0102","1212","2002"]\n"0202"\n
// @lcpr case=end

// @lcpr case=start
// ["8888"]\n"0009"\n
// @lcpr case=end

// @lcpr case=start
// ["8887","8889","8878","8898","8788","8988","7888","9888"]\n"8888"\n
// @lcpr case=end

 */
