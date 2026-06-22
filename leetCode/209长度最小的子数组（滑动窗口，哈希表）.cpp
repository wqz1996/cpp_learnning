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
using namespace std;
/************209长度最小的子数组********************/
//给定含有n个整数的数组和一个正整数s，找出满足和>=s
//的最小连续子数组。返回长度，若不存在返回0
//滑动窗口
class Solution {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		int L = 0, R = -1;//滑动窗口边界
		int sum = 0;
		int res = nums.size() + 1;//逐渐缩小
		while (L < nums.size()) {
			if (R+1<nums.size()&&sum < s) {
				R++;
				sum += nums[R];
			}
			else {
				sum -= nums[L];
				L++;
			}
			if (sum >= s) {
				res = min(res,R - L + 1);
			}
				
		}
		if (res == nums.size() + 1)//未找到
			return 0;
		return res;

	}
};
int main() {
	int arr[] = { 2,7,3,5 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));//使用数组创建vector
	cout<<Solution().minSubArrayLen(20, v);
	int tag=9;

	return 0;
}