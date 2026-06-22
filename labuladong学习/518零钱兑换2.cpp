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
#include<assert.h>
#include<set>
#include<map>
using namespace std;
/************************零钱兑换2****************************/
//给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个
class Solution {
public:
	int change(int amount, vector<int>& coins) {
		int n = coins.size();
		vector<vector<int>> dp(n+1,vector<int>(amount+1,0));
		for (int i = 0; i <= n; i++) {
			dp[i][0] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= amount; j++) {
				if (j >= coins[i-1])//当前容量大于等于当前硬币
					dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];//不选i则由上一个硬币状态转移，选i则根据容量转移
				else
					dp[i][j] = dp[i - 1][j];//容量小于coins[i]，则不能选择i，由上一个硬币状态直接转移
			}
		}
		return dp[n][amount];
	}
};
/***************空间压缩********************/
class Solution {
public:
	int change(int amount, vector<int>& coins) {
		int n = coins.size();
		vector<int> dp(amount + 1);
		dp[0] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 1; j <= amount; j++) {
				if (j >= coins[i])
					dp[j] = dp[j] + dp[j - coins[i]];//当前剩余重量可以选i或不选i进行转移
			}
		}
		return dp[amount];
	}
};
/******************找零钱1**********************/
class Solution {
public:
	/*******暴力递归**********/
	int dp(vector<int>& coins, int amount) {
		if (amount == 0)
			return 0;
		if (amount < 0)
			return -1;
		int res = INT_MAX;
		for (int i = 0; i < coins.size(); i++) {
			int subproblem = dp(coins, amount - coins[i]);//分解为amount-coins[i]的子问题
			if (subproblem == -1)
				continue;
			res = min(res, subproblem + 1);
		}
		return res != INT_MAX ? res : -1;
	}
	int coinChange(vector<int>& coins, int amount) {
		if (coins.empty() || amount < 0)
			return -1;
		return dp(coins, amount);

	}
	/****************记忆化搜索***********************************/
	vector<int> mem;
	int dp(vector<int>& coins, int amount) {
		if (amount == 0)
			return 0;
		if (amount < 0)
			return -1;
		if (mem[amount] != -1)
			return mem[amount];
		int res = INT_MAX;
		for (int i = 0; i < coins.size(); i++) {
			int subproblem = dp(coins, amount - coins[i]);//分解为amount-coins[i]的子问题
			if (subproblem == -1)
				continue;
			res = min(res, subproblem + 1);

		}
		mem[amount] = res != INT_MAX ? res : -1;
		return mem[amount];
	}
	int coinChange(vector<int>& coins, int amount) {
		if (coins.empty() || amount < 0)
			return -1;
		mem = vector<int>(amount + 1, -1);
		return dp(coins, amount);

	}
	/*****************动态规划*************************/
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount + 1, amount + 1);
		dp[0] = 0;
		for (int i = 1; i <= amount; i++) {
			for (int j = 0; j < coins.size(); j++) {
				if (coins[j] <= i) {
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
				}
			}
		}
		return dp[amount] > amount ? -1 : dp[amount];

	}
};
int main() {

	
	return 0;
}
