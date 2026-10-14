#include <vector> // 使用处：第 9 行的 vector
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
