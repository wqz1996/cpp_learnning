#include <algorithm> // 使用处：第 15 行的 min(
#include <vector> // 使用处：第 9 行的 vector
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


