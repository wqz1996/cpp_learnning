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
// 面试题3（一）：找出数组中重复的数字
// 题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
// 也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，
// 那么对应的输出是重复的数字2或者3。
int duplicate1(int arr[], int len) {//桶排序 时间复杂度O(N)，空间复杂度O(N)
	int* bot = new int[len] {0};
	if (arr == nullptr || len <= 0) {//空指针处理
		return -1;
	}
	for (int i = 0; i < len; i++) {
		if (arr[i]<0 || arr[i]>len - 1) {//输入合理判断
			cout << "the array is unlaw" << endl;
			return -1;
		}

		bot[arr[i]] += 1;
		if (bot[arr[i]] > 1)
			return arr[i];
	}
	return -1;

}
int duplicate2(int arr[], int len) {//时间复杂度O(N)，空间复杂度O(1)
	if (arr == nullptr || len <= 0) {//空指针处理
		return -1;

	}
	for (int i = 0; i < len; i++) {
		if (arr[i]<0 || arr[i]>len - 1)//输入合理判断
			return -1;
		while (arr[i] != i) {
			if (arr[i] == arr[arr[i]]) {
				return arr[i];
			}
			int temp = arr[arr[i]];
			arr[arr[i]] = arr[i];
			arr[i] = temp;
		}

	}
	return -1;


}
/***********在线IDE**********/
class Solution {
public:
	// Parameters:
	//        numbers:     an array of integers
	//        length:      the length of array numbers
	//        duplication: (Output) the duplicated number in the array number
	// Return value:       true if the input is valid, and there are some duplications in the array number
	//                     otherwise false
	bool duplicate(int numbers[], int length, int* duplication) {
		if (numbers == nullptr || length <= 0) {
			return false;
		}
		for (int i = 0; i < length; i++) {
			if (numbers[i]<0 || numbers[i]>length - 1) {
				return false;
			}
			while (numbers[i] != i) {
				if (numbers[i] == numbers[numbers[i]]) {
					*duplication = numbers[i];
					return true;
				}
				int temp = numbers[i];
				numbers[i] = numbers[temp];
				numbers[temp] = temp;
			}
		}
	}
};
int main()
{
	int arr[7] = { 4,3,1,0,2,5,3 };
	int len = sizeof(arr) / sizeof(int);
	cout << duplicate2(arr, len) << endl;
	return 0;

}



