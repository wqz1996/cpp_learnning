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
//输入n个整数，输出其中最小的k个。
int main() {
	int n,k;

	while (cin >> n >> k) {
		priority_queue<int,vector<int>,greater<>> q;
		int temp;
		for (int i = 0; i < n; i++) {
			cin >> temp;
			q.push(temp);
		}
		for (int i = 0; i < k; i++) {
			int res = q.top();
			q.pop();
			cout << res <<' ';
		}
		cout << endl;
	}
	
	return 0;
}

