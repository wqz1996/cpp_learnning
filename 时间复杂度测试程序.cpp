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
#include<assert.h>
#include<set>
#include<map>
using namespace std;
class Mytest {
public:
	void printarr(vector<int> arr) {
		for (int i = 0; i < arr.size(); i++)
			cout << arr[i] << ' ';
		cout << endl;
	}
	vector<int> generateRandomArray(int n, int RangeL, int RangeR) {//生成长度为n，范围从RangeL到RangeR的数组
		assert(n > 0 && RangeL <= RangeR);
		vector<int> arr(n);
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			arr[i] = rand() % (RangeR - RangeL + 1) + RangeL;
		}
		return arr;
	}
	vector<int> genarateOrdererArray(int n) {//生成长度为n的有序数组
		assert(n > 0);
		vector<int> arr(n);
		for (int i = 0; i < n; i++) {
			arr[i] = i;
		}
		return arr;
	}
/**********待测试程序***********/
private:
	vector<int> partition(vector<int>& arr, int L, int R) {
		int less = L - 1;
		int more = R;
		while (L < more) {
			if (arr[L] < arr[R]) {
				swap(arr[++less], arr[L++]);
			}
			else if (arr[L] > arr[R]) {
				swap(arr[--more], arr[L]);
			}
			else {
				L++;
			}
		}
		swap(arr[more], arr[R]);
		return vector<int>{less + 1, more};
	}
	void quicksort(vector<int>& arr, int L, int R, int k) {
		swap(arr[R], arr[L + (int)(rand() / (RAND_MAX + 1.0)) * (R - L + 1)]);
		vector<int> p = partition(arr, L, R);
		if (k == p[0])
			return;
		else if (k < p[0]) {
			quicksort(arr, L, p[0] - 1, k);
		}
		else {
			quicksort(arr, p[0] + 1, R, k);
		}
	}
public:
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		vector<int> res;
		if (k <= 0)
			return res;
		quicksort(arr, 0, arr.size() - 1, k);
		for (int i = 0; i < k; i++) {
			res.push_back(arr[i]);
		}
		return res;
	}
	

};
int main() {

	for (int i = 10; i <= 15; i++) {//测试数据长度的范围
		int n = pow(2, i);
		vector<int> arr = Mytest().generateRandomArray(n, 0, 1000000000);//生成长度为n，每个元素在[0,1000000000]的随机数组
		clock_t starttime = clock();
		Mytest().getLeastNumbers(arr, 5);
		clock_t endtime = clock();
		cout << "data size 2^" << i << "=" << n << "\t";
		cout << "time cost:" << (double)(endtime - starttime) / CLOCKS_PER_SEC << endl;
	}
	return 0;
}