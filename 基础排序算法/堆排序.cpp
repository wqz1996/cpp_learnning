#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
#include<set>
#include<map>
using namespace std;
void heapinsert(vector<int>& arr, int index) {
	while (arr[index] > arr[(index - 1) / 2]) {//index==0,(index-1)/2==0不进入循环
		swap(arr[index], arr[(index - 1) / 2]);//与父节点交换
		index = (index - 1) / 2;//更新下标到父节点位置继续比较交换直到到最顶端
	}
}
void heapify(vector<int>& arr, int index, int heapsize) {//当堆中某个数值改变，重新生成大根堆
	int left = index * 2 + 1;//当前节点左孩子下标
	int right = index * 2 + 2;//当前节点右孩子下标
	while (left < heapsize) {//左孩子小于堆的最大值
		int largest = (right<heapsize && arr[right]>arr[left]) ? right : left;//选取左右孩子最大值的下标
		largest = (arr[largest] > arr[index]) ? largest : index;//最大值是左右孩子和当前节点的最大值的下标
		if (largest == index)//若当前值比左右孩子的最大值大，则跳出循环完成交换
			break;
		swap(arr[largest], arr[index]);//交换当前节点与左右孩子的最大值
		index = largest;//更新索引为左右孩子的最大值
		left = index * 2 + 1;
		right = index * 2 + 2;
	}
}
void heapsort(vector<int>& arr) {//堆排序（升序）
	int heapsize = arr.size();
	for (int i = 0; i < heapsize; i++)
		heapinsert(arr, i);//先将数组形成大顶堆
	while (heapsize > 0) {//未超过堆的边界
		swap(arr[0], arr[--heapsize]);//重复操作
		heapify(arr, 0, heapsize);//将弹出堆底后的整个堆重新调整为大顶堆		
	}
}
int main()
{
	vector<int> arr{ 1,1,2,4,5,3,6,7,0,3,3 };
	heapsort(arr);
	
	return 0;
}

