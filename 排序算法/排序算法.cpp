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
/****************排序算法***********************************/
void printarr(int arr[], int len) {
	for (int i = 0; i < len; i++)
		cout << arr[i] << ' ';
	cout << endl;
}
void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
/****************冒泡排序***********************************///时间复杂度O(n^2) 稳定的排序：当二者相等时不进行交换即可
void bubblesort(int arr[], int len) {

	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {

			if (arr[i] < arr[j]) {//降序排列  arr[i]>arr[j] 升序排列
				swap(arr, i, j);
			}
		}
	}
	printarr(arr, len);
}
/****************选择排序***********************************///时间复杂度O(n^2) 不稳定的排序：可能会使得相等的元素相对位置改变
void selectsort(int arr[], int len) {//升序
	int min;
	for (int i = 0; i < len; i++) {
		min = i;
		for (int j = i + 1; j < len; j++) {
			min = arr[j] < arr[min] ? j : min;

		}
		swap(arr, i, min);
	}
	printarr(arr, len);


}
/****************插入排序***********************************///真实时间复杂度与数据有关，最差时间复杂度O(n^2) 稳定的排序：遇到相等的数放在后面即可
void insertsort(int arr[], int len) {//当数据近似有序时可以退化为O(N)
	for (int i = 1; i < len; i++) {//当前位置
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)//
			swap(arr, j, j + 1);
	}
}
/****************归并排序***********************************///时间复杂度O(N*logN) 额外空间复杂度O(N) 稳定的排序：
void mergesort(int arr[], int L, int R) {
	if (L == R)
		return;
	int mid = L + (R - L) / 2;//L+((R-l)>>1) 求中点
	mergesort(arr, L, mid);//将左半部分排序
	mergesort(arr, mid + 1, R);//将有半部分排序

	int* help = new int[R - L + 1];
	int i = 0;
	int p1 = L;
	int p2 = mid + 1;
	while (p1 <= mid && p2 <= R) {//在p1没到mid并且p2没到R时循环
		*(help + i++) = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];//选择两个指针中较小的数放入help中
	}
	while (p1 <= mid) {//相当于p2越界，将p1后面所有的数放入help
		*(help + i++) = arr[p1++];
	}
	while (p2 <= R) {//相当于p1越界，将p2后面所有的数放入help
		*(help + i++) = arr[p2++];
	}
	int len = _msize(help) / sizeof(int);
	for (i = 0; i < len; i++) {
		arr[L + i] = *(help + i);
	}
}
int main()
{
	int arr[5] = { 2, 5, 1, 3, 4 };
	int len = sizeof(arr) / sizeof(int);
	mergesort(arr, 0, len - 1);
	//bubblesort(arr, n);
	//selectsort(arr, n);
	for (int i = 0; i < len; i++)
		cout << arr[i] << ' ';
	cout << endl;
	return 0;


}

