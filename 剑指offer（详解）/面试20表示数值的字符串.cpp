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
//面试题20.表示数值的字符串
// 题目：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
//例如，字符串"+100"、"5e2"、"-123"、"3.1416"、"0123"都表示数值，
//但"12e"、"1a3.14"、"1.2.3"、"+-5"、"-1E-16"及"12e+5.4"都不是。
/*********自写****************/
class Solution {
private:
	bool judge1(string s) {//判断底数
		if (s.empty())//若字符串为空则直接返回false
			return false;
		bool point = false;//小数点标记位
		int p1 = 0;
		bool res = false;//返回结果
		while (p1 < s.size()) {
			if (p1 == 0 && (s[p1] == '+' || s[p1] == '-')) {//若第一个字符是'+'或者'-'则跳过判断下一个字符
				p1++;
				continue;
			}
			else if (s[p1] == '.') {//小数点只能有一个
				if (point)//当point为true则证明已经存在一个小数点了，再次进入该判断则存在第二个小数点，返回false
					return false;
				point = true;
			}
			else if (s[p1] > '9' || s[p1] < '0') {//若存在0-9以外的字符返回false
				return false;
			}
			else {//不能直接在循环外返回true，因为需要排除掉上述不符合要求的字符，在下一次循环中才可以将结果置位true，防止只有不合法字符存在。例如s为'+'
				res = true;
			}
			p1++;
		}
		return res;
	}
	bool judge2(string s) {
		if (s.empty())
			return false;
		int p1 = 0;
		bool res = false;
		while (p1 < s.size()) {
			if (p1 == 0 && (s[p1] == '+' || s[p1] == '-')) {//若第一个字符是'+'或者'-'则跳过判断下一个字符
				p1++;
				continue;
			}
			else if (s[p1] > '9' || s[p1] < '0') {//指数中不存在小数点，因此合并到只判断数字即可
				return false;
			}
			else {
				res = true;
			}
			p1++;
		}
		return res;
	}

public:
	bool isNumber(string s) {
		int begin = s.find_first_not_of(' ');
		int end = s.find_last_not_of(' ');
		if (begin == string::npos)//若没有找到不是空格的元素则有效字符为空
			return false;
		s = s.substr(begin, end - begin + 1);//去除头部和尾部的空格
		int p1 = 0;
		while (p1 < s.size() && (s[p1] != 'e' && s[p1] != 'E')) {//找到e/E的位置
			p1++;
		}

		if (p1 == s.size())//若没找到e/E则不存在指数部分，直接判断底数即可
			return judge1(s);
		else
			return judge1(s.substr(0, p1)) && judge2(s.substr(p1 + 1));//分别判断底数和指数

	}
};
//没考虑包含大写E的情况
class Solution {
private:
	bool judgeP(string s) {//判断底数是否合法
		bool res = false;
		bool point = false;
		int n = s.size();
		for (int i = 0; i < n; i++) {
			if (s[i] == '+' || s[i] == '-') {//若存在'+'或'-'则必须是第一位
				if (i != 0)
					return false;
			}
			else if (s[i] == '.') {//只能存在一个'.'
				if (point)
					return false;
				point = true;
			}
			else if (s[i] < '0' || s[i]>'9')//数字必须在0-9范围
				return false;
			else
				res = true;
		}
		return res;
	}
	bool judgeS(string s) {//判断指数是否合法
		bool res = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '+' || s[i] == '-') {
				if (i != 0)
					return false;
			}
			else if (s[i] < '0' || s[i] > '9') {//指数中不能有小数点
				return false;
			}				
			else {
				res = true;
			}

		}
		//若直接循环跳出循环，证明存在e，但是指数为空，不合法
		return res;
	}
public:
	bool isNumber(string s) {
		int i = s.find_first_not_of(' ');
		if (i == string::npos)
			return false;
		int j = s.find_last_not_of(' ');
		if (j == string::npos)
			return false;
		s = s.substr(i, j - i + 1);//保存第一个不是空格和最后一个不是空格中间的字符
		if (s.empty())
			return false;

		int e = s.find('e');//找到e

		if (e == string::npos)//没有指数，只判断底数
			return judgeP(s);
		else
			return (judgeP(s.substr(0, e)) && judgeS(s.substr(e + 1)));

	}
};

int main()
{
	string s = "2e0";
	cout << Solution().isNumber(s);
	return 0;
}

