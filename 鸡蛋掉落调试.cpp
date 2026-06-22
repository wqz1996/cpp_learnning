#include <algorithm> //包含堆操作
#include <cmath>
#include <ctime>
#include <deque> //双端队列，兼顾随即存取，和两端数据的插入删除
#include <iostream>
#include <list> //类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include <queue>   //队列
#include <sstream> //istringstream 可以将string以空格为分隔符分割
#include <stack>   //栈
#include <string>
#include <vector> //不注重插入和删除效率

// #include< unordered_map>
// #include< unordered_set>
#include <assert.h>
#include <climits>
#include <map>
#include <set>

using namespace std;
//鸡蛋掉落
// dp[i][j],i=[0,k],j=[0,N]
class Solution {
public:
  int superEggDrop(int K, int N) {
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, INT_MAX));
    for (int i = 0; i <= K; i++) {
      dp[i][0] = 0; // N=0,k>=2,都为0
    }
    for (int j = 0; j <= N; j++) {
      dp[1][j] = j; // k=1,必须线性搜索因此次数为N
    }

    for (int j = 1; j <= N; j++) {
      for (int i = j; i <= K; i++) {
        dp[i][j] = min(dp[i][j], max(dp[i - 1][j - 1], dp[i][j - i]) + 1);
      }
    }
    return dp[K][N];
  }
};
int main() {

  // Solution().superEggDrop(3, 14);
  cout << Solution().superEggDrop(3, 14);
  return 0;
}
