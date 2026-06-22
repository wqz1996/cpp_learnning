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
//买卖股票121一次122无数次123两次，188k次
//第一题是只进行一次交易，相当于 k = 1；第二题是不限交易次数，相当于 k = +infinity（正无穷）；第三题是只进行 2 次交易，相当于 k = 2；剩下两道也是不限次数，但是加了交易「冷冻期」和「手续费」的额外条件，其实就是第二题的变种，都很容易处理。
//dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
/*
max(选择 rest, 选择 sell)

解释：今天我没有持有股票，有两种可能：
要么是我昨天就没有持有，然后今天选择 rest，所以我今天还是没有持有；
要么是我昨天持有股票，但是今天我 sell 了，所以我今天没有持有股票了。

dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i])
max(选择 rest, 选择 buy)

解释：今天我持有着股票，有两种可能：
要么我昨天就持有着股票，然后今天选择 rest，所以我今天还持有着股票；
要么我昨天本没有持有，但今天我选择 buy，所以今天我就持有股票了。

初始状态
dp[-1][k][0] = 0
解释：因为 i 是从 0 开始的，所以 i = -1 意味着还没有开始，这时候的利润当然是 0 。
dp[-1][k][1] = -infinity
解释：还没开始的时候，是不可能持有股票的，用负无穷表示这种不可能。
dp[i][0][0] = 0
解释：因为 k 是从 1 开始的，所以 k = 0 意味着根本不允许交易，这时候利润当然是 0 。
dp[i][0][1] = -infinity
解释：不允许交易的情况下，是不可能持有股票的，用负无穷表示这种不可能。
*/

/******买卖k次股票问题********/
class Solution {
public:
	//k==1
	int maxProfit1(vector<int>& prices) {
		int n = prices.size();
		// base case
		int dp_i_0 = 0, dp_i_1 = INT_MIN;
		// dp_i_0: 第i天的最大利润, 0表示不持有股票
		// dp_i_1: 第i天的最大利润, 1表示持有股票

		for (int i = 1; i <= n; i++) {
			// 如果今天不持有股票，表示昨天也不持有股票或是今天卖掉了股票
			dp_i_0 = max(dp_i_0, dp_i_1 + prices[i - 1]);
			// 如果今天持有股票，表示昨天就持有股票或是今天买了股票
			dp_i_1 = max(dp_i_1, -prices[i - 1]);
		}
		return dp_i_0;
	}
	//k==+INF
	int maxProfit2(vector<int>& prices) {
		int n = prices.size();
		// base case
		int dp_i_0 = 0, dp_i_1 = INT_MIN;
		// dp_i_0: 第i天的最大利润, 0表示不持有股票
		// dp_i_1: 第i天的最大利润, 1表示持有股票

		for (int i = 1; i <= n; i++) {
			int temp = dp_i_0;
			// 如果今天不持有股票，表示昨天也不持有股票或是今天卖掉了股票
			dp_i_0 = std::max(dp_i_0, dp_i_1 + prices[i - 1]);
			// 如果今天持有股票，表示昨天就持有股票或是今天买了股票
			dp_i_1 = std::max(dp_i_1, temp - prices[i - 1]);
		}

		return dp_i_0;
	}
	//k=+INF with cooldown
	int maxProfit3(vector<int>& prices) {
		int n = prices.size();
		// base case
		// dp_i_0: 第i天的最大利润, 0表示不持有股票
		// dp_i_1: 第i天的最大利润, 1表示持有股票
		int dp_i_0 = 0, dp_i_1 = INT_MIN;
		// 表示第(i-2)天的最大利润，并且未持有股票
		int prev_dp_i_0 = 0;
		for (int i = 1; i <= n; i++) {
			// temp和prev_dp_i_0用来记录第(i-2)天(前天)的最大利润
			int temp = dp_i_0;
			// 如果今天不持有股票，表示昨天也不持有股票或是今天卖掉了股票
			dp_i_0 = std::max(dp_i_0, dp_i_1 + prices[i - 1]);
			// 如果今天持有股票，表示昨天就持有股票或是今天买了股票
			dp_i_1 = std::max(dp_i_1, prev_dp_i_0 - prices[i - 1]);
			prev_dp_i_0 = temp;
		}
		return dp_i_0;
	}
	//k==+INF with fee
	int maxProfit4(vector<int>& prices, int fee) {
		int n = prices.size();
		// base case
		int dp_i_0 = 0, dp_i_1 = INT_MIN;
		// dp_i_0: 第i天的最大利润, 0表示不持有股票
		// dp_i_1: 第i天的最大利润, 1表示持有股票

		for (int i = 1; i <= n; i++) {
			int temp = dp_i_0;
			// 如果今天不持有股票，表示昨天也不持有股票或是今天卖掉了股票
			dp_i_0 = std::max(dp_i_0, dp_i_1 + prices[i - 1]);
			// 如果今天持有股票，表示昨天就持有股票或是今天买了股票
			//tips:为什么不在卖股票的时候减掉transaction fee？因为在base case中， dp_i_1 == INT_MIN, INT_MIN + prices[i] - fee 可能会造成整型溢出
			dp_i_1 = std::max(dp_i_1, temp - prices[i - 1] - fee);
		}
		return dp_i_0;
	}
	//k==2
	int maxProfit5(vector<int>& prices) {
		int size = prices.size();
		int max_k = 2;

		// i从1开始而不是0，这样可以使base case是 dp[0][0][0] 和 dp[0][0][1] 而不是 dp[-1][0][0] 或者 dp[-1][0]
		vector<vector<vector<int>>> dp(size + 1, vector<vector<int>>(max_k + 1, vector<int>(2)));

		// 初始化
		for (int k = max_k; k >= 0; k--) {
			dp[0][k][0] = 0;
			dp[0][k][1] = INT_MIN;
		}

		for (int i = 1; i <= size; i++) {
			dp[i][0][0] = 0;
			dp[i][0][1] = INT_MIN;
			for (int k = max_k; k >= 1; k--) {
				dp[i][k][0] = std::max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i - 1]);
				dp[i][k][1] = std::max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i - 1]);
			}
		}
		return dp[size][max_k][0];
	}
	//k==any int
	int maxProfit6(int k, vector<int>& prices) {
		int size = prices.size();


		// i从1开始而不是0，这样可以使base case是 dp[0][0][0] 和 dp[0][0][1] 而不是 dp[-1][0][0] 或者 dp[-1][0][1]
		vector<vector<vector<int>>> dp(size + 1, vector<vector<int>>(k + 1, vector<int>(2)));

		// 初始化
		for (int j = k; j >= 0; j--) {
			dp[0][j][0] = 0;
			dp[0][j][1] = INT_MIN;
		}

		for (int i = 1; i <= size; i++) {
			dp[i][0][0] = 0;
			dp[i][0][1] = INT_MIN;
			for (int j = k; j >= 1; j--) {
				dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
				dp[i][j][1] = std::max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i - 1]);
			}
		}
		return dp[size][k][0];
	}

};
int main()
{
	vector<int> nums{ -2,3,-4 };

	return 0;
}


