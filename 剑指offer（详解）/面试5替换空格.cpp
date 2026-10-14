#include <iostream> // 使用处：第 55 行的 cout
#include <string> // 使用处：第 9 行的 string
using namespace std;
//面试5 替换空格
//请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
/***************空间复杂度O(N)*******************/
class Solution {
public:
	string replaceSpace(string s) {
		string res;
		if (s.empty())
			return res;
		for (auto str : s) {
			if (str == ' ')
				res += "%20";
			else
				res += str;
		}
		return res;
	}
};
/*******************空间复杂度O(N)时间O(1)*************************/
class Solution1 {
public:
	string replaceSpace(string s) {
		int p1 = s.size()-1;//指向string中的最后一个元素
		int count = 0;
		for (auto str : s) {
			if (str == ' ')
				count++;
		}
		s.resize(p1 + 1 + 2 * count);//重新分配空间，nums.size()+2*count
		int p2 = s.size() - 1;//指向重分配空间的最后一个元素
		if (p2 <= p1)
			return s;
  		while (p1 >= 0) {//循环到p1指向第一个元素
			if (s[p1] == ' ') {
				p1--;//p1为空则指向下一个元素等待拷贝
				s[p2--] = '0';
				s[p2--] = '2';
				s[p2--] = '%';
			}
			else {
				s[p2--] = s[p1--];//s[p1]付给s[p2]，p2向前移动一个，p1也向前移动一个
			}

		}

		return s;
	}
};
int main()
{
	string s{ "We are happy" };
	cout<<Solution1().replaceSpace(s)<<endl;
	return 0;
}

