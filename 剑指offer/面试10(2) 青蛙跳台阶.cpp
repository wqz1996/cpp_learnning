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
using namespace std;
// 面试题11：跳台阶
// 一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙
//跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

/**************在线IDE************/
class Solution {
public:
	int jumpFloor(int number) {
		int begin[2] = {1,1};
		if (number < 2)
			return begin[number];
		int fibfirst = 1;
		int fibsecond = 1;
		int fibn=0;
		for (int i = 2; i <= number; i++) {
			fibn = fibfirst + fibsecond;
			fibfirst = fibsecond;
			fibsecond = fibn;
		}
		return fibn;
	}
};
int main()
{
	Solution s;
	cout<<s.jumpFloor(0)<<endl;
	cout << s.jumpFloor(1) << endl;
	cout << s.jumpFloor(2) << endl;
	cout << s.jumpFloor(3) << endl;
	cout << s.jumpFloor(4) << endl;
	cout << s.jumpFloor(5) << endl;
	return 0;

}



