#include <algorithm> // 使用处：第 31 行的 reverse(
#include <string> // 使用处：第 11 行的 string
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

