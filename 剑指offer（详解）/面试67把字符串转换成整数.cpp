#include <climits> // 使用处：第 40 行的 INT_MAX
#include <iostream> // 使用处：第 88 行的 cout
#include <string> // 使用处：第 19 行的 string
using namespace std;
//面试题67. 把字符串转换成整数
// 写一个函数 StrToInt，实现把字符串转换成整数这个功能。
//不能使用 atoi 或者其他类似的库函数。
//注：首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格
//的字符为止。当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后
//面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数
//字，则直接将其与之后连续的数字字符组合起来，形成整数。该字符串除了有效的
//整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应
//该造成影响。注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、
//字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。
//在任何情况下，若函数不能进行有效的转换时，请返回 0。
class Solution {
public:

	int strToInt(string str) {
		if (str.empty())
			return 0;
		long res = 0;//防止超过int范围
		int i = 0;
		bool flag = true;//符号位
		while (i + 1 < str.size() && str[i] == ' ')//找到第一个不是空格的位置
			i++;
		if (str[i] == '-') {//判断第一个字符是否是‘+’‘-’
			flag = false;
			i++;//移动到符号的下一位计算数值
		}
		else if (str[i] == '+') {
			flag = true;
			i++;//移动到符号的下一位计算数值
		}
		while (i < str.size()) {
			if (str[i] <= '9' && str[i] >= '0')//将数字字符转换为数值
				res = 10 * res + str[i++] - '0';
			else//遇到最后一个不是数字字符的停止转换
				return res *= flag ? 1 : -1;//返回带符号的数值
			if (res > INT_MAX)//超过INT范围则表示为最大或最小值
				return flag ? INT_MAX : INT_MIN;
		}


		return res *= flag ? 1 : -1;
	}
};
//自己写的
class Solution {
public:
	int strToInt(string str) {
		if (str.empty())//空字符串直接返回0
			return 0;
		int begin = str.find_first_not_of(' ');//找到第一个不是空格的索引
		if (begin == -1)//全是空格begin=-1
			return 0;
		str = str.substr(begin);//截取字符
		int i = 0;
		int len = str.size();
		bool flag = true;//正负号标志
		long long sum = 0;//防止超范围
		if (str[0] == '-') {//第一个字符是‘-’更改符号标志位
			flag = false;
			i++;//跳过'-'
		}
		else if (str[0] == '+') {//第一个字符是'+'直接跳过即可
			i++;
		}
		else if (str[0] > '9' || str[0] < '0')//第一个字符不是'+'/'-'也不是数字字符则返回0
			return 0;
		while (i < len) {
			if (str[i] >= '0' && str[i] <= '9') {				
				sum = sum * 10 + str[i] - '0';
				if (sum > INT_MAX)//只要当前已经超过INT_MAX，根据符号位返回，不在计算下一个字符
					return flag ? INT_MAX : INT_MIN;
			}
			else {
				return flag ? sum : -sum;//遇到第一个不是数字字符，根据符号位返回当前sum
			}
			i++;
		}
		return flag ? sum : -sum;//所有字符均转化完成

	}
};
int main() {
	string s = "2147483648";
	cout << Solution().strToInt(s);

	return 0;
}
