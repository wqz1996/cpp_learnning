#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
using namespace std;
struct node
{
	int x;
	int y;
	bool operator<(const node& a) const//重载运算符
	{
		return x < a.x; //大顶堆
	}

};

int main() {
	stack<int> s;//栈
	queue<int> q;//队列
	queue<node> my_q;//自定义类型
	int x=1;
	/****************栈操作************************/
	s.empty();//判断栈是否为空，返回bool类型
	s.size();//返回栈中元素个数
	s.pop();//弹出栈顶元素，但不返回值
	s.top();//返回栈顶元素，但不删除该元素
	s.push(x);//将栈顶压入新元素
	/**********************************************/

	/****************队列操作************************/
	q.empty();//判断队列是否为空，返回bool类型
	q.size();//队列元素个数
	q.pop();//删除队列首个元素。不返回值
	q.front();//返回队首元素的值，但不删除该元素
	q.back();//返回队尾元素的值，但不删除该元素
	q.push(x);//队尾压入新元素

	priority_queue<int, vector<int>, greater<int> > q;//用优先级队列实现小顶堆


}
