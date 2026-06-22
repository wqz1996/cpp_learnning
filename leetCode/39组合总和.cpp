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
using namespace std;
/*************排列组合问题*****************/
class Solution
{
private:
	vector<vector<int>> res;
	vector<int> temp;
	void backtrack(vector<int> &candidates, int target, int idx)
	{
		if (target == 0)
		{
			res.push_back(temp);
			return;
		}
		if (target < 0)
			return;
		for (int i = idx; i < candidates.size(); i++)
		{
			temp.push_back(candidates[i]);
			backtrack(candidates, target - candidates[i], i);
			temp.pop_back();
		}
	}

public:
	vector<vector<int>> combinationSum(vector<int> &candidates, int target)
	{
		backtrack(candidates, target, 0);
		return res;
	}
};
int main()
{

	return 0;
}
