#include<algorithm>//包含堆操作
#include<iostream>
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
/*************300最长上升子序列******************/
class Solution {
public:

	int lengthOfLIS(vector<int>& nums) {
		if (nums.size() == 0)
			return 0;
		vector<int> mem(nums.size(), 1);//以nums[i]结尾的最长子序列长度
		for (int i = 1; i < nums.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (nums[j] < nums[i])
					mem[i] = max(mem[i], 1 + mem[j]);
			}
		}

		int res = 1;
		for (int i = 0; i < nums.size(); i++) {
			res = max(res, mem[i]);
		}
		return res;
	}
};
int main()
{
	vector<int> arr{ 10,9,2,5,3,7,101,18 };
	//vector<int> arr{ 1,4,2,3,5,10 };
	cout<<Solution().lengthOfLIS(arr);
	return 0;
}

