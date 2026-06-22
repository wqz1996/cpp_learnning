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
// 面试题10：变态跳台阶
// 一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。
//求该青蛙跳上一个n级的台阶总共有多少种跳法。

/**************在线IDE************/
class Solution {
public:
	int jumpFloor(int number) {
		if (number == 0) {
			return 0;
		}
		int sum = 1;
		for (int i = 0; i < number-1; i++) {
			sum *= 2;
		}
		return sum;
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



