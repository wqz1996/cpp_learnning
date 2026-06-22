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
/************20有效的括号*******************/
class Solution {
public:
	bool isValid(string s) {
		stack<char> mystack;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '{' || s[i] == '[' || s[i] == '(') {
				mystack.push(s[i]);
			}
			else {
				if (mystack.size()==0)
					return false;
				char c = mystack.top();
				mystack.pop();
				char match;
				if (s[i] == ')')
					match = '(';
				else if (s[i] == ']')
					match = '[';
				else {
					assert(s[i] == '}');
					match = '{';
				}
					
				if (c != match) {
					return false;
				}

			}
		}
		if (mystack.size()!=0)
			return false;

		return true;
	}
};
int main() {
	string s{ "()" };
	cout<<Solution().isValid(s)<<endl;
	return 0;
} 