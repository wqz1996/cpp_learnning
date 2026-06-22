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
/**********************448找出所有数组中消失的数字*************************/
//给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，
//数组中的元素一些出现了两次，另一些只出现一次。
//找到所有在 [1, n] 范围之间没有出现在数组中的数字。
/*********************额外空间O(N)***********************/
class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int>& nums) {
		int len = nums.size();
		vector<bool> board(len+1,false);//记录nums[i]是否出现过
		vector<int> res;
		if (len == 0)
			return res;
		for (int i = 0; i < len; i++) {
			board[nums[i]] = true;
		}
		for (int i = 1; i <= len; i++) {
			if (board[i] == false)//遍历寻找未出现的数字
				res.push_back(i);
		}
		return res;

	}
};
class Solution1 {
public:
	vector<int> findDisappearedNumbers(vector<int>& nums) {
	
		int len = nums.size();
		vector<int> res;
		if (len == 0)
			return res;
		for (int i = 0; i < len; i++) {
			if(nums[abs(nums[i]) - 1] > 0)//若该索引的数字未出现过
			nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];//将该索引的元素标记为负
		}
		for (int i = 0; i < len; i++) {
			if (nums[i] > 0)//未标记过的则是未出现过的元素索引
				res.push_back(i + 1);
		}
		return res;

	}
};
int main()
{
	vector<int> nums{ 1,3,3,4,4 };
	Solution1().findDisappearedNumbers(nums);
	return 0;
}

