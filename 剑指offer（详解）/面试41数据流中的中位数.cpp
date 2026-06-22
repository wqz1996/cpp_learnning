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
//面试题41. 数据流中的中位数
// 题目：如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，
//那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶
//数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
/*********************堆实现***************************/
class MedianFinder {
private:
	vector<int> greatheap;//大根堆
	vector<int> lessheap;//小根堆
public:	
	/** initialize your data structure here. */
	MedianFinder() {

	}

	void addNum(int num) {
		

		if (greatheap.empty()) {
			greatheap.push_back(num);
			make_heap(greatheap.begin(), greatheap.end(), less<int>());//创建大根堆
		}
		else {
			if (num >= greatheap.front()) {
				lessheap.push_back(num);
				push_heap(lessheap.begin(), lessheap.end(), greater<int>());//创建小根堆
			}
			else {
				greatheap.push_back(num);
				push_heap(greatheap.begin(), greatheap.end(), less<int>());//重新生成大根堆
			}			
		}		
		
		int greatheapsize = greatheap.size();
		int lessheapsize = lessheap.size();
		if (greatheapsize - lessheapsize > 1) {//大根堆比小根堆元素数量多超过1时，将大根堆堆顶放入小根堆中

			pop_heap(greatheap.begin(), greatheap.end(), less<int>());//将大根堆中的堆顶放到数组最末尾
			lessheap.push_back(greatheap.back());//将大根堆中的末尾数据放入小根堆中
			greatheap.pop_back();//弹出大根堆末尾元素
			push_heap(lessheap.begin(), lessheap.end(), greater<int>());//重新生成小根堆
			
		}
		if (lessheapsize - greatheapsize > 1) {//小根堆比大根堆元素数量多超过1时，将小根堆堆顶放入大根堆中

			pop_heap(lessheap.begin(), lessheap.end(), greater<int>());//将小根堆中的堆顶放到数组最末尾
			greatheap.push_back(lessheap.back());//将小根堆中的末尾数据放入大根堆中
			lessheap.pop_back();//弹出小根堆末尾元素
			push_heap(greatheap.begin(), greatheap.end(), less<int>());//重新生成大根堆

		}
		
	}

	double findMedian() {
		if (greatheap.size() == lessheap.size())
			return (((double)greatheap.front() + (double)(lessheap.front())) / 2.0);
		else if(greatheap.size() > lessheap.size())
			return (double)greatheap.front();
		else 
			return (double)lessheap.front();
	}
};
/********************优先队列*******************/
class MedianFinder {
private:
	priority_queue<int> big;//大根堆
	priority_queue<int, vector<int>, greater<>> small;//小根堆
public:
	MedianFinder() {

	}

	void addNum(int num) {
		if (big.empty())
			big.push(num);
		else {
			if (big.top() <= num)
				small.push(num);
			else
				big.push(num);
		}
		int error = big.size() - small.size();//vector.size()是无符号整数，（0-1）会越界
		if (error > 1) {
			small.push(big.top());
			big.pop();
		}
		else if (error < -1) {
			big.push(small.top());
			small.pop();
		}

	}

	double findMedian() {
		if (big.size() == small.size())
			return ((double)(big.top() + small.top()) / 2.0);
		else if (big.size() > small.size())
			return (double)big.top();
		else
			return (double)small.top();
	}
};
/********************优先队列*******************/
class MedianFinder {
private:
	priority_queue<int> greatheap;//大根堆
	priority_queue<int,vector<int>,greater<int>> lessheap;//小根堆
public:
	/** initialize your data structure here. */
	MedianFinder() {

	}

	void addNum(int num) {
		greatheap.push(num);//先将数据放入大根堆
		lessheap.push(greatheap.top());//将大根堆堆顶数据放入小根堆，保证是大根堆中最大的数
		greatheap.pop();
		if (greatheap.size() < lessheap.size()) {//当两边不平衡时移动
			greatheap.push(lessheap.top());
			lessheap.pop();
		}
		
	}

	double findMedian() {
		if (greatheap.size() > lessheap.size())
			return (double)greatheap.top();
		else
			return (((double)greatheap.top() + (double)lessheap.top()) / 2.0);
	}
};

int main()
{
	MedianFinder test;
	test.addNum(1);
	test.addNum(2);
	cout << test.findMedian() << endl;
	test.addNum(3);
	cout << test.findMedian() << endl;
	


	return 0;
}

