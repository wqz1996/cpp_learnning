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
double random0_1() {
	return (rand() / (RAND_MAX + 1.0));

}
/****************快速排序与荷兰国旗***********************************/
void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
/*************************荷兰国旗问题1*************************************/
int* partition(int arr[], int L, int R) {//以最后一个数做划分，将整个数组分为两个部分,返回中间等于区域的下标
	int less = L - 1;//小于区域开始为-1，即空
	int more = R;//大于区域为最后一个数,
	while (L < more) {
		if (arr[L] < arr[R])//调整小于区域 arr[R]为划分区域的数
			swap(arr, ++less, L++);//当前值与小于区域的下一个值交换，less扩一个，然后跳到下一个数
		else if (arr[L] > arr[R])
			swap(arr, --more, L);//与大于区域的前一个数交换，停在原地，将大于区域的前一个数继续作比较
		else
			L++;//即arr[L]==arr[R],直接跳下一个
	}
	swap(arr, more, R);//将数组中最后的数与大于区域第一个数交换，保证划分的数在中间
	return new int[2]{ less + 1, more };//返回等于区域的下标
}
/************************荷兰国旗问题2******************************************************************/
int* partitionisland(int arr[], int L, int R, int num) {
	int less = L - 1;
	int more = R + 1;
	int cur = L;
	while (cur < more) {
		if (arr[cur] < num) {
			swap(arr, ++less, cur++);
		}
		else if (arr[cur] > num) {
			swap(arr, --more, cur);
		}
		else {
			cur++;

		}

	}
	return new int[2]{ less + 1,more - 1 };
}
/*************************改进快速排序*******************************************///复杂度与数据状况有关O(N)或O(N^2)
void quicksort(int arr[], int L, int R) {
	if (L < R) {
		int* p = partition(arr, L, R);
		quicksort(arr, L, *p - 1);//从左边到等于区域前一个
		quicksort(arr, *(p + 1) + 1, R);//从等于区域后一个到右边
	}
}
/****************************随机快排*********************************************///在数组中随机选一个数作为区分的数，统计来讲复杂度O(N*logN)
void randomquicksort(int arr[], int L, int R) {
	if (L < R) {
		swap(arr, L + (int)(random0_1() * (R - L + 1)), R);//将末尾的数随机与中间的一个数交换
		int* p = partition(arr, L, R);
		randomquicksort(arr, L, *p - 1);//从左边到等于区域前一个
		randomquicksort(arr, *(p + 1) + 1, R);//从等于区域后一个到右边
	}
}

int main()
{
	int arr[11] = { 1,1,2,4,5,3,6,7,0,3,3 };
	int len = sizeof(arr) / sizeof(int);
	/*quicksort(arr, 0, len - 1);*/
	randomquicksort(arr, 0, len - 1);
	//int num = arr[10];
	//int* p= partitionisland(arr, 0, len - 1,num);
/***************荷兰国旗输出***************************/
	//for (int i = 0; i < *(p); i++) {
	//	cout << arr[i];
	//}
	//for (int i = *p; i < *(p + 1); i++) {
	//	cout << arr[i];
	//}
	//for (int i = *(p + 1); i <len; i++) {
	//	cout << arr[i];
	//}
/***************************************/
	for (int i = 0; i < len; i++)
		cout << arr[i];
	cout << endl;

	return 0;


}

