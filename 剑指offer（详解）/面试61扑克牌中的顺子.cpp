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
//面试题61. 扑克牌中的顺子
// 从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。
//2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以
//看成任意数字。A 不能视为 14。
class Solution {
public:
	bool isStraight(vector<int>& nums) {
		sort(nums.begin(),nums.end());//数组排序
		int numsof0 = 0;//统计0的个数
		int numsGap = 0;//统计缺少牌的数目
		for (int i = 0; i < nums.size(); i++) {//统计0的个数
			if (nums[i] == 0)
				numsof0++;
		}
		int p1 = numsof0;//从0的下一个数开始
		int p2 = p1 + 1;//p1的下一个数
		while (p2 < nums.size()) {//p2没到末尾
			if (nums[p1] == nums[p2])//有相等的数则不是顺子
				return false;
			numsGap += nums[p2] - nums[p1] - 1;//统计差值超过1的数目
			p1 = p2;
			p2++;

		}
		return numsGap <= numsof0 ? true : false;//差值小于0的个数可以补齐

	}
};
/************自己写*******************/
class Solution {
public:
	bool isStraight(vector<int>& nums) {
		sort(nums.begin(), nums.end());//数组排序
		int numsof0 = 0;
		int numsGap = 0;
		for (int i = 0; i < nums.size(); i++)
			if (nums[i] == 0)
				numsof0++;

		for (int i = numsof0 + 1; i < nums.size(); i++) {
			if (nums[i] == nums[i - 1])
				return false;
			numsGap += nums[i] - nums[i - 1] - 1;
		}
		return numsGap <= numsof0 ? true : false;

	}
};
//自己写的
class Solution {
public:
	bool isStraight(vector<int>& nums) {
		sort(nums.begin(), nums.end());//先排序
		int numof0 = 0;//统计0的个数
		int numGap = 0;//统计两个数字差值超过1的数值和
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == 0)//统计0
				numof0++;
			else {
				if (i < nums.size() - 1) {
					if (nums[i + 1] == nums[i])//两个数字相等直接返回false
						return false;
					numGap += nums[i + 1] - nums[i] - 1;//将两个相邻数字差值超过1的数值累加起来
				}
			}
		}
		return numof0 >= numGap;//0的数量大于间隔差超过1的总和
	}
};
int main()
{
	vector<int> arr = { 10, 11, 0, 12, 6 };
	Solution().isStraight(arr);
	return 0;
}

