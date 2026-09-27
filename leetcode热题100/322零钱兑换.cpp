#include <algorithm> // min：第 12 行首次使用
#include <vector> // vector：第 6 行首次使用
using namespace std;
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount + 1,amount + 1);//所有值初始化超过amount的不可能值，在coins[j]>i时直接跳过，保证值为
		dp[0] = 0;
		for (int i = 1; i <= amount; i++) {
			for (int j = 0; j < coins.size(); j++) {
				if (coins[j] <= i)//跳过不合法索引
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
			}
		}
		return dp[amount]>amount?-1:dp[amount];
	}
};
int main()
{
	vector<int> coins = { 1,2,5 };
	Solution().coinChange(coins, 11);

	return 0;
}

