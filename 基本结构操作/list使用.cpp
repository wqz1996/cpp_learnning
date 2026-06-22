#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
#include<vector>//不注重插入和删除效率
#include<list>//类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include<deque>//双端队列，兼顾随即存取，和两端数据的插入删除
using namespace std;
/****************list使用***********************************/
bool mycmp(const int &a, const int &b) {
	return a > b;
}
int main()
{

	list<int> first;
	list<int> second;
	list<int>::iterator t;
	vector<int> v(2, 30);//在数组中放入两个30
	first.push_back(2);//将元素加入到链表中
	first.push_back(1);
	first.push_back(4);
	second.push_back(3);
	second.push_back(6);
	second.push_back(5);
	first.assign(7, 100);//7个整形100相连接
	t = first.begin();
	advance(t, 2);//将指针指导第二个元素
	first.front();//访问第一个元素
	first.back();//访问最后一个元素
	first.push_front(3);//将3插入到开头
	first.pop_front();//将第一个元素删除 同理push_back()\pop_back()
	swap(first, second);//交换两个list内容
	first.clear();//清除所有内容
	first.erase(t);//动态删除对应位置的元素
	first.insert(t,10);//在t位置插入10  first.insert(t,2,10)在t位置插入两个10
	first.insert(t, 2, 10);// 在t位置插入两个10
	first.insert(t, v.begin(), v.end());//在t位置按顺序插入vector数组
	first.sort();//链表按照大小排序
	first.sort(mycmp);//链表按照自定义规则排序
	second.sort();//链表按照大小排序
	first.merge(second);//要求先排序才可以连接
	first.merge(second,mycmp);
	first.remove(3);//移除链表中所有匹配的元素
	first.unique();//清除重复值
	for (list<int>::iterator i = first.begin(); i != first.end(); ++i)
		cout << *i<<" ";
	cout << endl;
	for (list<int>::reverse_iterator i = first.rbegin(); i != first.rend(); ++i)//逆向遍历
		cout << *i << " ";
	cout << endl;
	for (list<int>::iterator i = second.begin(); i != second.end(); i++)
		cout << *i << " ";
	cout << endl;
	return 0;

	
}

