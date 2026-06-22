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
using namespace std;
/*************测试时间复杂度*******************/
class Mytest {
public:
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
	int* generateRandomArray(int n, int RangeL, int RangeR) {//生成长度为n，范围从RangeL到RangeR的数组
		assert(n > 0 && RangeL <= RangeR);
		int* arr = new int[n];
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			arr[i] = rand() % (RangeR - RangeL + 1) + RangeL;
		}
		return arr;
	}
	int* genarateOrdererArray(int n) {//生成长度为n的有序数组
		assert(n > 0);
		int* arr = new int[n];
		for (int i = 0; i < n; i++) {
			arr[i] = i;
		}
		return arr;
	}
	//二分查找O(logN)
	int binarySearch(int arr[], int n, int target) {
		int L = 0;
		int R = n - 1;
		while (L <= R) {
			int mid = L + (R - L) / 2;
			if (arr[mid] == target)
				return mid;
			if (arr[mid] > target)
				R = mid - 1;
			else
				L = mid + 1;
		}
		return -1;

	}
	//寻找最大值O(N)
	int findMax(int arr[], int n) {
		assert(n > 0);
		int max=0;
		for (int i = 0; i < n; i++) {
			if (arr[i] > arr[max])
				max = i;
		}
		return arr[max];
	}
	//选择排序
	void selectionSort(int arr[], int n) {
		for (int i = 0; i < n; i++) {
			int min = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[min])
				{
					swap(arr,j, min);
				}
					
			}
		}
	}
	void insertsort(int arr[], int len) {//当数据近似有序时可以退化为O(N)
		for (int i = 1; i < len; i++) {//当前位置
			for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) 
				swap(arr, j, j + 1);
		}
	}
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

};
int main() {

	for (int i = 10; i <= 15; i++) {
		int n = pow(2, i);
		int* arr=Mytest().generateRandomArray(n, 0, 1000000000);
		/*int* arr = Mytest().genarateOrdererArray(n);*/
		clock_t starttime = clock();
		//Mytest().findMax(arr, n);
		Mytest().insertsort(arr, n);
		clock_t endtime = clock();
		cout << "data size 2^" << i << "=" << n << "\t";
		cout << "time cost:" << (double)(endtime - starttime) / CLOCKS_PER_SEC << endl;

		delete[] arr;
	}
	//int arr[] = { 2,3,6,1,7,5 };
	//int len = sizeof(arr) / sizeof(int);
	//Mytest().insertsort(arr, len);
	//for (int i = 0; i < len; i++)
	//	cout << arr[i] << ' ';
	//cout << endl;


	return 0;
}