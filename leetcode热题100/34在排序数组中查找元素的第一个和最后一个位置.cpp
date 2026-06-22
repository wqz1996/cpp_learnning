#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
//33. 搜索旋转排序数组
//给定一个按照升序排列的整数数组 nums，和一个目标值 target。
//找出给定目标值在数组中的开始位置和结束位置。
//你的算法时间复杂度必须是?O(log n) 级别。
//如果数组中不存在目标值，返回?[-1, -1]。
/*******************自己解法**************************/
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		if (nums.size() == 0)
			return  vector<int>{-1, -1};
		if (nums.size() == 1) {
			return nums[0] == target ? vector<int>{0, 0} : vector<int>{ -1,-1 };
		}
		int left = 0;
		int right = nums.size() - 1;
		while (nums[left] != nums[right] && left < right) {
			int mid = left - (left - right) / 2;
			if (nums[mid] <= target && nums[left]!=target) {
				left = mid;
				while (nums[left]==target && left > 0 && nums[left - 1] == nums[left]) {
					left--;
				}
				if (nums[mid] == target)
					continue;
			}				
			if (nums[mid] >= target && nums[right] != target) {
				right = mid;
				while (nums[right] == target && right < nums.size()-1 && nums[right + 1] == nums[right]) {
					right++;
				}
			}
			if (right - left == 1) {
				if (nums[left] == target && nums[right] != target)
					return  vector<int>{left, left};
				else if (nums[left] != target && nums[right] == target)
					return  vector<int>{right, right};
				else
					break;
			}								
		}
		if (nums[left]==target)
			return vector<int>{left, right};
		else
			return vector<int>{-1, -1};
	}
};
/*******************分别搜索开始和结束的位置**************************/
class Solution {
private:
	int findfirstposition(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		while (left < right) {
			int mid = (left + right) >> 1;//
			if (nums[mid] < target)//小于则一定不是解的范围
				left = mid + 1;//[mid+1,right]
			else//大于等于可能是
				right = mid;
		}
		if (nums[left] != target)
			return -1;
		return left;
	}
	int findlastposition(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		while (left < right) {
			int mid = (left + right + 1) >> 1;
			if (nums[mid] > target)//大于则一定不是解的范围
				right = mid - 1;//下一轮搜索区间是 [left, mid - 1]
			else
				left = mid;
		}
		if (nums[left] != target)
			return -1;
		return left;
	}
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		if (nums.size() == 0)
			return { -1,-1 };
		int firstpos = findfirstposition(nums, target);
		if (firstpos == -1)
			return { -1,-1 };
		int lastpos = findlastposition(nums, target);
		return { firstpos,lastpos };
	}
};
int main()
{
	vector<int> nums = {1,4 };
	Solution().searchRange(nums,4);

	return 0;
}

