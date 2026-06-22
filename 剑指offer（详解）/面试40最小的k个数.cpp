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
#include<set>
#include<map>
using namespace std;
//面试题40. 最小的k个数
// 题目：输入整数数组 arr ，找出其中最小的 k 个数。
//例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。
/****************简单方法*******************/
class Solution {
public:
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		vector<int> res;
		sort(arr.begin(), arr.end());
		for (int i = 0; i < k; i++)
			res.push_back(arr[i]);
		return res;
	}
};
/**************优先级队列*****************/
class Solution1 {
public:
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		vector<int> res;
		priority_queue<int> q;
		if (k == 0)
			return res;
		for (int i = 0; i < k; i++)
			q.push(arr[i]);
		for (int i = k; i <(int)arr.size(); i++) {
			if (arr[i] < q.top()) {
				q.pop();
				q.push(arr[i]);
			}				
		}
		while (!q.empty()) {
			res.push_back(q.top());
			q.pop();
		}
		return res;
	}
};
/***************快速选择**********************/
class Solution {
private:
	int partition(vector<int>& arr, int L, int R) {//分区
		int less = L - 1;
		int more = R;
		while (L < more) {
			if (arr[L] < arr[R])
				swap(arr[++less], arr[L++]);
			else if (arr[L] > arr[R])
				swap(arr[--more], arr[L]);
			else
				L++;
		}
		swap(arr[more], arr[R]);
		return less + 1;//返回等于区域的第一个下标
	}
	void partitionArray(vector<int>& arr, int left, int right, int k) {
		int m = partition(arr, left, right);//
		if (k == m)//找到了前k个元素[0,k)
			return;
		else if (k < m)//若k<m则一定在左半部分继续分区
			partitionArray(arr, left, m - 1, k);//注：k为下标
		else
			partitionArray(arr, m + 1, right, k);//k>m在右半部分继续partition，找到k

	}
public:
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		vector<int> res;
		if (k == 0)
			return res;
		if (k >= arr.size())
			return arr;;
		partitionArray(arr, 0, arr.size() - 1, k);//将前k+1个元素完成排序[0,k]
		for (int i = 0; i < k; i++)//[0,k)一共k个元素
			res.push_back(arr[i]);
		return res;

	}
};
int main()
{
	vector<int> arr{ 0,1,2,1 };
	Solution1().getLeastNumbers(arr, 1);
	
	return 0;
}

