#include <iostream> // 使用处：第 83 行的 cin
#include <string> // 使用处：第 27 行的 string
#include <stack> // 使用处：第 30 行的 stack
#define N 100
using namespace std;
//表达式求解
//中缀表达式-后缀表达式（逆波兰表达式）
int prioritylevel(char ch){//优先级判断'('<'+'and'-'<'*'and'/'
	int level=0;
	switch (ch) {
	case '(':
		level = 1;
		break;
	case'+':
	case'-':
		level = 2;
		break;
	case'*':
	case'/':
		level = 3;
	default:
			break;
	}
	return level;

}
int calculate(string s) {
	int len = s.size();
	int i = 0;
	stack<int> data;
	while (i < len) {
		if (s[i] >= '0' && s[i] <= '9') {
			int num = 0;
			while (s[i] != ' ') {
				num = num * 10 + (s[i] - '0');
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
			int res = a + b;
			data.push(res);
			i++;
		}
		else if (s[i] == '-') {
			int b = data.top();
			data.pop();
			int a = data.top();
			data.pop();
			int res = a - b;
			data.push(res);
			i++;
		}
		else if (s[i] == '*') {
			int b = data.top();
			data.pop();
			int a = data.top();
			data.pop();
			int res = a * b;
			data.push(res);
			i++;
		}
		else if (s[i] == '/') {
			int b = data.top();
			data.pop();
			int a = data.top();
			data.pop();
			int res = a / b;
			data.push(res);
			i++;
		}
	}
	return data.top();

}
int main() {
	string s;
	while (cin >> s) {
		string behind;//后缀表达式
		stack<char> op;//运算符栈
		int len = s.size();
		int i = 0;
		char c;//运算符栈顶元素缓存
		while (i < len) {
			if (s[i] >= '0' && s[i] <= '9') {//如果是数字，直接保存
				int num = 0;
				do {
					num = num * 10 + (s[i] - '0');
					i++;
				} while (s[i] >= '0' && s[i] <= '9');
				
				behind += to_string(num);
				behind += ' ';
			}
			else if (s[i] == '(') {//左括号直接压入栈
				op.push(s[i]);
				i++;
			}
			else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {//运算符操作
				if (op.empty()) {//栈空则直接压入
					op.push(s[i]);
					i++;
				}
				else {//栈不空
					while (!op.empty()) {
						c = op.top();
						if (prioritylevel(s[i]) <= prioritylevel(c)) {//当前运算符比栈顶元素优先级低则弹出栈顶元素，直到当前元素优先级高于栈顶压入
							behind += c;
							op.pop();						
						}
						else
							break;
					
					}
					op.push(s[i]);//压入当前运算符
					i++;
				}
			}
			else if (s[i] == ')') {//如果是右括号
				while (op.top() != '(') {//一直弹出栈顶直到遇到左括号
					behind += op.top();
					op.pop();
				}
				op.pop();//弹出左括号，后缀表达式不包含括号
				i++;
			}
			else//如果是当前字符是其他字符则跳过不做保存
				i++;
		}
		while (!op.empty()) {//继续弹出运算符栈中的剩余运算符
			behind += op.top();
			op.pop();
		}
		int res = calculate(behind);
		cout << res << endl;

	}
	return 0;
}
