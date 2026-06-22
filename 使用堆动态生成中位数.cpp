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
/*******************循环输入，实时生成中位数*******************************************/
int main()
{
	int arr[11] = { 1,1,2,4,5,3,6,7,0,3,3 };
	int n;
	int len = sizeof(arr) / sizeof(int);
	vector<int> top;
	vector<int> down;
	int sizetop = 0;
	int sizedown = 0;
	while (cin >> n) {
		
		if (sizetop == 0) {//第一个数放到大顶堆中
			top.push_back(n);
			make_heap(top.begin(), top.end(), less<int>());
			sizetop++;
			cout << top[0] << endl;
			continue;

		}
		if (top[0] >= n) {//若第二个数小于等于大顶堆堆顶则放入大顶堆
			top.push_back(n);
			make_heap(top.begin(), top.end(), less<int>());
			sizetop++;
		}
		else {//若第二个数大于大顶堆堆顶则放入小顶堆
			down.push_back(n);
			make_heap(down.begin(), down.end(), greater<int>());
			sizedown++;
		}
		if ((sizetop - sizedown) > 1) {//当大顶堆比小顶堆大的数值超过1，则将大顶堆堆顶放入到小顶堆中
			down.push_back(top[0]);
			sizedown++;
			make_heap(down.begin(), down.end(), greater<int>());
			pop_heap(top.begin(), top.end(), less<int>());
			top.pop_back();
			sizetop--;
		}
		if ((sizedown - sizetop )> 1) {//当小顶堆比大顶堆大的数值超过1，则将小顶堆堆顶放入到大顶堆中
			top.push_back(down[0]); 
			sizetop++;
			make_heap(top.begin(), top.end(), less<int>());
			pop_heap(down.begin(), down.end(), greater<int>());
			down.pop_back();
			sizedown--;

		}
		if (sizetop == sizedown)//较小的(N/2)在大顶堆中，较大的(N/2)在小顶堆中，根据情况取两个堆顶元素即可得中位数
			cout << (float)((top[0] + down[0]) / 2) << endl;
		else if (sizetop > sizedown)
			cout << top[0] << endl;
		else
			cout << down[0] << endl;
		

	}
	//for (int i = 0; i < len; i++)
	//cout << arr[i];
	//cout << endl;

	return 0;

	
}

