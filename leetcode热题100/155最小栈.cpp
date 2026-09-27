#include <algorithm> // min：第 22 行首次使用
#include <stack> // stack：第 11 行首次使用
#include <vector> // vector：第 41 行首次使用
#include <climits> // INT_MAX：第 14 行首次使用
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

