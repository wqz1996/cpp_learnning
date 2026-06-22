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
//dp[i]->sum=i时最少的硬币数
//dp[i]=min(dp[i-coin[j]] + 1)
//j=[0,n-1]
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount + 1, amount + 1);//将所有初值赋最大amount+1为不可能的数字
		dp[0] = 0;
		for (int i = 1; i <= amount; i++) {
			for (int j = 0; j < coins.size(); j++) {
				if (coins[j] <= i)
					dp[i] = min(dp[i - coins[j]] + 1, dp[i]);
			}
		}
		return dp[amount] > amount ? -1 : dp[amount];//dp[amount]>amount则无法组成amount
	}
};
int main()
{

	 
	return 0;
}


