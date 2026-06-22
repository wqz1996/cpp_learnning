#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
#include<string>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
#include<vector>//不注重插入和删除效率
#include<list>//类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include<deque>//双端队列，兼顾随即存取，和两端数据的插入删除
#include<ctime>
#include< unordered_map>
#include< unordered_set>
#include<hash_map>
#include<hash_set>
#include<assert.h>
#include<set>
#include<map>
using namespace std;
//现在有一个城市销售经理，需要从公司出发，去拜访市内的商家，已知他的位置以及商家的位置
//但是由于城市道路交通的原因，他只能在左右中选择一个方向，在上下中选择一个方向，现在问
//他有多少种方案到达商家地址。
//给定一个地图map及它的长宽n和m，其中1代表经理位置，2代表商家位置， - 1代表不能经过的
//地区，0代表可以经过的地区，请返回方案数，保证一定存在合法路径。保证矩阵的长宽都小于
//等于10。
class Visit {
public:
	int countPath(vector<vector<int>> map, int n, int m) {
		vector<vector<int>> dp(n, vector<int>(m, 0));
		int xb, yb, xe, ye;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 1) {//找到起始点
					xb = i;
					yb = j;
				}
				if (map[i][j] == 2) {//找到目标点
					xe = i;
					ye = j;
				}

			}
		}
		int detax = xe > xb ? 1 : -1;//确定增量方向
		int detay = ye > yb ? 1 : -1;
		for (int i = xb; i != xe + detax; i += detax) {
			for (int j = yb; j != ye + detay; j += detay) {
				if (i == xb && j == yb)
					dp[i][j] = 1;
				else if (i == xb)
					dp[i][j] = map[i][j] == -1 ? 0 : dp[i][j - detay];
				else if (j == yb)
					dp[i][j] = map[i][j] == -1 ? 0 : dp[i - detax][j];
				else
					dp[i][j] = map[i][j] == -1 ? 0 : dp[i - detax][j] + dp[i][j - detay];
			}

		}
		return dp[xe][ye];

	}
};
int main() {

	return 0;
}

