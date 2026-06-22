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
//面试题57. 和为s的两个数字
// 题目：输入一个递增排序的数组和一个数字s，在数组中查找两个数，
//使得它们的和正好是s。如果有多对数字的和等于s，则输出任意一对即可。
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> res;
		if (nums.size() == 1)
			return res;
		int p1 = 0;
		int p2 = nums.size()-1;
		while (p1 < p2) {
			int sum = nums[p1] + nums[p2];
			if (sum == target) {
				res.push_back(nums[p1]);
				res.push_back(nums[p2]);
				break;
			}
			else if (sum < target) {//和大于target左指针移动一位
				p1++;
			}
			else {//和小于target右指针移动一位
				p2--;
			}
		}
		return res;
	}
};
int main()
{
	vector<int> arr{ 2,7,11,15 };
	Solution().twoSum(arr,9);
	return 0;
}

