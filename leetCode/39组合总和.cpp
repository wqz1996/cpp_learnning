#include <vector> // 使用处：第 7 行的 vector
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
