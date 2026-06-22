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
//39. 组合总和
//给定一个无重复元素的数组?candidates?和一个目标数?target?，
//找出?candidates?中所有可以使数字和为?target?的组合。
//candidates?中的数字可以无限制重复被选取。
class Solution {
private:
	vector<vector<int>> res;//记录结果
	vector<int> path;//记录路径
	void dfs(vector<int>& candidates, int start,int target) {
		if (target == 0) {//当目标值为0，则找到一条路径回溯
			res.push_back(path);
			return;
		}
		//由于是有序数组，直接剪掉target-candidates[i]>=0后面所有分支，不进入循环
		for (int i = start; i < candidates.size()&&target-candidates[i]>=0; i++) {//target-candidates[i]>=0剪枝
			path.push_back(candidates[i]);//压入当前路径
			dfs(candidates, i, target - candidates[i]);//搜索下一个数字
			path.pop_back();//回溯
		}
	}
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		dfs(candidates, 0, target);
		return res;
	}
};
int main()
{
	vector<int> nums{ 2,3,6,7 };
	Solution().combinationSum(nums,7);
	return 0;
}

