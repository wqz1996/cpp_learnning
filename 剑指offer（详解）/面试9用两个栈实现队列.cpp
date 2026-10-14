#include <stack> // 使用处：第 7 行的 stack
using namespace std;
// 面试题9:用两个栈实现队列
// 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，
//分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead?操作返回 -1 )
class CQueue {
	stack<int> spop;
	stack<int> spush;
public:
	CQueue() {
		
	}
	void appendTail(int value) {
		spush.push(value);
	}

	int deleteHead() {
		if (spop.empty()) {//pop栈为空
			if (spush.empty()) {
				return -1;
			}
			else {
				while (!spush.empty()) {//将push栈中所有元素压入pop栈
					spop.push(spush.top());
					spush.pop();
				}

			}
		}//若pop不为空则不用将push栈中的元素压入，直接返回栈顶元素即可
		//若pop为空则先将push栈元素压入pop栈后再返回栈顶
		int temp = spop.top();
		spop.pop();
		return temp;
	}
};

int main()
{

	return 0;
}

