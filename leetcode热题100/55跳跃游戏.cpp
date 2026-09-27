#include <algorithm> // max：第 14 行首次使用
#include <vector> // vector：第 10 行首次使用
using namespace std;
//55. 跳跃游戏
//给定一个非负整数数组，你最初位于数组的第一个位置。
//数组中的每个元素代表你在该位置可以跳跃的最大长度。
//判断你是否能够到达最后一个位置。
class Solution {
public:
	bool canJump(vector<int>& nums) {
		int longest = 0;//记录当前可达最远位置
		for (int i = 0; i < nums.size(); i++) {
			if (i <= longest) {//i<=longest说明nums[i]可达
				longest = max(longest, i + nums[i]);//记录当前可达最远位置
				if (longest >= nums.size() - 1)//当可达最远位置大于等于数组最后一个索引则说明可达到最后
					return true;
			}
			else {//当前nums[i]位置不可达直接跳出循环
				break;
			}
		}
		return false;
	}
};
int main()
{

	return 0;
}

