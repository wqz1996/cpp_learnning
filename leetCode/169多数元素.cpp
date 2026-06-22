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
/**********************169多数元素*************************/
//给定大小为n的数组，找到多数元素
//多数元素值出现次数大于n/2的元素
//假设数组非空，并且给定数组总是存在多数元素
/***************哈希表*************************/
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		unordered_map<int, int> nummap;
		int n = nums.size();
		int element = 0;
		for (int i = 0; i < n; i++) {
			nummap[nums[i]]++;
			if (nummap[nums[i]] > n / 2)
				element =nums[i];
		}
		
		return element;
	}
};
/***************排序*************************/
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		return nums[nums.size()/2];//排序后直接返回中间元素即为众数
	}
};
/***************随机化*************************/
//由于众数占大多数，因此随机选取一个数判断其是否为众数
//有很大几率可以快速判断
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		while (1) {
			int index = rand() % nums.size();//在范围内随机选一个下标
			int sum = 0;
			for (auto num : nums) {//判断随机选取的数是否为众数
				if (num == nums[index])
					sum++;
			}
			if (sum > nums.size() / 2)
				return nums[index];
		}
	}
};
/***************摩尔投票法************************/

class Solution {
public:
	int majorityElement(vector<int>& nums) {
		int count = 0;
		int res = -1;
		for (auto num : nums) {//从遍历数组，让所有元素都担任一次候选人
			if (count == 0)//当票数为0，更换候选人
				res = num;
			if (num == res)//元素与候选人相等的投一票
				count++;
			else//不相等的减一票
				count--;
		}
		//最终剩下的就是票数大于0的
		return res;
	}
};
int main()
{
	vector<int> nums{ 3,2,3 };
	cout << Solution().majorityElement(nums) << endl;
	return 0;
}

