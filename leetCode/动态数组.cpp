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
template<typename T>//MyVector<int...double>
/*************动态数组*******************/
class MyVector {
private:
	T* data;
	int capacity;
	int size;
	void resize(int newcapacity) {//开辟新的空间O(N)
		assert(newcapacity >= size);
		T* newdata = new int[newcapacity];
		for (int i = 0; i < size; i++) {
			newdata[i] = data[i];
		}
		delete[] data;
		data = newdata;
		capacity = newcapacity;
	}
public:
	MyVector() {
		data = new T[10];
		capacity = 10;
		size = 0;

	}
	~MyVector() {
		delete[] data;
	}
	void push_back(T e) {

		if (size == capacity)
			resize(2 * capacity);
		data[size++] = e;
	}
	T pop_back() {
		T ret = data[size];
		assert(size > 0);
		size--;
		if (size == capacity / 4)
			resize(capacity / 2);
		return ret;
		
	}


};
/*************时间复杂度测试程序*************/
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

};
int main() {

	for (int i = 10; i <= 26; i++) {
		int n = pow(2, i);
		int* arr = Mytest().generateRandomArray(n, 0, 1000000000);
		/*int* arr = Mytest().genarateOrdererArray(n);*/
		clock_t starttime = clock();
		//Mytest().findMax(arr, n);
		MyVector<int> vec;
		for (int i = 0; i < n; i++) {
			vec.push_back(i);
		}
		for (int i = 0; i < n; i++) {
			vec.pop_back();
		}
		clock_t endtime = clock();
		cout << "data size 2^" << i << "=" << n << "\t";
		cout << "time cost:" << (double)(endtime - starttime) / CLOCKS_PER_SEC << endl;

		delete[] arr;
	}



	return 0;
}