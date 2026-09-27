#include <algorithm> // max, min：第 17 行首次使用
#include <vector> // vector：第 7 行首次使用
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

