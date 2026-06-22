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
//面试题51. 数组中的逆序对
// 题目：在数组中的两个数字，如果前面一个数字大于后面的数字，
//则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
/***************O(N^2)(部分无法通过)************************/
class Solution {
public:
	int reversePairs(vector<int>& nums) {
		if (nums.empty()|| nums.size() == 1)
			return 0;
		int count = 0;
		for (int i = 0; i < nums.size()-1; i++) {
			for (int j = i+1; j < nums.size(); j++) {
				if (nums[j] < nums[i])
					count++;
			}
		}
		return count;
	}
};
/****************优化方法**********************/
class Solution {
public:
	int mergeSort(vector<int>& nums, vector<int>& tmp, int l, int r) {
		if (l >= r) {
			return 0;
		}

		int mid = (l + r) / 2;
		int inv_count = mergeSort(nums, tmp, l, mid) + mergeSort(nums, tmp, mid + 1, r);
		int i = l, j = mid + 1, pos = l;
		while (i <= mid && j <= r) {
			if (nums[i] <= nums[j]) {
				tmp[pos] = nums[i];
				++i;
				inv_count += (j - (mid + 1));
			}
			else {
				tmp[pos] = nums[j];
				++j;
			}
			++pos;
		}
		for (int k = i; k <= mid; ++k) {
			tmp[pos++] = nums[k];
			inv_count += (j - (mid + 1));
		}
		for (int k = j; k <= r; ++k) {
			tmp[pos++] = nums[k];
		}
		copy(tmp.begin() + l, tmp.begin() + r + 1, nums.begin() + l);
		return inv_count;
	}

	int reversePairs(vector<int>& nums) {
		int n = nums.size();
		vector<int> tmp(n);
		return mergeSort(nums, tmp, 0, n - 1);
	}
};
class Solution {
public:
	int global_count = 0;
	int reversePairs(vector<int>& nums) {
		vector<int> copyarr(nums.size(), 0);
		merge_sort(nums, copyarr, 0, nums.size() - 1);
		return global_count;
	}

	void merge_sort(vector<int>& nums, vector<int>& copyarr, int left, int right) {
		if (left >= right) return;
		int mid = (left + right) / 2;
		merge_sort(nums, copyarr, left, mid);
		merge_sort(nums, copyarr, mid + 1, right);
		int i = left, j = mid + 1, k = left;
		while (i <= mid && j <= right) {
			if (nums[j] < nums[i]) {
				copyarr[k++] = nums[j++];
				global_count += (mid - i + 1);         // 关键点，也是归并排序添加的唯一一行代码。
			}
			else {
				copyarr[k++] = nums[i++];
			}
		}
		if(i <= mid) copy(nums.begin() + i, nums.begin() + mid + 1, copyarr.begin() + k);
		if (j <= right) copy(nums.begin() + j, nums.begin() + right + 1, copyarr.begin() + k);
		copy(copyarr.begin() + left, copyarr.begin() + right + 1, nums.begin() + left);
	}
};
int main()
{
	vector<int> nums = { 7,5,6,4 };
	Solution().reversePairs(nums);
	return 0;
}

