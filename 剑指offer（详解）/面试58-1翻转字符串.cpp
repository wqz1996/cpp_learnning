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

