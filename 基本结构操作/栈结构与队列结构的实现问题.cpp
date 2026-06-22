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
using namespace std;
/*******************基本类型实现栈、队列等*******************************************/
/****************实现特殊的栈，在栈中返回最小元素，要求pop，push，getmin时间复杂度为O(1)*********************/
//设计两个栈，一个为data，另一个为min栈
//首先将数据压入data栈，同时压入min栈
//再压入数据时，将数据与min栈栈顶比较，若小于栈顶则压入，若大于栈顶则重复压入min栈栈顶
//弹出时同步弹出
class specialstack {
private:
	stack<int> stackdata;
	stack<int> stackmin;
public:
	void specialpush(int obj) {
		if (this->stackmin.empty()) {
			this->stackmin.push(obj);
		}
		else if(obj<this->stackmin.top())
		{
			this->stackmin.push(obj);
		}
		else {
			this->stackmin.push(this->stackmin.top());
		}
		this->stackdata.push(obj);
	}
	int specialpop() {
		if (this->stackdata.empty()) {
			cout << "this stack is empty" << endl;
		}
		this->stackmin.pop();
		int temp = this->stackdata.top();
		this->stackdata.pop();
		return temp;
	}
	int getmin() {
		if (this->stackmin.empty()) {
			cout << "this stack is empty" << endl;
		}
		return this->stackmin.top();
	}
	
};
/**********使用固定数组实现栈**********/
class ArrayStack {
private:
	int* arr;
	int index;
public:
	void creatstack(int initsize) {//固定数组实现栈，需要确定初始空间大小
		if (initsize < 0)
			cout << "ERROR" << endl;
		arr = new int[initsize];//初始化数组
		index = 0;//当前指针
	} 
	int top() {
		if (index == 0)
			return NULL;
		return arr[index - 1];//返回当前指针的前一个元素
	}
	void push(int obj) {
		if (index == _msize(arr) / sizeof(int))
			cout << "the stack is full" << endl;
		arr[index++] = obj;
	}
	int pop() {
		if (index == 0)
			cout << "the stack is empty" << endl;
		return arr[--index];//由于index当前指向为栈顶的下一个元素，要先减1
	}
};
/****************固定数组实现队列***********************************/
class Arrayqueue {
private:
	int* arr;
	int output;//输出指针
	int input;//输入指针
	int size;//记录当前队列的容量
public:
	void creatqueue(int initsize){
		if (initsize < 0)
			cout << "ERROR" << endl;
		arr = new int[initsize];
		input = 0;
		output = 0;
		size = 0;

	}
	void push(int obj) {
		int len = _msize(arr) / sizeof(int);
		if (size == len) //当队列容量满了
			cout << "the queue is full" << endl;
		else {
			size++;
			arr[input] = obj;
			input = input == len - 1 ? 0 : input + 1;//size未满时，input指针运动到底以后返回顶部循环运动
		}
			

	}
	int pop() {
		if (size == 0)
			cout << "the queue is empty" << endl;
		else {
			int len = _msize(arr) / sizeof(int);
			size--;//每弹出一个数队列容量减 1
			int temp = output;//需要记录output当前指向的值，在移动指针以后进行返回
			output = output == len - 1 ? 0 : output + 1;//size非空时，output指针追end指针，运动到底以后同样返回顶部，循环运动
			return arr[temp];

		}
		
	}

};
/************************用队列实现栈**************************************/
//用两个队列实现
class queuetostack {
private:
	queue<int> q;
	queue<int> help;
public:
	void stackpush(int obj) {
		q.push(obj);
	}
	int stackpop() {//将最后一个进入q队列的元素保留，其他的进入到help队列，返回并弹出q中的元素
		if (q.empty()) {
			cout << "this stack is empty" << endl;
		}
		while (q.size() > 1) {
			help.push(q.front());
			q.pop();
		}
		int res = q.front();
		q.pop();
		swap(q, help);
		return res;
		
	}
	int stacktop() {
		return q.back();
	}

};
/**************************用栈实现队列**************************************/
class stacktoqueue {
private:
	stack<int> stackpush;
	stack<int> stackpop;
public:
	void queuepush(int obj) {
		stackpush.push(obj);
	}
	void queuepop() {//弹出时先将stackpush栈中所有数据弹出并压入stackpop栈中，然后将stackpop栈顶元素弹出
		if (stackpush.empty() && stackpop.empty()) {
			cout << "this queue is empty" << endl;
		}
		rechange();
		stackpop.pop();
	}
	int queuefront() {
		if (stackpush.empty() && stackpop.empty()) {
			cout << "this queue is empty" << endl;
		}
		rechange();
		return stackpop.top();
	}
	void rechange() {//将stackpush栈中所有数据弹出并压入stackpop栈中
		if (!stackpop.empty())
			return;
		while (!stackpush.empty()) {
			stackpop.push(stackpush.top());
			stackpush.pop();
		}
	}
};
int main()
{
	ArrayStack s;
	Arrayqueue q;
	specialstack s1;
	stacktoqueue que;
	int arr[5] = { 2,0,3,6,8 };
	for (int i = 0; i < 5; i++) {
		que.queuepush(arr[i]);
	}
	cout << que.queuepop() << endl;
	/*q.creatqueue(5);
	s.creatstack(5);
	for (int i = 0; i < 5; i++) {
		s.push(i);
	}
	for (int i = 0; i < 5; i++) {
		q.push(i);
	}
	q.push(1);*/
	//s1.specialpush(1);
	//s1.specialpop();
	//cout << s1.getmin()<< endl;

	/*cout << q.pop() << endl;*/
	//cout << s.getpeek()<< endl;
	//cout << s.pop() << endl;
	//cout << s.getpeek() << endl;

	return 0;

	
}

