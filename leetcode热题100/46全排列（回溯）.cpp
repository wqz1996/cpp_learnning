#include <iostream> // cout, endl：第 43 行首次使用
#include <vector> // vector：第 7 行首次使用
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

