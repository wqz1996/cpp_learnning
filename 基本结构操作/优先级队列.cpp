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
/************279完全平方数*******************/
//给定正整数n，找到若干个完全平方数（1，4，9，16。。。）
//使得它们的和等于n，使得完全平方数个数最少
//提示：无权图
struct cmp {//自定义比较方式
	bool operator()(const int& a,const int& b) {
		return a % 10 < b % 10;
	}
};

int main() {
	srand(time(NULL));
	priority_queue<int> pq;//默认大顶堆
//等同于priority_queue<int, vector<int>, less<int>> pq;//生成小顶堆
	for (int i = 0; i < 10; i++) {
		int num = rand() % 100;
		pq.push(num);
	}
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
		cout << " ";
		
	}
	cout << endl;

	priority_queue<int,vector<int>,greater<int>> pq1;//生成小顶堆
	for (int i = 0; i < 10; i++) {
		int num = rand() % 100;
		pq1.push(num);
	}
	while (!pq1.empty()) {
		cout << pq1.top() << " ";
		pq1.pop();
		cout << " ";

	}
	cout << endl;
	//自定义比较方式
	priority_queue<int, vector<int>, cmp> pq2;
	for (int i = 0; i < 10; i++) {
		int num = rand() % 100;
		pq2.push(num);
	}
	while (!pq2.empty()) {
		cout << pq2.top() << " ";
		pq2.pop();
		cout << " ";

	}
	return 0;
} 