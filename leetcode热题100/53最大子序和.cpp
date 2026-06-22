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
/****************53最大子序和***********************************/
//给定整数数组，寻找一个具有最大和的连续子数组，返回最大和
/************************动态规划O(N^2)**************************/
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int maxval = INT32_MIN;
		int len = nums.size();
		if (len == 1)
			return nums[0];
		if (len == 0)
			return 0;
		vector<vector<int>> dp(len,vector<int>(len,INT32_MIN));
		for (int i = 0; i < len; i++) {
			dp[i][i] = nums[i];
			maxval = max(maxval, dp[i][i]);
		}
		for (int i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				dp[i][j] = dp[i][j - 1] + nums[j];
				maxval = max(maxval, dp[i][j]);
			}
		}
		
		return maxval;
	}
};
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int len = nums.size();
		int maxval = nums[0];
		int pre = 0;
		for (int i = 0; i < len; i++) {//f(i)=max{f(i-1)+nums[i],nums[i]}
			pre = max(pre + nums[i], nums[i]);//pre为i-1结尾元素的最大和，判断是否使用保留前i-1的最大和
			maxval = max(maxval, pre);
		}
		return maxval;
	}
};
int main()
{
	vector<int> nums{ 1 };
	cout<<Solution().maxSubArray(nums);

	return 0;
}

