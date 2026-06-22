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
//面试题53 - II. 0～n-1中缺失的数字
// 题目：一个长度为n-1的递增排序数组中的所有数字都是唯一的，
//并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中
//有且只有一个数字不在该数组中，请找出这个数字。
class Solution {
public:
	int missingNumber(vector<int>& nums) {
		int left = 0, right = nums.size();//为了判断只有一个元素的情况
		while (left < right) {
			int mid = left - (left - right) / 2;
			if (nums[mid] == mid)//中间相等则缺失的在右半部分
				left = mid + 1;
			else//否则在左半部分
				right = mid;
		}
		return left;
	}
};
int main()
{
	vector<int> arr{ 0 };
	cout<<Solution().missingNumber(arr);
	return 0;
}

