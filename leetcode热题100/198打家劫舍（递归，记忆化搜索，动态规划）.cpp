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
/*************198打家劫舍******************/
//沿街偷窃所有房屋，每个房间有一定量现金
//不能同一晚偷相邻的房间
//计算一夜之内的最高金额
//例[3,4,1,2]->6
//函数定义[x...n-1]的房子
//状态转移方程
//f(0)=max{v(0)+f(1),v(1)+f(3),v(2)+f(4),.....,v(n-3)+f(n-1),v(n-2)+0,v(n-1)+0}
/*****************暴力递归**********************/
class Solution {
private:
	int findrob(vector<int>& nums, int index) {
		if (index >= nums.size())
			return 0;
		return max((nums[index] + findrob(nums, index + 2)), findrob(nums, index + 1));//抢劫当前家则要隔一家再抢，否则到下一家进行递归

	}
public:
	int rob(vector<int>& nums) {
		return findrob(nums, 0);
	}
};
/***************记忆化搜索**************/
class Solution {
private:
	vector<int> mem;
	int findrob(vector<int>& nums, int index) {
		if (index >= nums.size())
			return 0;
		if (mem[index] != -1)
			return mem[index];
		mem[index] = max((nums[index] + findrob(nums, index + 2)), findrob(nums, index + 1));
		return mem[index];

	}
public:
	int rob(vector<int>& nums) {
		mem = vector<int>(nums.size(), -1);
		return findrob(nums, 0);
	}
};
/***************动态规划************************/
class Solution {
public:
	int rob(vector<int>& nums) {
		int n = nums.size();
		vector<int> dp(n + 2, 0);//dp[i]表示从第i间开始抢最大的收益
		//base case dp[n]=0;
		if (nums.empty())
			return 0;
		for (int i = n - 1; i >= 0; i--) {
			dp[i] = max(dp[i + 1], nums[i] + dp[i + 2]);
		}
		return dp[0];

	}
};
/***************动态规划空间优化************************/
class Solution {
public:
	int rob(vector<int>& nums) {
		int n = nums.size();
		int dp_i_1 = 0, dp_i_2 = 0, dp_i = 0;
		if (nums.empty())
			return 0;
		for (int i = n - 1; i >= 0; i--) {
			dp_i = max(dp_i_1, nums[i] + dp_i_2);
			dp_i_2 = dp_i_1;
			dp_i_1 = dp_i;
		}
		return dp_i;

	}
};
class Solution {
private:
	vector<int> mem;//抢劫nums[i...n]范围的房子获得的最大收益
	//nums[index...nums.size()]范围的房子
	int tryRob(vector<int>& nums,int index) {
		if (index >= nums.size())//递归终止条件
			return 0;
		int res=0;
		if (mem[index] != -1)//是否解决过index问题
			return mem[index];
		for (int i = index; i < nums.size(); i++) {
			res=max(res,nums[i] + tryRob(nums, i + 2));
		}
		mem[index] = res;
		return res;
	}
public:
	int rob(vector<int>& nums) {
		mem = vector<int>(nums.size(), -1);
		return tryRob(nums,0);
	}
};
class Solution {
public:
	int rob(vector<int>& nums) {
		int n = nums.size();
		vector<int> mem(n, -1);
		if (n == 0)//n-1要大于等于1，解决n=0的特殊情况
			return 0;
		mem[n - 1] = nums[n - 1];//总问题是mem[0],初始条件为mem[n-1]
		for (int i = n - 2; i >= 0; i--) {//从下向上分析
			for (int j = i; j < n; j++) {//[i...n-1]的房子
				mem[i] = max(mem[i], nums[j] + (j+2<n? mem[j + 2]:0)); //(j + 2 < n ? mem[j + 2] : 0)保证j+2不越界
			}
		}
		return mem[0];
	}
};

int main()
{
	
	return 0;

}

