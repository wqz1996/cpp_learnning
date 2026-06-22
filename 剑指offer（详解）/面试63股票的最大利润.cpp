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
//面试题63. 股票的最大利润
// 假设把某股票的价格按照时间先后顺序存储在数组中，
//请问买卖该股票一次可能获得的最大利润是多少？
/***********************O(n^2)部分样例不通过**********************/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int maxprofit = 0;
		
		for (int i = 0; i < prices.size(); i++) {
			int minprice = prices[i];
			for (int j = i + 1; j < prices.size(); j++) {
				maxprofit = max(maxprofit, prices[j] - prices[i]);
			}
		}
		return maxprofit;
	}
};
/***********************修改**********************/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.empty())
			return 0;
		int maxprofit = 0;
		int minvalue = prices[0];
		for (int i = 0; i < prices.size(); i++) {
			minvalue = min(minvalue, prices[i]);//记录历史最小值
			maxprofit = max(maxprofit, prices[i] - minvalue);//在历史最小值买入，当前卖出记录收益
		}
		return maxprofit;		
	}
};
int main()
{
	vector<int> arr{ 7,1,5,3,6,4 };
	Solution().maxProfit(arr);
	return 0;
}

