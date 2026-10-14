#include <algorithm> // 使用处：第 15 行的 max(
#include <vector> // 使用处：第 10 行的 vector
using namespace std;
//面试题42. 连续子数组的最大和
// 题目：输入一个整型数组，数组里有正数也有负数。
//数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。
//要求时间复杂度为O(n)。
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int len = nums.size();
		int maxval = nums[0];
		int pre = 0;
		for (int i = 0; i < len; i++) {
			pre = max(pre + nums[i], nums[i]);//pre表示当前可以做到的最大的和，取之前的和加当前数或者直接以当前数开始计算最大和
			maxval = max(maxval, pre);//取所有过程中最大的pre
		}
		return maxval;
	}
};
int main()
{
	


	return 0;
}

