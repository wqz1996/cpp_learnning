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

