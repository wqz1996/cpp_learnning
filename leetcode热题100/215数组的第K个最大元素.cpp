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
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int,vector<int>,greater<>> q;
		int len = nums.size();
		if (k <= 0)
			return -1;
		for (int i = 0; i < k; i++)
			q.push(nums[i]);
		for (int i = k; i < len; i++) {
			if (nums[i] > q.top()) {
				q.pop();
				q.push(nums[i]);
			}
		}
		return q.top();
	}
};
/****************自己实现堆结构****************/
class heapbymy {
public:
	void heapinsert(vector<int>& arr, int index) {//小根堆
		while (arr[index] < arr[(index - 1) / 2]) {
			swap(arr[index], arr[(index - 1) / 2]);
			index = (index - 1) / 2;
		}			
	}
	void heapify(vector<int>& arr, int index, int heapsize) {
		int left = index * 2 + 1;
		int right = index * 2 + 2;
		while (left < heapsize) {
			int smallest = (right < heapsize && arr[left] >= arr[right]) ? right : left;
			smallest = (arr[smallest] <= arr[index]) ? smallest : index;
			if (smallest == heapsize)
				break;
			swap(arr[smallest], arr[index]);
			index = smallest;
			left = index * 2 + 1;
			right = index * 2 + 2;
		}
	}
	int findKthLargest(vector<int>& nums, int k) {
		int len = nums.size();
		int heapsize = k;
		for (int i = 0; i < k; i++)
			heapinsert(nums, i);
		for (int i = k; i < len; i++) {
			if (nums[i] > nums[0]) {
				swap(nums[0], nums[i]);
				heapify(nums, 0, heapsize);
			}
		}
		return nums[0];
		
	}
};
int main()
{
	vector<int> nums{ 3, 2, 3, 1, 2, 4, 5, 5, 6 };
	heapbymy().findKthLargest(nums, 4);

	return 0;
}

