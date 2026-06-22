#include <algorithm> //包含堆操作
#include <iostream>
#include <sstream> //istringstream 可以将string以空格为分隔符分割
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
// 78. 子集
// 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
// 说明：解集不能包含重复的子集。
class Solution
{
private:
	vector<vector<int>> res;
	vector<int> path;
	void findsubset(vector<int> &nums, int start)
	{
		res.push_back(path);
		for (int i = start; i < nums.size(); i++)
		{
			path.push_back(nums[i]);
			findsubset(nums, i + 1);
			path.pop_back();
		}
	}

public:
	vector<vector<int>> subsets(vector<int> &nums)
	{
		findsubset(nums, 0);
		return res;
	}
};
int main()
{
	vector<int> nums{1, 2, 3};
	Solution().subsets(nums);
	return 0;
}
