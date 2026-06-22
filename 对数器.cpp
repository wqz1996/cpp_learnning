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
/*******************对数器**********************************/
double getrandom() {
	srand(time(0));
	double num = (rand() % 100 / (double)101);
	return num;
}
int* copyArray(int* arr) {
	int len = _msize(arr) / sizeof(int);
	int* res = new int[len];
	for (int i = 0; i < len; i++) {
		res[i] = arr[i];
	}
	return res;
}
int* generateRandomArray(int size, int value) {//size 数组最大长度 value 
	int cursize = (int)(size + 1) * getrandom();
	int* arr = new int[cursize];
	for (int i = 0; i < cursize; i++) {
		arr[i] = (int)((value + 1) * rand()) - (int)(value * getrandom());
	}
	return arr;
}
void logUse() {
	int testtime = 500000;
	int size = 10;
	int value = 100;
	bool issucceed = true;
	for (int i = 0; i < testtime; i++) {
		int* arr1 = generateRandomArray(size, value);
		int* arr2 = copyArray(arr1);
		int* arr3 = copyArray(arr1);

	}

}
