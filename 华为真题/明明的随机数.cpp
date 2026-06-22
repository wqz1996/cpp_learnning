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
//明明想在学校中请一些同学一起做一项问卷调查，为了实验的客观性，
//他先用计算机生成了N个1到1000之间的随机整数（N≤1000），对于其
//中重复的数字，只保留一个，把其余相同的数去掉，不同的数对应着不
//同的学生的学号。然后再把这些数从小到大排序，按照排好的顺序去找
//同学做调查。请你协助明明完成“去重”与“排序”的工作(同一个测试
//用例里可能会有多组数据，希望大家能正确处理)。
int main() {
	int n;
	while (cin >> n) {
		vector<int> nums;
		vector<int> res;
		int temp;
		vector<int> botto(1000);
		for (int i = 0; i < n; i++) {
			cin >> temp;
			nums.push_back(temp);
		}
		for (int i = 0; i < n; i++) {
			botto[nums[i]] = 1;
		}
		for (int i = 0; i < botto.size(); i++) {
			if (botto[i] == 1)
				res.push_back(i);
		}
		for (int i = 0; i < res.size(); i++) {
			cout << res[i] << endl;
		}
	
	}

	return 0;
}

