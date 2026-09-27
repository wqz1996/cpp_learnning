#include <iostream> // cout、endl：main 输出两种堆实现结果
#include <utility> // swap：heapbymy 调整堆元素
#include <queue> // priority_queue：第 10 行首次使用
#include <vector> // vector：第 9 行首次使用
#include <functional> // greater：第 10 行首次使用
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
    vector<int> first{3, 2, 1};
    vector<int> second = first;
    cout << "标准优先队列: " << Solution().findKthLargest(first, 1) << endl;
    cout << "自写堆: " << heapbymy().findKthLargest(second, 1) << endl;
    return 0;
}
