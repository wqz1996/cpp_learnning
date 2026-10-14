#include <algorithm> // 使用处：第 25 行的 min(
#include <iostream> // 使用处：第 34 行的 cout
#include <vector> // 使用处：第 15 行的 vector

// #include< unordered_map>
// #include< unordered_set>
#include <climits> // 使用处：第 15 行的 INT_MAX

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
