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
using namespace std;
/*************排列组合问题*****************/
class Solution {
private:
	vector<vector<int>> res;
	vector<bool> used;
	void Perms(const vector<int>& nums, int index,vector<int>&p) {
		if (index == nums.size()) {
			res.push_back(p);
			return;
		}
		for (int i = 0; i < nums.size(); i++) {
			if (!used[i]) {//当前数字未使用过则进入
				p.push_back(nums[i]);
				used[i] = true;//使用了nums[i]元素
				Perms(nums, index + 1, p);
				p.pop_back();//递归完以后恢复使用过的数字再次使用的权限
				used[i] = false;
			}
		}

		return;
	}
public:
	vector<vector<int>> Permutation(vector<int>& nums) {
		res.clear();
		if (nums.empty())
			return res;
		used = vector<bool>(nums.size(), false);//初始化一个与nums大小相等的bool数组，用于判断是否使用过该数字
		vector<int> p;
		Perms(nums, 0, p);
		return res;
	}
};
int main()
{
	vector<int> v{ 1,2,3 };
	vector<vector<int>> s = Solution().Permutation(v);
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < s[0].size(); j++) {
			cout << s[i][j];
		}
		cout << endl;
	}

	return 0;
}

