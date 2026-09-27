#include <stdexcept> // invalid_argument：Solution::numSquares 无解时抛出异常
#include <algorithm> // min：第 55 行首次使用
#include <iostream> // cout, endl：第 64 行首次使用
#include <queue> // queue：第 17 行首次使用
#include <vector> // vector：第 19 行首次使用
#include <cassert> // assert：第 16 行首次使用
#include <utility> // pair, make_pair：第 17 行首次使用
using namespace std;
/************279完全平方数*******************/
//给定正整数n，找到若干个完全平方数（1，4，9，16。。。）
//使得它们的和等于n，使得完全平方数个数最少
//提示：无权图
class Solution {
public:
	int numSquares(int n) {
		assert(n > 0);
		queue<pair<int, int>> q;//第一个int表示第几个数字，第二个int表示图中经历了多少路径
		q.push(make_pair(n, 0));
		vector < bool > visited(n + 1, false);
		visited[n] = true;//判断该数字是否访问过
		while (!q.empty()) {//广度优先遍历
			int num = q.front().first;//数字
			int step = q.front().second;//走的步数
			q.pop();
			
			for (int i = 1;; i++) {//
				int a = num - i * i;
				if (a < 0)
					break;
				if (a == 0)
					return step + 1;
					if (!visited[a]) {
						q.push(make_pair(a, step + 1));
						visited[a] = true;
					}
							
			}


		}
		throw invalid_argument("No Solution");


	}
};
// 动态规划解法，转化为0-1背包问题
class Solution1 {
public:
    int numSquares(int n) {
		vector<int> dp(n+1,0); // 代表从0-n每个数字所需要的最小组成数量
        for(int i = 1; i<=n; i++){ // 从前到后的顺序来递推
			dp[i] = i; // 最差就是全用1来组成，这样所需的数量最大
            for(int j = 1; i-j*j >=0;j++){
                // 转化为0-1背包问题，i - j*j 来遍历之前的完全平方数所需最小的组成数量，1为代价，即每次增加一个数量
                dp[i] = min(dp[i], dp[i-j*j] +1);
            }
        }
        return dp[n];
    }
};

int main()
{
    cout << "广度优先搜索: " << Solution().numSquares(12) << endl;
    cout << "动态规划: " << Solution1().numSquares(12) << endl;
    return 0;
}
