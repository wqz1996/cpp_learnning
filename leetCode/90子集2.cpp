#include <algorithm> // 使用处：第 29 行的 sort(
#include <vector> // 使用处：第 10 行的 vector
using namespace std;
// 78. 子集
// 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
// 说明：解集不能包含重复的子集。
class Solution
{
private:
	vector<vector<int>> res;
	vector<int> temp;
	void backtrack(vector<int> &nums, int idx)
	{
		res.push_back(temp);
		for (int i = idx; i < nums.size(); i++)
		{
			// 如果发现当前元素和上一个元素相同则跳过，剪枝操作避免重复
			if (i > idx && nums[i] == nums[i - 1])
				continue;
			temp.push_back(nums[i]);
			backtrack(nums, i + 1);
			temp.pop_back();
		}
	}

public:
	vector<vector<int>> subsetsWithDup(vector<int> &nums)
	{
		sort(nums.begin(), nums.end()); // 保证相同的元素是紧邻的
		backtrack(nums, 0);
		return res;
	}
};
int main()
{
	vector<int> nums{1, 2, 3};
	Solution().subsets(nums);
	return 0;
}
