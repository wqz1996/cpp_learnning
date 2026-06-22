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

