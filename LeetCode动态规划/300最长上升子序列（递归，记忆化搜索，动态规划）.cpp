#include <algorithm> // 使用处：第 17 行的 max(
#include <iostream> // 使用处：第 84 行的 cout
#include <vector> // 使用处：第 9 行的 vector
using namespace std;
/*************300最长上升子序列******************/
class Solution {
public:

	int lengthOfLIS(vector<int>& nums) {
		if (nums.size() == 0)
			return 0;
		int res = 1;
		vector<int> mem(nums.size(), 1);//以nums[i]结尾的最长子序列长度
		for (int i = 1; i < nums.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (nums[j] < nums[i])
					mem[i] = max(mem[i], 1 + mem[j]);
			}
			res = max(res, mem[i]);
		}
		return res;
	}
};
/*******O(NlogN)**********/
class Solution {
	int findlastmax(vector<int> arr, int target) {//二分法查找最后一个大于等于target元素的索引
		int left = 0;
		int right = arr.size() - 1;
		while (left < right) {
			int mid = left + ((right - left) >> 1);
			if (arr[mid] < target)//mid元素小于target，left->mid+1
				left = mid + 1;
			else if (arr[mid] > target && (mid == 0 || arr[mid - 1] <= target))//mid大于target，mid等于0或者mid-1小于等于target则返回mid索引
				return mid;
			else if (arr[mid] >= target)
				right = mid;
		}
		return left;
	}
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int n = nums.size();
		vector<int> lis;//记录可能的上升子序列
		lis.push_back(nums[0]);
		for (int i = 1; i < n; i++) {
			if (nums[i] > lis.back()) {//当前元素大于lis最后一个元素则将当前元素放入上升子序列中
				lis.push_back(nums[i]);
			}
			else {//将lis中最后一个大于等于当前元素的值替换为当前元素
				int index = findlastmax(lis, nums[i]);//找到符合条件元素索引
				lis[index] = nums[i];
			}
		}
		return lis.size();
	}
};
/**********使用STL库****************/
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int n = nums.size();
		vector<int> lis;//记录可能的上升子序列
		lis.push_back(nums[0]);
		for (int i = 1; i < n; i++) {
			vector<int>::iterator it = lower_bound(lis.begin(), lis.end(), nums[i]);//找到第一个大于等于nums[i]的位置
			//upper_bound返回第一个大于查找元素的位置
			//binary_bound返回是否存在查找元素，bool值
			if (it == lis.end())//没找到大于等于nums[i]的元素
				lis.push_back(nums[i]);
			else
				*it = nums[i];//找到了进行替换
		}
		return lis.size();
	}
};
int main()
{
	vector<int> arr{ 10,9,2,5,3,7,101,18 };
	//vector<int> arr{ 1,4,2,3,5,10 };
	cout<<Solution().lengthOfLIS(arr);
	return 0;
}

