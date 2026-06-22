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
	string s;

	while (cin >> s) {
		map<char, pair<int,int>> m;
		for (int i = 0; i < s.size(); i++) {
			if (m.find(s[i]) == m.end()) {
				m[s[i]].first = i;
			}			
			m[s[i]].second += 1 ;		
		}
		char res;
		int minindex=s.size()-1;
		bool find = false;
		for (auto mp : m) {
			if (mp.second.second == 1) {
				find = true;
				if (mp.second.first <= minindex)
					res = mp.first;
				minindex = min(mp.second.first, minindex);				
			}		
		}
		if (find)
			cout << res << endl;
		else
			cout << -1 << endl;

	}
	
	return 0;
}
//
int main() {
	string s;

	while (cin >> s) {
		for (int i = 0; i < s.size(); i++) {
			if (s.find_first_of(s[i]) == s.find_last_of(s[i])) {
				cout << s[i] << endl;
				break;
			}
			if (i == s.size() - 1) {
				cout << -1 << endl;
				break;
			}
				
		}

	}

	return 0;
}

