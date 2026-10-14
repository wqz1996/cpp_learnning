#include <algorithm> // 使用处：第 32 行的 min(
#include <stack> // 使用处：第 9 行的 stack
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

