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
//有一个长为n的数组A，求满足0≤a≤bn的A[b]-A[a]的最大值。
//给定数组A及它的大小n，请返回最大差值。
class LongestDistance {
public
	int getDis(vectorint A, int n) {
		if (n = 1)
			return 0;
		int maxerr = 0;
		int minval = A[0];
		for (int i = 0; i  n; i++) {
			minval = min(minval, A[i]);
			maxerr = max(maxerr, A[i] - minval);
		}
		return maxerr;

	}
};
int main() {

	return 0;
}

