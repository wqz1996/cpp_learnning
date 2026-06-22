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
//面试题29. 顺时针打印矩阵
// 题目：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素
//的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。
class MinStack {
public:
	stack<int> datastack;//记录数据
	stack<int> minstack;//记录最小值
	MinStack() {

	}

	void push(int x) {
		datastack.push(x);
		if (minstack.empty() || minstack.top() >= x)//min栈为空或者min栈栈顶大于等于x
			minstack.push(x);
		else//min栈不为空且min栈栈顶小于x
			minstack.push(minstack.top());
	}

	void pop() {
		datastack.pop();//两个栈同时弹出一个元素
		minstack.pop();
	}

	int top() {
		return datastack.top();
	}

	int min() {
		return minstack.top();
	}
};
int main()
{
	
	return 0;
}

