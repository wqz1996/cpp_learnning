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
int getMax(int arr[], int L, int R) {//寻找数组中最大值：将数组分为左右，左边最大值和右边最大值的最大值即为全局最大值
	if (L == R) {
		return arr[L];
	}
	int mid = (L + R) / 2;
	int maxleft = getMax(arr, L, mid);
	int maxright = getMax(arr, mid + 1, R);
	return max(maxleft, maxright);

}
int main()
{
	int arr[5] = { 2, 5, 1, 3, 4 };
	int len = sizeof(arr) / sizeof(int);
	cout << getMax(arr, 0, len);

	return 0;


}