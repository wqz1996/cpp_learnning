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
//假设按照升序排序的数组在预先未知的某个点上进行了旋转。
//(例如，数组?[0, 1, 2, 4, 5, 6, 7]?可能变为?[4, 5, 6, 7, 0, 1, 2])。
//搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回? - 1?。
//你可以假设数组中不存在重复的元素。
//你的算法时间复杂度必须是?O(log?n) 级别。
class Solution {
public:
	int search(vector<int>& nums, int target) {
		if (nums.empty())
			return -1;
		if (nums.size() == 1)//只有一个元素直接判断
			return target == nums[0] ? 0 : -1;
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right) {
			int mid = left - (left - right) / 2;
			if (nums[mid] == target)//找到中点值为target返回中点值索引
				return mid;
			if (nums[left] <= nums[mid]) {//左半边有序 注：必须加等号，可能出现左边只有一个元素的情况
				if (nums[left]<=target && nums[mid]>=target) //在有序数组中
					right = mid - 1;
				else//在无序数组中
					left = mid + 1;
			}
			else {//右半边有序
				if (nums[mid]<=target && nums[right]>=target)
					left = mid + 1;//在右侧有序数组中
				else//在左侧无序数组中
					right = mid - 1;
			}
		}
		return -1;
				
	}
};
int main()
{
	vector<int> nums = { 4,5,6,7,0,1,2 };
	cout<<Solution().search(nums, 0);

	return 0;
}

