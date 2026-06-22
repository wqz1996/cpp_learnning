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
void bubblesort(vector<int>& arr) {//冒泡
	for (int i = 0; i < arr.size(); i++) {
		for (int j = i + 1; j < arr.size(); j++) {
			if (arr[j] < arr[i])
				swap(arr[i], arr[j]);
		}
	}
}
void selectsort(vector<int>& arr) {//选择
	int min;
	for (int i = 0; i < arr.size(); i++) {
		min = i;
		for (int j = i + 1; j < arr.size(); j++) {
			min = arr[j] < arr[min] ? j : min;//在i+1到末尾范围找到最小的元素
		}
		swap(arr[i], arr[min]);//与当前元素进行交换
	}
}
void insertsort(vector<int>& arr) { // 插入
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
			swap(arr[j], arr[j + 1]);
	}
}
int main()
{
	vector<int> arr{ 2,5,1,3,4 };
	bubblesort(arr);
	
	return 0;
}

