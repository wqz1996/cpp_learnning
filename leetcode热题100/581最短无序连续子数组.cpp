#include <cstdint> // INT32_MIN、INT32_MAX：Solution::findUnsortedSubarray
#include <algorithm> // min, max：第 20 行首次使用
#include <iostream> // cout：第 44 行首次使用
#include <vector> // vector：第 11 行首次使用
using namespace std;
/****************281最短无序连续子数组***********************************/
//给定整数数组，寻找连续子数组，对该子数组排序，则整个数组有序
//返回最短子数组的长度
class Solution {
public:
	int findUnsortedSubarray(vector<int>& nums) {
		int len = nums.size();
		int maxnum = INT32_MIN;
		int minnum = INT32_MAX;
		bool flag = false;
		for (int i = 0; i < len-1; i++) {//从左到右找到第一个递减项
			if (nums[i] > nums[i + 1])
				flag = true;//必须写为true，不能写为!flag否则会一直翻转
			if(flag)
				minnum = min(minnum, nums[i+1]);

		}
		flag = false;
		for (int i = len-1; i > 0; i--) {//从右到左找到第一个递增项
			if (nums[i] < nums[i - 1])
				flag = true;
			if (flag)
				maxnum = max(maxnum, nums[i-1]);

		}
		int L;
		int R;
		for (L = 0; L < len && nums[L] <= minnum; L++);//从左向右找到第一个大于minnum的数

		for (R = len - 1; R >= 0 && nums[R] >= maxnum; R--);//从右向左找到第一个小于maxnum的数

		return R - L > 0 ? R - L + 1 : 0;//判断当前R与L的位置，最小输出为0
		
	}
};
int main()
{
	vector<int> nums{2,6,4,8,10,9,15};
	cout << Solution().findUnsortedSubarray(nums);

	return 0;
}

