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
//面试题57. 和为s的两个数字
// 题目：输入一个正整数 target ，输出所有和为 target 的连续正整数序列
//（至少含有两个数）。序列内的数字由小到大排列，不同序列按照首个数字
//从小到大排列
class Solution {
public:
	vector<vector<int>> findContinuousSequence(int target) {
		vector<vector<int>> res;
		vector<int> temp;
		int small = 1, big = 2;
		int mid = (1 + target) / 2;
		int cursum = small + big;
		while (small < mid) {
			if (cursum == target) {
				for (int i = small; i <= big; i++) {
					temp.push_back(i);
				}
				res.push_back(temp);
				temp.clear();
			}
			while (cursum > target) {
				cursum -= small;
				small++;
				if (cursum == target) {
					for (int i = small; i <= big; i++) {
						temp.push_back(i);
					}
					res.push_back(temp);
					temp.clear();
				}

			}
			big++;
			cursum += big;
		}
		return res;
	}
};
/*************滑动窗口******************/
//剑指 Offer 57 - II. 和为s的连续正数序列
class Solution {
public:
	vector<vector<int>> findContinuousSequence(int target) {
		int p1 = 1;//从1，2开始
		int p2 = 2;
		int sum = p1 + p2;
		vector<vector<int>> res;//保存所有结果
		while (p1 <= target / 2) {//p1=target/2时是终止条件
			if (sum < target) {//和小于sum
				p2++;
				sum += p2;//sum中增加一个数
			}
			else if (sum > target) {
				sum -= p1;//去掉较小的数
				p1++;
			}
			else {
				vector<int> temp;
				for (int i = p1; i <= p2; i++) {
					temp.push_back(i);
				}
				res.push_back(temp);
				sum -= p1;//继续尝试下一种组合
				p1++;
			}
		}
		return res;
	}
};
int main()
{
	
	Solution1().findContinuousSequence(9);
	return 0;
}

