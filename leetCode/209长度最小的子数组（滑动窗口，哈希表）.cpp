#include <algorithm> // 使用处：第 25 行的 min(
#include <iostream> // 使用处：第 38 行的 cout
#include <vector> // 使用处：第 11 行的 vector
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