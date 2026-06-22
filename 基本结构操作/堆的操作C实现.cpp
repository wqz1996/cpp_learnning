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
void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;

}
//大顶堆的实现
void heapinsert(int arr[], int index) {//堆插入数据
	while (arr[index] > arr[(index - 1) / 2]) {//与父节点比较 如果index=0->(index-1)/2=0,不进入循环
		swap(arr, index, (index - 1) / 2);//大于父节点则交换
		index = (index - 1) / 2;//更新下标到交换后的父节点位置
	}
}
void heapify(int arr[], int index, int heapsize) {//当堆中有某个元素数值改变，重新生成大根堆
	int left = index * 2 + 1;//当前位置左孩子下标
	int right = index * 2 + 2;//当前位置右孩子下标
	while (left < heapsize) {//当左孩子不越界
		int largest = (right < heapsize && arr[right] > arr[left]) ? right : left;//左孩子存在且右孩子不越界，选左孩子和右孩子最大的下标
		largest = (arr[largest] > arr[index]) ? largest : index;//最大值为当前值和左右孩子的最大值中的最大值
		if (largest == index)//如果当前值比左右孩子大，则已经完成
			break;
		swap(arr, largest, index);//当前值小于左右孩子的最大值，与左右孩子的最大值交换
		index = largest;//来到下一个子树
		left = index * 2 + 1;//更新左右孩子下标
		right = index * 2 + 2;
	}
}
void heapsort(int arr[],int len) {//堆排序（升序）
	for (int i = 0; i < len; i++)
		heapinsert(arr, i);//先将数组形成大顶堆
	int heapsize = len;
	swap(arr, 0, --heapsize);//将堆顶元素与堆底元素交换，并弹出堆底
	while (heapsize > 0) {//未超过堆的边界
		heapify(arr, 0, heapsize);//将弹出堆底后的整个堆重新调整为大顶堆
		swap(arr, 0, --heapsize);//重复操作
	}
}
int main()
{
	int arr[11] = { 1,1,2,4,5,3,6,7,0,3,3 };
	int len = sizeof(arr) / sizeof(int);

	heapsort(arr, len);
	for (int i = 0; i < len; i++)
	cout << arr[i];
	cout << endl;

	return 0;

	
}

