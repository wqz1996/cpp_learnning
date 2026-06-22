#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
//面试题59 - II. 队列的最大值
// 请定义一个队列并实现函数 max_value 得到队列里的最大值，
//要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。
//若队列为空，pop_front 和 max_value?需要返回 - 1

class MaxQueue {
private:
	deque<int> dq;
	queue<int> q;
public:
	MaxQueue() {

	}

	int max_value() {
		if (dq.empty())
			return -1;
		return dq.front();
	}

	void push_back(int value) {
		//相当于维护一个递减数组
		while (!dq.empty() && dq.back() < value)
			dq.pop_back();//在队尾弹出所有比value小的
		dq.push_back(value);//将value放入队尾
		q.push(value);
	}

	int pop_front() {
		if (q.empty())
			return -1;
		int res = q.front();
		if (res == dq.front())//弹出的元素是最大的元素，则在dq中弹出队首
			dq.pop_front();
		q.pop();
		return res;
	}
};
int main()
{

	return 0;
}

