#include <cstddef> // 使用处：第 27 行的 NULL
#include <algorithm> // 使用处：第 96 行的 swap(
#include <iostream> // 使用处：第 16 行的 cout
#include <stack> // 使用处：第 104 行的 stack
#include <queue> // 使用处：第 77 行的 queue
#include <vector> // 使用处：第 11 行的 vector
using namespace std;
/**********数组实现栈*****************/
class ArrayStack {
private:
	vector<int> arr;
	int index;
public:
	void creatstack(int initsize) {
		if (initsize < 0)
			cout << "ERROR" << endl;
		arr = vector<int>(initsize);
		index = 0;
	}
	void push(int val) {
		if (index == arr.size())
			cout << "Full" << endl;
		arr[index++] = val;//将当前索引位置赋值
	}
	int top() {
		if (index == 0)
			return NULL;
		return arr[index - 1];//返回当前索引前一个元素,index不变
	}
	int pop() {
		if (index == 0)
			cout << "Empty" << endl;
		return arr[--index];//返回上一个元素，index向前移动一个
	}
};
/***************数组实现队列*****************/
class ArrayQueue {
private:
	vector<int> arr;
	int size;
	int output;
	int input;
public:
	void creatqueue(int initsize) {
		if (initsize < 0)
			cout << "ERROR" << endl;
		arr = vector<int>(initsize);
		output = 0;//弹出值索引
		input = 0;//压入值索引
		size = 0;//当前队列容量
	}
	void push(int val) {
		int len = arr.size();
		if (size == len)
			cout << "Full" << endl;
		else {
			size++;
			arr[input] = val;
			input = input == len - 1 ? 0 : input + 1;//运动到末尾从头继续运动
		}
	}
	int pop() {
		int len = arr.size();
		if (size == 0)
			cout << "Empty" << endl;
		else {
			size--;
			int temp = arr[output];
			output = output == len - 1 ? 0 : output + 1;//运动到末尾从头继续运动
			return temp;
		}
	}
};
/*************两个队列实现栈**************/
class queuetostack {
private:
	queue<int> data;
	queue<int> help;
public:
	void push(int val) {
		data.push(val);
	}
	int top() {
		return data.back();
	}
	int pop() {
		if (data.empty())
			cout << "Empty" << endl;
		else {
			while (data.size() > 1) {
				help.push(data.front());
				data.pop();
			}
			int res = data.front();
			data.pop();
			swap(data, help);
			return res;
		}
	}
};
/*************两个栈实现队列**************/
class stacktoqueue {
private:
	stack<int> spush;
	stack<int> spop;
public:
	void push(int val) {
		spush.push(val);
	}
	int front() {
		if (spush.empty() && spop.empty())
			cout << "Empty" << endl;
		else {
			if (spop.empty()) {
				while (!spush.empty()) {
					spop.push(spush.top());
					spush.pop();
				}
			}
			return spop.top();			
		}
		
	}
	int pop() {
		if (spush.empty() && spop.empty()) {
			cout << "Empty" << endl;
			return -1;
		}
		else {
			if (spop.empty()) {
				while (!spush.empty()) {
					spop.push(spush.top());
					spush.pop();
				}
			}
			int temp = spop.top();
			spop.pop();
			return temp;
		}
	}
};
int main()
{
	vector<int> arr{ 1,1,2,4,5,3,6,7,0,3,3 };
	
	return 0;
}

