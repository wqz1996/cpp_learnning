#include <algorithm> // max：第 16 行首次使用
#include <iostream> // cout：第 31 行首次使用
#include <vector> // vector：第 9 行首次使用
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

