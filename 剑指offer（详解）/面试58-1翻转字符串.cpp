#include <sstream> // 使用处：第 14 行的 istringstream
#include <string> // 使用处：第 11 行的 string
#include <stack> // 使用处：第 12 行的 stack
using namespace std;
//面试题58 - I. 翻转单词顺序
// 题目：输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
//为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "
//，则输出"student. a am I"。
class Solution {
public:
	string reverseWords(string s) {
		stack<string> strstack;
		string res, str;
		istringstream ss(s);
		while (ss >> str) {//将string字符串以空格为分隔符输出
			strstack.push(str);
			strstack.push(" ");//每个字符串后面加一个空格
		}
		if (!strstack.empty())
			strstack.pop();//弹出最后一个空格
		while (!strstack.empty()) {
			res += strstack.top();
			strstack.pop();
		}
		return res;
	}
};
int main()
{
	string s = "I am a student";
	string res=Solution().reverseWords(s);

	return 0;
}

