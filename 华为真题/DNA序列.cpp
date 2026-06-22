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
//一个DNA序列由A/C/G/T四个字母的排列组合组成。G和C的比例（定义为GC-Ratio）是序列中G和C两个字母的总的出现次数除以总
//的字母数目（也就是序列长度）。在基因工程中，这个比例非常重要。因为高的GC-Ratio可能是基因的起始点。

//给定一个很长的DNA序列，以及要求的最小子序列长度，研究人员经常会需要在其中找出GC - Ratio最高的子序列。
int ratio(string s) {
	int count = 0;
	int len = s.size();
	for (int i = 0; i < len; i++) {
		if (s[i] == 'C' || s[i] == 'G')
			count++;
	}
	return count;
}
int main() {
	string s;
	int k;
	while (cin >> s >> k) {
		int p1 = 0;
		int p2 = k-1;
		int len = s.size();
		int maxratio = 0;
		string res;
		string temp;
		while (p2 < s.size()) {
			temp = s.substr(p1, p2 - p1 + 1);
			int count = ratio(temp);
			if (count > maxratio)
				res = temp;
			maxratio = max(count, maxratio);
			p1++;
			p2++;
		}
		cout << res << endl;
		

	}
	return 0;
}
