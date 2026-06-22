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
//面试题21. 调整数组顺序使奇数位于偶数前面
// 题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
//使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。
/*****************最优********************/
class Solution {
public:
	vector<int> exchange(vector<int>& nums) {
		int p1 = 0;
		int p2 = nums.size() - 1;
		while (p1 < p2) {
			if ((nums[p1] & 1) == 0) {//nums[p1]是偶数则与p2位置交换，p2向前移动一位，p1不动
				swap(nums[p1], nums[p2--]);
			}
			else {//nums[p1]是奇数则p1向前移动一位
				p1++;
			}
		}
		return nums;
	}
};
class Solution {
private:
	void swap(vector<int>& nums, int i, int j) {//交换两个元素
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}
public:
	vector<int> exchange(vector<int>& nums) {
		if (nums.empty() || nums.size() == 1)//nums为空或者只有一个元素则直接返回原数组
			return nums;
		int p1 = 0;//指向开始
		int p2 = nums.size() - 1;//指向结尾
		while (p1 < p2) {//指针不对撞时
			if (nums[p1] % 2 == 0 && nums[p2] % 2 == 1) {//p1指向偶数，p2指向奇数则交换
				swap(nums, p1, p2);
				p1++;//两个指针分别移动一步
				p2--;
			}
			else if (nums[p1] % 2 == 1 && nums[p2] % 2 == 1) {//p1指向奇数，p2指向奇数
				p1++;//p2指针不变，p1移动一位
			}
			else if (nums[p1] % 2 == 0 && nums[p2] % 2 == 0) {//p1指向偶数，p2指向偶数
				p2--;//p1指针不变，p2移动一位
			}
			else {//p1指向奇数，p2指向偶数
				p1++;//直接判断下一位
				p2--;
			}
		}
		return nums;
	}
};
/*******************简化****************/
class Solution1 {
private:
	void swap(vector<int>& nums, int i, int j) {//交换两个元素
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}
public:
	vector<int> exchange(vector<int>& nums) {
		if (nums.empty() || nums.size() == 1)//nums为空或者只有一个元素则直接返回原数组
			return nums;
		int p1 = 0;//指向开始
		int p2 = nums.size() - 1;//指向结尾
		while (p1 < p2) {//指针不对撞时
			if ((nums[p1] & 1) != 0) {//左侧指向是奇数
				p1++;
				continue;
			}
			if ((nums[p2] & 1) != 1) {//右侧指向是偶数
				p2--;
				continue;
			}
			swap(nums, p1, p2);//左侧右侧都指向奇数交换，都指向偶数也交换，左侧指向偶数右侧指向奇数交换
			p1++;
			p2--;
		}
		return nums;
	}
};
class Solution {
public:
	vector<int> exchange(vector<int>& nums) {
		int p1 = 0;
		int p2 = nums.size() - 1;
		while (p1 < p2) {
			if ((nums[p1] & 1) == 0)//p1是偶数则与p2位置交换，p2保证是偶数，p1位置继续判断
				swap(nums[p1], nums[p2--]);
			else if ((nums[p2] & 1) == 1)//p2是奇数则与p1位置交换，p1保证是奇数，p2位置继续判断
				swap(nums[p1++], nums[p2]);
			else {//p1位置是奇数并且p2位置是偶数则指针向内收缩
				p1++;
				p2--;
			}

		}
		return nums;
	}
};
int main()
{
	vector<int> arr = { 2,16,3,5,13,1,16,1,12,18,11,8,11,11,5,1 };
	Solution1().exchange(arr);
	return 0;
}

