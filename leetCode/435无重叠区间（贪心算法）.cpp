#include<algorithm>//包含堆操作
#include<iostream>
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
/*************435无重叠区间*****************************/
bool cmp(const vector<int>& a, const vector<int>& b) {
	if (a[0] != b[0])//若起始点不同
		return a[0] < b[0];//起始点小的在前面
	return a[1] < b[1];//若起始点相同则终止点小的在前面
}
bool cmp1(const vector<int>& a, const vector<int>& b) {
	if (a[1] != b[1])//若终止点不同
		return a[1] < b[1];//终止点小的在前面
	return a[0] < b[0];//若终止点相同则起始点小的在前面
}
class Solution {
public:
	/****************动态规划***********************************/
	int eraseOverlapIntervalsDp(vector<vector<int>>& intervals) {
		if (intervals.size() == 0)
			return 0;
		sort(intervals.begin(), intervals.end(),cmp);//按照开始时间升序排列
		//intervals[0...i]的最长不重叠区间序列
		vector<int> mem(intervals.size(),1);
		for (int i = 1; i < intervals.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (intervals[i][0] >= intervals[j][1])//i的起始大于j的结束，不重叠的条件
					mem[i] = max(mem[i], 1 + mem[j]);

			}
		}
		int res = 0;
		for (int i = 0; i < mem.size(); i++)//返回mem中最大的元素
			res = max(res, mem[i]);

		return intervals.size() - res;

	}
	/****************贪心算法***********************************/
	//按照结尾排序，优先选择结尾最早的，并且和前一个区间不重合的
	int eraseOverlapIntervals(vector<vector<int>>& intervals) {
		if (intervals.size() == 0)
			return 0;
		sort(intervals.begin(), intervals.end(), cmp1);//按照终止点早排序

		int res = 1;//最少有一个区间
		int pre = 0;//保存i之前的一个区间
		for (int i = 1; i < intervals.size(); i++) {
			if (intervals[i][0] >= intervals[pre][1]) {//i的起始大于pre的结束，不重叠的条件
				res++;//
				pre = i;//更新当前保存区间的索引
			}
		}

		return intervals.size() - res;//返回最少需要删除多少个区间
	}
};
int main()
{
	vector<vector<int>>  arr{ {1, 2 }, { 2, 3 }, { 3, 4 }, { 1, 3 } };
	cout << Solution().eraseOverlapIntervals(arr);
	return 0;
}

