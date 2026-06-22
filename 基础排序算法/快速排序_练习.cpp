#include <algorithm> //包含堆操作
#include <iostream>
#include <sstream> //istringstream 可以将string以空格为分隔符分割
#include <string>
#include <cmath>
#include <stack>  //栈
#include <queue>  //队列
#include <vector> //不注重插入和删除效率
#include <list>	  //类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include <deque>  //双端队列，兼顾随即存取，和两端数据的插入删除
#include <ctime>
#include < unordered_map>
#include < unordered_set>
#include <hash_map>
#include <hash_set>
#include <assert.h>
#include <set>
#include <map>
using namespace std;
vector<int> partition(vector<double> &arr, int L, int R)
{
	less = L - 1;
	more = R;
	while (L < more)
	{
		if (arr[L] < arr[R])
		{
			swap(arr[++less], arr[L++]);
		}
		else if (arr[L] > arr[R])
		{
			swap(arr[--more], arr[L])
		}
		else
		{
			L++;
		}
		swap(arr[more], arr[R]);
		return vector<int>{less + 1, R};
	}
}
void quicksort(vector<double> &arr, int L, int R)
{
	if (L >= R)
		return;
	vector<int> p = partition(arr, L, R);
	quicksort(arr, L, p[0] - 1);
	quicksort(arr, p[1] + 1, R);
}
int main()
{
	vector<int> arr{2, 5, 1, 3, 4};
	quicksort(arr, 0, arr.size());
	cout << "qize";
	return 0;
}
