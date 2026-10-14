#include <iostream> // 使用处：第 25 行的 cout
#include <vector> // 使用处：第 10 行的 vector
using namespace std;
//面试题53 - II. 0～n-1中缺失的数字
// 题目：一个长度为n-1的递增排序数组中的所有数字都是唯一的，
//并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中
//有且只有一个数字不在该数组中，请找出这个数字。
class Solution {
public:
	int missingNumber(vector<int>& nums) {
		int left = 0, right = nums.size();//为了判断只有一个元素的情况
		while (left < right) {
			int mid = left - (left - right) / 2;
			if (nums[mid] == mid)//中间相等则缺失的在右半部分
				left = mid + 1;
			else//否则在左半部分
				right = mid;
		}
		return left;
	}
};
int main()
{
	vector<int> arr{ 0 };
	cout<<Solution().missingNumber(arr);
	return 0;
}

