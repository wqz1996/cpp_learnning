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
/**************回溯法（不能通过）********************/
class Solution {
private:
	int res;
	vector<bool> used;
	int temp;
	void findway(vector<int>& nums, int S, int index) {		
		if (index == nums.size()) {
			if (temp == S) {//结果正好为S，则找到一个组合
				res++;				
			}
			return;			
		}
		if (!used[index]) {//每个元素只能用一次
			temp += nums[index];//选择‘+’
			used[index] = true;
			findway(nums, S, index + 1);
			temp -= nums[index];
			used[index] = false;

			temp -= nums[index];//选择‘-’
			used[index] = true;
			findway(nums, S, index + 1);
			temp += nums[index];
			used[index] = false;
		}
		
			
	}
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		if (nums.empty())
			return 0;
		res = 0;
		temp = 0;
		used = vector<bool>(nums.size(), false);		
		findway(nums, S, 0);
		return res;
	}
};
/*******************修改回溯，返回int*******************/
class Solution {
private:
	vector<bool> used;
	int temp;
	int findway(vector<int>& nums, int S, int index) {
		if (index == nums.size()) {
			if (temp == S) {//结果正好为S，则找到一个组合
				return 1;
			}
			return 0;
		}
		int res1,res2;
		if (!used[index]) {//每个元素只能用一次
			temp += nums[index];//选择‘+’
			used[index] = true;
			res1 = findway(nums, S, index + 1);
			temp -= nums[index];
			used[index] = false;

			temp -= nums[index];//选择‘-’
			used[index] = true;
			res2 = findway(nums, S, index + 1);
			temp += nums[index];
			used[index] = false;
		}
		return res1 + res2;
	}
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		if (nums.empty())
			return 0;
		temp = 0;
		used = vector<bool>(nums.size(), false);
		return findway(nums, S, 0);
		
	}
};
/*************记忆化搜索**********************/
class Solution {
private:
	unordered_map<string, int> mem;
	int findway(vector<int>& nums, int index, long S) {
		if (index == nums.size()) {
			if (S == 0) {
				return 1;
			}
			return 0;
		}
		string key = to_string(index) + "," + to_string(S);//用于记忆当前计算到的位置包括index和S值
		if (mem.find(key) != mem.end())
			return mem[key];
		int  result = findway(nums, index + 1, S - nums[index]) + findway(nums, index + 1, S + nums[index]);
		mem.insert({ key, result });
		return result;
	}
public:
	int findTargetSumWays(vector<int>& nums, long S) {//leetcode上S超过int范围修改为long
		if (nums.empty())
			return 0;
		return findway(nums, 0, S);
	}
};
/********************DP****************************/
//sum(A)-sum(B)=target
//sum(A)=target+sum(B)
//sum(A)+sum(A)=target+sum(A)+sum(B)
//sum(A)=(target+sum(nums))/2
//A是选‘+’B是选‘-’
//转化为nums中有多少个子集A使得和为(target+sum(nums))/2

class Solution {
private:
	int subset(vector<int> nums,int sum){
		vector<int> dp(sum + 1);//i为背包剩余容量，dp[i]是有多少个子集可以组成sum
		dp[0] = 1;
		for (int i = 0; i < nums.size(); i++) {
			for (int j = sum; j >= 0; j--) {
				if (j >= nums[i])
					dp[j] = dp[j] + dp[j - nums[i]];
				else
					dp[j] = dp[j];
			}
		}
		return dp[sum];

	}
public:
	int findTargetSumWays(vector<int>& nums, long S) {//leetcode上S超过int范围修改为long
		int sum = 0;
		for (int n : nums)//求所有元素的和
			sum += n;
		if (sum < S || (sum + S) % 2 == 1)//所有nums[i]加起来小于S则全是“+”也不能达到S
			return 0;					//sum+S不能平分也不行
		return subset(nums, (sum+S)/2);		
	}
};
int main() {

	vector<int> arr = { 1,1,1,1,1 };
	

	return 0;
}
