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
/*************416分割等和子集*****************************/
//给定只包含正整数的非空数组，将该数组分割成两个子集，
//使得两个子集元素和相等
class Solution {
private:
	vector<vector<int>> mem;//bool型两个状态不够用，需要判断mem[i][c]是否计算过
	//-1表示未计算，0表示不可以填充，1表示可以填充
	//使用nums[0....index]是否可以完全填充一个容量为sum的背包
	bool tryPatition(const vector<int>& nums, int index, int sum) {
		if (sum == 0)
			return true;

		if (sum < 0 || index < 0)//背包容量不够，或者物品已经用完了还没填满
			return false;

		if (mem[index][sum] != -1)
			return mem[index][sum] == 1;

		mem[index][sum] = (tryPatition(nums, index - 1, sum) || tryPatition(nums, index - 1, sum - nums[index])) ? 1 : 0;

		return  mem[index][sum]==1;
			


	}
public:
	bool canPartition(vector<int>& nums) {
		int sum = 0;
		
		for (int i = 0; i < nums.size(); i++) {//求解背包的总容量
			assert(nums[i] > 0);
			sum += nums[i];
		}

		if (sum % 2 != 0)//要求背包可以被平分，否则无法分割
			return false;

		mem = vector<vector<int>>(nums.size(), vector<int>((sum/2)+1, -1));
		
		return tryPatition(nums, nums.size() - 1, sum / 2);
	}
	/*************压缩空间一维dp**************/
	bool canPartitionDP(vector<int>& nums) {
		int sum = 0;

		for (int i = 0; i < nums.size(); i++) {//求解背包的总容量
			assert(nums[i] > 0);
			sum += nums[i];
		}

		if (sum % 2 != 0)//要求背包可以被平分，否则无法分割
			return false;

		int n = nums.size();
		int c = sum/2;
		vector<bool> mem(c+1, false);

		mem[0] = true;
		for (int i = 1; i < n; i++) {//从第二个物品开始放
			for (int j = c; j >= nums[i]; j--) {//从后向前放

				mem[j] = mem[j] || mem[j - nums[i]];

			}
		}

		return mem[c];



	}
};
/*********************二维dp***************/
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int sum = 0;
		int n = nums.size();
		for (int num : nums) {//求所有数字的和
			sum += num;
		}
		if (sum % 2 != 0)//和不能平分则一定不存在
			return false;
		int c = sum / 2;//转化为sum/2背包问题
		vector<vector<int>> dp(n + 1, vector<int>(c + 1, false));
		for (int i = 0; i <= n; i++) {//容量为0则一定为true
			dp[i][0] = true;
		}
		for (int i = 1; i <= n; i++) {//从第一个数字开始放
			for (int j = 1; j <= c; j++) {//剩余容量[1,c]
				if (j < nums[i - 1])//若剩余容量小于当前数字值则不能放进去
					dp[i][j] = false;
				else
					dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];//不放第i个数字||放第i个数字，且容量够用
			}
		}
		return dp[n][c];

	}
};
int main()
{
	vector<int> nums{ 1,5,11,5 };
	cout << Solution().canPartition(nums)<<endl;
	return 0;
}

