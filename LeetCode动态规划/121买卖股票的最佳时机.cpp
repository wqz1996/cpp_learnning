#include<algorithm>//包含堆操作
#include<iostream>
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
/****************121买卖股票的最佳时机*********************************/
/*****************暴力搜索************************/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int len = prices.size();
		int maxval = INT32_MIN;
		for (int i = 0; i < len-1; i++) {
			for (int j = len - 1; j > i; j--) {
				maxval = max(maxval, prices[j] - prices[i]);
			}
		}
		if (maxval <= 0)
			return 0;
		return maxval;
	}
};
/*****************动态规划************************/
class Solution1 {
public:
	int maxProfit(vector<int>& prices) {
		int len = prices.size();
		int maxval = INT32_MIN;
		if (len == 0)
			return 0;
		vector<vector<int>> dp(len, vector<int>(len, 0));
		for(int i=0;i<len;i++){
			dp[i][i] = 0;
		}
		for (int i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				dp[i][j] = max(dp[i][j - 1], prices[j] - prices[i]);
			}
		}
		for (int i = 0; i < dp.size(); i++) {
			for (int j = 0; j < dp[0].size(); j++) {
				maxval = max(maxval, dp[i][j]);
			}
		}
		return maxval;

	}
};
class Solution2 {
public:
	int maxProfit(vector<int>& prices) {
		int len = prices.size();
		int minval = INT32_MAX;
		int maxval = 0;
		for (int i = 0; i < len; i++) {
			maxval = max(maxval, prices[i] - minval);//在历史最小值买入，第i天卖出的收益
			minval = min(minval, prices[i]);//记录第i天以前的最小值，即历史最小值	

		}
		
		return maxval;
	}
};
int main()
{
	vector<int> arr{ 7,1,5,3,6,4 };
	cout << Solution1().maxProfit(arr)<<endl;

	return 0;
}

