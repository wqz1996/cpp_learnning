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
//面试题58 - II. 左旋转字符串
// 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
//请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和
//数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

class Solution {
public:
	string reverseLeftWords(string s, int n) {
		string temp= s.substr(0, n);
		string str=s.substr(n,s.size());
		str += temp;
		return str;
	}
};
/***************简单方法********************/
class Solution {
public:
	string reverseLeftWords(string s, int n) {
		return (s + s).substr(n, s.size());
	}
};
//局部翻转+整体翻转
class Solution {
public:
	string reverseLeftWords(string s, int n) {
		if (s.empty())
			return "";
		reverse(s.begin(), s.begin() + n);
		reverse(s.begin() + n, s.end());
		reverse(s.begin(), s.end());
		return s;
	}
};
int main()
{
	string s = "abcdefg";
	Solution().reverseLeftWords(s,2);
	return 0;
}

