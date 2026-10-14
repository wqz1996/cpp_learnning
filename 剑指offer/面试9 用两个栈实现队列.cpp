#include <iostream> // 使用处：第 16 行的 cout
#include <stack> // 使用处：第 31 行的 stack
using namespace std;
// 面试题9：用两个栈实现队列
// 题目：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail
// 和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。
class Solution
{
public:
	void push(int node) {
		stack1.push(node);
	}

	int pop() {
		if (stack2.empty()) {
			cout << "the queue is empty" << endl;
		}
		if (stack2.empty()) {//pop栈弹空了才能将push的内容压入
			while (!stack1.empty()) {//将push栈中所有元素压入pop
				stack2.push(stack1.top());
				stack1.pop();
			}
		}		
		int temp = stack2.top();
		stack2.pop();
		return temp;

	}

private:
	stack<int> stack1;
	stack<int> stack2;
};
int main()
{

	return 0;

}



