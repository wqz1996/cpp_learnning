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
class Solution {
public:
	/******动态规划**************/
	int maxProduct(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int len = nums.size();
		int curmin = nums[0];//维护当前最小值
		int curmax = nums[0];//维护当前最大值
		int maxval = nums[0];//保存当前可能的最大值
		for (int i = 1; i < len; i++) {
			int temp = curmax;//
			//考虑到负负为正，因此需要考虑curmin*nums[i]是否为最大乘积
			curmax = max(curmax * nums[i], max(curmin * nums[i], nums[i]));
			curmin = min(temp * nums[i], min(curmin * nums[i], nums[i]));
			maxval = max(curmax, max(curmin, maxval));//记录当前最大值
		}
		return maxval;

	}
};
int main()
{
	vector<int> nums{ -2,3,-4 };
	Solution().maxProduct(nums);

	return 0;
}

