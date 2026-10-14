#include <iostream> // 使用处：第 44 行的 cout
#include <string> // 使用处：第 9 行的 string
#include <stack> // 使用处：第 10 行的 stack
#include <cassert> // 使用处：第 26 行的 assert(
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