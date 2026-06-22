#include <algorithm> //包含堆操作
#include <iostream>
#include <string>
#include <cmath>
#include <stack>  //栈
#include <queue>  //队列
#include <vector> //不注重插入和删除效率
#include <list>	  //类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include <deque>  //双端队列，兼顾随即存取，和两端数据的插入删除
#include <ctime>
#include < unordered_map>
#include < unordered_set>
#include <hash_map>
#include <hash_set>
#include <assert.h>
#include <set>
#include <map>
using namespace std;
// 面试3 数组中重复的数字
// 在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。
// 数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每
// 个数字重复了几次。请找出数组中任意一个重复的数字。
// 示例：输入：
//[2, 3, 1, 0, 2, 5, 3]
// 输出：2 或 3
/*************时间O(N)**空间O(N)*************************/
class Solution
{
public:
	int findRepeatNumber(vector<int> &nums)
	{
		int len = nums.size();
		int res = 0;
		set<int> numset;
		for (int i = 0; i < len; i++)
		{
			if (numset.find(nums[i]) != numset.end())
				res = nums[i];
			else
				numset.insert(nums[i]);
		}

		return res;
	}
};
/*************时间O(N)**空间O(1)*************************/
class Solution1
{
public:
	int findRepeatNumber(vector<int> &nums)
	{
		int len = nums.size();
		if (len <= 0)
			throw invalid_argument("The nums is empty");
		for (int i = 0; i < len; i++)
		{
			if (nums[i] < 0 || nums[i] > len - 1) // 异常处理
				throw invalid_argument("Out of range");
			while (nums[i] != i)
			{								  // 只要当前数字与索引不等继续交换
				if (nums[i] == nums[nums[i]]) // 若对应索引位置已经有nums[i]则说明该元素重复
					return nums[i];
				swap(nums[i], nums[nums[i]]); // 将nums[i]放在对应的索引位置
			}
		}
		throw invalid_argument("There is no repeat number");
	}
};

// TODO:这段有点问题，暂时为debug出来
// 面试3变形
// 在长度为n+1的数组中所有数字都在[1,n]范围内
//[1,n]有n个数字，但是数组中有n+1个数字
// 原题长度为n，范围[0,n-1]
//[0,n-1]有n个数字，数组也有n个数字，无法使用该方法。
/*************不修改数组*************************/
class Solution2
{
private:
	// 遍历原数组，统计[start,end]范围的数字一共出现了多少次
	int countRange(vector<int> &nums, int start, int end)
	{
		int count = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] >= start && nums[i] <= end)
				count++;
		}
		return count;
	}

public:
	int findRepeatNumber(vector<int> &nums)
	{
		int len = nums.size();
		if (len <= 0)
			throw invalid_argument("The nums is empty");
		int start = 0;
		int end = len - 1;
		while (start <= end)
		{
			int mid = (end - start) / 2 + start; // 找到数组中点
			int count = countRange(nums, start, mid);

			if (end == start)
			{ // 终止条件
				if (count > 1)
					return start;
				else
					break;
			}
			if (count > (mid - start + 1)) // 数量大于应有数量
				end = mid;				   // 继续缩小该区间的范围进行判断
			else						   // 选择另外一段
				start = mid + 1;
		}
		return -1; // 未找到重复元素
	}
};
int main()
{
	vector<int> n{0, 1, 2, 0, 4, 5, 6, 7, 8, 9};
	cout << Solution2().findRepeatNumber(n) << endl;
	return 0;
}
