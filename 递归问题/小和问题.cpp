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
/****************小和问题***********************************///一个数组中当每一个数左边比当前数小的数累加起来叫做数组的小和
//在merge过程中求得小和，将
int merge1(int arr[], int L, int mid, int R) {
	int* help = new int[R - L + 1];
	int i = 0;
	int p1 = L;//左部分第一个数
	int p2 = mid+1;//右部分第一个数
	int res = 0;//merge过程中的小和
	while (p1 <= mid && p2 <= R) {
		res += arr[p1] < arr[p2] ? arr[p1] * (R - p2 + 1) : 0;//若arr[p1]<arr[p2]则存在（R-p2+1）个比arr[p1]大的数
		*(help + i++) = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= mid) {
		*(help + i++) = arr[p1++];
	}
	while (p2 <= R) {
		*(help + i++) = arr[p2++];
	}
	int len = _msize(help) / sizeof(int);
	for (int i = 0; i < len; i++)
		arr[L + i] = *(help + i);
	return res;



}
int smallSum(int arr[], int L, int R) {
	if (L == R)
		return 0;
	int mid = L + (R - L)/2;//求取中间位置
	return smallSum(arr, L, mid) + smallSum(arr, mid + 1, R) + merge1(arr, L, mid, R);//左侧产生的小和与右侧产生的小和以及merge过程中产生的小和
}
int main()
{
	int arr[5] = { 1,3,4,2,5 };
	int len = sizeof(arr) / sizeof(int);
	cout << smallSum(arr, 0, len-1) << endl;

	return 0;

	
}

