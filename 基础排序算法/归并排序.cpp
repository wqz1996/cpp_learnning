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
void mergesort(vector<int>& arr, int L, int R) {
	if (L == R)//递归终止条件
		return;
	int mid = L + ((R - L)>> 1);//要考虑运算符优先级>>的优先级低，必须加括号
	mergesort(arr, L, mid);//先将左半部分排序
	mergesort(arr, mid + 1, R);
	vector<int> help(R - L + 1);//辅助数组
	int i = 0;
	int p1 = L;
	int p2 = mid + 1;
	while (p1 <= mid && p2 <= R) {//在p1没到mid并且p2没到R时循环
		help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];//升序排列
	}
	while (p1 <= mid) {//p2越界，将p1后面数组存入help
		help[i++] = arr[p1++];
	}
	while (p2 <= R)//p1越界，将p2后面数组存入help
		help[i++] = arr[p2++];
	for (i = 0; i < help.size(); i++) {//将辅助数组中的元素拷贝回原数组
		arr[L + i] = help[i];
	}

}

int main()
{
	vector<int> arr{ 2,5,1,3,4 };
	mergesort(arr, 0, arr.size() - 1);
	
	return 0;
}

