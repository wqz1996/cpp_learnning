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

