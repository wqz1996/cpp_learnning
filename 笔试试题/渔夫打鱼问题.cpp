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
int res;
int findmethor(int n, int k,int index,int rest) {
	if (index == 2 * n + 1) {
		if (rest == 0)
			res++;
		return rest;
	}
	if(index==1)
		rest = findmethor(n, k, index + 1, rest + 1);
	else if (index != k) {
		rest = findmethor(n, k, index + 1,rest + 1);
		rest = findmethor(n, k, index + 1, rest - 1);
	}
	else if(index==k){
		rest = findmethor(n, k, index + 1, rest - 1);
	}
	return rest;

}
int main()
{

	int n, k;
	while (cin >> n >> k) {
		res = 0;
		findmethor(n,k,1,0);
		cout << res << endl;
	}

	return 0;
}
