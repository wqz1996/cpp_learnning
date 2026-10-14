#include <algorithm> // 使用处：第 33 行的 sort(
#include <vector> // 使用处：第 7 行的 vector
using namespace std;
/*************排列组合问题*****************/
class Solution
{
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
		{
			return;
		}
		for (int i = idx; i < candidates.size(); i++)
		{
			if (i > idx && candidates[i - 1] == candidates[i])
				continue;
			temp.push_back(candidates[i]);
			backtrack(candidates, target - candidates[i], i + 1);
			temp.pop_back();
		}
	}

public:
	vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
	{
		sort(candidates.begin(), candidates.end());
		backtrack(candidates, target, 0);
		return res;
	}
};
int main()
{

	return 0;
}
