#include <algorithm> // 使用处：第 22 行的 min(
#include <stack> // 使用处：第 11 行的 stack
#include <vector> // 使用处：第 41 行的 vector
#include <climits> // 使用处：第 14 行的 INT_MAX
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

