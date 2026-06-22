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
//面试题53 - I. 在排序数组中查找数字 I
// 题目：统计一个数字在排序数组中出现的次数。
/*****************传统办法*****************/
class Solution {
public:
	int search(vector<int>& nums, int target) {
		int count = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == target)
				count++;
		}
		return count;
	}
};
/*****************二分法1 O（n/2）*****************/
class Solution {
public:
	int search(vector<int>& nums, int target) {
		if (nums.empty())
			return 0;
		int p1 = 0;
		int p2 = nums.size() - 1;
		while (p1 <= p2) {
			if (nums[p1] == target && nums[p2] == target) {//计算两个target之间的长度即为出现次数
				return p2 - p1 + 1;
			}
			p1 = nums[p1] < target ? ++p1 : p1;
			p2 = nums[p2] > target ? --p2 : p2;

		}
		return 0;
	}
};
/*****************二分法递归方法写二分*****************/
class Solution2 {
private:
	int searchfirsttarget(vector<int>& nums, int target, int left, int right) {
		if (left > right)//没找到第一个target返回-1
			return -1;
		int mid = left - (left - right) / 2;
		if (nums[mid] < target) {//中间的小于target，target在右半部分
			left = mid + 1;
		}
		else if (nums[mid] > target) {//在左半部分
			right = mid - 1;
		}
		else {
			if (mid > 0 && nums[mid - 1] != target || mid == 0)//判断是否是第一个target
				return mid;//返回第一个target索引
			else
				right = mid - 1;//第一个在左半部分
		}
		return searchfirsttarget(nums, target, left, right);

	}
	int searchlasttarget(vector<int>& nums, int target, int left, int right) {
		if (left > right)
			return -1;
		int mid = left - (left - right) / 2;
		if (nums[mid] < target) {
			left = mid + 1;
		}
		else if (nums[mid] > target) {
			right = mid - 1;
		}
		else {
			if (mid < nums.size() - 1 && nums[mid + 1] != target || mid == nums.size() - 1)
				return mid;//
			else
				left = mid + 1;
		}
		return searchlasttarget(nums, target, left, right);

	}
public:
	int search(vector<int>& nums, int target) {
		if (nums.empty())
			return 0;
		int res = 0;
		int start = searchfirsttarget(nums, target, 0, nums.size() - 1);//二分查找第一个target
		int end = searchlasttarget(nums, target, 0, nums.size() - 1);//二分查找最后一个target
		if (start > -1 && end > -1)//判断是否存在target
			res = end - start + 1;
		return res;
	}
};
/******************二分法架构方便理解 O(logn)*******************/
class Solution {
private:
	int findleftbound(vector<int> num, int target) {
		int left = 0;
		int right = num.size() - 1;
		while (left <= right) {
			int mid = left + ((right - left) >> 1);
			if (num[mid] < target)
				left = mid + 1;
			else if (num[mid] > target)
				right = mid - 1;
			else if (num[mid] == target) {
				if (mid == 0 || (mid > 0 && num[mid - 1] != target))//防止mid-1越界
					return mid;
				else
					right = mid - 1;
			}
		}
		if (left > right)//left>right则不存在target
			return -1;
		return left;
	}
	int findrightbound(vector<int> num, int target) {
		int left = 0;
		int right = num.size() - 1;
		while (left <= right) {
			int mid = left + ((right - left) >> 1);
			if (num[mid] < target)
				left = mid + 1;
			else if (num[mid] > target)
				right = mid - 1;
			else if (num[mid] == target) {
				if (mid == num.size() - 1 || (mid < num.size() - 1 && num[mid + 1] != target))
					return mid;
				else
					left = mid + 1;
			}
		}
		if (left > right)
			return -1;
		return right;
	}
public:
	int search(vector<int>& nums, int target) {
		int start = findleftbound(nums, target);
		int end = findrightbound(nums, target);
		if (start != -1 && end != -1)
			return end - start + 1;
		return 0;
	}
};
int main()
{
	vector<int> arr{ 5,7,7,8,8,10 };
	Solution2().search(arr, 6);
	return 0;
}

