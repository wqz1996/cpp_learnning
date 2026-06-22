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
//判断短字符串中的所有字符是否在长字符串中全部出现
int main() {
	string s1,s2;
	while (cin >> s1 >> s2) {
		bool res = true;
		for (int i = 0; i < s1.size(); i++) {
			if (s2.find(s1[i])!=string::npos)
				continue;
			else {
				res = false;
				break;
			}

		}
		if(res)
			cout<<"true"<<endl;
		else
			cout << "false" << endl;

	}
	return 0;
}
