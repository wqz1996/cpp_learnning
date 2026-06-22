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
/**********************4最小栈*************************/
/*************用栈实现*************************/
class MinStack {
public:
	
	stack<int> stackdata;
	stack<int> stackmin;
	MinStack() {
		stackmin.push(INT_MAX);
	}

	void push(int x) {
		stackdata.push(x);
		if(stackmin.empty())
			stackmin.push(x);
		else
		stackmin.push(min(stackmin.top(), x));
	}

	void pop() {
		stackdata.pop();
		stackmin.pop();
	}

	int top() {
		return stackdata.top();
	}

	int getMin() {
		return stackmin.top();
	}
};
/*************vector实现*************************/
class MinStack {
private:
	vector<int> data, Min;
public:
	MinStack() {
		Min.push_back(INT_MAX);
	}

	void push(int x) {
		data.push_back(x);
		if (Min.empty())
			Min.push_back(x);
		else
			Min.push_back(min(Min.back(), x));
	}

	void pop() {
		data.pop_back();
		Min.pop_back();
	}

	int top() {
		return data.back();
	}

	int getMin() {
		return Min.back();
	}
};

int main()
{


	return 0;
}

