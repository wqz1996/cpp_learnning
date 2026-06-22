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
//面试题40. 数组中出现次数超过一半的数字
// 题目：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
//你可以假设数组是非空的，并且给定的数组总是存在多数元素。
/******************排序法*******************/
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int n = nums.size() / 2;
		return nums[n];

	}
};
/****************投票法*********************/
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		int times = 1;
		int res = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			if (res == nums[i])//res等于当前遍历的数字
				times++;//投一票
			else
				times--;//否则减一票
			if (times == 0){//当票数为0切换res为当前数字
				res = nums[i];
				times = 1;
			}
				
		}
		return res;//最后剩下的就是答案

	}
};
int main()
{
	vector<int> arr{ 0,1,2,1 };

	return 0;
}

