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
using namespace std;
// 面试题11：旋转数组的最小数字
// 题目：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
// 输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如数组
// {3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}的一个旋转，该数组的最小值为1。
int getmininorder(int arr[], int len) {
	int min = 0;
	for (int i = 1; i < len; i++) {
		if (arr[i] < arr[min])
			min = i;

	}
	return arr[min];
}

int getMin(int arr[], int len) {
	int p1 = 0;
	int p2 = len - 1;
	int mid = p1;
	int minnum = p1;
	while (arr[p1] >= arr[p2]) {
		if (p2 - p1 == 1) {
			minnum = p2;
			break;
		}
		mid = (p1 + p2) / 2;
		if (arr[p1] == arr[mid] && arr[p2] == arr[mid] && arr[p1] == arr[p2]) {
			return getmininorder(arr, len);
		}
		if (arr[mid] >= arr[p1])
			p1 = mid;
		if (arr[mid] <= arr[p2])
			p2 = mid;
	}

	return arr[minnum];

}
/**************在线IDE************/
class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		int len = rotateArray.size();
		int p1 = 0;
		int p2 = len - 1;
		int mid;
		int minnum = p1;
		while (rotateArray[p1] >= rotateArray[p2]) {
			if (p2 - p1 == 1) {
				minnum = p2;
				break;
			}
			mid = p1 + (p2 - p1) / 2;
			if (rotateArray[p1] == rotateArray[mid] && rotateArray[p2] == rotateArray[mid] && rotateArray[p2] == rotateArray[p1]) {
				return getmininorder(rotateArray);
			}
			if (rotateArray[p1] <= rotateArray[mid])
				p1 = mid;
			if (rotateArray[p2] >= rotateArray[mid])
				p2 = mid;

		}
		return rotateArray[minnum];
	}
	int getmininorder(vector<int> v) {
		int len = v.size();
		int min = 0;
		for (int i = 1; i < len; i++) {
			if (v[i] < v[min])
				min = i;
		}
		return v[min];
	}

};
int main()
{
	Solution s;
	vector<int> v{ 1,0,1,1,1 };
	int arr[] = { 3,4,5,1,2 };
	int arr1[] = { 1,2,3,4,5 };
	int arr2[] = { 1,0,1,1,1 };
	int len = sizeof(arr2) / sizeof(int);
	cout << s.minNumberInRotateArray(v) << endl;
	//cout << getMin(arr2,len) << endl;
	return 0;

}



