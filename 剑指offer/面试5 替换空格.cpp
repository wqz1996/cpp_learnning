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
using namespace std;
// 面试题5：替换空格
// 题目：请实现一个函数，把字符串中的每个空格替换成"%20"。例如输入“We are happy.”，
// 则输出“We%20are%20happy.”。
void replacespace(char* str, int length) {
	if (str == nullptr)
		return;
	int changelength=length;
	int spacenum = 0;
	for (int i = 0; i < length; i++) {
		if (str[i] == ' ') {
			spacenum++;
			changelength += 2;
		}
	}
	int p1 = length-1;
	int p2 = changelength-1;
	while (p1 >= 0&&p1 <= p2) {
		if (str[p1] == ' ') {
			str[p2--] = '0';
			str[p2--] = '2';
			str[p2--] = '%';
		}
		else {
			str[p2--] = str[p1];
		}
		p1--;
	}
}
/************在线IDE*****************/

int main()
{
	char s[13] = {"we are happy"};
	replacespace(s,13);
	return 0;

}



