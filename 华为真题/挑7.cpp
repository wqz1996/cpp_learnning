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
//输出7有关数字的个数，包括7的倍数，还有包含7的数字（如17，27，37...70，71，72，73...）的个数（一组测试用例里可能有多组数据，请注意处理）
using namespace std;
int main() {
	int n;
	while (cin >> n) {
		int res = 0;
		if (n < 7) {
			res = 0;
		}
		else {
			for (int i = 7; i <= n; i++) {
				if ((i % 7) == 0 || (i % 10) == 7 || (i % 100) / 10 == 7 || (i % 1000) / 100 == 7 || (i % 10000) / 1000 == 7)
					res++;
			}
		}
		cout << res << endl;
	}

	return 0;
}

