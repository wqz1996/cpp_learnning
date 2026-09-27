#include <algorithm> // sort：第 31 行首次使用
#include <iostream> // cout, endl：第 75 行首次使用
#include <vector> // vector：第 14 行首次使用
#include <unordered_map> // unordered_map：第 15 行首次使用
#include <cstdlib> // rand：第 42 行首次使用
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

