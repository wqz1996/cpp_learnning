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
int level(char s) {
	int levels = 0;
	switch (s)
	{
	case '(':
		levels = 1;
		break;
	case '+':
	case '-':
		levels = 2;
		break;
	case '*':
	case '/':
		levels = 3;
		break;
	default:
		break;
	}
	return levels;
}
string tobehind(string s) {
	int len = s.size();
	stack<char> op;
	string behind;
	int i = 0;
	while (i < len) {
		if (s[i] >= '0' && s[i] <= '9') {
			int num = 0;
			while (s[i] >= '0' && s[i] <= '9') {
				num = num * 10 + s[i] - '0';
				i++;
			}
			behind += to_string(num);
			behind += ' ';
		}
		else if (s[i] == '(') {
			op.push(s[i]);
			i++;
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			if (op.empty()) {
				op.push(s[i]);
				i++;
			}
			else {
				while (!op.empty() && level(s[i]) <= level(op.top())) {
					behind += op.top();
					op.pop();
				}
				op.push(s[i]);
				i++;
			}
		}
		else if (s[i] == ')') {
			while (!op.empty() && op.top() != '(') {
				behind += op.top();
				op.pop();
			}
			op.pop();
			i++;
		}
		else
			i++;
	}
	while (!op.empty()) {
		behind += op.top();
		op.pop();
	}
	return behind;
}
int calculate(string s) {
	int len = s.size();
	int i = 0;
	stack<int> data;
	while (i < len) {
		if (s[i] >= '0' && s[i] <= '9') {
			int num = 0;
			while (s[i] != ' ') {
				num = num * 10 + s[i] - '0';
				i++;
			}
			i++;
			data.push(num);
		}
		else if (s[i] == '+') {
			int b = data.top();
			data.pop();
			int a = data.top();
			data.pop();
			int sum = a + b;
			data.push(sum);
			i++;
		}
		else if (s[i] == '-') {
			int b = data.top();
			data.pop();
			int a = data.top();
			data.pop();
			int sum = a - b;
			data.push(sum);
			i++;
		}
		else if (s[i] == '*') {
			int b = data.top();
			data.pop();
			int a = data.top();
			data.pop();
			int sum = a * b;
			data.push(sum);
			i++;
		}
		else if (s[i] == '/') {
			int b = data.top();
			data.pop();
			int a = data.top();
			data.pop();
			int sum = a / b;
			data.push(sum);
			i++;
		}	
	}
	return data.top();
}
int main() {
	string s;
	while (cin >> s) {
		string behind = tobehind(s);
		int res = calculate(behind);
		cout << res << endl;
	}	
	return 0;
}